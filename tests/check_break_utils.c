/* Check polyalpha decrypt core
 *
 *
 * @author  Santiago Torres
 * @date    10/03/2014
 * @license MIT
 */


#include <check.h>
#include "break_utils.h"


/* 
 * test_empty
 *
 * Verifies that input sanitation runs as expected, also provides a 
 * valid ciphertext to test the correct return value
 */
START_TEST(test_empty)
{

    ck_assert(1);

}END_TEST

/* test_find_plaintext_in_dict1
 *
 * Verifies the basic functionality of the search function in dict 1
 */
START_TEST(test_find_plaintext_in_dict1)
{
   
    /* This dictionary contains:
     *  1 correct plaintext
     *  1 subset of the correct plaintext
     *  1 incorrect plaintext by a byte in the beginning
     *  1 incorrect plaintext by an invalid punctuation character
     *  1 incorrect plaintext by a by a random byte flipped
     */
    char test_vectors[6][151] = {
    "ablethanusualonastomachfullofspaghettibologneseandtinnedpearshehadalsohadtheforesighttosuggestthattheytakeafewhoursbreakfromwearingthehorcruxwhichwash",
    "aboutonceamonthwewrotetojamesthreetimesaweeklastyearsaidginnyand",
    "zboutpeopleincloaksmrdursleycouldntbearpeoplewhodressedinbutontheedgeoftondrillsweredrivenoutofhismindbysomethingelseashesatintheusualmorninghewatchev",
    "actididconfundhimronwhispe:redtoharryastogethertheyliftedalbusstrunkandowlontothetrainionlyforgottolookinthewingmirrorandletsfaceiticanuseasupersensory",
    "adlingeredagoodhouraftertheywouldusuallyhavedepartedtheircampsitefinallyhavingentirelyrepackedthebeadedbagthreetimeshermioneseemedunabletofindanymorea",};

    /* test for null pointer first */
    ck_assert(find_plaintext_in_dict1(NULL) == 0);
    ck_assert(find_plaintext_in_dict1(test_vectors[0]) > 0);
    ck_assert(find_plaintext_in_dict1(test_vectors[1]) > 0);
    ck_assert(find_plaintext_in_dict1(test_vectors[2]) == 0);
    ck_assert(find_plaintext_in_dict1(test_vectors[3]) == 0);
    ck_assert(find_plaintext_in_dict1(test_vectors[4]) == 0);

}END_TEST


/* test_find_plaintext_in_dict2
 *
 * Verifies the basic functionality of the search plaintext function for dict2
 */
START_TEST(test_find_plaintext_in_dict2)
{
    /* This array contains:
     *  1 correct plaintext made from manually appending some words
     *  1 correct plaintext made from manually appending some words, last word is truncated
     *  1 incorrect plaintext from manually writing words not in the dictionary
     *  1 incorrect plaintext like the first one, with only one letter changed
     */
   char test_vectors[4][151] = {
        "aloofamorphousanalogueanecdoteanticipationantipathyapatheticappointmentapprovalattenuateblackout",
        "botherbucketbureaucracybuttercalibratecardinalcausticcerebralchroniccircumventaloo",
        "wafflescerealmilkyoghurtbananasbagelscoffeecookieseggshambaconorangejuice",
        "aloofamorphousanalogueanecdoteanticizationantipathyapatheticappointmentapprovalattenuateblackout",};

   ck_assert(find_plaintext_in_dict2(NULL) == 0);
   ck_assert(find_plaintext_in_dict2(test_vectors[0]) > 0 );
   ck_assert(find_plaintext_in_dict2(test_vectors[1]) > 0 );
   ck_assert(find_plaintext_in_dict2(test_vectors[2]) == 0);
   ck_assert(find_plaintext_in_dict2(test_vectors[3]) == 0);

 

}END_TEST


/* test_find_word_in_dict2
 *
 * Verifies the basic functionality of the search word function for dict2
 */
START_TEST(test_find_word_in_dict2)
{
    /* this array contains:
     *      1 correct word
     *      1 correct word subset
     *      1 correct word (the longest in the dictionary)
     *      1 existing word but non in the dictionary
     *      1 gibberish word
     */
    char test_vectors[5][20] = {
        "evidence",
        "exami",
        "reconnaissance",
        "flow",
        "roflsaurus",};

    /* basic tests */
    ck_assert(find_word_in_dict2(NULL) == 0);
    ck_assert(find_word_in_dict2(test_vectors[0]) > 0);
    ck_assert(find_word_in_dict2(test_vectors[1]) > 0);
    ck_assert(find_word_in_dict2(test_vectors[2]) > 0);
    ck_assert(find_word_in_dict2(test_vectors[3]) == 0);
    ck_assert(find_word_in_dict2(test_vectors[4]) == 0);
 
}END_TEST

/* test_verify_chunk_in_dict1
 *
 * tests for the basic functionality of the function;
 */
