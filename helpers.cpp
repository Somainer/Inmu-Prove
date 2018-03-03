//
// Created by somai on 2018/3/3.
//

#include "helpers.h"

#define OPOF(o) [](auto aa,auto bb){return (aa o bb);}
#define ITEMOF(o) {#o[0], OPOF(o)}
map<char, function<RationalExpr(RationalExpr, RationalExpr)>> operations = {
        ITEMOF(+), ITEMOF(-), ITEMOF(*), ITEMOF(/)
};
#undef OPOF
#undef ITEMOF

RationalExpr inmu::calculateTree(Tree<char> p) {
    if(isdigit(p.val)){
        return p.val-'0';
    }
    RationalExpr l=calculateTree(*p.lch), r=calculateTree(*p.rch);
    return operations[p.val](l,r);
}

template<class T> auto inmu::TreeWithLeavesOf(int n, auto leaves, T defRoot){
    int rootC = n-1;
    typedef Tree<T>* Node;
    queue<Node> que;
    while(!que.empty()) que.pop();
    auto res = new Tree<T>(defRoot);
    que.push(res);
    while(!que.empty()){
        auto cur=que.front();
        que.pop();
        if(rootC) {
            cur->insertL(defRoot);
            cur->insertR(defRoot);
            que.push(cur->lch);que.push(cur->rch);
            --rootC;
        }
        else break;//cur->val=*leaves++;
    }
    res->middleTraversal([&](auto x){if(!(x->lch||x->rch)) x->val = *leaves++;});
    return res;
}

auto inmu::enumExpr(vector<int> l) {
    map<RationalExpr, vector<string>> res;
    vector<char> cl(l.size());
    transform(l.begin(), l.end(), cl.begin(), [](int c){return c+'0';});
    auto calTree = TreeWithLeavesOf(l.size(), cl.begin(), '+');
    string ops="+-*/";
    //cout << "Tree Built, enumerating..." << endl;
    char fops[l.size()-1];
    for(long long p=0;p<1<<(l.size()-1<<1);++p){
        long long c=p;
        for(int i=1;i<l.size();i++,c>>=2){
            fops[i-1]=ops[c&3];
        }
        calTree->fillRoots(fops);
        auto ans = calculateTree(*calTree);
        if(ans.isValid()) res[ans].push_back(getExpr(calTree));
    }
    return res;
}

string inmu::getExpr(Tree<char>* t){
    string resl, resr;
    int prl=0,prr=0, prm=priorityOfOperator(t->val);
    if(t->lch) {
        prl=priorityOfOperator(t->lch->val);
        resl=getExpr(t->lch);
    }
    if(t->rch) {
        prr=priorityOfOperator(t->rch->val);
        resr=getExpr(t->rch);
    }
    if(prm<prl) resl="("+resl+")";
    if(prm<prr||((t->val=='-' || t->val=='/')&&priorityOfOperator(t->rch->val))) resr="("+resr+")";
    return resl+t->val+resr;
}

int inmu::priorityOfOperator(char o) {
    switch (o){
        case '*':
        case '/':return 1;
        case '+':
        case '-':return 2;
    }
    return 0;
}

int inmu::analyseAndPrint(auto resL, auto resR, int limit) {
    int res=0;
    for(auto &ite:resL){
        if(resR[ite.first].size()) cout << "Scope " << ite.first << ":" << endl;
        for(auto& eql:ite.second){
            for(auto & eqr:resR[ite.first]){
                ++res;
                cout << "\t" << eql << "==" << eqr << endl;
                if(limit > 0 && res >= limit) return res;
            }
        }
    }
    return res;
}

int inmu::slightDigest(auto resL, auto resR) {
    int res=0;
    for(auto &ite:resL){
        auto eqR = resR[ite.first];
        auto eqL = ite.second;
        if(eqR.size()) {
            //cout << "Scope " << ite.first << ":" << endl;
            cout << "\n" << eqL[0] << " == " << eqR[0] << " == " << ite.first << endl;
            res += eqL.size() * eqR.size();
        }
    }
    return res;
}

void inmu::startProve(vector<int> left, vector<int> right, int limit=-1, bool digest = false) {
    auto leftResult = enumExpr(left), rightResult = enumExpr(right);
    auto cnt = digest?slightDigest(leftResult, rightResult):analyseAndPrint(leftResult, rightResult, limit);
    cout << "\nTotal " << cnt << " results found." << endl;

}