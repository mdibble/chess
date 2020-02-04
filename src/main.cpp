#include <iostream>

class Piece {

    public:
        char id = 'X';
        char side;
        int row;
        int col;
        bool ingame = true;
    
};

class Pawn: public Piece {

    public:
        const char id = 'P';
        bool moved = false;
};

class Knight: public Piece {

    public:
        const char id = 'N';
};

class Bishop: public Piece {

    public:
        const char id = 'B';
};

class Rook: public Piece {

    public:
        const char id = 'R';
        bool moved = false;
};

class Queen: public Piece {

    public:
        const char id = 'Q';
};

class King: public Piece {

    public:
        const char id = 'K';
        bool check = false;
};

class Tile {

    public:
        bool occupied = false;
        int row;
        int col;
        Piece piece;

};

Tile board[8][8];

Pawn b_P1, b_P2, b_P3, b_P4, b_P5, b_P6, b_P7, b_P8, w_P1, w_P2, w_P3, w_P4, w_P5, w_P6, w_P7, w_P8;
Rook b_Rl, b_Rr, w_Rl, w_Rr;
Knight b_Nl, b_Nr, w_Nl, w_Nr;
Bishop b_Bl, b_Br, w_Bl, w_Br;
Queen b_Q, w_Q;
King b_K, w_K;

void initBoard() {

    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++) {

            board[j][i].col = j; 
            board[j][i].row = i;
        }

    board[0][0].piece = b_Rr;
    board[1][0].piece = b_Nr;
    board[2][0].piece = b_Br;
    board[3][0].piece = b_K;
    board[4][0].piece = b_Q;
    board[5][0].piece = b_Bl;
    board[6][0].piece = b_Nl;
    board[7][0].piece = b_Rl;
    board[0][1].piece = b_P8;
    board[1][1].piece = b_P7;
    board[2][1].piece = b_P6;
    board[3][1].piece = b_P5;
    board[4][1].piece = b_P4;
    board[5][1].piece = b_P3;
    board[6][1].piece = b_P2;
    board[7][1].piece = b_P1;

    board[0][6].piece = w_Rl;
    board[1][6].piece = w_Nl;
    board[2][6].piece = w_Bl;
    board[3][6].piece = w_K;
    board[4][6].piece = w_Q;
    board[5][6].piece = w_Br;
    board[6][6].piece = w_Nr;
    board[7][6].piece = w_Rr;
    board[0][7].piece = w_P1;
    board[1][7].piece = w_P2;
    board[2][7].piece = w_P3;
    board[3][7].piece = w_P4;
    board[4][7].piece = w_P5;
    board[5][7].piece = w_P6;
    board[6][7].piece = w_P7;
    board[7][7].piece = w_P8;

    for (int i = 0; i < 8; i++) 
        for (int j = 0; j < 8 ; j++) {

            board[j][i].piece.col = board[j][i].col;
            board[j][i].piece.row = board[j][i].row;
        }

    return;
}

int main() {

    initBoard();

    for (int i = 0; i < 8; i++) {

        for (int j = 0; j < 8 ; j++) {
            std::cout << board[j][i].piece.id << " ";
        }

        std::cout<<"\n";
    }

    return 0;
}