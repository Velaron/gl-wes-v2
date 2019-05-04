#! /usr/bin/env python
# encoding: utf-8
# mittorn, 2018

from waflib import Logs
import os

top = '.'

def options(opt):
	# stub
	return

def configure(conf):
	# stub
	if conf.env.DEST_OS2 != 'android':
		conf.load('sdl2')
		conf.env.append_unique('DEFINES', 'XASH_SDL')
	else:
		conf.check_cc(lib='log')
	conf.env.append_unique('DEFINES', 'WES_MANGLE_PREPEND')
	return

def build(bld):
	source = bld.path.ant_glob(['src/*.c'])
	libs = []
	if bld.env.DEST_OS2 != 'android':
		libs += [ 'SDL2' ]
	else: libs += ['LOG']
	includes = [ 'src/' ]

	bld.stlib(
		source   = source,
		target   = 'gl-wes-v2',
		features = 'c',
		includes = includes,
		use      = libs,
		install_path = bld.env.LIBDIR,
		subsystem = bld.env.MSVC_SUBSYSTEM
	)
