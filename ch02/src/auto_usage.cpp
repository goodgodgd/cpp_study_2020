#include <iostream>

struct Foo {
    auto val() const {
        return m_;
    }
    auto& cref() const {
        return m_;
    }
    auto& mref() {
        return m_;
    }
    // C++14 부터 이런것도 허용되지만 권장하진 않는다.
    // void set(auto val) {
    //     m_ = val;
    // }

    int m_{};
};

int main() {
    auto i = 0;
    auto x = Foo{};
    auto y1 = x.cref();     // auto->int, y1: int, const int가 아닌 int로 받는다.
    auto z1 = x.mref();     // auto->int, z1: int
    y1 = 1;
    z1 = 1;
    std::cout << "y1=" << y1 << ", cref=" << x.cref() << std::endl;
    std::cout << "z1=" << z1 << ", mref=" << x.mref() << std::endl;

    {
        // const ref.는 변수 뿐만 아니라 임시 객체도 받을 수 있다.
        const int& a = 1;
        // mutable ref.는 '상수'를 받을 수 없다. 
        // int& a = 1;
        int b = a;  // const int&도 그냥 int로 받는게 자연스럽다.
        b = 2;
        std::cout << "a=" << a << ", b=" << b << std::endl;
    }

    auto& y2 = x.cref();    // auto->const int, y2: const int&, 참조를 받을때는 const를 유지한다.
                            // const가 명시적이지 않으므로 권장하지 않는다.
    auto& z2 = x.mref();    // auto->int, z2: int&
    // y2 = 2;  // error
    z2 = 2;
    std::cout << "y2=" << y2 << ", cref=" << x.cref() << std::endl;
    std::cout << "z2=" << z2 << ", mref=" << x.mref() << std::endl;

    const auto& y3 = x.cref();      // auto->const int, y3: const int&, const가 명시적이므로 권장!
    const auto& z3 = x.mref();      // auto->const int, z3: const int&, 
    // y3 = 3;  // error
    // z3 = 3;
    std::cout << "y3=" << y3 << ", cref=" << x.cref() << std::endl;
    std::cout << "z3=" << z3 << ", mref=" << x.mref() << std::endl;

    return 0;
}

