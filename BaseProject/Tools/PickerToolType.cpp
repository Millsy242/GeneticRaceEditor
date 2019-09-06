//
//  PickerToolType.cpp
//  GeneticRaceEditor
//
//  Created by Daniel Harvey on 02/09/2019.
//  Copyright © 2019 Daniel Harvey. All rights reserved.
//
#include "Tool.hpp"
#include "Canvas.hpp"

void PickerToolType::OnMouseDown(sf::Vector2i MousePos, Canvas& canvas, PaintOptions &options)
{
    if(canvas.GetPixel(sf::Vector2f(MousePos)) != sf::Color::Transparent)
        options.MainBrushColour = canvas.GetPixel(sf::Vector2f(MousePos));
}
void PickerToolType::OnMouseUp(sf::Vector2i MousePos, Canvas& canvas, PaintOptions &options)
{
    
}
void PickerToolType::OnMouseMove(sf::Vector2i MousePos, Canvas& canvas, PaintOptions &options)
{
    
}
