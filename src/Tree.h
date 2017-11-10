/* Copyright (c) 2017 B.Riebold */

#ifndef TREE_H
#define TREE_H

#include <vector>
#include "DecisionTree_global.h"
#include <queue>
class Node;

class Tree
{
    

public:

    Tree();
    ~Tree();

    /*
    *   build the decision tree as spezified in borders
    *   QList<QList<feature>> borders - holds all information for tree structure and features with corresponing borders
    */
    bool builtTree(std::vector<std::vector<feature> > borders);

    /*
    *   apply the decision tree to the feature set
    *   QMap<decisionTreeFeatures, float> features - holds the features needed for classification
    *   int* layer - returns layer number of last node in decison path for testing
    *   int* branch - returns branch number of last node in decison path for testing
    */
    float decide(std::vector< double> features, int* layer = nullptr, int* branch = nullptr);
    

    void setUseProbability(bool probs){ m_useProps = probs; }


    bool readTreeStructureFromFile(std::ifstream& stream);


private:
    Node* m_root; // root node of the tree held by this class
    int m_numberOfNodes; // number of nodes in the tree
    int m_nodesAdded;    // number of nodes added while setting up the tree
    std::vector<int> m_NodesInLayer;

    std::vector<std::vector<feature> > m_borders; // set of borders with complete infomation 
    //QList<QList<QPair<float, float>>> m_leafProps;
    bool m_useProps;

    /*
    *   adds a child to the parent node parent with borders(layer, branch)
    *   this function is used to build the tree recusivly
    */
    void addChild(Node* parent, int layer, int branch);

    /*
    *   counts the number of nodes that are containd in m_borders
    */
    void countNodes();

    /*
    *   counts the number of the nodes that were added to the tree
    *   returns false if the number of nodes was reached
    */
    bool nodeAdded();

    /*
    *   increses the branch index with respect to the current layer
    *   if there is no higher branch number the funtion returns false
    */
    bool nextBranch(int layer, int branch, int& newBranch);

    /*
    *   increses the layer
    *   if there is no higher layer number the funtion returns false
    */
    bool nextLayer(int layer, int& newLayer);


    /*
    *   calculates the branch number of the first child of the node
    *   specified by layer and branch
    */
    int getBranchNumberOfFirstChild(int layer, int branch);
};

#endif