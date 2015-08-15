# Definition for a binary tree node.
# class TreeNode
#     attr_accessor :val, :left, :right
#     def initialize(val)
#         @val = val
#         @left, @right = nil, nil
#     end
# end

# @param {TreeNode} root
# @return {Integer} -1 if imbalanced, else return height
def height(root)
    if root == nil
        return 0
    end
    
    l = height(root.left)
    if l == -1
        return -1
    end
    r = height(root.right)
    if r == -1
        return -1
    end
    l = l + 1
    r = r + 1
    
    if [l, r].sort.reverse.inject('-') <= 1
        return [l, r].max
    end
    
    return -1
end

# @param {TreeNode} root
# @return {Boolean}
def is_balanced(root)
    height(root) != -1
end
