#pragma once
namespace GameInput
{
    template<typename T>
    struct Inject {
        T* ptr_;

        Inject() : ptr_(nullptr) {}
        explicit Inject(T* _p) : ptr_(_p) {}

        T* operator->() const { return ptr_; }
        T& operator*() const { return *ptr_; }
        operator bool() const { return ptr_ != nullptr; }
    };
}
