[PYTHON]
class QueryGenerator:
    def __init__(self, dialect):
        self.dialect = dialect

    def get_where_conditions(self, smth, table_name, factory, options, prepend=True):
        if smth is None:
            return '1=1'

        if hasattr(smth, '_isSequelizeMethod') and smth._isSequelizeMethod:
            return self.handle_sequelize_method(smth, table_name, factory, options, prepend)
        elif isinstance(smth, dict):
            return self.where_items_query(smth, {
                'model': factory,
                'prefix': prepend and table_name
            })
        elif isinstance(smth, (int, float)):
            primary_keys = ['id'] if not factory else list(factory.primaryKeys)
            if len(primary_keys) == 0:
                primary_keys = 'id'
            else:
                primary_keys = primary_keys[0]
            where = {primary_keys: smth}
            return self.where_items_query(where, {
                'model': factory,
                'prefix': prepend and table_name
            })
        elif isinstance(smth, str):
            return self.where_items_query(smth, {
                'model': factory,
                'prefix': prepend and table_name
            })
        elif isinstance(smth, buffer):
            return self.escape(smth)
        elif isinstance(smth, list):
            if len(smth) == 0:
                return '1=1'
            elif Utils.can_treat_array_as_and(smth):
                smth = { '$and': smth }
                return self.get_where_conditions(smth, table_name, factory, options, prepend)
            else:
                return Utils.format(smth, self.dialect)
        elif smth is None:
            return self.where_items_query(smth, {
                'model': factory,
                'prefix': prepend and table_name
            })

    def boolean_value(self, value):
        return value

    def handle_sequelize_method(self, method, table_name, factory, options, prepend=True):
        if method.key == '$or' or method.key == '$and':
            return self.where_items_query(method.value, {
                'model': factory,
                'prefix': prepend and table_name
            })
        elif method.key == '$eq':
            where = { method.value: 1 } if method.value else None
            return self.where_items_query(where, {
                'model': factory,
                'prefix': prepend and table_name
            })
        elif method.key == '$ne':
            where = { method.value: 0 } if method.value else None
            return self.where_items_query(where, {
                'model': factory,
                'prefix': prepend and table_name
            })
        else:
            raise Exception('Unknown sequelize method')

    def where_items_query(self, smth, options):
        if isinstance(smth, dict):
            return self.where_item_query(smth, options)
        elif isinstance(smth, list):
            return ' AND '.join([self.where_item_query(x, options) for x in smth])
        else:
            raise Exception('Unknown where condition')

    def where_item_query(self, smth, options):
        if isinstance(smth, dict):
            return self.where_items_query(smth, options)
        elif isinstance(smth, str):
            return f'{smth} = {self.escape(smth)}'
        else:
            raise Exception('Unknown where condition')

    def escape(self, value):
        return '{}'.format(value)
 [/PYTHON]
