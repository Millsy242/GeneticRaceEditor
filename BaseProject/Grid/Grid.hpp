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

enum class Tool
{
    eNull,
    eBrush,
    eFill,
    eColourPick,
    eErase
};

enum BrushShape
{
    eCircle,
    eSquare
};

class Grid
{
public:
    Grid(){};
    ~Grid() = default;
    
    void SetupGrid(sf::Vector2f gridPos, int width, int height, int cellW, int cellH);
    void SetupGrid(sf::Vector2f gridPos, std::string ImagePath, int cellW=1, int cellH=1);
    void SetupGrid(sf::Vector2f gridPos, sf::Image Image, int cellW=1, int cellH=1);
    
    
    void Render(Window &window, bool isshown = true);
    
    void SetCell(sf::Vector2f pos, sf::Color colour);
    void SetCell(int xGrid, int yGrid, sf::Color colour);
    void SetBackgroundColour(sf::Color NewColour);
    
    
    
    bool PointOnGrid(sf::Vector2f point, bool GridPos);
    sf::Vector2i ConverttoGrid(sf::Vector2f point, bool GridPos); 
    
    bool isMouseOnGrid();
    
    bool LoadFromImage(sf::Image image);
    bool LoadFromImage(std::string ImageFilepath);
    
    void LoadFromFile(std::string FileName);
    
    void SaveToFile(std::string &data, sw::ProgressBar &bar);
    
    bool Changed = true;
	
	 int Width,  Height,  CellW,  CellH, NumRow,NumCol;
	unsigned int TotalSize;
	 sf::Color GridBackground;
    
      sf::Vector2f GridPosition;
     std::vector<std::vector<Cell>> myGrid;
    
private:
    
    
	
    bool MouseOnGrid = false;
    
    unsigned int temp = 0; 
    
  
    
    sf::Texture gridTexture;
    sf::Sprite gridSprite;
    
    sf::RectangleShape rect;
    
    
    sf::Color TargetColour{sf::Color::White}, ReplaceColour{sf::Color::Black};
    
    sf::RenderTexture rendertexture; 
  
    
};

#endif /* Grid_hpp */
