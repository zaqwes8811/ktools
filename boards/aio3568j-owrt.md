
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

./tmp/info/.packageinfo-boot_uboot-armsr
./tmp/.kconfig-armsr_armv8
./tmp/.kconfig-armsr_armv7


./scripts/ext-toolchain.sh --toolchain \
		/opt/openwrt-toolchain-rockchip-armv8_gcc-14.3.0_musl.Linux-x86_64/toolchain-aarch64_generic_gcc-14.3.0_musl/ \
		--config armsr_armv8

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


export EXPORT_DIR=openwrt/build_dir/target-aarch64-openwrt-linux-musl_musl/linux-rockchip_armv8/tmp/ \
&& rm -rf owrt.img && \
gunzip -dkf $EXPORT_DIR/openwrt-rockchip-armv8-radxa_rock-3b-squashfs-sysupgrade.img.gz || true && \
	cp $EXPORT_DIR/openwrt-rockchip-armv8-radxa_rock-3b-squashfs-sysupgrade.img owrt.img


patch from 

/workspace/openwrt/dl/linux-6.6.119.tar.xz

cat /sys/kernel/debug/pinctrl/*/pinmux-pins

ls -la /sys/class/gpio/
cat /sys/kernel/debug/gpio | grep 89

cat /sys/kernel/debug/gpio | grep 98

RK_PD1: 2*32 + 3*8 + 1 = 64 + 24 + 1 = 89

root@OpenWrt:~# 

cat /sys/kernel/debug/pinctrl/*/pinmux-pins | grep -A2 -B2 "89"

