//
//  DrawingGrid.hpp
//  BaseProject
//
//  Created by Daniel Harvey on 02/08/2019.
//  Copyright © 2019 Daniel Harvey. All rights reserved.
//

#ifndef DrawingGrid_hpp
#define DrawingGrid_hpp
#include "Tool.hpp"
#include <SFML/Graphics.hpp>
#include "Window.hpp"
#include "Grid.hpp"
#include "SelbaWard.hpp"
#include "Yaml.hpp"


enum class Tool
{
    eNull,
    eBrush,
    eFill,
    eColourPick,
    eSpray,
    eErase
};


enum BrushShape
{
    eCircle,
    eSquare
};
class Track;
class DrawingGrid
{
public:
    DrawingGrid();
    ~DrawingGrid(){};
    
    void Start(int width, int height, float offsetx, float offsety, int cellW, int cellH);
    void Start(float offsetx, float offsety, std::string filename);
    void Input(sf::Vector2i mousepos);
    void Render(Window *window);
    
    void Onleave();
    void OnReEntry(); 
	void saveTracktoGrid(Track *track);
    Grid* getGrid();
	
    void Serialise(Yaml::Node &root, sw::ProgressBar &bar, std::string filename); 
    
private:
    void Controls();
	sf::CircleShape& GetPointer();
	void UpdatePointers(int brushSize, bool ReCenter, sf::Vector2i MousePos = {-1,-1}); 
    
    Grid grid;
    int scale; 
    
    bool IsShown = false;
    bool imguiHovered = false; 
    
    std::thread mythread;
    bool updatinggrid = false; 
    sf::Vector2i MousePos = {0,0};
	sf::CircleShape pointerSquare;
    sf::Cursor cursor;
    sf::Cursor OnScreenCursor;
    BrushShape brushShape = BrushShape::eCircle;
    Tool SelectedTool = Tool::eNull;
	
	sf::Color TrackEdgeColour = sf::Color(64,64,64);
	
	bool Optimise = false;
    PaintOptions options; 
    std::unique_ptr<ToolType> currentTool;
    
};

#endif /* DrawingGrid_hpp */
