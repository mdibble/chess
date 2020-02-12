#include <iostream>

class Piece {
private:
    char id;
    char side;
    int row;
    int col;
    bool ingame; 
    bool moved;

public:
    char getid();
    char getside();
    int getrow();
    int getcol();
    bool getingame();
    bool getmoved();

    void setid(char arg);
    void setside(char arg);
    void setrow(int arg);
    void setcol(int arg);
    void setingame(bool arg);
    void setmoved(bool arg);
    virtual void move(int arg1, int arg2);

    Piece();
};

Piece::Piece() {
    this -> setid('X');
    this -> setside('X');
    this -> setcol(-1);
    this -> setrow(-1);
    this -> setingame(false);
    this -> setmoved(false);
}

char Piece::getid() { return this -> id; }
char Piece::getside() { return this -> side; }
int Piece::getrow() { return this -> row; }
int Piece::getcol() { return this -> col; }
bool Piece::getingame() { return this -> ingame; }
bool Piece::getmoved() { return this -> moved; }

void Piece::setid(char arg) { this -> id = arg; }
void Piece::setside(char arg) { this -> side = arg; }
void Piece::setrow(int arg) { this -> row = arg; }
void Piece::setcol(int arg) { this -> col = arg; }
void Piece::setingame(bool arg) { this -> ingame = arg; }
void Piece::setmoved(bool arg) { this -> moved = arg; }

void Piece::move(int arg1, int arg2) { std::cout<<"This piece is not in the game"<<std::endl; }

Piece *board[8][8];
Piece *ptrPce;
Piece *nullPiece = new Piece();

class Pawn: public Piece {
public:
    void move(int col, int row);
    Pawn(char side, int col, int row);
};

class Knight: public Piece {
public:
    void move(int col, int row);
    Knight(char side, int col, int row);
};

class Bishop: public Piece {
public:
    void move(int col, int row);
    Bishop(char side, int col, int row);
};

class Rook: public Piece {
public:
    void move(int col, int row);
    Rook(char side, int col, int row);
};

class Queen: public Piece {
public:
    void move(int col, int row);
    Queen(char side, int col, int row);
};

class King: public Piece {
public:
    void move(int col, int row);
    King(char side, int col, int row);
};

Pawn::Pawn(char side, int col, int row) {
    this -> setid('P');
    this -> setside(side);
    this -> setcol(col);
    this -> setrow(row);
    this -> setingame(true);
    this -> setmoved(false);
    board[col][row] = this;
}

void Pawn::move(int col, int row) {

    if (col > 7 || col < 0 || row > 7 || row < 0) {
        std::cout << "Invalid move" << std::endl;
        return;
    }

    // moveset where 1 indicates moveable, 2 indicates takeable, maybe other implementations

    int validMoveset[8][8] = {{0, 0, 0, 0, 0, 0, 0, 0},
                              {0, 0, 0, 0, 0, 0, 0, 0},
                              {0, 0, 0, 0, 0, 0, 0, 0},
                              {0, 0, 0, 0, 0, 0, 0, 0},
                              {0, 0, 0, 0, 0, 0, 0, 0},
                              {0, 0, 0, 0, 0, 0, 0, 0},
                              {0, 0, 0, 0, 0, 0, 0, 0},
                              {0, 0, 0, 0, 0, 0, 0, 0}};

    // white pawns

    if (this -> getside() == 'W') {

        // forward one
        if (this -> getrow() != 0 && board[this -> getcol()][this -> getrow() - 1] == nullPiece)
            validMoveset[this -> getcol()][this -> getrow() - 1] = 1;

        // forward two
        if (this -> getmoved() == false && board[this -> getcol()][this -> getrow() - 2] == nullPiece)
            validMoveset[this -> getcol()][this -> getrow() - 2] = 1;

        // take left 
        if (this -> getrow() != 0 && board[this -> getcol() - 1][this -> getrow() - 1] -> getside() == 'B')
            validMoveset[this -> getcol() - 1][this -> getrow() - 1] = 2;

        // take right
        if (this -> getrow() != 0 && board[this -> getcol() + 1][this -> getrow() - 1] -> getside() == 'B')
            validMoveset[this -> getcol() + 1][this -> getrow() - 1] = 2;
    }

    // black pawns

    else if (this -> getside() == 'B') {

        // forward one
        if (this -> getrow() != 7 && board[this -> getcol()][this -> getrow() + 1] == nullPiece)
            validMoveset[this -> getcol()][this -> getrow() + 1] = 1;

        // forward two
        if (this -> getmoved() == false && board[this -> getcol()][this -> getrow() + 2] == nullPiece)
            validMoveset[this -> getcol()][this -> getrow() + 2] = 1;

        // take left 
        if (this -> getrow() != 7 && board[this -> getcol() - 1][this -> getrow() + 1] -> getside() == 'W')
            validMoveset[this -> getcol() - 1][this -> getrow() + 1] = 2;

        // take right
        if (this -> getrow() != 7 && board[this -> getcol() + 1][this -> getrow() + 1] -> getside() == 'W')
            validMoveset[this -> getcol() + 1][this -> getrow() + 1] = 2;
    }

    // print moveset
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++)
            std::cout<<validMoveset[j][i]<<" ";
        std::cout<<std::endl;
    }

    if (validMoveset[col][row] != 0) {
        board[col][row] -> setingame(false);

        int tempCol = this -> getcol();
        int tempRow = this -> getrow();
        this -> setcol(col);
        this -> setrow(row);

        if (this -> getmoved() == false)
            this -> setmoved(true);

        board[tempCol][tempRow] = nullPiece;
        board[col][row] = this;
    }

    else
        std::cout << "Can't move there" << std::endl;
}

