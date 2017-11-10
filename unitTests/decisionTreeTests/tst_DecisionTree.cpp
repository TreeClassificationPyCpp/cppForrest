
#include "BoostTest.h"
#include "DecisionTree.h"
#include <fstream>
#include<vector>


TEST(DecisionTreeTests, DecisionTreeTest)
{
    // set up the tree
    DecisionTree* decisionTree = new DecisionTree();

	// enter path to test data and klassifier sturcture
    decisionTree->setupTreeClassifier("treeClassifier_tree.txt");

    std::ifstream data("data_tree.txt");
    std::ifstream predict("test_tree.txt");
    decisionTree->setUseProbability(false);
    std::string line;
    std::vector<double> features;

    //data.open(QFile::ReadOnly);
    //predict.open(QFile::ReadOnly);

    //QTextStream stream(&data);

    std::vector<std::string> splitLine;

    //QTextStream stream2(&predict);
    std::getline(predict, line);
    std::string::size_type prev_pos = 0, pos = 0;

    while ((pos = line.find(' ', pos)) != std::string::npos)
    {
        std::string substring(line.substr(prev_pos, pos - prev_pos));

        splitLine.push_back(substring);

        prev_pos = ++pos;
    }
    std::string lastword = line.substr(prev_pos, pos - prev_pos);
    if (!lastword.empty())
        splitLine.push_back(lastword); // Last word


    //splitLine = stream2.readLine().trimmed().split(" ");


    std::vector<int> predictedLabels;
    predictedLabels.resize(splitLine.size());

    for (int i = 0; i < splitLine.size(); i++)
    {
        predictedLabels[i] = (int)std::stof(splitLine[i]);
    }

    predict.close();
    int of = 0;
    int index = 0;
    while (std::getline(data, line))
    
    //while (!stream.atEnd())
    {
        //line = stream.readLine().trimmed();
        //splitLine = line.split(" ");
        splitLine.clear();
        prev_pos = 0;
        pos = 0;

        while ((pos = line.find(' ', pos)) != std::string::npos)
        {
            std::string substring(line.substr(prev_pos, pos - prev_pos));

            splitLine.push_back(substring);

            prev_pos = ++pos;
        }
        lastword = line.substr(prev_pos, pos - prev_pos);
        if (!lastword.empty())
            splitLine.push_back(lastword); // Last word


        if (index == 2)
            int test = 0;

        features.resize(splitLine.size());

        for (int i = 0; i < splitLine.size(); ++i)
        {
            features[i] = std::stof(splitLine[i]);
        }

        int result = decisionTree->decide(features);
        std::cout << index<< " " << result << " " << predictedLabels[index];
        EXPECT_TRUE(result == predictedLabels[index]);
        
        if (result != predictedLabels[index])
            of++;

        index++;

    }
    data.close();
    EXPECT_TRUE(of == 0);

    delete decisionTree;
}

TEST(DecisionTreeTests, StructureTests1)
{

    int layer = 0;
    int branch = 0;
    DecisionTree* decisionTree = new DecisionTree();

    std::vector<feature> help;
    std::vector<std::vector<feature>> borders;
    //delete decisionTree;
    //decisionTree = new DecisionTree(0);

    help.clear();
    help.push_back(std::make_pair(slope1, 0.5));

    borders.clear();
    borders.push_back(help);
    help.clear();
    help.push_back(std::make_pair(slope2, 0.5));
    help.push_back(std::make_pair(slope3, 0.5));
    borders.push_back(help);


    help.clear();
    help.push_back(std::make_pair(leaf, -1.0));
    help.push_back(std::make_pair(leaf, 1.0));
    help.push_back(std::make_pair(leaf, -1.0));
    help.push_back(std::make_pair(leaf, 1.0));
    borders.push_back(help);


    decisionTree->setUseProbability(false);
    decisionTree->builtTree(borders);

    std::vector<double> features;
    features.clear();
    features.resize(slope1 + 1);
    features[slope1] = 0.1;
    features[slope2] = 0.1;
    features[slope3] = 0.1;

    int result = decisionTree->decide(features, &layer, &branch);
    EXPECT_TRUE(result == 0);
    EXPECT_TRUE(layer == 2);
    EXPECT_TRUE(branch == 0);

    features.clear();
    features.resize(slope1 + 1);
    features[slope1] = 0.1;
    features[slope2] = 0.6;
    features[slope3] = 0.1;

    result = decisionTree->decide(features, &layer, &branch);
    EXPECT_TRUE(result == 1);
    EXPECT_TRUE(layer == 2);
    EXPECT_TRUE(branch == 1);

    features.clear();
    features.resize(slope1 + 1);
    features[slope1] = 0.6;
    features[slope2] = 0.1;
    features[slope3] = 0.1;

    result = decisionTree->decide(features, &layer, &branch);
    EXPECT_TRUE(result == 0);
    EXPECT_TRUE(layer == 2);
    EXPECT_TRUE(branch == 2);

    features.clear();
    features.resize(slope1 + 1);
    features[slope1] = 0.6;
    features[slope2] = 0.1;
    features[slope3] = 0.6;

    result = decisionTree->decide(features, &layer, &branch);
    EXPECT_TRUE(result == 1);
    EXPECT_TRUE(layer == 2);
    EXPECT_TRUE(branch == 3);
}
