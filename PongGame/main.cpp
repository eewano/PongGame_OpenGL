#include <iostream>
#include <glad/glad.h>
#include <glad/glad.c>
#include <GLFW/glfw3.h>
#include <linmath.h>
#include <fstream>
#include <numeric>
#include <memory>
#include <vector>

#include "Shader.hpp"
#include "Vec2.hpp"
#include "Define.hpp"
#include "Bar.hpp"
#include "Ball.hpp"
#include "Input.hpp"
#include "Score.hpp"
#include "Texts.hpp"
#include "Utility.hpp"
#include "Loader.hpp"
#include "GameManager.hpp"

bool isGameOver;
bool isReady;
bool isGameStop;
bool isRestart;
int pointLeft;
int pointRight;
int timeCount;

const float X_LIMIT = 0.5f * ASPECT_RATIO - BALL_RADIUS * 0.5;

std::unique_ptr<Ball> mBall;
std::unique_ptr<Bar> mBarLeft;
std::unique_ptr<Bar> mBarRight;
std::unique_ptr<Score> mScore10Left;
std::unique_ptr<Score> mScore01Left;
std::unique_ptr<Score> mScore01Right;
std::unique_ptr<Score> mScore10Right;
std::unique_ptr<Texts> gameOver;
std::unique_ptr<Texts> winGame;
std::unique_ptr<Texts> readyGame;

GLuint ballId;
GLuint bar01Id;
GLuint bar02Id;
GLuint scoreId;
GLuint gameOverId;
GLuint winId;
GLuint readyId;

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
void InitGame();
void GetScore(char player);
void ReadyGame();
void StopGame();
void Draw();

template<int IBall, int IBar>
bool IsTouchedBar01_X(Sprite<IBall> ball, Sprite<IBar> bar);

template<int IBall, int IBar>
bool IsTouchedBar02_X(Sprite<IBall> ball, Sprite<IBar> bar);

Shader shader;
Input input;

int main(int argc, const char * argv[]) {
    
    std::cout << "Current directory is " << GetCurrentWorkingDir().c_str() << ".\n";
    
    mBall = std::make_unique<Ball>(BALL_RADIUS, 75.0f, 0.02f);
    mBarLeft = std::make_unique<Bar>(BAR_SIZE, Vec2f{ -0.5f, 0.0f });
    mBarRight = std::make_unique<Bar>(BAR_SIZE, Vec2f{ +0.5f, 0.0f });
    mScore10Left = std::make_unique<Score>(SCORE_SIZE, Vec2f{ -0.55f, 0.4f });
    mScore01Left = std::make_unique<Score>(SCORE_SIZE, Vec2f{ -0.45f, 0.4f });
    mScore01Right = std::make_unique<Score>(SCORE_SIZE, Vec2f{ +0.55f, 0.4f });
    mScore10Right = std::make_unique<Score>(SCORE_SIZE, Vec2f{ +0.45f, 0.4f });
    gameOver = std::make_unique<Texts>(GAMEOVER_SIZE, Vec2f{ 0.0f, 0.0f });
    winGame = std::make_unique<Texts>(WIN_SIZE, Vec2f{ 0.0f, 0.0f });
    readyGame = std::make_unique<Texts>(READY_SIZE, Vec2f{ 0.0f, 0.2f });
    
    if(!glfwInit()){
        return -1;
    }
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    GLFWwindow* window = glfwCreateWindow(WINDOW_SIZE.x, WINDOW_SIZE.y, "Pong Game", NULL, NULL);
    
    if(!window){
        glfwTerminate();
        return -1;
    }
    
    glfwSetErrorCallback(ErrorCallback);
    glfwSetKeyCallback(window, KeyCallback);
    
    glfwMakeContextCurrent(window);
    auto addr = (GLADloadproc)glfwGetProcAddress;
    gladLoadGLLoader(addr);
    glfwSwapInterval(1);
    
    shader.SetUp();
    
    ballId = LoadBmp("Ball01.bmp");
    bar01Id = LoadBmp("Bar01.bmp");
    bar02Id = LoadBmp("Bar02.bmp");
    scoreId = LoadBmp("Numbers.bmp");
    gameOverId = LoadBmp("GameOver.bmp");
    winId = LoadBmp("Win.bmp");
    readyId = LoadBmp("Ready.bmp");
    
    InitGame();
    ReadyGame();
    
    timeCount = 0;
    
    while(glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
          glfwWindowShouldClose(window) == 0)
    {
        if(isGameOver)
        {
            if(isRestart == true)
            {
                InitGame();
            }
        }
        else
        {
            if(isGameStop)
            {
                StopGame();
            }
            else
            {
                //---各バーの移動---
                if(input.mKeyStates[GLFW_KEY_W].pressed)
                {
                    mBarLeft->Move({ 0, MOVE_SPEED });
                }
                else if(input.mKeyStates[GLFW_KEY_S].pressed)
                {
                    mBarLeft->Move({ 0, MOVE_SPEED * -1.0f });
                }
                
                if(input.mKeyStates[GLFW_KEY_I].pressed)
                {
                    mBarRight->Move({ 0, MOVE_SPEED });
                }
                else if(input.mKeyStates[GLFW_KEY_K].pressed)
                {
                    mBarRight->Move({ 0, MOVE_SPEED * -1.0f });
                }
                //---各バーの移動---
                
                //---ボールがバーに当たった際のX軸での処理---
                if(IsTouchedBar01_X(*mBall, *mBarLeft))
                {
                    mBall->SwitchX();
                }
                
                if(IsTouchedBar02_X(*mBall, *mBarRight))
                {
                    mBall->SwitchX();
                }
                //---ボールがバーに当たった際のX軸での処理---
                
                if(mBall->pos.x > X_LIMIT)
                {
                    GetScore('L');
                    ReadyGame();
                }
                else if(mBall->pos.x < -X_LIMIT)
                {
                    GetScore('R');
                    ReadyGame();
                }
                
                mBall->Move();
            }
        }
        
        if(pointLeft == WIN_SCORE || pointRight == WIN_SCORE)
        {
            isGameOver = true;
        }
        
        Draw();
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glfwTerminate();
    return 0;
}

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if(action == GLFW_PRESS)
    {
        input.mKeyStates[key].pressed = true;
    }
    else if(action == GLFW_RELEASE)
    {
        input.mKeyStates[key].pressed = false;
    }
    
    if(isGameOver)
    {
        if(input.mKeyStates[GLFW_KEY_R].pressed)
        {
            isRestart = true;
        }
    }
}

