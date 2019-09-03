//
//  Grid.hpp
//  BaseProject
//
//  Created by Daniel Harvey on 01/07/2019.
//  Copyright © 2019 Daniel Harvey. All rights reserved.
//

#ifndef Grid_hpp
#define Grid_hpp
#include "Cell.hpp"
#include <vector>
#include "Window.hpp"
#include <SFML/Graphics.hpp>
#include <fstream>
#include "xmlwriter.h"
#include <thread>
#include "SelbaWard.hpp"



class Grid
{
public:
    Grid(){};
    ~Grid() = default;
    
    void SetupGrid(sf::Vector2f gridPos, int width, int height);
    void SetupGrid(sf::Vector2f gridPos, std::string ImagePath);

    bool PointOnCanvas(sf::Vector2f Pos, bool adjustme = true);
    void Render(Window &window, bool isshown = true);
    sf::Color GetPixel(sf::Vector2f pos);
    void SetCell(sf::Vector2f pos, sf::Color colour);
    void SaveImage(std::string filename);
   
    
    bool Changed = true;
	
    int Width,  Height;
	unsigned int TotalSize;
	 sf::Color GridBackground;
    
    sf::Vector2f GridPosition;

    
private:

    bool MouseOnGrid = false;
    
    sf::Image renderimage;
    sf::RectangleShape canvas;
    sf::Texture canvasTexture;
    
};

#endif /* Grid_hpp */
