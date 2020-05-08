#ifndef DECISIONTREENODE_H
#define DECISIONTREENODE_H
#include <iostream>
using namespace std;
/**
* Title : Decision Tree
* Author : Melike Demirci
* ID: 21702346
* Section : 2
* Assignment : 2
* Description : Decision Tree Node Header File
*/

class DecisionTreeNode {
private:
	int item;                   // Data portion
	bool nodeType;              // 0 for observation node, 1 for class node
	DecisionTreeNode* leftChildPtr;  	// Pointer to left child
	DecisionTreeNode* rightChildPtr; 	// Pointer to right child

public:
	DecisionTreeNode();
    DecisionTreeNode(int anItem, bool theNodeType);

    void setItem( const int& anItem);
    void setNodeType(const bool theNodeType);
    int getItem() const ;
    bool getNodeType() const;
    DecisionTreeNode* getLeftChildPtr() const ;
    DecisionTreeNode* getRightChildPtr() const ;
    void setLeftChildPtr(DecisionTreeNode* leftPtr);
    void setRightChildPtr(DecisionTreeNode* rightPtr);
    friend class DecisionTree;
};
#endif
