#include <memory>
#include "polymorphic/shared_polymorphic.hpp"
#include "time_it.hpp"

struct icalculator
{
    virtual int calculate(int) = 0;
    virtual ~icalculator() = default;
};

struct adder : public icalculator
{
    int calculate(int x) override
    {
        return x + x;
    }
};

template<class T>
struct user
{
    user(T calc) : _calc(calc)
    {
    }

    int calculate(int x)
    {
        return _calc->calculate(x);
    }

private:
    T _calc;
};

template<class T>
void loop(T & impl)
{
    time_it t;
    for (int i = 0; i < 1000000; ++i)
    {
        impl.calculate(i);
    }
}

int main()
{
    user<std::shared_ptr<icalculator>> u(std::make_shared<adder>());
    loop(u);
}
