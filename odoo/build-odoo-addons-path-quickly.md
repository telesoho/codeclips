## Build Odoo addons path quickly

see: 
https://indaclouds.fr/build-odoo-addons-path-quickly.html

Use the following command to build odoo addons path quickly.

```sh
ls -d $PWD/*/ | tr "\\n" "," | sed 's/\(.*\),/\1/'
```

The command as three parts:

1. ls -d $PWD/*/ list only directories from the current directory.
2. | tr "\\n" "," take the output of 1 and replace the line feed by a comma.
3. | sed 's/\(.*\),/\1/' take the output of 2 and remove the trailing comma at the end.

Now you can just paste the output of this command to the end of your addons path in your config file or directly pass it to the command line.
