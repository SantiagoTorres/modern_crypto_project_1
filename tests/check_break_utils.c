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

    ck_assert(0);

}END_TEST

// Define the suite.
Suite * input_break_utils_suite(void)
{

    Suite *s = suite_create ("buildup");
    TCase *tc_core = tcase_create ("core");


    /* add the case */
    tcase_add_test (tc_core, test_empty);
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


