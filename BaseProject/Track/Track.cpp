//
//  Track.cpp
//  BaseProject
//
//  Created by Daniel Harvey on 02/08/2019.
//  Copyright © 2019 Daniel Harvey. All rights reserved.
//

#include "Track.hpp"


Track::Track()
{
}
void Track::Start(int ScreenWidth, int ScreenHeight,bool loading ,int NumNodes,int s1 , int s2, int s3, int Start, int End, float Twidth)
{
    if(loading)
    {
        numNodes = NumNodes;
        Sectors[0] = s1;
        Sectors[1] = s2;
        Sectors[2] = s3;
        StartLine = Start;
        FinishLine = End;
        trackwidth = Twidth; 
    }
    
    font.loadFromFile("Roboto-Black.ttf");
    text.setFillColor(sf::Color::Magenta);
    text.setCharacterSize(20);
    text.setFont(font);
    
    for (int i = 0; i < numNodes; i++)
    {
		node newnode;
        newnode.setup(spline,{((float)numNodes * 10.0f) * sinf((float)i / (float)numNodes * 3.14159f * 2.0f) + ScreenWidth / 2, ((float)numNodes * 10.0f) * cosf((float)i / (float)numNodes * 3.14159f * 2.0f) + ScreenHeight / 2 });
        
        node LNode;
        LNode.setup(Lspline, {0,0});
        node RNode;
        RNode.setup(Rspline, {0,0});
        
        
        
        nodes.push_back(newnode);
        Lnodes.push_back(LNode);
        Rnodes.push_back(RNode);
        
    }
	
    UpdateTrack();
}
void Track::StartFromData(int ScreenWidth, int ScreenHeight,std::vector<sf::Vector2f> datapoints,int s1, int s2 , int s3  , int Start , int End , float Twidth )
{
    Clear();
        numNodes = (int)datapoints.size();
        Sectors[0] = s1;
        Sectors[1] = s2;
        Sectors[2] = s3;
        StartLine = Start;
        FinishLine = End;
        trackwidth = Twidth;
    
    font.loadFromFile("Roboto-Black.ttf");
    text.setFillColor(sf::Color::Magenta);
    text.setCharacterSize(20);
    text.setFont(font);
    
    for (int i = 0; i < numNodes; i++)
       {
           node newnode;
           newnode.setup(spline,datapoints[i]);
           
           node LNode;
           LNode.setup(Lspline, {0,0});
           node RNode;
           RNode.setup(Rspline, {0,0});
           
           
           
           nodes.push_back(newnode);
           Lnodes.push_back(LNode);
           Rnodes.push_back(RNode);
           
       }
       
       UpdateTrack();
}
void Track::Clear()
{
    spline.points.clear();
    Rspline.points.clear();
    Lspline.points.clear();
}
void Track::AddNode(int pos)
{
	numNodes++;
	if(pos < numNodes)
	{
		node newNode;
		newNode.setup(spline, spline.GetSplinePoint(pos-0.5),false);
		
		node LNode;
		LNode.setup(Lspline, {0,0},false);
		node RNode;
		RNode.setup(Rspline, {0,0},false);
		
		
		
		nodes.insert( nodes.begin()+pos, newNode);
		Lnodes.insert( Lnodes.begin()+pos, newNode);
		Rnodes.insert( Rnodes.begin()+pos, newNode);
		
		spline.points.insert( spline.points.begin()+pos, {spline.GetSplinePoint(pos-0.5).x,spline.GetSplinePoint(pos-0.5).y});
		Lspline.points.insert( Lspline.points.begin()+pos, {0,0});
		Rspline.points.insert( Rspline.points.begin()+pos, {0,0});
		
		UpdateTrack();
	}
}
void Track::RemoveNode(int pos)
{
	if(pos < numNodes)
	{
		numNodes--;
		
		
		
		nodes.erase( nodes.begin()+pos);
		Lnodes.erase( Lnodes.begin()+pos);
		Rnodes.erase( Rnodes.begin()+pos);
		
			//gives a strange error
		spline.points.erase( spline.points.begin()+pos);
		Lspline.points.erase( Lspline.points.begin()+pos);
		Rspline.points.erase( Rspline.points.begin()+pos);
		
		UpdateTrack();
	}
}
void Track::Input(sf::Vector2i MousePos)
{
	 bool changed = false;

	ImGuiWindowFlags window_flags = 0;
//	window_flags |= ImGuiWindowFlags_MenuBar;
//	window_flags |= ImGuiWindowFlags_NoMove;
//  window_flags |= ImGuiWindowFlags_NoResize;
	
	ImGui::Begin("Track Tools",NULL, window_flags);

	if(ImGui::SliderFloat("TrackWidth", &trackwidth, 5.f, 500.f))
	{
		changed = true;
	}
    if (ImGui::Button("Set Start"))
    {
        StartLine = selected;
    }
    if (ImGui::Button("Add Node"))
    {
			AddNode(selected);
	       	changed = true;
    }
	if (ImGui::Button("Remove Node"))
	{
		RemoveNode(selected);
		changed = true;
	}
    if (ImGui::Button("ShowNodes"))
    {
		shownodes = !shownodes;
    }
    if(sf::Mouse::isButtonPressed(sf::Mouse::Right))
    {
        spline.points[selected].x = MousePos.x;
        spline.points[selected].y = MousePos.y;
        spline.UpdateSplineProperties();
        changed = true;
    }
	ImGui::End();
	if(shownodes)
	{
		for(int i{0}; i<nodes.size();i++)
		{
			auto rect = nodes[i].dot.getGlobalBounds();
			if(rect.contains(MousePos.x,MousePos.y))
			{
				if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					selected = i;
				}
				nodes[i].dot.setFillColor(sf::Color::Yellow);
			}
            else if (i == StartLine)
            {
                nodes[i].dot.setFillColor(sf::Color::White);
            }
			else if( i != selected)
			{
				nodes[i].dot.setFillColor(sf::Color::Blue);
			}
            else
            {
                nodes[i].dot.setFillColor(sf::Color::Red);
            }
		}
	}
    if(changed)
    {
        UpdateTrack();
    }
}
void Track::UpdateTrack()
{
    for(int i{0}; i<nodes.size();i++)
    {
        auto p1 = spline.GetSplinePoint(i);
        auto g1 = spline.GetSplineGradient(i);
        float glen = sqrt(g1.x*g1.x+g1.y*g1.y);
        
        Lspline.points[i].x = p1.x + trackwidth * (-g1.y / glen);
        Lspline.points[i].y = p1.y + trackwidth * ( g1.x / glen);
        Rspline.points[i].x = p1.x - trackwidth * (-g1.y / glen);
        Rspline.points[i].y = p1.y - trackwidth * (g1.x / glen);
        
        Lspline.UpdateSplineProperties();
        Rspline.UpdateSplineProperties();
		
		float r = atan2(-g1.y, g1.x);
		nodes[i].Line.setPoints({trackwidth * sin(r) + p1.x, trackwidth * cos(r) + p1.y}, {-trackwidth * sin(r) + p1.x, -trackwidth * cos(r) + p1.y});
    }
}
void Track::Onleave()
{
    IsShown = false;
    shownodes = false;
}
void Track::OnReEntry()
{
    IsShown = true;
    shownodes = true;
}
void Track::Render( Window *window)
{
    spline.Length = 0.0f;
    Rspline.Length = 0.0f;
    Lspline.Length = 0.0f;
    
    Lspline.DrawSelf(window);
    Rspline.DrawSelf(window);
	
    
    if(shownodes)
    {
        for(int i{0}; i<nodes.size();i++)
        {
            Rspline.Length += Rspline.CalculateSegmentLength(i);
            Lspline.Length += Lspline.CalculateSegmentLength(i);
            spline.Length +=  spline.CalculateSegmentLength(i);
            text.setPosition(nodes[i].dot.getPosition().x + 15,nodes[i].dot.getPosition().y + 15);
            text.setString(std::to_string(i));
            nodes[i].dot.setPosition(spline.points[i].x,spline.points[i].y);
            
            window->draw(nodes[i].Line);
            window->draw(nodes[i].dot);
            window->draw(text);
			

			
        }
    }
}

std::pair<mySpline*, mySpline*> Track::getSplines()
{
    return {&Lspline,&Rspline};
}

void Track::Serialise(Yaml::Node &root)
{
	std::string Data = "";
	
	Data += "IsLooped: " + std::to_string((int)spline.Loop) + "\nNumNodes: " + std::to_string(spline.points.size()) + "\nTrackWidth: " + std::to_string(trackwidth) + "\nSector1: " + std::to_string(Sectors[0]) + "\nSector2: " + std::to_string(Sectors[1]) + "\nSector3: " + std::to_string(Sectors[2]) + "\nStartLine: " + std::to_string(StartLine) + "\nFinishLine: " + std::to_string(FinishLine) + "\n";
	
	

	for(int node{0}; node < nodes.size(); node++)
	{
		Data += "Node" + std::to_string(node) + "_X:" + std::to_string(spline.GetSplinePoint(node).x) + "\nNode" + std::to_string(node) + "_Y: " + std::to_string(spline.GetSplinePoint(node).y) + "\n";

	}
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

