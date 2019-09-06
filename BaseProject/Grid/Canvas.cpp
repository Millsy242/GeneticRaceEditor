//
//  Grid.cpp
//  BaseProject
//
//  Created by Daniel Harvey on 01/07/2019.
//  Copyright © 2019 Daniel Harvey. All rights reserved.
//

#include "Canvas.hpp"
#include <iostream>

void Canvas::SetupCanvas(sf::Vector2f gridPos,int width, int height)
{
    Width =  width;
    Height = height;
    GridPosition = gridPos;
    
    renderimage.create(width, height,sf::Color::Green);
    canvasTexture.create(width, height);
    canvasTexture.loadFromImage(renderimage);
    canvasShape.setTexture(&canvasTexture);
    canvasShape.setPosition(GridPosition);
    canvasShape.setSize(sf::Vector2f(width,height));
}
void Canvas::SetupCanvas(sf::Vector2f gridPos, std::string ImagePath)
{

    GridPosition = gridPos;
    
    renderimage.loadFromFile(ImagePath);
    
    Width =  renderimage.getSize().x;
    Height = renderimage.getSize().y;
    
    canvasTexture.create(Width, Height);
    canvasTexture.loadFromImage(renderimage);
    
    canvasShape.setTexture(&canvasTexture);
    canvasShape.setPosition(GridPosition);
    canvasShape.setSize(sf::Vector2f(Width, Height));
}
void Canvas::SetPixel(sf::Vector2f pos, sf::Color colour)
{
    pos-=GridPosition;
    if(PointOnCanvas(pos))
        renderimage.setPixel(pos.x, pos.y, colour);
}
sf::Color Canvas::GetPixel(sf::Vector2f pos)
{
    pos-=GridPosition;
    if(PointOnCanvas(pos))
        return renderimage.getPixel(pos.x, pos.y);
    
    
    return sf::Color::Transparent;
}
bool Canvas::PointOnCanvas(sf::Vector2f pos,bool adjustme)
{
    if(adjustme)
        pos+=GridPosition;
    if(canvasShape.getGlobalBounds().contains(pos))
        return true;
    else
        return false;
}
void Canvas::Render(Window &window, bool isshown)
{
    
    canvasTexture.loadFromImage(renderimage);
    canvasShape.setTexture(&canvasTexture);
    
    window.draw(canvasShape);
}
void Canvas::SaveImage(std::string filename)
{
    renderimage.saveToFile(filename);
}
/*

void Grid::SetupGrid(sf::Vector2f gridPos, std::string ImagePath, int cellW, int cellH)
{
    sf::Image tempImage;
    tempImage.loadFromFile(ImagePath);
    
    SetupGrid(gridPos, tempImage, cellW, cellH);
}
void Grid::SetupGrid(sf::Vector2f gridPos, sf::Image Image, int cellW, int cellH)
{
    SetupGrid(gridPos, Image.getSize().x * cellW, Image.getSize().y * cellH, cellW, cellH);
    LoadFromImage(Image);
}
bool Grid::CheckMouseInCell(int x, int y, sf::Vector2f mouse, int radius)
{
    return myGrid[y][x].MouseInCell(mouse,radius);
}
bool Grid::PointOnGrid(sf::Vector2f point, bool GridPos)
{
    if(!GridPos)
    {
        point.y = roundDown(point.y - GridPosition.y, CellH) / CellH;
        point.x = roundDown(point.x - GridPosition.x, CellW) / CellW;
    }
    else
    {
        point.y = roundDown(point.y, CellH) / CellH;
        point.x = roundDown(point.x, CellW) / CellW;
    }
    if(point.y < 0 || point.y > NumRow)
        return false;
    if(point.x < 0 || point.x > NumCol)
        return false;

    
    return true;
}

void Grid::SetBackgroundColour(sf::Color NewColour)
{
    Changed = true;
    GridBackground = NewColour;
    for(int y{0}; y< NumRow; y++)
    {
        for(int x{0}; x< NumCol ; x++)
        {
            if(myGrid[y][x].backgroundColour)
            {
                myGrid[y][x].SetColour(GridBackground);
                updatethesecells.push_back({x,y});
            }
        }
    }
}
 */



