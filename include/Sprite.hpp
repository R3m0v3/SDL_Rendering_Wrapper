#ifndef SPRITE_HPP
#define SPRITE_HPP

#include <SDL_image.h>
#include <Object.hpp>
#include <Color.hpp>
#include <Position.hpp>
#include <Dimension.hpp>
#include <string>

class Sprite : public Object{
private:

    Color color;
    std::string path;
    SDL_Texture* texture;
    SDL_Surface* surface;
    SDL_Rect spriteOffset; //for offset in the picture 
    Dimension tinyCorrectionOffset; //offset to correct the sprite
    SDL_Rect rect; //for position on screen
    uint32_t collumns;
    uint32_t rows;
    SDL_Renderer* renderer;

public:
    Sprite(std::string path, Position* pos, Dimension* dim, uint32_t collumns, uint32_t rows, SDL_Renderer* renderer, uint32_t ID);

    void setPosition(Position* pos);
    Position getPosition();

    void setDimensions(Dimension* dim);
    Dimension getDimensions();

    void setColor(Color* color);
    Color getColor();

    void spriteStepRight();
    void spriteStepLeft();
    void spriteStepDown();
    void spriteStepUp();

    //void setTinySpriteOffset(int32_t w, int32_t h);

    void render(SDL_Renderer* renderer);

};

#endif