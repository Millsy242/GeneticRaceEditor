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
            
            //make sure we're inside a cell
            auto gridcoords = grid.ConverttoGrid(sf::Vector2i(xi,yi), true);
            int x = gridcoords.x;
            int y = gridcoords.y;
            
            if(y < 0 )
                y = 1;
            if(x < 0)
                x = 1;
            if(y>grid.NumRow)
                y = grid.NumRow;
            if(x>grid.NumCol)
                x = grid.NumCol;
            
            sf::Vector2f m(MousePos.x,MousePos.y);
            if( grid.CheckMouseInCell(x,y,m,ShapeWidth/2))
            {
                grid.SetCell(gridcoords.x, gridcoords.y, options.MainBrushColour);
            }
        }
    }
}
void BrushToolType::OnMouseUp(sf::Vector2i MousePos, Grid& grid, const PaintOptions &options)
{
    
}
void BrushToolType::OnMouseMove(sf::Vector2i MousePos, Grid& grid, const PaintOptions &options)
{
    
}
