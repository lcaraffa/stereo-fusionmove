#!/bin/bash

export SCRIPT_DIR="$(cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd  )/"
libs=("${SCRIPT_DIR}/extern/QPBO" "${SCRIPT_DIR}/")


COMPILE_TYPE=Release
#COMPILE_TYPE=Debug

COMPLILE_FLAGS=""
#-DCMAKE_BUILD_TYPE=Release ..
function build {
    
    for i in ${!libs[@]}; do
	echo "------------------------------------------" 
	echo "[$0] Installing/Updating ${libs[i]} ..."
	mkdir -p ${libs[i]}/build-$COMPILE_TYPE
	cd ${libs[i]}/build-$COMPILE_TYPE
	#cmake -DCMAKE_BUILD_TYPE=$COMPILE_TYPE -DCMAKE_CXX_FLAGS=-pg ..
	cmake -DCMAKE_BUILD_TYPE=$COMPILE_TYPE $COMPILE_FLAGS ..
	make $1
	rc=$?; if [[ $rc != 0 ]]; then exit $rc; fi
	cd -
    done


    echo [$0] supports -jN flag to speed up compilation
    echo [$0] Done !!!
}

function clean {

    for i in ${!libs[@]}; do
	echo "------------------------------------------" 
	echo "[$0] Cleaning ${libs[i]} ..."
	cd ${libs[i]}
	rm -rf build-$COMPILE_TYPE
	rm -rf lib/*
	cd -
    done

    echo [$0] Done !!!

}

$@
