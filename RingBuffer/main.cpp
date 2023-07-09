#include"RingBuffer.h"

int main()
{
	RingBuffer ringbuffer(5);

	ringbuffer.push(1);
	ringbuffer.push(2);
	ringbuffer.push(3);
	ringbuffer.push(4);
	ringbuffer.push(5);

	ringbuffer.print();
	std::cout << "size:" << ringbuffer.size() << std::endl;

	ringbuffer.push(6);
	ringbuffer.push(7);
	ringbuffer.push(8);

	ringbuffer.print();
	std::cout << "size:" << ringbuffer.size() << std::endl;

	ringbuffer.pop();
	ringbuffer.pop();
	ringbuffer.pop();
	ringbuffer.pop();
	ringbuffer.pop();
	ringbuffer.pop();
	ringbuffer.print();
	std::cout << "size:" << ringbuffer.size() << std::endl;
}