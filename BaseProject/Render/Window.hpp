//
//  Window.hpp
//  SFGameEngine
//
//  Created by Daniel Harvey on 27/05/2019.
//  Copyright © 2019 Daniel Harvey. All rights reserved.
//

#ifndef Window_hpp
#define Window_hpp

#include "imgui.h"
#include "imgui-SFML.h"
#include "FPS.hpp"
#include <SFML/Graphics.hpp>

class Window
{
public:
    Window(const std::string& windowName);
    
    void Update();
    
    void BeginDraw(sf::Color colour = sf::Color::Magenta);
    void draw(const sf::Drawable& drawable);
    void EndDraw();
	
    bool IsOpen() const;
	sf::Vector2u GetCentre();
    sf::Vector2i GetMouse();
	void Process();
	
	void sharpen(std::vector<sf::Uint8> &pixels);
	
	void Close();
	
	void SetTitle(std::string title);
	
	bool RenderToTexture = false;
    
    float getDT();
    float ScreenHeight();
    float ScreenWidth();
    sf::RenderWindow SFwindow;
    sf::RenderTexture rendertexture;
    
private:
    void CalculateDT(); 
    
    
	sf::Sprite windowtexture;
	FPS fps;
    float deltatime;
    sf::Clock clock;
    bool temp = false;
};


#endif /* Window_hpp */
