# Usige

- Docker build

```
docker build -f DockerfileAarch64 -t qemu_wrapper_aarch64:latest .
```

- Docker build and run

```
cd emb
./qemu-research/docker_run.sh
```

- Unpack and build kernel, dts will be external with patches for developed drivers - virt emu specific thing

```
cd $KERNEL_SRC

make defconfig  # default

scripts/kconfig/merge_config.sh $EXTERNAL_ROOT/qemu-research/kcsan.fragment  # HANG at start

or 

scripts/kconfig/merge_config.sh $EXTERNAL_ROOT/qemu-research/kcsan.fragment

make Image -j`nproc` && make modules -j`nproc`
```

- Pack rootfs. It stored at docker build in `$ROOTFS_ROOT`

```
emb_pack_initramfs.sh
```

- Dts from base virt dts

```
emb_gen_dtb.sh
```

- Run emu

```
cd $KERNEL_SRC && $QEMU_AARCH64_CALL_PREFIX \
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
/bin/mount -t devtmpfs devtmpfs /dev
```

- Mount host folder

```
mkdir -p /workdir
mount -t 9p -o trans=virtio,version=9p2000.L host0 /workdir
```