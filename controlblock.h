#ifndef CONTROLBLOCK_H
#define CONTROLBLOCK_H

#include <iostream>
#include <vector>
#include <list>
#include "paircoordinate.h"

#define base_multiplier 10

class controlBlock
{
public:
    void setPromotionFee(int new_pf);
    void setHeuristicApproximation(int new_ha);
    void setPrevPointerObj(controlBlock& prevCB);
    void setTerrain_ComplexityFactor(int new_index);

    controlBlock* getPointerPrevObj() const;

    int getTotalWeight() const;
    int getPromotionFee() const;
    int getHeuristicApproximation() const;
    int getTerrain_ComplexityFactor() const;

    controlBlock(int new_pf, int new_ha) : PromotionFee(new_pf), HeuristicApproximation(new_ha) {}
    controlBlock() {};

    friend std::ostream& operator<<(std::ostream& os, const controlBlock& obj);
    friend std::ostream& operator<<(std::ostream& os, const controlBlock* obj);
    friend bool operator<(const controlBlock &obj1, const controlBlock &obj2);

    pairCoordinate test;

private:
    controlBlock* pPrev = nullptr;
    int PromotionFee = INT_MIN;
    int HeuristicApproximation = INT_MIN;
    int Terrain_ComplexityFactor = 1;

};

#endif // CONTROLBLOCK_H
