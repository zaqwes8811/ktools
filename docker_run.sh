#!/bin/bash

# From emb/

SCRIPT_ROOT=$(dirname "$0")

docker build -f $SCRIPT_ROOT/DockerfileAarch64 -t qemu_wrapper_aarch64:latest $SCRIPT_ROOT

docker run --name qemu_aarch64 -it --rm --volume /etc/passwd:/etc/passwd:ro --volume /etc/group:/etc/group:ro \
    --volume $PWD:/home/builder/workdir:rw --user $(id -u) qemu_wrapper_aarch64:latest bash -c ". /env.sh && exec bash"