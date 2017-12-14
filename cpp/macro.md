# C++ MACRO

## Concate

https://gcc.gnu.org/onlinedocs/cpp/Concatenation.html#Concatenation

## Arg

'''cpp

#define ABC(x, ...) (x) ? #__VA_ARGS__ : ""
#define PROPS(a, p) str.##a(p)

void main() {
    CStringArray str;

    PROPS(Add, ABC(1, 2, 3, 4));

    std::cout << str[0] ;
}

'''

Output
2, 3, 4
