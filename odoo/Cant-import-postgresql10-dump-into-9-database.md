# I need to somehow convert a v10 dump file into one which is 9.6 compatible
https://stackoverflow.com/questions/49547602/cant-import-postgresql10-dump-into-9-6-database

```sh
cat test10.sql | sed '/AS integer/d' > test9.sql
```
