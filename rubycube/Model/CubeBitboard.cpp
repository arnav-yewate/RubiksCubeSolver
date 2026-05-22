#pragma once

#include "RCube.h"

class CubeBitB : public RubiksCube
{

private:
    uint64_t solved_side_config[6]{};

    int arr[3][3] = {{0, 1, 2},
                     {7, 8, 3},
                     {6, 5, 4}};

    uint64_t one_8 = (1 << 8) - 1, one_24 = (1 << 24) - 1;

    void rotateFace(int ind)
    {
        uint64_t side = bitboard[ind];
        side = side >> (8 * 6);
        bitboard[ind] = (bitboard[ind] << 16) | (side);
    }

    void rotateSide(int s1, int s1_1, int s1_2, int s1_3, int s2, int s2_1, int s2_2, int s2_3)
    {
        uint64_t clr1 = (bitboard[s2] & (one_8 << (8 * s2_1))) >> (8 * s2_1);
        uint64_t clr2 = (bitboard[s2] & (one_8 << (8 * s2_2))) >> (8 * s2_2);
        uint64_t clr3 = (bitboard[s2] & (one_8 << (8 * s2_3))) >> (8 * s2_3);

        bitboard[s1] = (bitboard[s1] & ~(one_8 << (8 * s1_1))) | (clr1 << (8 * s1_1));
        bitboard[s1] = (bitboard[s1] & ~(one_8 << (8 * s1_2))) | (clr2 << (8 * s1_2));
        bitboard[s1] = (bitboard[s1] & ~(one_8 << (8 * s1_3))) | (clr3 << (8 * s1_3));
    }

    // Helper to getCorners()
    int get5bitCorner(string corner)
    {
        int ret = 0;
        string actual_str;
        for (auto c : corner)
        {
            if (c != 'W' && c != 'Y')
                continue;
            actual_str.push_back(c);
            if (c == 'Y')
            {
                ret |= (1 << 2);
            }
        }

        for (auto c : corner)
        {
            if (c != 'R' && c != 'O')
                continue;
            if (c == 'O')
            {
                ret |= (1 << 1);
            }
        }

        for (auto c : corner)
        {
            if (c != 'B' && c != 'G')
                continue;
            if (c == 'G')
            {
                ret |= (1 << 0);
            }
        }

        if (actual_str.empty())
            return ret;

        if (corner[1] == actual_str[0])
        {
            ret |= (1 << 3);
        }
        else if (corner[2] == actual_str[0])
        {
            ret |= (1 << 4);
        }

        return ret;
    }

public:
    uint64_t bitboard[6]{};

    CubeBitB()
    {
        for (int side = 0; side < 6; side++)
        {
            uint64_t clr = 1 << side;
            bitboard[side] = 0;
            for (int faceIdx = 0; faceIdx < 8; faceIdx++)
            {
                bitboard[side] |= clr << (8 * faceIdx);
            }
            solved_side_config[side] = bitboard[side];
        }
    }

    COLOR getColor(FACE face, unsigned row, unsigned col) const override
    {
        int idx = arr[row][col];
        if (idx == 8)
            return (COLOR)((int)face);

        uint64_t side = bitboard[(int)face];
        uint64_t color = (side >> (8 * idx)) & one_8;

        int bit_pos = 0;
        while (color != 0)
        {
            color = color >> 1;
            bit_pos++;
        }
        return (COLOR)(bit_pos - 1);
    }

    struct EdgePiece
    {
        uint8_t id;
        uint8_t orientation;
    };

