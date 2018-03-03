//
// Created by somai on 2018/3/3.
//

#ifndef INMU_PROVE_RATIONEXPR_H
#define INMU_PROVE_RATIONEXPR_H

#include "includes.h"
int gcd(int,int);
int lcm(int,int);
class RationalExpr{
public:
    int parseInt()const{
        return a/c;
    }

    explicit operator int(){
        return parseInt();
    }
    string show(){
        if(!isValid()) return "NaN";
        stringstream ss;
        string res;
        if(isInt()) ss << a;
        else ss << parseDouble();
        ss >> res;
        return res;
    }
    string _show()const{
        if(!isValid()) return "NaN";
        stringstream ss;
        string res;
        ss << a ;
        if(c!=1) ss << "/" << c;
        ss >> res;
        return res;
    }
    double parseDouble()const{
        return 1.0*a/c;
    }
    auto simplify(){
        if(err) return *this;
        int g=gcd(a,c);
        a/=g;c/=g;
        if(c<0) {a=-a; c=-c;}
        return *this;
    }
    bool isInt(){
        simplify();
        return c==1;
    }
    bool isValid() const{
        return !err;
    }
    bool isNaN(){
        return err;
    }
    RationalExpr INF(){
        return {0,0};
    }
    RationalExpr reciprocal() const{
        return {c,a};
    }
    friend ostream& operator<<(ostream& os, const RationalExpr& self){
        os << self._show();
        return os;
    }

    RationalExpr(int a=0,int b=1):a(a),c(b),err(!b){
        simplify();
    }
    bool operator==(const RationalExpr& e)const{
        return a*e.c == e.a*c;
    }
    bool operator<(const RationalExpr& e)const{
        return a*e.c < e.a*c;
    }
    RationalExpr operator+(const RationalExpr& e)const{
        return RationalExpr(a*e.c+c*e.a, c*e.c);
    }
    RationalExpr operator-()const{
        return RationalExpr(-a, c);
    }
    RationalExpr operator-(const RationalExpr& e)const{
        return {a*e.c-c*e.a, c*e.c};
    }
    RationalExpr operator*(const RationalExpr& e)const{
        return RationalExpr(a*e.a, c*e.c);
    }
    RationalExpr operator/(const RationalExpr& e)const{
        return this->operator*(e.reciprocal());
    }
private:
    int a,c;
    bool err;
};


#endif //INMU_PROVE_RATIONEXPR_H
