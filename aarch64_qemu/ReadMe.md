# Usige

Purpose: Fast test modules in target kernel with instrumentation (KASAN/KCSAN/etc.). Run unittests with KUnit.

- Docker build, run and connect to running

```
cd sources

./ktools/docker_run.sh

cd ~/workdir/

./Android-kernel/common - kernel code
./Android-kernel/bore-modules - app modules

# Connect to running container
docker exec -it qemu_aarch64 bash
```

- Build kernel

```
# Go to kernel code

ktools_to_kernel.sh

# Optional. At first run. Default config
make defconfig

./scripts/kconfig/merge_config.sh .config ../bore-modules/arch/arm64/configs/exynosauto.fragment
./scripts/kconfig/merge_config.sh .config ../bore-modules/drivers/soc/bore/arch/arm64/configs/bore.fragment
./scripts/kconfig/merge_config.sh .config ~/workdir/ktools/base.fragment

# Instruments
./scripts/kconfig/merge_config.sh .config ~/workdir/ktools/kasan.fragment

or

# A lot of troubles
./scripts/kconfig/merge_config.sh .config ~/workdir/ktools/kcsan.fragment
scripts/config -e KVM -e VHOST_NET -d KSM -d TRANSPARENT_HUGEPAGE

# Need to apply new or updated config
make Image -j`nproc` && make modules -j`nproc`

# Build app modules

ktools_build_ktools_modules.sh

# Clean app modules cmd
make M=$PWD clean
```

- Copy *.ko or other files to rootfs in `/initramfs`. As option we can run modules directly, workdir shared with qemu. `/workdir` folder inside of qemu

```
cp drivers/soc/bore/alure/aarch64_qemu/*.ko ../common/lib/kunit/kunit.ko $ROOTFS_ROOT/lib/modules/$KERNEL_VERSION
```

- Pack rootfs. It stored at docker build in `/initramfs`

```
ktools_pack_rootfs.sh
```

- Dts from base virt dts

```
ktools_gen_dtb.sh
```

- Run emu

```
ktools_run_qemu.sh
```

- Finish qemu init. Full autostart unimplemented yet

```
. /bin/post_initramfs.sh

# After it all build files available in /workdir. For example we can load modules
# without copy to initramfs
```

- Ctrl+A than X - out of qemu. `exit` from docker

# Usage 

```
insmod bore-modules/drivers/soc/bore/alure/aarch64_qemu/alure-mbx2-stub.ko

insmod aarch64_qemu/vgpio_customer.ko


# Apps
gcc -E prep.c

export ANDROID_ROOT=/home/builder/workdir/Android

cmake -DCMAKE_TOOLCHAIN_FILE=~/workdir/ktools/toolchain.cmake ..

```

```
cd /alure && insmod ktests/alure-mbx2-stub.ko \
		&& insmod ktests/vi2c_customer.ko \
		&& insmod bore_alure_virtual_gpio.ko \
		&& insmod bore_alure_virtual_i2c_bus.ko

ls | grep ko

insmod ktests/vi2c_customer.ko # should be loaded to kernel

insmod bore_ds90ub94x_monitor.ko

ifeq ($(CONFIG_BORE_VGPIO_SEAMS),y)
bore_alure_virtual_gpio-objs += ktests/vgpio_seams.o
endif

menuconfig BORE_VGPIO_SEAMS
	tristate "Bore vgpio seams"
	default n
	help
	  Enable Bore vgpio seams
```

```
make -C /home/builder/workdir/Android-kernel/common -j `nproc` VERBOSE=4 M=../bore-modules/ modules
```