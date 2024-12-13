#include <iostream>
#include <thread>
#include <chrono>
#include <cstdlib>  // untuk system("cls")
#include <conio.h>  // untuk _kbhit() dan _getch()

using namespace std;

// Fungsi untuk menghapus layar (khusus untuk Windows, untuk Linux atau MacOS bisa gunakan "clear")
void clearScreen() {
    system("cls");  // untuk Windows
    // system("clear");  // untuk Linux/MacOS
}

// Fungsi untuk membuat teks berkedip
void blinkingText() {
    while (true) {
        clearScreen();  // Hapus layar
        cout << "CLICK START BUTTON TO START THE GAME" << endl;
        this_thread::sleep_for(chrono::milliseconds(500));  // Tunggu 500 ms

        clearScreen();  // Hapus layar lagi
        this_thread::sleep_for(chrono::milliseconds(500));  // Tunggu 500 ms
    }
}

// Fungsi untuk mendeteksi tombol yang ditekan
void waitForStart() {
    while (true) {
        if (_kbhit()) {  // Cek apakah ada tombol yang ditekan
            char ch = _getch();  // Dapatkan tombol yang ditekan
            if (ch == 13) {  // 13 adalah kode ASCII untuk tombol Enter
                break;  // Keluar dari loop jika tombol Enter ditekan
            }
        }
    }
}

int main() {
    // Jalankan teks berkedip dalam thread terpisah
    thread blinkThread(blinkingText);

    // Tunggu sampai tombol Enter ditekan
    waitForStart();

    // Setelah Enter ditekan, berhenti berkedip dan lanjut ke game
    blinkThread.detach();  // Lepaskan thread blink agar tidak terus berjalan
    clearScreen();
    cout << "Game is starting..." << endl;

    // Masukkan logika game di sini
    cout << "Welcome to the Game!" << endl;

    // Tambahkan logika permainan Anda di sini

    return 0;
}