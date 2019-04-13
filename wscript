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
	conf.load('sdl2')
	conf.env.append_unique('DEFINES', 'XASH_SDL')
	conf.env.append_unique('DEFINES', 'WES_MANGLE_PREPEND')
	return

def build(bld):
	source = bld.path.ant_glob(['src/*.c'])
	libs = [ 'SDL2' ]
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
