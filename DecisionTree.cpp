#include "DecisionTree.h"
#include <string>
#include <iostream>
#include <fstream>
#include <cmath>

/**
* Title : Decision Tree
* Author : Melike Demirci
* ID: 21702346
* Section : 2
* Assignment : 2
* Description : Decision Tree Implementation
*/

DecisionTree::DecisionTree():rootPtr(NULL){}

DecisionTree::~DecisionTree(){
    destroyTree(rootPtr);
}

void DecisionTree::destroyTree(DecisionTreeNode* subTreePtr) {
    if (subTreePtr != NULL ) {
        destroyTree(subTreePtr->getLeftChildPtr());
        destroyTree(subTreePtr->getRightChildPtr());
        delete subTreePtr;
    } // end if
} // end destroyTree

bool DecisionTree::numUsedFeatures(const int numFeatures, const bool* usedFeatures){
    int c = 0;
    for(int i = 0; i < numFeatures; i++ ){
        if(usedFeatures[i])
            c++;
    }
    return c == 0;
}

int DecisionTree::getFrequentLabel(const int* labels, const bool* usedSamples, const int numSamples){
    int usedLabels[numSamples];
    int n = 0;
    for(int i = 0; i < numSamples; i++){
        if(usedSamples[i]){
            usedLabels[n] = labels[i];
            n++;
        }
    }

    insertionSort(usedLabels, n);

    int max_count = 1, mostFreq = usedLabels[0], curr_count = 1;
    for (int i = 1; i < n; i++) {
        if (usedLabels[i] == usedLabels[i - 1])
            curr_count++;
        else {
            if (curr_count > max_count) {
                max_count = curr_count;
                mostFreq = usedLabels[i - 1];
            }
            curr_count = 1;
        }
    }

    // If last element is most frequent
    if (curr_count > max_count)
    {
        max_count = curr_count;
        mostFreq = usedLabels[n - 1];
    }

    return mostFreq;
}

void DecisionTree::trainHelper(DecisionTreeNode*& treePtr, const bool** data, const int* labels, const int numSamples,
                     const int numFeatures, const bool* usedFeatures, const bool* usedSamples){
    //If there is only one feature left in available features
    bool noFutureLeft = numUsedFeatures(numFeatures, usedFeatures);
    //Calculate node entropy
    int* classCounts = new int[10];
    int numClasses;
    double entropy = 100.;
    int freqLabel = getFrequentLabel(labels, usedSamples, numSamples);
    getClassInfo(numSamples, labels, usedSamples, classCounts, numClasses);
    entropy = calculateEntropy(classCounts, numClasses);

    if(noFutureLeft){
       treePtr = new DecisionTreeNode(freqLabel,true);

    }
    else if(entropy <= 0.0){
       treePtr = new DecisionTreeNode(freqLabel,true);

    }
    else{
        //Calculate information gain for every available feature
        int featureId;
        double tempGain = 0;
        double maxGain = -1;
        for(int i = 0; i < numFeatures; i++){
            if(usedFeatures[i]){
                tempGain = calculateInformationGain(data, labels, numSamples, numFeatures, usedSamples, i);
                if(tempGain > maxGain){
                    maxGain = tempGain;
                    featureId = i;
                }
            }
        }
        //Create new decision tree node with future id that give max inf gain
        treePtr = new DecisionTreeNode(featureId, false);

        //Create new bool arrays for child nodes and fill accordingly
        bool uF1[numFeatures];
        bool uF2[numFeatures];
        bool uS1[numSamples];
        bool uS2[numSamples];

        for(int j = 0; j < numSamples; j++){
            if(usedSamples[j]){
                if(data[j][featureId]){
                    uS1[j]= true;
                    uS2[j]= false;
                }
                else{
                    uS1[j]= false;
                    uS2[j]= true;
                }
            }else{
                uS1[j] = usedSamples[j];
                uS2[j] = usedSamples[j];
            }
        }

        for(int k = 0; k < numFeatures; k++){
            if(k == featureId){
                uF1[k]=false;
                uF2[k]=false;
            }
            else{
                uF1[k]= usedFeatures[k];
                uF2[k]= usedFeatures[k];
            }
        }
        //call the function for the childs
        trainHelper(treePtr->leftChildPtr, data, labels, numSamples, numFeatures, uF1, uS1);
        trainHelper(treePtr->rightChildPtr, data, labels, numSamples, numFeatures, uF2, uS2);

        delete[] classCounts;
    }

}

