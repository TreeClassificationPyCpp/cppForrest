


#include "DecisionTree.h"
//#include "UtilityFunctions.h"
#include "Node.h"
#include <experimental/filesystem>

#include <string>
#include <iostream>
#include <fstream>
  
#include <algorithm> 
#include <functional> 
#include <cctype>
#include <locale>

DecisionTree::DecisionTree()
    : m_usePropability(false)
    , m_treeScalingParameter(nullptr)
{
    m_treeScalingParameter = new TreeScalingParameter();
}

DecisionTree::~DecisionTree()
{
    if (m_treeScalingParameter != nullptr)
    {
        delete m_treeScalingParameter;
        m_treeScalingParameter = nullptr;
    }
}

bool DecisionTree::builtTree(std::vector<std::vector<feature>> borders)
{
    if (borders.size() == 0)
        return false;

    m_treeList.push_back(new Tree());
    m_treeList.back()->setUseProbability(m_usePropability);
    return m_treeList.back()->builtTree(borders);
}


float DecisionTree::decide(std::vector< double> features, int* layer, int* branch)
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

bool DecisionTree::setupTreeClassifier(std::string treeStructureFile)
{
    if (!std::experimental::filesystem::exists(treeStructureFile))
        return false;
    std::ifstream file;
    file.open(treeStructureFile);
    std::string line;
    //QTextStream stream(&file);
    std::getline(file, line);
    line.erase(line.begin(), std::find_if(line.begin(), line.end(),
        std::not1(std::ptr_fun<int, int>(std::isspace))));
    int numOfTrees = std::stoi(line);
    if (numOfTrees == 0)
        return false;

    //m_treeList.resize(numOfTrees);
    
    std::getline(file, line);
    //std::string line = (file.getline()); // stream.readLine(); // read the empty line after number of Trees
    if (line.length() != 0)
    {
        std::cout << "Parsing TreeStructure: Missing blank line";
    }


    for (int i = 0; i < numOfTrees; i++)
    {
        std::cout << "TreeNumber: " << i;
        m_treeList.push_back(new Tree());
        if (!m_treeList.back()->readTreeStructureFromFile(file))
            return false;
    }

    file.close();
    return true;
}

bool DecisionTree::scaleFeatures(std::vector<double>& features)
{
    if (!m_treeScalingParameter)
        false;

    return m_treeScalingParameter->scaleFeatures(features);

}