    // Returns the ID (0-11) and Orientation (0 or 1) of the edge at a given position
    EdgePiece getEdge(int position) const
    {
        char c1, c2;

        // 1. Get the two colors based on the 12 physical edge positions
        switch (position)
        {
        case 0: // UP-FRONT
            c1 = getColorLetter(getColor(FACE::UP, 2, 1));
            c2 = getColorLetter(getColor(FACE::FRONT, 0, 1));
            break;
        case 1: // UP-RIGHT
            c1 = getColorLetter(getColor(FACE::UP, 1, 2));
            c2 = getColorLetter(getColor(FACE::RIGHT, 0, 1));
            break;
        case 2: // UP-BACK
            c1 = getColorLetter(getColor(FACE::UP, 0, 1));
            c2 = getColorLetter(getColor(FACE::BACK, 0, 1));
            break;
        case 3: // UP-LEFT
            c1 = getColorLetter(getColor(FACE::UP, 1, 0));
            c2 = getColorLetter(getColor(FACE::LEFT, 0, 1));
            break;
        case 4: // DOWN-FRONT
            c1 = getColorLetter(getColor(FACE::DOWN, 0, 1));
            c2 = getColorLetter(getColor(FACE::FRONT, 2, 1));
            break;
        case 5: // DOWN-RIGHT
            c1 = getColorLetter(getColor(FACE::DOWN, 1, 2));
            c2 = getColorLetter(getColor(FACE::RIGHT, 2, 1));
            break;
        case 6: // DOWN-BACK
            c1 = getColorLetter(getColor(FACE::DOWN, 2, 1));
            c2 = getColorLetter(getColor(FACE::BACK, 2, 1));
            break;
        case 7: // DOWN-LEFT
            c1 = getColorLetter(getColor(FACE::DOWN, 1, 0));
            c2 = getColorLetter(getColor(FACE::LEFT, 2, 1));
            break;
        case 8: // FRONT-RIGHT
            c1 = getColorLetter(getColor(FACE::FRONT, 1, 2));
            c2 = getColorLetter(getColor(FACE::RIGHT, 1, 0));
            break;
        case 9: // FRONT-LEFT
            c1 = getColorLetter(getColor(FACE::FRONT, 1, 0));
            c2 = getColorLetter(getColor(FACE::LEFT, 1, 2));
            break;
        case 10: // BACK-RIGHT
            c1 = getColorLetter(getColor(FACE::BACK, 1, 0));
            c2 = getColorLetter(getColor(FACE::RIGHT, 1, 2));
            break;
        case 11: // BACK-LEFT
            c1 = getColorLetter(getColor(FACE::BACK, 1, 2));
            c2 = getColorLetter(getColor(FACE::LEFT, 1, 0));
            break;
        }

        uint8_t id = 255; // Default error state
        uint8_t orientation = 0;

        string edge = "";
        edge += c1;
        edge += c2;

        // 2. Map colors to ID and determine Orientation
        // If White (W) or Yellow (Y) is c1, it means it's sitting correctly on the Up/Down face -> Orientation 0.
        if (edge == "WG" || edge == "GW")
        {
            id = 0;
            orientation = (c1 == 'W') ? 0 : 1;
        }
        else if (edge == "WR" || edge == "RW")
        {
            id = 1;
            orientation = (c1 == 'W') ? 0 : 1;
        }
        else if (edge == "WB" || edge == "BW")
        {
            id = 2;
            orientation = (c1 == 'W') ? 0 : 1;
        }
        else if (edge == "WO" || edge == "OW")
        {
            id = 3;
            orientation = (c1 == 'W') ? 0 : 1;
        }
        else if (edge == "YG" || edge == "GY")
        {
            id = 4;
            orientation = (c1 == 'Y') ? 0 : 1;
        }
        else if (edge == "YR" || edge == "RY")
        {
            id = 5;
            orientation = (c1 == 'Y') ? 0 : 1;
        }
        else if (edge == "YB" || edge == "BY")
        {
            id = 6;
            orientation = (c1 == 'Y') ? 0 : 1;
        }
        else if (edge == "YO" || edge == "OY")
        {
            id = 7;
            orientation = (c1 == 'Y') ? 0 : 1;
        }

        // For middle layer edges, if Green (G) or Blue (B) is c1, it's on the Front/Back face -> Orientation 0.
        else if (edge == "GR" || edge == "RG")
        {
            id = 8;
            orientation = (c1 == 'G') ? 0 : 1;
        }
        else if (edge == "GO" || edge == "OG")
        {
            id = 9;
            orientation = (c1 == 'G') ? 0 : 1;
        }
        else if (edge == "BR" || edge == "RB")
        {
            id = 10;
            orientation = (c1 == 'B') ? 0 : 1;
        }
        else if (edge == "BO" || edge == "OB")
        {
            id = 11;
            orientation = (c1 == 'B') ? 0 : 1;
        }
        // if (id == 255)
        // {
        //     cout << "Bad edge: '" << edge << "' at position " << position << endl;
        //     cout << "c1=" << c1 << " c2=" << c2 << endl;
        //     // print full cube state
        //     this->print();
        //     exit(1);
        // }
        return {id, orientation};
    }

