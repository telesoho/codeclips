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

# How to check operator << or >> exists?
https://stackoverflow.com/questions/4434569/is-it-possible-to-use-sfinae-templates-to-check-if-an-operator-exists

```cpp
namespace private_impl {
    typedef char yes;
    typedef char (&no)[2];

    struct anyx { template <class T> anyx(const T &); };

    no operator << (const anyx &, const anyx &);
    no operator >> (const anyx &, const anyx &);


    template <class T> yes check(T const&);
    no check(no);

    template <typename StreamType, typename T>
    struct has_loading_support {
        static StreamType & stream;
        static T & x;
        static const bool value = sizeof(check(stream >> x)) == sizeof(yes);
    };

    template <typename StreamType, typename T>
    struct has_saving_support {
        static StreamType & stream;
        static T & x;
        static const bool value = sizeof(check(stream << x)) == sizeof(yes);
    };

    template <typename StreamType, typename T>
    struct has_stream_operators {
        static const bool can_load = has_loading_support<StreamType, T>::value;
        static const bool can_save = has_saving_support<StreamType, T>::value;
        static const bool value = can_load && can_save;
    };
}
template<typename T>
struct supports_qdatastream : private_impl::has_stream_operators<std::ostream, T> {};

template<typename T>
struct can_load : private_impl::has_loading_support<std::ostream, T> {};

template<typename T>
struct can_save : private_impl::has_saving_support<std::ostream, T> {};

template<typename T>
struct can_log : private_impl::has_saving_support<c3::Log, T> {};


int test_main( int, char *[] )             // note the name!
{
    std::cout << can_log<c3::BANK_T>::value << can_save<BOOL>::value << std::endl;
    return 0;
}
```
