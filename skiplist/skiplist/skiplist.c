//
//  skiplist.c
//  skiplist
//
//  Created by leah on 3/17/15.
//  Copyright (c) 2015 leah. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "skiplist.h"

skip_list init()
{
    srand((unsigned int)time(NULL));
    skip_list *list = (skip_list *)malloc(sizeof(skip_list));
    list->level = 1;
    list->bottom = (skip_list_node *)malloc(sizeof(skip_list_node));
    list->bottom->down = NULL;
    list->bottom->right = NULL;
    list->bottom->value = 0;
    list->top = (skip_list_node *)malloc(sizeof(skip_list_node));
    list->top->down = list->bottom;
    list->top->right = NULL;
    list->top->value = 0;
    return *list;
}

int rand_level()
{
    int level = 1;
    while (rand() % 2) {
        level++;
    }
    return level;
}

void insert(skip_list *list, int val)
{
    skip_list_node *x = list->top->down;
    int lvl = rand_level();
    int max_level = list->level > lvl ? list->level : lvl;
    
    skip_list_node **update = (skip_list_node **)malloc(max_level * sizeof(skip_list_node *));

    int index = list->level - 1;
    while (x != NULL) {
        if (x->right) {
            int value = x->right->value;
            if (value == val) {
                return;
            }
            if (value > val) {
                update[index--] = x;
                x = x->down;
            } else {
                x = x->right;
            }
        } else {
            update[index--] = x;
            x = x->down;
        }
    }
    if (list->level < lvl) {
        for (int i = list->level; i < lvl; i++) {
            skip_list_node *t = (skip_list_node *)malloc(sizeof(skip_list_node));
            t->right = NULL;
            t->value = 0;
            t->down = list->top->down;
            list->top->down = t;
            update[i] = t;
        }
    }
    
    skip_list_node *new_node = (skip_list_node *)malloc(sizeof(skip_list_node) * lvl);
    for (int i = 0; i < lvl; ++i) {
        new_node[i].value = val;
        new_node[i].right = NULL;
        if (i == 0) {
            new_node[i].down = NULL;
        } else {
            new_node[i].down = &new_node[i - 1];
        }
    }
    for (int i = 0; i < lvl; ++i) {
        new_node[i].right = update[i]->right;
        update[i]->right = &new_node[i];
    }
    list->level = max_level;
    free(update);
}

void print_list(skip_list *list)
{
    skip_list_node *x = list->top->down;
    while (x) {
        skip_list_node *y = x->right;
        while (y) {
            printf("%d ", y->value);
            y = y->right;
        }
        x = x->down;
        printf("\n");
    }
}

void del(skip_list *list, int val)
{
    
}

int find(skip_list *list, int val)
{
    return 0;
}
