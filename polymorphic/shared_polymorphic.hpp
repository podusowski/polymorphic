#pragma once

template<class T>
struct shared_polymorphic
{
    template<class... Args>
    shared_polymorphic(Args... args)
    {
        new (_data) T(args...);
    }

private:
    alignas(T) char _data[32];
};

