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
            Node(const T data, Node * parent = nullptr, Node * left = nullptr, Node * right = nullptr)
            : data(data), parent(parent), left(left), right(right) {}
        };

        // tree root
        Node * root;

    public:

        // default constructor
        BinaryTree() { this->root = nullptr; }

        // copy constructor
        BinaryTree(BinaryTree* binary_tree);

        // de-constructor
        ~BinaryTree() {}

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
            T &operator*() const { return this->current->data; }
            preorder_iterator& operator++() { return *this; }
            preorder_iterator operator++(int value) { return *this; }
            bool operator==(const preorder_iterator &it) const { return false; }
            bool operator!=(const preorder_iterator &it) const { return false; }
            preorder_iterator& operator=(const preorder_iterator &iterator) { return iterator; }
            T *operator->() const { return &(this->current->data); }
            int size() const { return 0; }
        };

        preorder_iterator begin_preorder() { return preorder_iterator(this->root); }
        preorder_iterator end_preorder() { return preorder_iterator(); }

        // inorder iterator
        class inorder_iterator {
        private:
            Node * current;
        public:
            inorder_iterator(Node * node = nullptr) : current(node) {}
            T &operator*() const { return this->current->data; }
            inorder_iterator& operator++() { return *this; }
            inorder_iterator operator++(int value) { return *this; }
            bool operator==(const inorder_iterator &it) const { return false; }
            bool operator!=(const inorder_iterator &it) const { return false; }
            inorder_iterator& operator=(const inorder_iterator &iterator) { return iterator; }
            T *operator->() const { return &(this->current->data); }
            int size() const { return 0; }
        };

        inorder_iterator begin() { return begin_inorder(); }
        inorder_iterator end() { return end_inorder(); }
        inorder_iterator begin_inorder() { return inorder_iterator(this->root); }
        inorder_iterator end_inorder() { return inorder_iterator(); }

        // postorder iterator
        class postorder_iterator {
        private:
            Node * current;
        public:
            postorder_iterator(Node * node = nullptr) : current(node) {}
            T &operator*() const { return this->current->data; }
            postorder_iterator& operator++() { return *this; }
            postorder_iterator operator++(int value) { return *this; }
            bool operator==(const postorder_iterator &it) const { return false; }
            bool operator!=(const postorder_iterator &it) const { return false; }
            postorder_iterator& operator=(const postorder_iterator &iterator) { return iterator; }
            T *operator->() const { return &(this->current->data);}
            int size() const { return 0; }
        };

        postorder_iterator begin_postorder() { return postorder_iterator(this->root); }
        postorder_iterator end_postorder() { return postorder_iterator(); }

    };
}
