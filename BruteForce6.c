#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>



// function to print out all the possible permutations up to length k from a given alphabet of size n
static unsigned long count=0;

int genKeys(char alphabet[], char prefix[], int n, int k)

{
    //static unsigned long count=0;
    int i,j,len=strlen(prefix);
    char newprefix[len+2];
    char inputString[] = "rrrrrr##########";
    char key [20]; // only 16, but larger to accommodate null terminating character


    if (k==0)  // could print the resultant keys here, after all calcs finished, if wished.
    {
        return 1; // returns unsuccessful
    }

    for(i=0; i<n; i++)  // loop through alphabet array (ideal place for openMPI parallisation)
    {
        //Concatenation of currentPrefix + alphabet[i] = newPrefix
        for(j=0; j<len; j++)
        {
            newprefix[j] = prefix[j];
        }
        newprefix[len] = alphabet[i];
        newprefix[len+1] = '\0';
        //printf("%d key is %s\t length of key is %d\n", count,newprefix, strlen(newprefix));

        strcpy(key, newprefix);

        // add padding to generated keys
        int q;
        for (q =strlen(key); q<16; q++)
        {
            key[q] = '#';
        }
        key[q] = '\0'; // add null terminator for printing correctly, q = 16, ie 17th element
        //  printf("%lud key with padding is %s\n", ++count, key);
        count++;



        int sameString2;
        sameString2 = strcmp(inputString, key);
        if (sameString2 == 0)
        {
            printf("Count %lu\nGenerated key \"%s\" matches the input string \"%s\"",count, key, inputString);
            printf ("\nlength of key is %d   length of input string is %d\n", strlen(key), strlen(inputString));
            return 0;
        }

        else

        {
            //genKeys(alphabet, newprefix, n, k-1); //subtracting 1 from k until = 0, then executes first if statement
//            if (k==0)
//            {
//                return 0; // returns unsuccessful
//            }


            if (genKeys(alphabet, newprefix, n, k-1) == 0)
            {
                return 0;
            }

        }

    }  //end of for loop

//genKeys(alphabet, newprefix, n, k-1);






//        else
//        {
//            if (genKeys(alphabet, newprefix, n, k-1) == 0)
//            {
//                return 0;
//            }
//            else
//            {
//                genKeys(alphabet, newprefix, n, k-1); //subtracting 1 from k until = 0, then executes first if statement
//
//            }
//        }
//
//    }


    return 1;  // needs to be 1 to go to next letter of alphabet
}


int main()
{
    int k=6;
    char alphabet[] = "abcdefghijklmnopqrstuvwxyz0123456789";
    int n = strlen(alphabet);

    printf("\n*********************************************************\n");
    printf("******************Password Cracker**********************\n");
    printf("*********************************************************\n\n");


    clock_t start = clock(); // start the timer
    printf("timer started...\n\n");

    genKeys(alphabet,"",n,k); // calls the generate keys function and tries to match input string
    // note that initial prefix is an empty string ""

    //printf("\nNow back to main!\n");
    clock_t end = clock(); // stop the timer

    //printf("\ntimer stopped\n\n");

    float time_used = (float)(end - start)/ CLOCKS_PER_SEC;
    printf("\nExecution time = %.4lf seconds\n", time_used);

    return 0;
}
