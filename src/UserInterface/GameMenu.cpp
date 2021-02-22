#include "../Managers/Player.hpp"
#include "../Managers/TextureManager.hpp"
#include "../Managers/SummonDungeon.hpp"
#include "../Engine/Game.hpp"
#include "../Engine/Global.hpp"
#include "../Objects/SceneObject.hpp"
#include "GameMenu.hpp"
#include "Button.hpp"

GameMenu::GameMenu()
{
    this->json = nullptr;
    this->renderer = nullptr;
    this->dungeon = nullptr;
    this->player = nullptr;
    this->game = nullptr;
}

GameMenu::~GameMenu()
{
    this->game = nullptr;
    this->player = nullptr;
    this->dungeon = nullptr;
    this->renderer = nullptr;
    this->json = nullptr;
}

GameMenu::GameMenu( rapidjson::Value* json, SummonDungeon* dungeon, SDL_Renderer* renderer, TextureManager* textureManager, Player* player, Game* game )
{
    this->json = json;
    this->renderer = renderer;
    this->dungeon = dungeon;
    this->player = player;
    this->game = game;

    gameInfoBackground = new SceneObject( textureManager->GetTexture( "darkBackground" ), renderer, gameInfoBackgroundPos );

    playerFujika = new UILabel( renderer, (gameInfoBackgroundPos.w / 3 * 0), gameInfoBackgroundPos.y, FONT_SANS, 24, "Fujika " + std::to_string( player->GetFujika() ) + " / " + std::to_string( player->GetFujikaLimit() ), {255,255,255}, gameInfoBackgroundPos.w / 3, gameInfoBackgroundPos.h );
    levelInfo = new UILabel( renderer, (gameInfoBackgroundPos.w / 3 * 1), gameInfoBackgroundPos.y, FONT_SANS, 24, "Level " + std::to_string( game->Level() +1 ), {255,255,255}, gameInfoBackgroundPos.w / 3, gameInfoBackgroundPos.h );
    playerFuko = new UILabel( renderer, (gameInfoBackgroundPos.w / 3 * 2), gameInfoBackgroundPos.y, FONT_SANS, 24, "Fuko " + std::to_string( player->GetFuko() ) + " / " + std::to_string( player->GetFukoLimit() ), {255,255,255}, gameInfoBackgroundPos.w / 3, gameInfoBackgroundPos.h );

    int entityCounter = 0;
    int rectW = gameInfoBackgroundPos.w / ((*json)["summons"].MemberCount() + 1);
    SDL_Rect tmp_rect = { 0, 543, rectW, 225 };

    for( auto& entity : (*json)["summons"].GetObject())
    {
        std::string tmp_statText = "";
        for( auto& stat : entity.value.GetObject() )
        {
            auto itr = (*json)["lang"].FindMember(stat.name.GetString());
            if( itr != (*json)["lang"].MemberEnd() )
            {
                tmp_statText.append( std::string(itr->value.GetString()) + ": " + std::to_string(stat.value.GetInt()) );
                tmp_statText.append( "\n" );
            }
        }
        std::string tmp_name = entity.name.GetString();
        tmp_name[0] = toupper(tmp_name[0]);
        UILabel NameLabel = UILabel( renderer, tmp_rect.x + 5, tmp_rect.y + 5, FONT_SANS, 24, tmp_name, {255,255,255}, tmp_rect.w );
        UILabel StatsLabel = UILabel( renderer, tmp_rect.x + 5, tmp_rect.y + NameLabel.GetPosition().h + 5, FONT_SANS, 16, tmp_statText, {255,255,255} );
        Button button = Button( textureManager->GetButtonTexture( "button2" ), tmp_rect, renderer, (void*)(entity.name.GetString()), []( SummonDungeon* dungeon, rapidjson::Value& json, const char* type ){ dungeon->SummonObject( json["summons"][type] ); } );
        
        buttons.push_back({
            button,
            {
                {"name", NameLabel},
                {"stats", StatsLabel}
            }
        });

        ++entityCounter;
        tmp_rect.x = entityCounter * rectW;
    }

    enemyStatsBackground = new SceneObject(textureManager->GetTexture("darkBackground"), renderer, tmp_rect);
    enemyNameLabel = new UILabel(renderer, tmp_rect.x + 5, tmp_rect.y + 5, FONT_SANS, 24, "Enemy", {255,255,255}, tmp_rect.w);
    {
        std::string tmp_statText = "";
        for( auto& stat : (*json)["enemy"].GetObject() )
        {
            auto itr = (*json)["lang"].FindMember(stat.name.GetString());
            if( itr != (*json)["lang"].MemberEnd() )
            {
                tmp_statText.append( std::string(itr->value.GetString()) + ": " + std::to_string(stat.value.GetInt()) );
                tmp_statText.append( "\n" );
            }
        }
        enemyStatsLabel = new UILabel(renderer, tmp_rect.x + 5, tmp_rect.y + enemyNameLabel->GetPosition().h, FONT_SANS, 16, tmp_statText, {255,255,255});
    }

}

void GameMenu::Render()
{
    for( auto& button : buttons )
    {
        button.Render();
    }

    gameInfoBackground->Render();
    enemyStatsBackground->Render();
    enemyNameLabel->Render();
    enemyStatsLabel->Render();

    levelInfo->Render();
    playerFujika->Render();
    playerFuko->Render();
}

void GameMenu::HandleEvents( SDL_Event* event )
{
    for( auto& button : buttons )
    {
        if( button.HandleEvents( event ) )
            button.button.summon( dungeon, (*json), (const char*)(button.GetArg()) );
    }
}

void GameMenu::Reset( float multiplier )
{
    std::string tmp_statText = "";
    for( auto& stat : (*json)["enemy"].GetObject() )
    {
        auto itr = (*json)["lang"].FindMember(stat.name.GetString());
        if( itr != (*json)["lang"].MemberEnd() )
        {
            tmp_statText.append( std::string(itr->value.GetString()) + ": " + std::to_string((int)(stat.value.GetInt() * multiplier)) );
            tmp_statText.append( "\n" );
        }
    }
    enemyStatsLabel->ChangeText( tmp_statText.c_str() );
}

void GameMenu::Update()
{
    playerFujika->ChangeText( ("Fujika " + std::to_string( player->GetFujika() ) + " / " + std::to_string( player->GetFujikaLimit() )).c_str() );
    levelInfo->ChangeText( ("Level " + std::to_string( game->Level() +1 )).c_str() );
    playerFuko->ChangeText( ("Fuko " + std::to_string( player->GetFuko() ) + " / " + std::to_string( player->GetFukoLimit() )).c_str() );

    for( auto& button : buttons )
    {
        std::string tmp_statText = "";
        for( auto& stat : (*json)["summons"][(const char*)(button.GetArg())].GetObject() )
        {
            auto itr = (*json)["lang"].FindMember(stat.name.GetString());
            if( itr != (*json)["lang"].MemberEnd() )
            {
                tmp_statText.append( std::string(itr->value.GetString()) + ": " + std::to_string(stat.value.GetInt()) );
                tmp_statText.append( "\n" );
            }
        }

        button.ChangeText("stats" ,tmp_statText.c_str());
    }
}