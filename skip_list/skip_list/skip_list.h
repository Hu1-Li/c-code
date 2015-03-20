//
//  skip_list.h
//  skip_list
//
//  Created by leah on 3/18/15.
//  Copyright (c) 2015 leah. All rights reserved.
//

#ifndef __skip_list__skip_list__
#define __skip_list__skip_list__

#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <fstream>
#include <cstdio>

class skip_list_node {
public:
    int value;
    std::vector<skip_list_node *> forward;
    
    skip_list_node(int val);
    int get_level();
};

class skip_list {
public:
    skip_list();
    ~skip_list();
    bool find(int val);
    void insert(int val);
    void remove(int val);
    void gen_graph(std::string fname);
    void print_skip_list();

private:
    skip_list_node head, tail;
    int random_level();
    bool util(int val, bool is_remove);
};

#endif /* defined(__skip_list__skip_list__) */
