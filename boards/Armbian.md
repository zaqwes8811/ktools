# Build for `aio3568j`

```
# Can't run multiline command

docker run --rm --privileged multiarch/qemu-user-static --reset -p yes


mv userpatches/customize-image.sh userpatches/customize-image.sh.bak

./compile.sh CLEAN_LEVEL="make,debs" BOARD=station-p2 BRANCH=edge KERNEL_BTF=no BUILD_MINIMAL=yes BUILD_DESKTOP=no RELEASE=jammy KERNEL_GIT=shallow KERNEL_CONFIGURE=no PRIVATE_CCACHE=yes ENABLE_EXTENSIONS="hailo8-stationp2"


./compile.sh BOARD=station-p2 BRANCH=edge KERNEL_BTF=no BUILD_MINIMAL=yes BUILD_DESKTOP=no RELEASE=jammy KERNEL_GIT=shallow KERNEL_CONFIGURE=no PRIVATE_CCACHE=yes ENABLE_EXTENSIONS="hailo8-stationp2" PACKAGE_LIST_ADDITIONAL="pciutils"


 EXTENSION="$EXTENSION_PATH"


rm -rf .tmp output
sudo rm -rf cache


 Failed to apply 3 patches: ->media-0004-media-verisilicon-AV1-Fix-enable-cdef-computation(:1) (+8/-2)[1M] {rockchip_vpu981_hw_av1_dec.c}<-,->media-0005-media-verisilicon-AV1-Set-IDR-flag-for-intra_only-fr(:1) (+1/-1)[1M] {rockchip_vpu981_hw_av1_dec.c}<-,->media-0006-media-verisilicon-AV1-Fix-tx-mode-bit-setting(:1) (+26/-1)[1M] {rockchip_vpu981_hw_av1_dec.c}<-



./output/images/Armbian-unofficial_26.02.0-trunk_Station-p2_jammy_edge_6.19.6_minimal.img

99


   12  modinfo hailo_pci | grep -i firmware
   13  md5sum /lib/firmware/hailo/hailo8_fw.bin
   14  echo 1 | sudo tee /sys/module/firmware_class/parameters/verbose
   15  sudo modprobe -r hailo_pci
   16  sudo modprobe hailo_pci
   17  sudo dmesg | grep -i "firmware" | tail -50
   18  dmesg | grep hailo


   [  115.694993] hailo: Init module. driver version 4.23.0
[  115.695688] hailo 0002:21:00.0: Probing on: 1e60:2864...
[  115.695745] hailo 0002:21:00.0: Probing: Allocate memory for device extension, 9072
[  115.695851] hailo 0002:21:00.0: Probing: Device enabled
[  115.695980] hailo 0002:21:00.0: Probing: mapped bar 0 - 0000000034a71180 16384
[  115.696040] hailo 0002:21:00.0: Probing: mapped bar 2 - 00000000ae0711ec 4096
[  115.696090] hailo 0002:21:00.0: Probing: mapped bar 4 - 0000000029ec8082 16384
[  115.696143] hailo 0002:21:00.0: Probing: Setting max_desc_page_size to 4096, (page_size=4096)
[  115.696916] hailo 0002:21:00.0: Probing: Enabled 64 bit dma
[  115.696954] hailo 0002:21:00.0: Probing: Using userspace allocated vdma buffers
[  115.696996] hailo 0002:21:00.0: Disabling ASPM L0s 
[  115.697037] hailo 0002:21:00.0: Successfully disabled ASPM L0s 
[  115.697740] hailo 0002:21:00.0: Writing file hailo/hailo8_fw.bin
[  115.771249] hailo 0002:21:00.0: File hailo/hailo8_fw.bin written successfully
[  115.771308] hailo 0002:21:00.0: Writing file hailo/hailo8_board_cfg.bin
[  115.771698] hailo 0002:21:00.0: File hailo/hailo8_board_cfg.bin written successfully
[  115.771739] hailo 0002:21:00.0: Writing file hailo/hailo8_fw_cfg.bin
[  115.771917] hailo 0002:21:00.0: File hailo/hailo8_fw_cfg.bin written successfully
[  115.788513] hailo 0002:21:00.0: NNC Firmware loaded successfully
[  115.788527] hailo 0002:21:00.0: FW loaded, took 90 ms
[  115.799771] hailo 0002:21:00.0: Probing: Added board 1e60-2864, /dev/hailo0


root@station-p2:~# lsinitramfs /boot/initrd.img-$(uname -r) | grep hailo
etc/modprobe.d/hailo_pci.conf
usr/lib/firmware/hailo
usr/lib/firmware/hailo/hailo8_fw.bin
usr/lib/modules/6.19.6-edge-rockchip64/kernel/drivers/net/hailo_pci.ko


```


```
# Must remove old
sudo rm -f /etc/netplan/*.yaml

# Create new config for eth0
sudo tee /etc/netplan/01-netcfg.yaml > /dev/null << 'EOF'
network:
  version: 2
  renderer: networkd
  ethernets:
    eth0:
      dhcp4: no
      dhcp6: no
      addresses:
        - 192.168.1.100/24
      routes:
        - to: default
          via: 192.168.1.1
      nameservers:
        addresses: [8.8.8.8, 1.1.1.1]
EOF

# Set correct permissions
sudo chmod 600 /etc/netplan/01-netcfg.yaml

# Apply the configuration
sudo netplan apply


Host 192.168.1.100
  HostName 192.168.1.100
  User root
  ServerAliveInterval 60
  ServerAliveCountMax 5
  TCPKeepAlive yes
  ConnectTimeout 60

```