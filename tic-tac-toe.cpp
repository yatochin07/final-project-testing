#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

char square[10] = {'O', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

// Fungsi untuk memeriksa status kemenangan
int checkwin() {
    if(square[1] == square[2] && square[2] == square[3]) {
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

// Fungsi untuk memilih langkah komputer secara acak
int computerMove() {
    int move;
    do {
        move = rand() % 9 + 1; // Pilih angka acak antara 1-9
    } while (square[move] == 'X' || square[move] == 'O'); // Pastikan langkah valid
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
            choice = computerMove(); // Komputer memilih langkah
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