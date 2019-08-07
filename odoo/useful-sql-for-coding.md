## Useful sql for odoo

### Query all views inherited specified view id

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

### Query all fields of specified by model name

```sql
SELECT t.id
     , t.name
     , t.complete_name
     , t.model
     , t.relation
     , t.relation_field
     , t.relation_field_id
     , t.model_id
     , t.field_description
     , t.help
     , t.ttype
     , t.selection
     , t.copied
     , t.related
     , t.related_field_id
     , t.required
     , t.readonly
     , t.index
     , t.translate
     , t.size
     , t.state
     , t.on_delete
     , t.domain
     , t.selectable
     , t.relation_table
     , t.column1
     , t.column2
     , t.compute
     , t.depends
     , t.store
     , t.create_uid
     , t.create_date
     , t.write_uid
     , t.write_date
     , t.track_visibility
     , t.website_form_blacklisted
FROM public.ir_model_fields t
where model = 'product.image'
ORDER BY t.id
```
