set -e

trap 'last_command=$current_command; current_command=$BASH_COMMAND' DEBUG
# echo an error message before exiting
trap 'echo "\"${last_command}\" command failed with exit code $?."' EXIT

make -C kernel/ clean
make -C gnu-efi
make -C gnu-efi bootloader

file=yes

for i in kernel/icons/*; do
    hfile=$(echo $i | tr "/" " " | awk '{print $3}' | tr "." " " | awk '{print $1}').h
    echo
    ./tools/icontest $i kernel/src/icons/$hfile
done

make -C kernel kernel
make -C kernel buildimg

set +e
trap '' EXIT
trap '' DEBUG

make -C kernel run
