#include <iostream>

char turn = 'W';
int moveMatrix[8][8];

void resetMoveset() {
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            moveMatrix[j][i] = 0;
}

void printMoveset() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++)
            std::cout << moveMatrix[j][i] << " ";
        std::cout << std::endl;
    }
}

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
    virtual bool move(int arg1, int arg2);
    virtual void gatherMatrix();

    Piece();
};

Piece::Piece() {
    this -> setid('-');
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

bool Piece::move(int arg1, int arg2) { std::cout<<"This piece is not in the game"<<std::endl; return false; }
void Piece::gatherMatrix() { return; }

Piece *board[8][8];
Piece *ptrPce;
Piece *nullPiece = new Piece();

class Pawn: public Piece {
public:
    bool move(int col, int row);
    void gatherMatrix();
    Pawn(char side, int col, int row);
};

class Knight: public Piece {
public:
    bool move(int col, int row);
    void gatherMatrix();
    Knight(char side, int col, int row);
};

class Bishop: public Piece {
public:
    bool move(int col, int row);
    void gatherMatrix();
    Bishop(char side, int col, int row);
};

class Rook: public Piece {
public:
    bool move(int col, int row);
    void gatherMatrix();
    Rook(char side, int col, int row);
};

class Queen: public Piece {
public:
    bool move(int col, int row);
    void gatherMatrix();
    Queen(char side, int col, int row);
};

class King: public Piece {
public:
    bool move(int col, int row);
    void gatherMatrix();
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

void Pawn::gatherMatrix() {
    if (this -> getside() == 'W') {

        // forward one
        if (this -> getrow() != 0 && board[this -> getcol()][this -> getrow() - 1] == nullPiece)
            moveMatrix[this -> getcol()][this -> getrow() - 1] = 1;

        // forward two
        if (this -> getmoved() == false && board[this -> getcol()][this -> getrow() - 2] == nullPiece)
            moveMatrix[this -> getcol()][this -> getrow() - 2] = 1;

        // take left 
        if (this -> getrow() != 0 && board[this -> getcol() - 1][this -> getrow() - 1] -> getside() == 'B')
            moveMatrix[this -> getcol() - 1][this -> getrow() - 1] = 2;

        // take right
        if (this -> getrow() != 0 && board[this -> getcol() + 1][this -> getrow() - 1] -> getside() == 'B')
            moveMatrix[this -> getcol() + 1][this -> getrow() - 1] = 2;
    }

    else if (this -> getside() == 'B') {

        // forward one
        if (this -> getrow() != 7 && board[this -> getcol()][this -> getrow() + 1] == nullPiece)
            moveMatrix[this -> getcol()][this -> getrow() + 1] = 1;

        // forward two
        if (this -> getmoved() == false && board[this -> getcol()][this -> getrow() + 2] == nullPiece)
            moveMatrix[this -> getcol()][this -> getrow() + 2] = 1;

        // take left 
        if (this -> getrow() != 7 && board[this -> getcol() - 1][this -> getrow() + 1] -> getside() == 'W')
            moveMatrix[this -> getcol() - 1][this -> getrow() + 1] = 2;

        // take right
        if (this -> getrow() != 7 && board[this -> getcol() + 1][this -> getrow() + 1] -> getside() == 'W')
            moveMatrix[this -> getcol() + 1][this -> getrow() + 1] = 2;
    }
}

bool Pawn::move(int col, int row) {
    if (col > 7 || col < 0 || row > 7 || row < 0) {
        std::cout << "Invalid move" << std::endl;
        return false;
    }

    resetMoveset();
    gatherMatrix();
    printMoveset();

    if (moveMatrix[col][row] != 0) {
        board[col][row] -> setingame(false);

        int tempCol = this -> getcol();
        int tempRow = this -> getrow();
        this -> setcol(col);
        this -> setrow(row);

        if (this -> getmoved() == false)
            this -> setmoved(true);

        board[tempCol][tempRow] = nullPiece;
        board[col][row] = this;
        return true;
    }
    
    std::cout << "Can't move there" << std::endl;
    return false;
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

void Knight::gatherMatrix() {
    int colTile, rowTile;

    // l2d1
    colTile = this -> getcol() - 2;
    rowTile = this -> getrow() + 1;

    if (colTile >= 0 && colTile <= 7 && rowTile >= 0 && rowTile <= 7) {
        if (board[colTile][rowTile] == nullPiece)
            moveMatrix[colTile][rowTile] = 1;

        else if (board[colTile][rowTile] -> getside() != this -> getside())
            moveMatrix[colTile][rowTile] = 2;
    }

    // l2u1
    colTile = this -> getcol() - 2;
    rowTile = this -> getrow() - 1;

    if (colTile >= 0 && colTile <= 7 && rowTile >= 0 && rowTile <= 7) {
        if (board[colTile][rowTile] == nullPiece)
            moveMatrix[colTile][rowTile] = 1;

        else if (board[colTile][rowTile] -> getside() != this -> getside())
            moveMatrix[colTile][rowTile] = 2;
    }

    // r2d1
    colTile = this -> getcol() + 2;
    rowTile = this -> getrow() + 1;

    if (colTile >= 0 && colTile <= 7 && rowTile >= 0 && rowTile <= 7) {
        if (board[colTile][rowTile] == nullPiece)
            moveMatrix[colTile][rowTile] = 1;

        else if (board[colTile][rowTile] -> getside() != this -> getside())
            moveMatrix[colTile][rowTile] = 2;
    }

    // r2u1
    colTile = this -> getcol() + 2;
    rowTile = this -> getrow() - 1;

    if (colTile >= 0 && colTile <= 7 && rowTile >= 0 && rowTile <= 7) {
        if (board[colTile][rowTile] == nullPiece)
            moveMatrix[colTile][rowTile] = 1;

        else if (board[colTile][rowTile] -> getside() != this -> getside())
            moveMatrix[colTile][rowTile] = 2;
    }

    // u2l1
    colTile = this -> getcol() - 1;
    rowTile = this -> getrow() - 2;

    if (colTile >= 0 && colTile <= 7 && rowTile >= 0 && rowTile <= 7) {
        if (board[colTile][rowTile] == nullPiece)
            moveMatrix[colTile][rowTile] = 1;

        else if (board[colTile][rowTile] -> getside() != this -> getside())
            moveMatrix[colTile][rowTile] = 2;
    }

    // u2r1
    colTile = this -> getcol() + 1;
    rowTile = this -> getrow() - 2;

    if (colTile >= 0 && colTile <= 7 && rowTile >= 0 && rowTile <= 7) {
        if (board[colTile][rowTile] == nullPiece)
            moveMatrix[colTile][rowTile] = 1;

        else if (board[colTile][rowTile] -> getside() != this -> getside())
            moveMatrix[colTile][rowTile] = 2;
    }

    // d2l1
    colTile = this -> getcol() - 1;
    rowTile = this -> getrow() + 2;

    if (colTile >= 0 && colTile <= 7 && rowTile >= 0 && rowTile <= 7) {
        if (board[colTile][rowTile] == nullPiece)
            moveMatrix[colTile][rowTile] = 1;

        else if (board[colTile][rowTile] -> getside() != this -> getside())
            moveMatrix[colTile][rowTile] = 2;
    }

    // d2r1
    colTile = this -> getcol() + 1;
    rowTile = this -> getrow() + 2;

    if (colTile >= 0 && colTile <= 7 && rowTile >= 0 && rowTile <= 7) {
        if (board[colTile][rowTile] == nullPiece)
            moveMatrix[colTile][rowTile] = 1;

        else if (board[colTile][rowTile] -> getside() != this -> getside())
            moveMatrix[colTile][rowTile] = 2;
    }
}

bool Knight::move(int col, int row) {
    if (col > 7 || col < 0 || row > 7 || row < 0) {
        std::cout << "Invalid move" << std::endl;
        return false;
    }

    resetMoveset();
    gatherMatrix();
    printMoveset();

    if (moveMatrix[col][row] != 0) {
        board[col][row] -> setingame(false);

        int tempCol = this -> getcol();
        int tempRow = this -> getrow();
        this -> setcol(col);
        this -> setrow(row);

        if (this -> getmoved() == false)
            this -> setmoved(true);

        board[tempCol][tempRow] = nullPiece;
        board[col][row] = this;
        return true;
    }
    
    std::cout << "Can't move there" << std::endl;
    return false;
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

void Bishop::gatherMatrix() {
    int colTile, rowTile;

    // left down
    colTile = this -> getcol();
    rowTile = this -> getrow();

    while (colTile >= 0 && rowTile <= 7) {
        if (board[colTile][rowTile] == nullPiece)
            moveMatrix[colTile][rowTile] = 1;

        else if (board[colTile][rowTile] -> getside() != this -> getside()) {
            moveMatrix[colTile][rowTile] = 2;
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
            moveMatrix[colTile][rowTile] = 1;

        else if (board[colTile][rowTile] -> getside() != this -> getside()) {
            moveMatrix[colTile][rowTile] = 2;
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
            moveMatrix[colTile][rowTile] = 1;

        else if (board[colTile][rowTile] -> getside() != this -> getside()) {
            moveMatrix[colTile][rowTile] = 2;
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
            moveMatrix[colTile][rowTile] = 1;

        else if (board[colTile][rowTile] -> getside() != this -> getside()) {
            moveMatrix[colTile][rowTile] = 2;
            break;
        }
        colTile++;
        rowTile--;
    }
}

bool Bishop::move(int col, int row) {
    if (col > 7 || col < 0 || row > 7 || row < 0) {
        std::cout << "Invalid move" << std::endl;
        return false;
    }

    resetMoveset();
    gatherMatrix();
    printMoveset();

    if (moveMatrix[col][row] != 0) {
        board[col][row] -> setingame(false);

        int tempCol = this -> getcol();
        int tempRow = this -> getrow();
        this -> setcol(col);
        this -> setrow(row);

        if (this -> getmoved() == false)
            this -> setmoved(true);

        board[tempCol][tempRow] = nullPiece;
        board[col][row] = this;
        return true;
    }
    
    std::cout << "Can't move there" << std::endl;
    return false;
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

void Rook::gatherMatrix() {
    int tile;
    
    // left columns
    tile = this -> getcol();
    while (tile >= 0) {
        if (board[tile][this -> getrow()] == nullPiece)
            moveMatrix[tile][this -> getrow()] = 1;

        else if (board[tile][this -> getrow()] -> getside() != this -> getside()) {
            moveMatrix[tile][this -> getrow()] = 2;
            break;
        }
        tile--;
    }

    // right columns
    tile = this -> getcol();
    while (tile <= 7) {
        if (board[tile][this -> getrow()] == nullPiece)
            moveMatrix[tile][this -> getrow()] = 1;

        else if (board[tile][this -> getrow()] -> getside() != this -> getside()) {
            moveMatrix[tile][this -> getrow()] = 2;
            break;
        }
        tile++;
    }

    // rows upward
    tile = this -> getrow();
    while (tile >= 0) {
        if (board[this -> getcol()][tile] == nullPiece)
            moveMatrix[this -> getcol()][tile] = 1;

        else if (board[this -> getcol()][tile] -> getside() != this -> getside()) {
            moveMatrix[this -> getcol()][tile] = 2;
            break;
        }
        tile--;
    }

    // rows downward
    tile = this -> getrow();
    while (tile <= 7) {
        if (board[this -> getcol()][tile] == nullPiece)
            moveMatrix[this -> getcol()][tile] = 1;

        else if (board[this -> getcol()][tile] -> getside() != this -> getside()) {
            moveMatrix[this -> getcol()][tile] = 2;
            break;
        }
        tile++;
    }
}

bool Rook::move(int col, int row) {
    if (col > 7 || col < 0 || row > 7 || row < 0) {
        std::cout << "Invalid move" << std::endl;
        return false;
    }

    resetMoveset();
    gatherMatrix();
    printMoveset();

    if (moveMatrix[col][row] != 0) {
        board[col][row] -> setingame(false);

        int tempCol = this -> getcol();
        int tempRow = this -> getrow();
        this -> setcol(col);
        this -> setrow(row);

        if (this -> getmoved() == false)
            this -> setmoved(true);

        board[tempCol][tempRow] = nullPiece;
        board[col][row] = this;
        return true;
    }
    
    std::cout << "Can't move there" << std::endl;
    return false;
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

void Queen::gatherMatrix() {
    int colTile, rowTile;

    // left down
    colTile = this -> getcol();
    rowTile = this -> getrow();

    while (colTile >= 0 && rowTile <= 7) {
        if (board[colTile][rowTile] == nullPiece)
            moveMatrix[colTile][rowTile] = 1;

        else if (board[colTile][rowTile] -> getside() != this -> getside()) {
            moveMatrix[colTile][rowTile] = 2;
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
            moveMatrix[colTile][rowTile] = 1;

        else if (board[colTile][rowTile] -> getside() != this -> getside()) {
            moveMatrix[colTile][rowTile] = 2;
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
            moveMatrix[colTile][rowTile] = 1;

        else if (board[colTile][rowTile] -> getside() != this -> getside()) {
            moveMatrix[colTile][rowTile] = 2;
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
            moveMatrix[colTile][rowTile] = 1;

        else if (board[colTile][rowTile] -> getside() != this -> getside()) {
            moveMatrix[colTile][rowTile] = 2;
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
            moveMatrix[colTile][rowTile] = 1;

        else if (board[colTile][rowTile] -> getside() != this -> getside()) {
            moveMatrix[colTile][rowTile] = 2;
            break;
        }
        colTile--;
    }

    // right columns
    
    rowTile = this -> getrow();
    colTile = this -> getcol();

    while (colTile <= 7) {
        if (board[colTile][rowTile] == nullPiece)
            moveMatrix[colTile][rowTile] = 1;

        else if (board[colTile][rowTile] -> getside() != this -> getside()) {
            moveMatrix[colTile][rowTile] = 2;
            break;
        }
        colTile++;
    }

    // rows upward
    rowTile = this -> getrow();
    colTile = this -> getcol();

    while (rowTile >= 0) {
        if (board[colTile][rowTile] == nullPiece)
            moveMatrix[colTile][rowTile] = 1;

        else if (board[colTile][rowTile] -> getside() != this -> getside()) {
            moveMatrix[colTile][rowTile] = 2;
            break;
        }
        rowTile--;
    }

    // rows downward
    
    rowTile = this -> getrow();
    colTile = this -> getcol();

    while (rowTile <= 7) {
        if (board[colTile][rowTile] == nullPiece)
            moveMatrix[colTile][rowTile] = 1;

        else if (board[colTile][rowTile] -> getside() != this -> getside()) {
            moveMatrix[colTile][rowTile] = 2;
            break;
        }
        rowTile++;
    }
}

bool Queen::move(int col, int row) {
    if (col > 7 || col < 0 || row > 7 || row < 0) {
        std::cout << "Invalid move" << std::endl;
        return false;
    }

    resetMoveset();
    gatherMatrix();
    printMoveset();

    if (moveMatrix[col][row] != 0) {
        board[col][row] -> setingame(false);

        int tempCol = this -> getcol();
        int tempRow = this -> getrow();
        this -> setcol(col);
        this -> setrow(row);

        if (this -> getmoved() == false)
            this -> setmoved(true);

        board[tempCol][tempRow] = nullPiece;
        board[col][row] = this;
        return true;
    }
    
    std::cout << "Can't move there" << std::endl;
    return false;
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

void King::gatherMatrix() {
    int colTile, rowTile;

    // left
    colTile = this -> getcol() - 1;
    rowTile = this -> getrow();

    if (colTile >= 0 && colTile <= 7 && rowTile >= 0 && rowTile <= 7) {
        if (board[colTile][rowTile] == nullPiece)
            moveMatrix[colTile][rowTile] = 1;

        else if (board[colTile][rowTile] -> getside() != this -> getside())
            moveMatrix[colTile][rowTile] = 2;
    }

    // right
    colTile = this -> getcol() + 1;
    rowTile = this -> getrow();

    if (colTile >= 0 && colTile <= 7 && rowTile >= 0 && rowTile <= 7) {
        if (board[colTile][rowTile] == nullPiece)
            moveMatrix[colTile][rowTile] = 1;

        else if (board[colTile][rowTile] -> getside() != this -> getside())
            moveMatrix[colTile][rowTile] = 2;
    }

    // up
    colTile = this -> getcol();
    rowTile = this -> getrow() - 1;

    if (colTile >= 0 && colTile <= 7 && rowTile >= 0 && rowTile <= 7) {
        if (board[colTile][rowTile] == nullPiece)
            moveMatrix[colTile][rowTile] = 1;

        else if (board[colTile][rowTile] -> getside() != this -> getside())
            moveMatrix[colTile][rowTile] = 2;
    }

    // down
    colTile = this -> getcol();
    rowTile = this -> getrow() + 1;

    if (colTile >= 0 && colTile <= 7 && rowTile >= 0 && rowTile <= 7) {
        if (board[colTile][rowTile] == nullPiece)
            moveMatrix[colTile][rowTile] = 1;

        else if (board[colTile][rowTile] -> getside() != this -> getside())
            moveMatrix[colTile][rowTile] = 2;
    }

    // left up
    colTile = this -> getcol() - 1;
    rowTile = this -> getrow() - 1;

    if (colTile >= 0 && colTile <= 7 && rowTile >= 0 && rowTile <= 7) {
        if (board[colTile][rowTile] == nullPiece)
            moveMatrix[colTile][rowTile] = 1;

        else if (board[colTile][rowTile] -> getside() != this -> getside())
            moveMatrix[colTile][rowTile] = 2;
    }

    // left down
    colTile = this -> getcol() - 1;
    rowTile = this -> getrow() + 1;

    if (colTile >= 0 && colTile <= 7 && rowTile >= 0 && rowTile <= 7) {
        if (board[colTile][rowTile] == nullPiece)
            moveMatrix[colTile][rowTile] = 1;

        else if (board[colTile][rowTile] -> getside() != this -> getside())
            moveMatrix[colTile][rowTile] = 2;
    }

    // right up
    colTile = this -> getcol() + 1;
    rowTile = this -> getrow() - 1;

    if (colTile >= 0 && colTile <= 7 && rowTile >= 0 && rowTile <= 7) {
        if (board[colTile][rowTile] == nullPiece)
            moveMatrix[colTile][rowTile] = 1;

        else if (board[colTile][rowTile] -> getside() != this -> getside())
            moveMatrix[colTile][rowTile] = 2;
    }

    // right down
    colTile = this -> getcol() + 1;
    rowTile = this -> getrow() + 1;

    if (colTile >= 0 && colTile <= 7 && rowTile >= 0 && rowTile <= 7) {
        if (board[colTile][rowTile] == nullPiece)
            moveMatrix[colTile][rowTile] = 1;

        else if (board[colTile][rowTile] -> getside() != this -> getside())
            moveMatrix[colTile][rowTile] = 2;
    }
}

bool King::move(int col, int row) {
    if (col > 7 || col < 0 || row > 7 || row < 0) {
        std::cout << "Invalid move" << std::endl;
        return false;
    }

    resetMoveset();
    gatherMatrix();
    printMoveset();

    if (moveMatrix[col][row] != 0) {
        board[col][row] -> setingame(false);

        int tempCol = this -> getcol();
        int tempRow = this -> getrow();
        this -> setcol(col);
        this -> setrow(row);

        if (this -> getmoved() == false)
            this -> setmoved(true);

        board[tempCol][tempRow] = nullPiece;
        board[col][row] = this;
        return true;
    }

    std::cout << "Can't move there" << std::endl;
    return false;
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

void addNulls() {
    for (int i = 2; i < 6; i++)
        for (int j = 0; j < 8; j++) 
            board[j][i] = nullPiece;
}

void printBoard() {
    for (int i = 0; i < 8; i++) {
        std::cout << 8 - i << " | ";
        for (int j = 0; j < 8; j++) {
            ptrPce = board[j][i];
            std::cout << ptrPce -> getid() << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "  |_________________" << std::endl;
    std::cout << "    A B C D E F G H" << std::endl;
}

int parseInput(std::string str) {
    if (str.at(0) < 'a' || str.at(0) > 'h' || str.at(1) < '1' || str.at(1) > '8') 
        return -1;

    int col;
    int row;

    col = (int)str.at(0) - 97;
    row = 0;

    for (int i = (int)str.at(1) - 48; i < 8; i++)
        row++;

    return (col * 10) + row;
}

void toPlay() {
    // format: d2d4
    std::cout << turn << " to move: ";
    
    std::string input;
    std::cin >> input;

    if (input.length() != 4)
        toPlay();

    int start = parseInput(input.substr(0, 2));
    int end = parseInput(input.substr(2, 2));

    if (start == -1 || end == -1)
        toPlay();

    int startCol = start / 10;
    int startRow = start % 10;

    int endCol = end / 10;
    int endRow = end % 10;

    if (board[startCol][startRow] -> getside() == turn) {
        board[startCol][startRow] -> gatherMatrix();

        if (moveMatrix[endCol][endRow] != 0) {
            board[startCol][startRow] -> move(endCol, endRow);
            turn = (turn == 'B') ? 'W' : 'B';
            return;
        }
    }
    toPlay();
}

int main() {
    addNulls();
    printBoard();

    while (true) {
        toPlay();
        printBoard();
    }
    return 0;
}