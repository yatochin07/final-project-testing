#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <climits>

using namespace std;  // This allows us to use std components without prefixing with 'std::'

char square[10] = {'O', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

// Fungsi untuk memeriksa status kemenangan
int checkwin() 
{
    if (square[1] == square[2] && square[2] == square[3]) 
    {
        return 1;
    }
    else if (square[4] == square[5] && square[5] == square[6]) 
    {
        return 1;
    } 
    else if (square[7] == square[8] && square[8] == square[9]) 
    {
        return 1;
    } 
    else if (square[1] == square[4] && square[4] == square[7]) 
    {
        return 1;
    } 
    else if (square[2] == square[5] && square[5] == square[8]) 
    {
        return 1;
    } 
    else if (square[3] == square[6] && square[6] == square[9]) 
    {
        return 1;
    } 
    else if (square[1] == square[5] && square[5] == square[9]) 
    {
        return 1;
    } 
    else if (square[3] == square[5] && square[5] == square[7]) 
    {
        return 1;
    } 
    else if (square[1] != '1' && square[2] != '2' && square[3] != '3' &&
               square[4] != '4' && square[5] != '5' && square[6] != '6' &&
               square[7] != '7' && square[8] != '8' && square[9] != '9') 
    {
        return 0; // Draw
    } 
    else 
    {
        return -1; // Game is still going
    }
}

// Fungsi untuk menggambar game board
void drawBoard(sf::RenderWindow& window, sf::Font& font) 
{
    window.clear(sf::Color::White);

    sf::RectangleShape gridLine1(sf::Vector2f(600, 5));
    gridLine1.setPosition(0, 200);
    gridLine1.setFillColor(sf::Color::Black);
    window.draw(gridLine1);

    sf::RectangleShape gridLine2(sf::Vector2f(600, 5));
    gridLine2.setPosition(0, 400);
    gridLine2.setFillColor(sf::Color::Black);
    window.draw(gridLine2);

    sf::RectangleShape gridLine3(sf::Vector2f(5, 600));
    gridLine3.setPosition(200, 0);
    gridLine3.setFillColor(sf::Color::Black);
    window.draw(gridLine3);

    sf::RectangleShape gridLine4(sf::Vector2f(5, 600));
    gridLine4.setPosition(400, 0);
    gridLine4.setFillColor(sf::Color::Black);
    window.draw(gridLine4);

    // Tampilkan simbol X dan O
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(100);
    text.setFillColor(sf::Color::Black);

    for (int i = 1; i <= 9; ++i) {
        if (square[i] == 'X' || square[i] == 'O') {
            text.setString(string(1, square[i]));
            int row = (i - 1) / 3;
            int col = (i - 1) % 3;
            text.setPosition(100 + col * 200, 100 + row * 200);
            window.draw(text);
        }
    }

    window.display();
}

// Fungsi untuk validasi langkah
bool isMoveValid(int move) 
{
    return (move >= 1 && move <= 9 && square[move] != 'X' && square[move] != 'O');
}

// Fungsi untuk memilih langkah terbaik (komputer)
int bestMove() 
{
    int bestVal = INT_MIN;
    int move = -1;

    for (int i = 1; i <= 9; i++) 
    {
        if (isMoveValid(i)) 
        {
            square[i] = 'X'; // Tempatkan langkah komputer
            int moveVal = minimax(0, false);
            square[i] = char(i + '0'); // Batalkan langkah komputer

            if (moveVal > bestVal) 
            {
                move = i;
                bestVal = moveVal;
            }
        }
    }
    return move;
}

int main() 
{
    srand(time(0)); // Random number generator

    // Membuat jendela permainan
    sf::RenderWindow window(sf::VideoMode(600, 600), "Tic-Tac-Toe");

    // Memuat font untuk menampilkan teks
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        cerr << "Font tidak ditemukan!" << endl;
        return -1; // Keluar jika font gagal dimuat
    }

    int mode;
    char playAgain;

    do 
    {
        int player = 1, i, choice;
        char mark;

        // Game mode dan inisialisasi ulang
        square[1] = '1';
        square[2] = '2';
        square[3] = '3';
        square[4] = '4';
        square[5] = '5';
        square[6] = '6';
        square[7] = '7';
        square[8] = '8';
        square[9] = '9';

        // Pilihan mode game
        cout << "Pilih mode: 1. Pemain vs Pemain, 2. Pemain vs Komputer: ";
        cin >> mode;

        // Permainan berlanjut hingga ada kemenangan atau draw
        do 
        {
            drawBoard(window, font);
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();
            }

            player = (player % 2) ? 1 : 2; // Menentukan giliran pemain
            mark = (player == 1) ? 'X' : 'O'; // Penentuan simbol pemain

            // Pilihan jika bermain melawan player atau dengan komputer
            if (mode == 1 || (mode == 2 && player == 1)) 
            {
                cout << "Player " << player << ", masukkan angka: ";
                cin >> choice;
            } 
            else if (mode == 2 && player == 2) 
            {
                choice = bestMove(); // Komputer memilih langkah terbaik
                cout << "Komputer memilih tempat: " << choice << endl;
            }

            if (choice >= 1 && choice <= 9 && square[choice] != 'X' && square[choice] != 'O') 
            {
                square[choice] = mark;
            } 
            else 
            {
                cout << "Target tidak valid, coba lagi.\n";
                player--; // Batalkan giliran pemain jika langkah tidak valid
            }

            i = checkwin();
            player++;
        } while (i == -1); // Teruskan permainan sampai ada pemenang atau draw

        drawBoard(window, font);
        if (i == 1) 
        {
            cout << "SELAMAT! PLAYER " << --player << " ADALAH PEMENANGNYA!" << endl;
        } 
        else 
        {
            cout << "GAME DRAW!" << endl;
        }

        cout << "Apakah Anda ingin mengulangi permainan? (y/n): ";
        cin >> playAgain;

    } while (playAgain == 'Y' || playAgain == 'y');
    return 0;
}