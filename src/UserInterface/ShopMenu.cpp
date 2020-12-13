#include "ShopMenu.hpp"
#include "unordered_map"

ShopMenu::ShopMenu( SDL_Renderer* renderer, Game* game, TextureManager* textureManager, Player* player, rapidjson::Value* json )
{
    dictionary.emplace( "cost", "Cost" );
    dictionary.emplace( "health", "Health" );
    dictionary.emplace( "attackDamage", "Attack Damage" );
    dictionary.emplace( "movementSpeed", "Movement Speed" );
    dictionary.emplace( "attackSpeed", "Attack Speed" );
    dictionary.emplace( "range", "Range" );

    this->renderer = renderer;
    this->game = game;
    this->player = player;

    shop = new Shop( player, json );
    background = new SceneObject( textureManager->GetTexture( "darkBackground" ), renderer );
    label = new UILabel( renderer, 0, 50, "assets/fonts/Sans.ttf", 48, "Item Shop", {255,255,255}, 1024 );

    playerInfoLabel = new UILabel( renderer, label->GetPosition().x , label->GetPosition().y + label->GetPosition().h + 5, "assets/fonts/Sans.ttf", 24, "Fuko: " + std::to_string( player->GetFuko() ), {255,255,255}, label->GetPosition().w );
    warriorLabel = new UILabel( renderer, 1024 / 3 * 0, 160, "assets/fonts/Sans.ttf", 24, "Warrior", {255,255,255}, 1024 / 3 );
    tankLabel = new UILabel( renderer, 1024 / 3 * 1, 160, "assets/fonts/Sans.ttf", 24, "Tank", {255,255,255}, 1024 / 3 );
    archerLabel = new UILabel( renderer, 1024 / 3 * 2, 160, "assets/fonts/Sans.ttf", 24, "Archer", {255,255,255}, 1024 / 3 );

    UILabel* returnButtonLabel = new UILabel( renderer, returnButtonPos.x, returnButtonPos.y, "assets/fonts/Sans.ttf", 24, "Return", {255,255,255}, returnButtonPos.w, returnButtonPos.h );
    returnButton = new Button( textureManager->GetButtonTexture( "button1" ), returnButtonLabel, returnButtonPos, renderer, []( Game* game ){ game->WinMenu(); } );

    int columns = 3;
    int rows = 3;

    //TBD make item button creation more... just make it better please... this is just..... urgency 2
    // make this.. something.. into a class or struct at least like what even is this

    int spearCoord = 0;
    SDL_Rect spearItemButtonPos = { (1024 / rows * 0) + 10, ((768 - (warriorLabel->GetPosition().y + warriorLabel->GetPosition().h)) / columns * spearCoord) + warriorLabel->GetPosition().y + warriorLabel->GetPosition().h + 20, (1024 / rows) - 20, ((768 - (warriorLabel->GetPosition().y + warriorLabel->GetPosition().h)) / columns) - 20 };
    spear = shop->GetItem( "spear" );
    std::string spearItemText = "";
    spearItemText.append( "\n Level " + std::to_string( spear->level ) );
    for( auto stat : spear->stats )
    {
        spearItemText.append( "\n " + dictionary.at( stat.first ) + ": " + std::to_string( stat.second ) + " per Level" );
    }
    if( spear->specialEffect )
        spearItemText.append( "\n " + std::to_string( spear->specialEffectStatIncrese ) + " to " + spear->specialEffectStat + " at level " +  std::to_string( spear->specialEffectLevelReq ));
    
    spearItemName = new UILabel( renderer, warriorLabel->GetPosition().x , spearItemButtonPos.y, "assets/fonts/Sans.ttf", 20, "Spear", {255,255,255}, warriorLabel->GetPosition().w );
    spearItemLabel = new UILabel( renderer, spearItemButtonPos.x , spearItemButtonPos.y, "assets/fonts/Sans.ttf", 18, spearItemText, {255,255,255} );
    buttons.push_back( new Button( textureManager->GetButtonTexture( "button2" ), spearItemLabel, spearItemButtonPos, renderer, []( Shop* shop ){ shop->Buy( "spear" ); } ) );


    int armorCoord = 0;
    SDL_Rect armorItemButtonPos = { (1024 / rows * 1) + 10, ((768 - (tankLabel->GetPosition().y + tankLabel->GetPosition().h)) / columns * armorCoord) + tankLabel->GetPosition().y + tankLabel->GetPosition().h + 20, (1024 / rows) - 20, ((768 - (tankLabel->GetPosition().y + tankLabel->GetPosition().h)) / columns) - 20 };
    armor = shop->GetItem( "armor" );
    std::string armorItemText = "";
    armorItemText.append( "\n Level " + std::to_string( armor->level ) );
    for( auto stat : armor->stats )
    {
        armorItemText.append( "\n " + dictionary.at( stat.first ) + ": " + std::to_string( stat.second ) + " per Level" );
    }
    if( armor->specialEffect )
        armorItemText.append( "\n " + std::to_string( armor->specialEffectStatIncrese ) + " to " + armor->specialEffectStat + " at level " +  std::to_string( armor->specialEffectLevelReq ));
    
    armorItemName = new UILabel( renderer, tankLabel->GetPosition().x , armorItemButtonPos.y, "assets/fonts/Sans.ttf", 20, "Armor", {255,255,255}, tankLabel->GetPosition().w );
    armorItemLabel = new UILabel( renderer, armorItemButtonPos.x , armorItemButtonPos.y, "assets/fonts/Sans.ttf", 18, armorItemText, {255,255,255} );
    buttons.push_back( new Button( textureManager->GetButtonTexture( "button2" ), armorItemLabel, armorItemButtonPos, renderer, []( Shop* shop ){ shop->Buy( "armor" ); } ) );


    int bowCoord = 0;
    SDL_Rect bowItemButtonPos = { (1024 / rows * 2) + 10, ((768 - (archerLabel->GetPosition().y + archerLabel->GetPosition().h)) / columns * bowCoord) + archerLabel->GetPosition().y + archerLabel->GetPosition().h + 20, (1024 / rows) - 20, ((768 - (archerLabel->GetPosition().y + archerLabel->GetPosition().h)) / columns) - 20 };
    bow = shop->GetItem( "bow" );
    std::string bowItemText = "";
    bowItemText.append( "\n Level " + std::to_string( bow->level ) );
    for( auto stat : bow->stats )
    {
        bowItemText.append( "\n " + dictionary.at( stat.first ) + ": " + std::to_string( stat.second ) + " per Level" );
    }
    if( bow->specialEffect )
        bowItemText.append( "\n " + std::to_string( bow->specialEffectStatIncrese ) + " to " + bow->specialEffectStat + " at level " +  std::to_string( bow->specialEffectLevelReq ));
    
    bowItemName = new UILabel( renderer, archerLabel->GetPosition().x , bowItemButtonPos.y, "assets/fonts/Sans.ttf", 20, "Bow", {255,255,255}, archerLabel->GetPosition().w );
    bowItemLabel = new UILabel( renderer, bowItemButtonPos.x , bowItemButtonPos.y, "assets/fonts/Sans.ttf", 18, bowItemText, {255,255,255} );
    buttons.push_back( new Button( textureManager->GetButtonTexture( "button2" ), bowItemLabel, bowItemButtonPos, renderer, []( Shop* shop ){ shop->Buy( "bow" ); } ) );

}

