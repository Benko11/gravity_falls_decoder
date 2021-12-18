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

TEST(TestStringAddition, BasicAddition) {
	char helper[] = {'b', 'e', 'n', 'j', 'a', 'm', 'i', 'n', '\0'};

	crappy_string out, *name;
	name = &out;
	str_init(name);
	for (int i = 0; i < sizeof(helper) / sizeof(char) - 1; i++) {
		char aux[2];
		aux[0] = helper[i];
		aux[1] = '\0';
		str_add(name, aux);
	}

	ASSERT_EQ(strcmp(str_get(name), helper), 0);
	str_destroy(name);
}

TEST(TestStringAddition2, MoreAddition) {
	char *helpers[3] = {};
	helpers[0] = (char *) malloc(8 * sizeof(char));
	helpers[1] = (char *) malloc(2 * sizeof(char));
	helpers[2] = (char *) malloc(6 * sizeof(char));
	strcpy(helpers[0], "gravity");
	strcpy(helpers[1], " ");
	strcpy(helpers[2], "falls");

	char helper[] = "gravity falls";

	crappy_string out, *message;	
	message = &out;
	str_init(message);
	str_add(message, helpers[0]);
	str_add(message, helpers[1]);
	str_add(message, helpers[2]);

	ASSERT_EQ(strcmp(str_get(message), helper), 0);
	str_destroy(message);
}

TEST(TestStringAdditionAssignment, Case1) {
	char helper[] = {'b', 'e', 'n', 'j', 'a', 'm', 'i', 'n', '\0'};
	char helper2[] = {'a', 'b', 'C', '\0'};

	crappy_string a, *text;
	text = &a;
	str_init(text);
	for (int i = 0; i < sizeof(helper) / sizeof(char) - 1; i++) {
		char aux[2];
		aux[0] = helper[i];
		aux[1] = '\0';
		str_add(text, aux);
	}

	ASSERT_EQ(strcmp(str_get(text), helper), 0);
	str_assign(text, helper2);
	ASSERT_EQ(strcmp(str_get(text), helper2), 0);
	ASSERT_EQ(strlen(str_get(text)), 3);
	ASSERT_EQ(text->capacity, 4);

	str_destroy(text);
}