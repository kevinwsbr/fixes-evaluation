[PYTHON]
import collections
from functools import total_ordering

Node = collections.namedtuple('Node', ['value', 'left', 'right'])

@total_ordering
class Tree(object):
    def __init__(self, value=None, left=None, right=None):
        self.root = None
        if value is not None:
            self.root = Node(value, left, right)

    def __eq__(self, other):
        if not isinstance(other, Tree):
            return NotImplemented
        return self.root == other.root

    def __lt__(self, other):
        if not isinstance(other, Tree):
            return NotImplemented
        return self.root < other.root

    def insert(self, value):
        if self.root is None:
            self.root = Node(value)
        else:
            current = self.root
            while True:
                if value < current.value:
                    if current.left is None:
                        current.left = Node(value)
                        break
                    else:
                        current = current.left
                elif value > current.value:
                    if current.right is None:
                        current.right = Node(value)
                        break
                    else:
                        current = current.right
                else:
                    break

    def traverse_pre_order(self):
        if self.root is None:
            return
        stack = [self.root]
        while len(stack) > 0:
            node = stack.pop()
            print(node.value)
            if node.right:
                stack.append(node.right)
            if node.left:
                stack.append(node.left)

    def traverse_in_order(self):
        if self.root is None:
            return
        stack = []
        current = self.root
        while len(stack) > 0 or current is not None:
            if current is not None:
                stack.append(current)
                current = current.left
            else:
                node = stack.pop()
                print(node.value)
                current = node.right

    def traverse_post_order(self):
        if self.root is None:
            return
        stack = [self.root]
        visited = set()
        while len(stack) > 0:
            node = stack[-1]
            if all(child in visited for child in [node.left, node.right]):
                print(node.value)
                stack.pop()
                visited.add(node)
            else:
                if node.right and node.right not in visited:
                    stack.append(node.right)
                elif node.left and node.left not in visited:
                    stack.append(node.left)

if __name__ == '__main__':
    tree = Tree()
    tree.insert(10)
    tree.insert(5)
    tree.insert(3)
    tree.insert(8)
    tree.insert(2)
    tree.insert(6)
    tree.insert(9)
    tree.traverse_pre_order()
    print()
    tree.traverse_in_order()
    print()
    tree.traverse_post_order()
[/PYTHON]