void InitGame()
{
    isGameOver = false;
    isRestart = false;
    pointLeft = 0;
    pointRight = 0;
    mScore01Left->RestartUv();
    mScore10Left->RestartUv();
    mScore01Right->RestartUv();
    mScore10Right->RestartUv();
    ReadyGame();
}

void GetScore(char player)
{
    switch(player)
    {
        case 'L':
            pointLeft++;
            mScore01Left->Update(pointLeft);
            
            if(pointLeft >= 10)
            {
                mScore10Left->Update(pointLeft / 10);
            }
            break;
            
        case 'R':
            pointRight++;
            mScore01Right->Update(pointRight);
            
            if(pointRight >= 10)
            {
                mScore10Right->Update(pointRight / 10);
            }
            break;
            
        default:
            std::cout << "Unknown character !\n";
            break;
    }
}

void StopGame()
{
    timeCount++;
    
    if(timeCount % INTERVAL == 0)
    {
        isGameStop = false;
        isReady = false;
    }
}

void ReadyGame()
{
    isReady = true;
    isGameStop = true;
    mBall->Restart();
    mBarLeft->Restart();
    mBarRight->Restart();
}

void Draw()
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearDepth(1.0);
    
    mBall->Draw(ballId);
    mBarLeft->Draw(bar01Id);
    mBarRight->Draw(bar02Id);
    mScore01Left->Draw(scoreId);
    mScore10Left->Draw(scoreId);
    mScore01Right->Draw(scoreId);
    mScore10Right->Draw(scoreId);
    
    if(isGameOver)
    {
        gameOver->Draw(gameOverId);
        
        if(pointLeft == WIN_SCORE)
        {
            winGame->winLeft();
            winGame->Draw(winId);
        }
        else if(pointRight == WIN_SCORE)
        {
            winGame->winRight();
            winGame->Draw(winId);
        }
    }
    else
    {
        if(isGameStop)
        {
            if(isReady)
            {
                readyGame->Draw(readyId);
            }
        }
    }
}

template<int IBall, int IBar>
bool IsTouchedBar01_X(Sprite<IBall> ball, Sprite<IBar> bar)
{
    if(ball.pos.x - BALL_RADIUS / 4 < bar.pos.x + BAR_WIDTH / 2 &&
       bar.pos.x + BAR_WIDTH / 2 - 0.01 < ball.pos.x - BALL_RADIUS / 4)
    {
        if(bar.pos.y - BAR_LENGTH / 2 <= ball.pos.y - BALL_RADIUS &&
           ball.pos.y + BALL_RADIUS <= bar.pos.y + BAR_LENGTH / 2)
        {
            return true;
        }
    }
    
    return false;
}

template<int IBall, int IBar>
bool IsTouchedBar02_X(Sprite<IBall> ball, Sprite<IBar> bar)
{
    if(bar.pos.x - BAR_WIDTH / 2 < ball.pos.x + BALL_RADIUS / 4 &&
       ball.pos.x + BALL_RADIUS / 4 < bar.pos.x - BAR_WIDTH / 2 + 0.01)
    {
        if(bar.pos.y - BAR_LENGTH / 2 <= ball.pos.y - BALL_RADIUS &&
           ball.pos.y + BALL_RADIUS <= bar.pos.y + BAR_LENGTH / 2)
        {
            return true;
        }
    }
    
    return false;
}
