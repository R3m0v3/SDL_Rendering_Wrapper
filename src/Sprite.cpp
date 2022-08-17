#include <Sprite.hpp>
#include <iostream>


Sprite::Sprite(std::string path, Position* pos, Dimension* dim, uint32_t collumns, uint32_t rows, SDL_Renderer* renderer, uint32_t ID) : Object(SPRITE_OBJECT_TYPE, ID){
    color = {255, 255, 255, 255};
    this->path = path;
    rect.x = pos->x; rect.y = pos->y; rect.w = dim->w; rect.h = dim->h;
    this->collumns = collumns;
    this->rows = rows;
    this->renderer = renderer;

    surface = IMG_Load(path.c_str());
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    
    spriteOffset.w = surface->w/collumns;
    spriteOffset.h = surface->h/rows;
    spriteOffset.x = 0; spriteOffset.y = surface->h-spriteOffset.h;//0;
}


void Sprite::setPosition(Position* pos){
    rect.x = pos->x;
    rect.y = pos->y;
}

Position Sprite::getPosition(){
    Position pos;
    pos.x = rect.x;
    pos.y = rect.y;
    return pos;
}


void Sprite::setDimensions(Dimension* dim){
    rect.w = dim->w;
    rect.h = dim->h;
}

Dimension Sprite::getDimensions(){
    Dimension dim;
    dim.w = rect.w;
    dim.h = rect.h;
    return dim;
}


void Sprite::setColor(Color* color){
    this->color = *color;
}

Color Sprite::getColor(){
    return color;
}


void Sprite::spriteStepRight(){
    if(spriteOffset.x >= surface->w-2*spriteOffset.w){
        spriteOffset.x = 0;
    }
    else     
        spriteOffset.x += spriteOffset.w;
}

void Sprite::spriteStepLeft(){
    if(spriteOffset.x <= spriteOffset.w)
        spriteOffset.x = surface->w-spriteOffset.w;
    else
        spriteOffset.x -= spriteOffset.w;
}

void Sprite::spriteStepDown(){
    if(spriteOffset.y >= surface->h-spriteOffset.h)
        spriteOffset.y = 0;
    else
        spriteOffset.y += spriteOffset.h;
}

void Sprite::spriteStepUp(){
    if(spriteOffset.y <= 0)
        spriteOffset.y = surface->h-spriteOffset.h;
    else
        spriteOffset.y -= spriteOffset.h;

}

/*
void Sprite::setTinySpriteOffset(int32_t w, int32_t h){
    tinyCorrectionOffset.w = w; tinyCorrectionOffset.h = h;
    spriteOffset.w = surface->w/collumns + w;
    spriteOffset.h = surface->h/rows + h;
    
    spriteOffset.x = tinyCorrectionOffset.w;
    spriteOffset.y = tinyCorrectionOffset.h;
}
*/

void Sprite::render(SDL_Renderer* renderer){
    SDL_RenderCopy(renderer, texture, &spriteOffset, &rect);
}