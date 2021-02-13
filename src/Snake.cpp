#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>

#include <iostream>
#include <random>

bool gameOver;
const int width  = 70;
const int height = 20;
int x;
int y;
int dollarX;
int dollarY;
int score;
enum Direction { CENTER = 0, LEFT, RIGHT, UP, DOWN };
Direction dir;
int tailX[100] = {0}, tailY[100] = {0};
int tailLength;
std::uniform_int_distribution<int> random_number(1, 42);
std::random_device rd;

void Setup()
{
    gameOver = false;
    dir      = CENTER;
    x        = width / 2;
    y        = height / 2;
    dollarX  = random_number(rd) % width;
    dollarY  = random_number(rd) % height;
    score    = 0;
}
void Draw()
{
    std::system("clear");
    for (int i = 0; i < width; i++) {
        std::cout << "#";
    }
    std::cout << "\n";

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0 || j == width - 1) {
                std::cout << "#";
            } else {
                if (j == x && i == y) {
                    std::cout << "X";
                } else if (i == dollarY && j == dollarX) {
                    std::cout << "$";
                } else {
                    bool print = false;
                    for (int k = 0; k < tailLength; k++) {
                        if (tailX[k] == j && tailY[k] == i) {
                            std::cout << "-";
                            print = true;
                        }
                    }
                    if (!print) {
                        std::cout << " ";
                    }
                }
            }
        }
        std::cout << "\n";
    }

    for (int i = 0; i < width; i++) {
        std::cout << "#";
    }
    std::cout << "\n";
    std::cout << "Punkty: " << score << "\n";
}

int _kbhit()
{
    static const int STDIN  = 0;
    static bool initialized = false;

    if (!initialized) {
        termios term;
        tcgetattr(STDIN, &term);
        term.c_lflag &= ~ICANON;
        tcsetattr(STDIN, TCSANOW, &term);
        setbuf(stdin, NULL);
        initialized = true;
    }

    int bytesWaiting;
    ioctl(STDIN, FIONREAD, &bytesWaiting);
    return bytesWaiting;
}


void Input()
{
    if (_kbhit()) {
        char ch;
        std::cin >> ch;
        switch (ch) {
        case 'a':
            dir = LEFT;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 'w':
            dir = UP;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'x':
            gameOver = true;
            break;
        case 'q':
            gameOver = true;
            std::cout << "Opuszczono grę"
                      << "\n";
            break;
        }
    }
}
void Logic()
{
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;

    tailX[0] = x;
    tailY[0] = y;

    for (int i = 1; i < tailLength; i++) {
        prev2X   = tailX[i];
        prev2Y   = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX    = prev2X;
        prevY    = prev2Y;
    }
    switch (dir) {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    default:
        break;
    }

    if (x == dollarX && y == dollarY) {
        tailLength++;
        score++;
        dollarX = random_number(rd) % width;
        dollarY = random_number(rd) % height;
    }

    if (x == 0 || y == -1 || x == width || y == height) {
        gameOver = true;
    }


    for (int k = 1; k < tailLength; k++) {
        if (tailX[k] == x && tailY[k] == y)
            gameOver = true;
    }
}


int main()
{
    Setup();

    while (!gameOver) {
        Draw();
        Logic();
        Input();
        usleep(150000);
    }


    std::cout << "-------------Koniec gry-------------"
              << "\n";
    return 0;
}
