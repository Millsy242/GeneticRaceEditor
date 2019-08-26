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

void FillToolType::OnMouseDown(sf::Vector2i MousePos, Grid& grid, const PaintOptions &options)
{
    //make sure we're inside a cell
    auto gridcoords = grid.ConverttoGrid(sf::Vector2f(MousePos), true);
    
    if(grid.PointOnGrid(sf::Vector2f(gridcoords.x,gridcoords.y), true))
    {
        printf("point on grid1\n");
        sf::Color target = grid.myGrid[gridcoords.y][gridcoords.x].getColour();
        printf("targetcolour%i \n", target.toInteger());
        if( grid.myGrid[gridcoords.y][gridcoords.x].MouseInCell(sf::Vector2f(MousePos),5))
        {
            printf("mouse in cell -> %u\n", options.MainBrushColour.toInteger());
            if(options.MainBrushColour == target)
            {
                printf("brush colour == target\n");
                return;
            }
            std::vector<std::pair<int, int>> S;
            
            S.push_back(std::pair<int,int>(gridcoords.y,gridcoords.x));
            printf("Startwhile\n");
            int i = 0;
            while(S.size() > 0)
            {
                printf("while -> %i\n", i);
                auto p = S.back();
                S.pop_back();
                int x = p.second;
                int y = p.first;
                if(grid.PointOnGrid(sf::Vector2f(x,y), true))
                {
                    printf("point on grid2 -> %i\n",grid.myGrid[y][x].getColour().toInteger());
                    if(grid.myGrid[y][x].getColour() == target)
                    {
                        grid.SetCell(x, y, options.MainBrushColour);
                        printf("setcell\n");
                        S.push_back({y-1,x});
                        
                        S.push_back({y,x-1});
                        
                        S.push_back({y+1,x});
                        
                        S.push_back({y,x+1});
                        
                    }
                }
                i++;
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
