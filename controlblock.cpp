#include "controlblock.h"
#include <iostream>

void controlBlock::setPromotionFee(int new_pf)
{
    PromotionFee = new_pf;
}

void controlBlock::setHeuristicApproximation(int new_ha)
{
    HeuristicApproximation = new_ha;
}

int controlBlock::getTotalWeight() const
{
    return PromotionFee + HeuristicApproximation;
}
int controlBlock::getPromotionFee() const
{
    return PromotionFee;
}
int controlBlock::getHeuristicApproximation() const
{
    return HeuristicApproximation;
}
controlBlock* controlBlock::getPointerPrevObj() const
{
    return this->pPrev;
}


bool operator<(const controlBlock &obj1, const controlBlock &obj2)
{
    return obj1.getTotalWeight() < obj2.getTotalWeight();
}

std::ostream& operator<<(std::ostream& os, const controlBlock* obj)
{
    os.clear();
    os << &obj;
    return os;
}

std::ostream& operator<<(std::ostream& os, const controlBlock& obj)
{
    os.clear();
    os << obj.getTotalWeight();
    return os;
}


void controlBlock::setPrevPointerObj(controlBlock &prevCB)
{
    this->pPrev = &prevCB;
}


void controlBlock::setTerrain_ComplexityFactor(int new_index)
{
    Terrain_ComplexityFactor = new_index;
}

int controlBlock::getTerrain_ComplexityFactor() const
{
    return Terrain_ComplexityFactor;
}
