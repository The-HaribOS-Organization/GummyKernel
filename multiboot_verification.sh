if grub-file --is-x86-multiboot2 $1; then
    echo multiboot2 is confirmed
else
    echo multiboot2 is not confirmed
fi
