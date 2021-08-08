class CrmLead(models.Model):
    _inherit = 'crm.lead'
    _description = '案件'
    
    def get_attachement_write_date(self, field_name):
        attachment = self.env['ir.attachment'].search_read(
            domain=[['res_id', '=', self.id],['res_model', '=', self._name], ['res_field', '=', field_name]], 
            fields=['write_date'], limit=1)
        if attachment:
            return attachment[0]['write_date'] 
