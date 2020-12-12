#include "Player.hpp"

bool Player::Summon( int cost )
{
    if( cost > fujika ) return false;
    else
    {
        fujika -= cost;
        return true;
    }
}

void Player::Update()
{
    if( frameCounter == FPS )
    {
        if( fujika != fujikaLimit )
        {
            if( fujika + fukoGain > fujikaLimit ) fujika = fujikaLimit;
            else fujika += fujikaGain;
        } 
        else if ( fuko != fukoLimit )
        {
            if( fuko + fukoGain > fukoLimit ) fuko = fukoLimit;
            else fuko += fukoGain;
        }

        frameCounter = 0;
    }
    else ++frameCounter;
        
}

void Player::Reset()
{
    fujika = 0;
    frameCounter = 0;
}