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
        void move(int, int);

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

char Piece::getid() {return this -> id;}
char Piece::getside() {return this -> side;}
int Piece::getrow() {return this -> row;}
int Piece::getcol() {return this -> col;}
bool Piece::getingame() {return this -> ingame;}

void Piece::setid(char arg) {this -> id = arg;}
void Piece::setside(char arg) {this -> side = arg;}
void Piece::setrow(int arg) {this -> row = arg;}
void Piece::setcol(int arg) {this -> col = arg;}
void Piece::setingame(bool arg) {this -> ingame = arg;}

void Piece::move(int col, int row) {

    std::cout << "Moving piece";
}

class Pawn: public Piece {

    public:
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

char board[8][8];

Pawn b_P1, b_P2, b_P3, b_P4, b_P5, b_P6, b_P7, b_P8, w_P1, w_P2, w_P3, w_P4, w_P5, w_P6, w_P7, w_P8;
Rook b_Rl, b_Rr, w_Rl, w_Rr;
Knight b_Nl, b_Nr, w_Nl, w_Nr;
Bishop b_Bl, b_Br, w_Bl, w_Br;
Queen b_Q, w_Q;
King b_K, w_K;

void initBoard() {

    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            board[j][i] = '-';

    

}

int main() {

    initBoard();

    return 0;
}