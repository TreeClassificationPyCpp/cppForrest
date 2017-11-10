#include "TreeScalingParameter.h"

#include <iostream>
#include "INIReader.h"

TreeScalingParameter::TreeScalingParameter()
    //: m_emgBiSensitivity(0.0)
{

}

TreeScalingParameter::~TreeScalingParameter()
{

}


bool TreeScalingParameter::setIniFile(const std::string& filePathAndName)
{


    INIReader reader(filePathAndName);
    if (reader.ParseError() < 0) {
        std::cerr << "Can't load 'test.ini'\n";
        return false;
    }



    int featureNumber = reader.GetInteger("features", "number", -1);
    m_min.resize(featureNumber);
    m_max.resize(featureNumber);
    m_range.resize(featureNumber);


    std::string help;
    for (int i = 0; i < featureNumber; ++i)
    {
        help = std::to_string(i);

        //help = "features." + help;
        //std::string str = help.toStdString();
        //std::string feature = pt.get<std::string>(str);
        //m_scalingParameter.featureOrder.append(QString::fromStdString(feature));

        m_min[i] = reader.GetReal(help, "min", -1); 


        m_max[i] = reader.GetReal(help, "max", -1); 

        m_range[i] = reader.GetReal(help, "range", -1);
    }

    return true;
}

bool TreeScalingParameter::scaleFeatures(std::vector<double>& features)
{
    if (features.size() != m_range.size())
        return false;

    float X_std = 0;
    for (int i = 0; i < m_range.size(); i++)
    {
        X_std = (features[i] - m_min[i] - ((m_range[i]) / 2)) / (m_range[i]) * 2;
        features[i] = X_std;
    }

    return true;
}