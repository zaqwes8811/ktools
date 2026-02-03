FROM ubuntu:24.04

RUN apt update && apt-get install -y build-essential libncurses5-dev gawk git \
  libssl-dev gettext zlib1g-dev swig unzip time xsltproc python3 \
  python3-setuptools python3-yaml python3-pyelftools wget rsync file

RUN apt update && apt-get install -y xz-utils zstd

RUN cd /opt && wget https://downloads.openwrt.org/snapshots/targets/rockchip/armv8/openwrt-toolchain-rockchip-armv8_gcc-14.3.0_musl.Linux-x86_64.tar.zst \
    && ls -la &&  tar -xvf openwrt-toolchain-rockchip-armv8_gcc-14.3.0_musl.Linux-x86_64.tar.zst

RUN apt update && apt-get install -y python3.12-venv python3-pip
RUN apt update && apt-get install -y strace
# RUN apt update && apt-get install -y \
#     build-essential ccache ecj fastjar file g++ gawk \
#     gettext git java-propose-classpath libelf-dev libncurses5-dev \
#     libncursesw5-dev libssl-dev python2.7 python3 python3-dev \
#     python3-distutils python3-pip python3-setuptools rsync subversion \
#     swig time unzip wget xsltproc zlib1g-dev

#RUN pip3 install --user pyelftools

#ENV HOME /workspace