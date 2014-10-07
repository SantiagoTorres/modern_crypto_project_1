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
#include "break_utils.h"
#include "dictionary1.h"
#include "dictionary2.h"

char * break_polyalpha_assuming(int keylength, char *ciphertext)
{

    return NULL;

}



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
int *verify_plaintext(char *plaintext)
{
    int result;

    result = find_plaintext_in_dict1(plaintext);
    if (!result)
        result += find_plaintext_in_dict2(plaintext);

    return result;
}

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
int find_plaintext_in_dict1(char *plaintext) 
{

    size_t plaintext_length;
    int i,j;
    
    if (plaintext == NULL)
        return 0;

    plaintext_length = strlen(plaintext);

    if (plaintext_length < 1)
        return 0;

    for (i = 0; i < D1_DICTIONARY_LENGTH; i++) {
        for (j = 0; j < D1_LONGEST_WORD; j++) {

            if (j == plaintext_length)
                return 1;

            if (DICTIONARY1[i][j] != plaintext[j]) 
                break;


        } 
    }
    return 0;

}


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
int find_plaintext_in_dict2(char *plaintext)
{

    int i;
    size_t plaintext_length;
    char word_buffer[D2_LONGEST_WORD];

    if (plaintext == NULL)
        return 0;

    plaintext_length = strlen(plaintext);

    if (plaintext_length == 0)
        return 1;

    if (plaintext_length < D2_SHORTEST_WORD)
        return find_word_in_dict2(plaintext);

    for (i = D2_LONGEST_WORD; i > D2_SHORTEST_WORD; i--) {

        strncpy(word_buffer, plaintext, i);
        word_buffer[i] = '\0';

        /* This is an oversimplification since there are no words that are prefix
         * of other words in the dictionary and it allows for a greedy algorithm
         */
        if (find_word_in_dict2(word_buffer)) {
            return find_plaintext_in_dict2(plaintext + i);
        }
    }
    return 0;
}

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
int find_word_in_dict2(char *plaintext)
{

    size_t wordlength;
    int i;

    if (plaintext == NULL)
        return 0;

    wordlength = strlen(plaintext);

    if (wordlength < 1)
        return 0;

    for (i = 0; i < D2_DICTIONARY_LENGTH; i++) {
        if (strncmp(DICTIONARY2[i], plaintext, wordlength) == 0)
                return 1; 
    }
    return 0;

}
