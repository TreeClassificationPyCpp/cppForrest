
#include "BoostTest.h"
#include "DecisionTree.h"

// Qt includes
#include <QObject>
#include <QList>
#include <QDebug>
#include <QString>
#include <QFile>
#include <QTextStream>



TEST(DecisionTreeTests, DecisionTreeTest)
{
    // set up the tree
    DecisionTree* decisionTree = new DecisionTree(0);

	// enter path to test data and klassifier sturcture
    decisionTree->setupTreeClassifier("C://...//treeClassifier_tree.txt");
	QFile data("C://...//data_tree.txt");
	QFile predict("C://...//test_tree.txt");
    decisionTree->setUseProbability(false);

    QVector<double> features;

    data.open(QFile::ReadOnly);
    predict.open(QFile::ReadOnly);

    QTextStream stream(&data);
    QString line;
    QStringList splitLine;

    QTextStream stream2(&predict);
    splitLine = stream2.readLine().trimmed().split(" ");

    QVector<int> predictedLabels;
    predictedLabels.resize(splitLine.size());

    for (int i = 0; i < splitLine.size(); i++)
    {
        predictedLabels[i] = (int)splitLine[i].toFloat();
    }

    predict.close();
    int of = 0;
    int index = 0;
    while (!stream.atEnd())
    {
        line = stream.readLine().trimmed();
        splitLine = line.split(" ");

        if (index == 2)
            int test = 0;

        features.resize(splitLine.size());

        for (int i = 0; i < splitLine.size(); ++i)
        {
            features[i] = splitLine[i].toFloat();
        }

        int result = decisionTree->decide(features);
        qDebug() << index<< " " << result << " " << predictedLabels[index];
        EXPECT_TRUE(result == predictedLabels[index]);
        
        if (result != predictedLabels[index])
            of++;

        index++;

    }
    data.close();
    EXPECT_TRUE(of == 0);

    delete decisionTree;
}

