#!/usr/bin/env ruby

require 'fileutils'

$types = {}
# Map of of all rune types to lookup table name
$typemap = {
  # Letter Types
  "Lu" => [:alphas,:uppers],       # Upper Case
  "Ll" => [:alphas,:lowers],       # Lower Case
  "Lt" => [:alphas,:titles],       # Title Case
  "LC" => [:alphas,:otherletters], # Cased Letter
  "Lm" => [:alphas,:otherletters], # Modifier Letter
  "Lo" => [:alphas,:otherletters], # Other Letter
  # Combining Marks
  "Mn" => [:marks],                # Non-Spacing Mark
  "Mc" => [:marks],                # Spacing Mark
  "Me" => [:marks],                # Enclosing Mark
  # Numbers
  "Nd" => [:numbers,:digits],      # Decimal Digit
  "Nl" => [:numbers],              # Letter Number
  "No" => [:numbers],              # Other Number
  # Punctuation
  "Pc" => [:punctuation],          # Connector Punctuation
  "Pd" => [:punctuation],          # Dash Punctuation
  "Ps" => [:punctuation],          # Open Punctuation
  "Pe" => [:punctuation],          # Close Punctuation
  "Pi" => [:punctuation],          # Initial Punctuation
  "Pf" => [:punctuation],          # Final Punctuation
  "Po" => [:punctuation],          # Other Punctuation
  # Symbols
  "Sm" => [:symbols],              # Math Symbol
  "Sc" => [:symbols],              # Currency Symbol
  "Sk" => [:symbols],              # Modifier Symbol
  "So" => [:symbols],              # Other Symbol
  # Separator
  "Zs" => [:spaces],               # Space Separator
  "Zl" => [:spaces],               # Line Separator
  "Zp" => [:spaces],               # Paragraph Separator
  # Other
  "Cc" => [:controls],             # Control
  "Cf" => [:other],                # Format
  "Cs" => [:other],                # Surrogate
  "Co" => [:other],                # Private Use
  "Cn" => [:other]                 # Unassigned
}
$typenames

def register_codepoint(types, val)
  types.each do |type|
    $types[type] ||= []
    $types[type] << val
  end
end

if ARGV.length != 2 then
    puts "Usage: unicode.rb DATABASE OUTDIR"
    puts "\nError: Incorrect number of arguments"
    exit 1
end

unicode_data = File.open(ARGV[0],"r")
unicode_data.each_line do |data|
  fields = data.split(';')
  types  = $typemap[fields[2]]
  stype  = fields[4]
  val    = fields[0].to_i(16)

  if (stype == "WS") || (stype == "S") || (stype == "B")
    register_codepoint([:spaces], val)
  elsif types.include? :uppers
    register_codepoint(types, val)
    register_codepoint([:tolowers], (fields[13] == "") ? val : fields[13].to_i(16))
  elsif types.include? :lowers
    register_codepoint(types, val)
    register_codepoint([:touppers], (fields[14] == "") ? val : fields[14].to_i(16))
  else
    register_codepoint(types, val)
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

def generate_typecheck_func(type, count)
    "extern int runeinrange(const void* a, const void* b);\n" +
    "bool is#{type.to_s.gsub(/s$/,'')}rune(Rune ch) {\n" +
    "    return (NULL != bsearch(&ch, #{type}, #{count}, 2 * sizeof(Rune), &runeinrange));\n" +
    "}\n"
end

def generate_type_table(type, altcase = [])
  if $types[type]
    ranges = get_ranges($types[type])
    pairs  = ranges.map{|r| "{ 0x#{r.first.to_s(16)}, 0x#{r.last.to_s(16)} }" }.join(",\n    ")
    File.open("#{ARGV[1]}/#{type.to_s}.c", "w") do |f|
      f.puts("#include <libc.h>\n\n")
      f.puts("static Rune #{type.to_s}[#{ranges.length}][2] = {")
      f.print('    ')
      f.puts(pairs)
      f.print("};\n\n");
      f.print(generate_typecheck_func(type, ranges.length))
    end
  end
end

FileUtils.mkdir_p ARGV[1]
generate_type_table(:uppers, :tolowers)
generate_type_table(:lowers, :touppers)
alltypes = $typemap.values.flatten.uniq - [:uppers, :lowers]
alltypes.each do |type|
    generate_type_table(type)
end

