set -e

trap 'last_command=$current_command; current_command=$BASH_COMMAND' DEBUG
# echo an error message before exiting
trap 'echo "\"${last_command}\" command failed with exit code $?."' EXIT

make -C kernel/ clean
make -C gnu-efi
make -C gnu-efi bootloader
make -C kernel kernel
make -C kernel buildimg

set +e
trap '' EXIT
trap '' DEBUG

make -C kernel run
