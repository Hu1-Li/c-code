//
//  AVL.c
//  AVL
//
//  Created by leah on 3/25/15.
//  Copyright (c) 2015 leah. All rights reserved.
//

#include "AVL.h"
AVLTree *init()
{
    AVLTree *T = (AVLTree *)malloc(sizeof(AVLTree));
    T->root = NULL;
    return T;
}

AVLNode *new_node(int val)
{
    AVLNode *t = (AVLNode *)malloc(sizeof(AVLNode));
    t->right = NULL;
    t->left = NULL;
    t->val = val;
    t->height = 1;
    t->parent = NULL;
    return t;
}

static inline int max(int a, int b)
{
    return a > b ? a : b;
}

static inline int get_balance_factor(AVLNode *t)
{
    return ((t->left ? t->left->height : 0) - (t->right ? t->right->height : 0));
}

static inline int calc_balance_factor(AVLNode *t)
{
    return max((t->left ? t->left->height : 0), (t->right ? t->right->height : 0)) + 1;
}

void leftRotate(AVLNode *t, AVLTree *T)
{
    AVLNode *s = t->right;
    if (!t->parent) {
        T->root = s;
    } else {
        if (t->parent->left == t) {
            t->parent->left = s;
        } else {
            t->parent->right = s;
        }
    }
    t->right = s->left;
    if (s->left) {
        s->left->parent = t;
    }
    s->left = t;
    s->parent = t->parent;
    t->parent = s;
    
    t->height = calc_balance_factor(t);
    s->height = calc_balance_factor(s);
}

void rightRotate(AVLNode *t, AVLTree *T)
{
    AVLNode *s = t->left;
    if (!t->parent) {
        T->root = s;
    } else {
        if (t->parent->left == t) {
            t->parent->left = s;
        } else {
            t->parent->right = s;
        }
    }
    t->left = s->right;
    if (s->right) {
        s->right->parent = t;
    }
    s->right = t;
    s->parent = t->parent;
    t->parent = s;
    
    t->height = calc_balance_factor(t);
    s->height = calc_balance_factor(s);
}

void insert(AVLTree *T, int val)
{
    if (!T->root) {
        T->root = new_node(val);
        return;
    }
    
    AVLNode *x = T->root;
    AVLNode *p = NULL;
    while (x) {
        p = x;
        if (x->val > val) {
            x = x->left;
        } else if (x->val < val) {
            x = x->right;
        } else {
            return;
        }
    }
    AVLNode *n = new_node(val);
    if (p->val > val) {
        //left
        p->left = n;
        n->parent = p;
    } else {
        //right
        p->right = n;
        n->parent = p;
    }
    
    do {
        if (n == p->left) {
            p->height += 1;
            if (get_balance_factor(p) == 0) {
                //the insert node does not affect the height.
                p->height -= 1;
                break;
            }
            if (get_balance_factor(p) == 2) {
                if (get_balance_factor(n) == -1) {
                    leftRotate(n, T);
                }
                rightRotate(p, T);
                break;
            }
        } else {
            p->height += 1;
            if (get_balance_factor(p) == 0) {
                p->height -= 1;
                break;
            }
            if (get_balance_factor(p) == -2) {
                //unbalance node;
                if (get_balance_factor(n) == 1) {
                    rightRotate(n, T);
                }
                leftRotate(p, T);
                break;
            }
        }
        n = p;
        p = p->parent;
    } while (p);
}

void del(AVLTree *T, int val)
{
    if (!T->root) {
        return;
    }
    AVLNode *x = T->root;
    AVLNode *p = NULL;
    AVLNode *n = NULL;
    while (x) {
        if (x->val > val) {
            x = x->left;
        } else if (x->val < val) {
            x = x->right;
        } else {
            break;
        }
    }
    if (!x) {
        //not found;
        return;
    }
    //using the x->right(x->right->leftmost) or x->left to replace x;
    //then delete x;
    if (x->right) {
        if (x->right->left) {
            n = x->right;
            while (n->left) {
                n = n->left;
            }
            p = n->parent;
            p->left = x->left;
            if (x->parent) {
                if (x->parent->left == x) {
                    x->parent->left = n;
                } else {
                    x->parent->right = n;
                }
            } else {
                T->root = n;
            }
            n->parent = x->parent;
            x->left->parent = n;
            n->left = x->left;
            x->right->parent = n;
            n->right = x->right;
        } else {
            p = x->right;
            if (x->parent) {
                if (x->parent->left == x) {
                    x->parent->left = p;
                } else {
                    x->parent->right = p;
                }
            } else {
                T->root = p;
            }
            p->parent = x->parent;
            if (x->left) {
                x->left->parent = p;
            }
            p->left = x->left;
        }
    } else {
        p = x->parent;
        if (p) {
            if (p->left == x) {
                if (x->left) {
                    x->left->parent = p;
                }
                p->left = x->left;
            } else {
                if (x->left) {
                    x->left->parent = p;
                }
                p->right = x->left;
            }
        } else {
            T->root = x->left;
            if (x->left) {
                x->left->parent = p;
            }
        }
    }
    free(x);
    
    while (p) {
        p->height = calc_balance_factor(p);
        int balance_factor = get_balance_factor(p);
        if (balance_factor == 2) {
            if (get_balance_factor(p->left) == -1) {
                leftRotate(p->left, T);
            }
            rightRotate(p, T);
        }
        if (balance_factor == -2) {
            //it should never reach here.
            if (get_balance_factor(p->left) == 1) {
                rightRotate(p, T);
            }
            leftRotate(p, T);
        }
        p = p->parent;
    }
}

int find(AVLTree *T, int val)
{
    AVLNode *x = T->root;
    while (x) {
        if (x->val > val) {
            x = x->left;
        } else if (x->val < val) {
            x = x->right;
        } else {
            return 0;
        }
    }
    return -1;
}
