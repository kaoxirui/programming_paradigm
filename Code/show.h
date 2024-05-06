#ifndef _EXAMPLES_CPP_CODE_SHOW_H_
#define _EXAMPLES_CPP_CODE_SHOW_H_
#include <iostream>

#define SHOW(X) std::cout << #X << " :  " << X << "\n";
#define SHOW_BOOL(X) std::cout << #X << " :  " << std::boolalpha << X << "\n";//#是一个预处理操作符，用于将参数X转换为字符串字面量
                                                                            //使用 std::boolalpha 操纵符设置
                                                                            // std::cout 对象以输出布尔值为 true 或 false 的文本形式。
#define SHOW_PREFIX(P,X) std::cout << P << "\n" << #X << "\n" << X << "\n";
#define OUT(B) std::ostream& operator<<(std::ostream &s, B a)

#define __DODO(x) x
#define DO(x) std::cout << #x << "\n"; __DODO x
#endif
