//
//  Track.hpp
//  BaseProject
//
//  Created by Daniel Harvey on 02/08/2019.
//  Copyright © 2019 Daniel Harvey. All rights reserved.
//

#ifndef Track_hpp
#define Track_hpp
#include "mySpline.hpp"
#include <SFML/Graphics.hpp>
#include "Window.hpp"
#include "SelbaWard.hpp"
#include "Yaml.hpp"
#include "SfMath.hpp"

struct node
{
    sf::RectangleShape dot;
	sw::Line Line;
    
    
    sf::Color cols[10] = {sf::Color::Blue,sf::Color::Green,sf::Color(230,55,89) ,sf::Color::Yellow,sf::Color::Magenta,sf::Color::Red,sf::Color(128,128,128),sf::Color::Cyan,sf::Color(255,192,203),sf::Color(255,165,0)};
    node()
    {
        
    }
    
    void setup(mySpline &Spline, sf::Vector2f position, bool Add = true)
    {
        dot.setSize(sf::Vector2f(15,15));
        dot.setFillColor(cols[0]);
        dot.setOutlineThickness(2);
        dot.setOutlineColor(cols[1]);
        dot.setPosition(position);
		Line.setColor(sf::Color::Yellow);
		Line.setThickness(4);
		if(Add)
			Spline.AddPoint(position);

    }
};

class Track
{
public:
    Track();
	~Track(){};
    
    void Start(int ScreenWidth, int ScreenHeight,bool loading = false,int NumNodes = -1,int s1 = -1, int s2 = -1, int s3 = -1 , int Start = -1, int End = -1, float Twidth = -1.f);
    void Input(sf::Vector2i MousePos); 
    void UpdateTrack();
    void Render(Window *window);
    
    void Onleave();
    void OnReEntry();
    void Clear(); 
    std::pair<mySpline*, mySpline*> getSplines();
	
	void Serialise(Yaml::Node &root);
    
    mySpline spline;
    
private:
	void AddNode(int pos);
	void RemoveNode(int pos);
	
    
    mySpline Rspline;
    mySpline Lspline;
    
    int num = 0;
    int numNodes = 10; 
    int selected = 0;
	
	bool TEMP = false; 
    bool IsShown; 
    bool shownodes = true;
    float trackwidth = 50.f;
	
	int Sectors[3] = {1,2,3};
	
	int StartLine{0}, FinishLine{0};
	
	
    
    std::vector<node> nodes;
    std::vector<node> Rnodes;
    std::vector<node> Lnodes;
    
    sf::Font font;
    sf::Text text;
};

#endif /* Track_hpp */

