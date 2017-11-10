#include "Tree.h"
//#include "UtilityFunctions.h"
#include "Node.h"

#include <string>
#include <iostream>
#include <fstream>

#include <algorithm> 
#include <functional> 
#include <cctype>
#include <locale>


Tree::Tree()
    : m_root(nullptr)
    , m_numberOfNodes(0)
    , m_nodesAdded(0)
    , m_useProps(true)
{

}

Tree::~Tree()
{

}

bool Tree::builtTree(std::vector<std::vector<feature> > borders)
{
    if (borders.size() == 0)
        return false;

    m_borders = borders; // safe borders
    countNodes();        // count nodes for 

	if (m_root)
	{
		delete (m_root);
		m_root == NULL;
	}
    m_nodesAdded = 0;

    // create node, set feature and position
    m_root = new Node(nullptr);
    m_root->setBorder(borders[0][0]);
    m_root->m_branch = 0;
    m_root->m_layer = 0;

    nodeAdded(); // count node


    if (borders.size() == 1) // if tree has just one node return
        return true;

    //qDebug() << "set childs to root.";
    addChild(m_root, 1, 0); // add childs to root

    return true;
}

float Tree::decide(std::vector< double> features, int* layer, int* branch)
{
    if (m_root == nullptr)
        return -1;

    if (m_useProps)
    {
        float result = -1;
        m_root->decide(features, result, layer, branch);
        return result;
    }
    else
    {
        int result = -1;
        m_root->decide(features, result, layer, branch);
        return (float)result;
    }
}

void Tree::addChild(Node* parent, int layer, int branch)
{
    if (m_nodesAdded >= m_numberOfNodes)
        return;

    //qDebug() << "layer: " << layer << "branch: " << branch;

    Node* child = new Node(parent);

    child->m_branch = branch;
    child->m_layer = layer;


    if (m_borders[layer][branch].first == leaf)
    {
        child->m_returnValue = m_borders[layer][branch].second;
        child->setBorder(m_borders[layer][branch]);

    }
    else
    {
        child->setBorder(m_borders[layer][branch]);
    }


    child->m_branchNumberOfFirstChild = getBranchNumberOfFirstChild(layer, branch);
    parent->setChildren(child);

    int newLayer = 0;
    int newBranch = 0;

    if (!nodeAdded())
        return;


    if (parent->getNumberOfChildren() < 2 && parent->m_border.first != leaf)
    {
        if (!nextBranch(layer, branch, newBranch))
            return;

        //qDebug() << "second child layer: " << layer << "branch: " << newBranch;
        addChild(parent, layer, newBranch);
    }



    if (!nextLayer(child->m_layer, newLayer))
        return;

    if (m_borders[newLayer][2 * child->m_branch].first != nada && child->m_border.first != leaf)
    {
        //qDebug() << "child as parent layer: " << newLayer << "branch: " << 2 * child->m_branchNumberOfFirstChild;
        addChild(child, newLayer, 2 * child->m_branch);
    }

}

void Tree::countNodes()
{
    m_numberOfNodes = 0;

    for (int l = 0; l < m_borders.size(); l++)
    {
        m_NodesInLayer.push_back(0);
        for (int b = 0; b < m_borders[l].size(); b++)
        {

            if (m_borders[l][b].first != nada)
            {
                m_numberOfNodes++; // count number of nodes
                m_NodesInLayer[l]++; // count number of nodes in layer
            }
        }
    }
}


bool Tree::nodeAdded()
{
    m_nodesAdded++;
    if (m_nodesAdded < m_numberOfNodes)
    {
        return true;
    }
    else
    {
        return false;
    }
}


bool Tree::nextBranch(int layer, int branch, int& newBranch)
{
    if (branch < m_borders[layer].size() - 1)
    {
        newBranch = branch + 1;
        return true;
    }
    else
    {
        return false;
    }
}

bool Tree::nextLayer(int layer, int& newLayer)
{
    if (layer < m_borders.size() - 1)
    {
        newLayer = layer + 1;
        return true;
    }
    else
    {
        return false;
    }

}


int Tree::getBranchNumberOfFirstChild(int layer, int branch)
{
    if (layer + 1 == m_borders.size())
    {
        return -1;
    }


    int balancedTreeBranchIndex = 2 * branch;
    int firstChildBranchIndex = 0;

    for (int i = 0; i < balancedTreeBranchIndex; i++)
    {
        if (m_borders[layer + 1][i].first != nada)
        {
            firstChildBranchIndex++;
        }
    }

    return firstChildBranchIndex;
}


bool Tree::readTreeStructureFromFile(std::ifstream& stream)
{
    std::string line;
    std::getline(stream, line);
    line.erase(line.begin(), std::find_if(line.begin(), line.end(),
        std::not1(std::ptr_fun<int, int>(std::isspace))));
    //QString line = stream.readLine().trimmed();
    std::vector<std::string> splitList;

    m_borders.clear();

    while (line.length() != 0)
    { 
    
        std::string::size_type prev_pos = 0, pos = 0;
        splitList.clear();
        while ((pos = line.find(' ', pos)) != std::string::npos)
        {
            std::string substring(line.substr(prev_pos, pos - prev_pos));

            splitList.push_back(substring);

            prev_pos = ++pos;
        }
        std::string lastword = line.substr(prev_pos, pos - prev_pos);
        if (!lastword.empty())
            splitList.push_back(lastword); // Last word

        //splitList = line.split(" ");
        std::vector<feature> list;

        div_t divresult = div(splitList.size(), 2);
        if (divresult.rem != 0)
        {
            std::cout << "line length not even";
            break;
        }

        for (int i = 0; i < divresult.quot; ++i)
        {
            decisionTreeFeatures feature = nada;
            float thershold = 0;


            if (splitList[2 * i].compare("NA") != 0)
            {
                feature = (decisionTreeFeatures)std::stoi(splitList[2 * i]);
                thershold = std::stof(splitList[2 * i + 1]);
            }


            list.push_back(std::make_pair(feature, thershold));
        }

        m_borders.push_back(list);
        //line = stream.readLine().trimmed();
        std::getline(stream, line);
        line.erase(line.begin(), std::find_if(line.begin(), line.end(),
            std::not1(std::ptr_fun<int, int>(std::isspace))));
    }

    m_borders.pop_back();// last line does not contain any information
    bool test = builtTree(m_borders);
    return test;
}