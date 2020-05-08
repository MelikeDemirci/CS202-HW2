#include   "DecisionTreeNode.h"

/**
* Title : Decision Tree
* Author : Melike Demirci
* ID: 21702346
* Section : 2
* Assignment : 2
* Description : Decision Tree Node Implementation
*/

DecisionTreeNode::DecisionTreeNode(){
    rightChildPtr = NULL;
    leftChildPtr = NULL;
}

DecisionTreeNode::DecisionTreeNode(int anItem, bool theNodeType):item(anItem),nodeType(theNodeType){
    rightChildPtr = NULL;
    leftChildPtr = NULL;
}

void DecisionTreeNode::setItem( const int& anItem){
    item = anItem;
}

void DecisionTreeNode::setNodeType( const bool theNodeType){
    nodeType = theNodeType;
}

int DecisionTreeNode::getItem() const{
    return item;
}

bool DecisionTreeNode::getNodeType() const{
    return nodeType;
}

DecisionTreeNode* DecisionTreeNode::getLeftChildPtr() const {
    return leftChildPtr;
}

DecisionTreeNode* DecisionTreeNode::getRightChildPtr() const {
    return rightChildPtr;
}

void DecisionTreeNode::setLeftChildPtr(DecisionTreeNode* leftPtr){
    leftChildPtr = leftPtr;
    if(leftPtr != NULL)
        nodeType = false;
}

void DecisionTreeNode::setRightChildPtr(DecisionTreeNode* rightPtr){
    rightChildPtr = rightPtr;
    nodeType = false;

}
