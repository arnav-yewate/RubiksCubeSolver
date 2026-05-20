#include "RCube.h"
#include <array>

class Cube3D : public RubiksCube
{
    private:

    // 3x3 square rotations
    void rotateface(int ind)
    {
        char temp[3][3] = {};
        for (int i = 0; i < 3; i++) 
        {
            for (int j = 0; j < 3; j++)
            {
                temp[i][j] = cube[ind][i][j];
            }
        }
        for (int i = 0; i < 3; i++) cube[ind][0][i] = temp[2 - i][0];
        for (int i = 0; i < 3; i++) cube[ind][i][2] = temp[0][i];
        for (int i = 0; i < 3; i++) cube[ind][2][2 - i] = temp[i][2];
        for (int i = 0; i < 3; i++) cube[ind][2 - i][0] = temp[2][2 - i];
    }

    public:

    std::array<std::array<std::array<char, 3>, 3>, 6> cube{};
    static constexpr std::array<std::array<std::array<char, 3>, 3>, 6> solved = {{
    // U (0) - White
    {{
        {'W', 'W', 'W'},
        {'W', 'W', 'W'},
        {'W', 'W', 'W'}
    }},
    // L (1) - Green
    {{
        {'G', 'G', 'G'},
        {'G', 'G', 'G'},
        {'G', 'G', 'G'}
    }},
    // F (2) - Red
    {{
        {'R', 'R', 'R'},
        {'R', 'R', 'R'},
        {'R', 'R', 'R'}
    }},
    // R (3) - Blue
    {{
        {'B', 'B', 'B'},
        {'B', 'B', 'B'},
        {'B', 'B', 'B'}
    }},
    // B (4) - Orange
    {{
        {'O', 'O', 'O'},
        {'O', 'O', 'O'},
        {'O', 'O', 'O'}
    }},
    // D (5) - Yellow
    {{
        {'Y', 'Y', 'Y'},
        {'Y', 'Y', 'Y'},
        {'Y', 'Y', 'Y'}
    }}
}};


    //constructor
    Cube3D() 
    {
        for (int i = 0; i < 6; i++) 
        {
            for (int j = 0; j < 3; j++) 
            {
                for (int k = 0; k < 3; k++)
                    cube[i][j][k] = getColorLetter(COLOR(i));
            }
        }
    }

    

    COLOR getColor(FACE face, unsigned row, unsigned col) const override 
    {
        char color = cube[(int)face][(int)row][(int)col];
        switch (color) 
        {
            case 'B':
                return COLOR::BLUE;
            case 'R':
                return COLOR::RED;
            case 'G':
                return COLOR::GREEN;
            case 'O':
                return COLOR::ORANGE;
            case 'Y':
                return COLOR::YELLOW;
            default:
                return COLOR::WHITE;
        }
    }

    bool isSolved() const override 
    {
        return cube==solved;
    }


    
    RubiksCube &u() override 
    {
        rotateface(0);

        char temp[3] = {};
        for (int i = 0; i < 3; i++) temp[i] = cube[4][0][2 - i];
        for (int i = 0; i < 3; i++) cube[4][0][2 - i] = cube[1][0][2 - i];
        for (int i = 0; i < 3; i++) cube[1][0][2 - i] = cube[2][0][2 - i];
        for (int i = 0; i < 3; i++) cube[2][0][2 - i] = cube[3][0][2 - i];
        for (int i = 0; i < 3; i++) cube[3][0][2 - i] = temp[i];

        return *this;
    }

    RubiksCube &uPrime() override 
    {
        u();
        u();
        u();

        return *this;
    }
    RubiksCube &u2() override 
    {
        u();
        u();
        return *this;
    }

    RubiksCube &l() override 
    {
        rotateface(1);

        char temp[3] = {};
        for (int i = 0; i < 3; i++) temp[i] = cube[0][i][0];
        for (int i = 0; i < 3; i++) cube[0][i][0] = cube[4][2 - i][2];
        for (int i = 0; i < 3; i++) cube[4][2 - i][2] = cube[5][i][0];
        for (int i = 0; i < 3; i++) cube[5][i][0] = cube[2][i][0];
        for (int i = 0; i < 3; i++) cube[2][i][0] = temp[i];

        return *this;
    }