cat /sys/kernel/debug/pinctrl/*/pinmux-pins | grep -A2 -B2 "98"

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


diff -Naur --exclude="*.o" --exclude="*.cmd" --exclude="*.ko" --exclude="*.dtb" --exclude="*.a" --exclude="Image" \
		 --exclude="generated" --no-dereference \
     linux-6.6.119.orig/ linux-6.6.119/ | \
     sed 's|linux-6.6.119.orig/|a/|g; s|linux-6.6.119/|b/|g' > ./0004-aio3568j-usb.patch

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

Bus 001 Device 036: ID 0bda:b851 Realtek Semiconductor Corp. 802.11ax WLAN Adapter

sudo /usr/sbin/usb_modeswitch -K -v 0x0bda -p 0xb851

```

4. Local

```
DS: Как настроить AP6275S на RK3568 под OpenWrt

drivers/net/wireless/Kconfig

obj-$(CONFIG_BCMDHD) += rockchip_wlan/rkwifi/bcmdhd/

make kernel_menuconfig

source "drivers/net/wireless/rockchip_wlan/Kconfig"
obj-$(CONFIG_BCMDHD) += rockchip_wlan/


/workspace/openwrt$ cp -R /workspace/openwrt/build_dir/target-aarch64-openwrt-linux-musl_musl/linux-rockchip_armv8/linux-6.6.119/drivers/net/wireless/rockchip_wlan/rkwifi package/kernel/bcmdhd/src/

make package/kernel/bcmdhd/compile V=s

disable Wereless lan in kernel?

Never enable wireless options in kernel_menuconfig

Always use OpenWrt's kmod-* packages for wireless drivers

grep -E "CONFIG_(CFG80211|MAC80211|WLAN)" .config | grep -v "PACKAGE_kmod"  # kernel

make kernel_oldconfig  # clean all soucr ceod


ehow to enable CONFIG_CFG80211_HEADERS

ifneq ($(KERNELRELEASE),)
    CFLAGS_dhd_config.o += -Wno-error=attribute-warning -Wno-stringop-overflow
endif

MAC*0... as ko modules

all 3 shoule be M

New soucrce code will be unpacked

make target/linux/clean
make target/linux/compile



diff -Naur --exclude="*.o" --exclude="*.cmd" --exclude="*.ko" --exclude="*.dtb" --exclude="Image" \
		 --exclude="generated" --no-dereference \
     bcmdhd-dkms-101.10.591.52.27-6.orig/ bcmdhd-dkms-101.10.591.52.27-6/ | \
     sed 's|bcmdhd-dkms-101.10.591.52.27-6.orig/|a/|g; s|bcmdhd-dkms-101.10.591.52.27-6/|b/|g' > /workspace/0001-wifi-aioxj.patch
```

4. Dongle Archer
```
enable lsusb

Kernel modules  ---> USB Support  ---> <*> kmod-usb-core
Kernel modules  ---> USB Support  ---> <*> kmod-usb2           (for USB 2.0)
Kernel modules  ---> USB Support  ---> <*> kmod-usb3           (for USB 3.0, if your hardware supports it)
```

5. Usb dts

```

# Aio

arch/arm64/boot/dts/rockchip/rk3568.dtsi
usbdrd30: usbdrd {
usbhost30: usbhost {


usb_host0_ehci: usb@fd800000 {
usb_host0_ohci: usb@fd840000 {
usb_host1_ehci: usb@fd880000 {
usb_host1_ohci: usb@fd8c0000 {

usb2phy0_grf: syscon@fdca0000 {
usb2phy1_grf: syscon@fdca8000 {

usb2phy0: usb2-phy@fe8a0000 {
		u2phy0_host: host-port {
		u2phy0_otg: otg-port {
usb2phy1: usb2-phy@fe8b0000 {


arch/arm64/boot/dts/rockchip/rk3568-firefly-core.dtsi
&u2phy0_host {  // shorted name
&u2phy0_otg {
&u2phy1_host {
&u2phy1_otg {
&usb2phy0 {
&usb2phy1 {
&u2phy0_host {
	phy-supply = <&vcc5v0_host>;
	status = "okay";
};

	vcc5v0_host: vcc5v0-host-regulator {
		compatible = "regulator-fixed";
		enable-active-high;
		gpio = <&gpio0 RK_PD6 GPIO_ACTIVE_HIGH>;
		pinctrl-names = "default";
		pinctrl-0 = <&vcc5v0_host_en>;
		regulator-name = "vcc5v0_host";
		regulator-always-on;
		regulator-boot-on;
	};

		usb {
		vcc5v0_host_en: vcc5v0-host-en {
			rockchip,pins = <0 RK_PD6 RK_FUNC_GPIO &pcfg_pull_none>;
		};

		vcc5v0_otg_en: vcc5v0-otg-en {
			rockchip,pins = <0 RK_PA5 RK_FUNC_GPIO &pcfg_pull_none>;
		};
	};

&u2phy0_otg {
	vbus-supply = <&vcc5v0_otg>;
	status = "okay";
};

&u2phy1_host {
	phy-supply = <&vcc5v0_host>;
	status = "okay";
};

&u2phy1_otg {
	phy-supply = <&vcc5v0_host>;
	status = "okay";
};

&usb2phy0 {
	status = "okay";
};

&usb2phy1 {
	status = "okay";
};


&usb_host0_ehci {
&usb_host0_ohci {
&usb_host1_ehci {
&usb_host1_ohci {
&usbdrd_dwc3 {
&usbdrd30 {
&usbhost_dwc3 {
&usbhost30 {

usb {
	vcc5v0_host_en: vcc5v0-host-en {
	vcc5v0_otg_en: vcc5v0-otg-en {
};

arch/arm64/boot/dts/rockchip/rk3568-firefly-aioj.dtsi
&usbdrd_dwc3 {
&pinctrl {
usb {
	vcc_hub_power_en: vcc-hub-power-en {
	vcc_hub_reset_en: vcc-hub-reset-en {
};
vcc_hub_power: vcc-hub-power-regulator {
	pinctrl-0 = <&vcc_hub_power_en>;
};

vcc_hub_reset: vcc-hub-reset-regulator {
	pinctrl-0 = <&vcc_hub_reset_en>;
};
```


```
# Radxa

USB3
usb_host0_xhci: usb@fcc00000 {
usb_host1_xhci: usb@fd000000 {

usb_host0_ehci: usb@fd800000 {  Usb2.0
usb_host0_ohci: usb@fd840000 {

usb_host1_ehci: usb@fd880000 {
usb_host1_ohci: usb@fd8c0000 {

usb2phy0_grf: syscon@fdca0000 {
usb2phy1_grf: syscon@fdca8000 {

usb2phy0: usb2phy@fe8a0000 {
		usb2phy1_host: host-port {
		usb2phy1_otg: otg-port {
usb2phy1: usb2phy@fe8b0000 {

/arch/arm64/boot/dts/rockchip/rk3568-pinctrl.dtsi

arch/arm64/boot/dts/rockchip/rk3568-rock-3b.dts
vcc5v0_usb_host: regulator-5v0-vcc-usb-host {
vcc5v0_usb_otg: regulator-5v0-vcc-usb-otg {

&usb_host0_xhci {

usb {
	usb_host_pwren_h: usb-host-pwren-h {
	usb_otg_pwren_h: usb-otg-pwren-h {
};

&usb_host0_ehci {
&usb_host0_ohci {
&usb_host0_xhci {
&usb_host1_xhci {
&usb2phy0 {
&usb2phy0_host {
&usb2phy0_otg {
&usb2phy1 {
&usb2phy1_otg {

&usb2phy0_host {
	phy-supply = <&vcc5v0_usb_host>;
	status = "okay";
};

	vcc5v0_usb_host: regulator-5v0-vcc-usb-host {
		compatible = "regulator-fixed";
		enable-active-high;
		gpios = <&gpio0 RK_PA6 GPIO_ACTIVE_HIGH>;
		pinctrl-names = "default";
		pinctrl-0 = <&usb_host_pwren_h>;
		regulator-name = "vcc5v0_usb_host";
		regulator-min-microvolt = <5000000>;
		regulator-max-microvolt = <5000000>;
		vin-supply = <&vcc5v0_sys>;
	};
		usb {
			usb_host_pwren_h: usb-host-pwren-h {
				rockchip,pins = <0 RK_PA6 RK_FUNC_GPIO &pcfg_pull_none>;
			};

			usb_otg_pwren_h: usb-otg-pwren-h {
				rockchip,pins = <0 RK_PA5 RK_FUNC_GPIO &pcfg_pull_none>;
			};
		};

		vcc5v0_sys: regulator-5v0-vcc-sys {
			compatible = "regulator-fixed";
			regulator-name = "vcc5v0_sys";
			regulator-always-on;
			regulator-boot-on;
			regulator-min-microvolt = <5000000>;
			regulator-max-microvolt = <5000000>;
		};


&usb2phy0_otg {
	phy-supply = <&vcc5v0_usb_otg>;
	status = "okay";
};

&usb2phy1 {
	status = "okay";
};

&usb2phy1_host {
	phy-supply = <&vcc5v0_usb_host>;
	status = "okay";
};

&usb2phy1_otg {
	phy-supply = <&vcc5v0_usb_host>;
	status = "okay";
};

usb {
	vcc5v0_host_en: vcc5v0-host-en {
	vcc5v0_otg_en: vcc5v0-otg-en {
};

```

```
ls /sys/class/phy/
dmesg | grep -i phy | grep -i usbdmesg | grep -i phy | grep -i usb


root@OpenWrt:~# ls /sys/class/phy/
phy-fe820000.phy.5      phy-fe8a0000.usb2phy.0  phy-fe8c0000.phy.6
phy-fe830000.phy.3      phy-fe8a0000.usb2phy.1
phy-fe840000.phy.4      phy-fe8b0000.usb2phy.2
root@OpenWrt:~# dmesg | grep -i phy | grep -i usb
root@OpenWrt:~# lsmod | grep phy
root@OpenWrt:~# 

```

root@OpenWrt:~# ls -la /sys/firmware/devicetree/base/ | grep -i usb
drwxr-xr-x    2 root     root             0 Dec 17 21:45 regulator-5v0-vcc-usb-host
drwxr-xr-x    2 root     root             0 Dec 17 21:45 regulator-5v0-vcc-usb-otg
drwxr-xr-x    4 root     root             0 Dec 17 21:45 usb2phy@fe8a0000
drwxr-xr-x    4 root     root             0 Dec 17 21:45 usb2phy@fe8b0000
drwxr-xr-x    2 root     root             0 Dec 17 21:45 usb@fcc00000
drwxr-xr-x    2 root     root             0 Dec 17 21:45 usb@fd000000
drwxr-xr-x    2 root     root             0 Dec 17 21:45 usb@fd800000
drwxr-xr-x    2 root     root             0 Dec 17 21:45 usb@fd840000
drwxr-xr-x    2 root     root             0 Dec 17 21:45 usb@fd880000
drwxr-xr-x    2 root     root             0 Dec 17 21:45 usb@fd8c0000


#####################

.config in kernel_menuconfig

General setup  --->
    [*] Kernel .config support
    [*]   Enable access to .config through /proc/config.gz (NEW)


# List all USB-related device tree nodes
ls -la /sys/firmware/devicetree/base/ | grep -i usb

# Check for PHY nodes specifically
find /sys/firmware/devicetree/base/ -name "*phy*" | grep -i usb



####################


diff -Naur -x "*.o" -x "*.cmd" -x "*.ko" -x "*.dtb" -x "*.a" -x "Image" -x "generated" --no-dereference \
     linux-6.6.119.orig/ linux-6.6.119/ | \
     sed 's|linux-6.6.119.orig/|a/|g; s|linux-6.6.119/|b/|g' > ./0004-aio3568j-usb.patch


cat > exclude_patterns.txt << 'EOF'
*.o
*.cmd
*.ko
*.dtb
*.a
*Image
generated
*/generated/*
EOF


lsusb -t


&combphy0 {
	status = "okay";
};

&combphy1 {
	status = "okay";
};

&combphy2 {
	status = "okay";
};

// HUB (критически важно для AIO-3568J!)
&usbhub {
    status = "okay";
};

Типичная структура USB на AIO-3568J
Согласно аппаратной документации :

USB 3.0 OTG — через контроллер dwc3

USB 3.0 Host — через хаб GL3523

USB 2.0 Host — через EHCI/OHCI контроллеры


USB контроллеры успешно загружены:
text
[    2.880732] ehci-platform fd800000.usb: EHCI Host Controller
[    2.880772] ohci-platform fd840000.usb: Generic Platform OHCI controller
[    2.880988] ehci-platform fd880000.usb: EHCI Host Controller
[    2.881269] ohci-platform fd8c0000.usb: Generic Platform OHCI controller
[    2.873403] usb usb1: xHCI Host Controller
✅ Хабы обнаружены:
text
[    3.264069] usb 1-1: USB2.1 Hub, Manufacturer: GenesysLogic
[    3.404452] usb 2-1: USB3.2 Hub, Manufacturer: GenesysLogic


0dfdf@pixelnas:~$ lsusb -v 2>/dev/null | grep -E "Bus|idVendor|idProduct|bDeviceClass" | head -30
Bus 006 Device 001: ID 1d6b:0001 Linux Foundation 1.1 root hub
  bDeviceClass            9 Hub
  idVendor           0x1d6b Linux Foundation
  idProduct          0x0001 1.1 root hub
Bus 005 Device 001: ID 1d6b:0002 Linux Foundation 2.0 root hub
  bDeviceClass            9 Hub
  idVendor           0x1d6b Linux Foundation
  idProduct          0x0002 2.0 root hub
Bus 004 Device 001: ID 1d6b:0001 Linux Foundation 1.1 root hub
  bDeviceClass            9 Hub
  idVendor           0x1d6b Linux Foundation
  idProduct          0x0001 1.1 root hub
Bus 003 Device 001: ID 1d6b:0002 Linux Foundation 2.0 root hub
  bDeviceClass            9 Hub
  idVendor           0x1d6b Linux Foundation
  idProduct          0x0002 2.0 root hub
Bus 002 Device 002: ID 05e3:0620 Genesys Logic, Inc. GL3523 Hub
  bDeviceClass            9 Hub
  idVendor           0x05e3 Genesys Logic, Inc.
  idProduct          0x0620 GL3523 Hub
Bus 002 Device 001: ID 1d6b:0003 Linux Foundation 3.0 root hub
  bDeviceClass            9 Hub
  idVendor           0x1d6b Linux Foundation
  idProduct          0x0003 3.0 root hub
Bus 001 Device 003: ID 0bda:1a2b Realtek Semiconductor Corp. RTL8188GU 802.11n WLAN Adapter (Driver CDROM Mode)
  bDeviceClass            0 
  idVendor           0x0bda Realtek Semiconductor Corp.
  idProduct          0x1a2b RTL8188GU 802.11n WLAN Adapter (Driver CDROM Mode)
Bus 001 Device 002: ID 05e3:0610 Genesys Logic, Inc. Hub
  bDeviceClass            9 Hub


  lsusb -v 2>/dev/null | grep -E "Bus|idVendor|idProduct|bDeviceClass" | head -30

##############################

Firefly:

1.
GPIO0_D6 -> USB30_HOST_PWREN_H

2.
SDMMC0_PWREN/SATA_MP_SWITCH/PCIE20_CLKREQn_M0/GPIO0_A5_d - USB_OTG_PWREN_H_GPIO0_A5

3.
HUB_USB1_PWREN_H - LCDC_D9/VOP_BT1120_D1/GMAC1_TXD2_M0/I2S3_MCLK_M0/SDMMC2_D1_M1/GPIO3_A2_d
GPIO3_A2_d -> HUB_USB1_PWREN_H

4.
!! WK2124_INT - USB_HOST_PWREN_H/GPU_PWREN/SATA_CP_POD/PCIE30X2_CLKREQn_M/GPIO0_A6_d


find /sys/bus/usb/devices/ -name "*8822*"


pin 5 (gpio0-5): regulator-5v0-vcc-usb-otg gpio0:5 function usb group usb-otg-pwren-h
pin 6 (gpio0-6): regulator-5v0-vcc-usb-host gpio0:6 function usb group usb-host-pwren-h
pin 28 (gpio0-28): regulator-3v3-vcc-pi6c-03 gpio0:28 function pcie group pcie-pwren-h
pin 98 (gpio3-2): vcc-hub-power-regulator gpio3:98 function usb group vcc-hub-power-en
pin 102 (gpio3-6): vcc-hub-reset-regulator gpio3:102 function usb group vcc-hub-reset-en


############### persistent

Step-by-Step Extroot Setup for SD Card

DS: openwrt enable extroot for sd card at build time

block-mount kmod-fs-ext4 e2fsprogs parted


files/etc/uci-defaults/99-enable-extroot

DS: Method 2: Build-Time Configuration Only (Runtime Automation)

This method is less flexible because it depends on a pre-formatted SD card with a known UUID and might not handle first-boot data migration automatically.

separated sd card

DS: Approach 2: Single Image with Persistent Data Partition

block-mount - For fstab management

kmod-fs-ext4 - ext4 filesystem support

e2fsprogs - Filesystem tools

fdisk or parted - Partition manipulation

sfdisk - Scriptable partitioning