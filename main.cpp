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

struct multiplier : public icalculator
{
    int calculate(int x) override
    {
        return x * x;
    }
};

template<class T>
struct user
{
    user(T calc, T calc2) : _calc(calc), _calc2(calc2)
    {
    }

    int calculate(int x)
    {
        return _calc2->calculate(_calc->calculate(x));
    }

private:
    T _calc;
    T _calc2;
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
    {
        user<std::shared_ptr<icalculator>> u(
            std::make_shared<adder>(), std::make_shared<multiplier>());
        loop(u);
    }

    {
        user<shared_polymorphic<icalculator>> u{
            shared_polymorphic<adder>(), shared_polymorphic<multiplier>()};
        loop(u);
    }

    {
        auto a = std::make_shared<adder>();
        user<std::shared_ptr<icalculator>> u(a, a);
        loop(u);
    }

    {
        shared_polymorphic<adder> a;
        user<shared_polymorphic<icalculator>> u{a.share(), a.share()};
        loop(u);
    }
}
