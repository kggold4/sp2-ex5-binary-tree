/**
 *
 * Assignment #5
 * COURSE:   Systems Programming 2 Ariel University
 * AUTHORS:  Kfir Goldfarb
 * https://www.github.com/kggold4
 * YEAR: 2021
 *
 * */

#include <iostream>
#include <bits/stdc++.h>
#include "doctest.h"
#include "BinaryTree.hpp"

using namespace std;
using namespace ariel;

const static int NUMBER_OF_INNER_CASES = 500;


// get random int between bottom and top
int rand_int(int bottom = INT_MIN + 1, int top = INT_MAX - 1) {
    return bottom + (rand() % (top - bottom + 1));
}

TEST_CASE("Add tests") {

    BinaryTree<int> int_bt;
    int number_of_checks = 0;

    while(number_of_checks < NUMBER_OF_INNER_CASES) {
        // add root
        CHECK_NOTHROW(int_bt.add_root(rand_int()));

        // add left
//        CHECK_NOTHROW(int_bt.add_left(rand_int()));

        // add right
//        CHECK_NOTHROW(int_bt.add_right(rand_int()));
        number_of_checks++;
    }






}