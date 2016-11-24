require 'test/unit'

def alpha3(s)
    res = s.each_byte.map { |ch|
        (ch - 96) % 10
    }.join
    if res[0].to_i % 2 == 0
        res.reverse!
    end
    /^(0+)?(.*)$/.match(res) do |m|
        if ! m[1]
            res
        elsif m[2] == ""
            "0"
        else
            m[2]
        end
    end
end

if __FILE__ == $0
class Alpha3Test < Test::Unit::TestCase
    def test_alpha3
        assert_equal alpha3('abc'), '123'
        assert_equal alpha3('abd'), '124'
        assert_equal alpha3('bcd'), '432'
        assert_equal alpha3('cde'), '345'
        assert_equal alpha3('hij'), '98'
        assert_equal alpha3('zfr'), '866'
        assert_equal alpha3('jtj'), '0'
        assert_equal alpha3('Longer string!!!'), '7777498096857450'
    end
end
end
