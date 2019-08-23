//
//  Game.hpp
//  BaseProject
//
//  Created by Daniel Harvey on 15/06/2019.
//  Copyright © 2019 Daniel Harvey. All rights reserved.
//

#ifndef Game_hpp
#define Game_hpp
#include <SFML/Graphics.hpp>
#include "Window.hpp"
#include "DrawingGrid.hpp"
#include "Track.hpp"
#include "Yaml.hpp"

enum State
{
    eDraw,
    eTrack,
    eLoad,
    eSave,
    eNull
};

class Game
{
public:
    Game();
    ~Game(){};
    void Start();
    void Update();
    void EarlyUpdate();
    void LateUpdate();
    void Render();
    void Input();
    
private:
	const double Version = 0.45; 
	std::string TrackName = "NewTrack";
	
    State GameState;
	Yaml::Node root;
   
    Window window;
    sf::Clock c; 
    
    sf::Sprite sprite;
    sf::Texture texture;
    
    Track track;
    DrawingGrid Grid; 
    
    const sf::Time TimePerFrame = sf::seconds(1.f/60.f);
    sf::Time elapsedTime;
    sf::Time OverallPlayerLapTime;
    sf::Time mStatisticsUpdateTime;
    sf::Time TotalTime;
    sf::Time timeSinceLastUpdate;
};

#endif /* Game_hpp */
