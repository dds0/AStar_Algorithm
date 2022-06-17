#ifndef ROUTESEARCHER_H
#define ROUTESEARCHER_H

#include <iostream>
#include <list>
#include <map>
#include <set>
#include <QString>
#include <QWidget>
#include <vector>
#include "controlblock.h"
#include "paircoordinate.h"

#define EnumRows 5
#define EnumColumns 7

class routeSearcher
{
public:
    //void setStartSize(size_t eI, size_t eJ);
    void setStartPoint(int i, int j);
    void setEndPoint(int i, int j);
    void setTerrain_ComplexityFactor(int i, int j, int new_f);
    int getTerrain_ComplexityFactor(int i, int j) const;

    void save(const QString& fileName);
    QVector<int> download(const QString& fileName);

    void setStandartProperties();
    std::pair<int, int>  getStartPointIndex() const;
    std::pair<int, int>  getEndPointIndex() const;

    void start();
    std::list<controlBlock*> giveRoute();

    //int getI() const;
    //int getJ() const;

    //friend bool operator==(routeSearcher rs1, routeSearcher rs2);

private:


    //std::vector<std::vector<controlBlock>> massive;
    controlBlock massive[EnumRows][EnumColumns];

    std::map<controlBlock*, pairCoordinate> FIRST_STEP_check_fill_add(); // добавить ячейки, рядом с активной (вроде в открытый список) //// сделал добавление в промежуточный список
    void SECOND_STEP_addCL_addOL_findMin(std::map<controlBlock*, pairCoordinate> objs);

    void setHeuristicApproximation_for_all_boundary_points(std::map<controlBlock*, pairCoordinate> objs); // установить эвристическое приближение для группы ячеек
    void setPromotionFee_for_all_boundary_points(std::map<controlBlock*, pairCoordinate> objs);
    void setPointers(std::map<controlBlock*, pairCoordinate> objs);
    void resetMassive();

    void setProperties(std::map<controlBlock*, pairCoordinate> objs);
    // запомнить, как мы попали в эту ячейку, установить эвристическое приближение, коэффициент прохождения данной клетки и т.д.

    void setActivePoint();
    bool checkItemForADD(int X, int Y);	// проверка, может ли добавить объект в закрытый список
    bool checkClosedList(int X, int Y); //проверка, входит ли ячейка в закрытый список
    bool checkOpenList(int X, int Y); // проверка, инициализирована ли ячейка, необходима выбора наилучшего пути через эту клетку

    void ISchangeCell(int X, int Y);

    std::map<controlBlock*, pairCoordinate> openList; // ищет по минимальному общему весу
    std::map<controlBlock*, pairCoordinate> closedList; // данные блоки в подсчетах не учавствуют

    std::pair<controlBlock*, pairCoordinate> startPoint;
    std::pair<controlBlock*, pairCoordinate> activePoint;
    std::pair<controlBlock*, pairCoordinate> endPoint;

    bool isSetStartPoint  = false;
    bool isSetEndPoint = false;

};

#endif // ROUTESEARCHER_H
