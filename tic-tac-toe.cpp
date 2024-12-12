#include <iostream>
#include <cstdlib>
#include <ctime>
#include <climits>

using namespace std;

char square[10] = {'O', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

// Fungsi untuk memeriksa status kemenangan
int checkwin() {
    if (square[1] == square[2] && square[2] == square[3]) {
        return 1;
    } else if (square[4] == square[5] && square[5] == square[6]) {
        return 1;
    } else if (square[7] == square[8] && square[8] == square[9]) {
        return 1;
    } else if (square[1] == square[4] && square[4] == square[7]) {
        return 1;
    } else if (square[2] == square[5] && square[5] == square[8]) {
        return 1;
    } else if (square[3] == square[6] && square[6] == square[9]) {
        return 1;
    } else if (square[1] == square[5] && square[5] == square[9]) {
        return 1;
    } else if (square[3] == square[5] && square[5] == square[7]) {
        return 1;
    } else if (square[1] != '1' && square[2] != '2' && square[3] != '3' &&
               square[4] != '4' && square[5] != '5' && square[6] != '6' &&
               square[7] != '7' && square[8] != '8' && square[9] != '9') {
        return 0; // Draw
    } else {
        return -1; // Game is still going
    }
}

// Fungsi untuk menggambar papan permainan
void board() {
    system("clear");
    cout << "\n\nGAME TIC-TAC-TOE\n\n";
    cout << "Player 1(X) - Player 2(O)" << endl << endl << endl;

    cout << "     |       |     " << endl;
    cout << " " << square[1] << "   |   " << square[2] << "   |   " << square[3] << endl;
    cout << "_____|_______|_____" << endl;
    cout << "     |       |     " << endl;
    cout << " " << square[4] << "   |   " << square[5] << "   |   " << square[6] << endl;
    cout << "_____|_______|_____" << endl;
    cout << "     |       |     " << endl;
    cout << " " << square[7] << "   |   " << square[8] << "   |   " << square[9] << endl;
    cout << "     |       |     " << endl;
}

// Fungsi untuk memeriksa apakah sebuah langkah valid
bool isMoveValid(int move) {
    return (move >= 1 && move <= 9 && square[move] != 'X' && square[move] != 'O');
}

// Fungsi Minimax untuk memilih langkah terbaik
int minimax(int depth, bool isMaximizingPlayer) {
    int score = checkwin();

    // Jika komputer menang
    if (score == 1) {
        return 10 - depth;
    }
    // Jika pemain menang
    if (score == 0) {
        return depth - 10;
    }
    // Jika permainan seri
    if (score == -1) {
        return 0;
    }

    // Jika giliran komputer (Maximizing player)
    if (isMaximizingPlayer) {
        int best = INT_MIN;
        for (int i = 1; i <= 9; i++) {
            if (isMoveValid(i)) {
                square[i] = 'X'; // Tempatkan langkah komputer
                best = max(best, minimax(depth + 1, false));
                square[i] = char(i + '0'); // Batalkan langkah komputer
            }
        }
        return best;
    }
    // Jika giliran pemain (Minimizing player)
    else {
        int best = INT_MAX;
        for (int i = 1; i <= 9; i++) {
            if (isMoveValid(i)) {
                square[i] = 'O'; // Tempatkan langkah pemain
                best = min(best, minimax(depth + 1, true));
                square[i] = char(i + '0'); // Batalkan langkah pemain
            }
        }
        return best;
    }
}

// Fungsi untuk memilih langkah terbaik komputer
int bestMove() {
    int bestVal = INT_MIN;
    int move = -1;

    for (int i = 1; i <= 9; i++) {
        if (isMoveValid(i)) {
            square[i] = 'X'; // Tempatkan langkah komputer
            int moveVal = minimax(0, false);
            square[i] = char(i + '0'); // Batalkan langkah komputer

            if (moveVal > bestVal) {
                move = i;
                bestVal = moveVal;
            }
        }
    }
    return move;
}

int main() {
    srand(time(0)); // Seed untuk random number generator

    int player = 1, i, choice;
    char mark;
    int mode;

    cout << "Pilih mode permainan:\n1. Pemain vs Pemain\n2. Pemain vs Komputer\n";
    cin >> mode;

    do {
        board();
        player = (player % 2) ? 1 : 2; // Menentukan giliran pemain
        mark = (player == 1) ? 'X' : 'O'; // Penentuan simbol pemain

        // Pilihan jika bermain dengan pemain lain atau dengan komputer
        if (mode == 1 || (mode == 2 && player == 1)) {
            cout << "Player " << player << ", masukkan angka : ";
            cin >> choice;
        } else if (mode == 2 && player == 2) {
            choice = bestMove(); // Komputer memilih langkah terbaik
            cout << "Komputer memilih tempat: " << choice << endl;
        }

        if (choice >= 1 && choice <= 9 && square[choice] != 'X' && square[choice] != 'O') {
            square[choice] = mark;
        } else {
            cout << "TEMPAT TIDAK VALID. Coba lagi.\n";
            player--; // Batalkan giliran pemain jika langkah tidak valid
        }

        i = checkwin();
        player++;
    } while (i == -1); // Teruskan permainan sampai ada pemenang atau draw

    board();
    if (i == 1) {
        cout << "\aSELAMAT! PLAYER " << --player << " ADALAH PEMENANGNYA!" << endl;
    } else {
        cout << "\aGAME DRAW!" << endl;
    }

    cin.ignore();
    cin.get();
    return 0;
}