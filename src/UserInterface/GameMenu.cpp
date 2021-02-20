#include "GameMenu.hpp"

GameMenu::GameMenu( rapidjson::Value* json, SummonDungeon* dungeon, SDL_Renderer* renderer, TextureManager* textureManager, Player* player, Game* game )
{
    this->json = json;
    this->dungeon = dungeon;
    this->renderer = renderer;
    this->player = player;
    this->game = game;

    gameInfoBackground = new SceneObject( textureManager->GetTexture( "darkBackground" ), renderer, gameInfoBackgroundPos );

    playerFujika = new UILabel( renderer, (gameInfoBackgroundPos.w / 3 * 0), gameInfoBackgroundPos.y, FONT_SANS, 24, "Fujika " + std::to_string( player->GetFujika() ) + " / " + std::to_string( player->GetFujikaLimit() ), {255,255,255}, gameInfoBackgroundPos.w / 3, gameInfoBackgroundPos.h );
    levelInfo = new UILabel( renderer, (gameInfoBackgroundPos.w / 3 * 1), gameInfoBackgroundPos.y, FONT_SANS, 24, "Level " + std::to_string( game->Level() +1 ), {255,255,255}, gameInfoBackgroundPos.w / 3, gameInfoBackgroundPos.h );
    playerFuko = new UILabel( renderer, (gameInfoBackgroundPos.w / 3 * 2), gameInfoBackgroundPos.y, FONT_SANS, 24, "Fuko " + std::to_string( player->GetFuko() ) + " / " + std::to_string( player->GetFukoLimit() ), {255,255,255}, gameInfoBackgroundPos.w / 3, gameInfoBackgroundPos.h );

    EntityStatsDict.emplace("cost", "Fujika Cost");
    EntityStatsDict.emplace("health", "Health");
    EntityStatsDict.emplace("attackDamage", "Attack Damage");
    EntityStatsDict.emplace("movementSpeed", "Movement Speed");
    EntityStatsDict.emplace("attackSpeed", "Attack Speed");
    EntityStatsDict.emplace("range", "Range");

    int entityCounter = 0;
    int rectW = gameInfoBackgroundPos.w / ((*json)["summons"].MemberCount() + 1);
    SDL_Rect tmp_rect = { 0, 543, rectW, 225 };

    for( auto& entity : (*json)["summons"].GetObject())
    {
        std::string tmp_statText = "";
        for( auto& stat : entity.value.GetObject() )
        {
            if( EntityStatsDict.find(stat.name.GetString()) != EntityStatsDict.end() )
            {
                tmp_statText.append( EntityStatsDict.at(stat.name.GetString()) + ": " + std::to_string(stat.value.GetInt()) );
                tmp_statText.append( "\n" );
            }
        }
        std::string tmp_name = entity.name.GetString();
        tmp_name[0] = toupper(tmp_name[0]);
        UILabel* tmp_uiNameLabel = new UILabel( renderer, tmp_rect.x + 5, tmp_rect.y + 5, FONT_SANS, 24, tmp_name, {255,255,255}, tmp_rect.w );
        UILabel* tmp_uiStatsLabel = new UILabel( renderer, tmp_rect.x + 5, tmp_rect.y + tmp_uiNameLabel->GetPosition().h + 5, FONT_SANS, 16, tmp_statText, {255,255,255} );
        Button* tmp_button = new Button(  textureManager->GetButtonTexture( "button2" ), tmp_uiStatsLabel, tmp_rect, renderer, entity.name.GetString(), []( SummonDungeon* dungeon, rapidjson::Value& json, const char* type ){ dungeon->SummonObject( json["summons"][type] ); } );
        
        EntityMenus.push_back( new EntityMenu({tmp_uiNameLabel, tmp_button}) );

        ++entityCounter;
        tmp_rect.x = entityCounter * rectW;
    }

    enemyInfoBackground = new SceneObject(textureManager->GetTexture("darkBackground"), renderer, tmp_rect);
    enemyNameLabel = new UILabel(renderer, tmp_rect.x + 5, tmp_rect.y + 5, FONT_SANS, 24, "Enemy", {255,255,255}, tmp_rect.w);
    {
        std::string tmp_statText = "";
        for( auto& stat : (*json)["enemy"].GetObject() )
        {
            if( EntityStatsDict.find(stat.name.GetString()) != EntityStatsDict.end() )
            {
                tmp_statText.append( "\n" );
                tmp_statText.append( EntityStatsDict.at(stat.name.GetString()) + ": " + std::to_string(stat.value.GetInt()) );
            }
        }
        enemyInfoLabel = new UILabel(renderer, tmp_rect.x + 5, tmp_rect.y + enemyNameLabel->GetPosition().h, FONT_SANS, 16, tmp_statText, {255,255,255});
    }

}

void GameMenu::Render()
{
    for( auto& entity : EntityMenus )
    {
        entity->Button->Render();
        entity->NameLabel->Render();
    }

    gameInfoBackground->Render();
    enemyInfoBackground->Render();
    enemyNameLabel->Render();
    enemyInfoLabel->Render();

    levelInfo->Render();
    playerFujika->Render();
    playerFuko->Render();
}

void GameMenu::HandleEvents( SDL_Event* event )
{
    for( auto& entity : EntityMenus )
    {
        if( entity->Button->HandleEvents( event ) )
            entity->Button->summon( dungeon, (*json), entity->Button->GetType() );
    }
}

void GameMenu::Reset( float multiplier )
{
    std::string tmp_statText = "";
    for( auto& stat : (*json)["enemy"].GetObject() )
    {
        if( EntityStatsDict.find(stat.name.GetString()) != EntityStatsDict.end() )
        {
            tmp_statText.append( "\n" );
            tmp_statText.append( EntityStatsDict.at(stat.name.GetString()) + ": " + std::to_string((int)(stat.value.GetInt() * multiplier)));
        }
    }
    enemyInfoLabel->ChangeText( tmp_statText.c_str() );
}

void GameMenu::Update()
{
    playerFujika->ChangeText( ("Fujika " + std::to_string( player->GetFujika() ) + " / " + std::to_string( player->GetFujikaLimit() )).c_str() );
    levelInfo->ChangeText( ("Level " + std::to_string( game->Level() +1 )).c_str() );
    playerFuko->ChangeText( ("Fuko " + std::to_string( player->GetFuko() ) + " / " + std::to_string( player->GetFukoLimit() )).c_str() );

    for( auto& entity : EntityMenus )
    {
        std::string tmp_statText = "";
        for( auto& stat : (*json)["summons"][entity->Button->GetType()].GetObject() )
        {
            if( EntityStatsDict.find(stat.name.GetString()) != EntityStatsDict.end() )
            {
                tmp_statText.append( EntityStatsDict.at(stat.name.GetString()) + ": " + std::to_string(stat.value.GetInt()) );
                tmp_statText.append( "\n" );
            }
        }

        entity->Button->ChangeText(tmp_statText.c_str());
    }
}