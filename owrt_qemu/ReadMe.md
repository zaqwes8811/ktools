# Tutorial 1

```
https://openwrt.org/docs/guide-user/virtualization/qemu

sudo apt install qemu-system-arm

# Download image

https://downloads.openwrt.org/releases/24.10.3/targets/armsr/armv8/

wget https://downloads.openwrt.org/releases/24.10.3/targets/armsr/armv8/openwrt-24.10.3-armsr-armv8-generic-initramfs-kernel.bin

qemu-system-arm -nographic -M virt -m 64 -kernel openwrt-24.10.3-armsr-armv8-generic-initramfs-kernel.bin

How quit:
Cntl + A after X

# Variant 0:
qemu-system-aarch64 -m 1024 -smp 2 -cpu cortex-a57 -M virt -nographic \
-kernel openwrt-24.10.3-armsr-armv8-generic-initramfs-kernel.bin

# Variant 1: Non persistent

Trouble:
No hvf
https://stackoverflow.com/questions/66819049/qemu-system-aarch64-accel-hvf-invalid-accelerator-hvf

qemu-system-aarch64 -m 1024 -smp 2 -cpu host -M virt,highmem=off \
-nographic \
-accel hvf \
-kernel openwrt-24.10.3-armsr-armv8-generic-initramfs-kernel.bin \
-device virtio-net,netdev=net0 -netdev user,id=net0,net=192.168.1.0/24,hostfwd=tcp:127.0.0.1:1122-192.168.1.1:22 \
-device virtio-net,netdev=net1 -netdev user,id=net1,net=192.0.2.0/24

No host:
https://www.reddit.com/r/qemu_kvm/comments/1fzg4gd/qemusystemx86_64_unable_to_find_cpu_model_host/

TODO() Build own emulator

qemu-system-aarch64 -m 1024 -smp 2 -cpu host -M virt,highmem=off \
-nographic \
-kernel openwrt-24.10.3-armsr-armv8-generic-initramfs-kernel.bin \
-device virtio-net,netdev=net0 -netdev user,id=net0,net=192.168.1.0/24,hostfwd=tcp:127.0.0.1:1122-192.168.1.1:22 \
-device virtio-net,netdev=net1 -netdev user,id=net1,net=192.0.2.0/24

qemu-system-aarch64 -m 1024 -smp 2 -M virt,highmem=off \
-nographic \
-kernel openwrt-24.10.3-armsr-armv8-generic-initramfs-kernel.bin \
-device virtio-net,netdev=net0 -netdev user,id=net0,net=192.168.1.0/24,hostfwd=tcp:127.0.0.1:1122-192.168.1.1:22 \
-device virtio-net,netdev=net1 -netdev user,id=net1,net=192.0.2.0/24

Can't start

```

# Build OpenWrt on Rpi 

```
link: https://www.cnx-software.com/2020/01/12/build-customize-openwrt-for-raspberry-pi/ , need VPN
```

openwrt/build_dir/target-aarch64-openwrt-linux-musl_musl/linux-rockchip_armv8/tmp/

qemu-system-aarch64 -M help | grep -i rockchip


qemu-system-aarch64 -machine virt,gic_version=3 -cpu cortex-a72 -machine type=virt -smp 2 -m 1024 \
    -dtb virt_aarch64.dtb \
    -kernel arch/arm64/boot/Image \
    -virtfs local,path=$HOME/workdir,mount_tag=host0,security_model=mapped,id=host0  \
    -append "console=ttyAMA0 rdinit=/init" -nographic \
    -initrd initramfs.cpio.gz

	-dtb image-rk3568-rock-3b.dtb \

qemu-system-aarch64 \
	-M virt \
	-cpu cortex-a55 \
	-smp 4 \
	-m 1024 \
	-nographic \
    -kernel openwrt/build_dir/target-aarch64-openwrt-linux-musl_musl/linux-rockchip_armv8/tmp/openwrt-rockchip-armv8-radxa_rock-3b-initramfs-kernel.bin \
    -append "console=ttyAMA0" 


