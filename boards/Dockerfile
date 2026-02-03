#FROM openwrt/sdk:latest
FROM ubuntu:24.04

#USER root

RUN apt update && apt-get install -y build-essential libncurses5-dev gawk git \
  libssl-dev gettext zlib1g-dev swig unzip time xsltproc python3 \
  python3-setuptools python3-yaml python3-pyelftools wget rsync file

#RUN git config --global http.postBuffer 524288000