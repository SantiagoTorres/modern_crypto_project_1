#include "polyalpha_decrypt.h"
#include "input_control.h"
#include "break_utils.h"

int main(void)
{

    int keylength;
    char ciphertext[200];
    char *plaintext;
    time_t begin, tick;
    int i = 0;


    char *(* break_cipher[ALGORITHM_NUMBER])(int keylength, char *ciphertext) = {
        break_polyalpha_assuming,
    };


    puts("Polyalpha decrypt 0.0");
    prompt_keylength(&keylength);
    prompt_ciphertext(ciphertext);

    /* We start the main loop and take the current time */
    begin  = time(NULL);

    do{

        plaintext = break_cipher[i](keylength, ciphertext);
        tick = time(NULL);

        // we could verify here... this returned a valid plaintext
        if (plaintext) {
            puts("Found plaintext");
            printf("[*] %s", plaintext);
            break;
        }

        /* If we are running out of time */    
        printf("%d\n", (int)(tick - begin));
        if ((tick - begin) > 110)
            break;

        i++;
    }while(i < ALGORITHM_NUMBER);

    if (!plaintext)
        puts("Program is done... no plaintext found");

    else
        free(plaintext);

    return 0;
}

