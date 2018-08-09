# Use incron monitor files and folder
https://www.linux.com/learn/how-use-incron-monitor-important-files-and-folders

# install incron
https://github.com/ar-/incron
http://blog.topspeedsnail.com/archives/4336

```sh
sudo apt-get install incron
sudo incrontab -e
vim /etc/incron.allow
```


```
$$ - a dollar sign
$@ - the watched filesystem path (see above)
$# - the event-related file name
$% - the event flags (textually)
$& - the event flags (numerically)
```

```
opt/lampp/htdocs/haibaobei-ec.com/upload IN_CREATE /bin/chown -R daemon:daemon $@/$#
```
