#include<iostream>
#include<fstream>
#include<bitset>
#include<vector>
#include<map>
#include<string>
#include"BitIO.h"
#include"CppIO.h"
#include<Windows.h>
using namespace std;
using namespace BIO;
#define mytyp <int,string>

#if 0

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
    
    /*table<char, char> h('A', 'B') ;
    btab<char, char> t(h);
    bbse<char, char> b("D:\\a.in");
    b.addtab(t);*/
#endif //Code Old


int main()
{
    char na[][2] = { "N","K" };
    base<char, char> bb("D:\\a.in", (const char**&)na,1);

    for (int i = 0; i < 100; i++)
        bb.addtab(table<char, char>('P', 'K'));
    bb.addtab(table<char, char>('A', 'B'));
    bb.FindId('A');

    
    /*try
    {
        bb.FBId('B');
    }
    catch (const char* s)
    {
        puts(s);
    }*/
    /*
    FILE* ff = bb.FBId('A');
    btab<char, char> f;
    f.In(ff);
    cout << GetObj(char, f.data[0]);
    bb.addtab(f);*/
    return 0;
}