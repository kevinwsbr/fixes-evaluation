[PYTHON]
import uuid
from azure.cosmosdb.table.tableservice import TableService

class CosmosClient:
    def __init__(self, uri):
        self.uri = uri
        self.account_name = None
        self.primary_key = None
        self.connection = None

    def initialize(self, account_name, primary_key):
        self.account_name = account_name
        self.primary_key = primary_key

        if self.uri:
            self.connection = TableService(account_uri=self.uri, account_key=self.primary_key)

    def get_table_service(self):
        return self.connection

    def create_table(self, table_name):
        if self.connection:
            try:
                self.connection.create_table(table_name)
            except Exception as ex:
                print("Error creating table")
                print(ex)

            return True
        else:
            print("Not connected to Cosmos DB.")
            return False

    def delete_table(self, table_name):
        if self.connection:
            try:
                self.connection.delete_table(table_name)
            except Exception as ex:
                print("Error deleting table")
                print(ex)

            return True
        else:
            print("Not connected to Cosmos DB.")
            return False

    def is_connected(self):
        if self.connection:
            return True
        else:
            return False

def get_cosmos_client():
    uri = None
    key = None

    try:
        with open('config.txt', 'r') as f:
            lines = f.readlines()
            
            for line in lines:
                line = line.replace('\n','')

                if line.startswith('uri'):
                    uri = line.split('=')[1]
                elif line.startswith('key'):
                    key = line.split('=')[1]

        cosmos_client = CosmosClient(uri)
        cosmos_client.initialize(account_name, primary_key)
        
        return cosmos_client
    except Exception as ex:
        print("Error getting Cosmos DB credentials")
        print(ex)
        return None
[/PYTHON]
[TESTS]
# Test case 1:
assert get_cosmos_client() is not None

# Test case 2:
uri = "myaccount.documents.azure.com"
key = "mykey=="
cosmos_client = CosmosClient(uri)
cosmos_client.initialize("myaccount", key)
assert cosmos_client.is_connected() == True

# Test case 3:
cosmos_client.create_table("test")
assert cosmos_client.is_connected() == True

# Test case 4:
cosmos_client.delete_table("test")
assert cosmos_client.is_connected() == True

# Test case 5:
uri = None
key = None
with open('config.txt', 'r') as f:
    lines = f.readlines()
    
    for line in lines:
        line = line.replace('\n','')

        if line.startswith('uri'):
            uri = line.split('=')[1]
        elif line.startswith('key'):
            key = line.split('=')[1]
cosmos_client = CosmosClient(uri)
cosmos_client.initialize("myaccount", primary_key)
assert cosmos_client.is_connected() == False
[/TESTS]
