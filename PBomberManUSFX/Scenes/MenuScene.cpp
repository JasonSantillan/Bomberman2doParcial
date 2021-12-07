#include <string>

#include "../Entities/Sprite.h"
#include "../GameManager.h"
#include "../Scenes/GameOverScene.h"
#include "../Scenes/LevelScene.h"
#include "../Scenes/MenuScene.h"
#include "../Scenes/StageScene.h"

// ++increment for menu id
MenuItem& operator++(MenuItem& c)
{
    using type = typename std::underlying_type<MenuItem>::type;
    c = static_cast<MenuItem>(static_cast<type>(c) + 1);
    if(c == MenuItem::Last)
        c = static_cast<MenuItem>(static_cast<type>(MenuItem::None) + 1);
    return c;
}

// --decrement for menu id
MenuItem& operator--(MenuItem& c)
{
    using type = typename std::underlying_type<MenuItem>::type;
    c = static_cast<MenuItem>(static_cast<type>(c) - 1);
    if(c == MenuItem::None)
        c = static_cast<MenuItem>(static_cast<type>(MenuItem::Last) - 1);
    return c;
}

// increment++ for menu id
MenuItem operator++(MenuItem& c, int)
{
    MenuItem result = c;
    ++c;
    return result;
}

// decrement-- for menu id
MenuItem operator--(MenuItem& c, int)
{
    MenuItem result = c;
    --c;
    return result;
}

MenuScene::MenuScene(GameManager* _gameManager) : Scene(_gameManager)
{
    // background
    auto background = std::make_shared<Sprite>(gameManager->getAssetManager()->getTexture(GameTexture::MenuBack), gameManager->getRenderer());
    
    background->setPosition(30, 20);
    
    background->setSize(gameManager->getWindowWidth() - 60,  static_cast<int>(gameManager->getWindowHeight() / 1.5f) - 20);
    addObject(background);

    // start menu
   /* startText = std::make_shared<Text>(gameManager->getAssetManager()->getFont(), gameManager->getRenderer(), "INICIO");
    startText->setColor(colorPressed);
    startText->setSize(static_cast<int>(gameManager->getWindowWidth() / 4.0f), static_cast<int>(gameManager->getWindowHeight() / 20.0f));
    startText->setPosition(static_cast<int>(gameManager->getWindowWidth() / 2.0f - startText->getWidth() / 2.0f), background->getHeight() + 60);
    addObject(startText);*/

    //____________________________________________________________________________________________________________________________________________________________________________
    //____________________________________________________________________________________________________________________________________________________________________________
    start1PlayerText = std::make_shared<Text>(gameManager->getAssetManager()->getFont(), gameManager->getRenderer(), "1 PLAYER");
    start1PlayerText->setColor(colorPressed);
    start1PlayerText->setSize(static_cast<int>(gameManager->getWindowWidth() / 4.0f), static_cast<int>(gameManager->getWindowHeight() / 20.0f));
    start1PlayerText->setPosition(static_cast<int>(gameManager->getWindowWidth() / 2.0f - start1PlayerText->getWidth() / 2.0f), background->getHeight() + 20);
    addObject(start1PlayerText);

    start2PlayerText = std::make_shared<Text>(gameManager->getAssetManager()->getFont(), gameManager->getRenderer(), "2 PLAYER");
    start2PlayerText->setColor(colorStandard);
    start2PlayerText->setSize(static_cast<int>(gameManager->getWindowWidth() / 4.0f), static_cast<int>(gameManager->getWindowHeight() / 20.0f));
    start2PlayerText->setPosition(static_cast<int>(gameManager->getWindowWidth() / 2.0f - start1PlayerText->getWidth() / 2.0f), background->getHeight() + 50);
    addObject(start2PlayerText);
   
    start3PlayerText = std::make_shared<Text>(gameManager->getAssetManager()->getFont(), gameManager->getRenderer(), "3 PLAYER");
    start3PlayerText->setColor(colorStandard);
    start3PlayerText->setSize(static_cast<int>(gameManager->getWindowWidth() / 4.0f), static_cast<int>(gameManager->getWindowHeight() / 20.0f));
    start3PlayerText->setPosition(static_cast<int>(gameManager->getWindowWidth() / 2.0f - start2PlayerText->getWidth() / 2.0f), background->getHeight() + 80);
    addObject(start3PlayerText);

    start4PlayerText = std::make_shared<Text>(gameManager->getAssetManager()->getFont(), gameManager->getRenderer(), "4 PLAYER");
    start4PlayerText->setColor(colorStandard);
    start4PlayerText->setSize(static_cast<int>(gameManager->getWindowWidth() / 4.0f), static_cast<int>(gameManager->getWindowHeight() / 20.0f));
    start4PlayerText->setPosition(static_cast<int>(gameManager->getWindowWidth() / 2.0f - start3PlayerText->getWidth() / 2.0f), background->getHeight() + 110);
    addObject(start4PlayerText);
    //____________________________________________________________________________________________________________________________________________________________________________
    //____________________________________________________________________________________________________________________________________________________________________________

    // exit menu
    exitText = std::make_shared<Text>(gameManager->getAssetManager()->getFont(), gameManager->getRenderer(), "SALIR");
    exitText->setSize(static_cast<int>(gameManager->getWindowWidth() / 5.0f), static_cast<int>(gameManager->getWindowHeight() / 20.0f));
    exitText->setPosition(start1PlayerText->getPositionX(), start4PlayerText->getPositionY() + exitText->getHeight() + 40);
    addObject(exitText);

    gameManager->getSceneManager()->addScene("gameover", std::make_shared<GameOverScene>(gameManager));
    // menu music
    menuMusic = std::make_shared<Music>(gameManager->getAssetManager()->getMusic(MusicEnum::MainMenu));
}

