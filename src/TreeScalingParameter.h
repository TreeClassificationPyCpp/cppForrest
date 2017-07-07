/* Copyright (c) 2017 B.Riebold */

#ifndef TREESCALINGPARAMETER_H
#define TREESCALINGPARAMETER_H

#include <QObject>
#include <QVector>


class TreeScalingParameter : public QObject
{
    Q_OBJECT

public:
    TreeScalingParameter(QObject* parent);
    ~TreeScalingParameter();

    bool setIniFile(const QString& filePathAndName);
    bool scaleFeatures(QVector<double>& features);

private:
    QVector<float> m_range;
    QVector<float> m_max;
    QVector<float> m_min;
};

#endif // TREESCALINGPARAMETER_H