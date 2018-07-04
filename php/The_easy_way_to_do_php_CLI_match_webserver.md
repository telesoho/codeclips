# The easy way to do php CLI match webserver
https://stackoverflow.com/questions/42909397/laravel-5-4-on-php-7-0-pdo-exception-could-not-find-driver-mysqlc

```
There's a conflict between the PHP that is used by Apache and the PHP that is linked to the command line. (It happens more often that it should to be honest).

What is typically done is:

which php
This tells you which php will be expecuted when running in the command line. e.g. /usr/bin/php

mv /usr/bin/php /usr/bin/php.old
Then link or copy the correct PHP version to an executable path:

ln -s /path/to/php/bin/php /usr/bin/php
or the following should also work.

cp /path/to/php/bin/php /usr/bin/php
Also suggested if you want to be able to manually install mods:

ln -s /path/to/php/bin/phpize /usr/bin/phpize
ln -s /path/to/php/bin/php-config /usr/bin/php-config
This way your CLI will match your webserver.
```
