# Usige

- Build

`docker build -f DockerfileAarch64 -t qemu_wrapper_aarch64:latest .`

- Docker run

`docker run -it --rm --volume /etc/passwd:/etc/passwd:ro --volume /etc/group:/etc/group:ro --volume $PWD:/home/builder/workdir:rw --user $(id -u) qemu_wrapper_aarch64:latest bash`

- Note: next actions inside of docker and image has env vars presets, base dtsi, bare rootfs and stock kernel archive. All from `~/workdir`


- Unpack and build kernel, dts will be external with patches for developed drivers - virt emu specific thing

```
tar -xvf /opt/linux-$KERNEL_VERSION.tar.xz -C ~/workdir

cd ~/workdir/linux-$KERNEL_VERSION

make defconfig

TODO() Merge with *.config

make Image
make modules
```

- Pack rootfs. It stored at docker build in $ROOTFS_ROOT

```
# It create initramfs from folder specified in $ROOTFS_ROOT
cd ~/workdir/linux-$KERNEL_VERSION && pack_rootfs.sh

```

- Dts from base virt dts

`cd ~/workdir/linux-$KERNEL_VERSION && dtc -i /opt/ -I dts -O dtb -o virt_aarch64.dtb ../virt_aarch64.dts`


- Run emu

```

cd ~/workdir/linux-$KERNEL_VERSION

from linux src root

qemu-system-aarch64 -machine virt,gic_version=3 -cpu cortex-a72 -machine type=virt -smp 4 -m 256 \
    -dtb virt_aarch64.dtb \
    -kernel arch/arm64/boot/Image \
    -append "console=ttyAMA0 rdinit=/bin/sh" -nographic \
    -initrd initramfs.cpio.gz

Or better

$QEMU_AARCH64_CALL_PREFIX \
    -dtb virt_aarch64.dtb \
    -kernel arch/arm64/boot/Image \
    -append "console=ttyAMA0 rdinit=/bin/sh" -nographic \
    -initrd initramfs.cpio.gz
```

- mount some fs

```
mount -t proc proc /proc
mount -t sysfs sysfs /sys

TODO() devfs?

```

