# Usige


- Docker build and run

```
cd emb
./ktools/docker_run.sh
```

- Get kernel sources

```
cd $KERNEL_SRC

make defconfig  # default

scripts/kconfig/merge_config.sh .config $EXTERNAL_ROOT/research.fragment

scripts/kconfig/merge_config.sh .config $EXTERNAL_ROOT/kcsan.fragment  # HANG at start

or 

scripts/kconfig/merge_config.sh .config $EXTERNAL_ROOT/kcsan.fragment

make Image -j`nproc` && make modules -j`nproc`
```

- Pack rootfs. It stored at docker build in `$ROOTFS_ROOT`

```
ktools_pack_initramfs.sh
```

- Dts from base virt dts

```
ktools_gen_dtb.sh
```

- Run emu

```
ktools_run_qemu.sh
```

- Host work folder `/workdir`
