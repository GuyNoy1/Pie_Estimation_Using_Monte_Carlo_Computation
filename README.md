# Task 1 from Introduction to Parallel Processing course
Topic: Embarrassingly Parallel Computations with MPI. Goal: Estimate π by Monte-Carlo computations

the algorithm - throw darts at a square with size 1 in the following way:   
   sample x & y randomly on (-1, 1),   
   if x^2 + y^2 < 1 we will mark a hit (located inside the circle),   
   pie ~ 4 * ([#hits] / [#tries]. 
   
 Added running time results and plots of speedup and efficiency. 
