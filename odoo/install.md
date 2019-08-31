## Install odoo

```sh
pip install -r requirements.txt
```

## How To Use Apache as Reverse Proxy on Odoo

https://www.wirasoenaryo.com/how-to-use-apache-as-reverse-proxy-on-odoo/

## How to Speed up Odoo

https://www.rosehosting.com/blog/how-to-speed-up-odoo/

## Login postgres as root

```sh
sudo -u postgres psql postgres
```



## install wkhtmltopdf

### download wkhtmltopdf
https://wkhtmltopdf.org/downloads.html

### Wkhtmltopdf failed (error code: -6). Message: The switch --header-spacing, is not support using unpatched qt (error when sending mail)
https://www.odoo.com/forum/help-1/question/wkhtmltopdf-failed-error-code-6-message-the-switch-header-spacing-is-not-support-using-unpatched-qt-error-when-sending-mail-99853


```sh
sudo dpkg -i wkhtmltox_0.12.5-1.xenial_amd64.deb
sudo apt-get install -f
```


# odoo配置中的addons路径必须使用绝对路径

```conf
addons_path = /home/telesoho/prjs/odoo/idcodoo/odoo12/odoo/addons,/home/telesoho/prjs/odoo/idcodoo/odoo12/addons,/home/telesoho/prjs/odoo/idcodoo/addons
```

