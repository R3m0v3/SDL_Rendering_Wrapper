#include <Window.hpp>
#include <Rectangle.hpp>
#include <Textbox.hpp>
#include <Sprite.hpp>
#include <iostream>
#include <SDL_ttf.h>

Window::Window(std::string Title, uint32_t windowPosX, uint32_t windowPosY, uint32_t windowWidth, uint32_t windowHeight, uint32_t SDL_FLAGS){
  if(SDL_Init(SDL_INIT_EVERYTHING != 0)){
    std::cerr << "SDL Init failed!" << std::endl;
  }

  if(TTF_Init() == -1)
    std::cerr << "SDL TTF Init failed!" << std::endl;

  if(IMG_Init(IMG_INIT_PNG|IMG_INIT_JPG) == 0)
    std::cerr << "SDL IMG Init failed!" << std::endl;

  sdlWindow = SDL_CreateWindow(Title.c_str(), windowPosX, windowPosY, windowWidth, windowHeight, SDL_FLAGS);
  sdlRenderer = SDL_CreateRenderer(sdlWindow, 0, 0);

  SDL_SetRenderDrawBlendMode(sdlRenderer, SDL_BLENDMODE_BLEND);

  objectList = new std::vector<Object*>();
  events = new std::vector<SDL_Event>();
  FPS = 60;

}

Window::~Window(){
  SDL_DestroyWindow(sdlWindow);
  SDL_DestroyRenderer(sdlRenderer);
}

void Window::pollEvents(){
  //clear events then load new events
  events->clear();

  SDL_Event event;
  while(SDL_PollEvent(&event)){
    events->push_back(event);
  }
}

void Window::render(){
  SDL_SetRenderDrawColor(sdlRenderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
  SDL_RenderClear(sdlRenderer);

  for(int i = 0; i<objectList->size(); i++){
    switch (objectList->at(i)->getType()) {
      case RECTANGLE_OBJECT_TYPE: ((Rectangle*)objectList->at(i))->render(sdlRenderer); break;
      case TEXTBOX_OBJECT_TYPE: ((Textbox*)objectList->at(i))->render(sdlRenderer); break;
      case SPRITE_OBJECT_TYPE: ((Sprite*)objectList->at(i))->render(sdlRenderer); break;
    }
  }

  SDL_RenderPresent(sdlRenderer);

  SDL_Delay(1.0/(float)FPS*1000.0);
}

void Window::close(){
  delete this;
}

SDL_Window* Window::getSDLWindow(){
  return sdlWindow;
}

SDL_Renderer* Window::getSDLRenderer(){
  return sdlRenderer;
}

void Window::maximize(){
  SDL_MaximizeWindow(sdlWindow);
}

void Window::minimize(){
  SDL_MinimizeWindow(sdlWindow);
}

uint32_t Window::getFPS(){
  return FPS;
}

void Window::setFPS(uint32_t FPS){
  this->FPS = FPS;
}

uint32_t Window::getWidth(){
  int w, h;
  SDL_GetWindowSize(sdlWindow, &w, &h);
  return w;
}

uint32_t Window::getHeight(){
  int w, h;
  SDL_GetWindowSize(sdlWindow, &w, &h);
  return h;
}

std::vector<Object*>* Window::getObjectList(){
  return objectList;
}

void Window::addObject(Object* object){
  objectList->push_back(object);
}

void Window::deleteObject(uint32_t ID){
  for(int i = 0; i<objectList->size(); i++)
    if(objectList->at(i)->getID() == ID){
      objectList->erase(objectList->begin()+i);
      return;
    }
}

uint32_t Window::nextFreeID(){
  if(objectList->empty()) return 0;
  return objectList->at(objectList->size()-1)->getID()+1;
}

bool Window::getKeyStatus(SDL_Scancode scancode){
  for(int i = 0; i<events->size(); i++){
    if(events->at(i).key.keysym.scancode == scancode)
      return true;
  }
  return false;
}

bool Window::getWindowEvent(SDL_WindowEventID event){
  //here the this pointer goes from (some mem address) to 0x0
  for(int i = 0; i<this->events->size(); i++){
    if(events->at(i).window.event == event)
      return true;
  }
  return false;
}


/*
bool Window::getEventStatus(SDL_Event event){
  for(int i = 0; i<events->size(); i++){
    if(events->at(i) == event)
      return true;
  }
  return false;
}
*/


void Window::setMinimumSize(uint32_t w, uint32_t h){
  SDL_SetWindowMinimumSize(sdlWindow, w, h);
}
