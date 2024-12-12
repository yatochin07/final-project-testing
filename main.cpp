#include <iostream>
#include "game1.h"  // Meng-include file header game1.h

using namespace std;

int main() {
    int choice;
    char playAgain;

    do {
        // Menu pilihan game
        cout << "Pilih game yang ingin dimainkan:" << endl;
        cout << "1. Tic-Tac-Toe" << endl;
        cout << "2. Game 2" << endl;
        cout << "Masukkan pilihan Anda (1 atau 2): ";
        cin >> choice;

        switch (choice) {
            case 1:
                playTicTacToe();  // Panggil fungsi playTicTacToe dari game1.cpp
                break;
            case 2:
                // Panggil game 2 jika ada
                break;
            default:
                cout << "Pilihan tidak valid." << endl;
        }

        // Tanyakan apakah pengguna ingin bermain lagi
        cout << "Apakah Anda ingin bermain lagi? (Y/N): ";
        cin >> playAgain;

    } while (playAgain == 'Y' || playAgain == 'y');  // Ulangi jika memilih Y

    cout << "Terima kasih telah bermain!" << endl;
    return 0;
}