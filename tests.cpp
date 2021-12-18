// Copyright 2005, Google Inc.
// All rights reserved.
#include <iostream>
#include "gtest/gtest.h"
#include <string.h>
#include "crappy_string.h"

using namespace ::testing;


//Uloha 1.
TEST(TestsStringAssignment, SettingAndGetting) {
	char helper[9];
	strcpy(helper, "Benjamin");
	crappy_string out, *a;
	a = &out;
	str_init(a);
	str_assign(a, helper);
	ASSERT_EQ(strcmp(str_get(a), helper), 0);
	str_destroy(a);
}

TEST(TestsStringAssignment, SettingAndGettingLongerString) {
	char helper[19];
	strcpy(helper, "Benjamin Bergstrom");
	crappy_string out, *name;
	name = &out;
	str_init(name);
	str_assign(name, helper);
	ASSERT_EQ(strcmp(str_get(name), helper), 0);
	str_destroy(name);
}

TEST(TestStringAssignment, SettingAndGettingParagraph) {
	char helper[128];
	strcpy(helper, "Gravity Falls is an American mystery-comedy animated television series created by Alex Hirsch for Disney Channel and Disney XD.");
	crappy_string out, *text;
	text = &out;
	str_init(text);
	str_assign(text, helper);

	ASSERT_EQ(strlen(str_get(text)), 128 - 1);
	ASSERT_EQ(text->capacity, 128);
	ASSERT_EQ(strcmp(str_get(text), helper), 0);
	str_destroy(text);
}