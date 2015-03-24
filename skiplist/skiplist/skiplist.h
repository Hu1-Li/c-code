//
//  skiplist.h
//  skiplist
//
//  Created by leah on 3/17/15.
//  Copyright (c) 2015 leah. All rights reserved.
//

#ifndef skiplist_skiplist_h
#define skiplist_skiplist_h

typedef struct skip_list_node {
    int value;
    struct skip_list_node *right;
    struct skip_list_node *down;
} skip_list_node;

typedef struct skip_list {
    int level;
    struct skip_list_node* top;
    struct skip_list_node* bottom;
} skip_list;

skip_list init();
int find(skip_list *list, int val);
void insert(skip_list *list, int val);
void del(skip_list *list, int val);
void print_list(skip_list *list);

#endif
