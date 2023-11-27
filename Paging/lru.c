#include <stdio.h>

int main(){

    int numPage, numFrame, pageRequests[20],pageFrames[20],pageFaults=0,k=0,currentIndex, leastUsed[20],sortedLU[20];
    
    printf("Enter the number of frames: ");
    scanf("%d", &numFrame);
    printf("Enter the number of pages: ");
    scanf("%d", &numPage);

    
    printf("Enter the reference string: ");
    for (int i = 0; i < numPage; i++){
        scanf("%d", &pageRequests[i]);
    }

    //initilizing
    pageFrames[k]=pageRequests[k];
    k++;
    pageFaults++;

    //main loop
    for (int i = 1; i < numPage; i++){
        
        currentIndex=0;
        for (int j= 0; j < numFrame; j++){
            
            if (pageFrames[j]!=pageRequests[i]){
                currentIndex++;
            }   
        }

        //pageFault occurs
        if (currentIndex==numFrame){
            
            pageFaults++;

            if (k<numFrame){
                pageFrames[k]=pageRequests[k];
                k++;
            }
            else{

                for (int r = 0; r < numFrame; r++){
                    leastUsed[r]=0;
                    for (int j = i-1; j >=0; j--){
                        
                        if (pageFrames[r]!=pageRequests[j]){
                            leastUsed[r]++;
                        }
                        else{
                            break;
                        }
                    }                    
                }

                // creating new 
                for (int j = 0; j < numFrame; j++){
                    sortedLU[j]=leastUsed[j];
                }

                //sorting
                for (int r = 0; r < numFrame; r++){
                    for (int j = r; j < numFrame; j++){
                        
                        if (sortedLU[r]<sortedLU[j]){
                            int temp=sortedLU[j];
                            sortedLU[j]=sortedLU[r];
                            sortedLU[r]=temp;
                        }
                    }
                }

                // replacing
                for (int j = 0; j < numFrame; j++){
                    
                    if (leastUsed[j]==sortedLU[0]){
                        pageFrames[j]=pageRequests[i];
                    }         
                }
                       
            }
            
        }
        
    } 
    printf("Page Fault= %d \n",pageFaults);
    return 0;
}