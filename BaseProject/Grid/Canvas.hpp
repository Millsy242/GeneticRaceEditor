//
//  Grid.hpp
//  BaseProject
//
//  Created by Daniel Harvey on 01/07/2019.
//  Copyright © 2019 Daniel Harvey. All rights reserved.
//

#ifndef Canvas_hpp
#define Canvas_hpp

#include <vector>
#include "Window.hpp"
#include <SFML/Graphics.hpp>
#include <fstream>
#include "xmlwriter.h"
#include <thread>
#include "SelbaWard.hpp"



class Canvas
{
public:
    Canvas(){};
    ~Canvas() = default;
    
    void SetupCanvas(sf::Vector2f gridPos, int width, int height);
    void SetupCanvas(sf::Vector2f gridPos, std::string ImagePath);

    bool PointOnCanvas(sf::Vector2f Pos, bool adjustme = true);
    void Render(Window &window, bool isshown = true);
    sf::Color GetPixel(sf::Vector2f pos);
    void SetPixel(sf::Vector2f pos, sf::Color colour);
    void SaveImage(std::string filename);
    void saveSpriteToCanvas(const sf::Texture *texture,sf::Vector2f pos);
    
    bool Changed = true;
	
    int Width,  Height;
	unsigned int TotalSize;
	 sf::Color GridBackground;
    
    sf::Vector2f GridPosition;
    sf::RectangleShape canvasShape;
    
protected:

    bool MouseOnGrid = false;
    
    sf::Image renderimage;
    
    sf::Texture canvasTexture;
    
};

#endif /* Canvas_hpp */
