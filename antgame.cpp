#include <iostream>
#include <windows.h>
#include <vector>
#include <fstream>
#include <conio.h>
#include <ctime>
#include <string>
//abstract,polymorphism,inheritance,encapsulation,file,class,friend function,operator overloading,template,virtual function

using namespace std;

#define SCREEN_WIDTH 90
#define SCREEN_HEIGHT 26
#define WIN_WIDTH 70

//function to move the console cursor to a specified position (x, y)
template<class T>
void gotoxy(T x, T y);

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

//base class for game objects
class GameObject {
protected:
    int x;
    int y;
    bool isActive;

public:
    GameObject() : x(0), y(0), isActive(true) {}

    //set the position of the game object
    void setPosition(int newX, int newY) {
        x = newX;
        y = newY;
    }

    //set the active status of the game object
    void setActive(bool active) {
        isActive = active;
    }

    // Get the x-coordinate of the game object
    int getX() const {
        return x;
    }

    //get the y-coordinate of the game object
    int getY() const {
        return y;
    }

    //check if the game object is active
    bool isActiveObject() const {
        return isActive;
    }

    //display instructions for the game (virtual function to be overridden by derived classes)
    virtual void displayinstru(){
        cout << "---------PLEASE READ IT-------" << endl;
        cout << "I am giving you instruction from GameObject" << endl;
        cout << "You will see a lot of snakes coming. They will kill you." << endl;
        cout << "You should eat food as an ant and score." << endl;
        cout << "Now enjoy playing." << endl;
        cout << "Also thank GameObject admin." << endl;
        cout << endl;
        cout << endl;
        cout << endl;
    }

    //abstract function to draw the game object(to be overridden by derived classes)
    virtual void draw() = 0;

    //abstract function to erase the game object(to be overridden by derived classes)
    virtual void erase() = 0;
};

//derived class for the Ant game object
class Ant : public GameObject {
protected:
    char shape[4][4];

public:
    Ant() {
        //Ant shape definition here given below
        char antShape[4][4] = {
            {' ', 'o', 'o', ' '},
            {'o', 'o', 'o', 'o'},
            {' ', 'o', 'o', ' '},
            {'o', 'o', 'o', 'o'}
        };

        //Copy the ant shape to the base class shape array using a loop
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                shape[i][j] = antShape[i][j];
            }
        }
    }

    //override the draw function to draw the Ant
    virtual void draw() {
        if (isActive) {
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    gotoxy<int>(x + j, y + i);
                    cout << shape[i][j];
                }
            }
        }
    }

    //override the erase function to erase the Ant
    virtual void erase() {
        if (isActive) {
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    gotoxy<int>(x + j, y + i);
                    cout << " ";
                }
            }
        }
    }

    //override the display instructions function for Ant
    void displayinstru(){
        cout << "---------PLEASE READ IT-------" << endl;
        cout << "I am giving you instruction from Ant admin" << endl;
        cout << "You will see a lot of snakes coming. They will kill you." << endl;
        cout << "You should eat food as an ant and score." << endl;
        cout << "Now enjoy playing." << endl;
        cout << "Also thank Ant admin." << endl;
        cout << endl;
        cout << endl;
        cout << endl;
    }
};

//derived class for the Food game object
class Food : public GameObject {
protected:
    char shape;

public:
    Food() : shape('*') {}

    //override the draw function to draw the Food
    virtual void draw() {
        if (isActive) {
            gotoxy<int>(x, y);
            cout << shape;
        }
    }

    //override the erase function to erase the Food
    virtual void erase() {
        if (isActive) {
            gotoxy<int>(x, y);
            cout << " ";
        }
    }
};

//derived class for the Snake game object
class Snake : public GameObject {
protected:
    char shape[3][3];

public:
    Snake() {
        //Snake shape definition is given below
        char snakeShape[3][3] = {
            {' ', 'o', ' '},
            {'o', 'o', 'o'},
            {' ', 'o', ' '}
        };

        //copy the snake shape to the base class shape array
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                shape[i][j] = snakeShape[i][j];
            }
        }
    }

    //Override the draw function to draw the Snake
    virtual void draw() {
        if (isActive) {
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    gotoxy<int>(x + j, y + i);
                    cout << shape[i][j];
                }
            }
        }
    }

    //Override the erase function to erase the Snake
    virtual void erase() {
        if (isActive) {
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    gotoxy<int>(x + j, y + i);
                    cout << " ";
                }
            }
        }
    }
};

//function to move the console cursor to a specified position (x, y)
template <class T>
void gotoxy(T x, T y) {
    CursorPosition.X = x;
    CursorPosition.Y = y;
    SetConsoleCursorPosition(console, CursorPosition);
}

//function to set the cursor's visibility and size
void setcursor(bool visible, DWORD size) {
    if (size == 0)
        size = 20;

    CONSOLE_CURSOR_INFO lpCursor;
    lpCursor.bVisible = visible;
    lpCursor.dwSize = size;
    SetConsoleCursorInfo(console, &lpCursor);
}

