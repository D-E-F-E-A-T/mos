# sudo kpartx -av out/c.img
sudo mount /dev/mapper/loop0p1 /mnt/img
sudo rm /mnt/img/kernel.bin
sudo cp kernel.bin /mnt/img && cd / && sudo umount /mnt/img
