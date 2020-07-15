//
// Created by 28064 on 2020/7/14.
//

LL gcd(LL a, LL b) {
    return b == 0 ? a : gcd(b,a % b);
}

LL lcm(LL a, LL b) {
    return a / gcd(a, b) * b;
}