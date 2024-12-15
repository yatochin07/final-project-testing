#include <SFML/Graphics.hpp>
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
    }
    else if (square[4] == square[5] && square[5] == square[6]) {
        return 1;
    } 
    else if (square[7] == square[8] && square[8] == square[9]) {
        return 1;
    } 
    else if (square[1] == square[4] && square[4] == square[7]) {
        return 1;
    } 
    else if (square[2] == square[5] && square[5] == square[8]) {
        return 1;
    } 
    else if (square[3] == square[6] && square[6] == square[9]) {
        return 1;
    } 
    else if (square[1] == square[5] && square[5] == square[9]) {
        return 1;
    } 
    else if (square[3] == square[5] && square[5] == square[7]) {
        return 1;
    } 
    else if (square[1] != '1' && square[2] != '2' && square[3] != '3' &&
               square[4] != '4' && square[5] != '5' && square[6] != '6' &&
               square[7] != '7' && square[8] != '8' && square[9] != '9') {
        return 0; // Draw
    } 
    else {
        return -1; // Game is still going
    }
}

// Fungsi untuk menggambar papan permainan menggunakan SFML
void drawBoard(sf::RenderWindow &window, sf::Font &font, sf::Text &text, int mode) {
    window.clear(sf::Color::White);

    // Draw grid
    sf::RectangleShape line1(sf::Vector2f(3, 600));
    line1.setPosition(200, 0);
    window.draw(line1);

    sf::RectangleShape line2(sf::Vector2f(3, 600));
    line2.setPosition(400, 0);
    window.draw(line2);

    sf::RectangleShape line3(sf::Vector2f(600, 3));
    line3.setPosition(0, 200);
    window.draw(line3);

    sf::RectangleShape line4(sf::Vector2f(600, 3));
    line4.setPosition(0, 400);
    window.draw(line4);

    // Draw text on the board
    for (int i = 1; i <= 9; i++) {
        text.setString(std::string(1, square[i]));
        int x = (i - 1) % 3 * 200 + 100;
        int y = (i - 1) / 3 * 200 + 100;
        text.setPosition(x - text.getLocalBounds().width / 2, y - text.getLocalBounds().height / 2);
        window.draw(text);
    }

    window.display();
}

// Fungsi untuk validasi
bool isMoveValid(int move) {
    return (move >= 1 && move <= 9 && square[move] != 'X' && square[move] != 'O');
}

// Fungsi Minimax untuk memilih langkah terbaik
int minimax(int depth, bool isMaximizingPlayer) {
    int score = checkwin();

    if (score == 1) {
        return 10 - depth;
    }
    if (score == 0) {
        return depth - 10;
    }
    if (score == -1) {
        return 0;
    }

    if (isMaximizingPlayer) {
        int best = INT_MIN;
        for (int i = 1; i <= 9; i++) {
            if (isMoveValid(i)) {
                square[i] = 'X';
                best = max(best, minimax(depth + 1, false));
                square[i] = char(i + '0');
            }
        }
        return best;
    } else {
        int best = INT_MAX;
        for (int i = 1; i <= 9; i++) {
            if (isMoveValid(i)) {
                square[i] = 'O';
                best = min(best, minimax(depth + 1, true));
                square[i] = char(i + '0');
            }
        }
        return best;
    }
}

int bestMove() {
    int bestVal = INT_MIN;
    int move = -1;

    for (int i = 1; i <= 9; i++) {
        if (isMoveValid(i)) {
            square[i] = 'X';
            int moveVal = minimax(0, false);
            square[i] = char(i + '0');

            if (moveVal > bestVal) {
                move = i;
                bestVal = moveVal;
            }
        }
    }
    return move;
}

int main() {
    srand(time(0));

    // Membuat jendela SFML
    sf::RenderWindow window(sf::VideoMode(600, 600), "Tic Tac Toe");

    // Memuat font
    sf::Font font;
    if (!font.loadFromFile("/usr/share/fonts/dejavu/DejaVuSans-Bold.ttf")) {
        cout << "Font tidak ditemukan!" << endl;
        return -1;
    }

    // Teks untuk papan permainan
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(100);
    text.setFillColor(sf::Color::Black);

    int mode;
    char playAgain;

    do {
        int player = 1, i, choice;
        char mark;
        bool gameEnded = false;

        cout << "=== GAME MODE ===\n\n1. Pemain vs Pemain\n2. Pemain vs Komputer\n";
        cout << "Pilih game mode: ";
        cin >> mode;

        // Inisialisasi ulang papan permainan
        for (int i = 1; i <= 9; i++) square[i] = char(i + '0');

        while (!gameEnded) {
            drawBoard(window, font, text, mode);

            player = (player % 2) ? 1 : 2;
            mark = (player == 1) ? 'X' : 'O';

            if (mode == 1 || (mode == 2 && player == 1)) {
                cout << "Player " << player << ", masukkan angka: ";
                cin >> choice;
            } else if (mode == 2 && player == 2) {
                choice = bestMove();
                cout << "Komputer memilih tempat: " << choice << endl;
            }

            if (choice >= 1 && choice <= 9 && square[choice] != 'X' && square[choice] != 'O') {
                square[choice] = mark;
            } else {
                cout << "TARGET TIDAK VALID, Coba lagi.\n";
                player--;
            }

            i = checkwin();
            if (i != -1) {
                gameEnded = true;
                drawBoard(window, font, text, mode);
                if (i == 1) {
                    cout << "SELAMAT! PLAYER " << player << " MENANG!" << endl;
                } else {
                    cout << "GAME DRAW!" << endl;
                }
            }

            player++;
        }

        cout << "Apakah Anda ingin mengulangi permainan? (y/n): ";
        cin >> playAgain;
    } while (playAgain == 'Y' || playAgain == 'y');

    cout << "Terima kasih telah bermain!" << endl;
    return 0;
}