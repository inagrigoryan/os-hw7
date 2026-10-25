Requirements

- GCC compiler
- Linux terminal or another environment that supports GCC

Files

- processor.c — has both scheduling algorithms and the main function
- struct.h — defines the Process structure

How to Compile

ppen a terminal in the directory containing processor.c and struct.h, then run:
1) gcc processor.c -o scheduling
2) ./scheduling


Input

- Enter the number of processes (between 1 and 100).
- For each process, enter its arrival time and burst time, separated by a space.


Output

The program displays a Gantt chart and a table containing each process's arrival time, burst time, waiting time, turnaround time, and response time for both algorithms. It also displays the average waiting time, turnaround time, and response time.

