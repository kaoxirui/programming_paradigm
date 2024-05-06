#ifdef NDEBUG
#undef NDEBUG
#endif

#include <iostream>
#include <cassert>

template <typename T>
T add1(T x) { return x + 1; }

std::string add1(std::string x) { return x + "1"; }


int execute(int(*fp)(int), int a) {
    return fp(a);
}

template <typename T>
T execute(T(*fp)(T), T a) {
    return fp(a);
}


int main() {

    int x = 64;

    auto a = add1(x);
    static_assert(std::is_same<decltype(a), int>::value, "");
    assert(a == 65);

    std::cout << "As int    " << a << "\n"; // Should print 65

    auto b = add1<char>(x);
    static_assert(std::is_same<decltype(b), char>::value, "");
    assert(b == 'A');

    std::cout << "As char   " << b << "\n"; // Should print 'A'

    std::string s("64 + ");
    auto c = add1(s);
    static_assert(std::is_same<decltype(c), std::string>::value, "");
    assert(c == "64 + 1");

    std::cout << "As string " << c << "\n";


    int (*fp)(int) = add1;

    auto d = execute(fp, 41);
    assert(d == 42);

    std::cout << d << "\n";


    float (*flp)(float) = add1;

    auto e = execute(flp, 40.9999f);
    assert(e == 41.9999f);

    std::cout << e << "\n";
}
