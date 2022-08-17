#include <Textbox.hpp>
#include <string>
#include <Object.hpp>
#include <iostream>


Textbox::Textbox(std::string text, std::string font, uint32_t fontsize, Position* pos,  Dimension* dim, SDL_Renderer* renderer, uint32_t ID) : Object(TEXTBOX_OBJECT_TYPE, ID){
    this->text = text;
    colorText = {255, 255, 255, 255};
    this->renderer = renderer;
    
    this->font = TTF_OpenFont(font.c_str(), fontsize);
    if(this->font == NULL){
        std::cerr << "Font not Found! Wrong Path?" << std::endl;
        return;
    }

    SDL_Color tmpColorText = {255, 255, 255, 255};
    SDL_Color tmpColorBack = {0, 0, 0, 255};
    //SDL_Surface* surface = TTF_RenderText_LCD(this->font, text.c_str(), tmpColorText, tmpColorBack);
    SDL_Surface* surface = TTF_RenderText_Blended(this->font, text.c_str(), tmpColorText);

    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    rect.x = pos->x;
    rect.y = pos->y;
    rect.w = dim->w;
    rect.h = dim->h;
}

    
std::string Textbox::getText(){
    return text;
}

void Textbox::setText(std::string text){
    this->text = text;
    SDL_Color tmpColorText = {colorText.R, colorText.G, colorText.B, colorText.A};
    //SDL_Color tmpColorBack = {colorBackground.R, colorBackground.G, colorBackground.B, colorBackground.A};
    //SDL_Surface* surface = TTF_RenderText_LCD(this->font, text.c_str(), tmpColorText, tmpColorBack);
    SDL_Surface* surface = TTF_RenderText_Blended(this->font, text.c_str(), tmpColorText);
    SDL_DestroyTexture(texture);
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
}

Position Textbox::getPosition(){
    Position pos;
    pos.x = rect.x;
    pos.y = rect.y;
    return pos;
}

void Textbox::setPosition(uint32_t x, uint32_t y){
    rect.x = x;
    rect.y = y;
}

/*
void Textbox::setBackgroundColor(Color* color){
    colorBackground = {color->R, color->G, color->B, color->A};
    setText(this->text);
}
*/

void Textbox::setColor(Color* color){
    colorText = {color->R, color->G, color->B, color->A};
    setText(this->text);
}

void Textbox::render(SDL_Renderer* renderer){
    SDL_RenderCopy(renderer, texture, NULL, &rect);

}