#include <stdio.h>
#include <stdlib.h>
#include "struct.h"

struct Process proc_cr (int pid, int at, int bt, int wt, int tat, int rt){
        struct Process new_p;

        new_p.pid = pid;
        new_p.arrival_time = at;
        new_p.burst_time = bt;
        new_p.waiting_time = wt;
        new_p.turnaround_time = tat;
        new_p.response_time =rt;

        return new_p;
}

// simple bubble sort sicne the array has maximum 100 elements
void sort_arrival(struct Process p[], int n){
        for (int i = 0; i < n-1; i++){
                for (int j = 0; j < n-1 - i; j++){
                        if (p[j].arrival_time > p[j+1].arrival_time) {
                                struct Process tmp = p[j];
                                p[j] = p[j+1];
                                p[j+1] = tmp;
                        }
                }
        }
}

void print_table(struct Process p[], int order[], int n){
        printf("PID     AT     BT     WT     TAT    RT\n");
        for (int i = 0; i < n; i++){
                int curr = order[i];
                printf("  %-7d%-7d%-7d%-7d%-7d%d\n",p[curr].pid, p[curr].arrival_time, p[curr].burst_time, p[curr].waiting_time, p[curr].turnaround_time, p[curr].response_time);
        }
}

void fcfs(struct Process p[], int n){
        sort_arrival(p, n);

        int curr_time = 0;

        int order[100];

        // for later average claculations
        int total_wt = 0;
        int total_tat = 0;
        int total_rt = 0;

        printf("Gangtt Chart: ");
        for (int i = 0; i < n; i++){
                if (curr_time < p[i].arrival_time) {
                        curr_time = p[i].arrival_time;
                }
                order[i] = i;

                p[i].waiting_time = curr_time - p[i].arrival_time;
                p[i].response_time = p[i].waiting_time; // same for fcfs
                curr_time += p[i].burst_time;
                p[i].turnaround_time = curr_time - p[i].arrival_time;
                printf("|   P%d   ", p[i].pid);

                total_wt+=p[i].waiting_time;
                total_tat+=p[i].turnaround_time;
                total_rt += p[i].response_time;
        }

        printf("|\n");
	print_table(p, order, n);

	printf("\naverage waiting time: %.2f\n", (float) total_wt/n);
	printf("average turnaround time: %.2f\n", (float) total_tat/n);
	printf("average response time: %.2f\n", (float) total_rt/n);
}


void sjf (struct Process p[], int n){
	sort_arrival(p, n);

	int curr_time = 0;
	// need an array to keep track of the executed processes, since they will not necessarily be in arrival order
	int executed[100] = {0}; //0 means not executes, 1 means executes
	int order[100];

	int completed = 0;

	int total_wt = 0;
	int total_tat = 0;
	int total_rt = 0;

	printf("Gantt Chart: ");
	// run until everyone is executed
	while (completed < n){
		int best = -1; // shortest available process
		
		for( int i = 0; i < n; i++){
			if (p[i].arrival_time > curr_time)
				break;

			if (executed[i] == 1)
				continue;

			if (best == -1)
				best = i;

			else if (p[i].burst_time < p[best].burst_time)
				best = i;

			else if (p[i].burst_time == p[best].burst_time && p[i].arrival_time < p[best].arrival_time)
				best = i;
		}

		if (best == -1){

			int next_arrival = -1;
			for (int i = 0; i < n; i++){
				if (executed[i] == 0){
					if (next_arrival == -1 || p[i].arrival_time < next_arrival) {
						next_arrival = p[i].arrival_time;

					}
				}

			}
			curr_time = next_arrival;
			continue;
		}
		
		order[completed] = best;
		p[best].waiting_time = curr_time - p[best].arrival_time;
		p[best].response_time = p[best].waiting_time;
		curr_time += p[best].burst_time;
		p[best].turnaround_time = curr_time - p[best].arrival_time;
		executed[best] = 1;
		completed++;
		printf("|   P%d   ", p[best].pid);
		
		total_wt += p[best].waiting_time;
		total_tat += p[best].turnaround_time;
		total_rt += p[best].response_time;

	}

	printf("|\n");
	print_table(p, order, n);
	printf("\naverage waiting time: %.2f\n", (float)total_wt / n);
	printf("average turnaround time: %.2f\n", (float)total_tat / n);
	printf("average response time: %.2f\n", (float)total_rt / n);
}

int main(){
        int n;
        printf("Enter number of processes: ");
        scanf("%d", &n);

        // limit the input from 1 to 100
        if (n <= 0 || n > 100) {
                printf("invalid number of processes.\n");
                exit(1);
        }

        struct Process processes[100];

        for (int i = 0; i < n; i++){
                int at, bt;
                printf("Enter arrival time and burst time for p%d: ", i+1);
                scanf("%d %d", &at, &bt);
                if (at < 0 || bt <= 0){
                        printf("invalid arrival or burst time.\n");
                      	exit(1);
                }

                processes[i] = proc_cr(i+1, at, bt, 0, 0, 0);
        }
	
	printf("\nFCFS\n");
        fcfs(processes, n);
	printf("\nSJF\n");
	sjf(processes,n);
        return 0;
}
