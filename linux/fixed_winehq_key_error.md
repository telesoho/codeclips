apt-get update error

```sh
Failed to fetch https://dl.winehq.org/wine-builds/ubuntu/dists/xenial/InRelease  The following signatures couldn't be verified because the public key is not available: NO_PUBKEY 76F1A20FF987672F
```

fixed:

```sh
wget -nc https://dl.winehq.org/wine-builds/winehq.key
sudo apt-key add winehq.key
```

