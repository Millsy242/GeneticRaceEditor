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
    grid.SetupGrid({offsetx,offsety}, width, height);
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
    
    nullIcon.loadFromFile("Icons/null.png");
    pickerIcon.loadFromFile("Icons/picker.png");
    eraserIcon.loadFromFile("Icons/eraser.png");
    sprayIcon.loadFromFile("Icons/spray.png");
    brushIcon.loadFromFile("Icons/brush.png");
    fillIcon.loadFromFile("Icons/fill.png");
    circleIcon.loadFromFile("Icons/circle.png");
    squareIcon.loadFromFile("Icons/square.png");
    
    //input while loop reading png files from file named Track_X
    //Make sure to do while(file_exists("Track_" + X + ".png")
    
    
    mythread = std::thread(&DrawingGrid::Controls, this);
}
void DrawingGrid::Start(float offsetx, float offsety, std::string filename)
{
    grid.SetupGrid({offsetx,offsety}, filename);
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
    
    ToolControls();
    Layers();
    Textures();
   
    UpdatePointers(options.BrushSize, true, MousePos);
}
void DrawingGrid::ToolControls()
{
    ImGuiWindowFlags window_flags = 0;
     
    // window_flags |= ImGuiWindowFlags_MenuBar;
     //window_flags |= ImGuiWindowFlags_NoMove;
    // window_flags |= ImGuiWindowFlags_NoResize;
     
     float col[3]{options.MainBrushColour.r/255.f, options.MainBrushColour.g/255.f,options.MainBrushColour.b/255.f};
     ImGui::Begin("Drawing Tools",NULL, window_flags);
     
     if(SelectedTool == Tool::eBrush || SelectedTool == Tool::eSpray || SelectedTool == Tool::eErase )
     {
         if(ImGui::SliderInt("BrushSize", &options.BrushSize, 1, 500))
             UpdatePointers(options.BrushSize, true);
     }
     if(ImGui::ColorPicker3("Colour Pick", col))
     {
         options.MainBrushColour = sf::Color(col[0]* 255.f,col[1]* 255.f,col[2]* 255.f);
     }
     ImGui::SliderInt("Scale", &scale, 1, 4);
     grid.canvas.setScale(scale,scale);
     ImGui::Columns(3,nullptr,false);
     ImGui::SetColumnOffset(1, 100);
     {
         
         if(ImGui::ImageButton(brushIcon, sf::Vector2f(64,64)))
         {
             SelectedTool = Tool::eBrush;
             currentTool = std::make_unique<BrushToolType>();
         }
         ImGui::NextColumn();
         if(ImGui::ImageButton(fillIcon, sf::Vector2f(64,64)))
         {
             SelectedTool = Tool::eFill;
             currentTool = std::make_unique<FillToolType>();
         }
         ImGui::NextColumn();
         if(ImGui::ImageButton(pickerIcon, sf::Vector2f(64,64)))
         {
             SelectedTool = Tool::eColourPick;
             currentTool = std::make_unique<PickerToolType>();
         }
         ImGui::NextColumn();
         if(ImGui::ImageButton(sprayIcon, sf::Vector2f(64,64)))
         {
             SelectedTool = Tool::eSpray;
             currentTool = std::make_unique<SprayToolType>();
         }
         ImGui::NextColumn();
         if(ImGui::ImageButton(eraserIcon, sf::Vector2f(64,64)))
         {
             SelectedTool = Tool::eErase;
             currentTool = std::make_unique<EraserToolType>();
         }
         ImGui::NextColumn();
         if(ImGui::ImageButton(nullIcon, sf::Vector2f(64,64)))
         {
             SelectedTool = Tool::eNull;
             currentTool = std::make_unique<NullToolType>();
         }
         ImGui::NextColumn();
         if(ImGui::ImageButton(circleIcon, sf::Vector2f(64,64)))
             brushShape = BrushShape::eCircle;
         ImGui::NextColumn();
         if(ImGui::ImageButton(squareIcon, sf::Vector2f(64,64)))
             brushShape = BrushShape::eSquare;
     }
     
     ImGui::End();
     
}
void DrawingGrid::Layers()
{
    ImGui::Begin("Layers");
       
       ImGui::End();
}
void DrawingGrid::Textures()
{
    ImGui::Begin("Texture Picker");
     ImGui::Columns(3,nullptr,false);
    ImGui::SetColumnOffset(1, 100);
    {
        for(int i{0}; i<TrackTextures.size();i++)
        {
            if(ImGui::ImageButton(TrackTextures[i], sf::Vector2f(64,64)))
            {
                
            }
        }
    }
    ImGui::End();
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
        if(grid.PointOnCanvas(sf::Vector2f(MousePos),false))
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
        
        else
        {
            cursor.loadFromSystem(sf::Cursor::Arrow);
            window->SFwindow.setMouseCursor(cursor);
        }
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
void DrawingGrid::Serialise(Yaml::Node &root, sw::ProgressBar &bar, std::string filename)
{
    grid.SaveImage(filename);
    std::string Data =
    "GridSize: " + std::to_string(grid.TotalSize) + "\n"
    "TrackEdgeColour: " + std::to_string((uint32_t)TrackEdgeColour.toInteger()) + "\n"
    "BackgroundColour: " + std::to_string((uint32_t)grid.GridBackground.toInteger()) + "\n"
    "ImagePath: " + filename + "\n"
    "Optimise: " + std::to_string((int)Optimise) + "\n\n\n";
    bar.setPercentage(bar.getPercentage()+1);
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
