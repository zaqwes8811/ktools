# Usige

Build

`docker build -f DockerfileAarch64 -t qemu_wrapper_aarch64:latest .`

Docker run

`docker run -it --rm --volume /etc/passwd:/etc/passwd:ro --volume /etc/group:/etc/group:ro --volume $PWD:/home/builder/workdir:rw --user $(id -u) qemu_wrapper_aarch64:latest bash`


Build kernel


Pack rootfs

Dts

`dtc -i /opt/ -I dts -O dtb -o virt_aarch64.dtb virt_aarch64.dts`


Run emu

```
qemu-system-aarch64 -machine virt,gic_version=3 -cpu cortex-a72 -machine type=virt -smp 4 -m 256 \
    -kernel arch/arm64/boot/Image \
    -append "console=ttyAMA0 rdinit=/bin/sh" -nographic \
    -initrd initramfs.cpio.gz
```

