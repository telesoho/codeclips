## Dealing with Docker Image Location on NTFS

edit /etc/docker/daemon.json

```json
{
	 "data-root": "/media/hd1/docker",
 	 "storage-driver": "devicemapper"
}
```

Then restart docker server.

```sh
sudo systemctl restart docker
```
