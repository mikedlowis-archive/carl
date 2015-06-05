#!/usr/bin/env ruby
require './modules/build-system/setup'

#------------------------------------------------------------------------------
# Environment Definitions
#------------------------------------------------------------------------------
# Define the default compiler environment
main_env = BuildEnv.new do |env|
  env["CFLAGS"]  += ['-O3', '-Wall', '-Wextra', '--std=c99', '--pedantic']
  env["CPPPATH"] += Dir['source/']
end

#------------------------------------------------------------------------------
# Release Build Targets
#------------------------------------------------------------------------------
# Build the library
main_env.Library('libc.a', FileList['source/**/*.c'])

#------------------------------------------------------------------------------
# Test Build Targets
#------------------------------------------------------------------------------
if Opts[:profile].include? "test"
  # Do nothing for now
end

