## Day 13

Part 2 need to be improved. Finds answer in ~25 seconds by simulating the gates step by step. This is somewhat optimized as each state starts from the end point of the last, so we don't have to simulate delays over and over, just one per step. 

Possible speed up methods are: 
    - using a triangle function to automatically calculate gate positions (small speed up?)
    - pre checking start time by using the % operator with the gate sizes (large speed up)