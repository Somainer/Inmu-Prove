//
// Created by somai on 2018/3/3.
//

#ifndef INMU_PROVE_HELPERS_H
#define INMU_PROVE_HELPERS_H

#include "includes.h"
#include "RationExpr.h"
#include "Tree.h"

const int NO_LIMIT = 0;
const bool I_WANT_DIGEST = true;

namespace inmu{
    RationalExpr calculateTree(Tree<char>);
    auto enumExpr(vector<int>);
    string getExpr(Tree<char>*);
    template<class T> auto TreeWithLeavesOf(int, auto, T);
    int priorityOfOperator(char);
    int analyseAndPrint(auto, auto, int);
    void startProve(vector<int>, vector<int>, int, bool);
    int slightDigest(auto, auto);
}


#endif //INMU_PROVE_HELPERS_H
