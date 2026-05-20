
#include "RCube.h"
#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <chrono>

using namespace std;


mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

char RubiksCube::getColorLetter(COLOR color) 
{
    switch (color) 
    {
        case COLOR::BLUE:
            return 'B';
        case COLOR::GREEN:
            return 'G';
        case COLOR::RED:
            return 'R';
        case COLOR::YELLOW:
            return 'Y';
        case COLOR::WHITE:
            return 'W';
        case COLOR::ORANGE:
            return 'O';
    }

    return '&';
}


string RubiksCube::getMove(MOVE ind) 
{
    switch (ind) 
    {
        case MOVE::L:
            return "L";
        case MOVE::LPRIME:
            return "L'";
        case MOVE::L2:
            return "L2";
        case MOVE::R:
            return "R";
        case MOVE::RPRIME:
            return "R'";
        case MOVE::R2:
            return "R2";
        case MOVE::U:
            return "U";
        case MOVE::UPRIME:
            return "U'";
        case MOVE::U2:
            return "U2";
        case MOVE::D:
            return "D";
        case MOVE::DPRIME:
            return "D'";
        case MOVE::D2:
            return "D2";
        case MOVE::F:
            return "F";
        case MOVE::FPRIME:
            return "F'";
        case MOVE::F2:
            return "F2";
        case MOVE::B:
            return "B";
        case MOVE::BPRIME:
            return "B'";
        case MOVE::B2:
            return "B2";
    }

    return '&';
}

RubiksCube &RubiksCube::move(MOVE ind) 
{
    switch (ind) 
    {
        case MOVE::L:
            return this->l();
        case MOVE::LPRIME:
            return this->lPrime();
        case MOVE::L2:
            return this->l2();
        case MOVE::R:
            return this->r();
        case MOVE::RPRIME:
            return this->rPrime();
        case MOVE::R2:
            return this->r2();
        case MOVE::U:
            return this->u();
        case MOVE::UPRIME:
            return this->uPrime();
        case MOVE::U2:
            return this->u2();
        case MOVE::D:
            return this->d();
        case MOVE::DPRIME:
            return this->dPrime();
        case MOVE::D2:
            return this->d2();
        case MOVE::F:
            return this->f();
        case MOVE::FPRIME:
            return this->fPrime();
        case MOVE::F2:
            return this->f2();
        case MOVE::B:
            return this->b();
        case MOVE::BPRIME:
            return this->bPrime();
        case MOVE::B2:
            return this->b2();
    }

    return this->l();
}


RubiksCube &RubiksCube::invert(MOVE ind) 
{
    switch (ind) 
    {
        case MOVE::L:
            return this->lPrime();
        case MOVE::LPRIME:
            return this->l();
        case MOVE::L2:
            return this->l2();
        case MOVE::R:
            return this->rPrime();
        case MOVE::RPRIME:
            return this->r();
        case MOVE::R2:
            return this->r2();
        case MOVE::U:
            return this->uPrime();
        case MOVE::UPRIME:
            return this->u();
        case MOVE::U2:
            return this->u2();
        case MOVE::D:
            return this->dPrime();
        case MOVE::DPRIME:
            return this->d();
        case MOVE::D2:
            return this->d2();
        case MOVE::F:
            return this->fPrime();
        case MOVE::FPRIME:
            return this->f();
        case MOVE::F2:
            return this->f2();
        case MOVE::B:
            return this->bPrime();
        case MOVE::BPRIME:
            return this->b();
        case MOVE::B2:
            return this->b2();
    }
    return this->l();
}



