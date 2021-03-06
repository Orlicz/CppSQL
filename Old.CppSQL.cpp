```cpp
#include<iostream>
#include<fstream>

using namespace std;

#define mytyp <int,string>
#define ull size_t

void d(void f(int e)) {
    f(0);
}


template<typename X, typename Y>
void h(void** data, X g, Y t) {
    data[0] = new X(g);
    data[1] = new Y(t);

    //cout << g << endl<< t;
}


template<typename X, typename ...Y>
void h(void** data, X g, Y... t) {
    //cout << g << endl;

    data[0] = new X(g);
    h(data + 1, t...);
}
namespace Typ {
    template<typename T>
    void GetCall(T Call, bool flg) {
        cout << Call;
        if (flg)
            cout << endl; 
        else 
            cout << ' ';
        return;
    }

    template<typename... T>
    struct TypSiz;
    template <typename T>
    struct TypSiz <T>{
        ull size;
        TypSiz(void f(ull,void**&),void**& c) {
            size = sizeof(T);
            f(size,c);
        }
        TypSiz() {
            size = sizeof(T);
        }
    };
    template <typename T,typename... I>
    struct TypSiz<T,I...> {
        ull size;
        TypSiz(void f(ull,void**&),void**& c) {
            size = sizeof(T);
            f(size,c);
            TypSiz<I...> n(f,c);
            size += n.size;
        }
        TypSiz() {
            size = sizeof(T);
            TypSiz<I...> n;
            size += n.size;
        }
    };
    template<typename... T>
    struct GetTyp;

    template<typename T>
    struct GetTyp<T> {
        GetTyp(void** data) {
            GetCall<T>((*((T*)data[0])), 1);
        }
    };

    template<typename T, typename... I>
    struct GetTyp<T, I...> {
        GetTyp(void** data)
        {
            GetCall<T>((*((T*)data[0])), 0);
            GetTyp<I...> n(data + 1);
        }
    };

    template<typename... T>
    struct SetTyp;

    template<typename T>
    struct SetTyp<T> {
        SetTyp(void** data, istream& fin) {
            data[0] = new T;
            fin >> *((T*)data[0]);
        }
    };

    template<typename T, typename... I>
    struct SetTyp<T, I...> {
        SetTyp(void** data, istream& fin) {
            data[0] = new T;
            fin >> *((T*)data[0]);
            SetTyp<I...>(data + 1, fin);
        }
    };
}
//
using namespace Typ;



//
template<typename ...T>
class table {
public:

    void** data;
    istream* myin;
    ull SIZE;
    table() {}

    table(T... t)
    {
        data = new void* [sizeof...(T)];
        h(data, t...);
        TypSiz<T...> n;
        SIZE = n.size;
    }


    template<typename IdTyp>
    IdTyp GetId() {
        return (*((IdTyp*)data[0]));
    }


    friend istream& operator >>(istream& fin, table<T...>& tab) {
        tab.data = new void* [sizeof...(T)];
        SetTyp<T...> test(tab.data, fin);
        return fin;
    }

};

#include<vector>

void BaseCall(ull s,void**& c) {
    
    cout << string((*((char**)c))) << ' ' << s << ' ';
    ((char**&)c)++;
}

template<typename ...T>
class base {
public:
    ofstream wfio;
    ifstream rfio;
    streambuf* ocin;
    streambuf* ocout;
    char* srcc;
    bool conso;

    base(const char* src, const char**& namelist,bool con = 0, basic_ios<ifstream>::openmode inmode = ios::in, basic_ios<ofstream>::openmode outmode = ios::out) {
        srcc = (char*)src;
        if (con) {
            puts("Open in file:");
            puts(src);
            puts("from: ");
            cout << this << endl;

            rfio.open(src, inmode);
            wfio.open(src, outmode);

            ocin = cin.rdbuf();
            ocout = cout.rdbuf();

            cin.rdbuf(rfio.rdbuf());
            cout.rdbuf(wfio.rdbuf());

        }
        else {
            puts("Debug:\nfrom: ");
            cout << this << endl;
        }
        conso = con;
        TypSiz<T...> t(BaseCall,(void**&)namelist);
        cout << endl;
    }
    ~base() {
        if (conso) {
            wfio.close();
            rfio.close();
            cin.rdbuf(ocin);
            cout.rdbuf(ocout);
        }
        cout << "DataBase " << this << " is close!\n";
    }

    void addtab(table<T...> tab) {
        GetTyp<T...>(tab.data);
    }

    template<typename r>
    size_t findtab(r mb) {
        cin.seekg(0L, ios::beg);
        char* red = new char[100];
        while (cin.get() != '\n');
        table<T...> tab;
        for ( ull re = 1; !(cin.eof()); re++) {
            cin >> tab;
            r id = tab.GetId<r>();
            printf("RE:%llu Id:%c\n", re, id);
            if (id == mb) {
                return re;
            }
            
        }
        return 0;
    }

    

};

int main(int t)
{
    const char** name = new const char*[2];
    name[0] = "Num";
    name[1] = "Nam";
    base<char, int> my("D:\\CppSQL.txt",name, 1, ios::in, ios::out);
    my.addtab(table<char, int>('A', 7));
    my.addtab(table<char, int>('B', 6));
    getchar();
    ull s=my.findtab('B');
    cout << s;
    return 0;
}
```
