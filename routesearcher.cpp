#include "routesearcher.h"
#include "controlblock.h"
#include <cmath>
#include <QVector>
#include <algorithm>
#include <QDebug>
#include <fstream>
#include <iostream>
#include <QFileDialog>
using namespace std;


#define CHECK_N_ADD(X,Y) \
    if (this->checkItemForADD(X, Y))\
    {\
        if (this->checkOpenList(X, Y))\
            objs.insert(std::pair<controlBlock*, pairCoordinate>(&massive[X][Y], pairCoordinate(X, Y)));\
        else\
            this->ISchangeCell(X, Y);\
    }



//void routeSearcher::setHeuristicApproximation_for_all_boundary_points()
//{
//	endPoint.first->setHeuristicApproximation(0);
//
//	for (auto& s : openList)
//	{
//		if (s.first->getHeuristicApproximation() == INT_MIN)
//		{
//			s.first->setHeuristicApproximation(base_multiplier * (abs(endPoint.second.getI() - s.second.getI()) + abs(endPoint.second.getJ() - s.second.getJ())));
//		} // без учета перемещения по диагонали ( метод Манхеттена(вроде так нзывается))
//	}
//}

void routeSearcher::setStartPoint(int i, int j)
{
    isSetStartPoint = true;
    startPoint = std::pair<controlBlock*, pairCoordinate>(&massive[i][j],pairCoordinate(i,j));
    startPoint.first->setPromotionFee(0);

    this->setActivePoint();
}

void routeSearcher::setEndPoint(int i, int j)
{
    isSetEndPoint = true;
    endPoint = std::pair<controlBlock*, pairCoordinate>(&massive[i][j], pairCoordinate(i, j));
    endPoint.first->setHeuristicApproximation(0);
}

void routeSearcher::setActivePoint()
{
    activePoint = startPoint;
    activePoint.first->setPromotionFee(0);
}

std::map<controlBlock*, pairCoordinate> routeSearcher::FIRST_STEP_check_fill_add()
{
    std::map<controlBlock*, pairCoordinate> objs;
    // 1,1
    int x = activePoint.second.getI();
    int y = activePoint.second.getJ();
    // 0,0
    CHECK_N_ADD(x - 1, y - 1);
    // 0,1
    CHECK_N_ADD(x - 1, y);
    // 0,2
    CHECK_N_ADD(x - 1, y + 1);
    // 1,0
    CHECK_N_ADD(x, y - 1);
    // 1,2
    CHECK_N_ADD(x, y + 1);
    // 2,0
    CHECK_N_ADD(x + 1, y - 1);
    // 2,1
    CHECK_N_ADD(x + 1, y);
    // 2,2
    CHECK_N_ADD(x + 1, y + 1);

    this->setProperties(objs);
    return objs;

}

void routeSearcher::setHeuristicApproximation_for_all_boundary_points(std::map<controlBlock*, pairCoordinate> objs)
{
    for (auto& s : objs)
        //if (s.first->getHeuristicApproximation() == INT_MIN)
        s.first->setHeuristicApproximation(base_multiplier * (abs(endPoint.second.getI() - s.second.getI()) + abs(endPoint.second.getJ() - s.second.getJ())));
        // без учета перемещения по диагонали ( метод Манхеттена(вроде так нзывается))
}

void routeSearcher::setPromotionFee_for_all_boundary_points(std::map<controlBlock*, pairCoordinate> objs) // сделать проверку, если уже инициализирована ячейка
{
    bool isDiagonal; // если true, то умножаем га 1.4 (чтобы добраться до объекта, идем по диагонали)
    for (auto& m : objs)
    {
        isDiagonal = (m.second.getI() != activePoint.second.getI() && m.second.getJ() != activePoint.second.getJ());

        if (isDiagonal)
            m.first->setPromotionFee(1.4 * base_multiplier * m.first->getTerrain_ComplexityFactor() + activePoint.first->getPromotionFee());
        else
            m.first->setPromotionFee(base_multiplier * m.first->getTerrain_ComplexityFactor() + activePoint.first->getPromotionFee());
    }
}