Knight::Knight(char side, int col, int row) {
    this -> setid('N');
    this -> setside(side);
    this -> setcol(col);
    this -> setrow(row);
    this -> setingame(true);
    this -> setmoved(false);
    board[col][row] = this;
}

void Knight::move(int col, int row) {

    if (col > 7 || col < 0 || row > 7 || row < 0) {
        std::cout << "Invalid move" << std::endl;
        return;
    }

    // moveset where 1 indicates moveable, 2 indicates takeable, maybe other implementations

    int validMoveset[8][8] = {{0, 0, 0, 0, 0, 0, 0, 0},
                              {0, 0, 0, 0, 0, 0, 0, 0},
                              {0, 0, 0, 0, 0, 0, 0, 0},
                              {0, 0, 0, 0, 0, 0, 0, 0},
                              {0, 0, 0, 0, 0, 0, 0, 0},
                              {0, 0, 0, 0, 0, 0, 0, 0},
                              {0, 0, 0, 0, 0, 0, 0, 0},
                              {0, 0, 0, 0, 0, 0, 0, 0}};
    
    int colTile, rowTile;

    // l2d1
    colTile = this -> getcol() - 2;
    rowTile = this -> getrow() + 1;

    if (colTile >= 0 && colTile <= 7 && rowTile >= 0 && rowTile <= 7) {
        if (board[colTile][rowTile] == nullPiece)
            validMoveset[colTile][rowTile] = 1;

        else if (board[colTile][rowTile] -> getside() != this -> getside())
            validMoveset[colTile][rowTile] = 2;
    }

    // l2u1
    colTile = this -> getcol() - 2;
    rowTile = this -> getrow() - 1;

    if (colTile >= 0 && colTile <= 7 && rowTile >= 0 && rowTile <= 7) {
        if (board[colTile][rowTile] == nullPiece)
            validMoveset[colTile][rowTile] = 1;

        else if (board[colTile][rowTile] -> getside() != this -> getside())
            validMoveset[colTile][rowTile] = 2;
    }

    // r2d1
    colTile = this -> getcol() + 2;
    rowTile = this -> getrow() + 1;

    if (colTile >= 0 && colTile <= 7 && rowTile >= 0 && rowTile <= 7) {
        if (board[colTile][rowTile] == nullPiece)
            validMoveset[colTile][rowTile] = 1;

        else if (board[colTile][rowTile] -> getside() != this -> getside())
            validMoveset[colTile][rowTile] = 2;
    }

    // r2u1
    colTile = this -> getcol() + 2;
    rowTile = this -> getrow() - 1;

    if (colTile >= 0 && colTile <= 7 && rowTile >= 0 && rowTile <= 7) {
        if (board[colTile][rowTile] == nullPiece)
            validMoveset[colTile][rowTile] = 1;

        else if (board[colTile][rowTile] -> getside() != this -> getside())
            validMoveset[colTile][rowTile] = 2;
    }

    // u2l1
    colTile = this -> getcol() - 1;
    rowTile = this -> getrow() - 2;

    if (colTile >= 0 && colTile <= 7 && rowTile >= 0 && rowTile <= 7) {
        if (board[colTile][rowTile] == nullPiece)
            validMoveset[colTile][rowTile] = 1;

        else if (board[colTile][rowTile] -> getside() != this -> getside())
            validMoveset[colTile][rowTile] = 2;
    }

    // u2r1
    colTile = this -> getcol() + 1;
    rowTile = this -> getrow() - 2;

    if (colTile >= 0 && colTile <= 7 && rowTile >= 0 && rowTile <= 7) {
        if (board[colTile][rowTile] == nullPiece)
            validMoveset[colTile][rowTile] = 1;

        else if (board[colTile][rowTile] -> getside() != this -> getside())
            validMoveset[colTile][rowTile] = 2;
    }

    // d2l1
    colTile = this -> getcol() - 1;
    rowTile = this -> getrow() + 2;

    if (colTile >= 0 && colTile <= 7 && rowTile >= 0 && rowTile <= 7) {
        if (board[colTile][rowTile] == nullPiece)
            validMoveset[colTile][rowTile] = 1;

        else if (board[colTile][rowTile] -> getside() != this -> getside())
            validMoveset[colTile][rowTile] = 2;
    }

    // d2r1
    colTile = this -> getcol() + 1;
    rowTile = this -> getrow() + 2;

    if (colTile >= 0 && colTile <= 7 && rowTile >= 0 && rowTile <= 7) {
        if (board[colTile][rowTile] == nullPiece)
            validMoveset[colTile][rowTile] = 1;

        else if (board[colTile][rowTile] -> getside() != this -> getside())
            validMoveset[colTile][rowTile] = 2;
    }

    // print moveset
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++)
            std::cout<<validMoveset[j][i]<<" ";
        std::cout<<std::endl;
    }

    if (validMoveset[col][row] != 0) {
        board[col][row] -> setingame(false);

        int tempCol = this -> getcol();
        int tempRow = this -> getrow();
        this -> setcol(col);
        this -> setrow(row);

        if (this -> getmoved() == false)
            this -> setmoved(true);

        board[tempCol][tempRow] = nullPiece;
        board[col][row] = this;
    }

    else
        std::cout << "Can't move there" << std::endl;
}

