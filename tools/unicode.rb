#!/usr/bin/env ruby

$types = {}
# Map of of all rune types to lookup table name
$typemap = {
  # Letter Types
  "Lu" => :uppers,        # Upper Case
  "Ll" => :lowers,        # Lower Case
  "Lt" => :titles,        # Title Case
  "LC" => :other_letters, # Cased Letter
  "Lm" => :other_letters, # Modifier Letter
  "Lo" => :other_letters, # Other Letter
  # Combining Marks
  "Mn" => :marks,         # Non-Spacing Mark
  "Mc" => :marks,         # Spacing Mark
  "Me" => :marks,         # Enclosing Mark
  # Numbers
  "Nd" => :numbers,       # Decimal Digit
  "Nl" => :numbers,       # Letter Number
  "No" => :numbers,       # Other Number
  # Punctuation
  "Pc" => :punctuation,   # Connector Punctuation
  "Pd" => :punctuation,   # Dash Punctuation
  "Ps" => :punctuation,   # Open Punctuation
  "Pe" => :punctuation,   # Close Punctuation
  "Pi" => :punctuation,   # Initial Punctuation
  "Pf" => :punctuation,   # Final Punctuation
  "Po" => :punctuation,   # Other Punctuation
  # Symbols
  "Sm" => :symbols,       # Math Symbol
  "Sc" => :symbols,       # Currency Symbol
  "Sk" => :symbols,       # Modifier Symbol
  "So" => :symbols,       # Other Symbol
  # Separator
  "Zs" => :spaces,        # Space Separator
  "Zl" => :spaces,        # Line Separator
  "Zp" => :spaces,        # Paragraph Separator
  # Other
  "Cc" => :controls,      # Control
  "Cf" => :other,         # Format
  "Cs" => :other,         # Surrogate
  "Co" => :other,         # Private Use
  "Cn" => :other          # Unassigned
}

def register_codepoint(type, val)
  $types[type] ||= []
  $types[type] << val
end

unicode_data = File.open(ARGV[0],"r")
unicode_data.each_line do |data|
  fields = data.split(';')
  type  = $typemap[fields[2]]
  stype = fields[4]
  val   = fields[0].to_i(16)

  if (stype == "WS") || (stype == "S") || (stype == "B")
    register_codepoint(:spaces, val)
  elsif type == :uppers
    register_codepoint(type, val)
     register_codepoint(:tolowers, (fields[13] == "") ? val : fields[13].to_i(16))
  elsif type == :lowers
    register_codepoint(type, val)
    register_codepoint(:touppers, (fields[14] == "") ? val : fields[14].to_i(16))
  else
    register_codepoint(type, val)
  end
end
unicode_data.close()
$types[:touppers].keep_if{|v| v > 0 }
$types[:tolowers].keep_if{|v| v > 0 }

def get_ranges(table)
  table.inject([]) do |spans, n|
    if spans.empty? || spans.last.last != n - 1
      spans + [n..n]
    else
      spans[0..-2] + [spans.last.first..n]
    end
  end
end

def generate_type_table(type, altcase = [])
  ranges = get_ranges($types[type])
  pairs  = ranges.map{|r| "0x#{r.first.to_s(16)}, 0x#{r.last.to_s(16)}" }.join(",\n    ")
  File.open("#{type.to_s}.c", "w") do |f|
    f.puts("Rune #{type.to_s}[#{ranges.length*2}] = {")
    f.print('    ')
    f.puts(pairs)
    f.puts("};");
  end
end

generate_type_table(:uppers, :tolowers)
generate_type_table(:lowers, :touppers)
generate_type_table(:titles)
generate_type_table(:other_letters)
generate_type_table(:marks)
generate_type_table(:numbers)
generate_type_table(:punctuation)
generate_type_table(:symbols)
generate_type_table(:spaces)
generate_type_table(:controls)

