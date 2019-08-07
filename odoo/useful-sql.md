## Useful sql for odoo

### Request all views inherited specified view id

```sql
SELECT t.id
     , t.name
     , t.model
     , t.key
     , t.priority
     , t.type
     , t.arch_db
     , t.arch_fs
     , t.inherit_id
     , t.field_parent
     , t.mode
     , t.active
     , t.create_uid
     , t.create_date
     , t.write_uid
     , t.write_date
     , t.website_meta_title
     , t.website_meta_description
     , t.website_meta_keywords
     , t.website_meta_og_img
     , t.customize_show
     , t.website_id
     , t.theme_template_id
FROM public.ir_ui_view t
  left join public.ir_ui_view t2 on t.inherit_id = t2.id
where t2.key='sale.variants'
or t.key = 'sale.variants' 
ORDER BY t.id
```

### 
```sql

```
