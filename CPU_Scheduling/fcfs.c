#include <stdio.h>
#define Max_Process 10
//process structure
typedef struct{
    int pid;
    int at;
    int bt;
    int ct;
    int wt;
    int tat;
} process;

int main()
{
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    //array to store processes
    process process_array[Max_Process];

    printf("Enter arrival time and burst time for each process(AT BT):\n");
    for (int i = 0; i < n; i++){
        process_array[i].pid = i + 1;
        scanf("%d %d", &process_array[i].at, &process_array[i].bt);

        //initilizing wt ct of the processes
        process_array[i].wt = 0;
        process_array[i].ct = 0;
    }

    
    float total_wt = 0, total_tat = 0;
    int current_time = 0;


    // Sort the processes based on arrival time (FCFS)
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (process_array[j].at > process_array[j + 1].at)
            {
                process temp = process_array[j];
                process_array[j] = process_array[j + 1];
                process_array[j + 1] = temp;
            }
        }
    }

    // Calculating ct tat wt total_wt total_tat 
    for (int i = 0; i < n; i++){   
        //if next process comes after a delay
        if (current_time < process_array[i].at){
            current_time = process_array[i].at;
        }
            

        process_array[i].ct = current_time + process_array[i].bt;
        process_array[i].tat = process_array[i].ct - process_array[i].at;
        process_array[i].wt = process_array[i].tat - process_array[i].bt;

        total_wt += process_array[i].wt;
        total_tat += process_array[i].tat;

        current_time = process_array[i].ct;
    }

    float avg_tat = total_tat / n;
    float avg_wt = total_wt / n;

    //printing the details
    printf("\nPID\tArrival\tBurst\tCompletion\tTurnaround\tWait\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\t%d\t%d\t\t%d\t\t%d\n", process_array[i].pid, process_array[i].at, process_array[i].bt, process_array[i].ct, process_array[i].tat, process_array[i].wt);
    }

    printf("Average Turnaround Time: %0.2f\n", avg_tat);
    printf("Average Waiting Time: %0.2f\n", avg_wt);

    return 0;
}