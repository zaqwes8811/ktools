#!/bin/bash

set -x
set -e

docker build -t owrt-builder:latest .

docker run -it --rm -v "$(pwd):/workspace" -u $(id -u):$(id -g) \
	-v /etc/passwd:/etc/passwd:ro \
	-v /etc/group:/etc/group:ro \
	-v /etc/shadow:/etc/shadow:ro \
	--cap-add=SYS_PTRACE \
	--cap-add=SYS_ADMIN \
	--security-opt seccomp=unconfined \
	owrt-builder:latest bash