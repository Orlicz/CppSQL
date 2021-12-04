#define _CRT_SECURE_NO_WARNINGS
#pragma once

#include<fstream>
#include<cstdio>
#include<cstdlib>
#include"CppIO.h"
#define fc cout<<format
#define GetObj(ObjTyp,ObjNam) (*((ObjTyp*)(ObjNam)))

namespace TypFun {
    template<typename... T>
    struct TypS;
    template<typename T>
    struct TypS<T> {
        ull size;
        TypS(int n) {
            size = sizeof(T);
        }
    };
    template<typename T,typename... I>
    struct TypS<T,I...>
    {
        ull size;
        TypS(int n) {
            if (n) {
                size = TypS<I...>(n-1).size;
            }
            else {
                size = sizeof(T);
            }
        }
    };
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
    

    template<typename... T>
    class btab {
    public:
        ull* blong;
        void** data;
        bool flg;
        ull index;
        ull Size;

        template<typename I>
        void Get(I i) {

        }
        void In(FILE* f) {
            data = new void* [sizeof...(T)];
            for (int i = 0; i < sizeof...(T); i++)
            {
                data[i] = new char[TypS<T...>(i).size];
                fscanf(f, "%s", (char*)(data[i]));
            }
        }


        template<typename I>
        void Set(I i) {
            data[index] = new I(i);
            blong[index] = sizeof(I);
            Size += (sizeof(I) + 1);
            index++;
        }
        btab(T... t) {
            flg = 1;
            index = 0;
            Size = 0;
            blong = new ull[sizeof...(T)];
            data = new void* [sizeof...(T)];
            int arr[] = { (Set(t),0)... };

        }
        btab() {

            flg = 0;
        }
    };
    template<typename... T>class bbse {
    public:
        FILE* f;
        FILE* inon;
        const char* Src;
        bbse(const char* src,const char* mode="a+") {
            f = fopen(src, mode);
            Src = src;
        }
        void addtab(btab<T...>& t) {
            fseek(f, 0L, SEEK_END);
            if (t.flg) {
                for (int i = 0; i < sizeof...(T); i++) {
                    for (int j = 0; j < t.blong[i]; j++)
                        fputc(((char*)(t.data[i]))[j], f);
                    if (i == sizeof...(T) - 1)
                        fputc('\n', f);
                    else
                        fputc(' ', f);
                }
            }
            else {
                for (int i = 0; i < sizeof...(T); i++) {
                    fprintf(f, ((char*)(t.data[i])));
                    if (i == sizeof...(T) - 1)
                        fputc('\n', f);
                    else
                        fputc(' ', f);
                }
            }
        }

        void addtabS(btab<T...> t) {
            fseek(f, 0L, SEEK_END);
            if (t.flg) {
                for (int i = 0; i < sizeof...(T); i++) {
                    for (int j = 0; j < t.blong[i]; j++)
                        fputc(((char*)(t.data[i]))[j], f);
                    if (i == sizeof...(T) - 1)
                        fputc('\n', f);
                    else
                        fputc(' ', f);
                }
            }
            else {
                for (int i = 0; i < sizeof...(T); i++) {
                    fprintf(f, ((char*)(t.data[i])));
                    if (i == sizeof...(T) - 1)
                        fputc('\n', f);
                    else
                        fputc(' ', f);
                }
            }
        }

        //Find By Id
        template<typename Id>
        FILE* FBId(Id id) {
            TypSiz<T...> TS;
            ull Size = TS.size+sizeof...(T);
            fclose(f);
            f = fopen(Src, "r+");
            fseek(f, 0L, SEEK_SET);
            char* ch = new char[sizeof(Id)];
            for (int y = 0;!(feof(f)); y++) {
                fseek(f, Size*y, SEEK_SET);
                for (int i = 0; i < sizeof(Id); i++) {
                    ch[i] = fgetc(f);
                    //fscanf(f, "%c", ch + i);
                    //throw;
                }
                
                if (((Id*)ch)[0] == id) {
                    fseek(f, (0L - (sizeof(Id))), SEEK_CUR);
                    return f;
                }
                
            }
            throw "No find!";
            return nullptr;
        }
    };
}