//
//  BrushToolType.cpp
//  GeneticRaceEditor
//
//  Created by Daniel Harvey on 25/08/2019.
//  Copyright © 2019 Daniel Harvey. All rights reserved.
//

#include <stdio.h>
#include "Tool.hpp"

void EraserToolType::OnMouseDown(sf::Vector2i MousePos, Grid& grid, const PaintOptions &options)
{
    auto ShapeHeight = options.shape.getGlobalBounds().height;
    auto ShapeWidth = options.shape.getGlobalBounds().width;
    
    for(int yi = (options.shape.getGlobalBounds().top-grid.GridPosition.y); yi < ((options.shape.getGlobalBounds().top + ShapeHeight) - grid.GridPosition.y); yi++)
    {
        for(int xi = (options.shape.getGlobalBounds().left-grid.GridPosition.x); xi < ((options.shape.getGlobalBounds().left + ShapeWidth) - grid.GridPosition.x); xi++)
        {
            
            //make sure we're inside a cell
            auto gridcoords = grid.ConverttoGrid({(float)xi,(float)yi}, true);
            
            if(grid.PointOnGrid(sf::Vector2f(gridcoords.x,gridcoords.y), true))
            {
                if( grid.myGrid[gridcoords.y][gridcoords.x].MouseInCell(sf::Vector2f(MousePos),ShapeWidth/2))
                {
                    grid.SetCell(gridcoords.x,gridcoords.y, grid.GridBackground);
                }
                
            }
        }
    }
    
    

}
void EraserToolType::OnMouseUp(sf::Vector2i MousePos, Grid& grid, const PaintOptions &options)
{
    
}
void EraserToolType::OnMouseMove(sf::Vector2i MousePos, Grid& grid, const PaintOptions &options)
{
    
}