void DecisionTree::train(const bool** data, const int* labels, const int numSamples, const int numFeatures){
    bool usedSamples[numSamples];
    bool usedFeatures[numFeatures];

    //Create root node
    /*if(rootPtr == NULL){
        rootPtr = new DecisionTreeNode();
    }*/
    //Set all used features and used features to true.
    for(int i = 0; i < numSamples; i++){
        usedSamples[i] = true;
    }

    for(int j = 0; j < numFeatures; j++){
        usedFeatures[j] = true;
    }
    trainHelper(rootPtr, data, labels, numSamples, numFeatures, usedFeatures, usedSamples);
}

void DecisionTree::train(const string fileName, const int numSamples, const int theNumFeatures){
    numFeatures = theNumFeatures;
    int allData[numSamples][theNumFeatures+1];

    ifstream inFile;
    inFile.open((fileName+".txt").c_str());
    if (!inFile) {
        cout << "Unable to open file";
    }
    else{
        for (int i=0; i < numSamples; i ++){
            for (int j=0; j < (theNumFeatures+1); j++){
                inFile >> allData[i][j];
            }
        }
    }
    //creating bool array
    bool** data;
    data = new bool* [numSamples];
    for ( int i = 0; i < numSamples; i++ )
        data[i] = new bool [numFeatures];

    int* labels = new int[numSamples];

    for (int m=0; m < numSamples; m ++){
        for (int n=0; n < theNumFeatures+1; n++){
            if(n == theNumFeatures){
                labels[m] = allData[m][n];
            }else{
                if(allData[m][n] == 0)
                    data[m][n] = false;
                else
                    data[m][n] = true;
            }
        }
    }

    //call actual train function
    train((const bool**)data, labels, numSamples, theNumFeatures);

    //deallocations
    for ( int j = 0; j < numSamples; j++ )
        delete [] data[j];

    delete [] data;
    delete []labels;
}

int DecisionTree::predict(const bool* data){
    DecisionTreeNode* ptr = rootPtr;
    int item;
    while(!ptr->getNodeType())
    {
        item = ptr->getItem();
        if(data[item]){
            ptr = ptr->getLeftChildPtr();
        }
        else{
            ptr = ptr->getRightChildPtr();
        }
    }
    return ptr->getItem();
}

double DecisionTree::test(const bool** data, const int* labels, const int numSamples){
    int numCorrect = 0;
    int temp;

    for(int i = 0; i < numSamples; i++){
        temp = predict((const bool*)data[i]);
        if(temp == labels[i]){
            numCorrect++;
        }
    }
    return ((double)numCorrect/(double)numSamples)*100;
}
int DecisionTree::getNumFeatures()const{
    return numFeatures;
}
double DecisionTree::test(const string fileName, const int numSamples){
    const int theNumFeatures = getNumFeatures();
    int allData[numSamples][theNumFeatures+1];

    ifstream inFile;
    inFile.open((fileName+".txt").c_str());
    if (!inFile) {
        cout << "Unable to open file";
    }
    else{
        for (int i=0; i < numSamples; i ++){
            for (int j=0; j < (theNumFeatures+1); j++){
                inFile >> allData[i][j];
            }
        }
    }
    //creating bool array
    bool** data;
    data = new bool* [numSamples];
    for ( int i = 0; i < numSamples; i++ )
        data[i] = new bool [numFeatures];

    int* labels = new int[numSamples];

    for (int m=0; m < numSamples; m ++){
        for (int n=0; n < theNumFeatures+1; n++){
            if(n == theNumFeatures){
                labels[m] = allData[m][n];
            }else{
                if(allData[m][n] == 0)
                    data[m][n] = false;
                else
                    data[m][n] = true;
            }
        }
    }

    //call actual test function
    double result = test((const bool**)data, labels, numSamples);

    //deallocations
    for ( int j = 0; j < numSamples; j++ )
        delete [] data[j];

    delete [] data;
    delete []labels;

    return result;
}

