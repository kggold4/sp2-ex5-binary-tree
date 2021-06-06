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
#include <stack>

using namespace std;

namespace ariel {

    // binary tree class
    template<typename T>
    class BinaryTree {
    private:

        // Node struct
        struct Node {
            T data;
            Node *parent, *left, *right;

            // default constructor
            Node(const T data, Node *parent = nullptr, Node *left = nullptr, Node *right = nullptr)
                    : data(data), parent(parent), left(left), right(right) {}

            // copy constructor
            Node(Node &other) : data(other.data), parent(other.parent), left(other.left), right(other.right) {} {}
        };

        // tree root
        Node *root;

        // inner private methods
        void node_recursive_copy(Node *&other, Node *&original) {
            if(other == nullptr) { original = nullptr; }
            else {
                original = new Node(other);
                copy(other->left, original->left);
                copy(other->right, original->right);
            }
        }

        bool isEmpty() { return this->root == nullptr; }

    public:

        // default constructor
        BinaryTree() { this->root = nullptr; }

        // copy constructor
        BinaryTree(BinaryTree& binary_tree) {
            if(isEmpty()) { this->root = nullptr; }
            else { node_recursive_copy(binary_tree.root, this->root); }
        }

        // de-constructor
        ~BinaryTree() {}

        // move constructor
        BinaryTree(BinaryTree&& binaryTree) noexcept {
            this->root = binaryTree.root;
        }

        // move operator
        BinaryTree &operator=(BinaryTree&& binaryTree) noexcept {
            delete this->root;
            this->root = binaryTree.root;
        }

        // regular = operator
        BinaryTree &operator=(BinaryTree binaryTree) {
            if(this == &binaryTree) {
                return *this;
            }
            delete this->root;
            root = new Node(binaryTree.root);
            node_recursive_copy(binaryTree.root, this->root);
            return *this;
        }

        // add root method
        BinaryTree<T> &add_root(const T &data) {

            // if current root is null
            if(isEmpty()) { this->root = new Node(data); }

            // replace current data of root
            else { this->root->data = data; }
        }

        // add left method
        BinaryTree<T> &add_left(const T &parent_data, const T &child_data) {
            if(isEmpty()) { throw(string) "root is null"; }
            stack<Node*> st;
            Node * current_node = this->root;
            while(current_node != nullptr) {
                st.push(current_node);
                current_node = current_node->left;
            }
            while(!st.empty()) {
                current_node = st.top();
                st.pop();
                if(current_node->data == parent_data) {

                    // left node does not exist
                    if(current_node->left == nullptr) { current_node->left = new Node(child_data); }

                    // change his data (exist)
                    else { current_node->left->data = child_data; }
                    return *this;
                }
                current_node = current_node->right;
            }
            throw invalid_argument("cannot found node");
        }


        // add right method
        BinaryTree<T> &add_right(const T &parent_data, const T &child_data) {
            if(isEmpty()) { throw(string) "root is null"; }
            stack<Node*> st;
            Node * current_node = this->root;
            while(current_node != nullptr) {
                st.push(current_node);
                current_node = current_node->left;
            }
            while(!st.empty()) {
                current_node = st.top();
                st.pop();
                if(current_node->data == parent_data) {

                    // right node does not exist
                    if(current_node->right == nullptr) { current_node->right = new Node(child_data); }

                    // change his data (exist)
                    else { current_node->left->data = child_data; }
                    return *this;
                }
                current_node = current_node->right;
            }
            throw invalid_argument("cannot found node");
        }

        // output
        // using other typename symbol
        template<typename E>
        friend ostream &operator<<(ostream &out, const BinaryTree<E> &binary_tree);

        /**
         * Nested Iterators Classes
         */

        // preorder iterator
        class preorder_iterator {
        private:
            Node *current;
        public:
            preorder_iterator(Node *node = nullptr) : current(node) {}

            T &operator*() const { return this->current->data; }

            preorder_iterator &operator++() { return *this; }

            preorder_iterator operator++(int value) { return *this; }

            bool operator==(const preorder_iterator &it) const { return false; }

            bool operator!=(const preorder_iterator &it) const { return false; }

            preorder_iterator &operator=(const preorder_iterator &iterator) { return iterator; }

            T *operator->() const { return &(this->current->data); }

            int size() const { return 0; }
        };

        preorder_iterator begin_preorder() { return preorder_iterator(this->root); }

        preorder_iterator end_preorder() { return preorder_iterator(); }

        // inorder iterator
        class inorder_iterator {
        private:
            Node *current;
        public:
            inorder_iterator(Node *node = nullptr) : current(node) {}

            T &operator*() const { return this->current->data; }

            inorder_iterator &operator++() { return *this; }

            inorder_iterator operator++(int value) { return *this; }

            bool operator==(const inorder_iterator &it) const { return false; }

            bool operator!=(const inorder_iterator &it) const { return false; }

            inorder_iterator &operator=(const inorder_iterator &iterator) { return iterator; }

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
            Node *current;
        public:
            postorder_iterator(Node *node = nullptr) : current(node) {}

            T &operator*() const { return this->current->data; }

            postorder_iterator &operator++() { return *this; }

            postorder_iterator operator++(int value) { return *this; }

            bool operator==(const postorder_iterator &it) const { return false; }

            bool operator!=(const postorder_iterator &it) const { return false; }

            postorder_iterator &operator=(const postorder_iterator &iterator) { return iterator; }

            T *operator->() const { return &(this->current->data); }

            int size() const { return 0; }
        };

        postorder_iterator begin_postorder() { return postorder_iterator(this->root); }

        postorder_iterator end_postorder() { return postorder_iterator(); }

    };

    /** Implementations */

    template<typename T>
    BinaryTree<T> &BinaryTree<T>::add_root(const T &data) { return *this; }

    template<typename T>
    BinaryTree<T> &BinaryTree<T>::add_left(const T &parent_data, const T &child_data) { return *this; }

    template<typename T>
    BinaryTree<T> &BinaryTree<T>::add_right(const T &parent_data, const T &child_data) { return *this; }

    // implement out operator
    template<typename T>
    ostream &operator<<(ostream &out, const BinaryTree<T> &binary_tree) {
        out << "output test";
        return out;
    }
}