void RubiksCube::print() const 
{
    cout << "Rubik's Cube:\n\n";

    for (int row = 0; row < 3; row++) 
    {
        for (int i = 0; i < 7; i++) cout << " ";
        for (int col = 0; col < 3; col++) 
        {
            cout << getColorLetter(getColor(FACE::UP, row, col)) << " ";
        }
        cout << "\n";
    }

    cout << "\n";

    for (int row = 0; row <3; row++) 
    {

        for (int col = 0; col <3; col++) 
        {
            cout << getColorLetter(getColor(FACE::LEFT, row, col)) << " ";
        }
        cout << " ";

        for (int col = 0; col <3; col++) 
        {
            cout << getColorLetter(getColor(FACE::FRONT, row, col)) << " ";
        }
        cout << " ";

        for (int col = 0; col <3; col++) 
        {
            cout << getColorLetter(getColor(FACE::RIGHT, row, col)) << " ";
        }
        cout << " ";

        for (int col = 0; col <3; col++) 
        {
            cout << getColorLetter(getColor(FACE::BACK, row, col)) << " ";
        }
        cout << "\n";
    }

    cout << "\n";

    for (int row = 0; row <3; row++) 
    {
        for (int i = 0; i < 7; i++) cout << " ";
        for (int col = 0; col <3; col++) 
        {
            cout << getColorLetter(getColor(FACE::DOWN, row, col)) << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}


vector<RubiksCube::MOVE> RubiksCube::randomshuffle(int times) 
{
    vector<RubiksCube::MOVE> moves;
    for (int i = 0; i < times; i++) 
    {
        int move = rng() % 18;
        auto generated_move = static_cast<RubiksCube::MOVE>(move);
        
        moves.push_back(generated_move);
        this->move(generated_move); 
    }
    return moves;
}



string RubiksCube::getCornerColorString(int ind) const 
{
    string str = "";

    switch (ind) 
    {
//        UFR
        case 0:
            str += getColorLetter(getColor(FACE::UP, 2, 2));
            str += getColorLetter(getColor(FACE::FRONT, 0, 2));
            str += getColorLetter(getColor(FACE::RIGHT, 0, 0));
            break;

//            UFL
        case 1:
            str += getColorLetter(getColor(FACE::UP, 2, 0));
            str += getColorLetter(getColor(FACE::FRONT, 0, 0));
            str += getColorLetter(getColor(FACE::LEFT, 0, 2));
            break;

//            UBL
        case 2:
            str += getColorLetter(getColor(FACE::UP, 0, 0));
            str += getColorLetter(getColor(FACE::BACK, 0, 2));
            str += getColorLetter(getColor(FACE::LEFT, 0, 0));
            break;

//            UBR
        case 3:
            str += getColorLetter(getColor(FACE::UP, 0, 2));
            str += getColorLetter(getColor(FACE::BACK, 0, 0));
            str += getColorLetter(getColor(FACE::RIGHT, 0, 2));
            break;

//            DFR
        case 4:
            str += getColorLetter(getColor(FACE::DOWN, 0, 2));
            str += getColorLetter(getColor(FACE::FRONT, 2, 2));
            str += getColorLetter(getColor(FACE::RIGHT, 2, 0));
            break;

//            DFL
        case 5:
            str += getColorLetter(getColor(FACE::DOWN, 0, 0));
            str += getColorLetter(getColor(FACE::FRONT, 2, 0));
            str += getColorLetter(getColor(FACE::LEFT, 2, 2));
            break;

//            DBR
        case 6:
            str += getColorLetter(getColor(FACE::DOWN, 2, 2));
            str += getColorLetter(getColor(FACE::BACK, 2, 0));
            str += getColorLetter(getColor(FACE::RIGHT, 2, 2));
            break;

//            DBL
        case 7:
            str += getColorLetter(getColor(FACE::DOWN, 2, 0));
            str += getColorLetter(getColor(FACE::BACK, 2, 2));
            str += getColorLetter(getColor(FACE::LEFT, 2, 0));
            break;
    }
    return str;
}


/*

    White/Yellow  → bit 2 (top/bottom face)
    Red/Orange    → bit 1 (front/back face)
    Blue/Green    → bit 0 (left/right face)


    Corner: W, R, B → ret = 000 = 0
    Corner: W, R, G → ret = 001 = 1
    Corner: W, O, B → ret = 010 = 2
    Corner: W, O, G → ret = 011 = 3
    Corner: Y, R, B → ret = 100 = 4
    Corner: Y, R, G → ret = 101 = 5
    Corner: Y, O, B → ret = 110 = 6
    Corner: Y, O, G → ret = 111 = 7
*/



int RubiksCube::getCornerIndex(int ind) const 
{
    string corner = getCornerColorString(ind);

    int ret = 0;
    for (auto c: corner)
    {
        if (c != 'W' && c != 'Y') continue;
        if (c == 'Y') 
        {
            ret |= (1 << 2);
        }
    }

    for (auto c: corner) 
    {
        if (c != 'R' && c != 'O') continue;
        if (c == 'O')
         {
            ret |= (1 << 1);
        }
    }

    for (auto c: corner) 
    {
        if (c != 'B' && c != 'G') continue;
        if (c == 'G') 
        {
            ret |= (1 << 0);
        }
    }
    return ret;
}


int RubiksCube::getCornerOrientation(int ind) const 
{
    string corner = getCornerColorString(ind);

    string actual_str = "";

    for (auto c: corner) 
    {
        if (c != 'W' && c != 'Y') continue;
        actual_str.push_back(c);
    }

    if (corner[1] == actual_str[0]) 
    {
        return 1;
    } 
    else if (corner[2] == actual_str[0]) 
    {
        return 2;
    } 
    else return 0;
}