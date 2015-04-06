//
//  main.c
//  RedBlackTree
//
//  Created by leah on 3/26/15.
//  Copyright (c) 2015 leah. All rights reserved.
//

#include <stdio.h>
#include "RBTree.h"
int main()
{
    int A[] = { 0, 1, 3, 5, 7, 2, 4, 6, 8, 10 };
    int n = sizeof(A) / sizeof(A[0]);
    RedBlackTree *T = init();
    for (int i = 0; i < n; ++i) {
        insert(T, A[i]);
        gen_graph(T);
    }
    return 0;
}