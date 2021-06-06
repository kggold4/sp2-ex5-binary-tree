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
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <stack>
#include <string>
#include <list>

using namespace std;

namespace ariel {

    template <class T>
    class BinaryTree {

    private:

        struct Node
        {
            T data;
            Node *parent, *left, *right;

            // default constructor
            Node(const T data, Node *parent = nullptr, Node *left = nullptr, Node *right = nullptr)
                : data(data), parent(parent), left(left), right(right) {}
        };

        Node *root;

        // inner private methods
        // recursive copy of nodes
        void node_recursive_copy(Node *&other, Node*&original) {
            if(other == nullptr) { original = nullptr; }
            else {
                original = new Node(other->data);
                node_recursive_copy(other->left, original->left);
                node_recursive_copy(other->right, original->right);
            }
        }

        // return true if root is null
        bool empty() { return this->root == nullptr; }

        // searching a node by data in recursive way
        Node * find_node(Node * node, T data) {

            // not found node
            if(node == nullptr) { return nullptr; }

            // found node
            if(node->data == data) { return node;}

            Node * left = nullptr;

            // searching in left
            if(node->left != nullptr) { left = find_node(node->left, data); }

            Node * right = nullptr;

            // searching in right
            if(node->right != nullptr) { right = find_node(node->right, data); }

            Node * ans = nullptr;

            // find left
            if(left != nullptr) { ans = left; }

            // find right
            else if(right != nullptr) { ans = right; }

            // else
            return ans;
        }

        // throw a message that cannot find node
        void cannot_find_node() const { throw invalid_argument("cannot find node"); }

    public:

        enum Order {PREORDER, INORDER, POSTORDER};

        // default constructor
        BinaryTree() { this->root = nullptr; }

        // copy constructor
        BinaryTree(BinaryTree<T> &other) {
            if(other.empty()) { this->root = nullptr; }
            else { node_recursive_copy(other.root, this->root); }
        }

        // de-constructor
        ~BinaryTree() { if(!empty()) { delete root; } }

        // move constructor
        BinaryTree(BinaryTree<T> &&other) noexcept {
            this->root = other.root;
            other.root = nullptr;
        }

        // move operator
        BinaryTree &operator=(BinaryTree<T> &&other) noexcept {
            this->root = other.root;
            other.root = nullptr;
        }

        // simple = operator
        BinaryTree &operator=(BinaryTree<T> other) {
            if(this == &other) { return *this; }
            this->root = new Node(other.root->data);
            node_recursive_copy(other.root, this->root);
            return *this;
        }

        BinaryTree &add_root(const T &data) {

            // if root is not define
            if(empty()) { this->root = new Node(data); }

            // change only his data
            else { this->root->data = data; }
            return *this;
        }

        BinaryTree &add_left(const T &parent_data, const T &child_data) {

            if(empty()) { cannot_find_node(); }
            Node * node = find_node(this->root, parent_data);

            // cannot find the node
            if(node == nullptr) { cannot_find_node(); }

            // if left is null
            if(node->left == nullptr) {
                node->left = new Node(child_data);
                node->left->parent = node;

            // else
            } else { node->left->data = child_data; }
            return *this;
        }

        BinaryTree &add_right(const T &parent_data, const T &child_data) {
            if(empty()) { cannot_find_node(); }
            Node * node = find_node(this->root, parent_data);

            // cannot find the node
            if(node == nullptr) { cannot_find_node(); }

            // if left is null
            if(node->right == nullptr) {
                node->right = new Node(child_data);
                node->right->parent = node;

                // else
            } else { node->right->data = child_data; }
            return *this;
        }

        class iterator {
        private:

            list<Node *> help_list;
            Node *current_node;
            stack<Node *> st;
            Order order;

        public:

