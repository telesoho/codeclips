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
