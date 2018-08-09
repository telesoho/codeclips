# Use incron monitor files and folder
https://www.linux.com/learn/how-use-incron-monitor-important-files-and-folders



```sh
sudo incrontab -e
```

opt/lampp/htdocs/haibaobei-ec.com/upload IN_CREATE /bin/chown -R daemon:daemon $@/$#
