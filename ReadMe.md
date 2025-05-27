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