# Cannt mount ntfs driver contains an unclean file system

see https://askubuntu.com/questions/462381/cant-mount-ntfs-drive-the-disk-contains-an-unclean-file-system

If you can't access the drive, execute the following command:

'''sh
sudo ntfsfix /dev/sdXY
'''
where XY is the partition

e.g sda2 or sdb1

Then, mount with:

'''sh
sudo mount -o rw /dev/sdXY
'''