Bishop::Bishop(char side, int col, int row) {
    this -> setid('B');
    this -> setside(side);
    this -> setcol(col);
    this -> setrow(row);
    this -> setingame(true);
    this -> setmoved(false);
    board[col][row] = this;
}

void Bishop::move(int col, int row) {

    if (col > 7 || col < 0 || row > 7 || row < 0) {
        std::cout << "Invalid move" << std::endl;
        return;
    }

    // moveset where 1 indicates moveable, 2 indicates takeable, maybe other implementations

    int validMoveset[8][8] = {{0, 0, 0, 0, 0, 0, 0, 0},
                              {0, 0, 0, 0, 0, 0, 0, 0},
                              {0, 0, 0, 0, 0, 0, 0, 0},
                              {0, 0, 0, 0, 0, 0, 0, 0},
                              {0, 0, 0, 0, 0, 0, 0, 0},
                              {0, 0, 0, 0, 0, 0, 0, 0},
                              {0, 0, 0, 0, 0, 0, 0, 0},
                              {0, 0, 0, 0, 0, 0, 0, 0}};
    
    int colTile, rowTile;

    // left down
    colTile = this -> getcol();
    rowTile = this -> getrow();

    while (colTile >= 0 && rowTile <= 7) {
        if (board[colTile][rowTile] == nullPiece)
            validMoveset[colTile][rowTile] = 1;

        else if (board[colTile][rowTile] -> getside() != this -> getside()) {
            validMoveset[colTile][rowTile] = 2;
            break;
        }
        colTile--;
        rowTile++;
    }

    // left up
    colTile = this -> getcol();
    rowTile = this -> getrow();

    while (colTile >= 0 && rowTile >= 0) {
        if (board[colTile][rowTile] == nullPiece)
            validMoveset[colTile][rowTile] = 1;

        else if (board[colTile][rowTile] -> getside() != this -> getside()) {
            validMoveset[colTile][rowTile] = 2;
            break;
        }
        colTile--;
        rowTile--;
    }

    // right down
    colTile = this -> getcol();
    rowTile = this -> getrow();

    while (colTile <= 7 && rowTile <= 7) {
        if (board[colTile][rowTile] == nullPiece)
            validMoveset[colTile][rowTile] = 1;

        else if (board[colTile][rowTile] -> getside() != this -> getside()) {
            validMoveset[colTile][rowTile] = 2;
            break;
        }
        colTile++;
        rowTile++;
    }

    // right up
    colTile = this -> getcol();
    rowTile = this -> getrow();

    while (colTile <= 7 && rowTile >= 0) {
        if (board[colTile][rowTile] == nullPiece)
            validMoveset[colTile][rowTile] = 1;

        else if (board[colTile][rowTile] -> getside() != this -> getside()) {
            validMoveset[colTile][rowTile] = 2;
            break;
        }
        colTile++;
        rowTile--;
    }

    // print moveset
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++)
            std::cout<<validMoveset[j][i]<<" ";
        std::cout<<std::endl;
    }

    if (validMoveset[col][row] != 0) {
        board[col][row] -> setingame(false);

        int tempCol = this -> getcol();
        int tempRow = this -> getrow();
        this -> setcol(col);
        this -> setrow(row);

        if (this -> getmoved() == false)
            this -> setmoved(true);

        board[tempCol][tempRow] = nullPiece;
        board[col][row] = this;
    }

    else
        std::cout << "Can't move there" << std::endl;
}

