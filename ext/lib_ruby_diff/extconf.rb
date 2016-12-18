require 'mkmf'

raise unless have_library('rsync')
have_header('librsync.h')

create_makefile('lib_ruby_diff/lib_ruby_diff')
