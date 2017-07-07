from __future__ import division, print_function, absolute_import

import numpy as np
import ConfigParser

def writeLayer(nodeList, classList, features, border, children_left, children_right, samplesInLeaf, file):
    print("writeLayer")
    nextList = []
    nextClassList = []
    test = False
    for i in range(0, len(nodeList)):
        node = nodeList[i]
        sign = classList[i]

        if(node < 0): #leaf
            file.write("NA NA ")
            nextList.append(-1)
            nextList.append(-1)
            nextClassList.append(0)
            nextClassList.append(0)

        elif (features[node] == -2): # last node before leaf children_left[node_id] != children_right[node_id]

            file.write(str(features[node]) + " " + str(samplesInLeaf[node,0]) + " ")# + ";R" + str(samplesInLeaf[node,0]) + " ")
            nextList.append(-1)
            nextList.append(-1)
            nextClassList.append(0)
            nextClassList.append(0)
            test = True

        elif (features[node] != -2):
            file.write(str(features[node])+" "+str(border[node]) + " ")
            nextList.append(children_left[node])
            nextList.append(children_right[node])
            nextClassList.append(-1)
            nextClassList.append(1)
            test = True

    file.write("\n")

    if test == True:
        writeLayer(nextList, nextClassList, features, border, children_left, children_right, samplesInLeaf, file)


###################################################################################################################
# export DecisionTree/RandomForrest Klassifier to dateiNameAndPathClassifier.txt file
#
# clf - instanze of the trained sklearn DecisionTree/RandomForrest Klassifier
# scaler - instance of a fitted sklearn StandartScaler
# featuresNames - list of feature names in the same order as they are stored in
# dateiNameAndPathClassifier - string with path and file name of *.txt file to write the classifier strukture
# dateiNameAndPathScaler - string with path and file name of *.ini file to write the scaler
# forrest - bool that has to be set to true if clf is a RandomForrest
# trainingsData - contains the data that was used to train the classifier - > needed to calculate propabilities of leafes in RandomForrest
#
###################################################################################################################

def exportTreeClassifier(clf, scaler, featuresNames, dateiNameAndPathClassifier, dateiNameAndPathScaler, forrest, trainingData):

    # export scaler
    mean = scaler.mean_
    std = scaler.std_

    cfgfile = open(dateiNameAndPathScaler,'w')

    # save scaling parameter
    Config = ConfigParser.ConfigParser()
    paramNames = list(featuresNames.columns.values)

    Config.add_section('features')
    Config.set("features", "number", str(len(paramNames)))

    for i in range(0, mean.shape[0]):
        Config.set('features', str(i), paramNames[i])
        Config.add_section(paramNames[i])
        Config.set(paramNames[i],"mean", str(mean[i]))
        Config.set(paramNames[i],"std", str(std[i]))

    Config.write(cfgfile)
    cfgfile.close()

    # export tree
    if forrest:
        treeList = clf.estimators_
    else:
        treeList = [clf.tree_]

    treeParamList = []
    leaveList = []
    file = open(dateiNameAndPathClassifier, 'w')
    file.write(str(len(treeList))+ "\n")

    for treeN in range(0, len(treeList)):
        if forrest:
            n_nodes = treeList[treeN].tree_.node_count
            children_left = treeList[treeN].tree_.children_left
            children_right = treeList[treeN].tree_.children_right
            feature = treeList[treeN].tree_.feature
            threshold = treeList[treeN].tree_.threshold
        else:
            n_nodes = treeList[treeN].node_count
            children_left = treeList[treeN].children_left
            children_right = treeList[treeN].children_right
            feature = treeList[treeN].feature
            threshold = treeList[treeN].threshold

        node_depth = np.zeros(shape=n_nodes)
        is_leaves = np.zeros(shape=n_nodes, dtype=bool)
        stack = [(0, -1)]  # seed is the root node id and its parent depth

        while len(stack) > 0:
            node_id, parent_depth = stack.pop()
            node_depth[node_id] = parent_depth + 1

            # If we have a test node
            if (children_left[node_id] != children_right[node_id]):
                stack.append((children_left[node_id], parent_depth + 1))
                stack.append((children_right[node_id], parent_depth + 1))
            else:
                is_leaves[node_id] = True

        treeParamList.append(node_depth)

        nodeList = [0]

        samplesInLeaf = np.zeros([n_nodes, 1])
        probOfLeaf = np.zeros([n_nodes, 1])
        leafCounter = np.zeros([n_nodes, 1])

        leave_id = treeList[treeN].apply(trainingData.astype(np.float32))

        predicted=clf.predict(trainingData)
        propability = clf.predict_proba(trainingData)
        index = 0
        for leaf in leave_id:
            if predicted[index] == 1:
                samplesInLeaf[leaf] = samplesInLeaf[leaf] + 1
                probOfLeaf[leaf,0] = probOfLeaf[leaf,0] +  propability[leaf, 0]
                leafCounter[leaf,0] = leafCounter[leaf,0] + 1
            else:
                samplesInLeaf[leaf] = samplesInLeaf[leaf] - 1
                probOfLeaf[leaf,0] = probOfLeaf[leaf,0] -  propability[leaf, 0]
                leafCounter[leaf,0] = leafCounter[leaf,0] + 1

            index = index + 1

        for i in range(0, n_nodes):
            probOfLeaf[i,0] = probOfLeaf[i,0] / leafCounter[i,0]

        samplesInLeaf = samplesInLeaf

        classList = [1]
        file.write("\n")
        writeLayer(nodeList, classList, feature, threshold, children_left, children_right, samplesInLeaf, file)
    file.close()