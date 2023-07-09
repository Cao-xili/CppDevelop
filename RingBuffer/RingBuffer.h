#pragma once
#include <vector>
#include "iostream"

class RingBuffer 
{
public:
    RingBuffer(int size);

    void push(int item);

    int pop();

    int size();

    void print();

private:
    int start;
    int end;
    std::vector<int> buf;
};
