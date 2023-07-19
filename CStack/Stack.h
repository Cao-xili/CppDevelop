#pragma once
#include "iostream"
#include "memory"
#include "stack"

//创建HolderBase来实现类型擦除，提供一个统一的类型
class HolderBase
{
public:
    //实现虚基类来确保子类析构
    virtual ~HolderBase() {}
};

//实现一个子类来存储数据，这样可以用HolderBase
template <typename T>
class Holder :public HolderBase 
{
public:
    Holder(const T& data) : Hdata(data) {}
    T Hdata;
};

class StackInfo
{
public:

    template <typename T>
    void push(T data) 
    {
        stack.push(std::make_shared<Holder<T>>(data));
    }

    //先将holderbase对象转换为holder对象，再对数据进行操作
    template <typename T>
    void pop(T& data)
    {
        auto holder = std::dynamic_pointer_cast<Holder<T>>(stack.top());
        data = holder->Hdata;
        stack.pop();
    }

private:
    std::stack<std::shared_ptr<HolderBase>> stack;
};


class Test
{
public:
    int p1 = 1;
    bool p2 = false;
    std::string p3 = "p33333333";

    void testWithStack(StackInfo& stack)
    {
        int v1 = 0;
        std::string v2;
        Test v3;
        Test* v4 = nullptr;

        stack.pop<Test*>(v4);
        stack.pop(v3);
        stack.pop(v2);
        stack.pop(v1);

        std::cout << "testWithStack "
            << v1 << " "
            << v2 << " "
            << v3.p3 << " "
            << v4->p3 << std::endl;

        stack.push(1);
    }
};

void test2()
{
    Test t1;

    StackInfo stack;  // 实现此类，就俩模板函数，push和pop
    stack.push(111);
    stack.push<std::string>("asdfasdfasdf");

    Test t2;
    t2.p3 = "t2teststring";
    stack.push(t2);
    stack.push(&t1);

    t1.testWithStack(stack);

    int ret = 0;
    stack.pop(ret);
    std::cout << "testWithStack ret " << ret << std::endl;
}