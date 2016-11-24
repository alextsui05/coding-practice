def bitWork(instructions)
    res = instructions.each_byte.reduce(:+)
    i = 0
    loop do
        break unless i < instructions.size
        i, res = process_instruction(instructions, i, res)
    end
    res = (res & (~(1 << instructions.size))) |
        (~res & (1 << instructions.size))
    res 
end

def parse_value(str, i)
    j = i
    loop do
        break unless j < str.size &&
            str[j] =~ /[[:digit:]]/
        j = j + 1
    end
    [j, str[i, j-i].to_i]
end

def process_instruction(str, i, res)
    if str[i] =~ /[[:digit:]]/
        j = i
        loop do
            break unless j < str.size &&
                str[j] =~ /[[:digit:]]/
            j = j + 1
        end
        return [j, res]
    end
    
    case str[i]
        when '&'
            i, val = parse_value(str, i + 1)
            res &= val
        when '|'
            i, val = parse_value(str, i + 1)
            res |= val
        when '^'
            i, val = parse_value(str, i + 1)
            res ^= val
        when '<'
            i, val = parse_value(str, i + 2)
            res <<= val
        when '>'
            i, val = parse_value(str, i + 2)
            res >>= val
        when 'S'
            i, val = parse_value(str, i + 2)
            res |= (1 << val)
        when 'C'
            i, val = parse_value(str, i + 2)
            res &= (~(1 << val))
    end
    
    [i, res]
end
