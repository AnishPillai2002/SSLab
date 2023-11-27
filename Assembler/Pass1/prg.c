#include<stdio.h>
#include<string.h>
#include<stdlib.h>


void display(){

}


void main(){
    //file pointers
    FILE *in; //input file
    FILE *symtab;//symbol table
    FILE *optab;//opcode table
    FILE *fpl;//length of program
    FILE *out;//intermediate file

    //variables
    char label[30],opcode[30],operand[30]; //label, mnemonic opcode, operand
    char code[30],value[30]; //opcode table code and value

    int locctr;//location counter
    int start;//start address
    int length;//length of program
    int bytelen,size=0;//length of byte and size of program
    
    //opening files
    in = fopen("input.txt","r");
    symtab = fopen("symtab.txt","w");
    optab = fopen("optab.txt","r");
    fpl = fopen("length.txt","w");
    out = fopen("intermediate.txt","w");

    //reading first line
    fscanf(in,"%s\t%s\t%s",label,opcode,operand);

    //checking for start
    if(strcmp(opcode,"START") == 0){
        start = atoi(operand);
        locctr = start;
        //printing first line to intermediate file
        fprintf(out,"**\t%s\t%s\t%s\n",label,opcode,operand);
        //reading next line
        fscanf(in,"%s\t%s\t%s",label,opcode,operand);
    }else{
        locctr = 0;
    }

    //reading till end of input file
    while(strcmp(opcode,"END") != 0){

        //printing to intermediate file
        fprintf(out,"%d\t%s\t%s\t%s\n",locctr,label,opcode,operand);
        
        //if there is label, print to symbol table
        if(strcmp(label,"**") != 0){
            fprintf(symtab,"%s\t%d\n",label,locctr);
        }

        //searching for opcode in opcode table
        fscanf(optab,"%s\t%s",code,value);
        while(strcmp(code,"END") != 0){
            if(strcmp(opcode,code) == 0){
                locctr += 3;
                size += 3;
                break;
            }
            //if not found, read next line in  opcode table
            fscanf(optab,"%s\t%s",code,value);
        }

        //if opcode is WORD, BYTE, RESW, RESB
        if(strcmp(opcode,"WORD") == 0){
            locctr += 3;
            size += 3;
        }else if(strcmp(opcode,"BYTE") == 0){
            bytelen = strlen(operand);
            if(operand[0] == 'C' || operand[0] == 'c'){
                locctr += (bytelen - 3);
                size += (bytelen - 3);
            }else{
                locctr += (bytelen - 3)/2;
                size += (bytelen - 3)/2;
            }
        }else if(strcmp(opcode,"RESW") == 0){
            locctr += 3 * atoi(operand);
        }else if(strcmp(opcode,"RESB") == 0){
            locctr += atoi(operand);
        }

        //read next line in input file
        fscanf(in,"%s\t%s\t%s",label,opcode,operand);
    }

    //printing last line to intermediate file
    fprintf(out,"%d\t%s\t%s\t%s\n",locctr,label,opcode,operand);

    //printing length of program to length.txt
    length = locctr - start;
    printf("Length of assembly program is (in hex) : %x %x",length,size);

    //printing length of program to length.txt
    fprintf(fpl,"%x\t%x",length,size);
    fprintf(symtab,"END\t*");

    fclose(in);
    fclose(out);
    fclose(symtab);
    fclose(optab);
    fclose(fpl);
}