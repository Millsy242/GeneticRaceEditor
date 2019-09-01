//
//  BrushToolType.cpp
//  GeneticRaceEditor
//
//  Created by Daniel Harvey on 25/08/2019.
//  Copyright © 2019 Daniel Harvey. All rights reserved.
//


#include "Tool.hpp"
#include <iostream>
#include "Grid.hpp"
#include <vector>

void BrushToolType::OnMouseDown(sf::Vector2i MousePos, Grid& grid, const PaintOptions &options)
{
    auto ShapeHeight = options.shape.getGlobalBounds().height;
    auto ShapeWidth = options.shape.getGlobalBounds().width;
    
    for(int yi = (options.shape.getGlobalBounds().top-grid.GridPosition.y); yi < ((options.shape.getGlobalBounds().top + ShapeHeight) - grid.GridPosition.y); yi++)
    {
        for(int xi = (options.shape.getGlobalBounds().left-grid.GridPosition.x); xi < ((options.shape.getGlobalBounds().left + ShapeWidth) - grid.GridPosition.x); xi++)
        {
            //int DX = MousePos.x - std::max(MousePos.x, std::min(MousePos.x, int(MousePos.x+ShapeWidth)) );
            //int DY = MousePos.y - std::max(MousePos.y, std::min(MousePos.y, int(MousePos.y+ShapeHeight)) );
            //int dx = std::abs(MousePos.x - MousePos.x+ShapeWidth);
            //int dy = std::abs(MousePos.y - MousePos.y+ShapeHeight);
            
            //if((DX * DX + DY * DY) < (options.BrushSize * options.BrushSize))
            //if(std::sqrt(dx * dx + dy * dy) <= options.shape.getRadius())
                grid.SetCell(sf::Vector2f(xi,yi), options.MainBrushColour);
        }
    }
}
void BrushToolType::OnMouseUp(sf::Vector2i MousePos, Grid& grid, const PaintOptions &options)
{
    
}
void BrushToolType::OnMouseMove(sf::Vector2i MousePos, Grid& grid, const PaintOptions &options)
{
    
}