    RubiksCube &lPrime() override 
    {
        l();
        l();
        l();

        return *this;
    }
    RubiksCube &l2() override 
    {
        l();
        l();
        return *this;
    }

    RubiksCube &f() override 
    {
        rotateface(2);

        char temp[3] = {};
        for (int i = 0; i < 3; i++) temp[i] = cube[0][2][i];
        for (int i = 0; i < 3; i++) cube[0][2][i] = cube[1][2 - i][2];
        for (int i = 0; i < 3; i++) cube[1][2 - i][2] = cube[5][0][2 - i];
        for (int i = 0; i < 3; i++) cube[5][0][2 - i] = cube[3][i][0];
        for (int i = 0; i < 3; i++) cube[3][i][0] = temp[i];

        return *this;
    }

    RubiksCube &fPrime() override 
    {
        f();
        f();
        f();

        return *this;
    }
    RubiksCube &f2() override 
    {
        f();
        f();
        return *this;
    }


     RubiksCube &r() override 
     {
        rotateface(3);

        char temp[3] = {};
        for (int i = 0; i < 3; i++) temp[i] = cube[0][2 - i][2];
        for (int i = 0; i < 3; i++) cube[0][2 - i][2] = cube[2][2 - i][2];
        for (int i = 0; i < 3; i++) cube[2][2 - i][2] = cube[5][2 - i][2];
        for (int i = 0; i < 3; i++) cube[5][2 - i][2] = cube[4][i][0];
        for (int i = 0; i < 3; i++) cube[4][i][0] = temp[i];

        return *this;
    }

    RubiksCube &rPrime() override 
    {
        r();
        r();
        r();

        return *this;
    }
    RubiksCube &r2() override 
    {
        r();
        r();
        return *this;
    }



    RubiksCube &b() override 
    {
        rotateface(4);

        char temp[3] = {};
        for (int i = 0; i < 3; i++) temp[i] = cube[0][0][2 - i];
        for (int i = 0; i < 3; i++) cube[0][0][2 - i] = cube[3][2 - i][2];
        for (int i = 0; i < 3; i++) cube[3][2 - i][2] = cube[5][2][i];
        for (int i = 0; i < 3; i++) cube[5][2][i] = cube[1][i][0];
        for (int i = 0; i < 3; i++) cube[1][i][0] = temp[i];

        return *this;
    }

    RubiksCube &bPrime() override 
    {
        b();
        b();
        b();

        return *this;
    }
    RubiksCube &b2() override 
    {
        b();
        b();
        return *this;
    }



    RubiksCube &d() override 
    {
        rotateface(5);

        char temp[3] = {};
        for (int i = 0; i < 3; i++) temp[i] = cube[2][2][i];
        for (int i = 0; i < 3; i++) cube[2][2][i] = cube[1][2][i];
        for (int i = 0; i < 3; i++) cube[1][2][i] = cube[4][2][i];
        for (int i = 0; i < 3; i++) cube[4][2][i] = cube[3][2][i];
        for (int i = 0; i < 3; i++) cube[3][2][i] = temp[i];

        return *this;
    }
    RubiksCube &dPrime() override 
    {
        d();
        d();
        d();

        return *this;
    }
    RubiksCube &d2() override 
    {
        d();
        d();
        return *this;
    }


    struct Hash3d {
    size_t operator()(const Cube3D &r1) const 
    {
        size_t hash_val = 14695981039346656037ULL; // FNV offset basis for 64-bit
        
        // Loop through all 6 faces, 3 rows, and 3 columns
        for (int f = 0; f < 6; f++) 
        {
            for (int r = 0; r < 3; r++) 
            {
                for (int c = 0; c < 3; c++) {
                    hash_val ^= static_cast<size_t>(r1.cube[f][r][c]);
                    hash_val *= 1099511628211ULL; // FNV prime
                }
            }
        }
        
        return hash_val;
    }
};
};