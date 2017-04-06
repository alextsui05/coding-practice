#!/usr/bin/env ruby

class TreeNode
    attr_accessor :data
    attr_accessor :left
    attr_accessor :right

    def initialize(data)
        @data = data
        @left = nil
        @right = nil
    end

    def height
        res = 1
        if @left != nil then
            res += @left.height
        end
        if @right != nil then
            res = [res, @right.height + 1].max
        end
        res
    end

    def check_height
        l = 0
        r = 0
        if @left != nil then
            l = @left.check_height
            if l == -1 then
                return -1
            end
        end
        if @right != nil then
            r = @right.check_height
            if r == -1 then
                return -1
            end
        end

        if l < r then
            if r - l > 1 then
                return -1
            end
        elsif r < l then
            if l - r > 1 then
                return -1
            end
        end
        [l, r].max + 1
    end

    def balanced?
        check_height != -1
    end

    def is_bst?
        res = self.check_bst
        return res != false
    end

    # Return false if not bst, else return [lo, hi]
    def check_bst
        if @left == nil and @right == nil
            return [@data, @data]
        elsif @left == nil
            res = @right.check_bst
            if ! res or @data > res[0]
                return false
            else
                return [@data, res[1]]
            end
        elsif @left == nil
            res = @right.check_bst
            if ! res or @data > res[0]
                return false
            else
                return [@data, res[1]]
            end
        else
            l = @left.check_bst
            if @data < l[1]
                return false
            end
            r = @right.check_bst
            if @data > r[0]
                return false
            end
            return [l[0], r[1]]
        end
    end

    def to_s
        res = "#{@data}"
        if @left != nil then
            res += " #{@left.to_s}"
        else
            res += " #"
        end
        if @right != nil then
            res += " #{@right.to_s}"
        else
            res += " #"
        end
        res
    end

    def inspect
        to_s
    end

    def to_levels
        res = [[@data]]
        if @left == nil and @right == nil then
            return res
        elsif @left == nil then
            rest = @right.to_levels
            return rest.unshift(res[0])
        elsif @right == nil then
            rest = @left.to_levels
            return rest.unshift(res[0])
        else
            l = @left.to_levels
            r = @right.to_levels
            while l.size < r.size
                l.push([])
            end
            while r.size < l.size
                r.push([])
            end
            rest = l.zip(r).map { |pair| pair[0].concat(pair[1]) }
            return rest.unshift(res[0])
        end
    end

    def to_levels_bfs
        res = []
        current_level = [self]
        while current_level.size > 0
            res.push(current_level)
            next_level = []
            current_level.each { |node|
                if node.left != nil then
                    next_level.push(node.left)
                end
                if node.right != nil then
                    next_level.push(node.right)
                end
            }
            current_level = next_level
        end
        res.map { |level| level.map { |node| node.data } }
    end

    def self.from_sorted_array(arr, l = 0, r = arr.size)
        if (r - l) == 0
            return nil
        elsif (r - l) == 1
            return TreeNode.new(arr[l])
        end
        m = (r + l)/2
        t = TreeNode.new(arr[m])
        t.left = from_sorted_array(arr, l, m)
        t.right = from_sorted_array(arr, m+1, r)
        t
    end

    def self.parse(str)
        tokens = str.split.map { |x| Integer(x) rescue nil }
        if tokens.size < 3
            return nil
        end
        val = tokens.shift
        t = TreeNode.new(val)
        parse_recursive(tokens, t)
        t
    end
    
    def self.parse_recursive(tokens, t)
        if tokens.size < 2 then
            return t
        end

        val = tokens.shift
        if val != nil then
            t.left = TreeNode.new(val)
            parse_recursive(tokens, t.left)
        end
        val = tokens.shift
        if val != nil then
            t.right = TreeNode.new(val)
            parse_recursive(tokens, t.right)
        end
    end
end

if __FILE__ == $0
    t = TreeNode.new(2)
    t.left = TreeNode.new(1)
    t.right = TreeNode.new(3)
    t.right.right = TreeNode.new(4)
    t.right.right.right = TreeNode.new(5)
    puts "t = #{t}"
    puts t.height
    puts t.balanced?
    puts TreeNode.parse("1 # 2 3 # # #")
    puts TreeNode.from_sorted_array([1,2,3,4,5,6,7,8,9])
    t.to_levels_bfs.each { |level| puts level.to_s }
    TreeNode.from_sorted_array([1,2,3,4,5,6,7,8,9]).to_levels_bfs.each { |level| puts level.to_s }
    puts t.is_bst?
    t.left.right = TreeNode.new(10)
    puts t.is_bst?
end
