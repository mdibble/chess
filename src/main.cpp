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
    void move(int arg1, int arg2);

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
    Knight(char side, int col, int row);
};

class Bishop: public Piece {
public:
    Bishop(char side, int col, int row);
};

class Rook: public Piece {
public:
    Rook(char side, int col, int row);
};

class Queen: public Piece {
public:
    Queen(char side, int col, int row);
};

class King: public Piece {
public:
    King(char side, int col, int row);
};

Pawn::Pawn(char side, int col, int row) {
    this -> setid('P');
    this -> setside(side);
    this -> setcol(col);
    this -> setrow(row);
    this -> setingame(true);
    this -> setmoved(false);
}

void Pawn::move(int col, int row) {

    if (col > 7 || col < 0 || row > 7 || row < 0) {
        std::cout << "Invalid move for a pawn" << std::endl;
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

        int tempCol = this -> getcol();
        int tempRow = this -> getrow();
        this -> setcol(col);
        this -> setrow(row);

        if (this -> getmoved() == false)
            this -> setmoved(true);

        // todo edit taken piece's status to removed from game

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
}

Bishop::Bishop(char side, int col, int row) {
    this -> setid('B');
    this -> setside(side);
    this -> setcol(col);
    this -> setrow(row);
    this -> setingame(true);
    this -> setmoved(false);
}

Rook::Rook(char side, int col, int row) {
    this -> setid('R');
    this -> setside(side);
    this -> setcol(col);
    this -> setrow(row);
    this -> setingame(true);
    this -> setmoved(false);
}

Queen::Queen(char side, int col, int row) {
    this -> setid('Q');
    this -> setside(side);
    this -> setcol(col);
    this -> setrow(row);
    this -> setingame(true);
    this -> setmoved(false);
}

King::King(char side, int col, int row) {
    this -> setid('K');
    this -> setside(side);
    this -> setcol(col);
    this -> setrow(row);
    this -> setingame(true);
    this -> setmoved(false);
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
    board[0][0] = b_r1;
    board[1][0] = b_n1;
    board[2][0] = b_b1;
    board[3][0] = b_q;
    board[4][0] = b_k;
    board[5][0] = b_b2;
    board[6][0] = b_n1;
    board[7][0] = b_r2; 
    board[0][1] = b_p1;
    board[1][1] = b_p2;
    board[2][1] = b_p3;
    board[3][1] = b_p4;
    board[4][1] = b_p5;
    board[5][1] = b_p6;
    board[6][1] = b_p7;
    board[7][1] = b_p8;

    board[0][7] = w_r1;
    board[1][7] = w_n1;
    board[2][7] = w_b1;
    board[3][7] = w_q;
    board[4][7] = w_k;
    board[5][7] = w_b2;
    board[6][7] = w_n1;
    board[7][7] = w_r2; 
    board[0][6] = w_p1;
    board[1][6] = w_p2;
    board[2][6] = w_p3;
    board[3][6] = w_p4;
    board[4][6] = w_p5;
    board[5][6] = w_p6;
    board[6][6] = w_p7;
    board[7][6] = w_p8;

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

    w_p2 -> move(1, 4);

    // todo tiles?

    printBoard();
    return 0;
}