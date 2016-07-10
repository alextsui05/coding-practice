#!/usr/bin/env python
import random
import heapq
import sys

class PriorityQueue(object):
    def __init__(self):
        self.pq = []
        self.seen = {}
        self.REMOVED = "X"
        self.counter = 0

    def add(self, data, priority = 0):
        if data in self.seen:
            # priorities are fixed
            #self.remove(data)
            return
        count = self.counter
        self.counter += 1
        entry = [priority, count, data]
        self.seen[data] = entry
        heapq.heappush(self.pq, entry)

    def remove(self, data):
        entry = self.seen.pop(data)
        data[-1] = self.REMOVED

    def pop(self):
        while self.pq:
            priority, count, data = heapq.heappop(self.pq)
            if data is not self.REMOVED:
                del self.seen[data]
                return data

class Solution(object):
    def kSmallestPairs(self, nums1, nums2, k):
        res = []
        if not nums1 or not nums2:
            return res

        q = PriorityQueue()
        q.add((0,0), nums1[0] + nums2[0])

        while q.pq and len(res) < k:
            i, j = q.pop()
            a, b = nums1[i], nums2[j]
            res.append((a, b))
            if a < b:
                if i + 1 < len(nums1):
                    q.add((i+1,j), nums1[i+1] + nums2[j])
                if j + 1 < len(nums2):
                    q.add((0,j+1), nums1[0] + nums2[j+1])
            #elif a > b:
            else:
                if j + 1 < len(nums2):
                    q.add((i,j+1), nums1[i] + nums2[j+1])
                if i + 1 < len(nums1):
                    q.add((i+1,0), nums1[i+1] + nums2[0])

        return res

if __name__ == '__main__':
    r = random.Random()
    a = [r.randint(0, 100) for i in xrange(10)]
    a.sort()
    b = [r.randint(0, 100) for i in xrange(10)]
    b.sort()

    s = Solution()
    res = s.kSmallestPairs(a, b, 3)
    print res
    #pq = PriorityQueue()
    #for i in xrange(10):
    #    for j in xrange(10):
    #        pq.add((i, j), a[i] + b[j])
    #while pq.pq:
    #    i, j = pq.pop()
    #    print i, j, a[i], b[j], a[i] + b[j]
