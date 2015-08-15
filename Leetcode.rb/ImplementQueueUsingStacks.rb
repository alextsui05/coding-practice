class Queue
    # Initialize your data structure here.
    def initialize
        @back = []
        @front = []
    end

    # @param {Integer} x
    # @return {void}
    def push(x)
        @back.push(x)
    end

    # @return {void}
    def pop
        if @front.empty?
            while !@back.empty?
                @front.push(@back.pop)
            end
        end
        @front.pop
    end

    # @return {Integer}
    def peek
        if @front.empty?
            while !@back.empty?
                @front.push(@back.pop)
            end
        end
        @front.last
    end

    # @return {Boolean}
    def empty
        @front.size == 0 and @back.size == 0
    end
end
