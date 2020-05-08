#ifndef DECISIONTREE_H
#define DECISIONTREE_H

#include "DecisionTreeNode.h"
#include <iostream>
using namespace std;

/**
* Title : Decision Tree
* Author : Melike Demirci
* ID: 21702346
* Section : 2
* Assignment : 2
* Description : Decision Tree Header File
*/

class DecisionTree {

private:
    DecisionTreeNode* rootPtr;
    int numFeatures;

protected:
    //------------------------------------------------------------
    //  Helper methods for the public methods.
    //------------------------------------------------------------
    void destroyTree(DecisionTreeNode* subTreePtr);// Recursively deletes all nodes from the tree.

    //------------------------------------------------------------
    //  Methods related to calculating entropy and information gain
    //------------------------------------------------------------
    double calculateEntropy(const int* classCounts, const int numClasses);
    double calculateInformationGain(const bool** data, const int* labels, const int numSamples, const int numFeatures, const bool* usedSamples, const int featureId);
    void insertionSort(int theArray[], int n);
    void getClassInfo(const int numSamples, const int* labels, const bool* usedSamples, int* classCounts, int& numClasses);

    //------------------------------------------------------------
    //  Helper methods for Train
    //------------------------------------------------------------
    void train(const bool** data, const int* labels, const int numSamples, const int numFeatures);
    void trainHelper(DecisionTreeNode*& treePtr, const bool** data, const int* labels, const int numSamples,
                     const int numFeatures, const bool* usedFeatures, const bool* usedSamples);
    bool numUsedFeatures(const int numFeatures, const bool* usedFeatures);
    int getFrequentLabel(const int* labels, const bool* usedSamples, const int numSamples);

    //------------------------------------------------------------
    //  Helper methods for Test
    //------------------------------------------------------------
    double test(const bool** data, const int* labels, const int numSamples);
    //Returns the prediction of the given boolean data set by using decision tree
    int predict(const bool* data);

    //------------------------------------------------------------
    //  Helper methods for Print
    //------------------------------------------------------------
    void preorderPrint(DecisionTreeNode* treePtr, int level);

public:
    //------------------------------------------------------------
    //  Constructor and Destructor Section.
    //------------------------------------------------------------
	DecisionTree();
    ~DecisionTree();

    //------------------------------------------------------------
    //  Public Decision Tree Methods Section.
    //------------------------------------------------------------
    int getNumFeatures() const;
    void train(const string fileName, const int numSamples, const int theNumFeatures);
    double test(const string fileName, const int numSamples);
    void print();


};
#endif
