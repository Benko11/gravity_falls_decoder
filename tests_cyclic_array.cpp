// Copyright 2005, Google Inc.
// All rights reserved.
#include <iostream>
#include "gtest/gtest.h"
#include <string.h>
#include "cyclic_array.h"

using namespace ::testing;

TEST(TestCyclicArray, ItemsAssignment) {
	cyclic_array out, *clock;
	clock = &out;

	char items[13];
	strcpy(items, "123456789abc");

	c_arr_init(clock, items);
	char *clock_items = c_arr_all_items(clock);
	ASSERT_EQ(strcmp(clock_items, items), 0);
	c_arr_destroy(clock);
}

TEST(TestCyclicArray, CharSeek) {
	cyclic_array out, *clock;
	clock = &out;

	char items[13];
	strcpy(items, "123456789abc");

	c_arr_init(clock, items);
	ASSERT_EQ(c_arr_at(clock, 2), '2');
	ASSERT_EQ(c_arr_at(clock, 10), 'a');
	ASSERT_EQ(c_arr_at(clock, 0), 0);
	ASSERT_NE(c_arr_at(clock, 13), '1');
	c_arr_destroy(clock);
}

TEST(TestCyclicArray, CharNumber) {
	cyclic_array out, *clock;
	clock = &out;

	char items[13];
	strcpy(items, "123456789abc");

	c_arr_init(clock, items);
	ASSERT_EQ(c_arr_number(clock, 'a'), 10);
	ASSERT_EQ(c_arr_number(clock, 'c'), 12);
	ASSERT_EQ(c_arr_number(clock, 'x'), -1);
	ASSERT_EQ(c_arr_number(clock, '1'), 1);
	c_arr_destroy(clock);
}

TEST(TestCyclicArray, MoveCharInBounds) {
	cyclic_array out, *clock;
	clock = &out;

	char items[13];
	strcpy(items, "123456789abc");

	c_arr_init(clock, items);

	ASSERT_EQ(c_arr_move(clock, '1', 2), '3');
	ASSERT_EQ(c_arr_move(clock, '4', 0), '4');
    ASSERT_EQ(c_arr_move(clock, 'c', 3), '3');
    ASSERT_EQ(c_arr_move(clock, 'c', -3), '9');
    ASSERT_EQ(c_arr_move(clock, 'c', -3), '9');
    ASSERT_EQ(c_arr_move(clock, '1', -9), '4');

	c_arr_destroy(clock);
}

TEST(TestCyclicArray, MoveCharOutsideBounds) {
	cyclic_array out, *clock;
	clock = &out;

	char items[13];
	strcpy(items, "123456789abc");

	c_arr_init(clock, items);

    ASSERT_EQ(c_arr_move(clock, 'c', 20), '8');
    ASSERT_EQ(c_arr_move(clock, 'c', 40), '4');
    ASSERT_EQ(c_arr_move(clock, 'c', 500), '8');
    ASSERT_EQ(c_arr_move(clock, 'a', 1e8), '2');
    ASSERT_EQ(c_arr_move(clock, 'c', -500), '4');

	c_arr_destroy(clock);
}

TEST(TestCyclicArray, MoveCharNaughtyBounds) {
	cyclic_array out, *clock;
	clock = &out;

	char items[13];
	strcpy(items, "123456789abc");

	c_arr_init(clock, items);

    ASSERT_EQ(c_arr_move(clock, 'x', 20), 0);
    ASSERT_EQ(c_arr_move(clock, ' ', 5), 0);
    ASSERT_EQ(c_arr_move(clock, '@', 1e5), 0);

	c_arr_destroy(clock);
}