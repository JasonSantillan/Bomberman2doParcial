#ifndef _BOMBERMAN_SCENES_STAGE_SCENE_H_
#define _BOMBERMAN_SCENES_STAGE_SCENE_H_

#include <SDL.h>
#include <memory>

#include "../Entities/Text.h"
#include "../Scenes/Scene.h"
#include "../GameVersions.h"
#include "../GamePlayers.h"

/**
    * @brief Stage Scene
    *
    */
class StageScene : public Scene
{
    public:
    /**
        * @brief Construct a new Stage Scene
        *
        * @param game
        */
    StageScene(GameManager* _gameManager, const unsigned int _level, const unsigned int _score);
    StageScene(GameManager* _gameManager, GameVersion _gameVersion, const unsigned int _level, const unsigned int _score);
    StageScene(GameManager* _gameManager, GameVersion _gameVersion, GamePlayer _gamePlayer, const unsigned int _level, const unsigned int _score);

    /**
        * @brief Trigger on update if scene is active
        *
        * @param delta - time in milliseconds
        */
    virtual void update(const unsigned int _delta) override;

    private:
    // timer until switch to next menu
    int untilNextSceneTimer = 0;
    // const
    const int sceneTimer = 2000;
    GameVersion gameVersion = GameVersion::GAMEVERSION_CLASIC;
    GamePlayer gamePlayer = GamePlayer::GAMEPLAYER_1PLAYER;
    unsigned int stage = 0;
    unsigned int score = 0;
};

#endif // _BOMBERMAN_SCENES_STAGE_SCENE_H_
