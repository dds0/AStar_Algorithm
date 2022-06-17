#include "widget.h"
#include "ui_widget.h"
#include "propertyhelper.h"
#include <QTabBar>
#include <list>
#include <fstream>
#include <iostream>
#include <QFileDialog>
#include <QFontDatabase>
#include <QDebug>
#include <QGridLayout>

void Widget::setPropertyRadioButtons()
{
    ui->river->setVisible(false);
    ui->mountain->setVisible(false);
    ui->forest->setVisible(false);

    ui->river->setStyleSheet(PropertyHelper::forRadioButton());
    ui->forest->setStyleSheet(PropertyHelper::forRadioButton());
    ui->mountain->setStyleSheet(PropertyHelper::forRadioButton());

    //ui->rb_start->setVisible(false);
    //ui->rb_finish->setVisible(false);

    ui->rb_start->setStyleSheet(PropertyHelper::forRadioButton());
    ui->rb_finish->setStyleSheet(PropertyHelper::forRadioButton());
}

void Widget::setPropertyPushButtons()
{
    // приконектить кнопки, добавить новые стили для радиобаттанов(улучшения)
////////////////////////////////////////////////////////////////////////////////////////////
    ui->tab->setStyleSheet(PropertyHelper::setStartButtonStyle());
    ui->tab_2->setStyleSheet(PropertyHelper::setStartButtonStyle());

    ui->start->setStyleSheet(PropertyHelper::setStartButtonStyle());
    ui->clear->setStyleSheet(PropertyHelper::setStartButtonStyle());
    ui->Information->setStyleSheet(PropertyHelper::setStartButtonStyle());
    ui->donwload->setStyleSheet(PropertyHelper::setStartButtonStyle());
    ui->save->setStyleSheet(PropertyHelper::setStartButtonStyle());
    ui->NEXT->setStyleSheet(PropertyHelper::setStartButtonStyle());

    ui->startOff->setStyleSheet(PropertyHelper::setActiveLeft());
    ui->startOn->setStyleSheet(PropertyHelper::setNormalRight());
    ui->endOff->setStyleSheet(PropertyHelper::setActiveLeft());
    ui->endOn->setStyleSheet(PropertyHelper::setNormalRight());

    // отдельно сделать обработку визуала
    //ui->startOn->setVisible(false);
    //ui->startOff->setVisible(false);
    //ui->endOn->setVisible(false);
    //ui->endOff->setVisible(false);

    ui->start->setVisible(false);
    ui->clear->setVisible(false);
    ////ui->donwload->setVisible(false);
    ui->save->setVisible(false);
}

void Widget::pairButtonsLogic()
{
    if (isStartPointEnable)
    {
        ui->startOff->setStyleSheet(PropertyHelper::setNormalLeft());
        ui->startOn->setStyleSheet(PropertyHelper::setActiveRight());
    }
    else
    {
        ui->startOff->setStyleSheet(PropertyHelper::setActiveLeft());
        ui->startOn->setStyleSheet(PropertyHelper::setNormalRight());
    }

    if (isEndPointEnable)
    {
        ui->endOff->setStyleSheet(PropertyHelper::setNormalLeft());
        ui->endOn->setStyleSheet(PropertyHelper::setActiveRight());
    }
    else
    {
        ui->endOff->setStyleSheet(PropertyHelper::setActiveLeft());
        ui->endOn->setStyleSheet(PropertyHelper::setNormalRight());
    }
}

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->isNextChecked = false;
    ui->tabWidget->tabBar()->hide();
    ui->tabWidget->setCurrentIndex(0);

    setInterfaceStyle();
    connectAllButtonforCurrentTabWidget();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p,this);
    QWidget::paintEvent(event);
}


void Widget::on_setSIZE_activated(int index)
{
    ui->tabWidget->setCurrentIndex(index);//здесь сделать дисконнект кнопок на всякий случай, затем приконектить остальные
}


void Widget::on_Information_clicked()
{
    if (ui->tabWidget->currentIndex() != 2)
    {
        currentID_tapWidget = ui->tabWidget->currentIndex();
        ui->tabWidget->setCurrentIndex(2);
    }
    else
        ui->tabWidget->setCurrentIndex(currentID_tapWidget);
}

void Widget::setInterfaceStyle()
{
    ui->tabWidget->setStyleSheet(PropertyHelper::setQTabWidgetStyle());

    ui->upgrade->setVisible(false);
    ui->setSIZE->setVisible(false);
    ui->label_setSIZE->setVisible(false);

    QFontDatabase::addApplicationFont("url(:/resourses/fonts/Helvetica-Bold.ttf)");
    this->setStyleSheet(PropertyHelper::setStartWindowIconStyle());

    ui->setSIZE->setStyleSheet(PropertyHelper::forComboBox());
    ui->upgrade->setStyleSheet(PropertyHelper::forLabel());
    ui->label_setSIZE->setStyleSheet(PropertyHelper::forLabel());

    //ui->upgrade->setVisible(false);

    setPropertyRadioButtons();
    setPropertyPushButtons();
}


