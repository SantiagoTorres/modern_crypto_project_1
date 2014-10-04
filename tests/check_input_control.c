/* Check polyalpha decrypt core
 *
 *
 * @author  Santiago Torres
 * @date    10/03/2014
 * @license MIT
 */


#include <check.h>
#include "input_control.h"


/* 
 * test_verify_ciphertext
 *
 * Verifies that input sanitation runs as expected, also provides a 
 * valid ciphertext to test the correct return value
 */
START_TEST(test_verify_ciphertext)
{

    int i;
    char test_short[] = "abcdefghijklmnopqrstuv";
    char test_long[500];
    char test_upper_bound[151];
    char test_lower_bound[51];
    char test_inbetween[101];
    char test_nonalpha[101];
    char test_nonprintable[101];
    
    for (i = 0; i < 500; i++) {
        if (i < MIN_CIPHERLENGTH)
            test_lower_bound[i] = 'a';
        if (i < MAX_CIPHERLENGTH)
            test_upper_bound[i] = 'a';
        if (i < 100) {
            test_inbetween[i] = 'a';
            test_nonalpha[i] = 'a';
            test_nonprintable[i] = 'a';
        }
        test_long[i] = 'a';

    }

    // terminate our strings properly
    test_lower_bound[50] = '\0';
    test_upper_bound[150] = '\0';
    test_inbetween[100] = '\0';
    test_nonalpha[100] = '\0';
    test_nonprintable[100] = '\0';

    // set adequate buffers
    test_nonalpha[10] = '0';
    test_nonprintable[10] = '\t';

    ck_assert(verify_ciphertext(test_short) > 0);
    ck_assert(verify_ciphertext(test_long) > 0);
    ck_assert(verify_ciphertext(test_nonalpha) > 0);
    ck_assert(verify_ciphertext(test_nonprintable) > 0);
    
    ck_assert(verify_ciphertext(test_upper_bound) == 0);
    ck_assert(verify_ciphertext(test_lower_bound) == 0);
    ck_assert(verify_ciphertext(test_inbetween) == 0);


}END_TEST


/*
 * test_verify_keylength
 *
 * Verifies that the input santiation runs as expected, also provides a
 * valid keylength to test the correct return value.
 */
START_TEST(test_verify_keylength)
{
    int test_underflow = 0;
    int test_overflow = 50;
    int test_negative = -10;
    int test_lower_bound = 1;
    int test_upper_bound = 40;
    int regular_value = (test_upper_bound + test_lower_bound) / 2;

    ck_assert(verify_keylength(test_underflow) > 0);
    ck_assert(verify_keylength(test_overflow) > 0);
    ck_assert(verify_keylength(test_negative) > 0);

    ck_assert(verify_keylength(test_lower_bound) == 0);
    ck_assert(verify_keylength(test_upper_bound) == 0);
    ck_assert(verify_keylength(regular_value) == 0);

}END_TEST


// Define the suite.
Suite * input_control_suite(void)
{

    Suite *s = suite_create ("buildup");
    TCase *tc_core = tcase_create ("core");


    /* add the case */
    tcase_add_test (tc_core, test_verify_ciphertext);
    tcase_add_test (tc_core, test_verify_keylength);
    suite_add_tcase (s, tc_core);

    return s;

}




// setup the suite runner
int main (void)
{

    int number_failed;


    Suite *s =  input_control_suite();
    SRunner *sr = srunner_create (s);
    srunner_run_all (sr, CK_VERBOSE);
    number_failed = srunner_ntests_failed (sr);
    srunner_free (sr);

    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;

}


