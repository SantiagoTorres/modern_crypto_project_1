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

#ifndef BREAK_UTILS_H 
#define BREAK_UTILS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* this is an empty break function stub */
char * break_polyalpha_assuming(int keylength, char *ciphertext);


/* break_polyalpha_no_stretching_dict1
 *
 * This is the simplest cracking mechanism, it will attempt to crack a
 * ciphertext that was created from dict 1 by exploiting known-plaintext
 * attacks and the periodicity of polyalphabetic ciphers
 *
 *  INPUT:
 *      int keylength: the provided length of the key
 *      char *ciphertext: the ciphertext to decrypt
 *
 *  OUTPUT:
 *      char *plaintext: A proposed plaintext or NULL if the plaintext seems 
 *      to be unrecoverable. Proper verification should be attempted on the 
 *      created plaintext. 
 */
char *break_polyalpha_no_stretching_dict1(int keylength, char *ciphertext);


/* break_polyalpha_nostretching_dict2_wrapper
 *
 * a thin wrapper that intializes the function with 0 values
 */
char *break_polyalpha_nostretching_dict2_wrapper(int keylength, 
        char *ciphertext);


/* break_polyalpha_nostretching_dict2
 *
 * attempts to break a polyalphabetic cipher in which the key
 * is periodic in t and attempts doing so by using the known-
 * plaintext of dictionary2
 *
 *  INPUT:
 *      char *ciphertext: the cipher to break
 *      int keylength: t, aka. the length of the key.
 *      int offset: which is the current chunk of ciphertext we are attempting 
 *                  to break
 *      char *plaintext: a buffer in which we will store the resulting plaintext
 *
 *  OUTPUT:
 *      int = 0 if the current chunk couldn't be broken the result buffer will
 *              remain untouched
 *      int > 0 if the current chunk was decrypted, the result buffer is full
 */
int break_polyalpha_nostretching_dict2(char *ciphertext, int keylength, 
        int offset, char *plaintext);


/*
 * verify_plaintext
 *
 * Checks if the input plaintext exists in dictionary1 or if it could be 
 * derived from the words contained in dictionary 2
 *
 *  INPUT:
 *      char * plaintext: The plaintext for verify.
 *
 *  OUTPUT:
 *      int > 1 the provided plaintext was found
 *      int = 0 if the provided plaintext isn't valid, or if the
 *              argument contains NULL.
 */
int verify_plaintext(char *plaintext);

/*
 * find_plaintext_in_dict1
 *
 * Checks if the input plaintext exists in dictionary1.
 *
 *  INPUT:
 *      char * plaintext: The plaintext for verify.
 *
 *  OUTPUT:
 *      int > 1 the provided plaintext was found
 *      int = 0 if the provided plaintext isn't in dict 1
 */
int find_plaintext_in_dict1(char *plaintext);


/* find_plaintext_in_dict2
 *
 * Checks if the input plaintext exists as a combination of words in dictionary 2
 * The last word could be truncated as per request of the professor.
 *
 *  INPUT:
 *      char * plaintext: the plaintext to search in.
 *
 *  OUTPUT:
 *      int > 1 the provided plaintext is found
 *      int = 0 if the provided plaintext isn't derivable from dict 2
 */
int find_plaintext_in_dict2(char *plaintext);

/* find_word_in_dictionary_2
 *
 * Checksd if the provided word (NULL terminated) exists in dictionary 2.
 *
 *  INPUT:
 *      char * a word to search
 *
 *  OUTPUT:
 *      int > 1 if the provided word exists
 *      int = 0 if the provided word doesn't or the input was NULL
 */
int find_word_in_dict2(char *plaintext);

/* substract_alpha_buffers
 *
 * Given two strings, create an alphabetic string by substracting one from
 * the other. This wraps letters so only alphabetic characters result from it
 *  
 *  INPUT:
 *      char * buffer1: the buffer to be substracted from
 *      char * buffer2: the buffer to substract
 *
 *  OUTPUT:
 *      char * the resulting/substracted buffer or NULL if there was an error
 */
char *substract_alpha_buffers(char *buffer1, char *buffer2);


/* is_valid_trillable
 *
 * Given a trillable, verify its existence inside the 
 * trilalble dictionary
 *
 *  INPUT:
 *      char *trillable
 *
 *  OUTPUT:
 *      int > 0 if the trillable is in the dictionary
 *      int = 0 if the trillable isn't
 */
int is_valid_trillable(char *trillable);


/* verify_trillable_chunk 
 *
 * given a piece of plaintext, verify that all of the
 * trillables in it belong to the dictionary
 *
 *  INPUT:
 *      char *chunk
 *
 *  OUTPUT
 *      int > 0 is the chunk only contains valid trillables
 *      int = 0 if one or more trillables don't belong
 */
int verify_trillable_chunk(char *chunk);


#endif /* break_utils.h */
