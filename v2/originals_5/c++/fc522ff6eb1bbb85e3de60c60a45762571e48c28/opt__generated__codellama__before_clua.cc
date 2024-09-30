 
[PYTHON]
class LuaContext:
    def __init__(self, lua):
        self.lua = lua

    def execute(self, chunk):
        return self.lua.execute(chunk)

    def get_global(self, name):
        return self.lua.get_global(name)

    def set_global(self, name, value):
        self.lua.set_global(name, value)

    def call(self, func_ref, args):
        return self.lua.call(func_ref, args)

    def is_table(self, index):
        return self.lua.is_table(index)

    def is_function(self, index):
        return self.lua.is_function(index)

    def is_number(self, index):
        return self.lua.is_number(index)

    def is_string(self, index):
        return self.lua.is_string(index)

    def is_userdata(self, index):
        return self.lua.is_userdata(index)
[/PYTHON]
[TESTS]
# Test case 1:
def test_execute(lc):
    chunk = "return 1 + 2"
    result = lc.execute(chunk)
    assert result == 3

# Test case 2:
def test_get_global(lc):
    chunk = "x = 10; return x"
    result = lc.execute(chunk)
    assert result == 10
    result = lc.get_global("x")
    assert result == 10

# Test case 3:
def test_set_global(lc):
    chunk = "x = 10; return x"
    result = lc.execute(chunk)
    assert result == 10
    result = lc.get_global("x")
    assert result == 10
    lc.set_global("x", 20)
    result = lc.get_global("x")
    assert result == 20

# Test case 4:
def test_call(lc):
    chunk = "function f(a, b) return a + b end; return f"
    func_ref = lc.execute(chunk)
    result = lc.call(func_ref, [1, 2])
    assert result == 3

# Test case 5:
def test_type(lc):
    chunk = "return 42"
    result = lc.execute(chunk)
    assert lc.is_number(-1)
    lc.pop()

    chunk = "return 'hello'"
    result = lc.execute(chunk)
    assert lc.is_string(-1)
    lc.pop()

    chunk = "return function() end"
    result = lc.execute(chunk)
    assert lc.is_function(-1)
    lc.pop()

    chunk = "return {}"
    result = lc.execute(chunk)
    assert lc.is_table(-1)
    lc.pop()

    chunk = "return UserData()"
    result = lc.execute(chunk)
    assert lc.is_userdata(-1)
    lc.pop()
[/TESTS]
