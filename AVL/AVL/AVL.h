//
//  AVL.h
//  AVL
//
//  Created by leah on 3/25/15.
//  Copyright (c) 2015 leah. All rights reserved.
//

#ifndef __AVL__AVL__
#define __AVL__AVL__
#include <stdio.h>
#include <stdlib.h>

typedef struct AVLNode {
    int val;
    int height;
    struct AVLNode *left;
    struct AVLNode *right;
    struct AVLNode *parent;
} AVLNode;

typedef struct AVLTree {
    struct AVLNode* root;
} AVLTree;

AVLTree* init();
void insert(AVLTree *T, int val);
void del(AVLTree *T, int val);
int find(AVLTree *T, int val);
#endif /* defined(__AVL__AVL__) */
