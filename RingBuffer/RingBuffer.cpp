#include "RingBuffer.h"

RingBuffer::RingBuffer(int size) : start(0), end(0), buf(size)
{

}

void RingBuffer::push(int item) 
{
    if ((end + 1) % buf.size() == start) 
    {
        int newSize = buf.size() * 2;
        std::vector<int> newBuf(newSize);
        int i = 0;
        do 
        {
            newBuf[i++] = buf[start];
            start = (start + 1) % buf.size();
        } while (start != end);

        start = 0;
        end = i;
        buf.swap(newBuf);  
    }
    buf[end] = item;
    end = (end + 1) % buf.size();
}

int RingBuffer::pop()
{
    if (start == end) 
    {
        std::cout << "Buffer is empty";
    }
    int ret = buf[start];
    start = (start + 1) % buf.size();

    if (size() < buf.size() / 4) 
    {
        int newSize = buf.size() / 2;
        std::vector<int> newBuf(newSize);
        int i = 0;
        while (start != end) 
        {
            newBuf[i++] = buf[start];
            start = (start + 1) % buf.size();
        }
        start = 0;
        end = i;
        buf.swap(newBuf);
    }
    return ret;
}


int RingBuffer::size() 
{
    return (end - start + buf.size()) % buf.size();
}

void RingBuffer::print() 
{
    int i = start;
    while (i != end) 
    {
        std::cout << buf[i] << ' ';
        i = (i + 1) % buf.size();
    }
    std::cout << std::endl;
}