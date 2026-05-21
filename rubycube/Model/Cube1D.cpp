#include "RCube.h"
#include <array>

class Cube1D : public RubiksCube
{
    private:
    

    static inline int getindex(int ind,int row,int col)
    {
        return (ind*9)+(row*3)+col;
    }

    // 3x3 square rotations
    void rotateface(int ind)
    {
        char temp[9] = {};
        for (int i = 0; i < 3; i++) 
        {
            for (int j = 0; j < 3; j++) 
            {
                temp[i * 3 + j] = cube[getindex(ind, i, j)];
            }
        }
        for (int i = 0; i < 3; i++) cube[getindex(ind, 0, i)] = temp[getindex(0, 2 - i, 0)];
        for (int i = 0; i < 3; i++) cube[getindex(ind, i, 2)] = temp[getindex(0, 0, i)];
        for (int i = 0; i < 3; i++) cube[getindex(ind, 2, 2 - i)] = temp[getindex(0, i, 2)];
        for (int i = 0; i < 3; i++) cube[getindex(ind, 2 - i, 0)] = temp[getindex(0, 2, 2 - i)];
    }

    public:

    std::array<char, 54> cube;
    static constexpr std::array<char, 54> solved = 
    {
    'W','W','W','W','W','W','W','W','W',  // U(0)
    'G','G','G','G','G','G','G','G','G',  // L(1)
    'R','R','R','R','R','R','R','R','R',  // F(2)
    'B','B','B','B','B','B','B','B','B',  // R(3)
    'O','O','O','O','O','O','O','O','O',  // B(4)
    'Y','Y','Y','Y','Y','Y','Y','Y','Y',  // D(5)
    };


    //constructor
    Cube1D() 
    {
        for (int i = 0; i < 6; i++) 
        {
            for (int j = 0; j < 3; j++) 
            {
                for (int k = 0; k < 3; k++) 
                {
                    cube[i * 9 + j * 3 + k] = getColorLetter(COLOR(i));
                }
            }
        }
    }

    

    COLOR getColor(FACE face, unsigned row, unsigned col) const override 
    {
        char color = cube[getindex((int)face, (int)row, (int)col)];
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
        for (int i = 0; i < 3; i++) temp[i] = cube[getindex(4, 0, 2 - i)];
        for (int i = 0; i < 3; i++) cube[getindex(4, 0, 2 - i)] = cube[getindex(1, 0, 2 - i)];
        for (int i = 0; i < 3; i++) cube[getindex(1, 0, 2 - i)] = cube[getindex(2, 0, 2 - i)];
        for (int i = 0; i < 3; i++) cube[getindex(2, 0, 2 - i)] = cube[getindex(3, 0, 2 - i)];
        for (int i = 0; i < 3; i++) cube[getindex(3, 0, 2 - i)] = temp[i];

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
        for (int i = 0; i < 3; i++) temp[i] = cube[getindex(0, i, 0)];
        for (int i = 0; i < 3; i++) cube[getindex(0, i, 0)] = cube[getindex(4, 2 - i, 2)];
        for (int i = 0; i < 3; i++) cube[getindex(4, 2 - i, 2)] = cube[getindex(5, i, 0)];
        for (int i = 0; i < 3; i++) cube[getindex(5, i, 0)] = cube[getindex(2, i, 0)];
        for (int i = 0; i < 3; i++) cube[getindex(2, i, 0)] = temp[i];

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
        for (int i = 0; i < 3; i++) temp[i] = cube[getindex(0, 2, i)];
        for (int i = 0; i < 3; i++) cube[getindex(0, 2, i)] = cube[getindex(1, 2 - i, 2)];
        for (int i = 0; i < 3; i++) cube[getindex(1, 2 - i, 2)] = cube[getindex(5, 0, 2 - i)];
        for (int i = 0; i < 3; i++) cube[getindex(5, 0, 2 - i)] = cube[getindex(3, i, 0)];
        for (int i = 0; i < 3; i++) cube[getindex(3, i, 0)] = temp[i];

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
        for (int i = 0; i < 3; i++) temp[i] = cube[getindex(0, 2 - i, 2)];
        for (int i = 0; i < 3; i++) cube[getindex(0, 2 - i, 2)] = cube[getindex(2, 2 - i, 2)];
        for (int i = 0; i < 3; i++) cube[getindex(2, 2 - i, 2)] = cube[getindex(5, 2 - i, 2)];
        for (int i = 0; i < 3; i++) cube[getindex(5, 2 - i, 2)] = cube[getindex(4, i, 0)];
        for (int i = 0; i < 3; i++) cube[getindex(4, i, 0)] = temp[i];

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
        for (int i = 0; i < 3; i++) temp[i] = cube[getindex(0, 0, 2 - i)];
        for (int i = 0; i < 3; i++) cube[getindex(0, 0, 2 - i)] = cube[getindex(3, 2 - i, 2)];
        for (int i = 0; i < 3; i++) cube[getindex(3, 2 - i, 2)] = cube[getindex(5, 2, i)];
        for (int i = 0; i < 3; i++) cube[getindex(5, 2, i)] = cube[getindex(1, i, 0)];
        for (int i = 0; i < 3; i++) cube[getindex(1, i, 0)] = temp[i];

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
        for (int i = 0; i < 3; i++) temp[i] = cube[getindex(2, 2, i)];
        for (int i = 0; i < 3; i++) cube[getindex(2, 2, i)] = cube[getindex(1, 2, i)];
        for (int i = 0; i < 3; i++) cube[getindex(1, 2, i)] = cube[getindex(4, 2, i)];
        for (int i = 0; i < 3; i++) cube[getindex(4, 2, i)] = cube[getindex(3, 2, i)];
        for (int i = 0; i < 3; i++) cube[getindex(3, 2, i)] = temp[i];

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

    bool operator==(const Cube1D& other) const 
    {
        return cube == other.cube;  
    }

    bool operator!=(const Cube1D& other) const 
    {
        return !(*this == other);
    }


    struct Hash1d
    {
        size_t operator()(const Cube1D &r1) const 
        {
        size_t hash_val = 14695981039346656037ULL; 
        for (int i = 0; i < 54; i++) 
        {
            hash_val ^= static_cast<size_t>(r1.cube[i]);
            hash_val *= 1099511628211ULL; 
        }
        return hash_val;
        }
    };
};