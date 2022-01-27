# show gitlab-runner log
```sh
journalctl -u gitlab-runner -f
```

## set: Illegal option -o pipefail

https://gitlab.com/gitlab-org/gitlab-runner/-/issues/1170

update entrypoint [""] works for me .
