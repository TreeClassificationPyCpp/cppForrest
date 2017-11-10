#ifndef DECISIONTREE_GLOBAL_H
#define DECISIONTREE_GLOBAL_H



#define EMG_FEATURES
#include <utility>
#include <map>
#ifdef EMG_FEATURES
enum decisionTreeFeatures
{
    leaf = -2,
    nada = -1,
    saxBI1 = 0,
    saxBI2 = 1,
    saxBI3 = 2,
    saxBI4 = 3,
    saxBI5 = 4,
    saxBI6 = 5,
    saxBI7 = 6,
    saxBI8 = 7,
    saxBI9 = 8,
    saxBI10 = 9,

    saxEMG11 = 10,
    saxEMG12 = 11,
    saxEMG13 = 12,
    saxEMG14 = 13,
    saxEMG15 = 14,
    saxEMG16 = 15,
    saxEMG17 = 16,
    saxEMG18 = 17,
    saxEMG19 = 18,
    saxEMG20 = 19,

    emgSNRtemp = 20,
    emgSNR1 = 21,
    slopeTemp = 22,
    valueRange = 23,
    slope3 = 24,
    slope2 = 25,
    slope1 = 26,
    numFeatures = slope1 + 1
};
#else
enum decisionTreeFeatures
{
    leaf = -2,
    nada = -1,
    saxBI1 = 0,
    saxBI2 = 1,
    saxBI3 = 2,
    saxBI4 = 3,
    saxBI5 = 4,
    saxBI6 = 5,
    saxBI7 = 6,
    saxBI8 = 7,
    saxBI9 = 8,
    saxBI10 = 9,

    saxEMG11 = 10,
    saxEMG12 = 11,
    saxEMG13 = 12,
    saxEMG14 = 13,
    saxEMG15 = 14,
    saxEMG16 = 15,
    saxEMG17 = 16,
    saxEMG18 = 17,
    saxEMG19 = 18,
    saxEMG20 = 19,

    //emgSNRtemp = 20,
    //emgSNR1 = 21,
    slopeTemp = 20,
    valueRange = 21,
    slope3 = 22,
    slope2 = 23,
    slope1 = 24,
    numFeatures = slope1 + 1
};
#endif

typedef std::pair<decisionTreeFeatures, float> feature;


#endif // DECISIONTREE_GLOBAL_H