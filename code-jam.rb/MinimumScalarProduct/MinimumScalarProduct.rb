#!/usr/bin/env ruby
if __FILE__ == $0
    File.open(ARGV[0]) do |fp|
        t = fp.readline.to_i
        1.upto(t) { |i|
            fp.readline
            v1 = fp.readline.split.map { |x| x.to_i }.sort
            v2 = fp.readline.split.map { |x| x.to_i }.sort.reverse
            x = v1.zip(v2).map { |x, y| x * y }.reduce('+')
            puts "Case ##{i}: #{x}"
        }
    end
end
