# access rule

  权限对象模型是 ir.model.access.csv
  一般是放在security 文件夹下的 ir.model.access.csv 文件来管理的
  文件表头如下：
  id,name,model_id:id,group_id:id,perm_read,perm_write,perm_create,perm_unlink
   
  一个例子：
  ```csv
  id,name,model_id:id,group_id:id,perm_read,perm_write,perm_create,perm_unlink
  access_payment_notice_account_user,payment.notice.account.user,model_payment_notice,account.group_account_user,1,1,1,1
  access_payment_notice_sale_user,payment.notice.sale.user,model_payment_notice,base.group_sale_salesman,1,1,0,0
  ```  
  
  分析这个是针对 payment.notice 这个模型做访问权限设置
  可以看一下对应模型定义的代码：
  ```python
   class PaymentNotice(models.Model):
    _name = "payment.notice"
  ```
   id:权限的ID不可重复 一般取名为 access_模型名_特定用户组名（用下划线连起来）
   name 描述 一般命名沿用模型名用“.”连接加 用户组名
   model_id:id：对象，命名是model_模型名（用下划线连起来）
   group_id:id  组名称 （模块.用户组名）
   下面的，0 表示无权限， 1 表示有权限
   perm_read  只读
   perm_write 修改
   perm_create 创建
   perm_unlink 删除

   记得修改__manifest__.py
   ```python
    # always loaded
    'data': [
        'security/ir.model.access.csv',
        'views/views.xml',
        'views/templates.xml',
        'views/menu.xml',
    ],
    ```
    
   最后，记得使用upgrade升级该模块，注意：即使用了--dev=all方式，也不会自动升级。
