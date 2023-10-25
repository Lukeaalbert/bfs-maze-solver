# maze-project
This is a simple breath-first maze solver implemented in c++. It works by exploring the maze in a breadth-first manner, 
starting from the start position (denoted with 's') and adding all of the adjacent positions to a queue, checking north, west, south, 
then east. The solver then repeatedly removes the first position from the queue and explores its adjacent positions, adding 
them to the queue if they have not already been visited. When the solver reaches the finish spot (denoted with 'f'), it backtraces and 
returned the solved maze.

The start is denoted with 's'.
The finish is denoted with 'f'.
Open spots are denoted with '.'.
"Walls," or spots that cannot be occupied, are denoted with '#'.
The found path is denoted with '*'.

The dimensions of the maze (columns, rows) must be stated on the first line of the input file, seperated by a space.
The unsolved maze in the specified format must follow.

Exp)

3 5  
.s..#  
.##.#  
..f..
