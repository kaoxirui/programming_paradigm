#include "../show.h"
#include <functional>

namespace A {
    template<typename To, typename From>
    To convert(From f)
    {
        return f;
    }

    void g(double d)
    {
        int i = convert<int>(d);    // calls convert<int, double>(double)
        char c = convert<char>(d);  // calls convert<char, double>(double)
        int(*ptr)(float) = convert; // instantiates convert<int, float>(float)
    }
}

namespace B {
    template<typename From, typename To>
    To convert(From f)
    {
        return f;
    }

    void g(double d)
    {
        int i = convert<double, int>(d); // now both are needed
        int j = convert<int, int>(d); // Conversion happens while passing the argument
        char c = convert<double, char>(d);
        int(*ptr)(double) = convert; // instantiates convert_<double, int>(duoble)
    }
}

template <typename T>
void foo(T a) {
    ++a;
    //a = a+1; //  This line is commented out for the __EXTRA_EXS__ stuff which is not very interesting
}

template <typename T>
void foo_r(T& a) {
    ++a;
    //a = a+1; //  This line is commented out for the __EXTRA_EXS__ stuff which is not very interesting
}

#ifdef __EXTRA_EXS__
// Look at these only as entartainment, if you are entartained by this stuff
template <typename T>
struct rw {
    T& x;
    rw(T& x) : x(x) {}

    operator T&() {return x;}
};


template <typename T>
rw<T> my_ref(T& x) { return rw<T>(x); }
#endif

int main() {
    A::g(2.3);
    B::g(2.3);

    int x = 10;

    foo(x);
    SHOW(x);

    int& y = x;
    foo(y);
    SHOW(x);

    foo<int&>(x);
    SHOW(x);


    // Extras
#ifdef __EXTRA_EXS__
    std::cout << "exatrs\n";
    foo(std::ref(x)); // This is cheating
    SHOW(x);

    auto foo1 = std::bind(foo<int&>, std::ref(x));
    foo1();
    SHOW(x);

    foo(my_ref(x)); // This is cheating
    SHOW(x);
#endif

}
