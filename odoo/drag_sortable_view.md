# drag and sorable tree view

```xml

    <record id="product_template_attribute_value_line_view" model="ir.ui.view">
        <field name="name">Product template attribute values</field>
        <field name="model">product.template.attribute.value</field>
        <field name="arch" type="xml">
            <tree string="product attribute value sortable"
                editable="bottom"
                create="false"
                edit="false"
                default_order="website_sequence"
                delete="false">
                <field name="website_sequence" widget="handle"/>
                <field name="product_attribute_value_id"/>
                <field name="product_tmpl_id"/>
            </tree>
        </field>
    </record>
    
 ```
