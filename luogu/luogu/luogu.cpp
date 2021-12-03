#include<iostream>
#include<fstream>
#include<bitset>
#include<vector>
#include<map>
#include<string>
#include"BitIO.h"
#include"CppIO.h"
using namespace std;
using namespace BIO;
#define mytyp <int,string>




int main()
{
    /*
    printf("%xhh\n", 02);
    // ofstream oco(cout);
    const char** name = new const char* [2];
    name[0] = "Num";
    name[1] = "Nam";
    base<char, int> my("D:\\a.in", name, 1, ios::in, ios::out);
    my.addtab(table<char, int>('A', 7));
    my.addtab(table<char, int>('B', 6));
    my.addtab(table<char, int>('d', 5));

    getchar();

    ull s = my.FindId('B');
    printf("%llu\n", s);

#define myy table<char, int>
    myy ss;
    //cout << my.FindTab('A');
    cout << my.GetTab("Nam", 7)[0];
    //s = my.FindId('d');
    //printf("%llu\n", s);
    */
    table<char, char> h('A', 'B') ;
    btab<char, char> t(h);
    bbse<char, char> b("D:\\a.in");
    b.addtab(t);
    return 0;
}