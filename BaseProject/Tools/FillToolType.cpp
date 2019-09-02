//
//  BrushToolType.cpp
//  GeneticRaceEditor
//
//  Created by Daniel Harvey on 25/08/2019.
//  Copyright © 2019 Daniel Harvey. All rights reserved.
//

#include "Tool.hpp"
#include <vector>
#include "Grid.hpp"
#include <iostream>
#include <thread>


void FillToolType::OnMouseDown(sf::Vector2i MousePos, Grid& grid, const PaintOptions &options)
{

        sf::Color target = grid.GetPixel(sf::Vector2f(MousePos));
        if(options.MainBrushColour == target)
        {
            return;
        }
        std::vector<std::pair<int, int>> S;
        
        S.push_back(std::pair<int,int>(MousePos.y,MousePos.x));
        while(S.size() > 0)
        {
            auto p = S.back();
            S.pop_back();
            int x = p.second;
            int y = p.first;
            if(grid.PointOnCanvas(sf::Vector2f(x-grid.GridPosition.x,y-grid.GridPosition.y)))
            {
                if(grid.GetPixel(sf::Vector2f(x, y)) == target)
                {
                    grid.SetCell(sf::Vector2f(x, y), options.MainBrushColour);
                    
                    S.push_back({y-1,x});
                    
                    S.push_back({y,x+1});
                    
                    S.push_back({y,x-1});
                    
                    S.push_back({y+1,x});
                }
            }
        }
        

}

void FillToolType::OnMouseUp(sf::Vector2i MousePos, Grid& grid, const PaintOptions &options)
{
    
}
void FillToolType::OnMouseMove(sf::Vector2i MousePos, Grid& grid, const PaintOptions &options)
{
    
}