void MenuScene::onEnter()
{
    menuMusic->play();
}

void MenuScene::onExit()
{
    menuMusic->stop();
}

void MenuScene::onEvent(const SDL_Event& event)
{
    Scene::onEvent(event);
    if(event.type == SDL_KEYDOWN)
    {
        switch(event.key.keysym.scancode)
        {
            // we should select next menu item
            case SDL_SCANCODE_S:
            case SDL_SCANCODE_DOWN:
                currentSelectedMenu++;
                onMenuItemSelect();
                break;
            // we should select prev menu item
            case SDL_SCANCODE_W:
            case SDL_SCANCODE_UP:
                currentSelectedMenu--;
                onMenuItemSelect();
                break;
            // enter in menu item
            case SDL_SCANCODE_SPACE:
            case SDL_SCANCODE_RETURN:
                onMenuItemPress();
                break;
            default:
                break;
        }
    }
}

void MenuScene::onMenuItemSelect()
{
    // reset menu items color
    start1PlayerText->setColor(colorStandard);
    start2PlayerText->setColor(colorStandard);
    start3PlayerText->setColor(colorStandard);
    start4PlayerText->setColor(colorStandard);

    exitText->setColor(colorStandard);
    // change color of selected menu item
    switch(currentSelectedMenu)
    {
        case MenuItem::Start1Player:
            start1PlayerText->setColor(colorPressed);
            break;
        case MenuItem::Start2Player:
            start2PlayerText->setColor(colorPressed);
            break;
        case MenuItem::Start3Player:
            start3PlayerText->setColor(colorPressed);
            break;
        case MenuItem::Start4Player:
            start4PlayerText->setColor(colorPressed);
            break;
        case MenuItem::Exit:
            exitText->setColor(colorPressed);
            break;
        default:
            break;
    }
}

void MenuScene::onMenuItemPress()
{
    switch(currentSelectedMenu)
    {
        case MenuItem::Start1Player:
            // go to level scene
            gameManager->getSceneManager()->addScene("stage", std::make_shared<StageScene>(gameManager, GameVersion::GAMEVERSION_CARTOON, GamePlayer::GAMEPLAYER_1PLAYER, 1, 0));
            gameManager->getSceneManager()->activateScene("stage");
            break;
        case MenuItem::Start2Player:
            // go to level scene
            gameManager->getSceneManager()->addScene("stage", std::make_shared<StageScene>(gameManager, GameVersion::GAMEVERSION_CARTOON, GamePlayer::GAMEPLAYER_2PLAYER, 1, 0));
            gameManager->getSceneManager()->activateScene("stage");
            break;
        case MenuItem::Start3Player:
            // go to level scene
            gameManager->getSceneManager()->addScene("stage", std::make_shared<StageScene>(gameManager, GameVersion::GAMEVERSION_CARTOON, GamePlayer::GAMEPLAYER_3PLAYER, 1, 0));
            gameManager->getSceneManager()->activateScene("stage");
            break;
        case MenuItem::Start4Player:
            // go to level scene
            gameManager->getSceneManager()->addScene("stage", std::make_shared<StageScene>(gameManager, GameVersion::GAMEVERSION_CARTOON, GamePlayer::GAMEPLAYER_4PLAYER, 1, 0));
            gameManager->getSceneManager()->activateScene("stage");
            break;
        case MenuItem::Exit:
            // stop gameManager loop
            gameManager->stop();
            break;
        default:
            break;
    }
}
