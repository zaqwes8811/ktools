

git clone https://git.openwrt.org/openwrt/openwrt.git

Close

```

Key Specifications of Core-3568J SOM

https://en.t-firefly.com/product/core/core3568j.html


u-boot: Please install the Python3 elftools module

python3 -m pip install pyelftools

u-boot: Please install the swig package

sudo apt install swig


https://wiki.friendlyelec.com/wiki/index.php/NanoPi_R5S



AI Overview
The RK3568B2 and RK3568J are pin-compatible (FCCSP636L) variants of the Rockchip RK3568 processor. The main differences lie in their operating temperature range and performance: the RK3568J (Industrial) operates at -40 to +85°C (up to 1.4–1.8 GHz), while the RK3568B2 operates at -20 to +70°C (up to 2.0 GHz). This makes the B2 better for high-speed applications, while the J variant is more suitable for harsh environmental conditions.
```

docker run -it --rm   --memory=8g   --memory-swap=8g   --cpus=4   -v $(pwd):/openwrt   openwrt/sdk:rockchip-armv8


# Successful, may be build
docker run -it --rm -v "$(pwd):/workspace" -u $(id -u):$(id -g) \
	-v /etc/passwd:/etc/passwd:ro \
	-v /etc/group:/etc/group:ro \
	-v /etc/shadow:/etc/shadow:ro \
	ubuntu:24.04 bash

Can't install

sudo apt-get install build-essential libncurses5-dev gawk git \
  libssl-dev gettext zlib1g-dev swig unzip time xsltproc python3 \
  python3-setuptools python3-yaml python3-pyelftools wget rsync file


# From docker

```
cd openwrt

./run_docker.sh

cd /workspace/openwrt

./scripts/feeds update -a
./scripts/feeds install -a

make menuconfig

# Select Radxa ROCK 3B

make -j1 V=sc

```