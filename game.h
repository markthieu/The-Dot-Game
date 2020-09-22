#pragma once
#include "drawer.h"
#include <vector>
#include <list>
#include <iostream>
#include <time.h>
#include <string>

class Game {
public:
    static Game* Create(Drawer* drawer);
    //struct to create rectangles
    struct squares {
        SDL_Rect r;
        bool used;
        bool green;
        bool x;
    };
    //current rect that is initially highligted;
    SDL_Rect* currentRect = nullptr;
    //multi-array of type squares, used to create the squares
    squares boxRect[10][10];
    //Update function
    void Update(float deltaTime);
    //Function to create the grid using a two dimensional array
    void createRectangles();
    //Function to get which rectangle is hovered over by mouse event using the array method
    SDL_Rect* whichrect(SDL_Event& event, squares boxRect[10][10]);
    //Set a collision box for the mouse;
    void setMouseBoxLeft(SDL_Event& event);
    void setMouseBoxRight(SDL_Event& event);
    /*
    //Update function for the vector method implementation
    void UpdateWithVec(float deltaTime);
    //Funcion to create the grid using a vector
    void vectorRectangles();
    //Function to get which rectangle is hovered over by mouse event using the vector method
    SDL_Rect* whichElement(SDL_Event& event);
    */
    //Draw functions that draws game elements
    void Draw();
    void DrawMenu();
    void DrawGameOver();
    //get whether the player lost or won
    bool getLost() { return isLost; };
    bool getWon();
    //Reset the game, score and bools
    void reset();
    //this is used at the game over state to reset into playing state
    int getTime() { return lastTime; }
private:
    Drawer* drawer;
    //Vector to create squares
    //std::vector<SDL_Rect> rectangles;
    int rectangleX = 0;
    int rectangleY = 50;
    //width and height of a sqaure
    int wh = 65;
    //Variables for coins
    SDL_Rect greenCoin{999,999,50,50};
    SDL_Rect redCoin{999,999,50,50};
    //rectangle for the mouse collision box
    SDL_Rect mouseBox;
    //variable used to decide green or red coin should be moved
    int greenOrRed;
    //variable used to measure time elapse
    int lastTime;
    int disappearTime;
    //Score used for displaying score and state change previousDots.Size() could be used too
    int score = 0;
    //Bool to checker whether the player lost
    bool isLost = false;
    bool isWon = false;
    //A vector to store the previous dots
    std::vector<bool> previousDots;
};