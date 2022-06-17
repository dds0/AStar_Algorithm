#include "propertyhelper.h"


QString PropertyHelper::setStartWindowIconStyle() // поменять вверху плашку
{
    setQTabWidgetStyle();
    return "QWidget{"
           "background-color: #525354;}";
}

QString PropertyHelper::setQTabWidgetStyle() // убрать границы
{
    return "QTabWidget{"
           //"background-color: rgb(46, 47, 48);"
           "border: none;"
           "}"
           "QTabWidget::pane{"
           "border:none"
           "}";
}

QString PropertyHelper::forComboBox()
{
    return "QComboBox{"
           "    background: none;"
           "    font-family: 'Helvetica-Bold';"
           "    font: 700 16px;"
           "}"
           "QPushButton::hover{"
           "background-color: #c4c4c4}"
           "QPushButton::pressed{"
           "background: none;}"
            ;
}

QString PropertyHelper::forRadioButton()
{
    return "QRadioButton{"
           "    font-family: 'Helvetica-Bold';"
           "    font: 700 16px;"
           "}"
           "QPushButton::hover{"
           "background-color: #c4c4c4}"
           "QPushButton::pressed{"
           "background: none;}"
            ;
}

QString PropertyHelper::forLabel()
{
    return "QLabel{"
           "    font-family: 'Helvetica-Bold';"
           "    font: 700 16px;"
           "}";
}

QString PropertyHelper::setStartPoint()
{
    return "QPushButton{"
                "  border:none;"
                //"  background-color: #c4c4c4;"
                "  background-image: url(:/resourses/images/modify_start.png); "
                "  background-repeat: no-repeat;"
                "  background-position: center center;"
                "}";
}

QString PropertyHelper::setEndPoint()
{
    return "QPushButton{"
                "  border:none;"
                //"  background-color: #c4c4c4;"
                "  background-image: url(:/resourses/images/modify_finish.png); "
                "  background-repeat: no-repeat;"
                "  background-position: center center;"
                "}";
}

QString PropertyHelper::setRiver()
{
    return "QPushButton{"
                "  border:none;"
                //"  background-color: #c4c4c4;"
                "  background-image: url(:/resourses/images/modify_river.png); "
                "  background-repeat: no-repeat;"
                "  background-position: center center;"
                "}";
}

QString PropertyHelper::setForest()
{
    return "QPushButton{"
                "  border:none;"
                //"  background-color: #c4c4c4;"
                "  background-image: url(:/resourses/images/modify_forest.png); "
                "  background-repeat: no-repeat;"
                "  background-position: center center;"
                "}";
}

QString PropertyHelper::setMountain()
{
    return "QPushButton{"
                "  border:none;"
                //"  background-color: #c4c4c4;"
                "  background-image: url(:/resourses/images/modify_mountain.png); "
                "  background-repeat: no-repeat;"
                "  background-position: center center;"
                "}";
}

QString PropertyHelper::setNormalLeft()
{
    return "QPushButton{"
            "   background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0.0284091, stop:0 rgba(62, 70, 81, 255), stop:1 rgba(92, 100, 111, 255));"
            "   background-image: url(:/resourses/images/krest.png);"
            "   background-repeat:no-repeat;"
            "   background-position: center center;"
            "   border:1px solid #333;"
            "   border-top-left-radius:5px;"
            "   border-bottom-left-radius:5px;"
            "}";
}

QString PropertyHelper::setNormalRight()
{
    return "QPushButton{"
            "   background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0.0284091, stop:0 rgba(62, 70, 81, 255), stop:1 rgba(92, 100, 111, 255));"
            "   background-image: url(:/resourses/images/galka.png);"
            "   background-repeat:no-repeat;"
            "   background-position: center center;"
            "   border:1px solid #333;"
            "   border-left:none;"
            "   border-top-right-radius:5px;"
            "   border-bottom-right-radius:5px;"
            "}";
}

QString PropertyHelper::setActiveLeft()
{
    return "QPushButton{"
            "   background-color: #f87878;"
            "   background-image: url(:/resourses/images/krest.png);"
            "   background-repeat:no-repeat;"
            "   background-position: center center;"
            "   border:1px solid #333;"
            "   border-top-left-radius:5px;"
            "   border-bottom-left-radius:5px;"
            "}";
}

QString PropertyHelper::setActiveRight()
{
    return "QPushButton{"
            "   background-color: #6b8652;"
            "   background-image: url(:/resourses/images/galka.png);"
            "   background-repeat:no-repeat;"
            "   background-position: center center;"
            "   border:1px solid #333;"
            "   border-left:none;"
            "   border-top-right-radius:5px;"
            "   border-bottom-right-radius:5px;"
           "}";
}

QString PropertyHelper::setRoute() //#91a2ac
{
    return "QPushButton{"
           "background-color: //#91a2ac;"
           "}";
}

QString PropertyHelper::forForest()
{
    return "QPushButton{"
                "  border:none;"
                "  background-color: #91a2ac;"
                "  background-image: url(:/resourses/images/modify_forest.png); "
                "  background-repeat: no-repeat;"
                "  background-position: center center;"
           "}";
}

QString PropertyHelper::forRiver()
{
    return "QPushButton{"
                "  border:none;"
                "  background-color: #91a2ac;"
                "  background-image: url(:/resourses/images/modify_river.png); "
                "  background-repeat: no-repeat;"
                "  background-position: center center;"
                "}";
}

QString PropertyHelper::forMountain()
{
    return "QPushButton{"
                "  border:none;"
                "  background-color: #91a2ac;"
                "  background-image: url(:/resourses/images/modify_mountain.png); "
                "  background-repeat: no-repeat;"
                "  background-position: center center;"
                "}";
}

QString PropertyHelper::forSimpleButton()
{
    return "QPushButton{"
           "    background-color: #91a2ac;"
           "}"
            ;
}

QString PropertyHelper::setStartButtonStyle() // убрать границы кнопок, хз как сделать
{
    return "QPushButton{"
           "    background: none;"
           "    background-image: none;"
           "    color: #2e2f30;"
           "    background: none;"
           "    font-family: 'Helvetica-Bold';"
           "    font: 700 16px;"
           "}"
           "QPushButton::hover{"
           "    background-color: #c4c4c4}"
           "QPushButton::pressed{"
           "    background: none;}"
            ;
}
