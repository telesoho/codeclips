# Configure vhost folder outside of htdocs on ubuntu

1. Set vhost folder by edit httpd-vhost.conf

```
<virtualhost 127.0.0.4:80>
      documentroot "/home/telesoho/prjs/ShopsN_Web"
      <directory "/home/telesoho/prjs/ShopsN_Web">
         options all
         allowoverride all
         require all granted
      </directory>
 </virtualhost>
```

2. Change folder owner to deamon

```sh
sudo chown -R daemon:daemon /home/telesoho/prjs/ShopsN_Web/
```
