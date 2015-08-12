require_relative 'util/binarytree'
include BinaryTree

# Definition for a binary tree node.
# class TreeNode
#     attr_accessor :val, :left, :right
#     def initialize(val)
#         @val = val
#         @left, @right = nil, nil
#     end
# end
def flatten_tree(tree)
    if tree == nil
        return nil
    end
    l = flatten_tree(tree.left)
    r = flatten_tree(tree.right)
    tree.left = nil
    if l != nil
        tree.right = l
        tail = l
        while tail.right != nil
            tail = tail.right
        end
        tail.right = r
    end
    puts tree
    return tree
end

# @param {TreeNode} root
# @return {Void} Do not return anything, modify root in-place instead.
def flatten(root)
    flatten_tree(root)
end

if __FILE__ == $0
    #tree = load_tree('data/flatten_binary_tree_to_linked_list.txt')
    tree = TreeNode.new(0)
    puts tree
    flatten_tree(tree)
end
