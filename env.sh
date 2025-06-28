#!/bin/bash

export KERNEL_SRC=$HOME/workdir/linux
export EXTERNAL_ROOT=$HOME/workdir/qemu-research/

cmd='cd $ROOTFS_ROOT && find . | cpio -H newc -ov --owner root:root > /tmp/initramfs.cpio && cd - && gzip -f /tmp/initramfs.cpio && mv /tmp/initramfs.cpio.gz $KERNEL_SRC && cd $KERNEL_SRC'
echo "alias emb_pack_initramfs.sh='$cmd'" >> ~/.bashrc

cmd='cd $EXTERNAL_ROOT && dtc -i /opt/ -I dts -O dtb -o $KERNEL_SRC/virt_aarch64.dtb virt_aarch64.dts && cd $KERNEL_SRC'
echo "alias emb_gen_dtb.sh='$cmd'" >> ~/.bashrc

cmd='cd $KERNEL_SRC && $QEMU_AARCH64_CALL_PREFIX \
    -dtb virt_aarch64.dtb \
    -kernel arch/arm64/boot/Image \
    -virtfs local,path=$HOME/workdir,mount_tag=host0,security_model=mapped,id=host0  \
    -append "console=ttyAMA0 rdinit=/init" -nographic \
    -initrd initramfs.cpio.gz'
echo "alias emb_run_qemu.sh='$cmd'" >> ~/.bashrc