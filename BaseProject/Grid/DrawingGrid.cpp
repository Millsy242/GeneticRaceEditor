//
//  DrawingGrid.cpp
//  BaseProject
//
//  Created by Daniel Harvey on 02/08/2019.
//  Copyright © 2019 Daniel Harvey. All rights reserved.
//

#include "DrawingGrid.hpp"
#include "Track.hpp"

DrawingGrid::DrawingGrid()
{
}
void DrawingGrid::Start(int width, int height, float offsetx, float offsety, int cellW, int cellH)
{
    grid.SetupGrid({offsetx,offsety}, width, height, cellW,cellH);
    options.shape.setRadius(options.BrushSize);
    options.shape.setFillColor(sf::Color::Transparent);
    options.shape.setOrigin(options.shape.getLocalBounds().width/2, options.shape.getLocalBounds().height/2);
    options.shape.setPointCount(2000);
    options.shape.setOutlineThickness(3);
    options.shape.setOutlineColor(sf::Color::Magenta);
	
	pointerSquare = options.shape;
	pointerSquare.setPointCount(4);
	pointerSquare.setRotation(45);
    
    options.BrushSize = 20;
    currentTool = std::make_unique<NullToolType>();
    
    mythread = std::thread(&DrawingGrid::Controls, this);
}
sf::CircleShape& DrawingGrid::GetPointer()
{
	if( brushShape == BrushShape::eCircle)
		return options.shape;
	else if (brushShape == BrushShape::eSquare)
		return pointerSquare;
	else
		return options.shape;
}
void DrawingGrid::UpdatePointers(int brushSize, bool ReCenter, sf::Vector2i MousePos)
{
	options.shape.setRadius(options.BrushSize);
	pointerSquare.setRadius(options.BrushSize);
	if(ReCenter)
	{
		options.shape.setOrigin(options.shape.getLocalBounds().width/2, options.shape.getLocalBounds().height/2);
        pointerSquare.setOrigin(options.shape.getLocalBounds().width/2, options.shape.getLocalBounds().height/2);
	}
	if(MousePos != sf::Vector2i(-1,-1))
	{
		options.shape.setPosition(MousePos.x,MousePos.y);
		pointerSquare.setPosition(MousePos.x,MousePos.y);
	}
}
void DrawingGrid::Input(sf::Vector2i mousepos)
{
    imguiHovered = ImGui::IsAnyWindowHovered();
    MousePos = mousepos;
	ImGuiWindowFlags window_flags = 0;
	
	window_flags |= ImGuiWindowFlags_MenuBar;
	//window_flags |= ImGuiWindowFlags_NoMove;
	window_flags |= ImGuiWindowFlags_NoResize;
	
	 float col[3]{options.MainBrushColour.r/255.f, options.MainBrushColour.g/255.f,options.MainBrushColour.b/255.f};
	ImGui::Begin("Drawing Tools",NULL, window_flags);
	
	if(SelectedTool != Tool::eFill )
	{
		if(ImGui::SliderInt("BrushSize", &options.BrushSize, 1, 500))
			UpdatePointers(options.BrushSize, true);
	}
	if(ImGui::ColorPicker3("Colour Pick", col))
	{
		options.MainBrushColour = sf::Color(col[0]* 255.f,col[1]* 255.f,col[2]* 255.f);
	}
	if(ImGui::Button("Brush"))
    {
		 SelectedTool = Tool::eBrush;
    currentTool = std::make_unique<BrushToolType>();
    }
	if(ImGui::Button("Fill"))
    {
		SelectedTool = Tool::eFill;
    currentTool = std::make_unique<FillToolType>();
    }
	if(ImGui::Button("Pick"))
    {
		 SelectedTool = Tool::eColourPick;
        currentTool = std::make_unique<PickerToolType>();
    }
    if(ImGui::Button("Spray"))
    {
        SelectedTool = Tool::eSpray;
        currentTool = std::make_unique<SprayToolType>();
    }
	if(ImGui::Button("Erase"))
    {
		 SelectedTool = Tool::eErase;
    currentTool = std::make_unique<EraserToolType>();
    }
	if(ImGui::Button("Null"))
    {
        SelectedTool = Tool::eNull;
		currentTool = std::make_unique<NullToolType>();
    }
	if(ImGui::Button("Circle"))
		brushShape = BrushShape::eCircle;
	if(ImGui::Button("Square"))
		brushShape = BrushShape::eSquare;
	
	ImGui::End();
    UpdatePointers(options.BrushSize, true, MousePos);
 
}
void DrawingGrid::Controls()
{
    while(true)
    {
        if(!updatinggrid)
        {
            if(!imguiHovered && grid.PointOnCanvas(sf::Vector2f(MousePos),false)) //Allow ImGui Windows to be above grid whilst also not drawing on grid
            {
                if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    updatinggrid = true;
                    currentTool->OnMouseDown(MousePos, grid, options);
                    updatinggrid = false;
                }
            }
        }
    }
}
void DrawingGrid::Render(Window *window)
{	
    grid.Render(*window,IsShown);
    if(IsShown)
    {    
        //if(grid.isMouseOnGrid())
        {
            window->draw(GetPointer());
            switch (SelectedTool)
            {
                case Tool::eNull:
                    cursor.loadFromSystem(sf::Cursor::NotAllowed);
                    break;
                case Tool::eBrush:
                    cursor.loadFromSystem(sf::Cursor::Cross);
                    break;
                case Tool::eFill:
                    cursor.loadFromSystem(sf::Cursor::Text);
                    break;
                case Tool::eColourPick:
                    cursor.loadFromSystem(sf::Cursor::Hand);
                    break;
                case Tool::eErase:
                    cursor.loadFromSystem(sf::Cursor::SizeVertical);
                    break;
                default:
                    break;
            }
            
            window->SFwindow.setMouseCursor(cursor);
        }
        /*
        else
        {
            cursor.loadFromSystem(sf::Cursor::Arrow);
            window->SFwindow.setMouseCursor(cursor);
        }            */
    }
    else
    {
        cursor.loadFromSystem(sf::Cursor::Arrow);
        window->SFwindow.setMouseCursor(cursor);
    }
}
void DrawingGrid::saveTracktoGrid(Track *track)
{
	
	sf::IntRect Rect;
	int width{4},height{4};
    auto splines = track->getSplines();
	
    //left
    auto LSplineVect = splines.first->getSplineLine();
    for(int l{0}; l<LSplineVect.size(); l++)
    {
		Rect = sf::IntRect(LSplineVect[l].x-(width),LSplineVect[l].y - (height), width*2,height*2);
		for(int y = Rect.top; y < (Rect.top + height*2); y++)
		{
			for(int x = Rect.left; x < (Rect.left + width*2); x++)
			{
				grid.SetCell(sf::Vector2f(x,y), sf::Color(64,64,64));
			}
		}
    }
    //right
    auto RSplineVect = splines.second->getSplineLine();

	for(int r{0}; r<RSplineVect.size(); r++)
	{
		Rect = sf::IntRect(RSplineVect[r].x-(width),RSplineVect[r].y - (height), width*2,height*2);
		for(int y = Rect.top; y < (Rect.top + height*2); y++)
		{
			for(int x = Rect.left; x < (Rect.left + width*2); x++)
			{
				grid.SetCell(sf::Vector2f(x,y), sf::Color(64,64,64));
			}
		}
	}
}
void DrawingGrid::Onleave()
{
    IsShown = false;
}
void DrawingGrid::OnReEntry()
{
     IsShown = true;
}

