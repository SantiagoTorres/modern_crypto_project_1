#include "polyalpha_decrypt.h"
#include "dictionary2.h"
#include "dictionary1.h"
#include "input_control.h"

int main(void)
{

    int keylength;
    char ciphertext[200];

    puts("Polyalpha decrypt 0.0");
    prompt_keylength(&keylength);
    prompt_ciphertext(ciphertext);

    return 0;
}

