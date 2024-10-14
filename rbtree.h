#pragma once
#pragma once
#include <iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <functional>
#define RED 0
#define BLACK 1

//typedef int Datatype;
template <class keytype, class Datatype>
class Tree;
template <class keytype, class Datatype>
class Node {
public:
    friend class Tree<keytype, Datatype>;
    Node<keytype, Datatype>(keytype k = 0, Datatype da = 0, int c = 1, Node* p = NULL, Node* l = NULL, Node* r = NULL) :key(k), data(da), color(c), par(p), left(l), right(r) {}
    ~Node<keytype, Datatype>() {};
    keytype& first() {
        return key;
    }
    Datatype& second() {
        return data;
    }

private:
    int color;
    keytype key;
    Datatype data;
    Node* par = NULL;
    Node* left = NULL;
    Node* right = NULL;
};
template <class keytype, class Datatype>
class Tree {
public:
    Tree<keytype, Datatype>() {
        nil = new Node<keytype, Datatype>(0, 0, BLACK);
    }
    void left_rotate(Node<keytype, Datatype>* x);
    void right_rotate(Node<keytype, Datatype>* x);
    Node<keytype, Datatype>* insert(keytype key = keytype(), Datatype data = Datatype());
    Node<keytype, Datatype>* find(Datatype tar);
    void delete_node(Node<keytype, Datatype>* tar);
    void delete_node(Datatype key);
    void insert_Balance(Node<keytype, Datatype>* t);
    void del_B_nil(Node<keytype, Datatype>* t);
    void traverse(Node<keytype, Datatype>* node, std::function<void(keytype, Datatype)> callback);
    Node<keytype, Datatype>* getroot();
    ~Tree() {};
    Datatype& operator[](const keytype& key);
private:
    Node<keytype, Datatype>* root = nil;
    Node<keytype, Datatype>* nil = NULL;
};
#include "rbtree.cpp"