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
    for(int y=-options.BrushSize; y<=options.BrushSize; y++)
    {
        for(int x=-options.BrushSize; x<=options.BrushSize; x++)
        {
            int actualX = MousePos.x + x;
            int actualY = MousePos.y + y;
            
            int dx = std::abs(MousePos.x - actualX);
            int dy = std::abs(MousePos.y - actualY);
            
            if(std::sqrt(dx * dx + dy * dy) <= options.BrushSize)
            {
                grid.SetCell(sf::Vector2f(MousePos.x+x,MousePos.y+y), grid.GridBackground);
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
