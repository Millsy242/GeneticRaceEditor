//
//  Cell.hpp
//  BaseProject
//
//  Created by Daniel Harvey on 01/07/2019.
//  Copyright © 2019 Daniel Harvey. All rights reserved.
//

#ifndef Cell_hpp
#define Cell_hpp
#include <SFML/Graphics.hpp>

enum class CellType
{
    eNull, eTrack, eGrass, eEdge
};

class Cell
{
public:
    Cell(int left, int top, int right, int base, int width, int height,unsigned int Cellnum);
    ~Cell() = default;
    
    
    bool backgroundColour = true; 
    sf::IntRect TextureRect; 
    int Width, Height, Left, Top, Right, Base;
    
    CellType celltype = CellType::eNull;
    
    bool active = false;
    
    
    bool MouseInCell(sf::Vector2f MousePosition);
    bool MouseInCell(sf::Vector2f MousePosition, int radius);
    bool MouseInCell(sf::Vector2f MousePosition, sf::FloatRect MouseShape );
    
    
    sf::Color getColour();
    void SetColour(sf::Color col, bool isBackground = false);
    
    const unsigned int CellNumber = 0;
    
private:
    sf::Color Colour;
	sf::FloatRect cell;
	
};

#endif /* Cell_hpp */
