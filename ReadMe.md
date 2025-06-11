# Base on
https://medium.com/@fprotopapa/embedded-linux-from-scratch-quick-easy-on-qemu-87e761834b51

https://linux-kernel-labs.github.io/refs/heads/master/so2/lab11-arm-kernel-development.html

https://www.orientdisplay.com/emulating-embedded-linux-systems-with-qemu/

6.1.68

wget https://cdn.kernel.org/pub/linux/kernel/v6.x/linux-6.1.68.tar.xz

/home/zaqwes/x-tools/arm-unknown-linux-gnueabi/arm-unknown-linux-gnueabi/sysroot

export SYSROOT=$(arm-unknown-linux-gnueabi-gcc -print-sysroot)

sudo mkdir -p /rootfss/rootfs
sudo chmod 0777 /rootfss -R

cd /rootfss/rootfs


qemu-system-arm -M vexpress-a9 -m 256M -kernel arch/arm/boot/zImage \
  -dtb arch/arm/boot/dts/vexpress-v2p-ca9.dtb \
  -append "console=ttyAMA0 rdinit=/bin/sh" -nographic \
  -initrd $HOME/initramfs.cpio.gz


Ctrl-A x

linux-6.1.68/arch/arm/boot/dts/vexpress-v2p-ca9.dts

# Gpio + pinmux

https://www.kernel.org/doc/html/v4.14/driver-api/pinctl.html

https://www.youtube.com/watch?v=p-lJ1QFgpig&ab_channel=TheLinuxFoundation
https://www.youtube.com/watch?v=VdiZjLd0DPM&ab_channel=BayLibre
https://www.youtube.com/watch?v=VdiZjLd0DPM&ab_channel=BayLibre

gpio sybsystem
pinctl sybsystem

pinmux - exclusive function
pin Config 

Pin ctontrol and gpio interaction - separatly controlled except `.stict` in `*_ops`

pad - GPIO/FuncA/FuncB...

PINCTRL Framework
PINS - pad/finger/ball...
pin groups - 

PINS -> PINGROUPS -> FUNCTIONS (i2c0, uart1, etc.)

pinctrl_ops
pinmux_ops

designed before DT

GPIO framework - gpiolib -> gpio_desc(?)

https://www.youtube.com/watch?v=lQRCDl0tFiQ&ab_channel=TheLinuxFoundation

# Docker

docker run -it --rm --volume /etc/passwd:/etc/passwd:ro --volume /etc/group:/etc/group:ro --user $(id -u) qemu_wrapper:latest bash

# Aarch64/Arm64
https://forum.armbian.com/topic/38258-running-self-build-image-on-qemu-arm64/

https://gist.github.com/luk6xff/9f8d2520530a823944355e59343eadc1 !!

https://www.altlinux.org/Ports/aarch64/QEMU
https://cdn.kernel.org/pub/linux/kernel/people/will/docs/qemu/qemu-arm64-howto.html

https://nuttx.apache.org/docs/latest/platforms/arm64/qemu/boards/qemu-armv8a/index.html

[!!!] https://android.googlesource.com/platform/external/syzkaller/+/HEAD/docs/linux/setup_linux-host_qemu-vm_arm64-kernel.md

https://wiki.debian.org/Arm64Qemu

rpi4
https://stackoverflow.com/questions/67045438/emulating-raspberry-pi-4-with-qemu

virt
https://translatedcode.wordpress.com/2017/07/24/installing-debian-on-qemus-64-bit-arm-virt-board/

https://xilinx-wiki.atlassian.net/wiki/spaces/A/pages/822312999/Building+and+Running+QEMU+from+Source+Code !!!

/home/builder/workdir/sys/rootfs

export CROSS_COMPILE=arm-unknown-linux-gnueabi-

CONFIG_TC=n


https://www.kernel.org/pub/linux/kernel/people/will/docs/qemu/qemu-arm64-howto.md !!

aarch64 virt with dtb
virt сам dtb генерит? https://gist.github.com/paranlee/3bf0f690baede7f9bf371249558348c8 !!!

```
qemu-system-aarch64 \
    -machine virt,gic_version=3 \
    -machine virtualization=true \
    -cpu cortex-a72 -machine type=virt \
    -smp 4 -m 4096 -display none \
    -machine dumpdtb=virt-gicv3.dtb
```

load vmlinuz


$ export ARCH=arm64
$ export CROSS_COMPILE=aarch64-unknown-linux-gnu-
$ make vexpress_defconfig

make ARCH=arm64 CROSS_COMPILE=aarch64-unknown-linux-gnu- menuconfig

make ARCH=arm64 CROSS_COMPILE=aarch64-unknown-linux-gnu- Image

https://github.com/raspberrypi/documentation/blob/c666656d8782a509d7eae82ffe634cbd28b147b8/linux/kernel/building.md


qemu-system-aarch64 -kernel arch/arm64/boot/Image \
    -machine virt,gic_version=3 \
    -machine virtualization=true \
    -cpu cortex-a72 -machine type=virt \
    -append "console=ttyAMA0 rdinit=/bin/sh" -nographic \
    -initrd ../initramfs.cpio.gz

aarch64-unknown-linux-gnu-readelf -a bin/busybox | grep "program interpreter"

[Requesting program interpreter: /lib/ld-linux-aarch64.so.1]

aarch64-unknown-linux-gnu-readelf -a bin/busybox | grep "Shared library"
 0x0000000000000001 (NEEDED)             Shared library: [libm.so.6]
 0x0000000000000001 (NEEDED)             Shared library: [libresolv.so.2]
 0x0000000000000001 (NEEDED)             Shared library: [libc.so.6]


 to lib64


sudo apt-get install vncviewer    

sudo apt-get install xtightvncviewer

https://unix.stackexchange.com/questions/479085/can-qemu-m-virt-on-arm-aarch64-have-multiple-serial-ttys-like-such-as-pl011-t

# CI-CD
Kernel from system image
Cons:
- tests should be added to build
- special defconfig options
- dts?

Pro:
- same kernel

Kernel from stock kernel version
Cons:
- kernel

Pro:
- any kernel options
- any test frameworks