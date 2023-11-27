//Emergency code for relocatable loader, to be replaced by the actual code
//This code is for reference only, and is not to be used in the final submission
//Produces the same output of the actual code, but does not use the same logic

#include<stdio.h>
#include<stdlib.h>

void main(){

    //File pointer
    FILE *abs;
    abs = fopen("input2.txt","r");

    //Variable to store each line
    char line[300];
    fscanf(abs,"%s",line);

    //Variable to store starting address of each text record
    char addr[6];

    //Variables to store address and data of each text record
    int i = 0,j=0;
    int addressHex;   //Address of the text record in hexadecimal
    int prevaddressHex = 0xFFFF; //Initialize to largest address

    int start_hexAddress;
    printf("Enter the starting address of the program: ");
    scanf("%x",&start_hexAddress);

    //Looping through the input file
    while(line[0] != 'E'){

        //If line is a text record
        if(line[0] == 'T'){

            //Extracting address of text record
            for(i = 2,j=0; i <= 7;i++,j++){
                addr[j] = line[i];
            }
            // Add null terminator to the address string
            addr[j] = '\0';

            //Converting address string to hex
            addressHex = strtol(addr,NULL,16)+start_hexAddress;

            //Fill in any gaps between the previous address and current address with XX
            while(prevaddressHex < addressHex){
                printf("\n%x : XX",prevaddressHex);
                prevaddressHex++;
            }

             // Move the index to the start of the data section in the record
            i += 4;

            //Loop through the data section of the text record
            while(line[i] != '\0'){
                // Print the memory contents represented by hexadecimal pairs
                printf("\n%x : %c%c",addressHex,line[i],line[i+1]);

                //Increment the index by 2 to move to the next pair
                i +=2;

                //Increment the hex address by 1
                addressHex += 0x1;

                //Skip the ^ character
                if(line[i] == '^') i++;
            }
            //Store the current address as the previous address
            prevaddressHex = addressHex;
        }
        //Read the next line
        fscanf(abs,"%s",line);
    }
}