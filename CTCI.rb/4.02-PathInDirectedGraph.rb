require 'set'
class DirectedGraph
    def initialize(str_list)
        nv = str_list[0].to_i
        @data = []
        1.upto(nv) {
            @data.push(Set.new)
        }
        1.upto(str_list.size - 1) { |i|
            nbrs = str_list[i].split.map { |x| Integer(x) }
            node = nbrs.shift
            nbrs.each { |nbr|
                @data[node].add(nbr)
            }
        }
    end

    def to_s
        res = "#{@data.size}\n"
        @data.each_with_index { |nbrs, i|
            if nbrs.size < 1
                next
            end
            res += "#{i}"
            nbrs.each { |n|
                res += " #{n}"
            }
            res += "\n"
        }
        res
    end

    def has_path?(s, t)
        q = [s]
        v = Set.new
        while ! q.empty? do
            n = q.shift
            if v.include? n then
                next
            end
            v.add(n)
            @data[n].each do |nbr|
                if v.include? nbr then
                    next
                end
                if nbr == t then
                    return true
                end
                q.push(nbr)
            end
        end
        false
    end
end

if __FILE__ == $0
    raw_data = ["4",
        "0 1",
        "1 2",
        "2 0"]
    g = DirectedGraph.new(raw_data)
    puts g
    puts g.has_path?(0, 2)
    puts g.has_path?(0, 3)
end
