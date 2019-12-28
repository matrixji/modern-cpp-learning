#include <iostream>
#include <memory>

class Foo {
public:
    Foo(): mem_{new char[512]} {
        std::cout << "constructor" << std::endl;
    }

    Foo(const Foo&) = delete;

    Foo(Foo&& foo): mem_{nullptr} {
        std::cout << "move constructor" << std::endl;
        std::swap(mem_, foo.mem_);
    }

    ~Foo() {
        delete mem_;
    }

private:
    char *mem_;
};

#include <iostream>
#include <memory>

void bar(const std::string&) {
    std::cout << "bar(const std::string&)" << std::endl;
}

void bar(std::string&&) {
    std::cout << "bar(std::string&&)" << std::endl;
}

template <typename T>
void foo(T &&x) {
    bar(std::forward<T>(x));
}

int main() {
    std::string str{"hello"};
    foo(str);                      // bar(const std::string&)
    foo(std::move(str));           // bar(std::string&&)
    foo(std::string("x"));  // bar(std::string&&)
}