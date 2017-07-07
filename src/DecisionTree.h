/* Copyright (c) 2017 B.Riebold */

#ifndef DECISIONTREE_H
#define DECISIONTREE_H

#include <QTextStream>
#include <QObject>
#include <QVector>
#include "DecisionTree_global.h"
#include "Tree.h"
#include "TreeScalingParameter.h"
class Node;


class DECISIONTREE_EXPORT DecisionTree : public QObject
{
    Q_OBJECT

public:

    DecisionTree(QObject* parent = 0);
    ~DecisionTree();

    /*
    *   build the decision tree as spezified in borders
    *   QList<QList<feature>> borders - holds all information for tree structure and features with corresponing borders
    */
    bool builtTree(QList<QList<feature>> borders);


    /*
    *   apply the decision tree to the feature set
    *   QVector< float> features - holds the features needed for classification
    *   int* layer - returns layer number of last node in decison path for testing
    *   int* branch - returns branch number of last node in decison path for testing
    */
    float decide(QVector<double> features, int* layer = nullptr, int* branch = nullptr);


    void setUseProbability(bool probs){ m_usePropability = probs; }

    bool setupTreeClassifier(QString treeStructureFile);

    void clearAllTrees(){ m_treeList.clear(); }

    bool setIniFile(const QString& filePathAndName){ 
        return m_treeScalingParameter->setIniFile(filePathAndName); 
    }

    bool scaleFeatures(QVector<double>& features);

    //void setEMgBiSensitivity(double value){ m_treeScalingParameter->setEmgBiSensitivity(value); }

private:
    QList<Tree*> m_treeList;
    bool m_usePropability;
    TreeScalingParameter* m_treeScalingParameter;

public Q_SLOTS:
    


Q_SIGNALS:

};

#endif // FESTRIGGERCAM_H
