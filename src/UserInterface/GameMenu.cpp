#include "GameMenu.hpp"

GameMenu::GameMenu( rapidjson::Value& json, SummonDungeon* dungeon, SDL_Renderer* renderer, TextureManager* textureManager )
{
    this->json = json;
    this->dungeon = dungeon;
    this->renderer = renderer;

    warriorLabelText.append( "Cost: " + std::to_string( this->json["summons"]["warrior"]["cost"].GetInt() ) );
    warriorLabelText.append( "\nHealth: " + std::to_string( this->json["summons"]["warrior"]["health"].GetInt() ) );
    warriorLabelText.append( "\nAttack Damage: " + std::to_string( this->json["summons"]["warrior"]["attackDamage"].GetInt() ) );
    warriorLabelText.append( "\nMovement Speed: " + std::to_string( this->json["summons"]["warrior"]["movementSpeed"].GetInt() ) );
    warriorLabelText.append( "\nAttack Speed: " + std::to_string( this->json["summons"]["warrior"]["attackSpeed"].GetInt() ) );
    warriorLabelText.append( "\nRange: " + std::to_string( this->json["summons"]["warrior"]["range"].GetInt() ) );

    warriorNameLabel = new UILabel( renderer, warriorRect.x + 5, warriorRect.y + 5, "assets/fonts/Sans.ttf", 24, "Warrior", {255,255,255}, warriorRect.w );
    warriorLabel = new UILabel( renderer, warriorRect.x + 5, warriorRect.y + warriorNameLabel->GetPosition().h + 5, "assets/fonts/Sans.ttf", 16, warriorLabelText, {255,255,255} );
    summonButtons.push_back( new Button( textureManager->GetButtonTexture( "button2" ), warriorLabel, warriorRect, renderer, []( SummonDungeon* dungeon, rapidjson::Value& json ){ dungeon->SummonObject( json["summons"]["warrior"] ); } ) );


    tankLabelText.append( "Cost: " + std::to_string( this->json["summons"]["tank"]["cost"].GetInt() ) );
    tankLabelText.append( "\nHealth: " + std::to_string( this->json["summons"]["tank"]["health"].GetInt() ) );
    tankLabelText.append( "\nAttack Damage: " + std::to_string( this->json["summons"]["tank"]["attackDamage"].GetInt() ) );
    tankLabelText.append( "\nMovement Speed: " +  std::to_string( this->json["summons"]["tank"]["movementSpeed"].GetInt() ) );
    tankLabelText.append( "\nAttack Speed: " + std::to_string( this->json["summons"]["tank"]["attackSpeed"].GetInt() ) );
    tankLabelText.append( "\nRange: " + std::to_string( this->json["summons"]["tank"]["range"].GetInt() ) );

    tankNameLabel = new UILabel( renderer, tankRect.x + 5, tankRect.y + 5, "assets/fonts/Sans.ttf", 24, "Tank", {255,255,255}, tankRect.w );
    tankLabel = new UILabel( renderer, tankRect.x + 5, tankRect.y + tankNameLabel->GetPosition().h + 5, "assets/fonts/Sans.ttf", 16, tankLabelText, {255,255,255} );
    summonButtons.push_back( new Button( textureManager->GetButtonTexture( "button2" ), tankLabel, tankRect, renderer, []( SummonDungeon* dungeon, rapidjson::Value& json ){ dungeon->SummonObject( json["summons"]["tank"] ); } ) );


    archerLabelText.append( "Cost: " + std::to_string( this->json["summons"]["archer"]["cost"].GetInt() ) );
    archerLabelText.append( "\nHealth: " + std::to_string( this->json["summons"]["archer"]["health"].GetInt() ) );
    archerLabelText.append( "\nAttack Damage: " + std::to_string( this->json["summons"]["archer"]["attackDamage"].GetInt() ) );
    archerLabelText.append( "\nMovement Speed: " + std::to_string( this->json["summons"]["archer"]["movementSpeed"].GetInt() ) );
    archerLabelText.append( "\nAttack Speed: " + std::to_string( this->json["summons"]["archer"]["attackSpeed"].GetInt() ) );
    archerLabelText.append( "\nRange: " + std::to_string( this->json["summons"]["archer"]["range"].GetInt() ) );

    archerNameLabel = new UILabel( renderer, archerRect.x + 5, archerRect.y + 5, "assets/fonts/Sans.ttf", 24, "Archer", {255,255,255}, archerRect.w );
    archerLabel = new UILabel( renderer, archerRect.x + 5, archerRect.y + archerNameLabel->GetPosition().h + 5, "assets/fonts/Sans.ttf", 16, archerLabelText, {255,255,255} );
    summonButtons.push_back( new Button( textureManager->GetButtonTexture( "button2" ), archerLabel, archerRect, renderer, []( SummonDungeon* dungeon, rapidjson::Value& json ){ dungeon->SummonObject( json["summons"]["archer"] ); } ) );


    enemyLabelText.append( "\nHealth: " + std::to_string( this->json["enemy"]["health"].GetInt() ) );
    enemyLabelText.append( "\nAttack Damage: " + std::to_string( this->json["enemy"]["attackDamage"].GetInt() ) );
    enemyLabelText.append( "\nMovement Speed: " + std::to_string( this->json["enemy"]["movementSpeed"].GetInt() ) );
    enemyLabelText.append( "\nAttack Speed: " + std::to_string( this->json["enemy"]["attackSpeed"].GetInt() ) );
    enemyLabelText.append( "\nRange: " + std::to_string( this->json["enemy"]["range"].GetInt() ) );

    enemyNameLabel = new UILabel( renderer, enemyRect.x + 5, enemyRect.y + 5, "assets/fonts/Sans.ttf", 24, "Enemy", {255,255,255}, enemyRect.w );
    enemyLabel = new UILabel( renderer, enemyRect.x + 5, enemyRect.y + enemyNameLabel->GetPosition().h + 5, "assets/fonts/Sans.ttf", 16, enemyLabelText, {255,255,255} );
    enemyLabelBackground = new SceneObject( textureManager->GetTexture( "enemyLabelBackground" ), renderer, enemyRect );

}

void GameMenu::Render()
{
    for( auto button : summonButtons )
    {
        button->Render();
    }

    enemyLabelBackground->Render();
    enemyLabel->Render();
    enemyNameLabel->Render();

    warriorNameLabel->Render();

    tankNameLabel->Render();

    archerNameLabel->Render();
}

void GameMenu::HandleEvents( SDL_Event* event )
{
    for( auto button : summonButtons )
    {
        if( button->HandleEvents( event ) )
            button->summon( dungeon, json );
    }
}