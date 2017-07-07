#include "TreeScalingParameter.h"

#ifndef Q_MOC_RUN
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/exception/all.hpp>
#include <boost/lexical_cast.hpp>
#endif

#include <QFile>

TreeScalingParameter::TreeScalingParameter(QObject* parent)
    //: m_emgBiSensitivity(0.0)
{

}

TreeScalingParameter::~TreeScalingParameter()
{

}


bool TreeScalingParameter::setIniFile(const QString& filePathAndName)
{
    if (!QFile::exists(filePathAndName))
        return false;


    boost::property_tree::ptree pt;
    try
    {
        boost::property_tree::ini_parser::read_ini(filePathAndName.toStdString(), pt);
    }
    catch (const std::exception&)
    {
        return false;
    }


    int featureNumber = pt.get<int>("features.number");
    m_min.resize(featureNumber);
    m_max.resize(featureNumber);
    m_range.resize(featureNumber);


    QString help;
    QString help2;
    for (int i = 0; i < featureNumber; ++i)
    {
        help.setNum(i);
        //help = "features." + help;
        //std::string str = help.toStdString();
        //std::string feature = pt.get<std::string>(str);
        //m_scalingParameter.featureOrder.append(QString::fromStdString(feature));

        help2 = help + ".min";
        m_min[i] = pt.get<float>(help2.toStdString());

        help2 = help + ".max";
        m_max[i] = pt.get<float>(help2.toStdString());

        help2 = help + ".range";
        m_range[i] = pt.get<float>(help2.toStdString());
    }

    return true;
}

bool TreeScalingParameter::scaleFeatures(QVector<double>& features)
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