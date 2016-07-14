# The guess API is already defined for you.
# @param num, your guess
# @return -1 if my number is lower, 1 if my number is higher, otherwise return 0
# def guess(num):
class Solution(object):
    def guessNumber(self, n):
        """
        :type n: int
        :rtype: int
        """
        lo, hi = 0, n
        while lo < hi:
            """
            These expressions are equivalent, but in a language that doesn't
            automatically promote to big ints like python, you might overflow
            when, say, both hi and lo are integers greater than half the max
            value of an integer
            """
            #m = (lo + hi)/2
            m = lo + (hi - lo)/2

            feedback = guess(m+1)

            if feedback == 0:
                return m+1
            elif feedback < 0:
                hi = m
            else:
                lo = m+1

        """
        There's a style of binary search where you do one comparison
        per iteration that is used to find the element with the minimum
        index that fits the criterion. It doesn't really benefit here
        because all the elements are unique and so we should return as soon
        as we find it. That being said, here's how it works.
        """
        #    if feedback <= 0:
        #        hi = m
        #    else
        #        lo = m+1
        #return lo+1