Rook::Rook(char side, int col, int row) {
    this -> setid('R');
    this -> setside(side);
    this -> setcol(col);
    this -> setrow(row);
    this -> setingame(true);
    this -> setmoved(false);
    board[col][row] = this;
}

void Rook::move(int col, int row) {

    if (col > 7 || col < 0 || row > 7 || row < 0) {
        std::cout << "Invalid move" << std::endl;
        return;
    }

    // moveset where 1 indicates moveable, 2 indicates takeable, maybe other implementations

    int validMoveset[8][8] = {{0, 0, 0, 0, 0, 0, 0, 0},
                              {0, 0, 0, 0, 0, 0, 0, 0},
                              {0, 0, 0, 0, 0, 0, 0, 0},
                              {0, 0, 0, 0, 0, 0, 0, 0},
                              {0, 0, 0, 0, 0, 0, 0, 0},
                              {0, 0, 0, 0, 0, 0, 0, 0},
                              {0, 0, 0, 0, 0, 0, 0, 0},
                              {0, 0, 0, 0, 0, 0, 0, 0}};

    int tile;
    
    // left columns
    tile = this -> getcol();
    while (tile >= 0) {
        if (board[tile][this -> getrow()] == nullPiece)
            validMoveset[tile][this -> getrow()] = 1;

        else if (board[tile][this -> getrow()] -> getside() != this -> getside()) {
            validMoveset[tile][this -> getrow()] = 2;
            break;
        }
        tile--;
    }

    // right columns
    tile = this -> getcol();
    while (tile <= 7) {
        if (board[tile][this -> getrow()] == nullPiece)
            validMoveset[tile][this -> getrow()] = 1;

        else if (board[tile][this -> getrow()] -> getside() != this -> getside()) {
            validMoveset[tile][this -> getrow()] = 2;
            break;
        }
        tile++;
    }

    // rows upward
    tile = this -> getrow();
    while (tile >= 0) {
        if (board[this -> getcol()][tile] == nullPiece)
            validMoveset[this -> getcol()][tile] = 1;

        else if (board[this -> getcol()][tile] -> getside() != this -> getside()) {
            validMoveset[this -> getcol()][tile] = 2;
            break;
        }
        tile--;
    }

    // rows downward
    tile = this -> getrow();
    while (tile <= 7) {
        if (board[this -> getcol()][tile] == nullPiece)
            validMoveset[this -> getcol()][tile] = 1;

        else if (board[this -> getcol()][tile] -> getside() != this -> getside()) {
            validMoveset[this -> getcol()][tile] = 2;
            break;
        }
        tile++;
    }

    // print moveset
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++)
            std::cout<<validMoveset[j][i]<<" ";
        std::cout<<std::endl;
    }

    if (validMoveset[col][row] != 0) {
        board[col][row] -> setingame(false);

        int tempCol = this -> getcol();
        int tempRow = this -> getrow();
        this -> setcol(col);
        this -> setrow(row);

        if (this -> getmoved() == false)
            this -> setmoved(true);

        board[tempCol][tempRow] = nullPiece;
        board[col][row] = this;
    }

    else
        std::cout << "Can't move there" << std::endl;
}

