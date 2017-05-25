#!/bin/bash -e
./install_gtest.sh
python run_all_tests.py
python3 perform_all_experiments.py
