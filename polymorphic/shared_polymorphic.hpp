#pragma once

#include <type_traits>

template<class T>
struct shared_polymorphic
{
    template<class... Args>
    explicit shared_polymorphic(Args... args)
    {
        new (_data) T(args...);
    }

    template<class U>
    shared_polymorphic(shared_polymorphic<U> && other)
    {
        new (_data) U(*other);
    }

    template<class U>
    shared_polymorphic(const shared_polymorphic<U> & other) = delete;

    T* operator->()
    {
        return reinterpret_cast<T*>(_data);
    }

    T& operator*()
    {
        return reinterpret_cast<T&>(_data);
    }

private:
    alignas(T) char _data[32];
};

