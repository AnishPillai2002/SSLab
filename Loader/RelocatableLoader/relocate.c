#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to convert a hexadecimal character to a 4-bit binary string
void convHex(char c, char *str) {
    switch (c) {
        case '0': strcpy(str, "0000"); break;
        case '1': strcpy(str, "0001"); break;
        case '2': strcpy(str, "0010"); break;
        case '3': strcpy(str, "0011"); break;
        case '4': strcpy(str, "0100"); break;
        case '5': strcpy(str, "0101"); break;
        case '6': strcpy(str, "0110"); break;
        case '7': strcpy(str, "0111"); break;
        case '8': strcpy(str, "1000"); break;
        case '9': strcpy(str, "1001"); break;
        case 'A': strcpy(str, "1010"); break;
        case 'B': strcpy(str, "1011"); break;
        case 'C': strcpy(str, "1100"); break;
        case 'D': strcpy(str, "1101"); break;
        case 'E': strcpy(str, "1110"); break;
        case 'F': strcpy(str, "1111"); break;
        default: strcpy(str, ""); break; // default case for invalid input
    }
}

// Main function
void main() {

    //file pointer
    FILE *input;
    input = fopen("input.txt", "r");

    //variables
    char *tok; //A pointer to a character used for tokenizing strings.
    char line[200]; //used to store lines read from the input file.
    char bits[100]; //meant to store binary representations extracted from the input file.
    char temp[5];   //used for temporary storage of binary strings during conversion from hexadecimal.
    char objcode[7];//used to store hexadecimal strings representing modified addresses.
    
    int hexAddr;   // used to hold converted hexadecimal addresses.
    int i;         // counter variable used in loops for iteration.
    int start;     // starting address of the program entered by the user.
    int current;   // keep track of the current address while processing records.
    int bitNo = 0; // used to track the bit position while processing bit masks.

    // Read the first line from the file
    fscanf(input, "%s", line);

    // Get the starting address from the user
    printf("Enter the starting address of the program: ");
    scanf("%X", &start);

    // Continue processing lines until 'E' record is encountered
    while (line[0] != 'E') {

        // Process 'T' records
        if (line[0] == 'T') {

            
            bitNo = 0;

            // Extract starting address and load bit masks
            tok = strtok(line, "^");    // Tokenize the line using '^' delimiter
            tok = strtok(NULL, "^");    // Get the next token
            current = strtol(tok, NULL, 16);// Convert the hexadecimal token to decimal
            strtok(NULL, "^");  //Move to the next token
            tok = strtok(NULL, "^");    // Get the next token containing bit masks

            // Convert bit masks to binary and concatenate them
            for (i = 0; i < strlen(tok); i++) {
                convHex(tok[i], temp);  // Convert each hexadecimal character to binary
                strcat(bits, temp);     // Concatenate the binary strings
            }

            tok = strtok(NULL, "^");    // Get the next token

            // Process the remaining tokens
            while (tok != NULL) {
                hexAddr = strtol(tok, NULL, 16);    //Convert hexadecimal token to decimal

                // Update address based on bit masks
                if (bits[bitNo] == '1') {
                    hexAddr += start;   // Adjust the address if the corresponding bit is '1'
                }

                // Convert modified address to hexadecimal string
                sprintf(objcode, "%X", hexAddr);

                i = 0;

                // Print modified addresses and corresponding data
                while (objcode[i] != '\0') {
                    printf("%X : %c%c\n", current + start, objcode[i], objcode[i + 1]);
                    i += 2;
                    current++;
                }

                // Move to the next token and bit mask
                tok = strtok(NULL, "^");
                bitNo++;
            }

            // Reset bit masks for the next record
            strcpy(bits, "");
        }

        // Read the next line from the file
        fscanf(input, "%s", line);
        printf("\n");
    }

    // Close the file
    fclose(input);
}