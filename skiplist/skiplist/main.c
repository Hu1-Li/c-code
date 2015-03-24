#include "skiplist.h"
#include <stdio.h>

int main()
{
    skip_list SL = init();
    for (int i = 1; i < 6; ++i) {
        insert(&SL, i);
    }
    print_list(&SL);
    return 0;
}