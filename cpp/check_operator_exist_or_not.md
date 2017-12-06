# How to check whether operator== exists?
https://stackoverflow.com/questions/6534041/how-to-check-whether-operator-exists


```cpp
namespace CHECK
{
  class No { bool b[2]; };
  template<typename T, typename Arg> No operator== (const T&, const Arg&);

  bool Check (...);
  No& Check (const No&);

  template <typename T, typename Arg = T>
  struct EqualExists
  {
    enum { value = (sizeof(Check(*(T*)(0) == *(Arg*)(0))) != sizeof(No)) };
  };

  template <typename T>
  struct DumpExists
  {
  };
}

int main( int, char *[] )             // note the name!
{
    std::cout << CHECK::EqualExists<c3::BANK_T>::value << std::endl;
    return 0;
}
```
