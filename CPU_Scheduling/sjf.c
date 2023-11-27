#include <stdio.h>
#define Max 10

typedef struct {
    int pid;
    int at;
    int bt;
    int rt;
    int ct;
    int tat;
    int wt;
} Process;

void calculateTimes(Process p[], int n) {
    int currentTime = 0;
    int completed = 0;

    while (completed < n) {
        int shortestJobIndex = -1;
        int shortestBurstTime = -1;

        for (int i = 0; i < n; i++) {
            if (p[i].at <= currentTime && p[i].rt > 0) {
                if (shortestJobIndex == -1 || p[i].bt < shortestBurstTime) {
                    shortestJobIndex = i;
                    shortestBurstTime = p[i].bt;
                }
            }
        }

        if (shortestJobIndex == -1) {
            currentTime++;
            continue;
        }

        p[shortestJobIndex].ct = currentTime + p[shortestJobIndex].bt;
        p[shortestJobIndex].tat = p[shortestJobIndex].ct - p[shortestJobIndex].at;
        p[shortestJobIndex].wt = p[shortestJobIndex].tat - p[shortestJobIndex].bt;
        p[shortestJobIndex].rt = 0;
        currentTime = p[shortestJobIndex].ct;
        completed++;
    }
}


void displayResults(Process p[], int n) {
    int totalTAT = 0;
    int totalWT = 0;

    printf("PID\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t\t%d\t\t%d\n",
               p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
        totalTAT += p[i].tat;
        totalWT += p[i].wt;
    }

    float avgTAT = (float)totalTAT / n;
    float avgWT = (float)totalWT / n;

    printf("Average Turnaround Time: %.2f\n", avgTAT);
    printf("Average Waiting Time: %.2f\n", avgWT);
}

int main() {
    int n;
    printf("Enter the number of Processes: ");
    scanf("%d", &n);

    Process p[Max];

    printf("Enter arrival time and burst time for each process:\n");
    for (int i = 0; i < n; i++) {
        
        scanf("%d %d", &p[i].at,&p[i].bt);
        
        p[i].pid = i + 1;
        p[i].ct = 0;
        p[i].tat = 0;
        p[i].wt = 0;
        p[i].rt=p[i].bt;
    }

    calculateTimes(p, n);
    displayResults(p, n);

    return 0;
}