Queen::Queen(char side, int col, int row) {
    this -> setid('Q');
    this -> setside(side);
    this -> setcol(col);
    this -> setrow(row);
    this -> setingame(true);
    this -> setmoved(false);
    board[col][row] = this;
}

void Queen::move(int col, int row) {

    if (col > 7 || col < 0 || row > 7 || row < 0) {
        std::cout << "Invalid move" << std::endl;
        return;
    }

    // moveset where 1 indicates moveable, 2 indicates takeable, maybe other implementations

    int validMoveset[8][8] = {{0, 0, 0, 0, 0, 0, 0, 0},
                              {0, 0, 0, 0, 0, 0, 0, 0},
                              {0, 0, 0, 0, 0, 0, 0, 0},
                              {0, 0, 0, 0, 0, 0, 0, 0},
                              {0, 0, 0, 0, 0, 0, 0, 0},
                              {0, 0, 0, 0, 0, 0, 0, 0},
                              {0, 0, 0, 0, 0, 0, 0, 0},
                              {0, 0, 0, 0, 0, 0, 0, 0}};
    
    int colTile, rowTile;

    // left down
    colTile = this -> getcol();
    rowTile = this -> getrow();

    while (colTile >= 0 && rowTile <= 7) {
        if (board[colTile][rowTile] == nullPiece)
            validMoveset[colTile][rowTile] = 1;

        else if (board[colTile][rowTile] -> getside() != this -> getside()) {
            validMoveset[colTile][rowTile] = 2;
            break;
        }
        colTile--;
        rowTile++;
    }

    // left up
    colTile = this -> getcol();
    rowTile = this -> getrow();

    while (colTile >= 0 && rowTile >= 0) {
        if (board[colTile][rowTile] == nullPiece)
            validMoveset[colTile][rowTile] = 1;

        else if (board[colTile][rowTile] -> getside() != this -> getside()) {
            validMoveset[colTile][rowTile] = 2;
            break;
        }
        colTile--;
        rowTile--;
    }

    // right down
    colTile = this -> getcol();
    rowTile = this -> getrow();

    while (colTile <= 7 && rowTile <= 7) {
        if (board[colTile][rowTile] == nullPiece)
            validMoveset[colTile][rowTile] = 1;

        else if (board[colTile][rowTile] -> getside() != this -> getside()) {
            validMoveset[colTile][rowTile] = 2;
            break;
        }
        colTile++;
        rowTile++;
    }

    // right up
    colTile = this -> getcol();
    rowTile = this -> getrow();

    while (colTile <= 7 && rowTile >= 0) {
        if (board[colTile][rowTile] == nullPiece)
            validMoveset[colTile][rowTile] = 1;

        else if (board[colTile][rowTile] -> getside() != this -> getside()) {
            validMoveset[colTile][rowTile] = 2;
            break;
        }
        colTile++;
        rowTile--;
    }

    // left columns

    rowTile = this -> getrow();
    colTile = this -> getcol();

    while (colTile >= 0) {
        if (board[colTile][rowTile] == nullPiece)
            validMoveset[colTile][rowTile] = 1;

        else if (board[colTile][rowTile] -> getside() != this -> getside()) {
            validMoveset[colTile][rowTile] = 2;
            break;
        }
        colTile--;
    }

    // right columns
    
    rowTile = this -> getrow();
    colTile = this -> getcol();

    while (colTile <= 7) {
        if (board[colTile][rowTile] == nullPiece)
            validMoveset[colTile][rowTile] = 1;

        else if (board[colTile][rowTile] -> getside() != this -> getside()) {
            validMoveset[colTile][rowTile] = 2;
            break;
        }
        colTile++;
    }

    // rows upward
    rowTile = this -> getrow();
    colTile = this -> getcol();

    while (rowTile >= 0) {
        if (board[colTile][rowTile] == nullPiece)
            validMoveset[colTile][rowTile] = 1;

        else if (board[colTile][rowTile] -> getside() != this -> getside()) {
            validMoveset[colTile][rowTile] = 2;
            break;
        }
        rowTile--;
    }

    // rows downward
    
    rowTile = this -> getrow();
    colTile = this -> getcol();

    while (rowTile <= 7) {
        if (board[colTile][rowTile] == nullPiece)
            validMoveset[colTile][rowTile] = 1;

        else if (board[colTile][rowTile] -> getside() != this -> getside()) {
            validMoveset[colTile][rowTile] = 2;
            break;
        }
        rowTile++;
    }

    // print moveset
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++)
            std::cout<<validMoveset[j][i]<<" ";
        std::cout<<std::endl;
    }

    if (validMoveset[col][row] != 0) {
        board[col][row] -> setingame(false);

        int tempCol = this -> getcol();
        int tempRow = this -> getrow();
        this -> setcol(col);
        this -> setrow(row);

        if (this -> getmoved() == false)
            this -> setmoved(true);

        board[tempCol][tempRow] = nullPiece;
        board[col][row] = this;
    }

    else
        std::cout << "Can't move there" << std::endl;
}

