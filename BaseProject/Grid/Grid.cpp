//
//  Grid.cpp
//  BaseProject
//
//  Created by Daniel Harvey on 01/07/2019.
//  Copyright © 2019 Daniel Harvey. All rights reserved.
//

#include "Grid.hpp"
#include <iostream>
#include  <queue>

//Please note: because we now render to a sf::RenderTexture; it is no longer required to use grid position as an offset.
//When Rendering to a render texture, "screen position" is reset to 0,0, rather than the position of the RenderTexture in window space.
//This makes working things out a lot easier! as well as being more efficient! YAY smart

int roundDown(int n, int m)
{
    return n >= 0 ? (n/m)*m : ((n-m+1)/m)*m;
}

void Grid::SetupGrid(sf::Vector2f gridPos,int width, int height, int cellW, int cellH)
{
    for(int i{0}; i < myGrid.size(); i++)
    {
        myGrid[i].clear();
    }
    myGrid.clear(); 
    
    Width =  width;
    Height = height;
    CellW = cellW;
    CellH = cellH;
    GridPosition = gridPos;
    NumRow = (Height/CellH);
    NumCol = (Width/CellW);
    
    myGrid.clear();
    
    for(int y{0}; y< NumRow; y++)
    {
        std::vector<Cell> row;
        
        for(int x{0}; x< NumCol ; x++)
        {
            int left =  x * CellW;
            int top =  y * CellH;
            int right =  left + CellW;
            int base = top + CellH ;
            Cell c(left, top, right, base, CellW, CellH, TotalSize);
            c.SetColour(sf::Color::Black);
            row.push_back(c);
            TotalSize++;
            // std::cout<<"Cell #" << TotalSize << "\nX = " << left << " Y = " << top << "\nRow = " << y << " Column = " << x << "\n\n\n";
        }
        myGrid.push_back(row);
    }
    NumRow--;
    NumCol--;
	
	gridTexture.create(cellW, cellH);
	std::vector<sf::Uint8> pix;
	for(int x{0}; x < cellW*4; x++)
	{
		for(int y{0}; y < cellH; y++)
		{
			pix.push_back(255);
		}
	}
	gridTexture.update(pix.data());
	
    gridSprite.setTexture(gridTexture);
    
    rendertexture.create(Width, Height);
    MouseOnGrid = true;
    
}
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
sf::Vector2i Grid::ConverttoGrid(sf::Vector2f point, bool GridPos)
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
    return sf::Vector2i((int)point.x,(int)point.y);
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
    if(point.y < 0 )
        return false;
    if(point.x< 0)
        return false;
    if(point.y>NumRow)
        return false;
    if(point.x>NumCol)
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
            }
        }
    }
}

void Grid::SetCell(sf::Vector2f pos, sf::Color colour)
{
    int y = roundDown(pos.y - GridPosition.y, CellH) / CellH;
    int x = roundDown(pos.x - GridPosition.x, CellW) / CellW;
if(y < 0 )
	y=0;
	if(x< 0)
		x=0;
	if(y>NumRow)
		y=NumRow;
	if(x>NumCol)
		x=NumCol;
	
    myGrid[y][x].SetColour(colour);
    Changed = true;
}
void Grid::SetCell(int xGrid, int yGrid, sf::Color colour)
{
	
	if(yGrid < 0 )
		yGrid=0;
	if(xGrid< 0)
		xGrid=0;
	if(yGrid>NumRow)
		yGrid=NumRow;
	if(xGrid>NumCol)
		xGrid=NumCol;
	
    this->myGrid.at(yGrid).at(xGrid).SetColour(colour);
    Changed = true;
}

void Grid::Render(Window &window, bool isshown)
{
    //This function is very inefficient!
    //please optimise
    if(Changed )
    {
        rendertexture.clear();
        for(int y{0}; y< NumRow; y++)
        {
            for(int x{0}; x< NumCol ; x++)
            {
                int gridy = myGrid[y][x].Top;
                int gridx = myGrid[y][x].Left;
                
                //gridSprite.setTextureRect(myGrid[y][x].TextureRect);
                gridSprite.setPosition(gridx, gridy);
                gridSprite.setColor(myGrid[y][x].getColour());
                
                rendertexture.draw(gridSprite);
            }
        }
    }
    
    rendertexture.display();
    
    sf::Sprite sprite(rendertexture.getTexture());
    sprite.setPosition(GridPosition);
    window.SFwindow.draw(sprite);
    Changed = false;
}

bool Grid::isMouseOnGrid()
{
    return MouseOnGrid;
}
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
	/*
	 
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
	 */
}
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
