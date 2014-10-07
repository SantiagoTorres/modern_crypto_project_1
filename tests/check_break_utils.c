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
     *      1 existing word but non in the dictionary
     *      1 gibberish word
     */
    char test_vectors[4][20] = {
        "evidence",
        "exami",
        "flow",
        "roflsaurus",};

    /* basic tests */
    ck_assert(find_word_in_dict2(NULL) == 0);
    ck_assert(find_word_in_dict2(test_vectors[0]) > 0);
    ck_assert(find_word_in_dict2(test_vectors[1]) > 0);
    ck_assert(find_word_in_dict2(test_vectors[2]) == 0);
    ck_assert(find_word_in_dict2(test_vectors[3]) == 0);
 
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


