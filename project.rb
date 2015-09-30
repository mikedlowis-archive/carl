project do
  env.CFLAGS   = '-g -O3 -Wall -Wextra --std=c99 --pedantic'
  env.CPPFLAGS = ['-Isource/', '-Imodules/atf/source']

  library 'libcarl.a', Dir['source/**/*.c']
  program 'test_libc', Dir["tests/**/*.c", "modules/atf/source/*.c"] + ["libcarl.a"]
  command 'Tests', 'test_libc', CMD: './test_libc'
end
