#include <vector>
#include <memory>

#define LEVEL 1

class Engine
{
public:
    auto set_oil_amount(float v) { oil_ = v; }
    auto get_oil_amount() { return oil_; }

private:
    float oil_;
};

class YamahaEngine: public Engine
{
};

#if LEVEL==0
class Boat {
public:
    Boat(std::shared_ptr<Engine> e, float l)
    : engine_{e}, length_{l} {}

    auto set_length(float l) { length_ = l; }
    auto get_length() { return length_; }
    auto& get_engine() { return engine_; }

private:
    std::shared_ptr<Engine> engine_;
    float length_;
};


int main()
{
    auto boat0 = Boat{std::make_shared<YamahaEngine>(), 6.7f};
    auto boat1 = boat0;

    printf("boat0) length=%1.3f, oil=%1.3f\n", boat0.get_length(), boat0.get_engine()->get_oil_amount());
    printf("boat1) length=%1.3f, oil=%1.3f\n", boat1.get_length(), boat1.get_engine()->get_oil_amount());

    printf("change boat0's oil amount\n");
    boat1.set_length(8.5f);
    boat1.get_engine()->set_oil_amount(3.4f);

    printf("boat0) length=%1.3f, oil=%1.3f\n", boat0.get_length(), boat0.get_engine()->get_oil_amount());
    printf("boat1) length=%1.3f, oil=%1.3f\n", boat1.get_length(), boat1.get_engine()->get_oil_amount());

    return 0;
}
#endif

//==================================================

#if LEVEL==1
class Boat {
private:
    // private에 있는 함수는 외부에서 실행 불가하다. 그러므로 이 클래스는 복사할 수 없다.
    // 단점: friend에서는 private에 접근할 수 있으므로 항상 불가능한건 아니다.
    Boat(const Boat& b) {}
    auto operator=(const Boat& b) {}

public:
    Boat(std::shared_ptr<Engine> e, float l)
    : engine_{e}, length_{l} {}

    auto set_length(float l) { length_ = l; }
    auto get_length() { return length_; }
    auto& get_engine() { return engine_; }

private:
    std::shared_ptr<Engine> engine_;
    float length_;
};


int main()
{
    /*
    // copy constructor is private
    auto boat0 = Boat{std::make_shared<YamahaEngine>(), 6.7f};
    // copy operator from other object is private
    auto boat1 = boat0;
    */
    Boat boat0{std::make_shared<YamahaEngine>(), 6.7f};
    printf("boat0) length=%1.3f, oil=%1.3f\n", boat0.get_length(), boat0.get_engine()->get_oil_amount());
    return 0;
    
}
#endif

//==================================================

#if LEVEL==2
class Boat {
public:
    Boat(std::shared_ptr<Engine> e, float l)
    : engine_{e}, length_{l} {}

    // private에 있든 public에 있든 함수가 삭제되었기 때문에 상관없이 복사 불가다.
    Boat(const Boat& b) = delete;
    auto operator=(const Boat& b) -> Boat& = delete;

    auto set_length(float l) { length_ = l; }
    auto get_length() { return length_; }
    auto& get_engine() { return engine_; }

private:
    std::shared_ptr<Engine> engine_;
    float length_;
};


int main()
{
    /*
    // copy constructor is deleted
    auto boat0 = Boat{std::make_shared<YamahaEngine>(), 6.7f};
    // copy operator from other object is deleted
    auto boat1 = boat0;
    */

    Boat boat0{std::make_shared<YamahaEngine>(), 6.7f};
    printf("boat0) length=%1.3f, oil=%1.3f\n", boat0.get_length(), boat0.get_engine()->get_oil_amount());
    return 0;
    
}
#endif
