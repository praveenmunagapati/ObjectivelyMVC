/*
 * ObjectivelyMVC: MVC framework for OpenGL and SDL2 in c.
 * Copyright (C) 2014 Jay Dolan <jay@jaydolan.com>
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 * claim that you wrote the original software. If you use this software
 * in a product, an acknowledgment in the product documentation would be
 * appreciated but is not required.
 *
 * 2. Altered source versions must be plainly marked as such, and must not be
 * misrepresented as being the original software.
 *
 * 3. This notice may not be removed or altered from any source distribution.
 */

#include <unistd.h>
#include <check.h>

#include <Objectively.h>

#include <ObjectivelyMVC.h>

START_TEST(selector)
{
	Selector *selector = $(alloc(Selector), initWithRule, "Panel#main .foo Control:highlighted");
	ck_assert_ptr_ne(NULL, selector);
	ck_assert_ptr_eq(_Selector(), classof(selector));
	ck_assert_int_eq(3, selector->sequences->count);

	SelectorSequence *selectorSequence;
	SimpleSelector *simpleSelector;

	// first sequence

	selectorSequence = $(selector->sequences, objectAtIndex, 0);
	ck_assert_int_eq(2, selectorSequence->simpleSelectors->count);

	simpleSelector = $(selectorSequence->simpleSelectors, objectAtIndex, 0);
	ck_assert_int_eq(SimpleSelectorTypeType, simpleSelector->type);
	ck_assert_str_eq("Panel", simpleSelector->pattern);

	simpleSelector = $(selectorSequence->simpleSelectors, objectAtIndex, 1);
	ck_assert_int_eq(SimpleSelectorTypeId, simpleSelector->type);
	ck_assert_str_eq("main", simpleSelector->pattern);

	// second sequence

	selectorSequence = $(selector->sequences, objectAtIndex, 1);
	ck_assert_int_eq(1, selectorSequence->simpleSelectors->count);

	simpleSelector = $(selectorSequence->simpleSelectors, objectAtIndex, 0);
	ck_assert_int_eq(SimpleSelectorTypeClass, simpleSelector->type);
	ck_assert_str_eq("foo", simpleSelector->pattern);

	// third sequence

	selectorSequence = $(selector->sequences, objectAtIndex, 2);
	ck_assert_int_eq(2, selectorSequence->simpleSelectors->count);

	simpleSelector = $(selectorSequence->simpleSelectors, objectAtIndex, 0);
	ck_assert_int_eq(SimpleSelectorTypeType, simpleSelector->type);
	ck_assert_str_eq("Control", simpleSelector->pattern);

	simpleSelector = $(selectorSequence->simpleSelectors, objectAtIndex, 1);
	ck_assert_int_eq(SimpleSelectorTypePseudo, simpleSelector->type);
	ck_assert_str_eq("highlighted", simpleSelector->pattern);
	
}END_TEST

int main(int argc, char **argv) {

	TCase *tcase = tcase_create("selector");
	tcase_add_test(tcase, selector);

	Suite *suite = suite_create("selector");
	suite_add_tcase(suite, tcase);

	SRunner *runner = srunner_create(suite);

	srunner_run_all(runner, CK_NORMAL);
	int failed = srunner_ntests_failed(runner);

	srunner_free(runner);

	return failed;
}
