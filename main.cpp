#include <iostream>
#include "DecisionTree.h"
using namespace std;

/**
* Title : Decision Tree
* Author : Melike Demirci
* ID: 21702346
* Section : 2
* Assignment : 2
* Description : Main.cpp
*/


int main(){
    double result = 0;
    DecisionTree* tree = new DecisionTree();
    tree->train("train_data", 450, 21);
    cout<< "data trained"<<endl;
    tree->print();
    result = tree->test("test_data", 450);
    cout<< "The result: " << result <<endl;
    delete tree;
    return 0;
}
