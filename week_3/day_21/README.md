## Day 21

Very happy with my solution. Implemented square matrix rotation and flipping functions as well as functions to split and combine matrices.

To speed up:
- Can expand rules list so that finding matches for rules is faster. (speed up increases with system size)
- As the picture increases, some blocks will be the same as others. Rather than matching and replacing these blocks multiple times, it is also possible to keep track of unique blocks and keep track of the number of times they occur to know the total number of on pixels at the end. This way the minimum number of rule lookup and piece replacement occurs. (large speed up)