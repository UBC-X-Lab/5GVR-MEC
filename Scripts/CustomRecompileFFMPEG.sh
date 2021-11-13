# !/bin/bash
rm -rf ~/ffmpeg_build ~/bin/{ffmpeg,ffprobe,ffplay,x264,x265} ~/ffmpeg_custom
cd ../../Augmentedx264/
PATH="$HOME/bin:$PATH" PKG_CONFIG_PATH="$HOME/ffmpeg_build/lib/pkgconfig" ./configure --prefix="$HOME/ffmpeg_build" --bindir="$HOME/bin" --enable-static --enable-pic && \
PATH="$HOME/bin:$PATH" make -j12 && \
make -j12 install
cd ..
mkdir ~/ffmpeg_custom && \
cd ~/ffmpeg_custom && \
cp -r ../ffmpeg_sources/ffmpeg ./ffmpeg && \
cd ffmpeg
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
  --enable-libxcb \
  --enable-pthreads && \
PATH="$HOME/bin:$PATH" make -n -j12 && \
make -j12 install && \
hash -r
cd ..
cd ..
cd bin
