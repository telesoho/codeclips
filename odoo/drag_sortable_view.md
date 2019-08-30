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
    <record id="action_product_template_attribute_value_line" model="ir.actions.act_window">
        <field name="name">Website Product Tag</field>
        <field name="res_model">product.template.attribute.value</field>
        <field name="view_type">form</field>
        <field name="view_mode">tree,form</field>
        <field name="context">{}</field>
        <field name="domain">[]</field>
    </record>
    <menuitem id="menu_product_template_attribute_value_line" name="Product attribute value" parent="website_sale.menu_catalog" sequence="11"
                action="action_product_template_attribute_value_line"/>
    
 ```
