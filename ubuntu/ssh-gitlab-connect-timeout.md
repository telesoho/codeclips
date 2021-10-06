Use ssh mode connect to gitlab.com very slow.

Try:

```sh
ssh -Tvvv git@gitlab.com
```

Got:
```
OpenSSH_8.2p1 Ubuntu-4ubuntu0.3, OpenSSL 1.1.1f  31 Mar 2020
debug1: Reading configuration data /home/telesoho/.ssh/config
debug1: /home/telesoho/.ssh/config line 46: Applying options for gitlab.com
debug1: Reading configuration data /etc/ssh/ssh_config
debug1: /etc/ssh/ssh_config line 19: include /etc/ssh/ssh_config.d/*.conf matched no files
debug1: /etc/ssh/ssh_config line 21: Applying options for *
debug2: resolving "gitlab.com" port 22
debug2: ssh_connect_direct
debug1: Connecting to gitlab.com [2606:4700:90:0:f22e:fbec:5bed:a9b9] port 22.

```

It got timeout

so, edit your ssh config

```conf
 Host gitlab.com
     PreferredAuthentications publickey
     hostName 172.65.251.78
     IdentityFile ~/.ssh/id_ed25519
```

Use gitlab ipv4 172.65.251.78 instead.
