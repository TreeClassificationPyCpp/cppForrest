/* Copyright (c) 2017 B.Riebold */

#ifndef NODE_H_
#define NODE_H_



#include <QObject>
#include <QList>
#include <QMap>
#include "DecisionTree_global.h"

class Node : public QObject
{
    Q_OBJECT

public:

    Node(Node* treeParent = nullptr, QObject* parent = 0);
    ~Node();


    /*
    *   returns true if the node is the rood node of a tree, aka has no parent
    */
    inline bool isRoot(){ return m_parent == nullptr; }

    /*
    *   returns true if the node has no childs and for that reason is a leaf
    */
    inline bool isLeaf(){ return m_children.size() == 0; }


    /*
    *   set a node as child to this node
    *   Node* child - pointer to the node that should be added as child
    *   returns true if the child was added, returns false if there are allready two childs attached
    */
    bool setChildren(Node* child);

    /*
    *   gets the feature value from the feature map - values
    *   compares it with th border stored in the node
    *   if this node is a leaf (size of m_children == 0) the function returns, decision is stored into result
    *   other wise the decion is handed allong the tree do the next node in decions path
    *
    *   values - map with feature values
    *   result - to return the result
    *   layer - layer of last node in decion path
    *   branch - branch of last node in decion path
    */
    void decide(QVector<double> values, int& result, int* layer = nullptr, int* branch=nullptr);



    void decide(QVector<double>& values, float& result, int* layer = nullptr, int* branch = nullptr);


    /*
    *   set feature and corresponding boreder to the node
    *   border feater - holds the kind of feature and the border
    */
    void setBorder(feature border){ m_border = border; }

    /*
    *   returns the number of nodes in the children list
    *   maximum number is two, limited is set in setChildren function
    */
    int getNumberOfChildren(){ return m_children.size(); }



    int m_layer; // layer of the node (root is zero)
    int m_branch; // number of the nod in the layer, beginning on the left side starting with zero
    int m_branchNumberOfFirstChild; // holds the index of the first child node, is -1 if this node is a leaf#float 
    QPair<float, float> m_leafPropability; // holds the propability of the leaf in reference to the trainignsdata
    float m_returnValue;
    feature m_border; // holds the kind of feature and the border for the decision in this node

private:
    Node* m_parent; // parent node of this node
    QList<Node*> m_children; // list of children, always two

};

#endif // NODE_H_