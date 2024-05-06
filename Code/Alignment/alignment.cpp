#include <cstddef>
#include "../show.h"

struct A {};
struct alignas(double) B {};//定义了一个结构体，使用alignas(double)对其进行对其。使用alignas
                            //关键字可以改变结构体的默认对奇方式。此处aligns(double)指示结构体B的对齐方式double相同

template <typename ...Ts>//...Ts使用参数包展开语法表示接受另个或多个类型参数，并将他们保存在参数包Ts中
struct alignas(Ts...) C{};

// struct alignas(char, double) C1{}; // Only packs allowed in alignas!

struct X {
    char a;
    int b;
    char c;
};

struct Y {
    char a;
    alignas(double) int b;
    char c;
};

struct Z {
    char a, b, a1, b1, c, a2, b2, a12, b12;
    int d;
};

template <typename T>
bool check_align(T const* const p, unsigned int alignment) {
    return ((reinterpret_cast<uintptr_t>(static_cast<void const* const>(p))&(alignment-1)) == 0);
};

int main() {
    SHOW(alignof(char));//alignof是C++中的一个运算符，用于获取类型的对其要求，如alignof int的对其要求是4
    SHOW(alignof(int16_t));
    SHOW(alignof(int));
    SHOW(alignof(float))
    SHOW(alignof(double));
    SHOW(alignof(bool));
    SHOW(alignof(A));
    SHOW(alignof(B));
    SHOW(alignof(C<char, double>));

    char a[8];
    alignas(double) char b[8]; // Why?
    SHOW(alignof(b));
    float *fp = new(b) float{3.14};//使用new运算符分配存储float类型对象所需的内存空间
                                    //b是一个指针，指向要放置对象的内存位置
                                    //float{3.14}是一个初始化器，创建并初始化一个float类型的临时对象，其中值为3.14
                                    //将临时对象3.14复制通过b指针指定的内存位置
    SHOW(*fp);
    SHOW_BOOL((static_cast<void*>(fp)==static_cast<void*>(b)));

    SHOW(alignof(std::max_align_t));

    alignas(128) char cache_line[128];
    alignas(128) char* p;
    SHOW_BOOL(check_align(cache_line, 128));
    SHOW_BOOL(check_align(&p, 128));
    char p1 = '0';
    p = &p1;
    SHOW_BOOL(check_align(&p, 128));
    SHOW_BOOL(check_align(p, 128));
    SHOW_BOOL(check_align(&p1, 128));

    std::cout << "--------------------------------\n";
    SHOW(sizeof(X));
    SHOW((sizeof(char) + sizeof(int) + sizeof(char)))
    SHOW(sizeof(Y));
    SHOW(sizeof(Z));
    std::cout << "--------------------------------\n";

    int *ip = new int{45};
    SHOW_BOOL(check_align(ip, 128));
    SHOW_BOOL(check_align(ip, 64));
    SHOW_BOOL(check_align(ip, 32));
    SHOW_BOOL(check_align(ip, sizeof(int)));

}
