# How to find all coloumn name from all the tables in mysql.

https://stackoverflow.com/questions/193780/how-to-find-all-the-tables-in-mysql-with-specific-column-names-in-them

```sql
SELECT DISTINCT TABLE_NAME 
    FROM INFORMATION_SCHEMA.COLUMNS
    WHERE COLUMN_NAME LIKE '%article_id%'
        AND TABLE_SCHEMA='haibaobei';
```