//global variables for food and snakes
int foodY;           //Y-coordinate of food
int foodX;           //X-coordinate of food
bool foodFlag;       //Flag to check if food is present
int antPos = WIN_WIDTH / 2;  //Initial position of the Ant
vector<Snake> snakes;       //Vector to store snake objects
int snakeSpeed = 500;       //Initial speed of snake appearance (milliseconds)
int snakeTimer = 0;         //Timer for snake appearance

//class to represent a player
class Player {
private:
    string name;
    int score;

public:
    Player() : name(""), score(0) {}

    //overload operator for player class and
    friend ofstream& operator<<(ofstream& ofs, const Player& player) { //taking the player
        ofs << "Player " << player.name << ": " << player.score << " points" << endl;
        return ofs;
    }

    //Set the name of the player
    void setName(const string& playerName) { name = playerName; }

    //increase the player's score
    void increaseScore() { score++; }

    //get the player's score
    int getScore() const { return score; }

    //Getting the player's name
    string getName() const { return name; }
};

//Function to draw the game border
void drawBorder() {
    for (int i = 0; i < SCREEN_HEIGHT; i++) {
        for (int j = 0; j < 17; j++) {
            gotoxy<int>(0 + j, i);
            cout << "±"; //Draw border characters
            gotoxy<int>(WIN_WIDTH - j, i);
            cout << "±"; //Draw border characters
        }
    }
    for (int i = 0; i < SCREEN_HEIGHT; i++) {
        gotoxy<int>(SCREEN_WIDTH, i);
        cout << "±"; //Draw border characters
    }
}

//Function to generate food at a random position
void genFood() {
    foodX = 17 + rand() % (33); //generate random X-coordinate for food
    foodFlag = true; //set foodFlag to true when generating new food
}

//function to draw the food
void drawFood() {
    if (foodFlag) {
        gotoxy<int>(foodX, foodY);
        cout << "*"; //draw food character
    }
}

//function to erase the food
void eraseFood() {
    if (foodFlag) {
        gotoxy<int>(foodX, foodY);
        cout << " "; //erase food character
    }
}

//Function to reset the food position
void resetFood() {
    eraseFood();
    foodY = 1; //Resetting Y-coordinate of food to the top
    genFood();
}

//Function to draw the Ant here given
void drawAnt() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            gotoxy<int>(j + antPos, i + 22);
            cout << "o"; //changing "shape[i][j]" to "o" to draw the ant
        }
    }
}

//Function to erase the Ant
void eraseAnt() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            gotoxy<int>(j + antPos, i + 22);
            cout << " "; //Erase the Ant
        }
    }
}

//Function to draw the snakes
void drawSnakes() {
    for (Snake& snake : snakes) {
        snake.draw();
    }
}

// Function to erase the snakes
void eraseSnakes() {
    for (Snake& snake : snakes) {
        snake.erase();
    }
}

//Function to update the snakes' positions
void updateSnakes() {
    if (snakeTimer >= snakeSpeed) {
        snakes.push_back(Snake());
        snakes.back().setPosition(17 + rand() % (33), 1);
        snakeTimer = 0;
    } else {
        snakeTimer += 50;
    }

    for (size_t i = 0; i < snakes.size(); i++) {
        snakes[i].erase();
        if (snakes[i].getY() >= SCREEN_HEIGHT - 1) {
            snakes.erase(snakes.begin() + i);
            i--;
        } else {
            snakes[i].setPosition(snakes[i].getX(), snakes[i].getY() + 1);
        }
    }
}

//check for collisions
int collision() {
    //Checking collision with food
    if (foodFlag && foodY + 3 == 22 && foodX <= antPos + 3 && foodX + 3 >= antPos) {
        foodFlag = false;
        return 1; // Food eaten
    }

    //Checking collision with snakes
    for (const Snake& snake : snakes) {
        if (snake.isActiveObject() && snake.getY() + 2 == 22 && snake.getX() <= antPos + 3 && snake.getX() + 2 >= antPos) {
            return -1; //Snake collision (game over); meaning if it collides with snake, it will be over
        }
    }

    return 0; //No collision found
}

//Function to handle game over
void gameover() {
    system("cls");
    cout << endl;
    cout << "\t\t--------------------------" << endl;
    cout << "\t\t-------- Game Over -------" << endl;
    cout << "\t\t--------------------------" << endl << endl;
    cout << "\t\tPress any key to go back to the menu.";
    getch();
}

//Function to update the player's score on the screen
void updateScore(Player& player) {
    gotoxy<int>(WIN_WIDTH + 7, 5);
    cout << "Score: " << player.getScore();
}

//Function to display game instructions
void instructions() {
    system("cls");
    cout << "Instructions";
    cout << "\n----------------";
    cout << "\n Eat the food by moving left or right.";
    cout << "\n Avoid the snakes!";
    cout << "\n\n Press 'a' to move left";
    cout << "\n Press 'd' to move right";
    cout << "\n Press 'q' or 'Esc' to exit";
    cout << "\n\nPress any key to go back to the menu";
    getch();
}

