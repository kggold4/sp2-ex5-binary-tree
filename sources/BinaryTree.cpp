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
#include "BinaryTree.hpp"

using namespace std;
using namespace ariel;

namespace ariel {

    template<typename T>
    BinaryTree<T>& BinaryTree<T>::add_root(const T &data) { return *this; }

    template<typename T>
    BinaryTree<T>& BinaryTree<T>::add_left(const T &parent_data, const T &child_data) { return *this; }

    template<typename T>
    BinaryTree<T>& BinaryTree<T>::add_right(const T &parent_data, const T &child_data) { return *this; }

    // implement out operator
    template<typename T>
    ostream& operator<<(ostream& out, const BinaryTree<T> &binary_tree) {
        out << "output test";
        return out;
    }
}
