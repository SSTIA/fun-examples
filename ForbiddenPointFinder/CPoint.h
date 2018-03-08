//
// Created by liu on 18-3-8.
//

#ifndef CPOINT_H
#define CPOINT_H


class CPoint {
public:
    int x, y;

    CPoint() : x(0), y(0) {}

    CPoint(int initX, int initY) : x(initX), y(initY) {}

    bool operator==(const CPoint &that) {
        return x == that.x && y == that.y;
    }

    bool operator!=(const CPoint &that) {
        return x != that.x || y != that.y;
    }

    CPoint operator+(const CPoint &that) {
        return {x + that.x, y + that.y};
    }

    CPoint operator-(const CPoint &that) {
        return {x - that.x, y - that.y};
    }

    CPoint operator-() {
        return {-x, -y};
    }

    CPoint &operator+=(const CPoint &that) {
        x += that.x;
        y += that.y;
        return *this;
    }

    CPoint &operator-=(const CPoint &that) {
        x -= that.x;
        y -= that.y;
        return *this;
    }

};


#endif //CPOINT_H