void ShopMenu::Update()
{
    playerInfoLabel->ChangeText( "Fuko: " + std::to_string( player->GetFuko() ) );

    // easy to optimise once this... thing.. above is made normally and update is made to be called only when there is a change
    std::string spearItemText = "";
    spearItemText.append( "\n Level " + std::to_string( spear->level ) );
    for( auto stat : spear->stats )
    {
        spearItemText.append( "\n " + dictionary.at( stat.first ) + ": " + std::to_string( stat.second ) + " per Level" );
    }
    if( spear->specialEffect )
        spearItemText.append( "\n " + std::to_string( spear->specialEffectStatIncrese ) + " to " + spear->specialEffectStat + " at level " +  std::to_string( spear->specialEffectLevelReq ));
    spearItemLabel->ChangeText( spearItemText );

    std::string armorItemText = "";
    armorItemText.append( "\n Level " + std::to_string( armor->level ) );
    for( auto stat : armor->stats )
    {
        armorItemText.append( "\n " + dictionary.at( stat.first ) + ": " + std::to_string( stat.second ) + " per Level" );
    }
    if( armor->specialEffect )
        armorItemText.append( "\n " + std::to_string( armor->specialEffectStatIncrese ) + " to " + armor->specialEffectStat + " at level " +  std::to_string( armor->specialEffectLevelReq ));
    armorItemLabel->ChangeText( armorItemText );

    std::string bowItemText = "";
    bowItemText.append( "\n Level " + std::to_string( bow->level ) );
    for( auto stat : bow->stats )
    {
        bowItemText.append( "\n " + dictionary.at( stat.first ) + ": " + std::to_string( stat.second ) + " per Level" );
    }
    if( bow->specialEffect )
        bowItemText.append( "\n " + std::to_string( bow->specialEffectStatIncrese ) + " to " + bow->specialEffectStat + " at level " +  std::to_string( bow->specialEffectLevelReq ));
    bowItemLabel->ChangeText( bowItemText );
}

void ShopMenu::Render()
{
    background->Render();
    label->Render();
    returnButton->Render();

    playerInfoLabel->Render();
    warriorLabel->Render();
    tankLabel->Render();
    archerLabel->Render();

    for( const auto& button : buttons )
    {
        button->Render();
    }

    spearItemName->Render();
    armorItemName->Render();
    bowItemName->Render();
}

void ShopMenu::HandleEvents( SDL_Event* event )
{
    if( returnButton->HandleEvents( event ) )
            returnButton->game( game );
    
    for( const auto& button : buttons )
    {
        if( button->HandleEvents( event ) )
            button->item( shop );
    }
}

void ShopMenu::Save( rapidjson::Document* saveJson )
{
    shop->Save( saveJson );
}

void ShopMenu::Load( rapidjson::Value* saveJson )
{
    shop->Load( saveJson );
}