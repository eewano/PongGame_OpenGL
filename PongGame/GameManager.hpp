#ifndef GameManager_hpp
#define GameManager_hpp

#include "Vec2.hpp"
#include "Define.hpp"
#include "Score.hpp"
#include <memory>

class GameManager
{
public:
    GameManager();
    ~GameManager();
    
public:
    void Init();
    void Draw();
    void Playing();
    void GetScore();
    void EndGame();
    
public:
    int mP01Score;
    int mP02Score;
    
private:
//    std::unique_ptr<Score> mScoreLeft01 = std::make_unique<Score>(SCORE_SIZE, Vec2f{ -0.45f, 0.4f });
//    std::unique_ptr<Score> mScoreLeft10 = std::make_unique<Score>(SCORE_SIZE, Vec2f{ -0.55f, 0.4f });
//    std::unique_ptr<Score> mScoreRight01 = std::make_unique<Score>(SCORE_SIZE, Vec2f{ +0.55f, 0.4f });
//    std::unique_ptr<Score> mScoreRight10 = std::make_unique<Score>(SCORE_SIZE, Vec2f{ +0.45f, 0.4f });
};

#endif /* GameManager_hpp */
