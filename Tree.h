//
// Created by somai on 2018/3/3.
//

#ifndef INMU_PROVE_TREE_H
#define INMU_PROVE_TREE_H


template<class T>class Tree{
    typedef Tree* Node;
public:
    Node lch, rch;
    T val;
    virtual Node newNode(T x){
        return new Tree(x);
    }
    Tree insertL(T x){
        lch=newNode(x);
        return *this;
    }
    Tree insertR(T x){
        rch=newNode(x);
        return *this;
    }
    Tree getL(){
        return *lch;
    }
    Tree getR(){
        return *rch;
    }
    void destroy(){
        if(lch) lch -> destroy();
        if(rch) rch -> destroy();
        delete lch, rch;
    }

    explicit Tree(T x):val(x){
        lch=nullptr;
        rch=nullptr;
    }
    Tree():Tree(0){}
    template<class F> void backTraversal(F then){
        if(lch) lch -> backTraversal(then);
        if(rch) rch -> backTraversal(then);
        then(this);
    }
    template<class F> void middleTraversal(F then){
        if(lch) lch->middleTraversal(then);
        then(this);
        if(rch) rch->middleTraversal(then);
    }
    void fillRoots(auto arr){
        //if(lch) printf("Fill array with:%c\n", *arr);
        if(lch||rch) val=*arr;
        if(lch) lch->fillRoots(++arr);
        if(rch) rch->fillRoots(++arr);
    }
};


#endif //INMU_PROVE_TREE_H