//Function to play the game
void play(Player& player) {
    antPos = -1 + WIN_WIDTH / 2;
    int gameoverFlag = 0;

    system("cls");
    drawBorder();
    updateScore(player);

    gotoxy<int>(WIN_WIDTH + 7, 2);
    cout << "Ant Game";
    gotoxy<int>(WIN_WIDTH + 6, 4);
    cout << "----------";
    gotoxy<int>(WIN_WIDTH + 6, 6);
    cout << "----------";
    gotoxy<int>(WIN_WIDTH + 7, 12);
    cout << "Control ";
    gotoxy<int>(WIN_WIDTH + 7, 13);
    cout << "-------- ";
    gotoxy<int>(WIN_WIDTH + 2, 14);
    cout << " A Key - Left";
    gotoxy<int>(WIN_WIDTH + 2, 15);
    cout << " D Key - Right";

    gotoxy<int>(18, 5);
    cout << "Press any key to start";
    getch();
    gotoxy<int>(18, 5);
    cout << "                      ";

    while (1) {
        if (kbhit()) {
            char ch = getch();
            if (ch == 'a' || ch == 'A') {
                if (antPos > 18)
                    antPos -= 4;
            }
            if (ch == 'd' || ch == 'D') {
                if (antPos < 50)
                    antPos += 4;
            }
            if (ch == 27) {
                break;
            }
        }

        drawAnt();
        drawFood();
        drawSnakes();

        int result = collision();
        if (result == 1) {
            player.increaseScore();
            resetFood();
        } else if (result == -1) {
            gameoverFlag = 1;
            break;
        }

        Sleep(50);
        eraseAnt();
        eraseFood();
        eraseSnakes();

        if (foodY == SCREEN_HEIGHT - 1) {
            resetFood();
        }

        foodY += 1;
        updateSnakes();

        gotoxy<int>(WIN_WIDTH + 14, 5);
        cout << player.getScore();
    }

    if (gameoverFlag == 1) {
        gameover();
    }
}

//function to write scores to a file
void writeScoresToFile(const vector<Player>& players, const string& fileName) {
    ofstream outputFile(fileName, ios::app); //file handling using here
    if (!outputFile.is_open()) { //if cannot open
        cout << "Error opening the file for writing scores." << endl;
        return;
    }

    for (const Player& player : players) {
        outputFile << player; //use the overloaded operator "<<" to write player information
    }

    outputFile.close();
}

int main() {
    {
        //Demonstrate the use of the displayinstru function for Ant
        GameObject *gob;
        Ant an;
        gob = &an;
        gob->displayinstru();
    }

    setcursor(0, 0);
    srand(static_cast<unsigned>(time(nullptr)));

    vector<Player> players;
    string playerName;
    int numPlayers;

    cout << "Enter the number of players: ";
    cin >> numPlayers;
    cin.ignore(); //clear the newline character from the input buffer

    if (numPlayers < 1) {
        cout << "Invalid number of players. Exiting..." << endl;
        return 1;
    }

    string fileName;
    cout << "Enter the file name to record scores: ";
    cin >> fileName;

    for (int i = 0; i < numPlayers; i++) {
        system("cls");
        gotoxy<int>(10, 5);
        cout << " -------------------------- ";
        gotoxy<int>(10, 6);
        cout << " |        Ant Game        | ";
        gotoxy<int>(10, 7);
        cout << " --------------------------";
        gotoxy<int>(10, 9);
        cout << "Player " << i + 1 << " - Enter your name: ";
        cin.ignore(); //clear any remaining newline characters
        getline(cin, playerName);
        players.push_back(Player());
        players[i].setName(playerName);

        gotoxy<int>(10, 11);
        cout << "1. Start Game";
        gotoxy<int>(10, 12);
        cout << "2. Instructions";
        gotoxy<int>(10, 13);
        cout << "3. Quit";
        gotoxy<int>(10, 15);
        cout << "Select option: ";
        char op = getch();

        if (op == '1') {
            play(players[i]);
        } else if (op == '2') {
            instructions();
        } else if (op == '3') {
            exit(0);
        }
    }

    int highestScoreIndex = 0;
    for (int i = 1; i < numPlayers; i++) {
        if (players[i].getScore() > players[highestScoreIndex].getScore()) {
            highestScoreIndex = i;
        }
    }

    system("cls");
    cout << endl;
    cout << " --------------------------" << endl;
    cout << "---- Highest Scores -----" << endl;
    cout << " --------------------------" << endl;
    for (int i = 0; i < numPlayers; i++) {
        cout << "Player " << players[i].getName() << ": " << players[i].getScore() << " points" << endl;
    }
    cout << "\nPlayer " << players[highestScoreIndex].getName() << " has the highest score!" << endl;
    cout << "--------------------------" << endl << endl;
    cout << "Press any key to exit.";
    getch();

    //write scores to the specified file
    writeScoresToFile(players, fileName);

    return 0;
}
