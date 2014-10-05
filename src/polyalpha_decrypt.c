#include "polyalpha_decrypt.h"
#include "dictionary2.h"
#include "dictionary1.h"
#include "input_control.h"
#include "break_utils.h"

char *(* break_cipher[1])(int keylength, char *ciphertext) = {
    break_polyalpha_assuming,
    };

int main(void)
{

    int keylength;
    char ciphertext[200];


    puts("Polyalpha decrypt 0.0");
    break_cipher[0](NULL, NULL);
    prompt_keylength(&keylength);
    prompt_ciphertext(ciphertext);

    return 0;
}