            // default constructor
            iterator(const Order order = Order::INORDER, Node *node = nullptr) : order(order), current_node(node) {
                if(this->current_node != nullptr) {

                    //preorder
                    if(this->order == Order::PREORDER) {

                        // add right
                        if(this->current_node->right != nullptr) { this->st.push(this->current_node->right); }

                        // add left
                        if(this->current_node->left != nullptr) { this->st.push(this->current_node->left); }
                    }

                    // inorder
                    else if(this->order == Order::INORDER) {
                        while(this->current_node != nullptr) {

                            // add node
                            this->st.push(this->current_node);

                            // make node be his left
                            this->current_node = this->current_node->left;
                        }
                        this->current_node = this->st.top();
                        this->st.pop();
                    }

                    // postorder
                    else {
                        while(this->current_node != nullptr || !this->st.empty()) {

                            // node exist
                            if(this->current_node != nullptr) {
                                this->st.push(this->current_node);
                                this->current_node = this->current_node->left;

                            // node is null
                            } else {
                                Node *node = this->st.top()->right;
                                if(node == nullptr) {
                                    node = this->st.top();
                                    this->st.pop();
                                    this->help_list.push_back(node);
                                    while(!this->st.empty() && node == this->st.top()->right) {
                                        node = this->st.top();
                                        this->st.pop();
                                        this->help_list.push_back(node);
                                    }
                                } else { this->current_node = node; }
                            }
                        }
                        this->current_node = this->help_list.front();
                        this->help_list.pop_front();
                    }

                }
            }

            // operator ++ int
            iterator operator++(int) {
                iterator iter = *this;
                if(this->order == Order::PREORDER) {
                    if(this->st.empty()) {
                        this->current_node = nullptr;
                        return iter;
                    }
                    this->current_node = this->st.top();
                    this->st.pop();

                    if(this->current_node->right != nullptr) { this->st.push(this->current_node->right); }
                    if(this->current_node->left != nullptr) { this->st.push(this->current_node->left); }
                } else if(this->order == Order::INORDER) {
                    if(!this->st.empty() || this->current_node->right != nullptr) {
                        this->current_node = this->current_node->right;

                        while(this->current_node != nullptr) {
                            this->st.push(this->current_node);
                            this->current_node = this->current_node->left;
                        }
                        this->current_node = this->st.top();
                        this->st.pop();
                    } else { this->current_node = nullptr; }
                } else {
                    if(!this->help_list.empty()) {
                        this->current_node = this->help_list.front();
                        this->help_list.pop_front();
                    } else { this->current_node = nullptr; }
                }
                return iter;
            }

            // operator ++
            iterator &operator++() {
                if(this->order == Order::PREORDER) {
                    if(this->st.empty()) {
                        this->current_node = nullptr;
                        return *this;
                    }
                    this->current_node = this->st.top();
                    this->st.pop();

                    if(this->current_node->right != nullptr) { this->st.push(this->current_node->right); }
                    if(this->current_node->left != nullptr) { this->st.push(this->current_node->left); }
                } else if(this->order == Order::INORDER) {
                    if(!this->st.empty() || this->current_node->right != nullptr) {
                        this->current_node = this->current_node->right;

                        while(this->current_node != nullptr) {
                            this->st.push(this->current_node);
                            this->current_node = this->current_node->left;
                        }

                        this->current_node = this->st.top();
                        this->st.pop();
                    } else { this->current_node = nullptr; }
                } else {
                    if(!this->help_list.empty()) {
                        this->current_node = this->help_list.front();
                        this->help_list.pop_front();
                    } else { this->current_node = nullptr; }
                }
                return *this;
            }

            T &operator*() const { return this->current_node->data; }
            T *operator->() const { return &(this->current_node->data); }
            bool operator==(const iterator &other) const { return this->current_node == other.current_node; }
            bool operator!=(const iterator &other) const { return this->current_node != other.current_node; }
        };

        iterator begin_preorder() { return iterator(Order::PREORDER, this->root); }
        iterator end_preorder() { return iterator(Order::PREORDER, nullptr); }
        iterator begin_inorder() { return iterator(Order::INORDER, this->root); }
        iterator end_inorder() { return iterator(Order::INORDER, nullptr); }
        iterator begin_postorder() { return iterator(Order::POSTORDER, this->root); }
        iterator end_postorder() { return iterator(Order::POSTORDER, nullptr); }
        iterator begin() { return iterator(Order::INORDER, this->root); }
        iterator end() { return iterator(Order::INORDER, nullptr); }

        friend ostream &operator<<(ostream &out, const BinaryTree &binary_tree) {
            out << "binary tree" << endl;
            return out;
        }
    };
}
