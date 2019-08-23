//
//  DrawingGrid.hpp
//  BaseProject
//
//  Created by Daniel Harvey on 02/08/2019.
//  Copyright © 2019 Daniel Harvey. All rights reserved.
//

#ifndef DrawingGrid_hpp
#define DrawingGrid_hpp

#include <SFML/Graphics.hpp>
#include "Window.hpp"
#include "Grid.hpp"
#include "SelbaWard.hpp"
#include "Yaml.hpp"
class Track;
class DrawingGrid
{
public:
    DrawingGrid();
    ~DrawingGrid(){};
    
    void Start(int width, int height, float offsetx, float offsety, int cellW, int cellH);
    void Input(sf::Vector2i mousepos);
    void Render(Window *window);
    
    void Onleave();
    void OnReEntry(); 
	void saveTracktoGrid(Track *track);
    Grid* getGrid();
	
	void Serialise(Yaml::Node &root); 
    
private:
	
	sf::CircleShape& GetPointer();
	void UpdatePointers(int brushSize, bool ReCenter, sf::Vector2i MousePos = {-1,-1}); 
    
    Grid grid;
    
    bool IsShown = false; 
    
    int BrushSize = 20;
    sf::Color BrushColour;
    sf::CircleShape pointerCircle;
	sf::CircleShape pointerSquare;
    sf::Cursor cursor;
    sf::Cursor OnScreenCursor;
    BrushShape brushShape = BrushShape::eCircle;
    Tool SelectedTool = Tool::eNull;
	
	sf::Color TrackEdgeColour = sf::Color(64,64,64);
	
	bool Optimise = false; 
    
};

#endif /* DrawingGrid_hpp */