    bool isSolved() const override
    {
        for (int i = 0; i < 6; i++)
        {
            if (solved_side_config[i] != bitboard[i])
                return false;
        }
        return true;
    }

    RubiksCube &u() override
    {
        this->rotateFace(0);
        uint64_t temp = bitboard[2] & one_24;
        bitboard[2] = (bitboard[2] & ~one_24) | (bitboard[3] & one_24);
        bitboard[3] = (bitboard[3] & ~one_24) | (bitboard[4] & one_24);
        bitboard[4] = (bitboard[4] & ~one_24) | (bitboard[1] & one_24);
        bitboard[1] = (bitboard[1] & ~one_24) | temp;
        return *this;
    }

    RubiksCube &d() override
    {
        this->rotateFace(5);
        uint64_t clr1 = (bitboard[2] & (one_8 << (8 * 4))) >> (8 * 4);
        uint64_t clr2 = (bitboard[2] & (one_8 << (8 * 5))) >> (8 * 5);
        uint64_t clr3 = (bitboard[2] & (one_8 << (8 * 6))) >> (8 * 6);

        this->rotateSide(2, 4, 5, 6, 1, 4, 5, 6);
        this->rotateSide(1, 4, 5, 6, 4, 4, 5, 6);
        this->rotateSide(4, 4, 5, 6, 3, 4, 5, 6);

        bitboard[3] = (bitboard[3] & ~(one_8 << (8 * 4))) | (clr1 << (8 * 4));
        bitboard[3] = (bitboard[3] & ~(one_8 << (8 * 5))) | (clr2 << (8 * 5));
        bitboard[3] = (bitboard[3] & ~(one_8 << (8 * 6))) | (clr3 << (8 * 6));
        return *this;
    }

    RubiksCube &f() override
    {
        this->rotateFace(2);
        uint64_t clr1 = (bitboard[0] & (one_8 << (8 * 4))) >> (8 * 4);
        uint64_t clr2 = (bitboard[0] & (one_8 << (8 * 5))) >> (8 * 5);
        uint64_t clr3 = (bitboard[0] & (one_8 << (8 * 6))) >> (8 * 6);

        this->rotateSide(0, 4, 5, 6, 1, 2, 3, 4);
        this->rotateSide(1, 2, 3, 4, 5, 0, 1, 2);
        this->rotateSide(5, 0, 1, 2, 3, 6, 7, 0);

        bitboard[3] = (bitboard[3] & ~(one_8 << (8 * 6))) | (clr1 << (8 * 6));
        bitboard[3] = (bitboard[3] & ~(one_8 << (8 * 7))) | (clr2 << (8 * 7));
        bitboard[3] = (bitboard[3] & ~(one_8 << (8 * 0))) | (clr3 << (8 * 0));
        return *this;
    }

