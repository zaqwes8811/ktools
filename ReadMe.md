# Usige

- Build

`docker build -f DockerfileAarch64 -t qemu_wrapper_aarch64:latest .`

- Docker run

`docker run -it --rm --volume /etc/passwd:/etc/passwd:ro --volume /etc/group:/etc/group:ro --volume $PWD:/home/builder/workdir:rw --user $(id -u) qemu_wrapper_aarch64:latest bash`

- Note: next actions inside of docker and image has env vars presets, base dtsi, bare rootfs and stock kernel archive. All from `~/workdir`


- Unpack and build kernel, dts will be external with patches for developed drivers - virt emu specific thing


- Pack rootfs

- Dts from base virt dts

`cd ~/workdir/ && dtc -i /opt/ -I dts -O dtb -o virt_aarch64.dtb virt_aarch64.dts`


- Run emu

```

from linux src root

qemu-system-aarch64 -machine virt,gic_version=3 -cpu cortex-a72 -machine type=virt -smp 4 -m 256 \
    -dtb ../../virt_aarch64.dtb \
    -kernel arch/arm64/boot/Image \
    -append "console=ttyAMA0 rdinit=/bin/sh" -nographic \
    -initrd initramfs.cpio.gz

Or better

$QEMU_AARCH64_CALL_PREFIX \
    -dtb ../virt_aarch64.dtb \
    -kernel arch/arm64/boot/Image \
    -append "console=ttyAMA0 rdinit=/bin/sh" -nographic \
    -initrd initramfs.cpio.gz
```