Grid* DrawingGrid::getGrid()
{
    return &grid;
}
void DrawingGrid::Serialise(Yaml::Node &root, sw::ProgressBar &bar)
{/*

	std::string Data = "";

	Data += "Cell Width: " + std::to_string(grid.CellW) + "\n"
	"Cell Height: " + std::to_string(grid.CellH) + "\n"
	"GridSize: " + std::to_string(grid.TotalSize) + "\n"
	"TrackEdgeColour: " + std::to_string((uint32_t)TrackEdgeColour.toInteger()) + "\n"
	"BackgroundColour: " + std::to_string((uint32_t)grid.GridBackground.toInteger()) + "\n"
	"Optimise: " + std::to_string((int)Optimise) + "\n\n\n";
    bar.setPercentage(bar.getPercentage()+1);

	if(!Optimise)
	{
		//Only run this when we dont want to optimise
		//Optimising involves only saving the Background colour,
		//Then using the Track Nodes Data to create the Track Ingame.
		//This is fine as long as there are no manual edits to the grid
		//such as: fine tuning tracks, adding trackside art etc.
		grid.SaveToFile(Data,bar);
		
		try
		{
			Yaml::Parse(root, Data);
		}
		catch (const Yaml::Exception e)
		{
			std::cout << "Exception " << e.Type() << ": " << e.what() << std::endl;
			return;
		}
		
	}
	
  */
	
}
