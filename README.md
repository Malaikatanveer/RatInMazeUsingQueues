# RatInMazeUsingQueues
A C++ program that solves the maze problem. It will use a 2-D dynamic array grid (as a maze). The dimensions of array will be taken as input from the user
This is a queue based solution (Lee's algorithm). In this solution a queue of reachable squares is used. The queue has initially position of source cell empty,  and the source square/cell has a distance value of 0.  

Here is a description of the solution:
"Dequeue the cell position and examine unreached, unblocked squares adjacent to this cell. Mark them with the distance (this is 1 more than the distance value of the dequeued cell). Add position of these marked  cells in the queue. Then a cell is removed from the queue and made the new examine cell. This process is  repeated until the end pin is reached or the queue becomes empty. If destination cell is reached trace back the path till source by visiting labeled cells with value -1 of current cell."
