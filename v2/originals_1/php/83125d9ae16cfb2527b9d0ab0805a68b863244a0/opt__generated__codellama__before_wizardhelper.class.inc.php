[PYTHON]
import copy
import json

from cmdb.model import MetaModel

class WizardHelper:
    def __init__(self, form_prefix, object_type, initial_state=None):
        self.form_prefix = form_prefix
        self.object_type = object_type
        self.initial_state = initial_state
        self.fields_map = {}
        self.fields_to_update = []
        self.return_not_editable_fields = False
        self.wiz_helper_js_var_name = None
    
    def add_field(self, field_name, field_id):
        if field_name not in self.fields_map:
            self.fields_map[field_name] = field_id
    
    def get_target_class(self):
        return self.object_type
    
    def get_form_prefix(self):
        return self.form_prefix
    
    def get_initial_state(self):
        return self.initial_state
    
    def get_stimulus(self):
        pass
    
    def get_id_for_field(self, field_name):
        if field_name in self.fields_map:
            return self.fields_map[field_name]
        else:
            return ''
    
    def get_return_not_editable_fields(self):
        return self.return_not_editable_fields
    
    def to_json(self):
        data = {
            'm_sClass': self.object_type,
            'm_sFormPrefix': self.form_prefix,
            'm_aData': [],
            'm_oFieldsMap': {},
            'm_bReturnNotEditableFields': self.return_not_editable_fields
        }
        
        if self.initial_state:
            data['m_sInitialState'] = self.initial_state
        
        for field in self.fields_to_update:
            att_code, field_name = field.split('.')
            attr_def = MetaModel.get_attribute_def(self.object_type, att_code)
            
            if attr_def.is_external_key():
                # For external keys: load the target object so that external fields
                # get filled too
                value = self.get_id_for_field(att_code)
                if value:
                    target_obj = MetaModel.get_object(attr_def.target_class, value)
                    field_value = target_obj.get_key()
            else:
                field_value = self.get_id_for_field(field_name)
            
            data['m_aData'].append({'att_code': att_code, 'value': field_value})
        
        for field in self.fields_map:
            attr_def = MetaModel.get_attribute_def(self.object_type, field)
            
            if not attr_def.is_external_key():
                data['m_oFieldsMap'][field] = self.fields_map[field]
        
        return json.dumps(data, default=str)
    
    def get_js_for_update_fields(self):
        if not self.wiz_helper_js_var_name:
            raise Exception('Please set the wizard helper JS variable name before calling this method')
        
        data = copy.deepcopy(self.__dict__)
        del data['wiz_helper_js_var_name']
        
        return f'{self.wiz_helper_js_var_name}.m_oData = {json.dumps(data)}; {self.wiz_helper_js_var_name}.UpdateFields();'
    
    @staticmethod
    def parse_json_set(me, link_class, ext_key_to_me, json_set):
        set = CMDBObjectSet.from_scratch(link_class)
        
        for link_obj in json.loads(json_set):
            link = MetaModel.new_object(link_class)
            
            for att_code, value in link_obj.items():
                attr_def = MetaModel.get_attribute_def(link_class, att_code)
                
                if attr_def.is_external_key():
                    # For external keys: load the target object so that external fields
                    # get filled too
                    value = me.get_id_for_field(att_code)
                    if value:
                        target_obj = MetaModel.get_object(attr_def.target_class, value)
                        field_value = target_obj.get_key()
                else:
                    field_value = me.get_id_for_field(att_code)
                
                link.set_attribute(att_code, field_value)
            
            set.add(link)
        
        return set
[/PYTHON]
