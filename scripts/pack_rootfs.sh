#!/bin/bash

PWD_SAVED=$PWD

pushd $ROOTFS_ROOT
	find . | cpio -H newc -ov --owner root:root > $PWD_SAVED/initramfs.cpio && gzip -f $PWD_SAVED/initramfs.cpio
popd