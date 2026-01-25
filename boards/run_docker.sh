#!/bin/bash

set -x
set -e

docker build -t owrt-builder:latest .

docker run -it --rm -v "$(pwd):/workspace" -u $(id -u):$(id -g) \
	-v /etc/passwd:/etc/passwd:ro \
	-v /etc/group:/etc/group:ro \
	-v /etc/shadow:/etc/shadow:ro \
	owrt-builder:latest bash