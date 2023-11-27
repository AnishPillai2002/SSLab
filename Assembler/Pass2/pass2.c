#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//Structure for OPTAB and SYMTAB
struct {
    char opcode[20];
    char hex[20];
}optab[20];

struct {
    char symbol[20];
    char value[20];
}symtab[20];


//Function to read SYMTAB
void read_symtab(){
    //file pointer
    FILE *sym; 
    sym = fopen("symtab.txt","r");
    int i = 0;
    fscanf(sym,"%s\t%s",symtab[i].symbol,symtab[i].value);
    while(strcmp(symtab[i].symbol,"END") != 0){
        i++;
        fscanf(sym,"%s\t%s",symtab[i].symbol,symtab[i].value);
    }
    fclose(sym);
}

//Function to read OPTAB
void read_optab(){
    FILE *op;
    op = fopen("optab.txt","r");
    int i = 0;
    fscanf(op,"%s\t%s",optab[i].opcode,optab[i].hex);
    while(strcmp(optab[i].opcode,"END") != 0){
        i++;
        fscanf(op,"%s\t%s",optab[i].opcode,optab[i].hex);
    }
    fclose(op);
}


void main(){

    //Reading OPTAB and SYMTAB
    read_optab();
    read_symtab();

    //File pointers
    FILE *objcode; //Object code
    FILE *assemlist;//Assembly listing
    FILE *len;//Length of program
    FILE *interm;//Intermediate file

    //Variables
    int length; //Length of program
    int size;   //Size of program
    int addr;   //Address of instruction
    int start_addr; //Starting address of program
    int bytelen,j,k;

    //label opecode operand
    char label[20], opcode[20],operand[20];

    //Opening files
    interm = fopen("intermediate.txt","r");  //Intermediate file (input)
    objcode = fopen("objectcode.txt","w");   //Object code (output)
    assemlist = fopen("assemlist.txt","w");  //Assembly listing (output)
    len = fopen("length.txt","r");           //Length of program (input)

    //Reading length and size
    fscanf(len,"%x\t%x",&length,&size);

    //Reading first line of intermediate file
    fscanf(interm,"%s\t%s\t%s\t%s",&addr,label,opcode,operand);

    //Reading starting address
    start_addr = atoi(operand);

    //Writing to assembly listing file
    if(strcmp(opcode,"START") == 0 ){
        //Listing line
        fprintf(assemlist,"**\t**\t%s\t%s\n",opcode,operand);
        
        //Object code
        fprintf(objcode,"H^PGM   ^00%d^0000%x\n",start_addr,length);
        fprintf(objcode,"T^00%d^%x",start_addr,size);

        //Reading next line
        fscanf(interm,"%x\t%s\t%s\t%s",&addr,label,opcode,operand);
    }

    //Looping through the intermediate file
    while(strcmp(opcode,"END") != 0){

        //Checking if opcode is BYTE
        if(strcmp(opcode,"BYTE") == 0){

            fprintf(objcode,"^");
            bytelen = strlen(operand) - 1;
            fprintf(assemlist,"%x\t%s\t%s\t%s\t",addr,label,opcode,operand);
            if(operand[0] == 'C' || operand[0] == 'c'){
                for(int i = 2; i < bytelen; i++){
                    fprintf(objcode,"%x",operand[i]);
                    fprintf(assemlist,"%x",operand[i]);
                }
                fprintf(assemlist,"\n");
            }else{
                // If hex
                
                operand[bytelen] = '\0';
                fprintf(objcode,"%s",operand+2);
                fprintf(assemlist,"%s\n",operand+2);
            }
        }
        //Checking if opcode is WORD
        else if (strcmp(opcode,"WORD") == 0){
            fprintf(objcode,"^00000%x",atoi(operand));
            fprintf(assemlist,"%x\t%s\t%s\t%s\t%x\n",addr,label,opcode,operand,atoi(operand));
        }
        //Checking if opcode is RESB or RESW
        else if(strcmp(opcode,"RESB") == 0 || strcmp(opcode,"RESW") == 0){
            fprintf(assemlist,"%x\t%s\t%s\t%s\n",addr,label,opcode,operand);
        }else{
            j=k=0;
            while(strcmp(opcode,optab[j].opcode) != 0){
                j++;
            }
            while(strcmp(operand,symtab[k].symbol) != 0){
                k++;
            }
            fprintf(objcode,"^%s%s",optab[j].hex,symtab[k].value);
            fprintf(assemlist,"%x\t%s\t%s\t%s\t%s%s\n",addr,label,opcode,operand,optab[j].hex,symtab[k].value);
        }
        //Reading next line
        fscanf(interm,"%x\t%s\t%s\t%s",&addr,label,opcode,operand);
    }
    fprintf(objcode,"\nE^00%d",start_addr);
    fprintf(assemlist,"%x\t%s\t%s\t%s",addr,label,opcode,operand);

    fclose(interm);
    fclose(objcode);
    fclose(assemlist);
}