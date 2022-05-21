#!/usr/bin/env bash
set -e

trap 'last_command=$current_command; current_command=$BASH_COMMAND' DEBUG
# echo an error message before exiting
trap 'echo "\"${last_command}\" command failed with exit code $?."' EXIT

make -C kernel clean

make -C gnu-efi
make -C gnu-efi bootloader

file=yes

if [[ ! -d kernel/src/icons ]]; then
    mkdir -p kernel/src/icons
fi

for i in kernel/icons/*; do
    hfile=$(echo $i | tr "/" " " | awk '{print $3}' | tr "." " " | awk '{print $1}').h
    echo
    ./tools/icontest.py $i kernel/src/icons/$hfile
done

if [[ ! -f kernel/fonts/zap-light16.psf ]]; then
    mkdir -p kernel/fonts
    wget https://ftp.zap.org.au/pub/fonts/console-fonts-zap/LATEST.tar.xz
    tar xvf LATEST.tar.xz
    cp -fv console-fonts-zap-*/zap-light16.psf kernel/fonts
    rm -rfv console-fonts-zap-*
    rm LATEST.tar.xz
fi

make -C kernel

set +e
trap '' EXIT
trap '' DEBUG

make -C kernel run