qemu-system-aarch64 \
    -M virt \
    -cpu cortex-a72 \
    -smp 4 \
    -m 1024 \
    -nographic \
    -kernel openwrt-aio3568j/build_dir/target-aarch64-openwrt-linux-musl_musl/linux-armsr_armv8/vmlinux-initramfs \
    -append "console=ttyAMA0 earlycon=pl011,0x9000000 loglevel=8" \
    -d int,cpu_reset,unimp,guest_errors \
    -D qemu.log

build_dir/target-aarch64-openwrt-linux-musl_musl/linux-armsr_armv8/linux-6.6.119/arch/arm64/boot/Image
    -kernel openwrt-aio3568j/build_dir/target-aarch64-openwrt-linux-musl_musl/linux-armsr_armv8/linux-6.6.119/arch/arm64/boot/Image \

qemu-system-aarch64 \
    -M virt \
    -cpu cortex-a72 \
    -smp 4 \
    -m 1024 \
    -nographic \
    -kernel openwrt-aio3568j/build_dir/target-aarch64-openwrt-linux-musl_musl/linux-armsr_armv8/vmlinux \
    -drive file=openwrt-disk-final.img,format=raw,if=virtio \
    -append "console=ttyAMA0 root=/dev/vda1 rootwait rootfstype=squashfs init=/sbin/init" \
    -d int,cpu_reset,unimp,guest_errors \
    -D qemu.log

root@(none):~# df -h
Filesystem                Size      Used Available Use% Mounted on
tmpfs                   492.5M     18.2M    474.3M   4% /
tmpfs                   492.5M     24.0K    492.5M   0% /tmp
tmpfs                   512.0K         0    512.0K   0% /dev


root@OpenWrt:~# ls /dev/vd*
/dev/vda   /dev/vda1  /dev/vda2
root@OpenWrt:~# cat /proc/partitions
major minor  #blocks  name

 254        0     204800 vda
 254        1     121856 vda1
 254        2          0 vda2


 cat /proc/partitions

# Pseudo disk

```
cd boards

export DISK_IMG=openwrt-disk.img
dd if=/dev/zero of=$DISK_IMG bs=1M count=200

sudo parted $DISK_IMG -- mklabel gpt

sudo parted $DISK_IMG -- mkpart primary 2048s 60%


START_BYTES=$(sudo parted $DISK_IMG unit B print | awk '/^ [0-9]/ {print $2; exit}' | sed 's/B//g')
echo "Смещение первого раздела: $START_BYTES байт"


sudo losetup -f --show -o 1048064 openwrt-disk.img

LOOP_DEV=$(sudo losetup -o $START_BYTES --find --show $DISK_IMG)

sudo dd if=openwrt-aio3568j/build_dir/target-aarch64-openwrt-linux-musl_musl/linux-armsr_armv8/root.squashfs of=$LOOP_DEV bs=1M status=progress


sudo mount $LOOP_DEV mnt
ls mnt
sudo umount mnt
```


# 1. Создадим образ с одним разделом
dd if=/dev/zero of=openwrt-disk-final.img bs=1M count=150

# 2. Создадим таблицу GPT и один раздел
sudo parted openwrt-disk-final.img mklabel gpt
sudo parted openwrt-disk-final.img mkpart primary 2048s 100%

# 3. Запишем squashfs в раздел
dd if=openwrt-aio3568j/build_dir/target-aarch64-openwrt-linux-musl_musl/linux-armsr_armv8/root.squashfs \
   of=openwrt-disk-final.img \
   bs=512 \
   seek=2048 \
   conv=notrunc



################


qemu-system-aarch64 \
    -M virt \
    -cpu cortex-a72 \
    -smp 4 \
    -m 1024 \
    -nographic \
    -kernel openwrt-aio3568j/build_dir/target-aarch64-openwrt-linux-musl_musl/linux-armsr_armv8/vmlinux \
    -drive file=openwrt-with-overlay.img,format=raw,if=virtio \
    -append "console=ttyAMA0 root=/dev/vda1 rootwait rootfstype=squashfs init=/sbin/init" \
    -d int,cpu_reset,unimp,guest_errors \
    -D qemu.log