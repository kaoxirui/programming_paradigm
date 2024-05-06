#include <iostream>
#include <thread>
#include <chrono>
#include <cassert>

struct func
{

	int m_id;
	
	func(int id)
	  :m_id(id)
		{}
	
	void operator()() const {

		std::cout<<"Thread with f "<<m_id<<" starts operator"<<std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(5));
		std::cout<<"Thread with f "<<m_id<<" operator call completed!"<<std::endl;
	}
	
};

int main()
{
	func f1(1);
	func f2(2);

	std::cout<<"Create thread 1"<<std::endl;
	std::thread t1(f1);
	assert(t1.joinable());
	
	std::cout<<"Waiting for thread 1"<<std::endl;
	t1.join();
	assert(!t1.joinable());

	std::cout<<"Thread 1 joined"<<std::endl;

	std::cout<<std::endl;
	
	std::cout<<"Create thread 2"<<std::endl;
	std::thread t2(f2);
	assert(t2.joinable());

	std::cout<<"Detaching thread 2"<<std::endl;
	t2.detach();
	assert(!t2.joinable());

	std::cout<<"Thread 2 detached"<<std::endl;
	
    // NOTE: try to comment out the join or detach call
	
}