    RubiksCube &b() override
    {
        this->rotateFace(4);
        uint64_t clr1 = (bitboard[0] & (one_8 << (8 * 0))) >> (8 * 0);
        uint64_t clr2 = (bitboard[0] & (one_8 << (8 * 1))) >> (8 * 1);
        uint64_t clr3 = (bitboard[0] & (one_8 << (8 * 2))) >> (8 * 2);

        this->rotateSide(0, 0, 1, 2, 3, 2, 3, 4);
        this->rotateSide(3, 2, 3, 4, 5, 4, 5, 6);
        this->rotateSide(5, 4, 5, 6, 1, 6, 7, 0);

        bitboard[1] = (bitboard[1] & ~(one_8 << (8 * 6))) | (clr1 << (8 * 6));
        bitboard[1] = (bitboard[1] & ~(one_8 << (8 * 7))) | (clr2 << (8 * 7));
        bitboard[1] = (bitboard[1] & ~(one_8 << (8 * 0))) | (clr3 << (8 * 0));
        return *this;
    }

    RubiksCube &l() override
    {
        this->rotateFace(1);
        uint64_t clr1 = (bitboard[2] & (one_8 << (8 * 0))) >> (8 * 0);
        uint64_t clr2 = (bitboard[2] & (one_8 << (8 * 7))) >> (8 * 7);
        uint64_t clr3 = (bitboard[2] & (one_8 << (8 * 6))) >> (8 * 6);

        this->rotateSide(2, 0, 7, 6, 0, 0, 7, 6);
        this->rotateSide(0, 0, 7, 6, 4, 4, 3, 2);
        this->rotateSide(4, 4, 3, 2, 5, 0, 7, 6);

        bitboard[5] = (bitboard[5] & ~(one_8 << (8 * 0))) | (clr1 << (8 * 0));
        bitboard[5] = (bitboard[5] & ~(one_8 << (8 * 7))) | (clr2 << (8 * 7));
        bitboard[5] = (bitboard[5] & ~(one_8 << (8 * 6))) | (clr3 << (8 * 6));
        return *this;
    }

    RubiksCube &r() override
    {
        this->rotateFace(3);
        uint64_t clr1 = (bitboard[0] & (one_8 << (8 * 2))) >> (8 * 2);
        uint64_t clr2 = (bitboard[0] & (one_8 << (8 * 3))) >> (8 * 3);
        uint64_t clr3 = (bitboard[0] & (one_8 << (8 * 4))) >> (8 * 4);

        this->rotateSide(0, 2, 3, 4, 2, 2, 3, 4);
        this->rotateSide(2, 2, 3, 4, 5, 2, 3, 4);
        this->rotateSide(5, 2, 3, 4, 4, 6, 7, 0);

        bitboard[4] = (bitboard[4] & ~(one_8 << (8 * 6))) | (clr1 << (8 * 6));
        bitboard[4] = (bitboard[4] & ~(one_8 << (8 * 7))) | (clr2 << (8 * 7));
        bitboard[4] = (bitboard[4] & ~(one_8 << (8 * 0))) | (clr3 << (8 * 0));
        return *this;
    }

    RubiksCube &uPrime() override
    {
        this->u();
        this->u();
        this->u();

        return *this;
    };

    RubiksCube &u2() override
    {
        this->u();
        this->u();

        return *this;
    };

    RubiksCube &lPrime() override
    {
        this->l();
        this->l();
        this->l();

        return *this;
    };

    RubiksCube &l2() override
    {
        this->l();
        this->l();

        return *this;
    };

    RubiksCube &fPrime() override
    {
        this->f();
        this->f();
        this->f();
        return *this;
    };

    RubiksCube &f2() override
    {
        this->f();
        this->f();

        return *this;
    };

    RubiksCube &rPrime() override
    {
        this->r();
        this->r();
        this->r();

        return *this;
    };

    RubiksCube &r2() override
    {
        this->r();
        this->r();

        return *this;
    };

    RubiksCube &bPrime() override
    {
        this->b();
        this->b();
        this->b();

        return *this;
    };

    RubiksCube &b2() override
    {
        this->b();
        this->b();

        return *this;
    };

    RubiksCube &dPrime() override
    {
        this->d();
        this->d();
        this->d();

        return *this;
    };

