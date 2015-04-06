//
//  RBTree.h
//  RedBlackTree
//
//  Created by leah on 3/26/15.
//  Copyright (c) 2015 leah. All rights reserved.
//

#ifndef __RedBlackTree__RBTree__
#define __RedBlackTree__RBTree__

#include <stdio.h>
#include <stdlib.h>
typedef enum RBNodeColor {
    RED,
    BLACK
} RBNodeColor;

typedef struct RedBlackNode {
    struct RedBlackNode* left;
    struct RedBlackNode* right;
    struct RedBlackNode* parent;
    int val;
    RBNodeColor color;
} RedBlackNode;

typedef struct RedBlackTree {
    struct RedBlackNode* root;
} RedBlackTree;

RedBlackTree *init();
void insert(RedBlackTree *T, int val);
void del(RedBlackTree *T, int val);
int find(RedBlackTree *T, int val);
void gen_graph(RedBlackTree *T);
#endif /* defined(__RedBlackTree__RBTree__) */
