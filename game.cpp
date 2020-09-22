#include "game.h"
#include "drawer.h"
#include <SDL.h>
#include <list>

/*static*/ Game* Game::Create(Drawer* drawer)
{
    Game* newGame = new Game();
    newGame->drawer = drawer;
    return newGame;
}
void Game::Update(float deltatime)
{
        //Coin logic
    srand ( time(NULL) );
        int elapsedTime = SDL_GetTicks();
        if (elapsedTime > lastTime + 2000) {
            //Generate random number to decide which coin to apepar
            greenOrRed = rand() % 2;
            //Random numbers to see which rectangle the coin should appear in
            int randomSeedXpos = rand() % 9;
            int randomSeedYpos = rand() % 9;
            int coinXpos = boxRect[randomSeedXpos]->r.x;
            int coinYpos = boxRect[randomSeedYpos]->r.y + randomSeedYpos * 65;
            std::cout << greenOrRed << std::endl;
            if (greenOrRed == 0) {
                greenCoin = SDL_Rect{ coinXpos,coinYpos,65,65 };
                //Set the other coin out of bounds
                redCoin = SDL_Rect{ 999,999,65,65 };
                lastTime = elapsedTime;
            }
            else {
                redCoin = SDL_Rect{ coinXpos,coinYpos,65,65 };
                //Set the other coin out of bounds
                greenCoin = SDL_Rect{ 999,999,65,65 };
                lastTime = elapsedTime;
            }
        }
}
void Game::createRectangles()
{
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
        {
            boxRect[i][j].used = false;
            boxRect[i][j].x = false;
            boxRect[i][j].r.x = 0 + wh * i;
            boxRect[i][j].r.y = 65 + wh * j;
            boxRect[i][j].r.w = wh;
            boxRect[i][j].r.h = wh;

        }
}

