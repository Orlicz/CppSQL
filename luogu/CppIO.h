#pragma once
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
    struct TypSiz <T> {
        ull size;
        TypSiz(void f(ull, void**&), void**& c) {
            size = sizeof(T);
            f(size, c);
        }
        TypSiz() {
            size = sizeof(T);
        }
    };
    template <typename T, typename... I>
    struct TypSiz<T, I...> {
        ull size;
        TypSiz(void f(ull, void**&), void**& c) {
            size = sizeof(T);
            f(size, c);
            TypSiz<I...> n(f, c);
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


template<typename... T>
class base;
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
    IdTyp GetId(int index) {
        return (*((IdTyp*)data[index]));
    }


    friend istream& operator >>(istream& fin, table<T...>& tab) {
        tab.data = new void* [sizeof...(T)];
        SetTyp<T...> test(tab.data, fin);
        return fin;
    }
    friend ostream& operator <<(ostream& fout, table<T...> tab) {

        base<T...> b(new double(0));;

        b.addtab(tab);
        return fout;
    }
};


void BaseCall(ull s, void**& c) {

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

    base(const char* src, const char**& namelist = (const char**&)cin, bool con = 0, basic_ios<ifstream>::openmode inmode = ios::in, basic_ios<ofstream>::openmode outmode = ios::out) {
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

            conso = con;
            TypSiz<T...> t(BaseCall, (void**&)namelist);
            cout << endl;
        }
        else {
            puts("Debug:\nfrom: ");
            cout << this << endl;
        }

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
    base(double* u) {
        puts("Con Debug:\nfrom: ");

        ocin = cin.rdbuf();
        ocout = cout.rdbuf();
        rfio.open("CON");
        wfio.open("CON");
        cin.rdbuf(rfio.rdbuf());
        cout.rdbuf(wfio.rdbuf());
        cout << this << endl;
    }
    void addtab(table<T...> tab) {
        GetTyp<T...>(tab.data);
    }

    template<typename r>
    table<T...> FindTab(r mb) {
        cin.seekg(0L, ios::beg);
        char* red = new char[100];
        while (cin.get() != '\n');
        table<T...> tab;
        for (ull re = 1; !(cin.eof()); re++) {
            cin >> tab;
            r id = tab.GetId<r>(0);
            printf("RE:%llu Id:%c\n", re, id);
            if (id == mb) {
                return tab;
            }

        }
        return table<T...>();
    }

    template<typename r>
    ull FindId(r mb) {
        cin.seekg(0L, ios::beg);
        char* red = new char[100];
        while (cin.get() != '\n');
        table<T...> tab;
        for (ull re = 1; !(cin.eof()); re++) {
            cin >> tab;
            r id = tab.GetId<r>(0);
            printf("RE:%llu Id:%c\n", re, id);
            if (id == mb) {
                return re;
            }

        }
        return 0;
    }

    template<typename r>
    vector<table<T...>> GetTab(string Name, r mb) {
        vector<table<T...>> ret;
        map<string, int> mm;
        cin.clear();
        cin.seekg(0L, ios::beg);
        string sgg;
        for (int i = 0; i < sizeof...(T); i++) {
            cin >> sgg;
            mm[sgg] = i + 1;
            short a;
            cin >> a;
        }
        if (!(mm[sgg])) {
            throw string("There haven't name ") + Name;
        }
        table<T...> tab;
        for (ull re = 1; !(cin.eof()); re++) {
            cin >> tab;
            r id = tab.GetId<r>(mm[Name] - 1);
            printf("RE:%llu Id:%c\n", re, id);
            if (id == mb) {
                ret.push_back(tab);
            }

        }
        return ret;
    }

    /*
    template<typename r>
    size_t FindId(r mb) {
        cin.seekg(0L, ios::beg);
        char* red = new char[100];
        ull Siz = sizeof...(T);
        string s;
        for (int i = 0; i < sizeof...(T); i++) {
            cin >> s;
            short a;
            cin >> a;
            Siz += a;
        }
        table<T...> tab;
        for (ull re = 1; !(cin.eof()); re++) {
            r Id;
            cin >> Id;
            printf("RE:%llu Id:%c\n", re, Id);
            if (Id == mb) {
                return re;
            }
            cin.seekg(Siz - sizeof(r), ios::cur);
        }
        return 0;
    }
    */

};