    RubiksCube &d2() override
    {
        this->d();
        this->d();

        return *this;
    }

    bool operator==(const CubeBitB &r1) const
    {
        for (int i = 0; i < 6; i++)
        {
            if (bitboard[i] != r1.bitboard[i])
                return false;
        }
        return true;
    }

    CubeBitB &operator=(const CubeBitB &r1)
    {
        for (int i = 0; i < 6; i++)
        {
            bitboard[i] = r1.bitboard[i];
        }
        return *this;
    }

    uint64_t getCorners()
    {
        uint64_t ret = 0;
        string top_front_right = "";
        top_front_right += getColorLetter(getColor(FACE::UP, 2, 2));
        top_front_right += getColorLetter(getColor(FACE::FRONT, 0, 2));
        top_front_right += getColorLetter(getColor(FACE::RIGHT, 0, 0));

        string top_front_left = "";
        top_front_left += getColorLetter(getColor(FACE::UP, 2, 0));
        top_front_left += getColorLetter(getColor(FACE::FRONT, 0, 0));
        top_front_left += getColorLetter(getColor(FACE::LEFT, 0, 2));

        string top_back_left = "";
        top_back_left += getColorLetter(getColor(FACE::UP, 0, 0));
        top_back_left += getColorLetter(getColor(FACE::BACK, 0, 2));
        top_back_left += getColorLetter(getColor(FACE::LEFT, 0, 0));

        string top_back_right = "";
        top_back_right += getColorLetter(getColor(FACE::UP, 0, 2));
        top_back_right += getColorLetter(getColor(FACE::BACK, 0, 0));
        top_back_right += getColorLetter(getColor(FACE::RIGHT, 0, 2));

        string bottom_front_right = "";
        bottom_front_right += getColorLetter(getColor(FACE::DOWN, 0, 2));
        bottom_front_right += getColorLetter(getColor(FACE::FRONT, 2, 2));
        bottom_front_right += getColorLetter(getColor(FACE::RIGHT, 2, 0));

        string bottom_front_left = "";
        bottom_front_left += getColorLetter(getColor(FACE::DOWN, 0, 0));
        bottom_front_left += getColorLetter(getColor(FACE::FRONT, 2, 0));
        bottom_front_left += getColorLetter(getColor(FACE::LEFT, 2, 2));

        string bottom_back_right = "";
        bottom_back_right += getColorLetter(getColor(FACE::DOWN, 2, 2));
        bottom_back_right += getColorLetter(getColor(FACE::BACK, 2, 0));
        bottom_back_right += getColorLetter(getColor(FACE::RIGHT, 2, 2));

        string bottom_back_left = "";
        bottom_back_left += getColorLetter(getColor(FACE::DOWN, 2, 0));
        bottom_back_left += getColorLetter(getColor(FACE::BACK, 2, 2));
        bottom_back_left += getColorLetter(getColor(FACE::LEFT, 2, 0));

        ret |= get5bitCorner(top_front_right);
        ret = ret << 5;

        ret |= get5bitCorner(top_front_left);
        ret = ret << 5;

        ret |= get5bitCorner(top_back_right);
        ret = ret << 5;

        ret |= get5bitCorner(top_back_left);
        ret = ret << 5;

        ret |= get5bitCorner(bottom_front_right);
        ret = ret << 5;

        ret |= get5bitCorner(bottom_front_left);
        ret = ret << 5;

        ret |= get5bitCorner(bottom_back_right);
        ret = ret << 5;
        ret |= get5bitCorner(bottom_back_left);

        return ret;
    }

    struct HashBit
    {
        size_t operator()(const CubeBitB &r1) const
        {
            size_t seed = 0;
            for (int i = 0; i < 6; i++)
            {
                seed ^= r1.bitboard[i] + 0x9e3779b9 + (seed << 6) + (seed >> 2);
            }
            return seed;
        }
    };
};
