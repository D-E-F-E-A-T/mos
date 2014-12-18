# sudo kpartx -av out/c.img
sudo mount /dev/mapper/loop1p1 /mnt/img
sudo cp -u kernel.bin /mnt/img 
sleep 1
cd / && sudo umount /mnt/img
