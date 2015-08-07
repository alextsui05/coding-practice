module BinaryTree
class TreeNode
    attr_accessor :val, :left, :right
    def initialize(val)
        @val = val
        @left, @right = nil, nil
    end

    def to_s
        l, r = "#", "#"
        if @left != nil
            l = @left.to_s
        end
        if @right != nil
            r = @right.to_s
        end
        "#{@val} #{l} #{r}"
    end
end

def load_tree(fn)
    File.open(fn) do |file|
        data = file.readline.split.map { |token| Integer(token) rescue nil }
        if data == [nil]
            return nil
        else
            root = TreeNode.new(data.shift)
            build_tree(root, data)
            return root
        end
    end
end

def build_tree(root, data)
    if data.empty?
        return
    end
    token = data.shift
    if token != nil
        root.left = TreeNode.new(token)
        build_tree(root.left, data)
    end
    token = data.shift
    if token != nil
        root.right = TreeNode.new(token)
        build_tree(root.right, data)
    end
end
end

if __FILE__ == $0
    include BinaryTree
    nodes = (1..3).map { |i| TreeNode.new(i) }
    nodes[1].left = nodes[0]
    nodes[1].right = nodes[2]
    File.open('tree.txt', 'w') do |file|
        file.puts nodes[1]
    end
    tree = load_tree('tree.txt')
    puts tree   
end