void Widget::on_NEXT_clicked()
{
    if (isStartPointEnable && isEndPointEnable)
    {
        isNextChecked = true;

        //ui->setSIZE->setVisible(false);
        ui->NEXT->setVisible(false);
       // ui->label_setSIZE->setVisible(false);
        ui->rb_start->setChecked(false);
        ui->rb_finish->setChecked(false);

        ui->startOn->setDisabled(true);
        ui->startOff->setDisabled(true);
        ui->endOn->setDisabled(true);
        ui->endOff->setDisabled(true);

        ui->upgrade->setVisible(true);
        ui->start->setVisible(true);
        ui->clear->setVisible(true);
        //ui->donwload->setVisible(true);
        ui->save->setVisible(true);
        ui->river->setVisible(true);
        ui->mountain->setVisible(true);
        ui->forest->setVisible(true);
    }
}


void Widget::on_clear_clicked()
{
    ui->donwload->setVisible(true);
    ui->NEXT->setVisible(true);
    isNextChecked = false;
    isStart = false;
    //ui->label_setSIZE->setVisible(true);

    setInterfaceStyle();

    QGridLayout *grid = qobject_cast <QGridLayout*>(ui->tab->layout());
    for(int row=0; row < EnumRows; row++)
    {
        for(int column=0; column < EnumColumns; column++)
        {
             QPushButton *btn = qobject_cast <QPushButton*>(grid->itemAtPosition(row, column)->widget());
             btn->setStyleSheet(PropertyHelper::setStartButtonStyle());
             this->rs.setTerrain_ComplexityFactor(row,column,1);
        }
    }
    isStartPointEnable = false;
    isEndPointEnable = false;

    rs.setStandartProperties();

}

void Widget::connectAllButtonforCurrentTabWidget()
{
    //this->rs.setStartSize(5,7);
    QGridLayout *grid = qobject_cast <QGridLayout*>(ui->tab->layout());
    for(int row=0; row < EnumRows; row++)
    {
        for(int column=0; column < EnumColumns; column++)
        {
             QPushButton *btn = qobject_cast <QPushButton*>(grid->itemAtPosition(row, column)->widget());
             btn->setProperty("row", row);
             btn->setProperty("column", column);
             connect(btn, &QPushButton::clicked, this, &Widget::onAreaButtonClicked);
        }
    }
}


void Widget::on_start_clicked()
{
    isStart = true;
    ui->save->setVisible(false);
    ui->donwload->setVisible(false);
    rs.start();
    std::list<controlBlock*> list = rs.giveRoute();
    QGridLayout *grid = qobject_cast <QGridLayout*>(ui->tab->layout());

    for (const auto& s: list) {

        qDebug() << s->test.getI()<<":" <<s->test.getJ();

        QPushButton *btn = qobject_cast <QPushButton*>(grid->itemAtPosition(s->test.getI(), s->test.getJ())->widget());
        switch (s->getTerrain_ComplexityFactor()) {
        case 1:
            btn->setStyleSheet(PropertyHelper::forSimpleButton());
            break;
        case 2:
            btn->setStyleSheet(PropertyHelper::forForest());
            break;
        case 5:
            btn->setStyleSheet(PropertyHelper::forRiver());
            break;
        case 10:
            btn->setStyleSheet(PropertyHelper::forMountain());
            break;
        }
    }
}

