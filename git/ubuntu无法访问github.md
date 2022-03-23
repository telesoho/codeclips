先后试了网上两个教程，终于解决。通过修改host文件实现访问。

教程1：

1）终端输入： sudo gedit /etc/hosts 打开hosts文件；

2）使用ip查找工具查询 http://github.com和IP:http://github.global.ssl.fastly.net的ip地址并添加到hosts文件末尾；

![image](https://user-images.githubusercontent.com/10979091/159617341-c961dedc-2bf3-4105-922e-659e0c91defe.png)

3）关掉hosts文件，在终端输入：/etc/init.d/networking restart即可。

ps1：通过以上操作后，在终端ping http://github.com可以连接到http://github.com，但是在浏览器上依旧无法打开。

教程2：

1）再次打开hosts文件，在127.0.0.1 localhost后追加

http://xxx.xxx.xxx.xxx http://github.com git

203.208.39.99 github.com

![image](https://user-images.githubusercontent.com/10979091/159617399-c77e34b3-3b64-4453-9202-6bff4ae11037.png)


2）保存关闭，即可打开 github.com

ps2：http://xxx.xxx.xxx.xxx 为本机ipv4的地址；203.208.39.99 是利用站长工具，获取的github数据库的ipv4地址。

可以点击这里跳转：站长工具

ps3:原教程链接

ps4:如果以上方法仍不行，且只是想git clone或者浏览github上的东西，可以搜一些镜像网站，如 gitclone.com/ 等

ubuntu 无法访问github.com