King::King(char side, int col, int row) {
    this -> setid('K');
    this -> setside(side);
    this -> setcol(col);
    this -> setrow(row);
    this -> setingame(true);
    this -> setmoved(false);
    board[col][row] = this;
}

void King::move(int col, int row) {

    if (col > 7 || col < 0 || row > 7 || row < 0) {
        std::cout << "Invalid move" << std::endl;
        return;
    }

    // moveset where 1 indicates moveable, 2 indicates takeable, maybe other implementations

    int validMoveset[8][8] = {{0, 0, 0, 0, 0, 0, 0, 0},
                              {0, 0, 0, 0, 0, 0, 0, 0},
                              {0, 0, 0, 0, 0, 0, 0, 0},
                              {0, 0, 0, 0, 0, 0, 0, 0},
                              {0, 0, 0, 0, 0, 0, 0, 0},
                              {0, 0, 0, 0, 0, 0, 0, 0},
                              {0, 0, 0, 0, 0, 0, 0, 0},
                              {0, 0, 0, 0, 0, 0, 0, 0}};
    
    int colTile, rowTile;

    // left
    colTile = this -> getcol() - 1;
    rowTile = this -> getrow();

    if (colTile >= 0 && colTile <= 7 && rowTile >= 0 && rowTile <= 7) {
        if (board[colTile][rowTile] == nullPiece)
            validMoveset[colTile][rowTile] = 1;

        else if (board[colTile][rowTile] -> getside() != this -> getside())
            validMoveset[colTile][rowTile] = 2;
    }

    // right
    colTile = this -> getcol() + 1;
    rowTile = this -> getrow();

    if (colTile >= 0 && colTile <= 7 && rowTile >= 0 && rowTile <= 7) {
        if (board[colTile][rowTile] == nullPiece)
            validMoveset[colTile][rowTile] = 1;

        else if (board[colTile][rowTile] -> getside() != this -> getside())
            validMoveset[colTile][rowTile] = 2;
    }

    // up
    colTile = this -> getcol();
    rowTile = this -> getrow() - 1;

    if (colTile >= 0 && colTile <= 7 && rowTile >= 0 && rowTile <= 7) {
        if (board[colTile][rowTile] == nullPiece)
            validMoveset[colTile][rowTile] = 1;

        else if (board[colTile][rowTile] -> getside() != this -> getside())
            validMoveset[colTile][rowTile] = 2;
    }

    // down
    colTile = this -> getcol();
    rowTile = this -> getrow() + 1;

    if (colTile >= 0 && colTile <= 7 && rowTile >= 0 && rowTile <= 7) {
        if (board[colTile][rowTile] == nullPiece)
            validMoveset[colTile][rowTile] = 1;

        else if (board[colTile][rowTile] -> getside() != this -> getside())
            validMoveset[colTile][rowTile] = 2;
    }

    // left up
    colTile = this -> getcol() - 1;
    rowTile = this -> getrow() - 1;

    if (colTile >= 0 && colTile <= 7 && rowTile >= 0 && rowTile <= 7) {
        if (board[colTile][rowTile] == nullPiece)
            validMoveset[colTile][rowTile] = 1;

        else if (board[colTile][rowTile] -> getside() != this -> getside())
            validMoveset[colTile][rowTile] = 2;
    }

    // left down
    colTile = this -> getcol() - 1;
    rowTile = this -> getrow() + 1;

    if (colTile >= 0 && colTile <= 7 && rowTile >= 0 && rowTile <= 7) {
        if (board[colTile][rowTile] == nullPiece)
            validMoveset[colTile][rowTile] = 1;

        else if (board[colTile][rowTile] -> getside() != this -> getside())
            validMoveset[colTile][rowTile] = 2;
    }

    // right up
    colTile = this -> getcol() + 1;
    rowTile = this -> getrow() - 1;

    if (colTile >= 0 && colTile <= 7 && rowTile >= 0 && rowTile <= 7) {
        if (board[colTile][rowTile] == nullPiece)
            validMoveset[colTile][rowTile] = 1;

        else if (board[colTile][rowTile] -> getside() != this -> getside())
            validMoveset[colTile][rowTile] = 2;
    }

    // right down
    colTile = this -> getcol() + 1;
    rowTile = this -> getrow() + 1;

    if (colTile >= 0 && colTile <= 7 && rowTile >= 0 && rowTile <= 7) {
        if (board[colTile][rowTile] == nullPiece)
            validMoveset[colTile][rowTile] = 1;

        else if (board[colTile][rowTile] -> getside() != this -> getside())
            validMoveset[colTile][rowTile] = 2;
    }

    // print moveset
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++)
            std::cout<<validMoveset[j][i]<<" ";
        std::cout<<std::endl;
    }

    if (validMoveset[col][row] != 0) {
        board[col][row] -> setingame(false);

        int tempCol = this -> getcol();
        int tempRow = this -> getrow();
        this -> setcol(col);
        this -> setrow(row);

        if (this -> getmoved() == false)
            this -> setmoved(true);

        board[tempCol][tempRow] = nullPiece;
        board[col][row] = this;
    }

    else
        std::cout << "Can't move there" << std::endl;
}

