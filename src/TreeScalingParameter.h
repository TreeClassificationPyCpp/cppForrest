/* Copyright (c) 2017 B.Riebold */

#ifndef TREESCALINGPARAMETER_H
#define TREESCALINGPARAMETER_H


#include <vector>
#include <string>

class TreeScalingParameter 
{

public:
    TreeScalingParameter();
    ~TreeScalingParameter();

    bool setIniFile(const std::string& filePathAndName);
    bool scaleFeatures(std::vector<double>& features);

private:
    std::vector<float> m_range;
    std::vector<float> m_max;
    std::vector<float> m_min;
};

#endif // TREESCALINGPARAMETER_H