#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on 26.11.2021

@author: mj-xmr
"""

import os
import sys
import time
import shutil
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
    parser.add_argument('-l', '--lto',       default=False, action='store_true', help="link time optimization (Release case; default: OFF)")
    parser.add_argument('-d', '--debug',     default=False, action='store_true', help="build debug (default: OFF)")
    parser.add_argument('-p', '--pch',       default=False, action='store_true', help="build pch   (Dev case; default: OFF)")
    parser.add_argument('-u', '--unity',     default=False, action='store_true', help="build unity (CI case;  default: OFF)")
    parser.add_argument('-q', '--build-qt',  default=False, action='store_true', help="build QT apps (default: OFF)")
    parser.add_argument('--build-r',         default=False, action='store_true', help="build R support (default: OFF)")
    parser.add_argument('-w', '--no-wx',     default=False, action='store_true', help="don't build WX apps (default: OFF)")
    parser.add_argument('-i', '--no-install',default=False, action='store_true', help="don't install (default: OFF)")
    parser.add_argument('-t', '--no-tests',  default=False, action='store_true', help="don't build Tests (default: OFF)")
    parser.add_argument('-r', '--run-demo',  default=False, action='store_true', help="run demo (default: OFF)")
    parser.add_argument('-c', '--compiler',  default="", help='compiler ({}; default: autodetect)'.format('/'.join(COMPILERS)))
    parser.add_argument('-j', '--proc',      default=NPROC, type=int, help="number of cores to use (default: all)")
    parser.add_argument('-m', '--make',      default="make", help="'make' program (for ex.: ninja; default: make)")
    parser.add_argument('-g', '--generator', default=GENERATOR, help='Generator of project files (default: "{}")'.format(GENERATOR))
    parser.add_argument('-a', '--path',      default=".",   help="Run path")
    # TODO: select clang or mingw, if gcc is not available
    return parser

def build(args):
    print("Args = ", args)
    if args.lto and args.shared:
        print("Enforcing a static build for the LTO to make sense.")
        args.shared = False
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
    #if platform.system() == 'Darwin':
        #prefix += 'PATH="$(brew --prefix qt5)/bin:$PATH"' # https://github.com/leela-zero/leela-zero/issues/2177 
    #    pass
    if platform.system() == 'Windows':
        prefix = ""
        #args.generator = "MinGW Makefiles"
        args.generator = "MSYS Makefiles"
        MINGW_PREFIX="x86_64-w64-mingw32"
        cccompiler=MINGW_PREFIX + "-gcc"
        cpcompiler=MINGW_PREFIX + "-g++"
        make = " mingw32-make "
        args.compiler = cccompiler

    cmd = prefix + ' cmake  -S {} -B .'.format(path)
    if args.generator:
        cmd += NL + '-G "{}"'.format(args.generator)
    cmd += NL + '-DUSE_STATIC={}' .format(OFF if args.shared else ON)
    cmd += NL + '-DUSE_LTO={}'    .format(ON  if args.lto    else OFF)
    cmd += NL + '-DUSE_DEBUG={}'  .format(ON  if args.debug  else OFF)
    cmd += NL + '-DUSE_UNITY={}'  .format(ON  if args.unity  else OFF)
    cmd += NL + '-DUSE_PCH={}'    .format(ON  if args.pch    else OFF)
    cmd += NL + '-DBUILD_QT={}'   .format(ON  if args.build_qt else OFF) # Optional
    cmd += NL + '-DBUILD_WX={}'   .format(OFF if args.no_wx    else ON ) # Optional
    cmd += NL + '-DBUILD_TESTS={}'.format(OFF if args.no_tests else ON ) # Optional
    cmd += NL + '-DBUILD_BOOST={}'.format(ON) # Required
    cmd += NL + '-DWITH_FEATURE_R={}'.format(ON if args.build_r else OFF) # TODO: Disabled for now
    if args.compiler:
        cmd += NL + '-DCMAKE_C_COMPILER="{}"'.format(cccompiler) 
        cmd += NL + '-DCMAKE_CXX_COMPILER="{}"'.format(cpcompiler)
        if platform.system() == 'Windows':
            cmd += NL + '-DCMAKE_MAKE_PROGRAM="{}"'.format(make.strip())
            
    if platform.system() == 'Windows':
        cmd += NL + '&&' +  make + proc
        subprocess.run(cmd, shell=True, check=True)
        if not args.no_install:
            subprocess.run(make + " install", shell=True, check=True)
        subprocess.run(ctest, shell=True, check=True)   
    else:
        cmd += NL + '&&' +  make + proc + '||' + make
        if not args.no_install:
            cmd += '&&' + make + proc_local + 'install'
        cmd += NL + '&& (' + ctest + proc_local + '||' + ctest + ')'

        print('Build command:\n')
        print(cmd)
        print('')
        proc = subprocess.run(cmd, shell=True, check=True)

    #print(cmd)
def run_demo(args):
    os.chdir(DIR_BIN)
    exports_r = ""
    if platform.system() == 'Linux':
        exports_r = "&& export R_HOME=/usr/lib/R && export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$R_HOME/lib"
    elif platform.system() == 'Darwin':
        dir_framework = '/Library/Frameworks/R.framework/Resources'
        dir_osx11 = '/usr/local/Cellar/r/4.1.2/lib/R'
        if os.path.isdir(dir_osx11):
            dir_framework = dir_osx11
        exports_r = "&& export R_HOME={} && export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$R_HOME/lib".format(dir_framework)
    
    cmd = ""
    cmd += ' export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:lib' # TODO: Solve in CMake?
    cmd += exports_r
    cmd += '&& ./tsqsim --help'
    cmd += '&& ./tsqsim'

    if platform.system() == 'Windows':
        #subprocess.run("ls ../..", shell=True, check=True)
        shutil.move('../../data', '.') # TODO: Ugly
        shutil.move('../../../src/tsqsim-lib/static', '.') # TODO: Even uglier
        cmd = "tsqsim.exe --help && tsqsim.exe"

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
