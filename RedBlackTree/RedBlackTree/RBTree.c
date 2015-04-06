//
//  RBTree.c
//  RedBlackTree
//
//  Rule 1: A node is either red or black;
//  Rule 2: The root is black;
//  Rule 3: All leaves are black;
//  Rule 4: Every red node must have two black child;
//  Rule 5: Every path from a given node to any of its desendant NIL node contains the same number of black nodes.
//  Created by leah on 3/26/15.
//  Copyright (c) 2015 leah. All rights reserved.
//

#include "RBTree.h"

RedBlackNode *new_node(int val)
{
    RedBlackNode *t = (RedBlackNode *)malloc(sizeof(RedBlackNode));
    t->left = NULL;
    t->right = NULL;
    t->parent = NULL;
    t->val = val;
    t->color = RED;
    return t;
}

RedBlackTree *init()
{
    RedBlackTree *T = (RedBlackTree *)malloc(sizeof(RedBlackTree));
    T->root = NULL;
    return T;
}

RedBlackNode *get_parent(RedBlackNode *N)
{
    return N ? N->parent : NULL;
}

RedBlackNode *get_uncle(RedBlackNode *N)
{
    RedBlackNode *P = get_parent(N);
    RedBlackNode *G = get_parent(P);
    if (G) {
        if (G->left == P) {
            return G->right;
        } else {
            return G->left;
        }
    } else {
        return NULL;
    }
}

RedBlackNode *get_sibling(RedBlackNode *N)
{
    RedBlackNode *P = get_parent(N);
    if (P) {
        if (P->left == N) {
            return P->right;
        } else {
            return P->left;
        }
    } else {
        return NULL;
    }
}

void rotate_left(RedBlackTree *RBT, RedBlackNode *S)
{
    RedBlackNode *T = S->right;
    RedBlackNode *SP = get_parent(S);
    if (SP) {
        if (SP->left == S) {
            SP->left = T;
        } else {
            SP->right = T;
        }
    } else {
        RBT->root = T;
    }
    T->parent = SP;
    if (T->left) {
        T->left->parent = S;
    }
    S->right = T->left;
    S->parent = T;
    T->left = S;
}

void rotate_right(RedBlackTree *RBT, RedBlackNode *S)
{
    RedBlackNode *T = S->left;
    RedBlackNode *SP = get_parent(S);
    if (SP) {
        if (SP->left == S) {
            SP->left = T;
        } else {
            SP->right = T;
        }
    } else {
        RBT->root = SP;
    }
    T->parent = SP;
    if (T->right) {
        T->right->parent = S;
    }
    S->left = T->right;
    S->parent = T;
    T->right = S;
}

void insert_balance(RedBlackTree *RBT, RedBlackNode *N)
{
    RedBlackNode *P = get_parent(N);
    RedBlackNode *G = get_parent(P);
    RedBlackNode *U = get_uncle(N);
    if (P == NULL) {
        N->color = BLACK;
    } else {
        //skip p->color == balck
        //skip g == null
        if (P->color == RED && G) {
            if (U && U->color == RED) {
                P->color = BLACK;
                U->color = BLACK;
                G->color = RED;
                insert_balance(RBT, G);
            } else {
                if (!U || U->color == BLACK) {
                    if (N == P->right && P == G->left) {
                        rotate_left(RBT, P);
                        N = P;
                    } else if (N == P->left && P == G->right) {
                        rotate_right(RBT, P);
                        N = P;
                    }
                }
                P = get_parent(N);
                G = get_parent(P);
                P->color = BLACK;
                G->color = RED;
                if (N == P->left) {
                    rotate_right(RBT, G);
                } else {
                    rotate_left(RBT, G);
                }
            }
        }
    }
}

void insert(RedBlackTree *T, int val)
{
    if (!T->root) {
        //empty tree.
        T->root = new_node(val);
        T->root->color = BLACK;
    } else {
        RedBlackNode *tmp = T->root;
        RedBlackNode *P = NULL;
        RedBlackNode *N = new_node(val);
        // first find the place to insert the new node;
        while (tmp) {
            if (tmp->val > val) {
                P = tmp;
                tmp = tmp->left;
                if (!tmp) {
                    P->left = N;
                    N->parent = P;
                }
            } else if (tmp->val < val) {
                P = tmp;
                tmp = tmp->right;
                if (!tmp) {
                    P->right = N;
                    N->parent = P;
                }
            } else {
                return;
            }
        }
        // then balance the red black tree.
        insert_balance(T, N);
    }
}

static inline char* get_color(RedBlackNode *N)
{
    return (N && N->color == RED) ? "RED" : "BLACK";
}

//the varible index should be increase after each recursive call of travel_tree
//the right tree should ref to the new index value.
void travel_tree(RedBlackNode *root, FILE *f, int *index)
{
    int old_index = *index;
    if (root->left) {
        (*index)++;
        fprintf(f, "node_%d[label=\"%d\", color=%s];", *index, root->left->val, get_color(root->left));
        fprintf(f, "node_%d->node_%d;", old_index, *index);
        travel_tree(root->left, f, index);
    } else {
        (*index)++;
        fprintf(f, "node_%d[label=\"%s\", color=%s];", *index, "nil", get_color(root->left));
        fprintf(f, "node_%d->node_%d;", old_index, *index);
    }
    if (root->right) {
        (*index)++;
        fprintf(f, "node_%d[label=\"%d\", color=%s];", *index, root->right->val, get_color(root->right));
        fprintf(f, "node_%d->node_%d;", old_index, *index);
        travel_tree(root->right, f, index);
    } else {
        (*index)++;
        fprintf(f, "node_%d[label=\"%s\", color=%s];", *index, "nil", get_color(root->right));
        fprintf(f, "node_%d->node_%d;", old_index, *index);
    }
}

void gen_graph(RedBlackTree *T)
{
    RedBlackNode *root = T->root;
    if (!root) return;
    int index = 0;
    FILE *f = fopen("rbt.txt", "w");
    if (!f) return;
    //start digraph
    fputs("digraph G{node[shape=circle];", f);
    //add root node
    fprintf(f, "node_%d[label=\"%d\", color=%s];", index, root->val, get_color(root));
    //add other node
    travel_tree(root, f, &index);
    //finish digraph
    fputs("}", f);
    fclose(f);
    
    char *cmd = "/usr/local/bin/dot -Tpng rbt.txt -o rbt.png";
    system(cmd);
}

void del(RedBlackTree *T, int val)
{
    
}