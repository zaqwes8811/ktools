#!/bin/bash

cd crosstool-ng && export PATH="$PATH:$(pwd)/bin/bin" && cd -

export PATH="$PATH:$HOME/x-tools/arm-unknown-linux-gnueabi/bin"

cd qemu-7.2.0 && export PATH="$PATH:$(pwd)/build/arm-softmmu" && cd -