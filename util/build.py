#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on 26.11.2021

@author: mj-xmr
"""

import os
import sys
import time
import platform
import subprocess
import argparse
import multiprocessing as mp

NPROC=mp.cpu_count()
ICECC_DIR = '/usr/lib/icecc/bin/'
ICECC='icecc'
GCC='gcc'
COMPILERS=[GCC, ICECC, 'clang', 'mingw']
DIR_BUILD_BASE='build'
DIR_BIN='bin'
GENERATOR="CodeBlocks - Unix Makefiles"
OFF='OFF'
ON='ON'
#NL=' \ \n'
NL=' '

def get_parser():
    parser = argparse.ArgumentParser()
    parser.add_argument('-s', '--shared',    default=False, action='store_true', help="build shared libraries (default: OFF)")
    parser.add_argument('-d', '--debug',     default=False, action='store_true', help="build debug (default: OFF)")
    parser.add_argument('-u', '--unity',     default=False, action='store_true', help="build unity (CI case; default: OFF)")
    parser.add_argument('-q', '--build-qt',  default=False, action='store_true', help="build QT apps (default: OFF)")
    parser.add_argument('-r', '--run-demo',  default=False, action='store_true', help="run demo (default: OFF)")
    parser.add_argument('-c', '--compiler',  default="", help='compiler ({}; default: autodetect)'.format('/'.join(COMPILERS)))
    parser.add_argument('-j', '--proc',      default=NPROC, type=int, help="number of cores to use (default: all)")
    parser.add_argument('-m', '--make',      default="make", help="'make' program (for ex.: ninja; default: make)")
    parser.add_argument('-g', '--generator', default=GENERATOR, help='Generator of project files (default: "{}")'.format(GENERATOR))
    parser.add_argument('-p', '--path',      default=".",   help="Run path")
    # TODO: select clang or mingw, if gcc is not available
    return parser

def build(args):
    print("Args = ", args)
    build_dir = DIR_BUILD_BASE + '/'
    if args.compiler:
        build_dir += args.compiler
    else:
        build_dir += 'default'
    build_dir += '-' + ('shared' if args.shared else 'static')
    build_dir += '-' + ('debug'  if args.debug  else 'release')

    path = os.path.abspath(args.path)
    os.chdir(path)
    print("Build dir = " + build_dir)
    os.makedirs(build_dir, exist_ok=True)
    os.chdir(build_dir)
    print("CWD = " +  os.getcwd())
    os.makedirs(DIR_BIN, exist_ok=True)
    make = ' {} '.format(args.make)
    proc_str = ' -j {} '
    proc       = proc_str.format(args.proc)
    proc_local = proc_str.format(args.proc if args.proc <= NPROC else NPROC)
    ctest = ' ctest --output-on-failure '

    cccompiler = args.compiler
    if args.compiler == GCC:
        cpcompiler = 'g++'
    elif args.compiler == ICECC:
        cccompiler = ICECC_DIR + 'cc'
        cpcompiler = ICECC_DIR + 'c++'
    else:
        cpcompiler = args.compiler + '++'
        
    prefix = "set -e\n"
    print("System = " + platform.system())
    if platform.system() == 'Darwin':
        #prefix += 'PATH="$(brew --prefix qt5)/bin:$PATH"' # https://github.com/leela-zero/leela-zero/issues/2177 
        pass

    cmd = prefix + " cmake -G '{}'".format(args.generator) + ' -S {} -B .'.format(path)
    cmd += NL + '-DUSE_STATIC={}' .format(OFF if args.shared else ON)
    cmd += NL + '-DUSE_DEBUG={}'  .format(ON  if args.debug  else OFF)
    cmd += NL + '-DUSE_UNITY={}'  .format(ON  if args.unity  else OFF)
    cmd += NL + '-DBUILD_QT={}'   .format(ON  if args.build_qt else OFF) # Optional
    cmd += NL + '-DBUILD_BOOST={}'.format(ON) # Required
    if args.compiler:
        cmd += NL + '-DCMAKE_C_COMPILER="{}"'.format(cccompiler) 
        cmd += NL + '-DCMAKE_CXX_COMPILER="{}"'.format(cpcompiler)    
    cmd += NL + '&&' +  make + proc + '||' + make + '&&' + make + proc_local + 'install'
    cmd += NL + '&& (' + ctest + proc_local + '||' + ctest + ')'

    print('Build command:\n')
    print(cmd)
    print('')
    proc = subprocess.run(cmd, shell=True, check=True)

    #print(cmd)
def run_demo(args):
    os.chdir(DIR_BIN)
    cmd = ""
    cmd += ' export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:lib' # TODO: Solve in CMake?
    cmd += '&& ./tsqsim --help'
    cmd += '&& ./tsqsim'

    proc = subprocess.run(cmd, shell=True, check=True)
    proc = subprocess.run(cmd, shell=True, check=True) # Run again to test the deserialization

def main(args):
    build(args)
    if args.run_demo:
        run_demo(args)

if __name__ == "__main__":
    parser = get_parser()
    args = parser.parse_args()
    main(args)
