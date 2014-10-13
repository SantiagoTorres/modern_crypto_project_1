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
#include "trillables.h"

char * break_polyalpha_assuming(int keylength, char *ciphertext)
{

    return NULL;

}

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
char *break_polyalpha_no_stretching_dict1(int keylength, char *ciphertext)
{

    char *plaintext = NULL;
    char plaintext_buffer[D1_MINIMUM_PREFIX + 1];
    char ciphertext_buffer[D1_MINIMUM_PREFIX + 1];
    char *key;
    int i;

    if (keylength < 0 || keylength > 40)
        return NULL;

    if (ciphertext == NULL)
        return NULL;

    ciphertext_buffer[D1_MINIMUM_PREFIX] = '\0';
    plaintext_buffer[D1_MINIMUM_PREFIX] = '\0';

    do{
        /* by doing this, we obtain a piece of the key */
        strncpy(ciphertext_buffer, ciphertext, D1_MINIMUM_PREFIX);
        strncpy(plaintext_buffer, DICTIONARY1[i], D1_MINIMUM_PREFIX);
        key = substract_alpha_buffers(ciphertext_buffer, plaintext_buffer);

        /* we obtain another piece of the plaintext with our guessed key... */
        strncpy(ciphertext_buffer, ciphertext+keylength, D1_MINIMUM_PREFIX);
        plaintext = substract_alpha_buffers(ciphertext_buffer, key);

        if (verify_chunk_in_dict1(plaintext, keylength)) {
            free(plaintext);
            free(key);
            plaintext = malloc(sizeof(*ciphertext)*strlen(ciphertext) + 1);
            strncpy(plaintext, DICTIONARY1[i], D1_LONGEST_WORD + 1);
            break;
            
        } else {
            free(key);
            free(plaintext);
            plaintext = NULL;
            i++;
        }
    }while(i < D1_DICTIONARY_LENGTH);
    
    return plaintext;
}


/* break_polyalpha_nostretching_dict2_wrapper
 *
 * a thin wrapper that intializes the function with 0 values
 */
char *break_polyalpha_nostretching_dict2_wrapper(int keylength, 
        char *ciphertext)
{
    
    int offset = 0;
    int result;
    char *plaintext;

    if (ciphertext == NULL)
        return NULL;

    plaintext = malloc(sizeof(*plaintext) * (strlen(ciphertext) + 1));

    result = break_polyalpha_nostretching_dict2(ciphertext, keylength, offset,
           plaintext); 

    if (result == 0) {
        free(plaintext);
        return NULL;
    } else
        return plaintext;

}

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
        int offset, char *plaintext)
{

    int i;
    char word_buffer[D2_LONGEST_WORD+1];
    char *shift_buffer, *trillable_pt;
    char verification_buffer[201];
    size_t wordlen;

    if (offset >= keylength)
        return 1;

    for (i = 0; i < D2_DICTIONARY_LENGTH; i++) {

        /* attempt to get a portion of the key from the cipher */
        wordlen = strlen(DICTIONARY2[i]);
        strncpy(word_buffer, ciphertext + offset, wordlen);
        word_buffer[wordlen] = '\0';
        shift_buffer = substract_alpha_buffers(word_buffer, DICTIONARY2[i]);

        /* now try to decrypt with these shifts */
        strncpy(word_buffer, ciphertext + offset + keylength, wordlen);
        trillable_pt = substract_alpha_buffers(word_buffer, shift_buffer);

        if (verify_trillable_chunk(trillable_pt) == 0) {

            free(trillable_pt);
            free(shift_buffer);
            continue; 

        } else if(break_polyalpha_nostretching_dict2(ciphertext, keylength,
                        offset + wordlen, plaintext) > 0) {
           
              
            strncpy(plaintext + offset, DICTIONARY2[i], wordlen);
            strncpy(plaintext + offset + keylength, trillable_pt, wordlen);
            free(shift_buffer);
            free(trillable_pt);
            strncpy(verification_buffer, plaintext + keylength + offset, 201);

            if (verify_trillable_chunk(verification_buffer) > 0)
                return 1;

        }
    }
    return 0;
}


