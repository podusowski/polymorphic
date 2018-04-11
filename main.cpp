#include "polymorphic/shared_polymorphic.hpp"
#include "time_it.hpp"

template<class T>
struct user
{
    user(T calc) : _calc(calc)
    {
    }

private:
    T _calc;
};

int main()
{
}
