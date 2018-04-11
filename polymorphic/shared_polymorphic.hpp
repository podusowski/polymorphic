#pragma once

#include <type_traits>

template<class T>
struct shared_polymorphic
{
    template<class... Args>
    explicit shared_polymorphic(Args... args)
    {
        new (_storage._data) T(args...);
    }

    template<class U>
    shared_polymorphic(shared_polymorphic<U> && other)
    {
        new (_storage._data) U(*other);
    }

    template<class U>
    shared_polymorphic(const shared_polymorphic<U> & other) = delete;

    shared_polymorphic<T> share()
    {
        if (_mode == inplace)
        {
            _storage._ptr = new heap_storage{2, std::move(**this)};
            _mode = heap;
        }
    }

    T* operator->()
    {
        return reinterpret_cast<T*>(_storage._data);
    }

    T& operator*()
    {
        return reinterpret_cast<T&>(_storage._data);
    }

private:
    struct heap_storage
    {
        std::size_t shared_count;
        T object;
    };

    union
    {
        alignas(T) char _data[32];
        heap_storage* _ptr;
    } _storage;

    enum mode
    {
        inplace,
        heap
    };

    mode _mode;
};

