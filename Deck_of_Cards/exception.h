#ifndef exception_h
#define exception_h

#include <exception>

namespace EXC {
  class E { 
    private:
    const char * msg;
    E(); // default constructor hidden
    public: 
    E(const char * s) noexcept(true) : msg(s) {}
    const char * what() const noexcept(true) {return msg;}
  };
}

#endif // exception_h
