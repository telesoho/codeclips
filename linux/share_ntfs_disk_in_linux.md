# Share NTFS folder in linux

1. Use ntfs-config to mount NTFS disk

   This step will add auto mount script to /etc/fstab.   
   
1. Install samba and add the following to /etc/samba/smb.conf

```
[global]
   workgroup = WORKGROUP
   force user = <username>

[linux-data]
   comment = Linux data
   path = /media/ntfs/data
   browseable = yes
   public = yes
   writeable = yes
```
