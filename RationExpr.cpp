//
// Created by somai on 2018/3/3.
//

#include "RationExpr.h"
int gcd(int a,int b){
    return b?gcd(b,a%b):a;
}
int lcm(int a,int b){
    return a/gcd(a,b)*b;
}