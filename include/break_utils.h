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
int *verify_plaintext(char *plaintext);

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

#endif /* break_utils.h */
