## Define one2one relation between two table

```python
class TestA(models.Model):
  _name = 'product.testa'
  test_name_a = fields.Char()

class TestB(models.Model):
  _name = 'product.testb'
  _inherits = {'product.testa': 'testa_id'}

  testa_id = fields.Many2one('product.testa', required=True, ondelete='restrict', auto_join=True,
  string='Related to testA')

  test_name_b = fields.Char()
```
