#include <memory>
#include <iostream>

struct B;

struct A {

	~A(){
		std::cout<<"A dtor"<<std::endl;
	}
	
	std::shared_ptr<B> m_ptr;
};

struct B {

	~B(){
		std::cout<<"B dtor"<<std::endl;
	}
	
	// Try to change data member type and check dtor usage
//	std::weak_ptr<A> m_ptr;
	std::shared_ptr<A> m_ptr;
};

int main() {

	
	std::shared_ptr<A> a(new A);
	std::shared_ptr<B> b(new B);

	a->m_ptr = b;
    b->m_ptr = a;
	
}