void Widget::onAreaButtonClicked()
{
    if (!isStart) // если игра началась
    {
        QPushButton *btn = qobject_cast<QPushButton*>(sender());
        int row = btn->property("row").toInt();
        int column = btn->property("column").toInt();
        if (isNextChecked) // установка препятствий
        {

            if (ui->river->isChecked())
            {
                rs.setTerrain_ComplexityFactor(row,column,5);
                btn->setStyleSheet(PropertyHelper::setRiver());
                qDebug() << row << " : " << column << " - " << 5;
            }
            else if (ui->forest->isChecked())
            {
                rs.setTerrain_ComplexityFactor(row,column,2);
                btn->setStyleSheet(PropertyHelper::setForest());
                qDebug() << row << " : " << column << " - " << 2;
            }
            else if (ui->mountain->isChecked())
            {
                rs.setTerrain_ComplexityFactor(row,column,10);
                btn->setStyleSheet(PropertyHelper::setMountain());
                qDebug() << row << " : " << column << " - " << 10;
            }
        } else { // обработка отправных и конечных точек маршрута

            if (ui->rb_start->isChecked())
            {
                if (rs.getStartPointIndex().first == row && rs.getStartPointIndex().second == column)
                {
                    btn->setStyleSheet(PropertyHelper::setStartButtonStyle());

                    isStartPointEnable = false;
                    pairButtonsLogic();
                }
                else
                {
                    if (helplogicStart == 1)
                    {
                        QGridLayout *grid = qobject_cast <QGridLayout*>(ui->tab->layout());
                        QPushButton *prevBut = qobject_cast <QPushButton*>(grid->itemAtPosition(rs.getStartPointIndex().first, rs.getStartPointIndex().second)->widget());
                        prevBut->setStyleSheet(PropertyHelper::setStartButtonStyle());

                        qDebug() << "old start xy:" << rs.getStartPointIndex().first <<":"<<rs.getStartPointIndex().second;
                    }

                    helplogicStart = 1;
                    btn->setStyleSheet(PropertyHelper::setStartPoint());
                    rs.setStartPoint(row,column);

                    isStartPointEnable = true;
                    pairButtonsLogic();

                    qDebug() << "new start xy:" << row <<":"<<column;
                    qDebug() <<"";
                }
            }

            if (ui->rb_finish->isChecked())
            {
                if (rs.getEndPointIndex().first == row && rs.getEndPointIndex().second == column)
                {
                    btn->setStyleSheet(PropertyHelper::setStartButtonStyle());
                    isEndPointEnable = false;
                    pairButtonsLogic();
                }
                else
                {
                    if (helplogicEnd == 1)
                    {
                        QGridLayout *grid = qobject_cast <QGridLayout*>(ui->tab->layout());
                        QPushButton *prevBut = qobject_cast <QPushButton*>(grid->itemAtPosition(rs.getEndPointIndex().first, rs.getEndPointIndex().second)->widget());
                        prevBut->setStyleSheet(PropertyHelper::setStartButtonStyle());

                        qDebug() << "old end xy:" << rs.getEndPointIndex().first <<":"<<rs.getEndPointIndex().second;
                    }

                    helplogicEnd = 1;

                    btn->setStyleSheet(PropertyHelper::setEndPoint());
                    rs.setEndPoint(row,column);

                    isEndPointEnable = true;
                    pairButtonsLogic();
                    qDebug() << "new end xy:" << row <<":"<<column;
                    qDebug() <<"";
                }
            }
        }

    }
}


void Widget::on_save_clicked()
{
    QString str;
    str = QFileDialog::getSaveFileName(this,"Save file","test","Bin files (*.bin);");

    rs.save(str);
}


void Widget::on_donwload_clicked()
{
    QString str;
    str = QFileDialog::getOpenFileName(this,"Choose file","test","Bin files (*.bin);");

    this->on_clear_clicked();

    QVector<int> v = rs.download(str);
    if (v.empty())
        qDebug()<<"some troubles in method rs.dowload.";
    else
    {
        // установка стилей для местности
        int temp = 3;

        QGridLayout *grid = qobject_cast <QGridLayout*>(ui->tab->layout());
        for(int row=0; row < EnumRows; row++)
        {
            for(int column=0; column < EnumColumns; column++)
            {
                 QPushButton *btn = qobject_cast <QPushButton*>(grid->itemAtPosition(row, column)->widget());
                 rs.setTerrain_ComplexityFactor(row,column,v[++temp]);

                 switch (v[temp]) {
                 case 2:
                     btn->setStyleSheet(PropertyHelper::setForest());
                     break;
                 case 5:
                     btn->setStyleSheet(PropertyHelper::setRiver());
                     break;
                 case 10:
                     btn->setStyleSheet(PropertyHelper::setMountain());
                     break;
                 }
            }
        }


        // проверка на наличие начала маршрута + styleHelper
        QPushButton *btn = qobject_cast <QPushButton*>(grid->itemAtPosition(v[0], v[1])->widget());
        btn->setStyleSheet(PropertyHelper::setStartPoint());
        rs.setStartPoint(v[0],v[1]);

        isStartPointEnable = true;
        pairButtonsLogic();
        // проверка на наличие конца маршрута + styleHelper

        btn = qobject_cast <QPushButton*>(grid->itemAtPosition(v[2], v[3])->widget());
        btn->setStyleSheet(PropertyHelper::setEndPoint());
        rs.setEndPoint(v[2],v[3]);

        isEndPointEnable = true;
        pairButtonsLogic();
    }

}

