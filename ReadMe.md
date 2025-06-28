# Usige

- Docker build

```
docker build -f DockerfileAarch64 -t qemu_wrapper_aarch64:latest .
```

- Docker run

```
docker run --name qemu_aarch64 -it --rm --volume /etc/passwd:/etc/passwd:ro --volume /etc/group:/etc/group:ro --volume $PWD:/home/builder/workdir:rw --user $(id -u) qemu_wrapper_aarch64:latest bash
```

- Note: next actions inside of docker and image has env vars presets, base dtsi, bare rootfs and stock kernel archive. All from `$KERNEL_SRC`


- Unpack and build kernel, dts will be external with patches for developed drivers - virt emu specific thing

```
tar -xvf /opt/linux-$KERNEL_VERSION.tar.xz -C ~/workdir

scripts/kconfig/merge_config.sh ../qemu-research/kcsan.fragment

cd $KERNEL_SRC

make defconfig

TODO() Merge with *.config

make Image -j`nproc` && make modules -j`nproc`
```

- Pack rootfs. It stored at docker build in `$ROOTFS_ROOT`

```
# It create initramfs from folder specified in $ROOTFS_ROOT
cd $KERNEL_SRC

cd $ROOTFS_ROOT && find . | cpio -H newc -ov --owner root:root > /tmp/initramfs.cpio && cd - && gzip -f /tmp/initramfs.cpio && mv /tmp/initramfs.cpio.gz .
```

- Dts from base virt dts

```
cd $KERNEL_SRC

dtc -i /opt/ -I dts -O dtb -o virt_aarch64.dtb ../virt_aarch64.dts
```

- Run emu

```
cd $KERNEL_SRC

$QEMU_AARCH64_CALL_PREFIX \
    -dtb virt_aarch64.dtb \
    -kernel arch/arm64/boot/Image \
    -virtfs local,path=$PWD,mount_tag=host0,security_model=mapped,id=host0  \
    -append "console=ttyAMA0 rdinit=/bin/sh" -nographic \
    -initrd initramfs.cpio.gz
```

- Mount some fs

```
mount -t proc proc /proc
mount -t sysfs sysfs /sys

TODO() devfs?
```

- Mount host folder

```
mkdir -p /mnt/shared9p
mount -t 9p -o trans=virtio,version=9p2000.L host0 /mnt/shared9p
```