# Install multiple php version on apache ubuntu
https://tecadmin.net/install-multiple-php-version-apache-ubuntu/

In fact you can use 

```
Include conf-available/php5.6-fpm.conf
```

to use fpm moduel easy.


```conf
 <VirtualHost *:8080>
     # The ServerName directive sets the request scheme, hostname and port that
     # the server uses to identify itself. This is used when creating
     # redirection URLs. In the context of virtual hosts, the ServerName
     # specifies what hostname must appear in the request's Host: header to
     # match this virtual host. For the default virtual host (this file) this
     # value is not decisive as it is used as a last resort host regardless.
     # However, you must set it for any further virtual host explicitly.
     #ServerName www.example.com
 
     ServerName haibaobei-dev
     ServerAdmin webmaster@haibaobei-dev
     DocumentRoot /home/hilines/prjs/haibaobei-ec-dev
     <Directory "/home/hilines/prjs/haibaobei-ec-dev">
         Options All
         AllowOverride All
         Require all granted
     </Directory>
 
     # Available loglevels: trace8, ..., trace1, debug, info, notice, warn,
     # error, crit, alert, emerg.
     # It is also possible to configure the loglevel for particular
     # modules, e.g.
     #LogLevel info ssl:warn
 
     ErrorLog ${APACHE_LOG_DIR}/haibaobei-ec-dev-error.log
     CustomLog ${APACHE_LOG_DIR}/haibaobei-ec-dev-access.log combined
 
     # For most configuration files from conf-available/, which are
     # enabled or disabled at a global level, it is possible to
     # include a line for only one particular virtual host. For example the
     # following line enables the CGI configuration for this host only
     # after it has been globally disabled with "a2disconf".
     #Include conf-available/serve-cgi-bin.conf
     Include conf-available/php5.6-fpm.conf
 </VirtualHost>
 

 <VirtualHost *:8081>
     # The ServerName directive sets the request scheme, hostname and port that
     # the server uses to identify itself. This is used when creating
     # redirection URLs. In the context of virtual hosts, the ServerName
     # specifies what hostname must appear in the request's Host: header to
     # match this virtual host. For the default virtual host (this file) this
     # value is not decisive as it is used as a last resort host regardless.
     # However, you must set it for any further virtual host explicitly.
     ServerName capi.haibaobei-ec.com
 
     ServerAdmin webmaster@localhost
     DocumentRoot /home/hilines/prjs/capi.haibaobei-ec/public
     <Directory "/home/hilines/prjs/capi.haibaobei-ec/public">
         Options All
         AllowOverride All
         Require all granted
     </Directory>
 
     # Available loglevels: trace8, ..., trace1, debug, info, notice, warn,
     # error, crit, alert, emerg.
     # It is also possible to configure the loglevel for particular
     # modules, e.g.
     #LogLevel info ssl:warn
 
     ErrorLog ${APACHE_LOG_DIR}/capi-haibaobei-ec-error.log
     CustomLog ${APACHE_LOG_DIR}/capi-haibaobei-ec-access.log combined
 
     # For most configuration files from conf-available/, which are
     # enabled or disabled at a global level, it is possible to
     # include a line for only one particular virtual host. For example the
     # following line enables the CGI configuration for this host only
     # after it has been globally disabled with "a2disconf".
     #Include conf-available/serve-cgi-bin.conf
     Include conf-available/php7.2-fpm.conf
 </VirtualHost>

```

Also, you should change owner for  /run/php/php7.2-fpm.sock same to apache user defined by config.

```sh
sudo chown hilines:hilines /run/php/php7.2-fpm.sock
```

