'''
    This script builds and runs all the implemented tests
    (see Makefile or test folder)

    You need to have Google Test installed in order to be able to run
    these tests.

    These tests check correctness and efficiency but they are NOT experiments
'''
import os
import glob
import subprocess

def main():
  if subprocess.call(['make', 'tests_allinone']) != 0:
    exit(1)
  exit_code = subprocess.call(['./testbin/main'])
  exit(exit_code)

if __name__ == "__main__":
  main()
