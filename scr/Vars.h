#pragma once

struct Tile {
    int x = 0, y = 0, w = 0, h = 0;
    int used = 0;

    Tile() {}

    Tile(int x, int y, int w, int h) {
        this->x = x;
        this->y = y;
        this->w = w;
        this->h = h;
    }

    bool hit(int(&mPos)[2]) {
        if (mPos[0] > x && mPos[0] < x + w && mPos[1] > y && mPos[1] < y + h) {
            return true;
        }

        return false;
    }

    bool operator==(Tile& t) {
        return this->used == t.used; 
    }
};
