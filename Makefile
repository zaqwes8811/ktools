ROOTFS:=/rootfss/rootfs

run: pack_rootfs
	cd linux-6.1.68 && \
	qemu-system-arm -M vexpress-a9 -m 256M -kernel arch/arm/boot/zImage \
			-dtb arch/arm/boot/dts/vexpress-v2p-ca9.dtb \
			-append "console=ttyAMA0 rdinit=/bin/sh" -nographic \
			-initrd $(HOME)/initramfs.cpio.gz


drv_dtb:
	cd linux-6.1.68 && \
			export ARCH=arm && \
			export CROSS_COMPILE=arm-unknown-linux-gnueabi- && \
			make modules -j$(nproc) && \
			make dtbs -j$(nproc)

	cp linux-6.1.68/drivers/soc/rockchip/sfi/atom_sfi_virtual_gpio_core.ko $(ROOTFS)/


pack_rootfs: drv_dtb
	cd $(ROOTFS) && find . | cpio -H newc -ov --owner root:root > $(HOME)/initramfs.cpio && gzip -f $(HOME)/initramfs.cpio



docker_build:
	docker build -t qemu_wrapper:latest .

docker_run:
	docker run -it --rm --volume /etc/passwd:/etc/passwd:ro --volume /etc/group:/etc/group:ro --user $(id -u) qemu_wrapper:latest bash