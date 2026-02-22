#!/bin/bash

export KERNEL_SRC=/home/builder/workdir/Android-kernel/common
export KCONFIG_EXT_PREFIX=/home/builder/workdir/Android-kernel/bore-modules/
export KTOOLS_DIR=/home/builder/workdir/ktools

cmd='cd $KERNEL_SRC'
echo "alias ktools_to_kernel_src.sh='$cmd'" >> ~/.bashrc

cmd='cd $KCONFIG_EXT_PREFIX'
echo "alias ktools_to_bore_modules.sh='$cmd'" >> ~/.bashrc

cmd='cd $KCONFIG_EXT_PREFIX && gcc -I/opt/ -I$KCONFIG_EXT_PREFIX/arch/arm64/boot/dts/exynos -E -nostdinc -undef -D__DTS__ \
    -x assembler-with-cpp -o virt_aarch64.dts.tmp $KTOOLS_DIR/virt_aarch64.dts \
    && dtc -i /opt/ -I dts -O dtb -o virt_aarch64.dtb virt_aarch64.dts.tmp'
echo "alias ktools_gen_dtb.sh='$cmd'" >> ~/.bashrc

# Parallel build create troubles
cmd='cd $KCONFIG_EXT_PREFIX && KBUILD_ABS_SRCTREE=y make all M=../bore-modules/'
echo "alias ktools_build_bore_modules.sh='$cmd'" >> ~/.bashrc

cmd='cd $ROOTFS_ROOT && find . | cpio -H newc -ov --owner root:root > /tmp/initramfs.cpio && cd - && gzip -f /tmp/initramfs.cpio && cd $KCONFIG_EXT_PREFIX && mv /tmp/initramfs.cpio.gz .'
echo "alias ktools_pack_rootfs.sh='$cmd'" >> ~/.bashrc

cmd='cd $KCONFIG_EXT_PREFIX && $QEMU_AARCH64_CALL_PREFIX \
    -dtb virt_aarch64.dtb \
    -kernel $KERNEL_SRC/arch/arm64/boot/Image \
    -virtfs local,path=$PWD/../../,mount_tag=host0,security_model=mapped,id=host0  \
    -append "console=ttyAMA0 rdinit=/init" -nographic \
    -initrd initramfs.cpio.gz'
echo "alias ktools_run_qemu.sh='$cmd'" >> ~/.bashrc
