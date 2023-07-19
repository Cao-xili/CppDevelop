#pragma once
#include "iostream"
#include "memory"
#include "stack"

//����HolderBase��ʵ�����Ͳ������ṩһ��ͳһ������
class HolderBase
{
public:
    //ʵ���������ȷ����������
    virtual ~HolderBase() {}
};

//ʵ��һ���������洢���ݣ�����������HolderBase
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

    //�Ƚ�holderbase����ת��Ϊholder�����ٶ����ݽ��в���
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

    StackInfo stack;  // ʵ�ִ��࣬����ģ�庯����push��pop
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