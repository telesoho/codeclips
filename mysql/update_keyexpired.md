# 发生key expires

```sh
telesoho@telesoho-UX430UNR:~/Downloads$ sudo apt-get update
Hit:1 http://jp.archive.ubuntu.com/ubuntu xenial InRelease
Get:2 http://repo.mysql.com/apt/ubuntu xenial InRelease [21.6 kB]                                                                                                                                        
Get:3 http://jp.archive.ubuntu.com/ubuntu xenial-updates InRelease [109 kB]                                                                                                                                                        
Ign:4 http://dl.google.com/linux/chrome/deb stable InRelease                                                                                                                                                                                  
Ign:2 http://repo.mysql.com/apt/ubuntu xenial InRelease                                                                                                                                                                                       
Get:5 http://jp.archive.ubuntu.com/ubuntu xenial-backports InRelease [107 kB]                                                                                                                                                                 
Hit:6 http://packages.microsoft.com/repos/vscode stable InRelease                                                                                                                                                                             
Hit:7 http://dl.google.com/linux/chrome/deb stable Release                                                                                                                         
Get:9 http://packages.elementary.io/appcenter xenial InRelease [6,128 B]                                                                                                              
Get:10 http://security.ubuntu.com/ubuntu xenial-security InRelease [109 kB]                                                                                              
Get:11 http://repo.mysql.com/apt/ubuntu xenial/mysql-5.7 Sources [942 B]                                                                                                
Get:12 http://repo.mysql.com/apt/ubuntu xenial/mysql-apt-config amd64 Packages [564 B]                                                                                  
Hit:13 http://ppa.launchpad.net/elementary-os/stable/ubuntu xenial InRelease                                                                                          
Get:14 http://packages.elementary.io/appcenter xenial/main amd64 DEP-11 Metadata [88.7 kB]                                                                                                                            
Get:15 http://repo.mysql.com/apt/ubuntu xenial/mysql-apt-config i386 Packages [564 B]                                                                                                                      
Hit:16 http://ppa.launchpad.net/graphics-drivers/ppa/ubuntu xenial InRelease                                                                                                                               
Get:17 http://repo.mysql.com/apt/ubuntu xenial/mysql-5.7 amd64 Packages [5,662 B]                                                                                                               
Hit:18 http://ppa.launchpad.net/jonathonf/vim/ubuntu xenial InRelease                                                             
Get:19 http://repo.mysql.com/apt/ubuntu xenial/mysql-5.7 i386 Packages [5,674 B]                                                                              
Get:20 http://repo.mysql.com/apt/ubuntu xenial/mysql-tools amd64 Packages [4,324 B]                                                                       
Get:21 http://repo.mysql.com/apt/ubuntu xenial/mysql-tools i386 Packages [3,582 B]                                                                                     
Hit:22 http://ppa.launchpad.net/ondrej/php/ubuntu xenial InRelease                                                                                                                                                                            
Hit:23 http://ppa.launchpad.net/elementary-os/os-patches/ubuntu xenial InRelease                                                                                                                                                              
Hit:24 http://archive.ubuntukylin.com:10006/ubuntukylin xenial InRelease                                                                                                                                                                      
Fetched 463 kB in 8s (51.5 kB/s)                                                                                                                                                                                                              
Reading package lists... Done
W: GPG error: http://repo.mysql.com/apt/ubuntu xenial InRelease: The following signatures were invalid: KEYEXPIRED 1550412832  KEYEXPIRED 1550412832  KEYEXPIRED 1550412832
W: The repository 'http://repo.mysql.com/apt/ubuntu xenial InRelease' is not signed.
N: Data from such a repository can't be authenticated and is therefore potentially dangerous to use.
N: See apt-secure(8) manpage for repository creation and user configuration details.
```

参考如下文章:

https://futurestud.io/tutorials/fix-ubuntu-debian-apt-get-keyexpired-the-following-signatures-were-invalid
