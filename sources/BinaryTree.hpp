/**
 *
 * Assignment #5
 * COURSE:   Systems Programming 2 Ariel University
 * AUTHORS:  Kfir Goldfarb
 * https://www.github.com/kggold4
 * YEAR: 2021
 *
 * */

#pragma once

#include <iostream>

using namespace std;

namespace ariel {

    // binary tree class
    template<typename T>
    class BinaryTree {
    private:

        // Node struct
        struct Node {
            T data;
            Node * parent, * left, * right;
            Node(const T data) : data(data) {}
        };

        // tree root
        Node * root;

    public:

        // default constructor
        BinaryTree<T>();

        // copy constructor
        BinaryTree<T>(BinaryTree* binary_tree);

        // de-constructor
        ~BinaryTree();

        // add root method
        BinaryTree<T>& add_root(const T &data);

        // add left method
        BinaryTree<T>& add_left(const T &parent_data, const T &child_data);

        // add right method
        BinaryTree<T>& add_right(const T &parent_data, const T &child_data);

        // output
        // using other typename symbol
        template<typename E> friend ostream& operator<<(ostream& out, const BinaryTree<E> &binary_tree);

        /**
         * Nested Iterators Classes
         */

        // preorder iterator
        class preorder_iterator {
            private:
                Node * current;
            public:
            preorder_iterator(Node * node = nullptr) : current(node) {}
            T &operator*() const { return current->data; }
            preorder_iterator& operator++() { return *this; }
            preorder_iterator operator++(int value) { return *this; }
            bool operator==(const preorder_iterator &it) const { return false; }
            bool operator!=(const preorder_iterator &it) const { return false; }
            preorder_iterator& operator=(const preorder_iterator &iterator) { return iterator; }
            T *operator->() const { T data; return data; }
            int size() const { return 0; }
        };

        preorder_iterator begin_preorder() const { return preorder_iterator(); }
        preorder_iterator end_preorder() const { return preorder_iterator(); }

        // inorder iterator
        class inorder_iterator {
        private:
            Node * current;
        public:
            inorder_iterator(Node * node = nullptr) : current(node) {}
            T &operator*() const { return current->data; }
            inorder_iterator& operator++() { return *this; }
            inorder_iterator operator++(int value) { return *this; }
            bool operator==(const inorder_iterator &it) const { return false; }
            bool operator!=(const inorder_iterator &it) const { return false; }
            inorder_iterator& operator=(const inorder_iterator &iterator) { return iterator; }
            T *operator->() const { T data; return data; }
            int size() const { return 0; }
        };

        inorder_iterator begin_inorder() const { return inorder_iterator(); }
        inorder_iterator end_inorder() const { return inorder_iterator(); }

        // postorder iterator
        class postorder_iterator {
        private:
            Node * current;
        public:
            postorder_iterator(Node * node = nullptr) : current(node) {}
            T &operator*() const { return current->data; }
            postorder_iterator& operator++() { return *this; }
            postorder_iterator operator++(int value) { return *this; }
            bool operator==(const postorder_iterator &it) const { return false; }
            bool operator!=(const postorder_iterator &it) const { return false; }
            postorder_iterator& operator=(const postorder_iterator &iterator) { return iterator; }
            T *operator->() const { T data; return data; }
            int size() const { return 0; }
        };

        postorder_iterator begin_postorder() const { return postorder_iterator(); }
        postorder_iterator end_postorder() const { return postorder_iterator(); }

    };
}
