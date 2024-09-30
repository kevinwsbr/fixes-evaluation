[PYTHON]
import ctypes as ct

def get_constant(name):
    return ct.c_ulonglong(ct.cast(ct.pointer(ct.byref(ct.PyLong_FromString(name))), ct.POINTER(ct.c_ulonglong)).contents).value

IPV6_ADDR_GEN_MODE = get_constant("IPV6_ADDR_GEN_MODE")
[/PYTHON]
[TESTS]
# Test case 1:
assert IPV6_ADDR_GEN_MODE == 53
# Test case 2:
assert IPV6_ADDR_GEN_MODE != 100
[/TESTS]
