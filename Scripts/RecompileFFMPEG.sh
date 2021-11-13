# !/bin/bash
rm -rf ~/ffmpeg_build ~/bin/{ffmpeg,ffprobe,ffplay,x264,x265} ~/ffmpeg_sources
cd ../../Augmentedx264
PATH="$HOME/bin:$PATH" PKG_CONFIG_PATH="$HOME/ffmpeg_build/lib/pkgconfig" ./configure --prefix="$HOME/ffmpeg_build" --bindir="$HOME/bin" --enable-static --enable-pic && \
PATH="$HOME/bin:$PATH" make -j12 && \
make -j12 install
cd ..
mkdir ~/ffmpeg_sources && \
cd ~/ffmpeg_sources && \
wget -O ffmpeg-snapshot.tar.gz https://git.ffmpeg.org/gitweb/ffmpeg.git/snapshot/1eca11f81a0204acfc85748c5f8d3c95719d8bab.tar.gz && \
tar xvzf ffmpeg-snapshot.tar.gz && \
mv ffmpeg-1eca11f ffmpeg && \
cd ffmpeg && \
PATH="$HOME/bin:$PATH" PKG_CONFIG_PATH="$HOME/ffmpeg_build/lib/pkgconfig" ./configure \
  --prefix="$HOME/ffmpeg_build" \
  --pkg-config-flags="--static" \
  --extra-cflags="-I$HOME/ffmpeg_build/include" \
  --extra-ldflags="-L$HOME/ffmpeg_build/lib" \
  --extra-libs="-lpthread -lm" \
  --bindir="$HOME/bin" \
  --enable-gpl \
  --enable-libass \
  --enable-libfreetype \
  --enable-libvorbis \
  --enable-libx264 \
  --enable-pthreads && \
PATH="$HOME/bin:$PATH" make -j12 && \
make -j12 install && \
hash -r
cd ..
cd ..
cd bin
