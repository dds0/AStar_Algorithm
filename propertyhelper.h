#ifndef PROPERTYHELPER_H
#define PROPERTYHELPER_H
#include <QString>

class PropertyHelper
{
public:
    static QString setStartButtonStyle();   //#ececec
    static QString setStartWindowIconStyle();
    static QString setQTabWidgetStyle();

    static QString forComboBox();
    static QString forRadioButton();
    static QString forLabel();

    static QString setStartPoint();
    static QString setEndPoint();

    static QString setRiver();
    static QString setForest();
    static QString setMountain();

    //for pairButtons
    static QString setNormalLeft();
    static QString setNormalRight();
    static QString setActiveLeft();
    static QString setActiveRight();

    static QString setRoute();

    //indicate route
    static QString forForest();
    static QString forRiver();
    static QString forMountain();
    static QString forSimpleButton();
};

#endif // PROPERTYHELPER_H
