//
//  PickerToolType.cpp
//  GeneticRaceEditor
//
//  Created by Daniel Harvey on 02/09/2019.
//  Copyright © 2019 Daniel Harvey. All rights reserved.
//
#include "Tool.hpp"
#include "Grid.hpp"

void PickerToolType::OnMouseDown(sf::Vector2i MousePos, Grid& grid, PaintOptions &options)
{
    if(grid.GetPixel(sf::Vector2f(MousePos)) != sf::Color::Transparent)
        options.MainBrushColour = grid.GetPixel(sf::Vector2f(MousePos));
}
void PickerToolType::OnMouseUp(sf::Vector2i MousePos, Grid& grid, PaintOptions &options)
{
    
}
void PickerToolType::OnMouseMove(sf::Vector2i MousePos, Grid& grid, PaintOptions &options)
{
    
}