double DecisionTree::calculateEntropy(const int* classCounts, const int numClasses){
    double entropy = 0.;
    double tempEntropy = 0.;
    double tempP = 0.;
    int tot = 0;

    for(int j = 0; j < numClasses ; j++){
        tot += classCounts[j];
    }

    for(int i = 0; i < numClasses ; i++){
        if(classCounts[i] == 0)
  		{
  			tempEntropy = 0.;
  		} else {
  			tempP = (double)classCounts[i]/(double)tot;
  			tempEntropy = -tempP*log2(tempP);
  		}
  		entropy += tempEntropy;
    }
    return entropy;
}

void DecisionTree::getClassInfo(const int numSamples, const int* labels, const bool* usedSamples, int* classCounts, int& numClasses){

    int arrSize = 0;
    //to get know size of an array for used labels.
    for(int i =0; i<numSamples; i++){
        if(usedSamples[i])
            arrSize++;
    }

    if(arrSize != 0){
        int usedLabels[arrSize];
        int j = 0;

        //put the used labels into another array
        for(int k = 0; k < numSamples; k++){
            if(usedSamples[k]){
                usedLabels[j] = labels[k];
                j++;
            }
        }

        //sort the new array
        insertionSort(usedLabels, arrSize);

        //calculate num of classes
        numClasses = 1;
        for(int l = 1; l < arrSize; l++){
            if(usedLabels[l] != usedLabels[l-1]){
                numClasses++;
            }
        }

        //fill the classCounts array
        for(int m = 0; m < numClasses; m++){
            classCounts[m] = 1;
        }

        int index = 0;
        for(int n = 1; n < arrSize; n++){
            if(usedLabels[n] != usedLabels[n-1])
                index++;
            else
                classCounts[index]++;
        }

    }
    else{
        numClasses = 0;
    }

}

double DecisionTree::calculateInformationGain(const bool** data, const int* labels, const int numSamples, const int numFeatures, const bool* usedSamples,
                                const int featureId){
    double entropy1, entropy2, entropy3;
    int *classCount1, *classCount2, *classCount3, numClasses1, numClasses2, numClasses3 ;
    classCount1 = new int[100];
    classCount2 = new int[100];
    classCount3 = new int[100];
    //Calculate entropy before split
    getClassInfo(numSamples, labels, usedSamples, classCount1, numClasses1);
    entropy1 = calculateEntropy(classCount1, numClasses1);

    //create 2 new used samples bool arrays for further use
    bool usedS2[numSamples];
    bool usedS3[numSamples];

    int n2 = 0;
    int n3 = 0;
    for(int i = 0; i < numSamples; i++){
        if(usedSamples[i]){
            if(data[i][featureId]){
                usedS2[i] = true;
                usedS3[i] = false;
                n2++;
            }
            else{
                usedS2[i] = false;
                usedS3[i] = true;
                n3++;
            }
        }
    }

    //calculate entropy of a child nodes
    getClassInfo(numSamples, labels, usedS2, classCount2, numClasses2);
    entropy2 = calculateEntropy(classCount2, numClasses2);

    getClassInfo(numSamples, labels, usedS3, classCount3, numClasses3);
    entropy3 = calculateEntropy(classCount3, numClasses3);
    delete [] classCount1;
    delete [] classCount2;
    delete [] classCount3;
    return entropy1 - double(n2/(n2+n3))*entropy2 - double(n3/(n2+n3))*entropy3;
}

void DecisionTree::insertionSort(int theArray[], int n) {

  for (int unsorted = 1; unsorted < n; ++unsorted) {

    int nextItem = theArray[unsorted];
    int loc = unsorted;

    for (  ;(loc > 0) && (theArray[loc-1] > nextItem); --loc)
       theArray[loc] = theArray[loc-1];

    theArray[loc] = nextItem;
  }
}

void DecisionTree::print(){
    int level = 0;
    preorderPrint(rootPtr, level);
}

void DecisionTree::preorderPrint(DecisionTreeNode* treePtr, int level){
   if (treePtr != NULL) {
        // The root
        int theItem = treePtr->getItem();
        bool type = treePtr->getNodeType();

        for(int i = 0; i < level; i++)
            cout<< "\t";

        if(type){
            cout <<"class = "<<theItem;
        }
        else{
            cout<<"id = "<<theItem;
        }
        cout<<""<<endl;
        level++;
        // The left
        preorderPrint(treePtr->getLeftChildPtr(), level);
        // The right
        preorderPrint(treePtr->getRightChildPtr(), level);
    } // end if
}
