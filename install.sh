#!/bin/sh

LIB_DIR=$(pwd)

rm -rfd "$LIB_DIR/build" 
mkdir -p "$LIB_DIR/build" 
cd "$LIB_DIR/build"

read -p $'Do you want to build shared libs? (Y/n) ' user_i

if [[ "$user_i" =~ ^[Yy]$ ]] then 
  echo -e "Building shared library..."
  cmake -S .. -B . -DFLUX_SHARED_LIBS=ON -DFLUX_INSTALL=ON -DCMAKE_INSTALL_PREFIX=/usr/local 
  build --build . --target install 
else 
  cmake -S .. -B . -DCMAKE_INSTALL_PREFIX=/usr/local -DFLUX_INSTALL=ON  
  cmake --build . --target install 
fi

read -p $'Do you want to build library examples? (Y/n) ' user_input 

if [[ "$user_input" =~ ^[Yy]$ ]]; then 
    echo -e "Building library examples..."
    cmake -S .. -B . -DFLUX_INSTALL=OFF -DBUILD_EXAMPLES=ON 
    cmake --build . 
else 
    echo -e "Examples will not be built"
fi 

 
