//
//  skip_list.cpp
//  skip_list
//
//  Created by leah on 3/18/15.
//  Copyright (c) 2015 leah. All rights reserved.
//

#include "skip_list.h"

skip_list_node::skip_list_node(int val):
    value(val)
{
    
}

int skip_list_node::get_level()
{
    return static_cast<int>(forward.size() - 1);
}

skip_list::skip_list():
    head(0), tail(0)
{
    head.forward.push_back(&tail);
    srand(static_cast<unsigned int>(time(NULL)));
}

skip_list::~skip_list()
{
    skip_list_node *current = head.forward[0];
    while(current != &tail) {
        skip_list_node *old = current;
        current = current->forward[0];
        delete old;
    }
}

bool skip_list::find(int val)
{
    return util(val, false);
}

void skip_list::insert(int val)
{
    std::vector<skip_list_node *> update(head.get_level() + 1);
    skip_list_node *x = &head;
    
    for (int i = static_cast<int>(head.get_level()); i >= 0; --i) {
        while (x->forward[i] != &tail) {
            if (x->forward[i]->value < val) {
                x = x->forward[i];
            } else if (x->forward[i]->value == val) {
                return;
            } else {
                break;
            }
        }
        update[i] = x;
    }
    
    int lvl = random_level();
    
    if (lvl > head.get_level()) {
        for (int i = head.get_level() + 1; i <= lvl; ++i) {
            update.push_back(&head);
            head.forward.push_back(&tail);
        }
    }
    
    skip_list_node *new_node = new skip_list_node(val);
    for (int i = 0; i <= lvl; ++i) {
        new_node->forward.push_back(update[i]->forward[i]);
        update[i]->forward[i] = new_node;
    }
    
}

//generate graphviz dot file
//then using graphviz to generate graph.
void skip_list::gen_graph(std::string fname)
{
    std::string digraph = "digraph g { nodesep=0;rankdir=LR;";
    digraph += "node[shape=record, width=.1, height=.1]; node0[label=\"";
    int lvl = head.get_level() + 1;
    std::vector<std::string> vh;
    for (int i = 0; i < lvl; i++) {
        vh.push_back("f" + std::to_string(i));
    }
    for (int i = 0; i < lvl; i++) {
        if (i == lvl - 1) {
            digraph += "<" + vh[i] + ">";
        } else {
            digraph += "<" + vh[i] + ">|";
        }
    }
    //digraph += "\", height=" + std::to_string(lvl * 1) + "];";
    digraph += "\"];";
    std::vector<std::vector<std::string > >vt;
    
    std::reverse(vh.begin(), vh.end());
    vt.push_back(vh);
    skip_list_node *x = head.forward[0];
    int index = 1;
    std::string name, node;
    while (x->forward.size() > 0) {
        int current_level = static_cast<int>(x->forward.size());
        std::vector<std::string> vs;
        for (int i = 0; i < current_level; ++i) {
            name = "node" + std::to_string(index++);
            node = name + "[label=\"{<n> " + std::to_string(x->value) + " |<p>}\"];";
            digraph += node;
            vs.push_back(name);
        }
        for (int i = current_level; i < lvl; ++i) {
            name = "node" + std::to_string(index++);
            node = name + "[label=\"{<n> " + std::to_string(x->value) + " |<p>}\", style=\"invisible\"];";
            digraph += node;
            vs.push_back(name);
        }
        
        vt.push_back(vs);
        x = x->forward[0];
    }

    std::vector<std::string>vs;
    for (int i = 0; i < lvl; ++i) {
        //adding nil node
        name = "node" + std::to_string(index++);
        node = name + "[label=\"{<n> nil}\"];";
        digraph += node;
        vs.push_back(name);
    }
    vt.push_back(vs);
    std::string relation;
    for (int i = 0; i < lvl; i++) {
        for (int j = 0; j < static_cast<int>(vt.size()) - 1; ++j) {
            if (j == 0) {
                relation = "node0:" + vt[j][i] + "->" + vt[j + 1][i] + ":n;";
            } else {
                relation = vt[j][i] + ":p->" + vt[j + 1][i] + ":n;";
            }
            digraph += relation;
        }
    }
    
    digraph += "}";
    
    std::ofstream f(fname + ".txt", std::ofstream::out);
    f << digraph;
    f.close();
    std::string cmd = "/usr/local/bin/dot -Tpng " + fname + ".txt -o" + fname + ".png";
    std::system(cmd.c_str());
    
}

void skip_list::print_skip_list()
{
    for (int i = head.get_level(); i >= 0; --i) {
        skip_list_node *x = head.forward[i];
        while (x) {
            if (x->forward.size() > 0) {
                std::cout << x->value << " ";
                x = x->forward[i];
            } else {
                break;
            }
        }
        std::cout << std::endl;
    }
}

void skip_list::remove(int val)
{
    util(val, true);
}

bool skip_list::util(int val, bool is_delete)
{
    skip_list_node *x = &head;
    int i = head.get_level();
    while (i >= 0) {
        if (x->forward[i] != &tail) {
            int value = x->forward[i]->value;
            if (value == val) {
                if (is_delete) {
                    int lvl = static_cast<int>(x->forward[i]->forward.size());
                    skip_list_node *to_de_delete = x->forward[i];
                    for (int j = 0; j <= lvl - 1; ++j) {
                        skip_list_node *tmp = x;
                        while (tmp->forward[j]->value != val) {
                            tmp = tmp->forward[j];
                        }
                        tmp->forward[j] = tmp->forward[j]->forward[j];
                    }
                    delete to_de_delete;
                    
                    while (head.get_level() > 0 && head.forward.back() == &tail) {
                        head.forward.pop_back();
                    }
                    return true;
                } else {
                    return true;
                }
            }
            if (value < val) {
                x = x->forward[i];
            } else {
                --i;
            }
        } else {
            i--;
        }
    }
    return false;
}

int skip_list::random_level()
{
    int level = 0;
    while (rand() % 2 > 0) {
        level++;
    }
    return level;
}