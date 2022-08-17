#ifndef TEXTBOX_HPP
#define TEXTBOX_HPP

#include <string>
#include <Position.hpp>
#include <Object.hpp>
#include <Dimension.hpp>
#include <SDL_ttf.h>
#include <Color.hpp>

class Textbox : public Object{
private:
    std::string text;
    Color colorText;
    //Color colorBackground;

    TTF_Font* font;
    SDL_Texture* texture;
    SDL_Rect rect;

    SDL_Renderer* renderer;

public:
    Textbox(std::string text, std::string font, uint32_t fontsize, Position* pos, Dimension* dim, SDL_Renderer* renderer, uint32_t ID);
    
    std::string getText();
    void setText(std::string text);
    Position getPosition();
    void setPosition(uint32_t x, uint32_t y);
    //void setBackgroundColor(Color* color); //NOT FINISHED
    void setColor(Color* color);
    void render(SDL_Renderer* renderer);
};

#endif