void routeSearcher::setPointers(std::map<controlBlock*, pairCoordinate> objs)
{
    for (auto& m : objs)
        //if (m.first->getPointerPrevObj() == nullptr)
        m.first->setPrevPointerObj(massive[activePoint.second.getI()][activePoint.second.getJ()]);
}

void routeSearcher::resetMassive()
{
    //controlBlock sM[EnumRows][EnumColumns];
    for (int row = 0; row <EnumRows;row++)
        for(int column = 0; column <EnumColumns; column++)
        {
            massive[row][column] = controlBlock();
        }
}

bool routeSearcher::checkClosedList(int X, int Y)
{
    if (closedList.find(&massive[X][Y]) == closedList.end())
        return true;
    return false;
}

bool routeSearcher::checkOpenList(int X, int Y)
{
    if (openList.find(&massive[X][Y]) == openList.end())
        return true;
    return false;
}

void routeSearcher::setProperties(std::map<controlBlock*, pairCoordinate> objs)
{
    this->setHeuristicApproximation_for_all_boundary_points(objs);
    this->setPromotionFee_for_all_boundary_points(objs);
    this->setPointers(objs);

}

bool routeSearcher::checkItemForADD(int X,int Y)
{
    if ((X >= 0 && X < EnumRows) && (Y >= 0 && Y < EnumColumns) && this->checkClosedList(X, Y))
        return true;
    return false;
}


void routeSearcher::ISchangeCell(int X, int Y)
{

    if (X != activePoint.second.getI() && Y != activePoint.second.getJ())
    {
        if (massive[X][Y].getPromotionFee() > (1.4 * base_multiplier * massive[X][Y].getTerrain_ComplexityFactor() + activePoint.first->getPromotionFee()))
        {
            massive[X][Y].setPromotionFee(1.4 * base_multiplier * massive[X][Y].getTerrain_ComplexityFactor() + activePoint.first->getPromotionFee());
            massive[X][Y].setPrevPointerObj(massive[activePoint.second.getI()][activePoint.second.getJ()]);// установка нового указателя, т.к. маршрут через эту ячейку быстрее
        }
    }
    else
    {
        if (massive[X][Y].getPromotionFee() > (base_multiplier * massive[X][Y].getTerrain_ComplexityFactor() + activePoint.first->getPromotionFee()))
        {
            massive[X][Y].setPromotionFee(base_multiplier * massive[X][Y].getTerrain_ComplexityFactor() + activePoint.first->getPromotionFee());
            massive[X][Y].setPrevPointerObj(massive[activePoint.second.getI()][activePoint.second.getJ()]); // установка нового указателя, т.к. маршрут через эту ячейку быстрее
        }
    }
}

void routeSearcher::SECOND_STEP_addCL_addOL_findMin(std::map<controlBlock*, pairCoordinate> objs)
{
    openList.erase(activePoint.first);
    closedList.insert(activePoint);

    for (auto& m : objs)
        openList.insert(m);

    std::pair<controlBlock*, pairCoordinate> min_element = *openList.begin();

    for (const auto& ol : openList)
    {
        if (ol.first->getTotalWeight() < min_element.first->getTotalWeight())
            min_element = ol;
    }

    activePoint = min_element;
}



void routeSearcher::start()
{
    for (size_t i = 0; i < EnumRows; i++)
    {
        for (size_t j = 0; j < EnumColumns; j++)
        {
            massive[i][j].test.setI(i);
            massive[i][j].test.setJ(j);
        }
    }

    if (isSetStartPoint && isSetEndPoint)
        while (activePoint.first != endPoint.first)
        {
            SECOND_STEP_addCL_addOL_findMin(FIRST_STEP_check_fill_add());
        }
}

