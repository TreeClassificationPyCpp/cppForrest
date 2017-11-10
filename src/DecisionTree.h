/* Copyright (c) 2017 B.Riebold */

#ifndef DECISIONTREE_H
#define DECISIONTREE_H


#include <list>
#include <string>
#include <vector>
#include "DecisionTree_global.h"
#include "Tree.h"
#include "TreeScalingParameter.h"
class Node;


class  DecisionTree
{


public:

    DecisionTree();
    ~DecisionTree();

    /*
    *   build the decision tree as spezified in borders
    *   QList<QList<feature>> borders - holds all information for tree structure and features with corresponing borders
    */
    bool builtTree(std::vector<std::vector<feature> > borders);


    /*
    *   apply the decision tree to the feature set
    *   QVector< float> features - holds the features needed for classification
    *   int* layer - returns layer number of last node in decison path for testing
    *   int* branch - returns branch number of last node in decison path for testing
    */
    float decide(std::vector<double> features, int* layer = nullptr, int* branch = nullptr);


    void setUseProbability(bool probs){ m_usePropability = probs; }

    bool setupTreeClassifier(std::string treeStructureFile);

    void clearAllTrees(){ m_treeList.clear(); }

    bool setIniFile(const std::string& filePathAndName){
        return m_treeScalingParameter->setIniFile(filePathAndName); 
    }

    bool scaleFeatures(std::vector<double>& features);

    //void setEMgBiSensitivity(double value){ m_treeScalingParameter->setEmgBiSensitivity(value); }

private:
    std::vector<Tree*> m_treeList;
    bool m_usePropability;
    TreeScalingParameter* m_treeScalingParameter;


};

#endif // FESTRIGGERCAM_H
