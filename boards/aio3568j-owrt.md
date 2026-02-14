
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

# New build

```
cd /workspace/openwrt

make -j1 V=sc

dtb
cp openwrt/build_dir/target-aarch64-openwrt-linux-musl_musl/linux-rockchip_armv8/image-rk3568-rock-3b.dtb .

build_dir/target-aarch64-openwrt-linux-musl_musl/linux-rockchip_armv8/linux-6.6.119



dtc -I dtb -O dts -o rock.dts image-rk3568-rock-3b.dtb

dtc -I dtb -O dts -o firefly.dts rk3568-firefly-aioj.dtb


openwrt/build_dir/target-aarch64-openwrt-linux-musl_musl/linux-rockchip_armv8/linux-6.6.119/arch/arm64/boot/dts/rockchip/rk3568-rock-3b.dts
  openwrt/build_dir/target-aarch64-openwrt-linux-musl_musl/linux-rockchip_armv8/linux-6.6.119/arch/arm64/boot/dts/rockchip/rk3568.dtsi
    openwrt/build_dir/target-aarch64-openwrt-linux-musl_musl/linux-rockchip_armv8/linux-6.6.119/arch/arm64/boot/dts/rockchip/rk356x.dtsi

./kernel/arch/arm64/boot/dts/rockchip/rk3568-firefly-aioj.dts

rk356x_sdk-linux5.10/kernel/arch/arm64/boot/dts/rockchip/rk3568-firefly-aioj.dts
  rk356x_sdk-linux5.10/kernel/arch/arm64/boot/dts/rockchip/rk3568-firefly-aioj.dtsi
    rk356x_sdk-linux5.10/kernel/arch/arm64/boot/dts/rockchip/rk3568-firefly-port.dtsi
      rk356x_sdk-linux5.10/kernel/arch/arm64/boot/dts/rockchip/rk3568-firefly-core.dtsi
        rk356x_sdk-linux5.10/kernel/arch/arm64/boot/dts/rockchip/rk3568.dtsi
      rk356x_sdk-linux5.10/kernel/arch/arm64/boot/dts/rockchip/rk3568-linux.dtsi


diff -u rk356x_sdk-linux5.10/kernel/arch/arm64/boot/dts/rockchip/rk3568.dtsi openwrt/build_dir/target-aarch64-openwrt-linux-musl_musl/linux-rockchip_armv8/linux-6.6.119/arch/arm64/boot/dts/rockchip/rk356x.dtsi


/workspace/openwrt/build_dir/target-aarch64-openwrt-linux-musl_musl/linux-rockchip_armv8/tmp

openwrt-rockchip-armv8-radxa_rock-3b-squashfs-sysupgrade.img


openwrt/build_dir/target-aarch64-openwrt-linux-musl_musl/linux-rockchip_armv8/tmp


export EXPORT_DIR=openwrt/build_dir/target-aarch64-openwrt-linux-musl_musl/linux-rockchip_armv8/tmp/


rm -rf owrt.img && \
gunzip -dkf $EXPORT_DIR/openwrt-rockchip-armv8-radxa_rock-3b-squashfs-sysupgrade.img.gz || true && \
	cp $EXPORT_DIR/openwrt-rockchip-armv8-radxa_rock-3b-squashfs-sysupgrade.img owrt.img


patch from 

/workspace/openwrt/dl/linux-6.6.119.tar.xz

cat /sys/kernel/debug/pinctrl/*/pinmux-pins

ls -la /sys/class/gpio/
cat /sys/kernel/debug/gpio | grep 89

RK_PD1: 2*32 + 3*8 + 1 = 64 + 24 + 1 = 89

root@OpenWrt:~# 

cat /sys/kernel/debug/pinctrl/*/pinmux-pins | grep -A2 -B2 "89"

pin 87 (gpio2-23): (MUX UNCLAIMED) (GPIO UNCLAIMED)
pin 88 (gpio2-24): 3c0000000.pcie (GPIO UNCLAIMED) function pcie20 group pcie20m1-pins
pin 89 (gpio2-25): 3c0000000.pcie gpio2:89 function pcie20 group pcie20m1-pins
pin 90 (gpio2-26): (MUX UNCLAIMED) (GPIO UNCLAIMED)
pin 91 (gpio2-27): (MUX UNCLAIMED) gpio2:91
root@OpenWrt:~# 

cat /sys/kernel/debug/pinctrl/*/pinmux-pins | grep -A2 -B2 "91"

pin 89 (gpio2-25): 3c0000000.pcie gpio2:89 function pcie20 group pcie20m1-pins
pin 90 (gpio2-26): (MUX UNCLAIMED) (GPIO UNCLAIMED)
pin 91 (gpio2-27): (MUX UNCLAIMED) gpio2:91
pin 92 (gpio2-28): 3c0800000.pcie (GPIO UNCLAIMED) function pcie30x2 group pcie30x2m1-pins
pin 93 (gpio2-29): 3c0800000.pcie (GPIO UNCLAIMED) function pcie30x2 group pcie30x2m1-pins


rm -rf openwrt/build_dir/target-aarch64-openwrt-linux-musl_musl/linux-rockchip_armv8/tmp/*


diff -Naur --exclude="*.o" --exclude="*.cmd" --exclude="*.ko" --exclude="Image" \
		 --exclude="generated" --no-dereference \
     linux-6.6.119.orig/ linux-6.6.119/ | \
     sed 's|linux-6.6.119.orig/|a/|g; s|linux-6.6.119/|b/|g' > /workspace/0000-aio3568j-gmac01.patch

# TODO() Apply patch at build time

```

2. Install iperf3

```
cd /workspace/openwrt

make menuconfig
```

3. Dongles

```
Bus 002 Device 001: ID 1d6b:0003 Linux Foundation 3.0 root hub
Bus 001 Device 004: ID 06cb:00bd Synaptics, Inc. 
Bus 001 Device 003: ID 04f2:b67c Chicony Electronics Co., Ltd Integrated Camera
Bus 001 Device 007: ID 093a:2510 Pixart Imaging, Inc. Optical Mouse
Bus 001 Device 006: ID 8087:0029 Intel Corp. 
Bus 001 Device 005: ID 058f:9540 Alcor Micro Corp. AU9540 Smartcard Reader
Bus 001 Device 019: ID a69c:5721 aicsemi Aic MSC
Bus 001 Device 001: ID 1d6b:0002 Linux Foundation 2.0 root hub

sudo usb_modeswitch -K -v 0xa69c -p 0x5721

doesn't work


Bus 002 Device 001: ID 1d6b:0003 Linux Foundation 3.0 root hub
Bus 001 Device 004: ID 06cb:00bd Synaptics, Inc. 
Bus 001 Device 003: ID 04f2:b67c Chicony Electronics Co., Ltd Integrated Camera
Bus 001 Device 007: ID 093a:2510 Pixart Imaging, Inc. Optical Mouse
Bus 001 Device 006: ID 8087:0029 Intel Corp. 
Bus 001 Device 005: ID 058f:9540 Alcor Micro Corp. AU9540 Smartcard Reader
Bus 001 Device 025: ID 0bda:b851 Realtek Semiconductor Corp. 802.11ax WLAN Adapter
Bus 001 Device 001: ID 1d6b:0002 Linux Foundation 2.0 root hub

```