/*
 
bool Grid::LoadFromImage(sf::Image image)
{
    Changed = true;
    std::cout<<"Warning Loading from image like this might not use the whole image\nPlease recreate grid if this effect is not desired\n";
    for(int y{0}; y< NumRow; y++)
    {
        for(int x{0}; x< NumCol ; x++)
        {
            if(y<=image.getSize().y && x<= image.getSize().x )
            {
                if(image.getPixel(x, y) != sf::Color::Transparent)
                {
                    myGrid[y][x].SetColour(image.getPixel(x, y),false);
                }
                else
                {
                    myGrid[y][x].SetColour(GridBackground,true);
                }
            }
        }
    }
    
    return true;
}

void Grid::SaveToFile(std::string &data, sw::ProgressBar &bar)
{
    float currentbar = bar.getPercentage();
    float numcomplete = 0;
	for(int y = 0; y<NumRow; y++)
	{
		for(int x = 0 ; x< NumCol ; x++)
		{
            auto cellnum = std::to_string(myGrid[y][x].CellNumber);
			data += "Cell" + cellnum + "X:" + std::to_string(x) + "\nCell" + cellnum + "Y:" + std::to_string(y) + "\nCell" + cellnum + "C:" + std::to_string((uint32_t)myGrid[y][x].getColour().toInteger()) + "\nCell"+ cellnum + "T:";
			
				switch (myGrid[y][x].celltype)
				{
					case CellType::eNull:
						data += "eNull\n";
						break;
					case CellType::eEdge:
						data +=  "eEdge\n";
						break;
					case CellType::eTrack:
						data +=  "eTrack\n";
						break;
					case CellType::eGrass:
						data += "eGrass\n";
						break;
					default:
						data +=  "eNull\n";
						break;
				}
            numcomplete++;
            bar.setPercentage(currentbar + ((numcomplete/TotalSize)*10));
		}
	}
}

bool Grid::LoadFromImage(std::string ImageFilepath)
{
    sf::Image image;
    if(image.loadFromFile(ImageFilepath))
        return LoadFromImage(image);
    else
        return false;
}
 
void Grid::LoadFromFile(std::string FileName)
{

	 
    Changed = true;
    std::string line;
    std::ifstream myfile (FileName);
    if (myfile.is_open())
    {
        int Cwid{-1},Chei{-1};
        while ( getline (myfile,line) )
        {
            if(line.front() == 'C')
            {
                
                line = line.substr(3);
                
                Cwid = std::stoi(line.substr(0,line.find_first_of(":")));
                Chei = std::stoi(line.substr(line.find_last_of(":")+1));
                SetupGrid(GridPosition, Width, Height, Cwid, Chei);
            }
            else
            {
                
                int x{-1}, y{-1};
                sf::Color colour = sf::Color::Magenta;
                
                line = line.substr(2);
                x = std::stoi(line.substr(0,line.find_first_of(":")));
                line = line.substr(line.find_first_of(":")+3);
                
                y = std::stoi(line.substr(0,line.find_first_of(":")));
                line = line.substr(line.find_first_of(":")+3);
                
                colour = sf::Color(sf::Int32(std::stol(line.substr(0,line.find_first_of(":")))));
                
                int posX = x * Cwid;
                int posY = y * Chei;
                
                //Setup Cell + remember to add cellwidth and height to save file!
                //
                Cell cell(posX, posY, posX+Cwid, posY+Chei, Cwid, Chei);
                cell.SetColour(colour);
                myGrid[y][x] = cell;
            }
            
            
            
            
        }
        myfile.close();
    }
 
}
 */
//|| (brushshape == BrushShape::eSquare &&      myGrid[y][x].MouseInCell(Mouse,sf::FloatRect(shape->getGlobalBounds().left - GridPosition.x,shape->getGlobalBounds().top- GridPosition.y,(shape->getGlobalBounds().left + ShapeWidth) - GridPosition.x,(shape->getGlobalBounds().top + ShapeHeight)- GridPosition.y)))


//Recursive floodfill
/*
 if(yIndex < 0 )
 yIndex=0;
 if(xIndex< 0)
 xIndex=0;
 if(yIndex>NumRow)
 yIndex=NumRow-1;
 if(xIndex>NumCol)
 xIndex=NumCol-1;
 
 if(xIndex < NumCol  && yIndex < NumRow && xIndex > 0 && yIndex > 0)
 {
 
 if( ReplaceColour != TargetColour)
 {
 if(myGrid.at(yIndex).at(xIndex).getColour() == TargetColour)
 {
 this->SetCell(xIndex, yIndex, ReplaceColour);
 this->Fill(xIndex +1, yIndex);
 this->Fill(xIndex, yIndex+1);
 this->Fill(xIndex -1, yIndex);
 this->Fill(xIndex, yIndex-1);
 }
 }
 
 }
 return false;
 */

/*
 int numThreads = 1;
 std::vector<std::thread> threads;
 threads.resize(numThreads);
 
 
 std::vector<std::pair<int, int>> pairs;
 
 for(int p{0}; p<numThreads;p++)
 {
 if(p == 0)
 {
 pairs.push_back(std::pair<int, int> (p,NumCol*(p+1/numThreads)) );
 pairs.push_back(std::pair<int, int> (p,NumRow*(p+1/numThreads)));
 
 }
 else
 {
 pairs.push_back(std::pair<int, int> (NumCol*(p/numThreads),NumCol*(p+1/numThreads)));
 pairs.push_back(std::pair<int, int> (NumRow*(p/numThreads),NumRow*(p+1/numThreads)) );
 }
 }
 int pairnum = 0;
 for(int i{0}; i<numThreads; i++)
 {
 //google: storing thread in vector
 // threads[i] = std::thread(&Grid::SaveXML,this,FileName+std::to_string(i), pairs[pairnum],pairs[pairnum+1]);
 pairnum+=2;
 
 }
 
 for(int i{0}; i<numThreads; i++)
 {
 //threads[i].join();
 }
 SaveXML(FileName, pairs[0], pairs[1]);
 */
