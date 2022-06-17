#ifndef PAIRCOORDINATE_H
#define PAIRCOORDINATE_H

class pairCoordinate
{
public:

    void setI(int new_i);
    void setJ(int new_j);
    int getI() const;
    int getJ() const;
    pairCoordinate(int new_i, int new_j) : i(new_i), j(new_j) {}
    pairCoordinate() {}
    friend bool operator != (const pairCoordinate& left, const pairCoordinate& right);

private:
    int i = -1;
    int j = -1;
};

#endif // PAIRCOORDINATE_H
