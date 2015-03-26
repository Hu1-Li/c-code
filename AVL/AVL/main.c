//
//  main.c
//  AVL
//
//  Created by leah on 3/25/15.
//  Copyright (c) 2015 leah. All rights reserved.
//

#include "AVL.h"
#include <stdio.h>

int main()
{
    AVLTree* T = init();
    int A[] = { 10, 11, 5, 4, 8, 7, 6 };
    int n = sizeof(A) / sizeof(A[0]);
    for (int i = 0; i < n; ++i) {
        insert(T, A[i]);
    }
    int B[] = { 8 };
    int m = sizeof(B) / sizeof(B[0]);
    for (int i = m - 1; i >= 0; --i) {
        del(T, B[i]);
    }
    return 0;
}
