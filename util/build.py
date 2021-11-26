#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on 26.11.2021

@author: mj-xmr
"""

import os
import sys
import time
import subprocess
import argparse
import multiprocessing as mp

NPROC=mp.cpu_count()
COMPILERS=['gcc', 'clang', 'mingw']
DIR_BUILD_BASE='build'
DIR_BIN='bin'
GENERATOR="CodeBlocks - Unix Makefiles"
OFF='OFF'
ON='ON'
NL=' \ \n'
NL=' '

def get_parser():
    parser = argparse.ArgumentParser()
    parser.add_argument('-s', '--shared',    default=False, action='store_true', help="build shared libraries (default: OFF)")
    parser.add_argument('-d', '--debug',     default=False, action='store_true', help="build debug (default: OFF)")
    parser.add_argument('-u', '--unity',     default=False, action='store_true', help="build unity (CI case; default: OFF)")
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

    os.chdir(args.path)
    print("Build dir = " + build_dir)
    os.makedirs(build_dir, exist_ok=True)
    os.chdir(build_dir)
    print("CWD = " +  os.getcwd())
    os.makedirs(DIR_BIN, exist_ok=True)
    make = ' {} '.format(args.make)
    proc = ' -j {} '.format(args.proc)
    ctest = ' ctest --output-on-failure '
    cccompiler = args.compiler
    cpcompiler = 'g++' if args.compiler == 'gcc' else args.compiler + '++'
    
    cmd = "cmake -G '{}'".format(args.generator) + ' -S ../.. -B .'
    cmd += NL + '-DUSE_STATIC={}'.format(OFF if args.shared else ON)
    cmd += NL + '-DUSE_DEBUG={}'.format (ON  if args.debug  else OFF)
    cmd += NL + '-DUSE_UNITY={}'.format (ON  if args.unity  else OFF)
    cmd += NL + '-DBUILD_BOOST={}'.format(ON) # Required
    cmd += NL + '-DBUILD_BOOST={}'.format(ON) # Required
    cmd += NL + '-DBUILD_BOOST={}'.format(ON) # Required
    if args.compiler:
        cmd += NL + '-DCMAKE_C_COMPILER="{}"'.format(cccompiler) 
        cmd += NL + '-DCMAKE_CXX_COMPILER="{}"'.format(cpcompiler)    
    cmd += NL + '&&' +  make + proc + '||' + make + '&&' + make + proc + 'install'
    cmd += NL + '&&' + ctest + proc + '||' + ctest

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

def main(args):
    build(args)
    if args.run_demo:
        run_demo(args)

if __name__ == "__main__":
    parser = get_parser()
    args = parser.parse_args()
    main(args)
