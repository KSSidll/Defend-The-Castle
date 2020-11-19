#include "PlayerSummon.hpp"

PlayerSummon::PlayerSummon(rapidjson::Value& object, SDL_Renderer* renderer)
{
    this->renderer = renderer;
    this->srcRect.x = object["srcRectX"].GetInt();
    this->srcRect.y = object["srcRectY"].GetInt();
    this->srcRect.h = object["srcRectH"].GetInt();
    this->srcRect.w = object["srcRectW"].GetInt();
    this->destRect.x = object["destRectX"].GetInt();
    this->destRect.y = object["destRectY"].GetInt();
    this->renderScale = object["renderScale"].GetFloat();

    this->cost = object["cost"].GetInt();
    this->health = object["health"].GetInt();
    this->attackDamage = object["attackDamage"].GetInt();
    this->movementSpeed = object["movementSpeed"].GetFloat();
    this->attackInterval = object["attackInterval"].GetFloat();
    this->range = object["range"].GetFloat();

    SDL_Surface* tempSurface = IMG_Load(object["textureSrc"].GetString());
    objTexture = SDL_CreateTextureFromSurface(renderer, tempSurface);
    SDL_FreeSurface(tempSurface);
}

PlayerSummon::~PlayerSummon()
{

}