std::list<controlBlock*> routeSearcher::giveRoute()
{
    std::list<controlBlock*> destination;

    controlBlock* next = endPoint.first->getPointerPrevObj();

    while (next->getPointerPrevObj() != nullptr)
    {
        destination.push_back(next);
        next = next->getPointerPrevObj();
    }
    return destination;
}

void routeSearcher::setTerrain_ComplexityFactor(int i, int j, int new_f)
{
    massive[i][j].setTerrain_ComplexityFactor(new_f);
}

int routeSearcher::getTerrain_ComplexityFactor(int i, int j) const
{
    return massive[i][j].getTerrain_ComplexityFactor();
}

void routeSearcher::save(const QString& fileName)
{
    std::ofstream file(fileName.toStdString(), std::ios::binary | std::ios::trunc | std::ios::in);

    if (file.is_open())
    {
        int temp;
        if (this->isSetStartPoint)
        {
            temp = this->getStartPointIndex().first;
            file.write(reinterpret_cast<const char*>(&temp), sizeof(temp));
            temp = this->getStartPointIndex().second;
            file.write(reinterpret_cast<const char*>(&temp), sizeof(temp));
        }
        //else
        //{
        //    temp = -1;
        //    file.write(reinterpret_cast<const char*>(&temp), sizeof(temp));
        //    file.write(reinterpret_cast<const char*>(&temp), sizeof(temp));
        //}

        if (this->isSetEndPoint)
        {
            temp = this->getEndPointIndex().first;
            file.write(reinterpret_cast<const char*>(&temp), sizeof(temp));
            temp = this->getEndPointIndex().second;
            file.write(reinterpret_cast<const char*>(&temp), sizeof(temp));
        }
        //else
        //{
        //    temp = -1;
        //    file.write(reinterpret_cast<const char*>(&temp), sizeof(temp));
        //    file.write(reinterpret_cast<const char*>(&temp), sizeof(temp));
        //}

        for (int i = 0; i < 5; ++i)
        {
            for (int j = 0; j < 7; ++j)
            {
                temp = this->massive[i][j].getTerrain_ComplexityFactor();
                file.write(reinterpret_cast<const char*>(&temp),sizeof(temp));
            }
        }

        qDebug() << "File " <<fileName<<" save";
        file.close();
    }
    else
        qDebug() << "File " <<fileName<<" cannot save";
}

QVector<int> routeSearcher::download(const QString &fileName)
{
    std::ifstream file(fileName.toStdString(), std::ios::binary);

    //file.seekg(0,std::ios::end);
    //size_t length = file.tellg();
    //qDebug() << "Size of file: "<<fileName<<" is "<<length;

    if (file.is_open())
    {
        char buff[4];
        int temp;
        QVector<int> v;
        while (file.read(buff,sizeof(int)))
        {
            memcpy(&temp,buff,sizeof(temp));
            v.push_back(temp);
        }
        file.close();
        return v;
    }
    else
        qDebug() << "File " <<fileName<<" cannot open";
    return QVector<int>();

}

void routeSearcher::setStandartProperties()
{
    openList.clear();
    closedList.clear();
    //this->setStartSize(5,7);
    this->resetMassive();
}

std::pair<int, int> routeSearcher::getStartPointIndex() const
{
    return std::pair<int,int >(this->startPoint.second.getI(),this->startPoint.second.getJ());
}

std::pair<int, int> routeSearcher::getEndPointIndex() const
{
    return std::pair<int,int >(this->endPoint.second.getI(),this->endPoint.second.getJ());
}

//void routeSearcher::setStartSize(size_t eI, size_t eJ)
//{
//    if (!massive.empty())
//        massive.clear();
//    for (size_t i = 0; i < eI; i++)
//    {
//        std::vector<controlBlock> temp;
//        temp.resize(eJ);
//        massive.push_back(temp);
//    }
//}
//
//int routeSearcher::getI() const{
//
//    return massive.size();
//}
//int routeSearcher::getJ() const{
//
//    return massive[0].size();
//}


