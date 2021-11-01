#!/bin/bash
rm -rf ~/librist_build ~/librist_source
mkdir ~/librist_source && \
cd ~/librist_source && \
wget -O librist.tar.gz 'https://code.videolan.org/rist/librist/-/archive/v0.2.0/librist-v0.2.0.tar.gz' && \
tar xvzf librist.tar.gz && \
cd librist-v0.2.0 && \ 
mkdir build && cd build && \
meson .. --default-library=static && \
ninja &
BACK_PID=$!
wait $BACK_PID
mv ~/librist_source/librist-v0.2.0/build ~/librist_build
cp ~/librist_source/librist-v0.2.0/include/librist/librist.h ~/librist_build/include/librist.h