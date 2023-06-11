#include <stdio.h>

union Number {
    int intValue;
    float floatValue;
};

int main() {
    union Number num;

    num.intValue = 10;
    printf("Integer value: %d\n", num.intValue);

    num.floatValue = 3.14;
    printf("Float value: %f\n", num.floatValue);

    printf("Integer value after assigning float: %d\n", num.intValue);

    return 0;
}


#include <stdio.h>

void    increase_num(void)
{
    static int  num = 4;

    printf("%d\n", num);
    ++num;
}

int main(void)
{
    increase_num();     // static int  num = 4 실행된다.
    increase_num();     // 초기화 구문 무시됨.
    increase_num();     // 초기화 구문 무시됨.
    return (0);
}