START_TEST(test_verify_in_dict1)
{
    /* This array contains
     *      1 Correct plaintext chunk
     *      1 the complete plaintext
     *      1 invalid plaintext chunk
     */
    char test_vectors[3][151] = {
        "logneseandtinnedpe",
        "ablethanusualonastomachfullofspaghettibologneseandtinnedpearshehadalsohadtheforesighttosuggestthattheytakeafewhoursbreakfromwearingthehorcruxwhichwash",
        "olongeze"
    };

    // check for wrong length values
    ck_assert(verify_chunk_in_dict1(NULL, 0) == 0);
    ck_assert(verify_chunk_in_dict1(test_vectors[0], -1) == 0);
    ck_assert(verify_chunk_in_dict1(test_vectors[0], 151 + 1) == 0);

    // This chunk of text doesn't belong here.
    ck_assert(verify_chunk_in_dict1(test_vectors[0], 0) == 0); 

    // verify test_vectors
    ck_assert(verify_chunk_in_dict1(test_vectors[0], 40) > 0);
    ck_assert(verify_chunk_in_dict1(test_vectors[1], 0) > 0);
    ck_assert(verify_chunk_in_dict1(test_vectors[2], 40) == 0);

}END_TEST

/* test_substract_alpha_buffers
 *
 * tests for the basic functionality of substracting buffers 
 */
START_TEST(test_substract_alpha_buffers) 
{
    /* this array contains:
     *      1 short string of 'a's to substract 1's
     *      1 short string of z's to force wrapping
     *      1 short escalating string to verify a correct tendency
     *      1 short string with non lowercase characters
     */
    char test_vectors[4][11] = {
        "aaaaaaaaaa",
        "zzzzzzzzzz",
        "bcdefghijk",
        "abcdefghi;",
    };
    char *result;
    int i;

    ck_assert(substract_alpha_buffers(NULL, test_vectors[0]) == NULL);
    ck_assert(substract_alpha_buffers(test_vectors[0], NULL) == NULL);
    ck_assert(substract_alpha_buffers(NULL, NULL) == NULL);

    result = substract_alpha_buffers(test_vectors[0], test_vectors[1]);
    ck_assert(result != NULL);
    ck_assert(strncmp(result, "aaaaaaaaaa", 10) == 0);
    free(result);

    result = substract_alpha_buffers(test_vectors[1], test_vectors[0]);
    ck_assert(result != NULL);
    ck_assert(strncmp(result, "yyyyyyyyyy", 10) == 0);
    free(result);

    result = substract_alpha_buffers(test_vectors[0], test_vectors[0]);
    ck_assert(result != NULL);
    ck_assert(strncmp(result, test_vectors[1], 10) == 0);
    free(result);

    result = substract_alpha_buffers(test_vectors[2], test_vectors[0]);
    ck_assert(result != NULL);
    for (i = 0; i < strlen(result) -1; i++)
        ck_assert(result[i] < result[i+1]);
    free(result);

    result = substract_alpha_buffers(test_vectors[3], test_vectors[0]);
    ck_assert(result == NULL);
    result = substract_alpha_buffers(test_vectors[0], test_vectors[3]);
    ck_assert(result == NULL);

}END_TEST

/* test_is_valid_trillable
 *
 * tests the trillable search function basic usage, no regrestion
 * tests are made here.
 */
START_TEST(test_is_valid_trillable)
{

    int i;

    /* this array contains five valid trillables */
    char valid_vectors[5][4] = {
        "zen",
        "aze",
        "bdo",
        "iaa",
        "omg",
    };

    /* This other array contains invalid trillables and wrong-length
     * strings
     */
    char invalid_vectors[5][10] = {
        "abcdefg",
        "aaa",
        "aa",
        "",
        "zeb",
    };


    /* We'll check for nullpointer first */
    ck_assert(is_valid_trillable(NULL) == 0);

    /* check invalid vectors */
    for (i = 0; i < 5; i++)
       ck_assert(is_valid_trillable(invalid_vectors[i]) == 0);


    /* check valid vectors */
    for (i = 0; i < 5; i++)
        ck_assert(is_valid_trillable(valid_vectors[i]) > 0);

}END_TEST

// Define the suite.
Suite * input_break_utils_suite(void)
{

    Suite *s = suite_create ("buildup");
    TCase *tc_core = tcase_create ("core");

    /* add the case */
    tcase_add_test (tc_core, test_empty);
    tcase_add_test (tc_core, test_find_plaintext_in_dict1);
    tcase_add_test (tc_core, test_find_plaintext_in_dict2);
    tcase_add_test (tc_core, test_find_word_in_dict2);
    tcase_add_test (tc_core, test_verify_in_dict1);
    tcase_add_test (tc_core, test_substract_alpha_buffers);
    tcase_add_test (tc_core, test_is_valid_trillable);
    suite_add_tcase (s, tc_core);

    return s;

}


// setup the suite runner
int main (void)
{

    int number_failed;


    Suite *s =  input_break_utils_suite();
    SRunner *sr = srunner_create (s);
    srunner_run_all (sr, CK_VERBOSE);
    number_failed = srunner_ntests_failed (sr);
    srunner_free (sr);

    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;

}


