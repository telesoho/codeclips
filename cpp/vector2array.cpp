#include <iostream>
#include <vector>
using namespace std;

struct BASE {
    int x;
};

struct BASE2 {
    int y;
};

class Test {
    vector<BASE*> g_base;
public:    
    vector<BASE*>& test() {
        BASE * a = new BASE();
        a->x = 1;
        g_base.push_back(a);
        return  g_base;
    }
};

void test3(BASE2** base2) {
    printf("test3 %p = %d\n",base2, base2[0]->y);
}

BASE2** test2(Test* t) {
    vector<BASE*>& base = t->test();
    BASE2** base2 = (BASE2**)&base[0];
    printf("test2 %p = %d\n", base2, base2[0]->y);
    test3(base2);
    return base2;
}

int main()
{
    Test t;
    BASE2 ** base2 = test2(&t);
    try {
        printf("main %p %d\n", base2, base2[0]->y);
    }catch (exception e) {
        printf(e.what());
    }
    return 0;
}
