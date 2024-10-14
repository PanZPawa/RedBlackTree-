#pragma once
#include "rbtree.h"


template <class keytype, class Datatype>
Node<keytype, Datatype>* Tree<keytype, Datatype>::getroot() {
    return root;
}

template <class keytype, class Datatype>
void Tree<keytype, Datatype>::left_rotate(Node<keytype, Datatype>* x) {
    Node<keytype, Datatype>* y = x->right;
    x->right = y->left;
    if (x->right != nil)
        x->right->par = x;
    y->par = x->par;
    if (x == root) {
        root = y;
    }
    else {
        if (x == x->par->right) {
            x->par->right = y;
        }
        else {
            x->par->left = y;
        }
    }
    y->left = x;
    x->par = y;
}

template <class keytype, class Datatype>
void Tree<keytype, Datatype>::right_rotate(Node<keytype, Datatype>* x) {
    Node<keytype, Datatype>* y = x->left;
    x->left = y->right;
    if (x->left != nil) x->right->par = x;
    y->par = x->par;
    if (x == root) {
        root = y;
    }
    else {
        if (x == x->par->left) {
            x->par->left = y;
        }
        else {
            x->par->right = y;
        }
    }
    y->right = x;
    x->par = y;
}
template <class keytype, class Datatype>
Node<keytype, Datatype>* Tree<keytype, Datatype>::insert(keytype key, Datatype data) {
    if (root == NULL) {
        root = new Node<keytype, Datatype>(key, data, BLACK, nil, nil, nil);
        if (root == NULL) {
            std::cerr << "fail" << std::endl;
            return nil;
        }
        if (!nil) {
            std::cerr << "fail" << std::endl;
            return nil;
        }
        return root;
    }
    //如果树为空 建树
    Node<keytype, Datatype>* temp = new Node<keytype, Datatype>(key, data, RED, nil, nil, nil);
    Node<keytype, Datatype>* cur = root;
    Node<keytype, Datatype>* pre = nil;
    while (cur != nil) {
        pre = cur;
        if (cur->key < key) {
            cur = cur->right;
        }
        else if (cur->key > key) {
            cur = cur->left;
        }
        else {
            // cur->data++;
            delete temp;
            return cur;
        }
    }


    if (key < pre->key) {
        pre->left = temp;
    }
    else {
        pre->right = temp;
    }
    temp->par = pre;
    insert_Balance(temp);
    return temp;
}
template <class keytype, class Datatype>
Node<keytype, Datatype>* Tree<keytype, Datatype>::find(Datatype tar) {
    Node<keytype, Datatype>* cur = root;
    while (cur != NULL) {
        if (tar == cur->key)
            return cur;
        else if (tar < cur->key)
            cur = cur->left;
        else
            cur = cur->right;
    }
    return nil;
}

