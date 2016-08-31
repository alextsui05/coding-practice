require 'set'
class Solution
    attr_accessor :dp
    def initialize(sentence, dict)
        @sentence = sentence
        @dict = dict
        @dp = [[0,0,0]]*(sentence.length + 1)
        @dp[sentence.length][0] = 0
        puts @sentence
        puts @dict.to_a.to_s
        (sentence.length-1).downto 0 do |i|
            parse(i)
        end
    end

    def extract
        words = []
        i = 0
        n = @sentence.length
        while i != n
            word = @sentence[@dp[i][1], @dp[i][2] - @dp[i][1]]
            words.push word
            i = @dp[i][2]
        end
        words
    end

    def word(s)
        puts "word = (#{s})"
        if @dict.include? s
            0
        else
            @sentence.length + 1
        end
    end

    def parse(i)
        n = @sentence.length
        cost = [n+1, 0, n]
        i.upto(n) do |k|
            (k).upto(n) do |l|
                puts "#{k}, #{l}"
                skip_score = k-i
                if k == n
                    word_score = 0
                else
                    substr = @sentence[k, (l-k)]
                    word_score = word(substr)
                end
                puts "#{skip_score} + #{word_score}"
                #cost = [cost, skip_score + word_score + @dp[l][0]].min
                new_score = skip_score + word_score + @dp[l][0]
                if cost[0] > new_score
                    cost[0] = new_score
                    cost[1] = k
                    cost[2] = l
                end
            end
        end
        @dp[i] = cost
        puts "#{i} : #{cost.to_s}"
    end
end
if __FILE__ == $0
    sentence = ARGV.shift
    dict = Set.new
    ARGV.each { |word| dict.add word }
    soln = Solution.new(sentence, dict)
    puts soln.dp.to_s
    soln = soln.extract
    puts soln.to_s
end
