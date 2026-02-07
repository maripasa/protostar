#!/bin/bash

PICOW_PATH="/media/$USER/RPI-RP2/"
PT_OUT="./build/paint_tool.out"
P_NAME="protostar"

build_paint_tool() {
  echo -e "\033[33;1;4mDebug paint_tool flag used, compiling paint_tool\033[0m"
  gcc -I./lib/draw ./src/paint_tool.c ./lib/draw/draw.c -o $PT_OUT
  if [ -f $PT_OUT ]; then
    $PT_OUT
  else
    echo -e "\033[31;1;4mFile ($PT_OUT) could not be found.\033[0m"
  fi
  exit 0
}

build_project() {
  cmake -S . -B build -DPICO_BOARD=pico_w && \
  cmake --build build --target $P_NAME

  if [ ! -d $PICOW_PATH ]; then
    echo -e "\033[33;1;4mPICOW_PATH ($PICOW_PATH) DOES NOT EXIST, ENABLE WRITE IN BOARD.\033[0m"
  else
      cp ./build/*.uf2 $PICOW_PATH
      echo ".uf2 FILE MOVED TO BOARD."
  fi
}

if [ "$1" == "pt" ]; then
  build_paint_tool
else
  build_project
fi
