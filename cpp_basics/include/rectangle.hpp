#ifndef CPP_BASICS_RECTANGLE_HPP
#define CPP_BASICS_RECTANGLE_HPP
struct Point {
    int x;
    int y;
};
#include "rectangle.hpp"
#include <iostream>
#include <cmath>
#include <iomanip>

#define XFRAME 20
#define YFRAME 15

int sumas(int x, int y);

class Rectangle {
private:
    int width;
    int height;

    int x;
    int y;

    Point A, B, C, D;

    void calculatePoints() {
        A.x = x;A.y = y;
        B.x = x + width;B.y = y;
        C.x = x + width;C.y = y + height;
        D.x = x;D.y = y + height;
    }

    int calculateField() {
        return width * height;
    }

public:
    Rectangle(int w, int h, int x, int y) : width(w), height(h), x(x), y(y) {calculatePoints();};    //constructor

    void prnt() {
        std::cout << "Pole=" << calculateField() << std::endl;

        std::cout << "Wierzcholki: A=" << "("<<A.x<<","<<A.y<<") ";
        std::cout << "B=" << "("<<B.x<<","<<B.y<<") ";
        std::cout << "C=" << "("<<C.x<<","<<C.y<<") ";
        std::cout << "D=" << "("<<D.x<<","<<D.y<<")"<<std::endl;
    }

    void scale(int factor) {
        width *= factor;
        height *= factor;
        calculatePoints();
    }
    int show_field(){
        return calculateField();
    }

    void show_edges() {
        for (int i = 0; i < YFRAME; ++i) {
            for (int j = 0; j < XFRAME; ++j) {
                if (i == YFRAME-1) {
                    std::cout << std::setw(4) << j - 1 << " "; // Indexacja X
                }else if(
                        (i <= YFRAME -2- A.y && i >= YFRAME -2- C.y && j >= A.x+1 && j <= B.x+1)
                        ) { ////2
                    std::cout << std::setw(5) << "o"; // indeksacja odwrotna Y
                }else if (j == 0) {
                    std::cout << std::setw(4) << YFRAME-2 - i; // indeksacja odwrotna Y
                } else { std::cout << std::setw(5) << "."; } //
            }
            std::cout << std::endl;
        }
    }
};



#endif //CPP_BASICS_RECTANGLE_HPP
