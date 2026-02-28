# Build for `aio3568j`

```
# Can't run multiline command

docker run --rm --privileged multiarch/qemu-user-static --reset -p yes

./compile.sh BOARD=station-p2 BRANCH=edge KERNEL_BTF=no BUILD_MINIMAL=yes BUILD_DESKTOP=no RELEASE=jammy KERNEL_GIT=shallow KERNEL_CONFIGURE=no PRIVATE_CCACHE=yes
```