SDL_Rect* Game::whichrect(SDL_Event& event, squares boxRect[10][10])
{
        int x = event.button.x;
        int y = event.button.y;

        for (int i = 0; i < 10; i++)
            for (int j = 0; j < 10; j++)
            {
                if (x >= boxRect[i][j].r.x && x <= (boxRect[i][j].r.x + wh))
                    if (y >= boxRect[i][j].r.y && y <= (boxRect[i][j].r.y + wh))
                        return &boxRect[i][j].r;
            }
        return nullptr;
}
void Game::setMouseBoxLeft(SDL_Event& event)
{
    //Make the box x and y position equal to the mouse position
    mouseBox.x = event.button.x;
    mouseBox.y = event.button.y;
    mouseBox.w = 25;
    mouseBox.h = 25;

    if (SDL_HasIntersection(&mouseBox, &greenCoin)) {
        score += 1;
        //put coin away
        greenCoin = SDL_Rect{ 999,999,50,50 };
        //add an element to the previous dots vector, true means green
        previousDots.push_back(true);
    }
    //If the player clicks the mouse with the left button end the game
    if (SDL_HasIntersection(&mouseBox, &redCoin)) {
        isLost = true;
    }

}
void Game::setMouseBoxRight(SDL_Event& event)
{
    //Make the box x and y position equal to the mouse position
    mouseBox.x = event.button.x;
    mouseBox.y = event.button.y;
    mouseBox.w = 25;
    mouseBox.h = 25;
    if (SDL_HasIntersection(&mouseBox, &redCoin)) {
        score += 1;
        //put coin away
        redCoin = SDL_Rect{ 999,999,50,50 };
        //add an element to the previous dots vector, false means red
        previousDots.push_back(false);
    }
    //If the player clicks the mouse with the right button end the game
    if (SDL_HasIntersection(&mouseBox, &greenCoin)) {
        isLost = true;
    }
}
/*//Vector solutions
void Game::UpdateWithVec(float deltaTime)
{
    int elapsedTime = SDL_GetTicks();
    int elapsedTime2 = SDL_GetTicks();
    if (elapsedTime > lastTime + 2000) {
        greenOrRed = rand() % 2;
        int randomSeed = rand() % rectangles.size();
        int coinXpos = rectangles.at(randomSeed).x;
        int coinYpos = rectangles.at(randomSeed).y;
        if (greenOrRed == 0) {
            greenCoin = SDL_Rect{ coinXpos,coinYpos,wh,wh };
            lastTime = elapsedTime;
            if (elapsedTime > disappearTime + 4000) {
                greenCoin = SDL_Rect{ 999,999,wh,wh };
                disappearTime = elapsedTime;
            }
        }
        if (greenOrRed == 1) {
            redCoin = SDL_Rect{ coinXpos,coinYpos,wh,wh };
            lastTime = elapsedTime;
            if (elapsedTime > disappearTime + 4000) {
                redCoin = SDL_Rect{ 999,999,wh,wh };
                disappearTime = elapsedTime;
            }
        }
    }
}
void Game::vectorRectangles()
{
    if (rectangles.size() == 0) {
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                rectangles.push_back(SDL_Rect{ rectangleX + i * wh,rectangleY + j * wh,wh,wh });
            }
        }
    }

}
SDL_Rect* Game::whichElement(SDL_Event& event)
{
    int x = event.button.x;
    int y = event.button.y;


    for (int i = 0; i < 100; i++) {
        if (x >= rectangles[i].x && x <= rectangles[i].x + wh)
            if (y >= rectangles[i].y && y <= rectangles[i].y + wh)
                return &rectangles[i]; 

    }
    return nullptr;
}
*/
void Game::Draw()
{
        //Draw the grid and highlighted square using a vector method
        /*for (SDL_Rect rectangle : rectangles) {
            drawer->DrawImage("assets/TileBackground.png", rectangle.x, rectangle.y);
        }
        if (currentRect != nullptr) {
            drawer->DrawImage("assets/TileMouseOver.png", currentRect->x, currentRect->y);
        }*/

        //Draw the grid and hightlighted square using multi a dimensional array
        for (int i = 0; i < 10; i++)
            for (int j = 0; j < 10; j++)
                drawer->DrawImage("assets/TileBackground.png", boxRect[i][j].r.x, boxRect[i][j].r.y);
        if (currentRect != nullptr) {
            drawer->DrawImage("assets/TileMouseOver.png", currentRect->x, currentRect->y);
        }
        //Draw green the coin
        drawer->DrawImage("assets/ClickableGreen.png", greenCoin.x, greenCoin.y);
        //Draw the red coin
        drawer->DrawImage("assets/ClickableRed.png", redCoin.x, redCoin.y);
        //Draw the previous coins, if it's true draw a green coin, if it's false draw a red one
        for (int i = 0; i != previousDots.size(); i++) {
            if (previousDots.at(i) == true) {
                drawer->DrawImage("assets/ClickableGreen.png", 0 + i * 65, 0);
            }
            if (previousDots.at(i) == false) {
                drawer->DrawImage("assets/ClickableRed.png", 0 + i * 65, 0);
            }
        }

}

void Game::DrawMenu()
{
    drawer->DrawText("assets/arial.ttf", "Mark Thieu Presents: The Dot Game ", 40, 50, 200);
    drawer->DrawText("assets/arial.ttf", "Press 'S' to START ", 30, 230, 300);
}

void Game::DrawGameOver()
{
    if (isWon == false) {
        drawer->DrawText("assets/arial.ttf", "Game Over ", 50, 250, 250);
        drawer->DrawText("assets/arial.ttf", "Your score:  ", 50, 250, 350);
        drawer->DrawText("assets/arial.ttf", std::to_string(score).c_str(), 50, 480, 350);
    }
    if (isWon == true) {
        drawer->DrawText("assets/arial.ttf", "Congratulations! You Won!", 50, 85, 350);
    }

}

bool Game::getWon()
{
    if (score == 10) {
        isWon = true;
    }
    return isWon;
}

void Game::reset()
{
    isLost = false;
    isWon = false;
    score = 0;
    previousDots.clear();
}
