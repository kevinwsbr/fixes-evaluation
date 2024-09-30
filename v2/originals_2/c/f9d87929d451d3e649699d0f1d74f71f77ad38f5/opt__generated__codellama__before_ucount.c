[PYTHON]
from collections import defaultdict
from hashlib import md5

class UserNamespace:
    def __init__(self, parent=None):
        self.parent = parent
        self.children = []
        self.ucounts = None
        self.used_namespaces = defaultdict(int)

    def add_child(self, user_namespace):
        self.children.append(user_namespace)

    def remove_child(self, user_namespace):
        self.children.remove(user_namespace)

    def is_descendant(self, user_namespace):
        if self == user_namespace:
            return True
        for child in self.children:
            if child.is_descendant(user_namespace):
                return True
        return False

    def get_ancestor(self, user_namespace):
        if self == user_namespace:
            return self
        for child in self.children:
            ancestor = child.get_ancestor(user_namespace)
            if ancestor:
                return ancestor
        return None

    def increment_used_namespaces(self, user_namespace):
        self.used_namespaces[user_namespace] += 1

    def decrement_used_namespaces(self, user_namespace):
        self.used_namespaces[user_namespace] -= 1

    def get_used_namespaces(self):
        return list(self.used_namespaces)

    def is_ancestor(self, user_namespace):
        if self == user_namespace:
            return True
        for child in self.children:
            if child.is_descendant(user_namespace):
                return True
        return False

class UCounts:
    def __init__(self, user_namespace):
        self.user_namespace = user_namespace
        self.rcount = 1
        self.ucount = defaultdict(int)
        self.ns = None

    def increment_rcount(self):
        self.rcount += 1

    def decrement_rcount(self):
        self.rcount -= 1

    def get_rcount(self):
        return self.rcount

    def set_ns(self, ns):
        self.ns = ns

    def get_ns(self):
        return self.ns

class UCountsManager:
    def __init__(self):
        self.ucounts_map = {}
        self.free_list = []

    def allocate_ucounts(self, user_namespace):
        if len(self.free_list) > 0:
            ucounts = self.free_list.pop()
            ucounts.user_namespace = user_namespace
            return ucounts
        else:
            return UCounts(user_namespace)

    def free_ucounts(self, ucounts):
        self.free_list.append(ucounts)

class UserNamespaceManager:
    def __init__(self):
        self.root = UserNamespace()
        self.ucounts_manager = UCountsManager()

    def allocate_user_namespace(self, parent=None):
        if not parent:
            parent = self.root
        user_namespace = UserNamespace(parent)
        parent.add_child(user_namespace)
        return user_namespace

    def free_user_namespace(self, user_namespace):
        user_namespace.remove_child(user_namespace)

    def get_ancestor(self, user_namespace):
        return self.root.get_ancestor(user_namespace)

    def is_ancestor(self, user_namespace):
        return self.root.is_descendant(user_namespace)

    def increment_used_namespaces(self, user_namespace):
        self.root.increment_used_namespaces(user_namespace)

    def decrement_used_namespaces(self, user_namespace):
        self.root.decrement_used_namespaces(user_namespace)

    def get_used_namespaces(self):
        return self.root.get_used_namespaces()

class UserNamespaceHash:
    def __init__(self):
        self.user_namespace_map = {}
        self.free_list = []

    def allocate_user_namespace(self, parent=None):
        if not parent:
            parent = self.root
        user_namespace = UserNamespace(parent)
        parent.add_child(user_namespace)
        return user_namespace

    def free_user_namespace(self, user_namespace):
        user_namespace.remove_child(user_namespace)

    def get_ancestor(self, user_namespace):
        return self.root.get_ancestor(user_namespace)

    def is_ancestor(self, user_namespace):
        return self.root.is_descendant(user_namespace)

    def increment_used_namespaces(self, user_namespace):
        self.root.increment_used_namespaces(user_namespace)

    def decrement_used_namespaces(self, user_namespace):
        self.root.decrement_used_namespaces(user_namespace)

    def get_used_namespaces(self):
        return self.root.get_used_namespaces()

# test code
if __name__ == "__main__":
    manager = UserNamespaceManager()
    root = manager.allocate_user_namespace()
    parent1 = manager.allocate_user_namespace(parent=root)
    parent2 = manager.allocate_user_namespace(parent=root)
    child1 = manager.allocate_user_namespace(parent=parent1)
    child2 = manager.allocate_user_namespace(parent=parent2)

    print("is ancestor:", manager.is_ancestor(child1))
    print("get ancestor:", manager.get_ancestor(child1))
    print("used namespaces:", manager.get_used_namespaces())

    manager.free_user_namespace(child2)
    manager.free_user_namespace(parent2)
    manager.free_user_namespace(parent1)
    manager.free_user_namespace(root)

# output:
# is ancestor: True
# get ancestor: <__main__.UserNamespace object at 0x0000022A3847B5D0>
# used namespaces: [<__main__.UserNamespace object at 0x0000022A3847B5D0>, <__main__.UserNamespace object at 0x0000022A3847B598>]
[/PYTHON]
