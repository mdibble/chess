#include <iostream>

char turn = 'W';
char check = 'N';
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
    virtual bool moveSoft(int arg1, int arg2);
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

void Piece::gatherMatrix() { std::cout << "Test" << std::endl; return; }

Piece *board[8][8];
Piece *ptrPce;
Piece *nullPiece = new Piece();

bool Piece::move(int col, int row) {
    if (col > 7 || col < 0 || row > 7 || row < 0) {
        std::cout << "Invalid move" << std::endl;
        return false;
    }

    if (board[col][row] -> getid() == 'K') {

        std::cout << "Can't capture a king" << std::endl;
        return false;
    }

    if (moveMatrix[col][row] != 0 && moveMatrix[col][row]) {
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

bool Piece::moveSoft(int col, int row) {
    if (col > 7 || col < 0 || row > 7 || row < 0) {
        std::cout << "Invalid move" << std::endl;
        return false;
    }

    if (moveMatrix[col][row] != 0) {

        int tempCol = this -> getcol();
        int tempRow = this -> getrow();
        this -> setcol(col);
        this -> setrow(row);

        board[tempCol][tempRow] = nullPiece;
        board[col][row] = this;
        return true;
    }
    
    std::cout << "Can't move there" << std::endl;
    return false;
}

class Pawn: public Piece {
public:
    void gatherMatrix();
    Pawn(char side, int col, int row);
};

class Knight: public Piece {
public:
    void gatherMatrix();
    Knight(char side, int col, int row);
};

class Bishop: public Piece {
public:
    void gatherMatrix();
    Bishop(char side, int col, int row);
};

class Rook: public Piece {
public:
    void gatherMatrix();
    Rook(char side, int col, int row);
};

class Queen: public Piece {
public:
    void gatherMatrix();
    Queen(char side, int col, int row);
};

class King: public Piece {
public:
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
        if (this -> getrow() != 0 && board[this -> getcol()][this -> getrow() - 1] == nullPiece)
            moveMatrix[this -> getcol()][this -> getrow() - 1] = 1;

        if (this -> getmoved() == false && board[this -> getcol()][this -> getrow() - 2] == nullPiece)
            moveMatrix[this -> getcol()][this -> getrow() - 2] = 1;
 
        if (this -> getrow() != 0 && this -> getcol() != 0 && board[this -> getcol() - 1][this -> getrow() - 1] -> getside() == 'B')
            moveMatrix[this -> getcol() - 1][this -> getrow() - 1] = 2;

        if (this -> getrow() != 0 && this -> getcol() != 7 && board[this -> getcol() + 1][this -> getrow() - 1] -> getside() == 'B')
            moveMatrix[this -> getcol() + 1][this -> getrow() - 1] = 2;
    }

    else if (this -> getside() == 'B') {
        if (this -> getrow() != 7 && board[this -> getcol()][this -> getrow() + 1] == nullPiece)
            moveMatrix[this -> getcol()][this -> getrow() + 1] = 1;

        if (this -> getmoved() == false && board[this -> getcol()][this -> getrow() + 2] == nullPiece)
            moveMatrix[this -> getcol()][this -> getrow() + 2] = 1;

        if (this -> getrow() != 7 && this -> getcol() != 0 && board[this -> getcol() - 1][this -> getrow() + 1] -> getside() == 'W')
            moveMatrix[this -> getcol() - 1][this -> getrow() + 1] = 2;

        if (this -> getrow() != 7 && this -> getcol() != 7 && board[this -> getcol() + 1][this -> getrow() + 1] -> getside() == 'W')
            moveMatrix[this -> getcol() + 1][this -> getrow() + 1] = 2;
    }
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

    colTile = this -> getcol() - 2;
    rowTile = this -> getrow() + 1;

    if (colTile >= 0 && colTile <= 7 && rowTile >= 0 && rowTile <= 7) {
        if (board[colTile][rowTile] == nullPiece)
            moveMatrix[colTile][rowTile] = 1;

        else if (board[colTile][rowTile] -> getside() != this -> getside())
            moveMatrix[colTile][rowTile] = 2;
    }

    colTile = this -> getcol() - 2;
    rowTile = this -> getrow() - 1;

    if (colTile >= 0 && colTile <= 7 && rowTile >= 0 && rowTile <= 7) {
        if (board[colTile][rowTile] == nullPiece)
            moveMatrix[colTile][rowTile] = 1;

        else if (board[colTile][rowTile] -> getside() != this -> getside())
            moveMatrix[colTile][rowTile] = 2;
    }

    colTile = this -> getcol() + 2;
    rowTile = this -> getrow() + 1;

    if (colTile >= 0 && colTile <= 7 && rowTile >= 0 && rowTile <= 7) {
        if (board[colTile][rowTile] == nullPiece)
            moveMatrix[colTile][rowTile] = 1;

        else if (board[colTile][rowTile] -> getside() != this -> getside())
            moveMatrix[colTile][rowTile] = 2;
    }

    colTile = this -> getcol() + 2;
    rowTile = this -> getrow() - 1;

    if (colTile >= 0 && colTile <= 7 && rowTile >= 0 && rowTile <= 7) {
        if (board[colTile][rowTile] == nullPiece)
            moveMatrix[colTile][rowTile] = 1;

        else if (board[colTile][rowTile] -> getside() != this -> getside())
            moveMatrix[colTile][rowTile] = 2;
    }

    colTile = this -> getcol() - 1;
    rowTile = this -> getrow() - 2;

    if (colTile >= 0 && colTile <= 7 && rowTile >= 0 && rowTile <= 7) {
        if (board[colTile][rowTile] == nullPiece)
            moveMatrix[colTile][rowTile] = 1;

        else if (board[colTile][rowTile] -> getside() != this -> getside())
            moveMatrix[colTile][rowTile] = 2;
    }

    colTile = this -> getcol() + 1;
    rowTile = this -> getrow() - 2;

    if (colTile >= 0 && colTile <= 7 && rowTile >= 0 && rowTile <= 7) {
        if (board[colTile][rowTile] == nullPiece)
            moveMatrix[colTile][rowTile] = 1;

        else if (board[colTile][rowTile] -> getside() != this -> getside())
            moveMatrix[colTile][rowTile] = 2;
    }

    colTile = this -> getcol() - 1;
    rowTile = this -> getrow() + 2;

    if (colTile >= 0 && colTile <= 7 && rowTile >= 0 && rowTile <= 7) {
        if (board[colTile][rowTile] == nullPiece)
            moveMatrix[colTile][rowTile] = 1;

        else if (board[colTile][rowTile] -> getside() != this -> getside())
            moveMatrix[colTile][rowTile] = 2;
    }

    colTile = this -> getcol() + 1;
    rowTile = this -> getrow() + 2;

    if (colTile >= 0 && colTile <= 7 && rowTile >= 0 && rowTile <= 7) {
        if (board[colTile][rowTile] == nullPiece)
            moveMatrix[colTile][rowTile] = 1;

        else if (board[colTile][rowTile] -> getside() != this -> getside())
            moveMatrix[colTile][rowTile] = 2;
    }
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
    bool first;

    colTile = this -> getcol();
    rowTile = this -> getrow();
    first = true;

    while (colTile >= 0 && rowTile <= 7) {
        if (board[colTile][rowTile] == nullPiece)
            moveMatrix[colTile][rowTile] = 1;

        else if (board[colTile][rowTile] -> getside() != this -> getside()) {
            moveMatrix[colTile][rowTile] = 2;
            break;
        }

        else if (board[colTile][rowTile] -> getside() == this -> getside() && !first)
            break;

        colTile--;
        rowTile++;
        first = false;
    }

    colTile = this -> getcol();
    rowTile = this -> getrow();
    first = true;

    while (colTile >= 0 && rowTile >= 0) {
        if (board[colTile][rowTile] == nullPiece)
            moveMatrix[colTile][rowTile] = 1;

        else if (board[colTile][rowTile] -> getside() != this -> getside()) {
            moveMatrix[colTile][rowTile] = 2;
            break;
        }

        else if (board[colTile][rowTile] -> getside() == this -> getside() && !first)
            break;
        colTile--;
        rowTile--;
        first = false;
    }

    colTile = this -> getcol();
    rowTile = this -> getrow();
    first = true;

    while (colTile <= 7 && rowTile <= 7) {
        if (board[colTile][rowTile] == nullPiece)
            moveMatrix[colTile][rowTile] = 1;

        else if (board[colTile][rowTile] -> getside() != this -> getside()) {
            moveMatrix[colTile][rowTile] = 2;
            break;
        }

        else if (board[colTile][rowTile] -> getside() == this -> getside() && !first)
            break;
        colTile++;
        rowTile++;
        first = false;
    }

    colTile = this -> getcol();
    rowTile = this -> getrow();
    first = true;

    while (colTile <= 7 && rowTile >= 0) {
        if (board[colTile][rowTile] == nullPiece)
            moveMatrix[colTile][rowTile] = 1;

        else if (board[colTile][rowTile] -> getside() != this -> getside()) {
            moveMatrix[colTile][rowTile] = 2;
            break;
        }

        else if (board[colTile][rowTile] -> getside() == this -> getside() && !first)
            break;
        colTile++;
        rowTile--;
        first = false;
    }
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
    bool first;
    
    tile = this -> getcol();
    first = true;

    while (tile >= 0) {
        if (board[tile][this -> getrow()] == nullPiece)
            moveMatrix[tile][this -> getrow()] = 1;

        else if (board[tile][this -> getrow()] -> getside() != this -> getside()) {
            moveMatrix[tile][this -> getrow()] = 2;
            break;
        }

        else if (board[tile][this -> getrow()] -> getside() == this -> getside() && !first)
            break;

        tile--;
        first = false;
    }

    tile = this -> getcol();
    first = true;

    while (tile <= 7) {
        if (board[tile][this -> getrow()] == nullPiece)
            moveMatrix[tile][this -> getrow()] = 1;

        else if (board[tile][this -> getrow()] -> getside() != this -> getside()) {
            moveMatrix[tile][this -> getrow()] = 2;
            break;
        }

        else if (board[tile][this -> getrow()] -> getside() == this -> getside() && !first)
            break;
        tile++;
        first = false;
    }

    tile = this -> getrow();
    first = true;

    while (tile >= 0) {
        if (board[this -> getcol()][tile] == nullPiece)
            moveMatrix[this -> getcol()][tile] = 1;

        else if (board[this -> getcol()][tile] -> getside() != this -> getside()) {
            moveMatrix[this -> getcol()][tile] = 2;
            break;
        }

        else if (board[this -> getcol()][tile] -> getside() == this -> getside() && !first)
            break;
        tile--;
        first = false;
    }

    tile = this -> getrow();
    first = true;

    while (tile <= 7) {
        if (board[this -> getcol()][tile] == nullPiece)
            moveMatrix[this -> getcol()][tile] = 1;

        else if (board[this -> getcol()][tile] -> getside() != this -> getside()) {
            moveMatrix[this -> getcol()][tile] = 2;
            break;
        }

        else if (board[this -> getcol()][tile] -> getside() == this -> getside() && !first)
            break;
        tile++;
        first = false;
    }
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
    bool first;

    colTile = this -> getcol();
    rowTile = this -> getrow();
    first = true;

    while (colTile >= 0 && rowTile <= 7) {
        if (board[colTile][rowTile] == nullPiece)
            moveMatrix[colTile][rowTile] = 1;

        else if (board[colTile][rowTile] -> getside() != this -> getside()) {
            moveMatrix[colTile][rowTile] = 2;
            break;
        }

        else if (board[colTile][rowTile] -> getside() == this -> getside() && !first)
            break;
        first = false;
        colTile--;
        rowTile++;
    }

    colTile = this -> getcol();
    rowTile = this -> getrow();
    first = true;

    while (colTile >= 0 && rowTile >= 0) {
        if (board[colTile][rowTile] == nullPiece)
            moveMatrix[colTile][rowTile] = 1;

        else if (board[colTile][rowTile] -> getside() != this -> getside()) {
            moveMatrix[colTile][rowTile] = 2;
            break;
        }

        else if (board[colTile][rowTile] -> getside() == this -> getside() && !first)
            break;
        first = false;
        colTile--;
        rowTile--;
    }

    colTile = this -> getcol();
    rowTile = this -> getrow();
    first = true;

    while (colTile <= 7 && rowTile <= 7) {
        if (board[colTile][rowTile] == nullPiece)
            moveMatrix[colTile][rowTile] = 1;

        else if (board[colTile][rowTile] -> getside() != this -> getside()) {
            moveMatrix[colTile][rowTile] = 2;
            break;
        }

        else if (board[colTile][rowTile] -> getside() == this -> getside() && !first)
            break;
        first = false;
        colTile++;
        rowTile++;
    }

    colTile = this -> getcol();
    rowTile = this -> getrow();
    first = true;

    while (colTile <= 7 && rowTile >= 0) {
        if (board[colTile][rowTile] == nullPiece)
            moveMatrix[colTile][rowTile] = 1;

        else if (board[colTile][rowTile] -> getside() != this -> getside()) {
            moveMatrix[colTile][rowTile] = 2;
            break;
        }

        else if (board[colTile][rowTile] -> getside() == this -> getside() && !first)
            break;
        first = false;
        colTile++;
        rowTile--;
    }

    rowTile = this -> getrow();
    colTile = this -> getcol();
    first = true;

    while (colTile >= 0) {
        if (board[colTile][rowTile] == nullPiece)
            moveMatrix[colTile][rowTile] = 1;

        else if (board[colTile][rowTile] -> getside() != this -> getside()) {
            moveMatrix[colTile][rowTile] = 2;
            break;
        }

        else if (board[colTile][rowTile] -> getside() == this -> getside() && !first)
            break;
        first = false;
        colTile--;
    }
    
    rowTile = this -> getrow();
    colTile = this -> getcol();
    first = true;

    while (colTile <= 7) {
        if (board[colTile][rowTile] == nullPiece)
            moveMatrix[colTile][rowTile] = 1;

        else if (board[colTile][rowTile] -> getside() != this -> getside()) {
            moveMatrix[colTile][rowTile] = 2;
            break;
        }

        else if (board[colTile][rowTile] -> getside() == this -> getside() && !first)
            break;
        first = false;
        colTile++;
    }

    rowTile = this -> getrow();
    colTile = this -> getcol();
    first = true;

    while (rowTile >= 0) {
        if (board[colTile][rowTile] == nullPiece)
            moveMatrix[colTile][rowTile] = 1;

        else if (board[colTile][rowTile] -> getside() != this -> getside()) {
            moveMatrix[colTile][rowTile] = 2;
            break;
        }

        else if (board[colTile][rowTile] -> getside() == this -> getside() && !first)
            break;
        first = false;
        rowTile--;
    }

    rowTile = this -> getrow();
    colTile = this -> getcol();
    first = true;

    while (rowTile <= 7) {
        if (board[colTile][rowTile] == nullPiece)
            moveMatrix[colTile][rowTile] = 1;

        else if (board[colTile][rowTile] -> getside() != this -> getside()) {
            moveMatrix[colTile][rowTile] = 2;
            break;
        }

        else if (board[colTile][rowTile] -> getside() == this -> getside() && !first)
            break;
        first = false;
        rowTile++;
    }
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

    colTile = this -> getcol() - 1;
    rowTile = this -> getrow();

    if (colTile >= 0 && colTile <= 7 && rowTile >= 0 && rowTile <= 7) {
        if (board[colTile][rowTile] == nullPiece)
            moveMatrix[colTile][rowTile] = 1;

        else if (board[colTile][rowTile] -> getside() != this -> getside())
            moveMatrix[colTile][rowTile] = 2;
    }

    colTile = this -> getcol() + 1;
    rowTile = this -> getrow();

    if (colTile >= 0 && colTile <= 7 && rowTile >= 0 && rowTile <= 7) {
        if (board[colTile][rowTile] == nullPiece)
            moveMatrix[colTile][rowTile] = 1;

        else if (board[colTile][rowTile] -> getside() != this -> getside())
            moveMatrix[colTile][rowTile] = 2;
    }

    colTile = this -> getcol();
    rowTile = this -> getrow() - 1;

    if (colTile >= 0 && colTile <= 7 && rowTile >= 0 && rowTile <= 7) {
        if (board[colTile][rowTile] == nullPiece)
            moveMatrix[colTile][rowTile] = 1;

        else if (board[colTile][rowTile] -> getside() != this -> getside())
            moveMatrix[colTile][rowTile] = 2;
    }

    colTile = this -> getcol();
    rowTile = this -> getrow() + 1;

    if (colTile >= 0 && colTile <= 7 && rowTile >= 0 && rowTile <= 7) {
        if (board[colTile][rowTile] == nullPiece)
            moveMatrix[colTile][rowTile] = 1;

        else if (board[colTile][rowTile] -> getside() != this -> getside())
            moveMatrix[colTile][rowTile] = 2;
    }

    colTile = this -> getcol() - 1;
    rowTile = this -> getrow() - 1;

    if (colTile >= 0 && colTile <= 7 && rowTile >= 0 && rowTile <= 7) {
        if (board[colTile][rowTile] == nullPiece)
            moveMatrix[colTile][rowTile] = 1;

        else if (board[colTile][rowTile] -> getside() != this -> getside())
            moveMatrix[colTile][rowTile] = 2;
    }

    colTile = this -> getcol() - 1;
    rowTile = this -> getrow() + 1;

    if (colTile >= 0 && colTile <= 7 && rowTile >= 0 && rowTile <= 7) {
        if (board[colTile][rowTile] == nullPiece)
            moveMatrix[colTile][rowTile] = 1;

        else if (board[colTile][rowTile] -> getside() != this -> getside())
            moveMatrix[colTile][rowTile] = 2;
    }

    colTile = this -> getcol() + 1;
    rowTile = this -> getrow() - 1;

    if (colTile >= 0 && colTile <= 7 && rowTile >= 0 && rowTile <= 7) {
        if (board[colTile][rowTile] == nullPiece)
            moveMatrix[colTile][rowTile] = 1;

        else if (board[colTile][rowTile] -> getside() != this -> getside())
            moveMatrix[colTile][rowTile] = 2;
    }

    colTile = this -> getcol() + 1;
    rowTile = this -> getrow() + 1;

    if (colTile >= 0 && colTile <= 7 && rowTile >= 0 && rowTile <= 7) {
        if (board[colTile][rowTile] == nullPiece)
            moveMatrix[colTile][rowTile] = 1;

        else if (board[colTile][rowTile] -> getside() != this -> getside())
            moveMatrix[colTile][rowTile] = 2;
    }
}

Piece *b_r1 = new Rook('B', 0, 0);
Piece *b_n1 = new Knight('B', 1, 0);
Piece *b_b1 = new Bishop('B', 2, 0);
Piece *b_q = new Queen('B', 3, 0);
Piece *b_k = new King('B', 4, 0);
Piece *b_b2 = new Bishop('B', 5, 0);
Piece *b_n2 = new Knight('B', 6, 0);
Piece *b_r2 = new Rook('B', 7, 0);
Piece *b_p1 = new Pawn('B', 0, 1);
Piece *b_p2 = new Pawn('B', 1, 1);
Piece *b_p3 = new Pawn('B', 2, 1);
Piece *b_p4 = new Pawn('B', 3, 1);
Piece *b_p5 = new Pawn('B', 4, 1);
Piece *b_p6 = new Pawn('B', 5, 1);
Piece *b_p7 = new Pawn('B', 6, 1);
Piece *b_p8 = new Pawn('B', 7, 1);

Piece *w_r1 = new Rook('W', 0, 7);
Piece *w_n1 = new Knight('W', 1, 7);
Piece *w_b1 = new Bishop('W', 2, 7);
Piece *w_q = new Queen('W', 3, 7);
Piece *w_k = new King('W', 4, 7);
Piece *w_b2 = new Bishop('W', 5, 7);
Piece *w_n2 = new Knight('W', 6, 7);
Piece *w_r2 = new Rook('W', 7, 7);
Piece *w_p1 = new Pawn('W', 0, 6);
Piece *w_p2 = new Pawn('W', 1, 6);
Piece *w_p3 = new Pawn('W', 2, 6);
Piece *w_p4 = new Pawn('W', 3, 6);
Piece *w_p5 = new Pawn('W', 4, 6);
Piece *w_p6 = new Pawn('W', 5, 6);
Piece *w_p7 = new Pawn('W', 6, 6);
Piece *w_p8 = new Pawn('W', 7, 6);

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

char checkStatus() {
    int kingCol, kingRow; 
    char sideToTest, sideToScan;

    sideToTest = 'W';
    sideToScan = 'B';

    while (sideToTest != 'X') {

        resetMoveset();

        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if (board[j][i] -> getid() == 'K' && board[j][i] -> getside() == sideToTest) {
                    kingCol = j;
                    kingRow = i;
                }
            }
        }

        for (int i = 0; i < 8; i++)
            for (int j = 0; j < 8; j++)
                if (board[j][i] -> getside() == sideToScan)
                    board[j][i] -> gatherMatrix();

        if (moveMatrix[kingCol][kingRow] != 0)
            return sideToTest;

        if (sideToTest == 'W') {
            sideToTest = 'B';
            sideToScan = 'W';
        }

        else
            sideToTest = 'X';
    }

    resetMoveset();
    return 'N';
}