Rook *b_r1 = new Rook('B', 0, 0);
Knight *b_n1 = new Knight('B', 1, 0);
Bishop *b_b1 = new Bishop('B', 2, 0);
Queen *b_q = new Queen('B', 3, 0);
King *b_k = new King('B', 4, 0);
Bishop *b_b2 = new Bishop('B', 5, 0);
Knight *b_n2 = new Knight('B', 6, 0);
Rook *b_r2 = new Rook('B', 7, 0);
Pawn *b_p1 = new Pawn('B', 0, 1);
Pawn *b_p2 = new Pawn('B', 1, 1);
Pawn *b_p3 = new Pawn('B', 2, 1);
Pawn *b_p4 = new Pawn('B', 3, 1);
Pawn *b_p5 = new Pawn('B', 4, 1);
Pawn *b_p6 = new Pawn('B', 5, 1);
Pawn *b_p7 = new Pawn('B', 6, 1);
Pawn *b_p8 = new Pawn('B', 7, 1);

Rook *w_r1 = new Rook('W', 0, 7);
Knight *w_n1 = new Knight('W', 1, 7);
Bishop *w_b1 = new Bishop('W', 2, 7);
Queen *w_q = new Queen('W', 3, 7);
King *w_k = new King('W', 4, 7);
Bishop *w_b2 = new Bishop('W', 5, 7);
Knight *w_n2 = new Knight('W', 6, 7);
Rook *w_r2 = new Rook('W', 7, 7);
Pawn *w_p1 = new Pawn('W', 0, 6);
Pawn *w_p2 = new Pawn('W', 1, 6);
Pawn *w_p3 = new Pawn('W', 2, 6);
Pawn *w_p4 = new Pawn('W', 3, 6);
Pawn *w_p5 = new Pawn('W', 4, 6);
Pawn *w_p6 = new Pawn('W', 5, 6);
Pawn *w_p7 = new Pawn('W', 6, 6);
Pawn *w_p8 = new Pawn('W', 7, 6);

void initBoard() {

    for (int i = 2; i < 6; i++)
        for (int j = 0; j < 8; j++) 
            board[j][i] = nullPiece;
}

void printBoard() {

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            ptrPce = board[j][i];
            std::cout << ptrPce -> getid() << " ";
        }
        std::cout<<std::endl;
    }
}

int main() {
    initBoard();
    
    board[1][7] -> move(2, 5);

    printBoard();
    return 0;
}