//
//  main.cpp
//  skip_list
//
//  Created by leah on 3/18/15.
//  Copyright (c) 2015 leah. All rights reserved.
//

#include "skip_list.h"

int main(int argc, const char * argv[]) {
    int A[] = { 1, 3, 5, 7, 2, 4, 6, 8, 10 };
    skip_list SL;
    for (int i = 0; i < sizeof(A)/sizeof(A[0]); ++i) {
        SL.insert(A[i]);
    }
    
    SL.gen_graph("skip_list");
    SL.remove(2);
    SL.gen_graph("skip_list_del");
    return 0;
}
