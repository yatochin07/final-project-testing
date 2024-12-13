#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <limits>
#ifdef _WIN32
    #define CLEAR "CLS"
#else
    #define CLEAR "clear"
#endif
using namespace std;

// Prototipe fungsi
void cetakGrid(const vector<vector<int>>& grid);
bool langkahValid(const vector<vector<int>>& grid, int baris, int kolom, int angka);
bool selesaikanSudoku(vector<vector<int>>& grid);
void mainGame(vector<vector<int>>& grid, const vector<vector<int>>& gridTetap);
void inisialisasiGrid(vector<vector<int>>& grid, vector<vector<int>>& gridTetap);
bool validasiInputAngka();
void clearScreen();

int main() {
    srand(time(0)); // Inisialisasi random seed
    vector<vector<int>> grid(9, vector<int>(9, 0));
    vector<vector<int>> gridTetap(9, vector<int>(9, 0));

    inisialisasiGrid(grid, gridTetap);

    cout << "Selamat datang di game Sudoku!\n";
    mainGame(grid, gridTetap);

    return 0;
}

// Fungsi untuk mencetak grid Sudoku dengan kotak
void cetakGrid(const vector<vector<int>>& grid) {
    cout << "  +===================================+\n";
    for (int i = 0; i < 9; i++) {
        cout << "  | ";
        for (int j = 0; j < 9; j++) {
            cout << (grid[i][j] == 0 ? ' ' : char(grid[i][j] + '0'));
            if ((j + 1) % 3 == 0) {
                cout << " | ";
            } else {
                cout << " | ";
            }
        }
        cout << "\n";
        if ((i + 1) % 3 == 0 && i != 8) {
            cout << "  |===========|===========|===========|\n";
        } else if (i != 8) {
            cout << "  |-----------|-----------|-----------|\n";
        }
    }
    cout << "  +===================================+\n";
}

// Fungsi untuk memeriksa apakah langkah valid
bool langkahValid(const vector<vector<int>>& grid, int baris, int kolom, int angka) {
    for (int x = 0; x < 9; x++) {
        if (grid[baris][x] == angka || grid[x][kolom] == angka ||
            grid[3 * (baris / 3) + x / 3][3 * (kolom / 3) + x % 3] == angka) {
            return false;
        }
    }
    return true;
}

// Fungsi untuk menyelesaikan grid Sudoku menggunakan backtracking
bool selesaikanSudoku(vector<vector<int>>& grid) {
    for (int baris = 0; baris < 9; baris++) {
        for (int kolom = 0; kolom < 9; kolom++) {
            if (grid[baris][kolom] == 0) {
                for (int angka = 1; angka <= 9; angka++) {
                    if (langkahValid(grid, baris, kolom, angka)) {
                        grid[baris][kolom] = angka;

                        if (selesaikanSudoku(grid)) {
                            return true;
                        }

                        grid[baris][kolom] = 0; // Backtracking
                    }
                }
                return false; // Memicu backtracking
            }
        }
    }
    return true; // Sudoku selesai
}

// Fungsi untuk mengisi grid secara acak
void inisialisasiGrid(vector<vector<int>>& grid, vector<vector<int>>& gridTetap) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (rand() % 4 == 0) { // 25% kemungkinan untuk mengisi angka awal
                int angka = rand() % 9 + 1;
                if (langkahValid(grid, i, j, angka)) {
                    grid[i][j] = angka;
                    gridTetap[i][j] = angka; // Simpan angka tetap
                }
            }
        }
    }
}

// Fungsi untuk memvalidasi input angka
bool validasiInputAngka() {
    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return false;
    }
    return true;
}

// Fungsi untuk membersihkan layar
void clearScreen() {
    system(CLEAR);
}

// Fungsi utama untuk memainkan game Sudoku
void mainGame(vector<vector<int>>& grid, const vector<vector<int>>& gridTetap) {
    int baris, kolom, angka;
    while (true) {
        clearScreen();
        cout << "\nAturan permainan:"
             << "\n1. Masukkan angka 1-9 pada grid kosong."
             << "\n2. Anda tidak dapat mengubah angka tetap."
             << "\n3. Angka tidak boleh sama dalam baris, kolom, atau kotak 3x3."
             << "\n4. Ketikkan -1 pada baris untuk meminta solusi otomatis.\n";

        cout << "\nGrid Sudoku saat ini:\n";
        cetakGrid(grid);

        cout << "\nMasukkan baris (1-9) atau -1 untuk menyelesaikan otomatis: ";
        cin >> baris;
        if (!validasiInputAngka()) {
            cout << "Input tidak valid. Harap masukkan angka.\n";
            cin.ignore();
            cin.get();
            continue;
        }

        if (baris == -1) {
            if (selesaikanSudoku(grid)) {
                cout << "\nGrid Sudoku yang telah diselesaikan:\n";
                cetakGrid(grid);
            } else {
                cout << "\nTidak ada solusi untuk grid ini.";
            }
            break;
        }

        cout << "Masukkan kolom (1-9): ";
        cin >> kolom;
        if (!validasiInputAngka()) {
            cout << "Input tidak valid. Harap masukkan angka.\n";
            cin.ignore();
            cin.get();
            continue;
        }

        if (gridTetap[baris - 1][kolom - 1] != 0) {
            cout << "Sel pada posisi tersebut adalah angka tetap dan tidak dapat diubah. Tekan Enter untuk melanjutkan...";
            cin.ignore();
            cin.get();
            continue;
        }

        cout << "Masukkan angka (1-9): ";
        cin >> angka;
        if (!validasiInputAngka()) {
            cout << "Input tidak valid. Harap masukkan angka.\n";
            cin.ignore();
            cin.get();
            continue;
        }

        if (baris < 1 || baris > 9 || kolom < 1 || kolom > 9 || angka < 1 || angka > 9) {
            cout << "Input tidak valid. Pastikan baris, kolom, dan angka berada dalam rentang 1-9.";
            cin.ignore();
            cin.get();
            continue;
        }

        if (!langkahValid(grid, baris - 1, kolom - 1, angka)) {
            cout << "Langkah tidak valid. Angka melanggar aturan Sudoku. Tekan Enter untuk melanjutkan...";
            cin.ignore();
            cin.get();
            continue;
        }

        grid[baris - 1][kolom - 1] = angka;
    }
}
