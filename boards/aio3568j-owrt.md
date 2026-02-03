
# Start

`./run_docker.sh`

git clone https://git.openwrt.org/openwrt/openwrt.git

More relailale:
git clone https://github.com/openwrt/openwrt.git

Close

cd openwrt && git checkout tags/v24.10.5

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
wget https://downloads.openwrt.org/snapshots/targets/rockchip/armv8/openwrt-toolchain-rockchip-armv8_gcc-14.3.0_musl.Linux-x86_64.tar.zst

python3 -m venv venv


rm .config

./scripts/ext-toolchain.sh --toolchain \
		/opt/openwrt-toolchain-rockchip-armv8_gcc-14.3.0_musl.Linux-x86_64/toolchain-aarch64_generic_gcc-14.3.0_musl/ \
		--config rockchip_armv8

make menuconfig  # select board


mistery
```
make[2]: Entering directory '/workspace/openwrt/scripts/config'
make[2]: 'conf' is up to date.
make[2]: Leaving directory '/workspace/openwrt/scripts/config'
Checking 'python3-pyelftools'... failed.
Checking 'python3-dev'... ok.
Checking 'python3-setuptools'... failed.
Checking 'swig'... ok.

u-boot: Please install the Python3 elftools module
u-boot: Please install the Python3 setuptools module
```


$(STAGING_DIR_HOST)/bin/python3
