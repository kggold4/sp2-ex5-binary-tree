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

namespace ariel {

    // binary tree class
    template<typename T>
    class BinaryTree {
    private:

        // nested node class
        template<typename T>
        class Node {

        private:
            T data;
            Node *left, right, parent;

        public:
            Node(T data) : data(data) {
                this->parent = this->left = this->right = nullptr;
            }

            explicit Node(T data, Node *parent) : data(data), parent(parent) {
                this->left = this->right = nullptr;
            }

            // getters
            T get_data() const { return this->data; }

            Node *get_left() const { return this->left; }

            Node *get_right() const { return this->right; }

            Node *get_parent() const { return this->parent; }

            // setters
            void set_data(const T data) { this->data = data; }

            void set_left() const { return this->left; }

            void set_right() const { return this->right; }

            void set_parent() const { return this->parent; }
        };

    public:

        // default constructor
        BinaryTree<T>();

        // copy constructor
        BinaryTree<T>(BinaryTree* binary_tree);

        // de-constructor
        ~BinaryTree();

        // add root method
        BinaryTree<T>& add_root(T data);

        // add left method
        BinaryTree<T>& add_left(T parent_data, T child_data);

        // add right method
        BinaryTree<T>& add_right(T parent_data, T child_data);

        // output
        friend ostream& operator<<(ostream& out, const BinaryTree<T>& binary_tree);
    };
}
