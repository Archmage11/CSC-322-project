#include<stdio.h>
#include<string.h>
#include<ctype.h>

int power(int a, int b);
// see README for usage details

// CHAR ASCII values 32-125
int main() {

    char first = ' ', last ='~';
    int shift = 5;
    char message[100]; 
    char *command; 

    while (!strncmp(message, "exit", strlen("exit")) == 0) // while the user has not entered "exit"
    {
        fgets(message, 100, stdin); // read user input 
        command = strtok(message, "("); // figure out what comes before the '(', if it's a command

        if (strcmp(command, "encrypt") == 0)
        { // encrypt case

            strcpy(message, strtok(NULL, ")")); // get the message and cut off the ')' on the end
            for (int i = 0; message[i] != '\0'; i++)
            {
                message[i] = (message[i] - first + shift) % (last - first + 1) + first; // encrypt with char logic
            }   

            printf("%s\n", message);
        }

        else if (strcmp(command, "decrypt") == 0)
        { // decrypt case 

            strcpy(message, strtok(NULL, ")")); // get the message and cut off the ')' on the end
            for (int i = 0; message[i] != '\0'; i++) 
            {
                message[i] = (message[i] - first - first + last - shift) % (last - first) + first; // decrypt with char logic 
            }   

            printf("%s\n", message);
        }

        else if (strcmp(command, "encode") == 0)
        { // encode to binary case

            strcpy(message, strtok(NULL, ")")); // get the message and cut off the ')' on the end
            char output[800]; // max output length of 800, since I couldn't figure out how to make it scale with the message length 
            int counter = 0;

            for (int i = 0; i < strlen(message); i++)
            { // iterate through the array of chars in the message 
                int j = message[i];
                for (int k = 128; k > 0; k /= 2) // go down by powers of two from 2^7 to 2^0
                {
                    if (k <= j) // if the power goes into the char's ASCII value, add a 1
                    {
                        output[counter] = '1';
                        j -= k;
                    }  

                    else  // otherwise, add 0
                        output[counter] = '0';
                    counter++;
                }
            }

            for (int i = 0; i < counter; i++)
                printf("%c", output[i]); // print only the non-null chars in array 
            
            printf("\n");
        }
        
        else if (strcmp(command, "decode") == 0)
        { // encrypt case

            strcpy(message, strtok(NULL, ")")); // get the message and cut off the ')' on the end
            char output[100];  
            int counter = 0;
            int i; // I'm using i later to print the right number of characters 
            
            for (i = 0; i < strlen(message); i++)
            {
                counter += (message[i] / 49) * power(2, 7 - ((i + 8) % 8));
                if (i != 0 && (i + 1) % 8 == 0)
                {
                    output[i / 8] = counter;
                    counter = 0;
                }
            }
            
            for (int j = 0; j < i / 8; j++)
                printf("%c", output[j]); // print only the non-null chars in array 
            
            printf("\n");
        }

        else if (!strncmp(message, "exit", strlen("exit")) == 0) 
            printf("ERROR: invalid command\n"); // command was not encrypt, decrypt, or exit 
    } 
    return 0;
}

int power(int a, int b) 
{ // stupid dumb built-in pow function didnt work so had to make this
    int product = 1;
    for (int i = 0; i < b; i++)
        product *= a;
    return product;
}
