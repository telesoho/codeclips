## 数量や金額の小数点表示を変えることはできますか？
https://www.quartile.co/en_US/forum/how-to/3/21

## 将商品贩卖数量的小数点位数和产品单位的小数点位数统一

```python
    sales_count = fields.Float(compute='_compute_sales_count', string='Sold')
```

改为:

```python
    sales_count = fields.Float(compute='_compute_sales_count', string='Sold', digits=dp.get_precision('Product Unit of Measure'))
```

## 一个比较好的odoo开发博客

https://www.cybrosys.com/blog

## 图片引入模块

https://www.odoo.com/apps/modules/12.0/import_image_fromurl/

## 将附件上传到s3模块

https://apps.odoo.com/apps/modules/12.0/pr1_s3/

## 亚马逊对接模块

https://apps.odoo.com/apps/modules/12.0/amazon_ept/
