//
//  BrushToolType.cpp
//  GeneticRaceEditor
//
//  Created by Daniel Harvey on 25/08/2019.
//  Copyright © 2019 Daniel Harvey. All rights reserved.
//


#include "Tool.hpp"
#include <iostream>
#include "Canvas.hpp"
#include <vector>

void BrushToolType::OnMouseDown(sf::Vector2i MousePos, Canvas& canvas, PaintOptions &options)
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
               canvas.SetPixel(sf::Vector2f(MousePos.x+x,MousePos.y+y), options.MainBrushColour);
            }
        }
    }
}
void BrushToolType::OnMouseUp(sf::Vector2i MousePos, Canvas& canvas, PaintOptions &options)
{
    
}
void BrushToolType::OnMouseMove(sf::Vector2i MousePos, Canvas& canvas, PaintOptions &options)
{
    
}
