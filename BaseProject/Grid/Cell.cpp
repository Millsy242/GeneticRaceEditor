//
//  Cell.cpp
//  BaseProject
//
//  Created by Daniel Harvey on 01/07/2019.
//  Copyright © 2019 Daniel Harvey. All rights reserved.
//

#include "Cell.hpp"
#include <iostream>

Cell::Cell(int left, int top, int right, int base, int width, int height, unsigned int Cellnum) : Width(width), Height(height), Left(left), Top(top), Right(right), Base(base), active(true),TextureRect(left,top,width,height),Colour(sf::Color::Black), CellNumber(Cellnum), cell(sf::FloatRect(Left,Top,Width,Height))
{
	 
}
bool Cell::MouseInCell(sf::Vector2f MousePosition)
{
    if(cell.contains(MousePosition.x,MousePosition.y))
        return true;
        
    return false;
}
bool Cell::MouseInCell(sf::Vector2f MousePosition, int radius)
{
    //Is the centre of the mouse pointer in the cell?
    if(MouseInCell(MousePosition))
        return true;

    //https://yal.cc/rectangle-circle-intersection-test/
    int DX = MousePosition.x - std::max(Left, std::min((int)MousePosition.x, Right) );
    int DY = MousePosition.y - std::max(Top, std::min((int)MousePosition.y, Base) );
    
    return (DX * DX + DY * DY) < (radius * radius);
}
bool Cell::MouseInCell(sf::Vector2f MousePosition, sf::FloatRect MouseShape )
{
    //Is the centre of the mouse pointer in the cell?
	if(MouseInCell(MousePosition))
        return true;
	
	if(cell.contains(MouseShape.left, MouseShape.top))
		return true;
	if(cell.contains(MouseShape.left, MouseShape.top + MouseShape.height))
		return true;
	if(cell.contains(MouseShape.left + MouseShape.width, MouseShape.top))
		return true;
	if(cell.contains(MouseShape.left + MouseShape.width, MouseShape.top + MouseShape.height))
		return true;
	
    return false;
}
sf::Color Cell::getColour()
{
    return Colour;
}
void Cell::SetColour(sf::Color col, bool isBackground)
{
    Colour = col;
    backgroundColour = isBackground;
    
}
