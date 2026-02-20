# 1. Узнаем размер squashfs
SQUASHFS_SIZE=$(stat -c%s openwrt-aio3568j/build_dir/target-aarch64-openwrt-linux-musl_musl/linux-armsr_armv8/root.squashfs)
SQUASHFS_MB=$(( (SQUASHFS_SIZE + 1048575) / 1048576 ))
OVERLAY_MB=100  # размер overlay для сохранений
TOTAL_MB=$((SQUASHFS_MB + OVERLAY_MB + 20))

# 2. Создадим образ с двумя разделами
dd if=/dev/zero of=openwrt-with-overlay.img bs=1M count=$TOTAL_MB
sudo parted openwrt-with-overlay.img mklabel gpt
sudo parted openwrt-with-overlay.img mkpart primary 2048s $((SQUASHFS_MB + 10))MB
sudo parted openwrt-with-overlay.img mkpart primary $((SQUASHFS_MB + 10))MB 100%

# 3. Запишем squashfs в первый раздел
dd if=openwrt-aio3568j/build_dir/target-aarch64-openwrt-linux-musl_musl/linux-armsr_armv8/root.squashfs \
   of=openwrt-with-overlay.img \
   bs=512 \
   seek=2048 \
   conv=notrunc

# 4. Отформатируем второй раздел как ext4
# Узнаем смещение второго раздела
START_SECTOR2=$(sudo parted openwrt-with-overlay.img unit s print | grep "primary" | tail -1 | awk '{print $2}' | sed 's/s//g')
sudo losetup -o $((START_SECTOR2 * 512)) --find --show openwrt-with-overlay.img
# Допустим, это /dev/loop7
sudo mkfs.ext4 /dev/loop7
sudo losetup -d /dev/loop7


cat > /etc/config/fstab << "EOF"
config global
    option anon_swap '0'
    option anon_mount '1'
    option auto_swap '0'
    option auto_mount '1'
    option delay_root '5'

config mount
    option target '/overlay'
    option device '/dev/loop0'
    option fstype 'ext4'
    option options 'rw,sync'
    option enabled '1'
    option enabled_fsck '0'
EOF