void toPlay() {

    // check if the user is in check
    // if they are, gather the moveset of the king
    // if all the spots in the moveset in the king
    // can be occupied by opponent pieces, the game
    // is over.

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
        resetMoveset();
        board[startCol][startRow] -> gatherMatrix();

        if (moveMatrix[endCol][endRow] != 0) {
            check = checkStatus();

            if (check == turn) {
                std::cout << "In check" << std::endl;

                resetMoveset();
                board[startCol][startRow] -> gatherMatrix();

                Piece *restoreBoard[8][8];

                for (int i = 0; i < 8; i++)
                    for (int j = 0; j < 8; j++)
                        restoreBoard[j][i] = board[j][i];

                board[startCol][startRow] -> moveSoft(endCol, endRow);

                check = checkStatus();

                for (int i = 0; i < 8; i++)
                    for (int j = 0; j < 8; j++)
                        board[j][i] = restoreBoard[j][i];

                board[startCol][startRow] -> setcol(startCol);
                board[startCol][startRow] -> setrow(startRow);

                if (board[endCol][endRow] != nullPiece) {
                    board[endCol][endRow] -> setcol(endCol);
                    board[endCol][endRow] -> setrow(endRow);
                }

                if (check == turn) {
                    std::cout << "Still in check" << std::endl;
                    toPlay();
                }
                    
                else {
                    std::cout << "No longer in check" << std::endl;\
                    resetMoveset();
                    board[startCol][startRow] -> gatherMatrix();
                    board[startCol][startRow] -> move(endCol, endRow);
                }
            }

            else {
                resetMoveset();
                board[startCol][startRow] -> gatherMatrix();
                board[startCol][startRow] -> move(endCol, endRow);
            }            

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

        check = checkStatus();
        std::cout << "In check? " << check << std::endl;
    }

    return 0;
}