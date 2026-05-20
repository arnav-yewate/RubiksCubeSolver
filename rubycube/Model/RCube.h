#ifndef PROJECTS_RUBYCUBE_RCUBE_H
#define PROJECTS_RUBYCUBE_RCUBE_H


#include <bits/stdc++.h>
using namespace std;

/*
     * 
     *
     * The cube is laid out as follows.
     *
     * The sides:
     *    U
     *  L F R B
     *    D
     *
     * Color wise:
     *
     *          W W W
     *          W W W   U(0)
     *          W W W
     *
     *  G G G   R R R   B B B   O O O
     *  G G G   R R R   B B B   O O O
     *  G G G   R R R   B B B   O O O
     *   L(1)    F(2)    R(3)    B(4)
     *          Y Y Y
     *          Y Y Y
     *          Y Y Y
     *           D(5)
    */

// base class for all types of cube representations

class RubiksCube 
{
public:
    enum class FACE
    {

       
        UP,
        LEFT,
        FRONT,
        RIGHT,
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
    virtual COLOR getColor(FACE face, unsigned row, unsigned col) const = 0;

    /*
     * Returns the first letter of the given COLOR
     * Eg: For COLOR::GREEN, it returns 'G'
     */
    static char getColorLetter(COLOR color);


    virtual bool isSolved()const=0;

    // returns the move in string format
    static string getMove(MOVE move) ;

    // prints in 2d format
    void print() const ;
     
    // randfully shuffles the cube by applying n random moves
    // returns vector of moves applied to shuffle the cube
    vector<MOVE> randomshuffle(int n);

    // changing my cube

    RubiksCube &move(MOVE ind);

    // invert a move
    RubiksCube &invert(MOVE ind);
     

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

    string getCornerColorString(int ind) const;

    int getCornerIndex(int ind) const;

    int getCornerOrientation(int ind) const;

    
};

#endif 



