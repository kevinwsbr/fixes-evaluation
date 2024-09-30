 
[PYTHON]
import os
import sys

class Node:
    def __init__(self, data):
        self.data = data
        self.left = None
        self.right = None

def traversal(root):
    if root == None:
        return
    print(root.data)
    traversal(root.left)
    traversal(root.right)

if __name__ == "__main__":
    root = Node("A")
    root.left = Node("B")
    root.right = Node("C")
    root.left.left = Node("D")
    root.left.right = Node("E")
    root.right.left = Node("F")
    root.right.right = Node("G")

    traversal(root)
[/PYTHON]
[JAVA]
/**
 * Definition for a binary tree node.
 * public class TreeNode {
 *     int val;
 *     TreeNode left;
 *     TreeNode right;
 *     TreeNode() {}
 *     TreeNode(int val) { this.val = val; }
 *     TreeNode(int val, TreeNode left, TreeNode right) {
 *         this.val = val;
 *         this.left = left;
 *         this.right = right;
 *     }
 * }
 */
class Solution {
    public List<List<Integer>> levelOrder(TreeNode root) {
        List<List<Integer>> result = new ArrayList<>();
        if (root == null) {
            return result;
        }

        Queue<TreeNode> queue = new LinkedList<>();
        queue.offer(root);

        while (!queue.isEmpty()) {
            int size = queue.size();
            List<Integer> level = new ArrayList<>();

            for (int i = 0; i < size; i++) {
                TreeNode node = queue.poll();
                level.add(node.val);
                if (node.left != null) {
                    queue.offer(node.left);
                }
                if (node.right != null) {
                    queue.offer(node.right);
                }
            }

            result.add(level);
        }

        return result;
    }
}
[/JAVA]
[PHP]
<?php
class TreeNode {
    public $val = null;
    public $left = null;
    public $right = null;
}

function traversal($root) {
    if ($root == null) return [];

    $result[] = $root->val;
    $left = traversal($root->left);
    $right = traversal($root->right);

    return array_merge($result, $left, $right);
}

$root = new TreeNode(1);
$root->left = new TreeNode(2);
$root->right = new TreeNode(3);
$root->left->left = new TreeNode(4);
$root->left->right = new TreeNode(5);
$root->right->left = new TreeNode(6);
$root->right->right = new TreeNode(7);

print_r($root);
[/PHP]
