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
#include "Data.hpp"
#include "Bar.hpp"
#include "Ball.hpp"
#include "Input.hpp"
#include "Score.hpp"
#include "GameOver.hpp"

#define TIME 60
#define WIN_SCORE 2

bool gameIsOver = false;
bool restart = false;

void ErrorCallback(int error, const char* description);
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

template<int IBall, int IBar>
bool IsTouchedBar01_X(Sprite<IBall> ball, Sprite<IBar> bar);

template<int IBall, int IBar>
bool IsTouchedBar02_X(Sprite<IBall> ball, Sprite<IBar> bar);

GLuint LoadBmp(const char* filename, int size);
std::string GetCurrentWorkingDir(void);

Shader shader;
Input input;

int main(int argc, const char * argv[]) {
    
    std::cout << "Current directory is " << GetCurrentWorkingDir().c_str() << ".\n";
    
    auto ball = std::make_unique<Ball<BALL_VERTS_COUNT>>(BALL_RADIUS, 75.0f, 0.02f);
    auto bar01 = std::make_unique<Bar<BAR_VERTS_COUNT>>(BAR_SIZE, Vec2{-0.5f, 0.0f});
    auto bar02 = std::make_unique<Bar<BAR_VERTS_COUNT>>(BAR_SIZE, Vec2{0.5f, 0.0f});
    auto scoreLeft10 = std::make_unique<Score<>>(SCORE_SIZE, Vec2{-0.55f, 0.4f});
    auto scoreLeft01 = std::make_unique<Score<>>(SCORE_SIZE, Vec2{-0.45f, 0.4f});
    auto scoreRight01 = std::make_unique<Score<>>(SCORE_SIZE, Vec2{0.55f, 0.4f});
    auto scoreRight10 = std::make_unique<Score<>>(SCORE_SIZE, Vec2{0.45f, 0.4f});
    auto gameOver = std::make_unique<GameOver<>>(GAMEOVER_SIZE, Vec2{0.0f, 0.0f});
    auto winGame = std::make_unique<GameOver<>>(WIN_SIZE, Vec2{0.0f, 0.0f});
    auto readyGame = std::make_unique<GameOver<>>(READY_SIZE, Vec2{0.0f, 0.2f});
    
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
    
    GLuint ballId = LoadBmp("Ball01.bmp", 122);
    GLuint bar01Id = LoadBmp("Bar01.bmp", 122);
    GLuint bar02Id = LoadBmp("Bar02.bmp", 122);
    GLuint scoreId = LoadBmp("Numbers.bmp", 122);
    GLuint gameOverId = LoadBmp("GameOver.bmp", 122);
    GLuint winId = LoadBmp("Win.bmp", 122);
    GLuint readyId = LoadBmp("Ready.bmp", 122);
    
    int pointLeft = 0;
    int pointRight = 0;
    
    int time = TIME;
    bool playing = false;
    bool countDown = true;
    bool game = true;
    
    while(!glfwWindowShouldClose(window))
    {
        if(pointLeft == WIN_SCORE || pointRight == WIN_SCORE)
        {
            gameIsOver = true;
        }
        
        if(!gameIsOver)
        {
            if(playing)
            {
                //---各バーの移動---
                if(input.mKeyStates[GLFW_KEY_W].pressed)
                {
                    bar01->MoveUp();
                }
                else if(input.mKeyStates[GLFW_KEY_S].pressed)
                {
                    bar01->MoveDown();
                }
                
                if(input.mKeyStates[GLFW_KEY_I].pressed)
                {
                    bar02->MoveUp();
                }
                else if(input.mKeyStates[GLFW_KEY_K].pressed)
                {
                    bar02->MoveDown();
                }
                //---各バーの移動---
                
                //---ボールがバーに当たった際のX軸での処理---
                if(IsTouchedBar01_X(*ball, *bar01))
                {
                    ball->SwitchX();
                }
                
                if(IsTouchedBar02_X(*ball, *bar02))
                {
                    ball->SwitchX();
                }
                //---ボールがバーに当たった際のX軸での処理---
                
                //---得点の処理---
                const float X_LIMIT = 0.67f - BALL_RADIUS * 0.5;
                
                if(ball->pos.x > X_LIMIT)
                {
                    pointLeft++;
                    scoreLeft01->Update(pointLeft);
                    
                    if(pointLeft >= 10)
                    {
                        scoreLeft10->Update(pointLeft / 10);
                    }
                    
                    playing = false;
                    countDown = true;
                    game = false;
                }
                else if(ball->pos.x < -X_LIMIT)
                {
                    pointRight++;
                    scoreRight01->Update(pointRight);
                    
                    if(pointRight >= 10)
                    {
                        scoreRight10->Update(pointRight / 10);
                    }
                    
                    playing = false;
                    countDown = true;
                    game = false;
                }
                //---得点の処理---
                
                ball->Move();
            }
            
            //---得点が入った時---
            if(countDown)
            {
                time--;
                
                if(time <= 0)
                {
                    if(!game)
                    {
                        time = TIME;
                        ball->Restart();
                        bar01->Restart();
                        bar02->Restart();
                        game = true;
                    }
                    else
                    {
                        time = TIME;
                        countDown = false;
                        playing = true;
                    }
                }
            }
            //---得点が入った時---
        }
        //----ゲームオーバー時----
        else
        {
            if(restart == true)
            {
                gameIsOver = false;
                
                time = TIME;
                pointLeft = 0;
                pointRight = 0;
                scoreLeft01->RestartUv();
                scoreLeft10->RestartUv();
                scoreRight01->RestartUv();
                scoreRight10->RestartUv();
                
                ball->Restart();
                bar01->Restart();
                bar02->Restart();

                playing = false;
                countDown = true;
                game = true;
                
                restart = false;
            }
        }
        //----ゲームオーバー時----
        
        //----描画----
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearDepth(1.0);
        
        ball->Draw(ballId);
        bar01->Draw(bar01Id);
        bar02->Draw(bar02Id);
        scoreLeft01->Draw(scoreId);
        scoreLeft10->Draw(scoreId);
        scoreRight01->Draw(scoreId);
        scoreRight10->Draw(scoreId);
        
        if(!playing)
        {
            if(game)
            {
                readyGame->Draw(readyId);
            }
        }
        
        if(gameIsOver)
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
        //----描画----
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glfwTerminate();
    return 0;
}

void ErrorCallback(int error, const char* description)
{
    std::cerr << "Error: " << description << ".\n";
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
    
    if(gameIsOver)
    {
        if(input.mKeyStates[GLFW_KEY_R].pressed)
        {
            restart = true;
        }
    }
    
    if(input.mKeyStates[GLFW_KEY_ESCAPE].pressed)
    {
        glfwSetWindowShouldClose(window, true);
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


GLuint LoadBmp(const char* filename, int size)
{
    int bmpHeaderSize = size;
    char header[bmpHeaderSize];
    
    GLuint id;
    glGenTextures(1, &id);
    
    std::ifstream fstr(filename, std::ios::binary);
    if(!fstr){
        std::cout << "Failed to load " << filename << ".\n";
        return -1;
    }
    
    fstr.read(header, bmpHeaderSize);
    if(header[0] != 'B' || header[1] != 'M'){
        std::cout << "Not a correct BMP file.\n";
        return 0;
    }
    
    int dataPos = *(int*)&(header[0x0A]);
    int imageSize = *(int*)&(header[0x22]);
    int width = *(int*)&(header[0x12]);
    int height = *(int*)&(header[0x16]);
    if(imageSize == 0){
        imageSize = width * height * 3;
    }
    
    if(dataPos == 0){
        dataPos = size;
    }
    
    const size_t fileSize = static_cast<size_t>(fstr.seekg(0, fstr.end).tellg());
    fstr.seekg(0, fstr.beg);
    if(fileSize >= std::numeric_limits<size_t>::max()){
        std::cout << "Failed to get filesize that must be less than size_t max.\n";
    }
    
    char* textureBuffer = new char[fileSize];
    fstr.read(textureBuffer, fileSize);
    
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glBindTexture(GL_TEXTURE_2D, id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, textureBuffer + size);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    delete[] textureBuffer;
    glBindTexture(GL_TEXTURE_2D, 0);
    
    return id;
}

#ifdef WINDOWS
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif

std::string GetCurrentWorkingDir(void)
{
    char buff[FILENAME_MAX];
    GetCurrentDir(buff, FILENAME_MAX);
    std::string currentWorkingDir(buff);
    return currentWorkingDir;
}
