## 解决国内 Pip 安装速度慢

1. Windows 在 C:\Users\（用户名）新建文件 pip.ini

2. 编辑 pip.ini 文件

[global]
# 防止超时，默认值为 100
timeout = 1000
# 地址可从 PS 选
index-url = http://pypi.douban.com/simple
[install]
trusted-host = pypi.douban.com


可以在使用pip的时候，加上参数-i和镜像地址(如 http://pypi.douban.com/simple)
例如：pip install -i http://pypi.douban.com/simple numpy --trusted-host pypi.douban.com，这样就会从豆瓣镜像安装 numpy 库。
 
PS：

清华：https://pypi.tuna.tsinghua.edu.cn/simple

阿里云：http://mirrors.aliyun.com/pypi/simple/

中国科技大学 https://pypi.mirrors.ustc.edu.cn/simple/

华中理工大学：http://pypi.hustunique.com/

山东理工大学：http://pypi.sdutlinux.org/ 

豆瓣：http://pypi.douban.com/simple

## 指定多个pip源

Linux环境下创建pip配置文件：

vim .pip/pip.conf

[global]
index-url=http://pypi.douban.com/simple
extra-index-url=http://mirrors.aliyun.com/pypi/simple/
 https://pypi.tuna.tsinghua.edu.cn/simple/
 http://pypi.mirrors.ustc.edu.cn/simple/

[install]
trusted-host=pypi.douban.com
 mirrors.aliyun.com
 pypi.tuna.tsinghua.edu.cn
 pypi.mirrors.ustc.edu.cn
