#include <bitset>         // std::bitset
#include <string>         // std::string
#include <bitset>         // std::bitset

int main(){
    //生成
    bitset<16> foo;
    bitset<16> bar (0xfa2);
    bitset<16> baz (string("0101111001"));
    //输出
    cout << "foo: " << foo << '\n';
    cout << "bar: " << bar << '\n';
    cout << "baz: " << baz << '\n';

    //运算
    bitset<4> foo (std::string("1001"));
    bitset<4> bar (std::string("0011"));

    cout << (foo^=bar) << '\n';       // 1010 (XOR,assign)
    cout << (foo&=bar) << '\n';       // 0010 (AND,assign)
    cout << (foo|=bar) << '\n';       // 0011 (OR,assign)

    cout << (foo<<=2) << '\n';        // 1100 (SHL,assign)
    cout << (foo>>=1) << '\n';        // 0110 (SHR,assign)

    cout << (~bar) << '\n';           // 1100 (NOT)
    cout << (bar<<1) << '\n';         // 0110 (SHL)
    cout << (bar>>1) << '\n';         // 0001 (SHR)

    cout << (foo==bar) << '\n';       // false (0110==0011)
    cout << (foo!=bar) << '\n';       // true  (0110!=0011)

    cout << (foo&bar) << '\n';        // 0010
    cout << (foo|bar) << '\n';        // 0111
    cout << (foo^bar) << '\n';        // 0101

    //函数
//    foo.size() 返回大小（位数）
//    foo.count() 返回1的个数
//    foo.any() 返回是否有1
//    foo.none() 返回是否没有1
//    foo.set() 全都变成1
//    foo.set(p) 将第p + 1位变成1
//    foo.set(p, x) 将第p + 1位变成x
//    foo.reset() 全都变成0
//    foo.reset(p) 将第p + 1位变成0
//    foo.flip() 全都取反
//    foo.flip(p) 将第p + 1位取反
//    foo.to_ulong() 返回它转换为unsigned long的结果，如果超出范围则报错
//    foo.to_ullong() 返回它转换为unsigned long long的结果，如果超出范围则报错
//    foo.to_string() 返回它转换为string的结果
    return 0;
}