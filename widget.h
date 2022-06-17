#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPainter>
#include "routesearcher.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
protected:
    void paintEvent(QPaintEvent *event);

private slots:
    void on_setSIZE_activated(int index);
    void onAreaButtonClicked();

    void on_Information_clicked();

    void on_NEXT_clicked();

    void on_clear_clicked();

    void on_start_clicked();

    void on_save_clicked();

    void on_donwload_clicked();

private:
    Ui::Widget *ui;

    void setInterfaceStyle();
    void setPropertyRadioButtons();
    void setPropertyPushButtons();
    void pairButtonsLogic();

    void connectAllButtonforCurrentTabWidget();

    bool isStartPointEnable = false;
    bool isEndPointEnable = false;

    bool isStart = false;
    bool isNextChecked = false;

    int currentID_tapWidget = 0;
    int helplogicStart = 0;
    int helplogicEnd = 0;

    routeSearcher rs;

};
#endif // WIDGET_H
