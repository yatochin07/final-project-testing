#include <iostream>
#include <cstdlib>
#include <stdlib.h>
#include <ctime>
using namespace std;

//Fungsi input dari komputer
string inputPilihanKomputer() {
    int pilihanRandom = rand() % 3; //menghasilkan angka acak 0, 1, atau 2
    if (pilihanRandom == 0) {
        return "batu"; 
    } 
    if (pilihanRandom == 1) {
        return "kertas"; 
    }
    return "gunting"; 
    
}

//Fungsi menentukan pemenang
string pemenang(string player, string komputer) {
    if (player == komputer) {
        return "Seri";
    }
    if ((player == "batu" && komputer == "kertas") || (player == "kertas" && komputer == "batu") || (player == "gunting" && komputer == "kertas")) {
        return "Player Menang";
    }
    return "Komputer Menang";
}

//Fungsi menampilkan pilihan
void pilihan() {
    cout << "\n\t\t+======== Pilihan ========+" << endl;
    cout << "\t\t| 1. Kertas               |" << endl;
    cout << "\t\t| 2. Batu                 |" << endl;
    cout << "\t\t| 3. Gunting              |" << endl;
    cout << "\t\t+=========================+" << endl;
}

//Fungsi input player
string inputPilihanPlayer() {
    int pilihanPemain;
    cout << "\n\tMasukkan pilihan (1/2/3)\t: ";
    cin >> pilihanPemain;
    
    switch (pilihanPemain) {
        case 1:
            return "kertas";
        case 2:
            return "batu";
        case 3: 
            return "gunting";
        default:
            return "invalid";
    }
}


int main() {
    srand(static_cast<unsigned int>(time(0))); //inisialisasi angka acak

    int skorPlayer = 0;
    int skorKomputer = 0;

    char mainLagi;

    do {
        pilihan();
        string pilihanPlayer = inputPilihanPlayer();
        cout << "\n\tPilihan Anda\t\t\t: " << pilihanPlayer << endl;

        //Validasi input
        if (pilihanPlayer == "invalid") {
            system("cls");
            cout << "\n\tPilihan tidak valid, Silahkan coba lagi !!" << endl;
            cout << "\n\t------------------------------------------" << endl;
            continue;
        }

        string pilihanKomputer = inputPilihanKomputer();
        cout << "\n\tKomputer memilih\t\t: " << pilihanKomputer << endl;

        string hasil = pemenang(pilihanPlayer, pilihanKomputer);
        cout << "\n\tHasil\t\t\t\t: " << hasil << endl;

        if (hasil == "Player Menang") {
            skorPlayer++;
        } else if (hasil == "Komputer Menang") {
            skorKomputer++;
        }
        cout << "\n\tSkor sementara : " << endl;
        cout << "\tPlayer " << skorPlayer << " - " << skorKomputer << " Komputer" << endl;

        cout << "\n\tIngin Bermain Lagi? (y/t)\t: ";
        cin >> mainLagi;

        if (mainLagi == 'y' || 'Y') {
            system("cls");
        }

    } while (mainLagi == 'y' || mainLagi == 'Y');
    cout << "\n\tSkor Akhir :" << endl;
    cout << "\tPlayer " << skorPlayer << " - " << skorKomputer << " Komputer" << endl;
    
    if (skorKomputer > skorPlayer) {
       cout << "\tPemenang adalah Komputer." << endl;
    }
    if (skorPlayer > skorKomputer) {
        cout << "\tPemenang adalah Player." << endl;
    }
    if (skorPlayer == skorKomputer) {
        cout << "\tHasil adalah seri." << endl;
    }
    cout << "\n\tTerima Kasih Sudah Bermain." << endl;
}