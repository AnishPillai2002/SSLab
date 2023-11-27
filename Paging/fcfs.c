#include<stdio.h>
#define P_Size 25
#define F_Size 10

//Function to calculate Page Hit & Miss

void calFault(int fsize, int psize, int page[]){

    int hit=0,miss=0;

    // initilizing the frames
    int frame[F_Size];
    for (int i = 0; i < fsize; i++){
        frame[i]=-1;
    }

    // variable to point to the frame to be modified next
    int f_pointer=0;
    
    for (int i = 0; i < psize; i++){
        int found=0;
        for (int j = 0; j < fsize; j++){
            
            if (frame[j]==page[i]){
                found=1;
                break;
            }      
        }
        
        if (found==0){
            
            frame[f_pointer]=page[i];
            f_pointer=(f_pointer+1)%fsize;
            miss++;
        }
        else{
            hit++;
        }     
    }

    printf("Page Fault = %d\n",miss);
    

    
     
        

}
    



int main(){

    int fsize,psize;
    printf("Enter the Number of Frames: ");
    scanf("%d",&fsize);

    printf("Enter the Number of Pages: ");
    scanf("%d",&psize);



    //page reference string
    int page[P_Size];
    printf("Enter the Page Reference String: ");
    for (int i = 0; i < psize; i++){
         scanf("%d",&page[i]);
    }
    
    calFault(fsize,psize,page);


}