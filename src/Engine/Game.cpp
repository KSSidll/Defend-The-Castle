#include "Game.hpp"
 
void Game::Init( const char* title, int width, int height, bool fullscreen )
{
    int flags = 0;
    if( fullscreen ) flags = SDL_WINDOW_FULLSCREEN;

    objectsDoc = new rapidjson::Document();

    FILE* objectsJsonFile = fopen( "assets/objects.json", "r" );
    char* readBuffer = new char[65536];
    rapidjson::FileReadStream objectsJson( objectsJsonFile, readBuffer, sizeof( readBuffer ) );
    objectsDoc->ParseStream( objectsJson );
    delete[] readBuffer;
    fclose( objectsJsonFile );

    saveDoc = new rapidjson::Document();

    if( !SDL_Init( SDL_INIT_EVERYTHING ) )
    {
        window = SDL_CreateWindow( title, SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, width, height, flags );

        renderer = SDL_CreateRenderer( window, -1, 0 );

        if( renderer )
        {
            SDL_SetRenderDrawColor( renderer, 50,50,50,255 );
        } 

        isRunning = true;
    }
    else
    {
        isRunning = false;
    }

    player = new Player();
    textureManager = new TextureManager( renderer );

    for ( auto& texture : (*objectsDoc)["textures"].GetArray() )
        textureManager->LoadTexture( texture );

    textureManager->LoadTexture( "enemyLabelBackground", "assets/prototypes/button2.png" );

    textureManager->LoadButtonTexture( "button1", "assets/prototypes/button1.png", "assets/prototypes/button1-over.png", "assets/prototypes/button1-down.png" );
    textureManager->LoadButtonTexture( "button2", "assets/prototypes/button2.png", "assets/prototypes/button2-over.png", "assets/prototypes/button2-down.png" );
    
    background = new SceneObject( textureManager->GetTexture( (*objectsDoc)["background"]["textureSrc"]), renderer );

    summonDungeon = new SummonDungeon( textureManager, renderer, player );

    enemy = new Enemy( textureManager->GetTexture( (*objectsDoc)["enemy"]["textureSrc"] ), (*objectsDoc)["enemy"], renderer );

    userInterface = new UserInterface( objectsDoc, summonDungeon, renderer, textureManager, this, player );
}

void Game::HandleEvents()
{
    SDL_Event event;
    SDL_PollEvent( &event );
    switch ( event.type )
    {
    case SDL_QUIT:
        isRunning = false;
        break;

    case SDL_KEYDOWN:
        switch ( event.key.keysym.sym )
        {
        case SDLK_ESCAPE:
            if( isPaused )
                UnPause();
            else
                Pause();
            break;
        }
        break;
    }

    userInterface->HandleEvents( &event );
}

void Game::Update()
{
    userInterface->Update();

    if( !isPaused )
    {
        HandleCollisions();

        player->Update();
        summonDungeon->Update();
        enemy->Update();
    }

    if( enemy->KillPending() )
        WinMenu();

    if( enemy->GetPosition() <= 0 )
        LoseGame();
}

void Game::Render()
{
    SDL_RenderClear( renderer );
    background->Render();

    summonDungeon->Render();
    enemy->Render();

    userInterface->Render();
    SDL_RenderPresent( renderer );
}

void Game::Clean()
{
    SDL_DestroyWindow( window );
    SDL_DestroyRenderer( renderer );
    SDL_Quit();
}

void Game::HandleCollisions()
{
    if( enemy->Alive() )
    for( auto const &summon : summonDungeon->getObjectArray() )
    {
        
        if( summon->GetPosition() + summon->GetRange() > enemy->GetPosition() )
        {
            summon->HandleCollision( enemy );
        }

        if( enemy->GetPosition() < summon->GetPosition() )
        {
            enemy->HandleCollision( summon );
        }

    }
}

void Game::Reset()
{
    enemy->Reset( powf(enemyStatsLevelMultiplier, level) );
    summonDungeon->Reset();
    userInterface->Reset( powf(enemyStatsLevelMultiplier, level) );
    player->Reset();
    UnPause();
}

void Game::Save()
{
    FILE* saveFile = fopen( "assets/save.json", "w" );

    char writeBuffer[65536];
    rapidjson::FileWriteStream saveStream( saveFile, writeBuffer, sizeof(writeBuffer) );
    saveDoc->SetObject();

    rapidjson::Value object( rapidjson::kObjectType );
    object.AddMember( "enemyStatsLevelMultiplier", enemyStatsLevelMultiplier, saveDoc->GetAllocator() );
    object.AddMember( "level", level, saveDoc->GetAllocator() );
    saveDoc->AddMember( "game", object, saveDoc->GetAllocator() );

    player->Save( saveDoc );
    userInterface->Save( saveDoc );

    rapidjson::Writer< rapidjson::FileWriteStream > writer( saveStream );
    saveDoc->Accept( writer );

    fclose( saveFile );
}

void Game::Load()
{
    FILE* saveJsonFile = fopen( "assets/save.json", "r" );
    char* readBuffer = new char[65536];
    rapidjson::FileReadStream saveJson( saveJsonFile, readBuffer, sizeof( readBuffer ) );
    saveDoc->ParseStream( saveJson );
    delete[] readBuffer;
    fclose( saveJsonFile );

    enemyStatsLevelMultiplier = (*(rapidjson::Value*)(saveDoc))["game"]["enemyStatsLevelMultiplier"].GetFloat();
    level = (*(rapidjson::Value*)(saveDoc))["game"]["level"].GetInt();

    player->Load( saveDoc );
    userInterface->Load( saveDoc );

    Reset();
    Start();
}

void Game::IncreaseLevel()
{
    ++level;
    Start();
}

void Game::ChangeEnemyLevelMultiplier( float multiplier )
{
    enemyStatsLevelMultiplier = multiplier;
    Start();
}

void Game::LoseGame()
{
    ResetMenus();
    Reset();
    loseMenu = true;
    isPaused = true;
}

void Game::NewGame()
{
    level = 0;
    ResetMenus();
    Reset();
    isPaused = true;
    difficultyMenu = true;
}

void Game::Start()
{
    ResetMenus();
}

void Game::MainMenu()
{
    ResetMenus();
    mainMenu = true;
    isPaused = true;
}

void Game::WinMenu()
{
    Reset();
    ResetMenus();
    winMenu = true;
    isPaused = true;
}

void Game::ShopMenu()
{
    ResetMenus();
    shopMenu = true;
    isPaused = true;
}

void Game::ResetMenus()
{
    mainMenu = false;
    isPaused = false;
    difficultyMenu = false;
    winMenu = false;
    loseMenu = false;
    shopMenu = false;
}