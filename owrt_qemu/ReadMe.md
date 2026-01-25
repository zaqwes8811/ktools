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