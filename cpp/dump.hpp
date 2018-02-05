#pragma once

#include <set>
#include <fstream>
#include <iomanip>

#include <iostream>

namespace c3
{
    template<typename T, typename CharT, typename Traits>
    std::basic_ostream<CharT, Traits> &
    operator<<(std::basic_ostream<CharT, Traits> &os, const T &v)
    {
        os.write(typeid(T).name(), (unsigned int) strlen(typeid(T).name()));
        return os;
    }

    template<typename CharT, typename Traits>
    std::basic_ostream<CharT, Traits> &
    operator<<(std::basic_ostream<CharT, Traits> &os, char * &v)
    {
        os.write(v, strlen(v));
        return os;
    }

}

#define DUMP(_v)         c3::dump(#_v, _v, __FILE__, __LINE__)

namespace c3 {
    template<typename T>
    static void dump(const char * vName, const T& v, const char * fname, int lineNum) {
        std::ofstream ofs;
        ofs.open ("unit_test.log", std::ofstream::out | std::ofstream::app);
        ofs << fname << "(" << lineNum << "):" << vName << "=" << std::setprecision(9) << v << std::endl;
    }

    template<typename T, size_t n>
    static void dump(const char * vName, const T (&v)[n], const char * fname, int lineNum) {
        CString vArrayName;
        for(int i = 0; i < n; i++) {
            vArrayName.Format("%s[%d]", vName, i);
            c3::dump(vArrayName, v[i], fname, lineNum);
        }
    }
}


struct Foo {};

void testDump() {
    using namespace c3;
    const char * szName = "abcdefg";
    std::cout << 2 << "\n" << Foo() << std::endl;
    DUMP(2);
    DUMP(Foo());
    DUMP(szName);
    DUMP("This is a test");
}