connect wifi by command
```sh
nmcli -a d wifi connect PrettyFlyForAWiFi-5G
```

[How can I tell Ubuntu to do nothing when I close my laptop lid?](https://askubuntu.com/questions/15520/how-can-i-tell-ubuntu-to-do-nothing-when-i-close-my-laptop-lid)


For 13.10 - 24.04:
To disable Ubuntu doing anything closing the laptop lid:

Open the /etc/systemd/logind.conf file in a text editor as root, for example,

```sh
sudo vi /etc/systemd/logind.conf
```

If HandleLidSwitch is not set to ignore then change it:

HandleLidSwitch=ignore
Make sure it's not commented out (it is commented out if it is preceded by the symbol #) or add it if it is missing.

Restart the systemd daemon (be aware that this will log you off) with this command:
```
sudo systemctl restart systemd-logind
```




