# ORM methods

https://www.odoo.com/documentation/14.0/developer/reference/addons/orm.html#common-orm-methods


One2many and Many2many use a special “commands” format to manipulate the set of records stored in/associated with the field.

This format is a list of triplets executed sequentially, where each triplet is a command to execute on the set of records. Not all commands apply in all situations. Possible commands are:

- (0, 0, values)
  adds a new record created from the provided value dict.

- (1, id, values)
  updates an existing record of id id with the values in values. Can not be used in create().

- (2, id, 0)
  removes the record of id id from the set, then deletes it (from the database). Can not be used in create().

- (3, id, 0)
  removes the record of id id from the set, but does not delete it. Can not be used in create().

- (4, id, 0)
  adds an existing record of id id to the set.

- (5, 0, 0)
  removes all records from the set, equivalent to using the command 3 on every record explicitly. Can not be used in create().

- (6, 0, ids)
  replaces all existing records in the set by the ids list, equivalent to using the command 5 followed by a command 4 for each id in ids.
