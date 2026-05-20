#ifndef PROJECTS_RUBYCUBE_CUBE_H
#define PROJECTS_RUBYCUBE_CUBE_H


#include <bits/stdc++.h>
using namespace std;

// base class for all types of cube representations

class RubiksCube 
{
public:
    enum class FACE
    {
        UP,
        LEFT,
        RIGHT,
        FRONT,
        BACK,
        DOWN
    };

    enum class COLOR
    {
        WHITE,
        GREEN,
        RED,
        BLUE,
        ORANGE,
        YELLOW
    };

    enum class MOVE
    {
        L,LPRIME,L2,
        R,RPRIME,R2,
        U,UPRIME,U2,
        D,DPRIME,D2,
        F,FPRIME,F2,
        B,BPRIME,B2
    };

   

    // RETURNS the color letter at position (row, column) on the specified face
    virtual char getColor(FACE face,int row,int col) const = 0;



    virtual bool isSolved()const=0;

    // returns the move in string format
    static string getMove(MOVE move) ;

    // prints in 2d format
    void print() const ;
     
    // randfully shuffles the cube by applying n random moves
    // returns vector of moves applied to shuffle the cube
    vector<MOVE> randomshuffle(int n);

    // changing my cube

    RubiksCube &Move(MOVE move);

    // invert a move
    RubiksCube &invert(MOVE move);
     

    virtual RubiksCube &f() = 0;

    virtual RubiksCube &fPrime() = 0;

    virtual RubiksCube &f2() = 0;

    virtual RubiksCube &u() = 0;

    virtual RubiksCube &uPrime() = 0;

    virtual RubiksCube &u2() = 0;

    virtual RubiksCube &l() = 0;

    virtual RubiksCube &lPrime() = 0;

    virtual RubiksCube &l2() = 0;

    virtual RubiksCube &r() = 0;

    virtual RubiksCube &rPrime() = 0;

    virtual RubiksCube &r2() = 0;

    virtual RubiksCube &d() = 0;

    virtual RubiksCube &dPrime() = 0;

    virtual RubiksCube &d2() = 0;

    virtual RubiksCube &b() = 0;

    virtual RubiksCube &bPrime() = 0;

    virtual RubiksCube &b2() = 0;

    string getCornerColorString(uint8_t ind) const;

    uint8_t getCornerIndex(uint8_t ind) const;

    uint8_t getCornerOrientation(uint8_t ind) const;

    
};

#endif // PROJECTS_RUBYCUBE_CUBE_H



