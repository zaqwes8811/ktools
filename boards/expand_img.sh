#!/bin/bash

set -x
set -e

export EXPORT_DIR=openwrt/build_dir/target-aarch64-openwrt-linux-musl_musl/linux-rockchip_armv8/tmp/ \
&& rm -rf owrt.img && \
gunzip -dkf $EXPORT_DIR/openwrt-rockchip-armv8-radxa_rock-3b-squashfs-sysupgrade.img.gz || true && \
	cp $EXPORT_DIR/openwrt-rockchip-armv8-radxa_rock-3b-squashfs-sysupgrade.img owrt.img

cp owrt.img owrt_expanded.img

SQUASHFS_SIZE=$(stat -c%s owrt_expanded.img)
SQUASHFS_MB=$(( (SQUASHFS_SIZE + 1048575) / 1048576 ))
OVERLAY_MB=100
TOTAL_MB=$((OVERLAY_MB + 20))

dd if=/dev/zero of=owrt_expanded.img oflag=append bs=1M count=$TOTAL_MB conv=notrunc

# Set boot flag on partition 1 if needed
parted -s owrt_expanded.img set 1 boot on

echo "New partition layout:"
fdisk -l owrt_expanded.img

# First, get the end of partition 2
PART2_END=$(fdisk -l owrt_expanded.img | grep owrt_expanded.img2 | awk '{print $3}')
echo "Partition 2 ends at sector: $PART2_END"

# Calculate start for extended partition (align to 1MB after partition 2)
EXTENDED_START=$(( (PART2_END + 2048) ))
echo "Extended partition start: $EXTENDED_START"

# Create extended partition first, then logical partition inside it
parted -s owrt_expanded.img mkpart primary ${EXTENDED_START}s 100%

echo "New partition layout:"
fdisk -l owrt_expanded.img

# Make filesystem