## postgresql

  ```sh
  apt-get install postgresql -y #install postgresql
  sudo -u postgres psql   #Use psql to connect postgresql by postgres user
  ```

  https://www.postgresql.org/docs/11/tutorial-sql-intro.html

```sql
--指定したテーブルのカラム一覧とコメントを取得するクエリ
select
c.table_name,
c.column_name,
c.data_type,
(select description from pg_description where
 pg_description.objoid= pg_stat_user_tables.relid and
 pg_description.objsubid= c.ordinal_position
)
from
 pg_stat_user_tables,
 information_schema.columns as c
WHERE 
  c.table_schema = 'public'
  AND c.table_name   like 'product_%'
and pg_stat_user_tables.relname = c.table_name
```
