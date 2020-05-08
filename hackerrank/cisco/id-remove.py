from heapq import heappush, heappop
def asdf(l, m):
   s = set(l)
   h = []
   for i in s:
     heappush(h, (l.count(i), i))
   while m:
     count, id = heappop(h)
     if m>count:
       s.remove(id)
       m -= count
     else:
       break
   return len(s)
