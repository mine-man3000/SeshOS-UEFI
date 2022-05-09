set -e

trap 'last_command=$current_command; current_command=$BASH_COMMAND' DEBUG
# echo an error message before exiting
trap 'echo "\"${last_command}\" command failed with exit code $?."' EXIT

distro=$(cat /etc/os-release | awk '{if(NR==1) print}' | tr "\"" " " | awk '{print $2}')

if [ $distro != "Debian" ]; then
    if [ $distro != "Ubuntu" ]; then
        echo "Your 'mformat' command is bad, sorry"
        echo "ca"
        exit 1
    fi
fi

make -C kernel/ clean
make -C gnu-efi
make -C gnu-efi bootloader
make -C kernel kernel
make -C kernel buildimg

set +e
trap '' EXIT
trap '' DEBUG

make -C kernel run