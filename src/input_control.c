#include "input_control.h"

/*
 * verify_cipher
 *
 * Check that the input ciphertext contains values declared in the
 * project 1's specification
 *
 * INPUT:
 *  char *key_buffer: the buffer to verify, must be at least 200 characters
 *      long
 *
 *  OUTPUT:
 *      int > 1 if there was an error
 *      int = 0 if the buffer provided is correct
 */
int verify_ciphertext(char *cipher_buffer)
{
    int i;

    if (cipher_buffer == NULL)
        return 1;

    /* we will traverse the string and check whether we find
     * a null, if we don't find a null we break.
     * If we do, it better fall into the proper length.
     * We are also checking for only lowercase characters in the
     * meantime
     */
    for (i = 0; i < MAX_CIPHERLENGTH; i++) {
        if (cipher_buffer[i] == 0){

            if (i >= 50 && i <= 150)
                return 0;
            return 1;
        }

        if (islower(cipher_buffer[i]) == 0)
            return 1;
    }
    return 1;
}

/*
 * verify_keylength
 *
 * Check that the input keylength contains values declared on the project's
 * specification.
 *
 *  INPUT:
 *      int keylength: the keylength to verify
 *
 *  OUTPUT:
 *      int > 1 if there was an error
 *      int = 0 if the keylength provided fits the requirements
 */
int verify_keylength(int key)
{

    if (key < 1)
        return 1;

    if (key > 40)
        return 1;

    return 0;
}

/*
 * prompt_keylength
 *
 * Asks the user to provide a keylength in stdin.
 *
 * INPUT:
 *      A pointer to store the keylength value.
 *      input from the keyboard.
 *
 *  OUTPUT:
 *      None
 *
 *  Errors:
 *      If keylength is NULL, brace yourselved.
 */
void prompt_keylength(int *keylength)
{
    int return_value;
    int key;
    
    if (keylength == NULL)
        return;

    do{

        printf("provide a keylength: ");
        scanf("%d", &key);
        return_value = verify_keylength(key);
        if (return_value)
            printf("That's a wrong keylength!");

    }while(return_value);

    *keylength = key;

    return;
}


/*
 * prompt_ciphertext
 *
 * Asks the user to provide a ciphertext in stdin.
 *
 *  INPUT:
 *      A char pointer to store the ciphertext, it must be
 *      at least 200 characters long (50 characters allow us some slack
 *
 *  OUTPUT:
 *      through the pointer, you will get a populated key.
 *
 *  ERRORS:
 *      Do not send NULL and everything will be fine
 */
void prompt_ciphertext(char *ciphertext) 
{

    int return_value;
    size_t count; 

    do{

        printf("provide a ciphertext (%d): ", MAX_CIPHERLENGTH);
        count = scanf("%s", ciphertext);

        return_value = verify_ciphertext(ciphertext);
        if (return_value || count > MAX_CIPHERLENGTH)
            printf("That's a wrong ciphertext!");

    }while(return_value);

    return;
}
