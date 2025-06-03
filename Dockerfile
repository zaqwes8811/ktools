FROM ubuntu:22.04


RUN apt-get update && apt-get install -y gcc g++ gperf bison flex texinfo help2man make libncurses5-dev \
    python3-dev autoconf automake libtool libtool-bin gawk wget bzip2 xz-utils unzip \
    patch libstdc++6 rsync git meson ninja-build dos2unix \
    libmpc-dev libgmp3-dev \
    bc

WORKDIR /opt/

RUN chmod -R 777 /opt/
RUN useradd -m builder
ENV HOME=/home/builder

USER builder

RUN git clone https://github.com/crosstool-ng/crosstool-ng.git \
	&& cd crosstool-ng && git checkout tags/crosstool-ng-1.25.0 -b ct-ng \
	&& find . -type f -exec dos2unix {} \; \
	&& ./bootstrap && ./configure --prefix=/opt/crosstool-ng-root/bin

RUN cd crosstool-ng && make install

RUN mkdir ~/src && cd ~/src/ && wget https://zlib.net/fossils/zlib-1.2.12.tar.gz

ENV PATH="$PATH:/opt/crosstool-ng-root/bin/bin"

RUN cd crosstool-ng && ct-ng arm-unknown-linux-gnueabi
RUN cd crosstool-ng && ct-ng build

ENV PATH="$PATH:$HOME/x-tools/arm-unknown-linux-gnueabi/bin"

COPY helloworld.c $HOME

RUN cd ~ && arm-unknown-linux-gnueabi-gcc helloworld.c -o helloworld

USER root
