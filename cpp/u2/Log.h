#include <fstream>
#include <iostream>
#include <memory>
#include <string.h>
#include <vector>

namespace u2
{
class fmt
{
  public:
    template <typename... Args>
    static std::string string_format(const std::string &format, Args... args)
    {
        size_t size = snprintf(nullptr, 0, format.c_str(), args...) + 1; // Extra space for '\0'
        std::unique_ptr<char[]> buf(new char[size]);
        snprintf(buf.get(), size, format.c_str(), args...);
        return std::string(buf.get(), buf.get() + size - 1); // We don't want the '\0' inside
    }
};

/*
Serialize Functions
*/
struct NameValuePairCore
{
}; //!< Traits struct for NVPs

template <class T>
class NameValuePair : NameValuePairCore
{
  private:
    // If we get passed an array, keep the type as is, otherwise store
    // a reference if we were passed an l value reference, else copy the value
    using Type = typename std::conditional<std::is_array<typename std::remove_reference<T>::type>::value,
                                           typename std::remove_cv<T>::type,
                                           typename std::conditional<std::is_lvalue_reference<T>::value,
                                                                     T,
                                                                     typename std::decay<T>::type>::type>::type;

    // prevent nested nvps
    static_assert(!std::is_base_of<NameValuePairCore, T>::value,
                  "Cannot pair a name to a NameValuePair");

    NameValuePair &operator=(NameValuePair const &) = delete;

  public:
    //! Constructs a new NameValuePair
    /*! @param n The name of the pair
          @param v The value to pair.  Ideally this should be an l-value reference so that
                   the value can be both loaded and saved to.  If you pass an r-value reference,
                   the NameValuePair will store a copy of it instead of a reference.  Thus you should
                   only pass r-values in cases where this makes sense, such as the result of some
                   size() call.
          @internal */
    NameValuePair(char const *n, T &&v) : name(n), value(std::forward<T>(v)) {}

    char const *name;
    Type value;
};

// ######################################################################
//! Creates a name value pair
/*! @relates NameValuePair
      @ingroup Utility */
template <class T>
inline NameValuePair<T> make_nvp(std::string const &name, T &&value)
{
    return {name.c_str(), std::forward<T>(value)};
}

//! Creates a name value pair
/*! @relates NameValuePair
      @ingroup Utility */
template <class T>
inline NameValuePair<T> make_nvp(const char *name, T &&value)
{
    return {name, std::forward<T>(value)};
}

//! Creates a name value pair for the variable T with the same name as the variable
/*! @relates NameValuePair
      @ingroup Utility */
#define MK_NVP(T) ::u2::make_nvp(#T, T)

/**
 * While try to dump unknow type will call this function.
 * */
template <typename T, typename CharT, typename Traits>
std::basic_ostream<CharT, Traits> &
operator<<(std::basic_ostream<CharT, Traits> &os, const T &v)
{
    os << "<Unknow Type:" << typeid(T).name() << ">";
    return os;
}

class Log
{
  public:
    template <class... Types>
    inline static void dump(Types &&... args)
    {
        dump_process(std::forward<Types>(args)...);
    }

    static inline void add_stream(std::ostream &os)
    {
        std::shared_ptr<std::ostream> new_os(new std::ostream(os.rdbuf()));
        new_os->rdbuf(os.rdbuf());
        _os.push_back(new_os);
    }

  private:
    template <class T>
    inline static void dump_process(T &&head)
    {
        dump_impl(head);
    }

    template <class T, size_t n>
    inline static void dump_process(T (&head)[n])
    {
        for (size_t i = 0; i < n; i++)
        {
            dump_impl(head[i]);
        }
    }

    inline static void dump_process(const char *v)
    {
        for (auto &os : _os)
        {
            *os << v << std::endl;
        }
    }

    template <class Head, class... Tail>
    inline static void dump_process(Head &&head, Tail &&... tail)
    {
        dump_process(std::forward<Head>(head));
        dump_process(std::forward<Tail>(tail)...);
    }

    template <class T>
    inline static void dump_impl(NameValuePair<T> &nvp)
    {
        dump_nvp_impl(nvp.name, nvp.value);
    }

    template <class T, size_t n>
    inline static void dump_nvp_impl(const char *name, T (&v)[n])
    {
        for (int i = 0; i < n; i++)
        {
            std::string aName = fmt::string_format("%s[%d]", name, i);
            dump_nvp_impl(aName.c_str(), v[i]);
        }
    }

    template <class T>
    inline static void dump_nvp_impl(const char *name, T &v)
    {
        for (auto &os : _os)
        {
            *os << name << "=" << v << std::endl;
        }
    }

    template <class T, size_t n>
    inline static void dump_impl(NameValuePair<T> &nvp)
    {
        for (auto &os : _os)
        {
            *os << nvp.name << "=" << nvp.value << std::endl;
        }
    }

    template <class T>
    inline static void dump_impl(T &nvp)
    {
        for (auto &os : _os)
        {
            *os << nvp << std::endl;
        }
    }

  private:
    static std::vector<std::shared_ptr<std::ostream>> _os;

  public:
    static int _dump_level;
};


#define DUMP(level, ...)           \
    if (level <= Log::_dump_level) \
    Log::dump(fmt::string_format("%s(%d):", __FILE__, __LINE__), __VA_ARGS__)
}
