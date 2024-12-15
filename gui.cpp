#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <climits>
#include <chrono>

using namespace std;

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
void board(sf::RenderWindow &window, sf::Font &font)
{
    // Gambar grid
    sf::RectangleShape line(sf::Vector2f(200, 5));
    line.setFillColor(sf::Color::Black);

    for (int i = 1; i <= 2; i++) {
        line.setPosition(200 * i, 0);
        window.draw(line);
        line.setRotation(90);
        line.setPosition(0, 200 * i);
        line.setRotation(0);
        window.draw(line);
    }

    // Gambar angka atau X / O
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(50);
    text.setFillColor(sf::Color::Black);

    for (int i = 1; i <= 9; i++) {
        int row = (i - 1) / 3;
        int col = (i - 1) % 3;
        text.setString(std::string(1, square[i]));
        text.setPosition(col * 200 + 70, row * 200 + 70);
        window.draw(text);
    }
}

// Fungsi untuk validasi langkah
bool isMoveValid(int move) 
{
    return (move >= 1 && move <= 9 && square[move] != 'X' && square[move] != 'O');
}

// Fungsi untuk menangani input pemain
void handleInput(sf::RenderWindow &window, int &player, int mode)
{
    if (player == 1 || (mode == 2 && player == 1)) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            int row = mousePos.y / 200;
            int col = mousePos.x / 200;
            int move = row * 3 + col + 1;

            if (isMoveValid(move)) {
                square[move] = (player == 1) ? 'X' : 'O';
                player = (player % 2) ? 2 : 1;
            }
        }
    }
}

void playTicTacToe()
{
    srand(time(0)); // random number generator
    int mode;
    char playAgain;

    do {
        sf::RenderWindow window(sf::VideoMode(600, 600), "Tic-Tac-Toe");

        sf::Font font;
        if (!font.loadFromFile("arial.ttf")) {
            std::cerr << "Error loading font" << std::endl;
            return;
        }

        int player = 1;
        int i;
        int mode;
        int choice;

        // Inisialisasi ulang game board untuk setiap permainan baru
        square[1] = '1';
        square[2] = '2';
        square[3] = '3';
        square[4] = '4';
        square[5] = '5';
        square[6] = '6';
        square[7] = '7';
        square[8] = '8';
        square[9] = '9';

        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();
            }

            window.clear(sf::Color::White);

            // Menggambar board
            board(window, font);

            // Menangani input
            handleInput(window, player, mode);

            i = checkwin();
            window.display();

            if (i != -1) {
                // Menampilkan pesan kemenangan
                sf::Text resultText;
                resultText.setFont(font);
                resultText.setCharacterSize(30);
                resultText.setFillColor(sf::Color::Black);
                if (i == 1) {
                    resultText.setString("Player " + std::to_string(player) + " Wins!");
                } else if (i == 0) {
                    resultText.setString("It's a Draw!");
                }

                resultText.setPosition(200, 250);
                window.clear(sf::Color::White);
                window.draw(resultText);
                window.display();

                sf::sleep(sf::seconds(2));
                window.close();
            }
        }

        cout << "Apakah Anda ingin mengulangi permainan? (y/n): ";
        cin >> playAgain;
    } while (playAgain == 'Y' || playAgain == 'y');
    
    cout << "Terima kasih telah bermain!" << endl;
}

int main() {
    playTicTacToe();
    return 0;
}