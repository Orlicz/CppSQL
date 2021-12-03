#define _CRT_SECURE_NO_WARNINGS
#pragma once

#include<fstream>
#include<cstdio>
#include<cstdlib>
#include"CppIO.h"
#define fc cout<<format
namespace TypFun {
    template<typename F, typename... T>
    struct TF;
    template <typename F, typename T>
    struct TF <F, T> {
        ull size;
        TF(void f(ull, F), F c) {
            size = sizeof(T);
            f(size, c);
        }
        TF() {
            size = sizeof(T);
        }
    };
    template <typename F, typename T, typename... I>
    struct TF<F, T, I...> {
        ull size;
        TF(void f(ull, F), F c) {
            size = sizeof(T);
            f(size, c);
            TF<F, I...> n(f, c);
            size += n.size;
        }
        TF() {
            size = sizeof(T);
            TF<F, I...> n;
            size += n.size;
        }
    };
}
using namespace std;
using namespace TypFun;

namespace BIO {
    void BCall(ull s,ull*& data) {
        data[0] = (s);
        printf("%llu:%llu\n", (ull)data, data[0]);
        data++;
    }

    template<typename... T>
    class btab {
    public:
        ull* blong;
        void** data;
        btab(table<T...>& t) {
            blong = new ull[sizeof...(T)];
            ull** u = &blong;
            TF<ull*&, T...>(BCall, blong);
            blong = *u;
            data = t.data;
        }
    };
    template<typename... T>class bbse {
    public:
        FILE* f;

        bbse(const char* src,const char* mode="a+") {
            f = fopen(src, mode);

        }
        void addtab(btab<T...>& t) {
            for (int i = 0; i < sizeof...(T); i++) {
                for (int j = 0; j < t.blong[i]; j++)
                    fputc( ((char*)(t.data[i]))[j],f);
                fputc('\n', f);
            }
        

        }
    };
}