

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



cp .config .config.backup

# 2. Полная очистка
make distclean
rm -rf tmp/ build_dir/ staging_dir/ bin/

# 3. Восстановить конфиг
cp .config.backup .config

# 4. Обновить feeds
./scripts/feeds update -a
./scripts/feeds install -a

# 5. Собрать заново
make toolchain/install -j$(nproc)
make -j$(nproc) V=s 2>&1 | tee rebuild.log


# Know issues

at feeds update:

git fetch-pack: unexpected disconnect while reading sideband packet fatal: early EOF fatal: index-pack failed

Updating feed 'packages' from 'https://git.openwrt.org/feed/packages.git' ...
Cloning into './feeds/packages'...
remote: Enumerating objects: 7396, done.
remote: Counting objects: 100% (7396/7396), done.
remote: Compressing objects: 100% (6095/6095), done.
error: RPC failed; curl 18 transfer closed with outstanding read data remaining
fetch-pack: unexpected disconnect while reading sideband packet
fatal: early EOF
fatal: index-pack failed
failed.

export HOME=/workspace

Solution:
https://stackoverflow.com/questions/38618885/error-rpc-failed-curl-transfer-closed-with-outstanding-read-data-remaining