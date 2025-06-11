FROM ubuntu:22.04


RUN apt-get update && apt-get install -y gcc g++ gperf bison flex texinfo help2man make libncurses5-dev \
    python3-dev autoconf automake libtool libtool-bin gawk wget bzip2 xz-utils unzip \
    patch libstdc++6 rsync git meson ninja-build dos2unix \
    libmpc-dev libgmp3-dev \
    bc \
    python3-venv python3-pip \
    pkg-config libglib2.0-dev libpixman-1-dev

WORKDIR /opt/

RUN chmod -R 777 /opt/
RUN useradd -m builder
ENV HOME=/home/builder

USER builder

RUN git clone https://github.com/crosstool-ng/crosstool-ng.git \
	&& cd crosstool-ng && git checkout tags/crosstool-ng-1.27.0 -b ct-ng \
	&& find . -type f -exec dos2unix {} \; \
	&& ./bootstrap && ./configure --prefix=/opt/crosstool-ng-root/bin

RUN cd crosstool-ng && make install

RUN mkdir ~/src && cd ~/src/ && wget https://zlib.net/fossils/zlib-1.2.12.tar.gz

ENV PATH="$PATH:/opt/crosstool-ng-root/bin/bin"

RUN cd crosstool-ng && ct-ng arm-unknown-linux-gnueabi
RUN cd crosstool-ng && export CT_PARALLEL_JOBS=4 && ct-ng build

RUN cd crosstool-ng && ct-ng aarch64-unknown-linux-gnu
RUN cd crosstool-ng && export CT_PARALLEL_JOBS=4 && ct-ng build

ENV PATH="$PATH:$HOME/x-tools/arm-unknown-linux-gnueabi/bin"

COPY helloworld.c $HOME

RUN cd ~ && arm-unknown-linux-gnueabi-gcc helloworld.c -o helloworld

USER root

# Qemu
WORKDIR /opt/
RUN mkdir tools && cd tools && wget https://download.qemu.org/qemu-9.2.4.tar.xz \
    && tar xvJf qemu-9.2.4.tar.xz

RUN pip3 install tomli

RUN cd tools/qemu-9.2.4 && ./configure --target-list="arm-softmmu,aarch64-softmmu" --enable-virtfs \
    && make

ENV PATH="$PATH:/opt/tools/qemu-9.2.4/build/qemu-bundle/usr/local/bin"

ENV PATH="$PATH:$HOME/x-tools/aarch64-unknown-linux-gnu/bin"