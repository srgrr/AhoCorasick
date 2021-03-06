#!/bin/bash
# downloads and installs googletest version 1.7.0

# please, read the script if you are not sure about what it does

if [ "$(id -u)" != "0" ]; then
   echo "[ ERROR ]: This script must be run as root. Please, read the scripts commands to know what this script does." 1>&2
   exit 1
fi

apt-get -qq update
apt-get install -y libgtest-dev
wget https://github.com/google/googletest/archive/release-1.7.0.tar.gz
tar xf release-1.7.0.tar.gz
cd googletest-release-1.7.0
cmake -DBUILD_SHARED_LIBS=OFF
make
cp -a include/gtest /usr/include
cp -a libgtest_main.a libgtest.a /usr/lib/
cd ..
rm googletest-release-1.7.0 -rf
rm release-1.7.0.tar.gz