/* verify_plaintext
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
int verify_plaintext(char *plaintext)
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
    int i,j, offset;
    
    if (plaintext == NULL)
        return 0;

    plaintext_length = strlen(plaintext);

    if (plaintext_length < 1)
        return 0;

    offset = plaintext[0] - 'a';
    if (offset == -1)
        return 0;


    for (i = D1_ALPHA_INDEX[offset]; i < D1_ALPHA_INDEX_END[offset]; i++) {
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
    int i, offset;
    int j;

    if (plaintext == NULL)
        return 0;

    wordlength = strlen(plaintext);
    

    if (wordlength < 1)
        return 0;
    
    offset = plaintext[0] - 'a';
    
    if (offset == -1)
        return 0;
    
    for (i = D2_ALPHA_INDEX[offset]; i < D2_ALPHA_INDEX[offset+1]; i++) {
        for (j = 0; j < wordlength; j++) {
            if (DICTIONARY2[i][j] != plaintext[j])
                break;
            else if (j == wordlength - 1)
                return 1;
        }
    }

    return 0;

}


/* verify_chunk_in_dict1
 *
 * Given a middle piece of a proposed ciphertext, verify if such piece
 * could belong to a valid ciphertext. 
 *  
 *  INPUT:
 *      char * proposed_cipher: The proposed cipher
 *      int offest:             The offset of this chunk in the original text
 *
 *  OUTPUT:
 *      int > 1: if this could belong to dictionary 1
 *      int == 0: if this cannot belong to dictionary 1
 */
int verify_chunk_in_dict1(char *proposed_cipher, int offset)
{

    size_t chunk_length;
    int i;

    if (proposed_cipher == NULL)
        return 0;

    chunk_length = strlen(proposed_cipher);
    
    if (offset < 0)
        return 0;

    if (offset + chunk_length > D1_LONGEST_WORD)
        return 0;
   
    for (i = 0; i < D1_DICTIONARY_LENGTH; i++) {
        if (strncmp(DICTIONARY1[i]+offset, proposed_cipher, chunk_length) == 0)
                return 1;

    }

    return 0;

}


/* add_alpha_buffers
 *
 * As substract, but adds instead
 *  
 *  INPUT:
 *      char * buffer1: the buffer to add to
 *      char * buffer2: the buffer to add
 *
 *  OUTPUT:
 *      char * the resulting buffer or NULL if there was an error
 */
char *add_alpha_buffers(char *buffer1, char *buffer2)
{
    
    char *result;
    char rollover = 'z' - 'a' + 1;
    char temp;
    int i;

    if (buffer1 == NULL || buffer2 == NULL)
        return NULL;
   
    if (strlen(buffer1) != strlen(buffer2))
       return NULL;

    result = malloc(sizeof(*result) * (strlen(buffer1)+1));
    if (result == NULL)
        return NULL;

    for (i = 0; i < strlen(buffer1); i++) {

        if (!islower(buffer1[i]) || !islower(buffer2[i])){
            free(result);
            return NULL; 
        }
        // this is a constant that "floors" the actual offset (z becomes 26, not hundreds);
        temp = buffer2[i] - 'a' + 1;
        result[i] = buffer1[i] + temp;
        if (!islower(result[i]))
            result[i] -= rollover;
    }    

    result[i] = '\0';

    return result;
}



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
char *substract_alpha_buffers(char *buffer1, char *buffer2)
{
    
    char *result;
    char rollover = 'z' - 'a' + 1;
    char temp;
    int i;

    if (buffer1 == NULL || buffer2 == NULL)
        return NULL;
   
    if (strlen(buffer1) != strlen(buffer2))
       return NULL;

    result = malloc(sizeof(*result) * (strlen(buffer1)+1));
    if (result == NULL)
        return NULL;

    for (i = 0; i < strlen(buffer1); i++) {

        if (!islower(buffer1[i]) || !islower(buffer2[i])){
            free(result);
            return NULL; 
        }
        // this is a constant that "floors" the actual offset (z becomes 26, not hundreds);
        temp = buffer2[i] - 'a' + 1;
        result[i] = buffer1[i] - temp;
        if (!islower(result[i]))
            result[i] += rollover;
    }    

    result[i] = '\0';

    return result;
}


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
int is_valid_trillable(char *trillable)
{

    int i;
    int offset;

    if (trillable == NULL)
        return 0;

    if (strlen(trillable) != 3)
        return 0;

    offset = trillable[0] - 'a';

    /* the offset table reports that there are no trillables
     * with this letter (this is for the j value actually
     */
    if (TRILLABLE_OFFSETS[offset] == -1)
        return 0;

    for (i = TRILLABLE_OFFSETS[offset]; i <= TRILLABLE_OFFSETS_END[offset]; i++)
        if (trillable[1] == TRILLABLES[i][1] && trillable[2] == TRILLABLES[i][2])
           return 1;

    return 0;
}

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
int verify_trillable_chunk(char *chunk) 
{

    size_t length;
    char trillable[4];
    int i;

    if (chunk == NULL)
        return 0;

    length = strlen(chunk);

    if (length < 3)
        return 0;
    // we traverse to length -2 because trillables are length 3...
    trillable[3] = '\0';
    for (i = 0; i < length -2; i++){
        trillable[0] = chunk[i];
        trillable[1] = chunk[i+1];
        trillable[2] = chunk[i+2];
        if(is_valid_trillable(trillable) == 0)
            return 0;
    }
    return 1;
}



