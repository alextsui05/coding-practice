require_relative 'tree'

def path_sum(t, s, p=[])
    p.push(t.data)
    if t.left == nil and t.right == nil 
        if p.reduce('+') == s
            puts p.to_s
        end
        p.pop
        return
    end

    if t.left != nil
        path_sum(t.left, s, p)
    end
    if t.right != nil
        path_sum(t.right, s, p)
    end
    p.pop
end

def path_sum_any_root(t, s, p=[])
    if t == nil
        return
    end
    p.push(t.data)
    partial_sum = 0
    p.reverse.each_with_index do |val, index|
        partial_sum += val
        if partial_sum == s
            puts p.reverse.slice(0, index + 1).to_s
        end
    end

    path_sum_any_root(t.left, s, p)
    path_sum_any_root(t.right, s, p)
    p.pop
end

if __FILE__ == $0
    puts "Hi"
    t = TreeNode.parse("1 2 3 7 # # # 4 5 # # 6 # 10 # # 9 # 3 # #")
    puts t.height
    #path_sum(t, 13)
    path_sum_any_root(t, 12)
end
