#!/usr/bin/env ruby

require 'fileutils'
require 'stringio'

# Check if we have the right number of arguments, bail otherwise
if ARGV.length != 2 then
    puts "Usage: unicode.rb DATABASE OUTDIR"
    puts "\nError: Incorrect number of arguments"
    exit 1
end

# Struct definition for representing a unicode character
UnicodeChar = Struct.new(
  :value,
  :name,
  :general_cat,
  :class,
  :bidir_cat,
  :decomp_map,
  :dec_value,
  :digit_val,
  :numeric_val,
  :mirrored,
  :name_1x,
  :comment,
  :toupper,
  :tolower,
  :totitle,
)

# Map of all Unicode Character Database entries by general category type
$types = { all: [] }

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

#------------------------------------------------------------------------------

# Register a character in the designated type tables combining adjacent
# characters into ranges
def register_codepoint(types, val)
  types.each do |type|
    $types[type] ||= []
    last = $types[type][-1]
    if (last.kind_of? Array) and ((last[-1].value + 1) == val.value)
        last << val
    elsif (not last.nil?) and (not last.kind_of? Array) and ((last.value + 1) == val.value)
        $types[type][-1] = [last, val]
    else
        $types[type] << val
    end
  end
end

# Generate a rune type checking function using the singles and ranges tables
def generate_typecheck_func(type, numranges, numsingles)
    out = StringIO.new
    out.print "extern int runeinrange(const void* a, const void* b);\n\n"
    out.print "bool is#{type.to_s.gsub(/s$/,'')}rune(Rune ch) {\n"
    if numsingles == 0
        out.print "    return (NULL != bsearch(&ch, ranges, #{numranges}, 2 * sizeof(Rune), &runeinrange));\n"
    else
        out.print "    return ((NULL != bsearch(&ch, singles, #{numsingles}, sizeof(Rune), &runeinrange)) || \n"
        out.print "            (NULL != bsearch(&ch, ranges, #{numranges}, 2 * sizeof(Rune), &runeinrange)));\n"
    end
    out.print "}\n"
    out.string
end

# Generates rune type tables organized by singles and ranges
def generate_type_tables(type)
  ranges, singles = $types[type].partition {|e| e.kind_of? Array }
  puts "Generating #{ARGV[1]}/#{type.to_s}.c"
  File.open("#{ARGV[1]}/#{type.to_s}.c", "w") do |f|
    f.puts("#include <libc.h>\n\n")
    table = singles.map{|e| "0x#{e.value.to_s(16)}" }.join(",\n    ")
    f.print("static Rune singles[#{singles.length}] = {\n    #{table}\n};\n\n") if singles.length > 0
    table = ranges.map{|r| "{ 0x#{r.first.value.to_s(16)}, 0x#{r.last.value.to_s(16)} }" }.join(",\n    ")
    f.print("static Rune ranges[#{ranges.length}][2] = {\n    #{table}\n};\n\n")
    f.print(generate_typecheck_func(type, ranges.length, singles.length))
  end
end

def generate_to_func(type, tblsz)
    out = StringIO.new
    out.print "extern int runeinrange(const void* a, const void* b);\n\n"
    out.print "Rune #{type}rune(Rune ch) {\n"
    out.print "    Rune* to = bsearch(&ch, mappings, #{tblsz}, 2 * sizeof(Rune), &runeinrange);\n"
    out.print "    return (to == NULL) ? ch : to[1];\n"
    out.print "}\n"
    out.string
end

def generate_to_table(type)
  mappings = $types[:all].select{|e| e[type] > 0 }
  puts "Generating #{ARGV[1]}/#{type.to_s}.c"
  File.open("#{ARGV[1]}/#{type.to_s}.c", "w") do |f|
    f.print "#include <libc.h>\n\n"
    f.print "static Rune mappings[#{mappings.length}][2] = {\n"
    mappings.each do |e|
      f.print "    { 0x#{e.value.to_s(16)}, 0x#{e[type].to_s(16)} },\n"
    end
    f.print "};\n\n"
    f.print generate_to_func(type, mappings.length)
  end
end

#------------------------------------------------------------------------------

# Read in the unicode character database and sort it into type classes
unicode_data = File.open(ARGV[0],"r")
unicode_data.each_line do |data|
  char = UnicodeChar.new(*data.split(';'))
  char.value    = char.value.to_i(16)
  char.tolower = char.tolower.to_i(16)
  char.toupper = char.toupper.to_i(16)
  char.totitle = char.totitle.to_i(16)
  types  = $typemap[char.general_cat]
  bicat  = char.bidir_cat
  $types[:all] << char
  if (bicat == "WS") || (bicat == "S") || (bicat == "B")
    register_codepoint([:spaces], char)
  else
    register_codepoint(types, char)
  end
  #register_codepoint([:tolower], char) if char.to_lower != 0
  #register_codepoint([:toupper], char) if char.to_upper != 0
  #register_codepoint([:totitle], char) if char.to_title != 0
end
unicode_data.close()

# Generate the runetype files into the designated directory
FileUtils.mkdir_p ARGV[1]
$typemap.values.flatten.uniq.each do |type|
    generate_type_tables(type)
end
generate_to_table(:tolower)
generate_to_table(:toupper)
generate_to_table(:totitle)

