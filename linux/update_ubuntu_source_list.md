#　变更源列表
https://wiki.ubuntu.org.cn/%E6%BA%90%E5%88%97%E8%A1%A8

1. 备份
```sh
sudo cp /etc/apt/sources.list /etc/apt/sources.list_backup
```

2. 修改/etc/apt/sources.list，删除不需要的源地址
```sh
sudo vim /etc/apt/sources.list
```

3.清空/var/lib/apt/lists里的文件
```sh
sudo rm /var/lib/apt/lists
```

4. 更新
```sh
sudo apt-get clean
sudo apt-get update
```


