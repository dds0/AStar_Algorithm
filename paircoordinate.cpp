#include "paircoordinate.h"

void pairCoordinate::setI(int new_i){
    i = new_i;
}
void pairCoordinate::setJ(int new_j){
    j = new_j;
}
int pairCoordinate::getI() const{
    return i;
}
int pairCoordinate::getJ() const{
    return j;
}

bool operator != (const pairCoordinate& left, const pairCoordinate& right)
{
    if (left.getI() != right.getI() || left.getJ() != right.getJ())
        return true;
    return false;
}
