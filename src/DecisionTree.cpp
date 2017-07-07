


#include "DecisionTree.h"
#include "UtilityFunctions.h"
#include "Node.h"
#include <QDebug>
#include <QTextStream>
#include "QFile"

  
DecisionTree::DecisionTree(QObject* parent)
    : QObject(parent)
    , m_usePropability(false)
    , m_treeScalingParameter(nullptr)
{
    m_treeScalingParameter = new TreeScalingParameter(this);
}

DecisionTree::~DecisionTree()
{

}

bool DecisionTree::builtTree(QList<QList<feature>> borders)
{
    if (borders.size() == 0)
        return false;

    m_treeList.append(new Tree(this));
    m_treeList.back()->setUseProbability(m_usePropability);
    return m_treeList.back()->builtTree(borders);
}


float DecisionTree::decide(QVector< double> features, int* layer, int* branch)
{
    if (m_treeList.size() == 0)
        return -1;

    if (features.size() != numFeatures)
        return -1;

    float result = 0;

    float tempResult = 0;
    float tempResult1 = 0;
    float tempResult2 = 0;
    for (int i = 0; i < m_treeList.size(); ++i)
    {
        tempResult = m_treeList[i]->decide(features, layer, branch);
        if (tempResult == 0)
        {
            int test = 0;
        }

        if (tempResult > 0)
        {
            tempResult1 += tempResult;
        }
        else
        {
            tempResult2 += tempResult;
        }
    }

    //qDebug() << "temp1" << tempResult1;
    //qDebug() << "temp2" << tempResult2;

    float reg = 0;
    if (abs(tempResult1) > abs(tempResult2))
    {
        //tempResult1 = m_treeList.size();
        reg = 1;
    }
    else
    {
        //tempResult1 = 0;
        reg = 0;
    }
    return reg;

}

bool DecisionTree::setupTreeClassifier(QString treeStructureFile)
{
    QFile file(treeStructureFile);
    if (!file.exists())
        return false;

    if (!file.open(QFile::ReadOnly))
        return false;

    QTextStream stream(&file);
    int numOfTrees = stream.readLine().trimmed().toInt();
    if (numOfTrees == 0)
        return false;

    m_treeList.reserve(numOfTrees);
    QString line = stream.readLine(); // read the empty line after number of Trees
    if (line.length() != 0)
    {
        qDebug() << "Parsing TreeStructure: Missing blank line";
    }


    for (int i = 0; i < numOfTrees; i++)
    {
		qDebug() << "TreeNumber: " << i;
        m_treeList.append(new Tree(this));
        if (!m_treeList.back()->readTreeStructureFromFile(stream))
            return false;
    }

    file.close();
    return true;
}

bool DecisionTree::scaleFeatures(QVector<double>& features)
{
    if (!m_treeScalingParameter)
        false;

    return m_treeScalingParameter->scaleFeatures(features);

}