template <class keytype, class Datatype>
void Tree<keytype, Datatype>::insert_Balance(Node<keytype, Datatype>* t) {
    if (t == root) return;
    Node<keytype, Datatype>* p = t->par;
    Node<keytype, Datatype>* pp = p->par;
    //爸爸是祖父的左孩子
    if (p == pp->left) {
        if (t->par->color == RED) {
            Node<keytype, Datatype>* uncle = pp->right;
            if (uncle->color == RED) {
                uncle->color = p->color = BLACK;
                pp->color = RED;
                insert_Balance(pp);
            }
            else {
                if (t == p->left) {
                    p->color = BLACK;
                    pp->color = RED;
                    right_rotate(pp);
                }
                else if (t == p->right) {
                    left_rotate(p);
                    t->color = BLACK;
                    pp->color = RED;
                    right_rotate(pp);
                }
            }
        }
    }
    //爸爸是祖父的右孩子
    else {
        if (t->par->color == RED) {
            Node<keytype, Datatype>* uncle = pp->left;
            if (uncle->color == RED) {
                pp->color = RED;
                uncle->color = p->color = BLACK;
                insert_Balance(pp);
            }
            else if (uncle->color == BLACK) {
                //rr
                if (t == p->right) {
                    pp->color = RED;
                    p->color = BLACK;
                    left_rotate(pp);
                }
                // rl       
                else {
                    right_rotate(p);
                    pp->color = RED;
                    t->color = BLACK;
                    left_rotate(pp);
                }
            }

        }
    }
    root->color = BLACK;
}
template <class keytype, class Datatype>
void Tree<keytype, Datatype>::delete_node(Node<keytype, Datatype>* tar) {
    if (tar == nil) return;
    //删除的节点是叶子节点
    if (tar->left == nil && tar->right == nil) {
        if (tar->color == RED) {
            if (tar == tar->par->left)
                tar->par->left = nil;
            else
                tar->par->right = nil;
            delete tar;
            return;
        }
        else {
            del_B_nil(tar);
        }
    }
    else if (tar->left != nil && tar->right == nil) {
        Node<keytype, Datatype>* lc = tar->left;
        tar->key = lc->key;
        tar->data = lc->data;
        tar->left = nil;
        delete lc;
    }
    else if (tar->right != nil && tar->left == nil) {
        Node<keytype, Datatype>* rc = tar->right;
        tar->key = rc->key;
        tar->data = rc->data;
        tar->right = nil;
        delete rc;
    }
    else {
        Node<keytype, Datatype>* cur = tar->left;
        while (cur->right != nil) {
            cur = cur->right;
        }
        tar->key = cur->key;
        tar->data = cur->data;
        delete_node(cur);
    }
    root->color = BLACK;
}
template <class keytype, class Datatype>
void Tree<keytype, Datatype>::del_B_nil(Node<keytype, Datatype>* t) {

    if (t == t->par->left) {
        Node<keytype, Datatype>* p = t->par;
        Node<keytype, Datatype>* b = p->right;
        p->left = nil;
        delete t;
        t = NULL;
        if (b->color == BLACK) {
            if (b->left == nil && b->right == nil) {
                p->color = BLACK;
                b->color = RED;
            }
            else if (b->left->color == RED && b->right == nil) {
                right_rotate(b);
                b->par->color = p->color;
                p->color = BLACK;
                left_rotate(p);
            }
            else if (b->right->color == RED && b->left == nil) {
                b->color = p->color;
                b->right->color = BLACK;
                p->color = BLACK;
                left_rotate(p);
            }
            else {
                left_rotate(p);
                b->color = p->color;
                p->color = BLACK;
                b->right->color = BLACK;
            }

        }
        //兄弟节点为红色
        else {
            b->color = RED;
            b->left->color = RED;
            left_rotate(p);
        }
    }
    //删除节点是节点p的右孩子
    else {
        Node<keytype, Datatype>* p = t->par;
        Node<keytype, Datatype>* b = p->left;
        p->right = nil;
        delete t;
        t = NULL;
        if (b->color == BLACK) {
            if (b->left == nil && b->right == nil) {
                p->color = BLACK;
                b->color = RED;
            }
            else if (b->left->color == RED && b->right == nil) {
                b->color = p->color;
                p->color = BLACK;
                b->left->color = BLACK;
                right_rotate(p);
            }
            else if (b->left == nil && b->right->color == RED) {
                left_rotate(b);
                b->par->color = p->color;
                b->color = BLACK;
                p->color = BLACK;
                right_rotate(p);
            }
            else {
                b->color = p->color;
                b->left->color = BLACK;
                right_rotate(p);
            }
        }
        else {
            b->color = RED;
            b->right->color = RED;
            right_rotate(p);
        }
    }
}
template <class keytype, class Datatype>
void Tree<keytype, Datatype>::delete_node(Datatype key) {
    delete_node(find(key));
}

template <class keytype, class Datatype>

Datatype& Tree<keytype, Datatype>::operator[](const keytype& key) {
    Node<keytype, Datatype>* node = find(key);
    if (node == nil) {
        node = this->insert(key);
    }
    return  node->data;
}
template<class keytype, class Datatype>
void Tree<keytype, Datatype>::traverse(Node<keytype, Datatype>* node, std::function<void(keytype, Datatype)> callback) {
    if (node != nil) {
        traverse(node->left, callback);
        callback(node->first(), node->second());
        traverse(node->right, callback);
    }
}