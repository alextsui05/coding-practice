#!/usr/bin/env ruby
require_relative 'util/binarytree'
include BinaryTree


def find_path(root, p)
    res = []
    pred = {}
    q = [root]
    pred[p] = nil
    while not q.empty?
        node = q.pop
        if node == p
            # extract path from root to p
            while node != nil
                res.push(node)
                node = pred[node]
            end
            res.reverse!
            break
        else
            # continue searching the children
            if node.left != nil
                pred[node.left] = node
                q.push(node.left)
            end
            if node.right != nil
                pred[node.right] = node
                q.push(node.right)
            end
        end # if node == p
    end # while

    return res
end

def longest_common_prefix(node_list_a, node_list_b)
    res = []
    n = [node_list_a.size, node_list_b.size].min
    0.upto(n-1) do |i|
        if node_list_a[i] == node_list_b[i]
            res.push(node_list_a[i])
        else
            break
        end
    end
    return res
end

def lowest_common_ancestor(root, p, q)
    p1 = find_path(root, p)
    p2 = find_path(root, q)
    prefix = longest_common_prefix(p1, p2)
    return prefix.last
end

def print_path(node_list)
    node_list.each do |node|
        print " #{node.val}"
    end
    puts
end

if __FILE__ == $0
    tree = load_tree('data/tree2.txt')
    puts tree
    p = tree.left
    q = tree.left.right.right
    puts p
    puts q
    lca = lowest_common_ancestor(tree, p, q)
    puts lca
end
