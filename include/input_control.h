/*
 * This file is Copyright Santiago Torres Arias <torresariass@gmail.com> 2014 
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 *
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT.  IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 */

#ifndef INPUT_CONTROL_H
#define INPUT_CONTROL_H

#include <stdio.h>
#include <strings.h>
#include <stdlib.h>
#include <ctype.h>

/* defines */
#define MIN_KEYLENGTH 1
#define MAX_KEYLENGTH 40
#define MIN_CIPHERLENGTH 51
#define MAX_CIPHERLENGTH 151

/*
 * verify_ciphertext
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
int verify_ciphertext(char *cipher_buffer);

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
int verify_keylength(int key);

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
void prompt_keylength(int *keylength);


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
void prompt_ciphertext(char *ciphertext);

#endif /* INPUT_CONTROL_H */

