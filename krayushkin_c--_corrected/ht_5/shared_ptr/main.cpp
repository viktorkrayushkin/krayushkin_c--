#include <iostream>
#include <functional>
#include <vector>

template <typename T>
class SharedPtr {
public:
    using DeleteFunctionType = std::function<void(T*)>;

    explicit SharedPtr():
            val_(nullptr),
            ctrlBlock_(nullptr)
    {
    }

    explicit SharedPtr(std::nullptr_t,
                       DeleteFunctionType = [](T* val) {
                           delete val;
                       }):
            val_(nullptr),
            ctrlBlock_(nullptr)
    {
    }

    explicit SharedPtr(T* val,
                       DeleteFunctionType deleteFunction = [](T* val) {
                           delete val;
                       }):
            val_(val),
            ctrlBlock_(new ControlBlock(1, std::move(deleteFunction)))
    {
    }

    ~SharedPtr() {
        if (val_ == nullptr) {
            return;
        }
        if (--ctrlBlock_->refCount <= 0) {
            ctrlBlock_->deleteFunction(val_);
            delete ctrlBlock_;

            val_ = nullptr;
            ctrlBlock_ = nullptr;
        }
    }

    SharedPtr(const SharedPtr& rhs):
            val_(rhs.val_),
            ctrlBlock_(rhs.ctrlBlock_)
    {
        if (ctrlBlock_ != nullptr) {
            ++ctrlBlock_->refCount;
        }
    }

    SharedPtr& operator=(SharedPtr rhs) {
        swap(rhs);
        return *this;
    }

    void swap(SharedPtr& rhs) {
        using std::swap;
        swap(val_, rhs.val_);
        swap(ctrlBlock_, rhs.ctrlBlock_);
    }

    bool operator==(const SharedPtr& rhs) const {
        return val_ == rhs.val_ && ctrlBlock_ == rhs.ctrlBlock_;
    }

    T* get() const {
        return val_;
    }

    T& operator*() const {
        return *val_;
    }

    T* operator->() const {
        return val_;
    }

    friend void swap(SharedPtr& lhs, SharedPtr& rhs) {
        lhs.swap(rhs);
    }

    operator bool() const {
        return val_ != nullptr;
    }

private:
    struct ControlBlock {
        ControlBlock(int cnt, DeleteFunctionType fnc):
                refCount(cnt),
                deleteFunction(fnc)
        {
        }

        int refCount;
        DeleteFunctionType deleteFunction;
    };

    T* val_;
    ControlBlock* ctrlBlock_;
};


template <typename T, typename... Args>
SharedPtr<T> MakeShared(Args&&... args) {
    return SharedPtr<T>(new T(std::forward<Args>(args)...));
}





struct Foo {
    Foo(int a, int b) : a_(a), b_(b) {}
    int a_;
    int b_;
    void sayHello() {
        std::cout << "Hello from " << *this << "\n";
    }
    friend std::ostream& operator<<(std::ostream& os, const Foo& rhs) {
        os << "Foo(" << rhs.a_ << ", " << rhs.b_ << ")";
        return os;
    }
};

int main() {
    {
        // Basic usage
        SharedPtr<Foo> c; // Default constructor
        SharedPtr<Foo> a(new Foo(1,2)); // Constructor with value
        auto b = a; // Copy constructor
        c = b; // Assignment operator
    }

    {
        // using custom delete
        constexpr int arrSize = 10;
        SharedPtr<int> a(new int[arrSize], [](auto p) {
            delete[] p;
        }); // custom deleter
        auto b = a; // copy constructor -- make sure the custom deleter is propogated
        SharedPtr<int> c;
        c = a; // copy assignment
    }

    {
        // nullptr
        SharedPtr<Foo> a(nullptr);
        auto b = a;
        SharedPtr<Foo> c;
        c = a;
    }

    {
        // Make shared -- basic usage
        SharedPtr<Foo> c; // Default constructor

        auto a = MakeShared<Foo>(2, 3);
        auto b = a; // Copy constructor
        c = b; // Assignment operator
        std::cout << "*c = " << *c << "\n";
        c->sayHello();
    }

    {
        std::vector<SharedPtr<std::vector<int>>> v;
        v.emplace_back();
        v.emplace_back();
        v.emplace_back();
        v.emplace_back();
        v.emplace_back();
        std::cout << v.size() << "\n";
    }
}