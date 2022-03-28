#!/bin/bash
build_prefix="${PWD}"
mkdir -p bin
pushd bin
echo ${build_prefix}
../avrdude-6.4/configure --prefix=${build_prefix} --sysconfdir=${build_prefix}/config
make clean
make
popd
