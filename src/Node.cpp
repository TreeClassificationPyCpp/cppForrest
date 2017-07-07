#include "Node.h"
#include <QDebug>

Node::Node(Node* treeParent, QObject* parent)
    : QObject(parent)
    , m_border(nada, 0.0f)
    , m_layer(0.0f)
    , m_branch(0.0f)
    , m_branchNumberOfFirstChild(0.0f)
    , m_returnValue(0.0f)
{     
    m_parent = treeParent;
}

Node::~Node()
{

}


bool Node::setChildren(Node* child)
{
    if (m_children.size() >= 2)
        return false;

    m_children.append(child);
    return true;
}

void Node::decide(QVector<double> values, int& result, int* layer, int* branch)
{

    // if node is a leaf make decision and retunr it
    if (isLeaf())
    {
        result = m_returnValue;

        if (layer != nullptr)
            *layer = m_layer;

        if (branch != nullptr)
            *branch = m_branch;

        return;
    }

    // get its feature - value
    float value = values.at((int)m_border.first);

    if (m_children.size() != 2)
        return;

    // if not is not a leaf make decision and forward decision to next leaf
    if (value <= m_border.second)
    {
        m_children[0]->decide(values, result, layer, branch);
    }
    else
    {
        m_children[1]->decide(values, result, layer, branch);
    }
}

void Node::decide(QVector< double>& values, float& result, int* layer, int* branch)
{



    // if node is a leaf make decision and retun it
    if (isLeaf())
    {
        result = m_returnValue;

        if (layer != nullptr)
            *layer = m_layer;

        if (branch != nullptr)
            *branch = m_branch;

        return;
    }

    // get its feature - value
    float value = values.at((int)m_border.first);

    if (m_children.size() != 2)
        return;

    // if not is not a leaf make decision and forward decision to next leaf
    if (value <= m_border.second)
    {
        m_children[0]->decide(values, result, layer, branch);
    }
    else
    {
        m_children[1]->decide(values, result, layer, branch);
    }
}


