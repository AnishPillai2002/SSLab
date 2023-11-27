#include<stdio.h>

#define Max_Resources 10
#define Max_Process 10

//Function to Calculate Need Matrix
void calculateNeed(int allocation[Max_Process][Max_Resources],int max[Max_Process][Max_Resources],int need[Max_Process][Max_Resources],int n,int m){

    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            need[i][j] = max[i][j]-allocation[i][j];
        }
    }
}

//Function to Find Safe State
int isSafe(int allocation[Max_Process][Max_Resources],int need[Max_Process][Max_Resources],int available[Max_Resources],int n,int m){
    
    int i,j, count=0;
    int found;

    int Finish[Max_Process]={0};
    int Work[Max_Resources];

    //initilizing Work;
    for ( i = 0; i < m; i++){
        Work[i]=available[i];
    }
    

    while (count<n){
        
        found=0;     
        for ( i = 0; i < n; i++){
            if (Finish[i]==0){
                int canbeAllocated=1;
                for ( j = 0; j < m; j++){          
                    if (need[i][j]>Work[j]){
                        canbeAllocated=0;
                        break;
                    }      
                }

                if (canbeAllocated){
                    //updating Work
                    for ( j = 0; j < m; j++){
                        Work[j]+=allocation[i][j];
                    }

                    //updating Finish
                    Finish[i]=1;   
                    found=1;    
                    count++;
                }
            }  
        } 

        if (found==0){
            break; //resources cannot be allocated
        }
    }

    if (count<n){
        return 0; //deadlock
    }
    else{
        return 1; // no deadlock;
    }
    
     
}


//Main Function

int main(){

    int n,m;
    printf("Enter the No. of Processes: ");
    scanf("%d",&n);
    printf("Enter the No. of Resources: ");
    scanf("%d",&m);

    //Defining the Matrix
    int Allocation[Max_Process][Max_Resources];
    int Max[Max_Process][Max_Resources];
    int Need[Max_Process][Max_Resources];
    int Available[Max_Resources];

    //Reading the Allocation Matrix
    printf("Enter the Allocation Matrix:\n");
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            scanf("%d",&Allocation[i][j]);
        }
    }

    //Reading the Max Matrix
    printf("Enter the Max Matrix:\n");
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            scanf("%d",&Max[i][j]);
        }
    }

    printf("Enter the Available Vector:");
    for (int i = 0; i < m; i++){
        scanf("%d",&Available[i]);
    }
    
    //Calculating Need Matrix
    calculateNeed(Allocation,Max,Need,n,m);


    int safe=isSafe(Allocation,Max,Need,Available,n,m);

    if (safe){
        printf("\nSafe State\n");
    }
    else{
        printf("Unsafe State");
    }
}