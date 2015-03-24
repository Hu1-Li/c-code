#include <string>
#include <iostream>
using namespace std;
void get_post_order(string pre, string in)
{
    if (pre.size() == 0 || in.size() == 0 || in.size() != pre.size()) {
        return;
    }
    char current = pre[0];
    int index = in.find(current);
    if (index == string::npos) {
        return;
    }
    get_post_order(pre.substr(1, index), in.substr(0, index));
    get_post_order(pre.substr(index + 1), in.substr(index + 1));
    cout << current;
}

int main()
{
    string pre = "ABCDE";
    string in = "CBADE";
    get_post_order(pre, in);
    cout << endl;
    cout << "EXPECT: CBEDA" << endl;

    pre = "ABCDE";
    in = "CBAED";
    get_post_order(pre, in);
    cout << endl;
    cout << "EXPECT: CBEDA" << endl;

    pre = "ABCDE";
    in = "BCAED";
    get_post_order(pre, in);
    cout << endl;
    cout << "EXPECT: CBEDA" << endl;
    
    pre = "ABCDE";
    in = "CBADE";
    get_post_order(pre, in);
    cout << endl;
    cout << "EXPECT: CBADE" << endl;

    pre = "ABCDEFG";
    in = "CBDAFEG";
    get_post_order(pre, in);
    cout << endl;
    cout << "EXPECT: CDBFGEA" << endl;

    return 0;
}
