# Definition for a binary tree node.
# class TreeNode
#     attr_accessor :val, :left, :right
#     def initialize(val)
#         @val = val
#         @left, @right = nil, nil
#     end
# end

class BSTIterator
    # @param {TreeNode} root
    def initialize(root)
        @stack = []
        n = root
        while n
            @stack.push n
            n = n.left
        end
    end

    # @return {Boolean}
    def has_next
        !@stack.empty?
    end

    # @return {Integer}
    def next
        res = @stack.last.val
        n = @stack.pop.right
        while n
            @stack.push n
            n = n.left
        end
        res
    end
end

# Your BSTIterator will be called like this:
# i, v = BSTIterator.new(root), []
# while i.has_next()
#    v << i.next
# end