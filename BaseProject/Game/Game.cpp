//
//  Game.cpp
//  BaseProject
//
//  Created by Daniel Harvey on 15/06/2019.
//  Copyright © 2019 Daniel Harvey. All rights reserved.
//

#include "Game.hpp"
#include <math.h>
#include <iostream>
#include "imgui_user.h"

Game::Game() : window{"Window"}, GameState(State::eNull)
{
	c.restart();
}

void Game::Start()
{
	Grid.Start(1500,900,400,0,2,2);
	
	track.Start(window.ScreenWidth(), window.ScreenHeight());
}

void Game::Update()
{
	int frame = 0;
	const float frameDuration = 20;
	const int maxTimePerFrame = 100;
	float accumulatedTime = 0;
	
	while (window.IsOpen())
	{
		//accumulatedTime += c.restart().asMilliseconds();
		if (accumulatedTime < maxTimePerFrame)
		{
			accumulatedTime = maxTimePerFrame;
		}
		window.Update();
		if(window.SFwindow.hasFocus())
		{
			Input();
		}
		//Ensure Fps doesnt change User experiance
		while (accumulatedTime >= frameDuration)
		{
			accumulatedTime -= frameDuration;
			
			EarlyUpdate();
			LateUpdate();
		}
		Render();
		frame++;
	}
}
void Game::Input()
{
	static std::array<char, 50> Trackname;
	
	ImGuiWindowFlags window_flags = 0;
	window_flags |= ImGuiWindowFlags_NoTitleBar;
	window_flags |= ImGuiWindowFlags_MenuBar;
	window_flags |= ImGuiWindowFlags_NoMove;
	//window_flags |= ImGuiWindowFlags_NoResize;
	ImGui::Begin("menu",NULL,window_flags);
	if(ImGui::InputTextWithHint("TrackName", "Input TrackName", Trackname.data(), Trackname.size()))
	{
		TrackName = Trackname.data();
		
	}
	if(ImGui::Button("Close"))
	{
		window.Close(); 
	}
	if(ImGui::Button("Track Edit") && GameState != State::eTrack)
	{
		GameState = State::eTrack;
		track.OnReEntry();
		Grid.Onleave();
	}
	if (ImGui::Button("Grid Edit") && GameState != State::eDraw)
	{
		GameState = State::eDraw;
		Grid.OnReEntry();
		track.Onleave();
	}
	if (ImGui::Button("none") && GameState != State::eNull)
	{
		GameState = State::eNull;
		Grid.Onleave();
		track.Onleave();
	}
	if(ImGui::Button("Save Track to Grid"))
	{
		Grid.saveTracktoGrid(&track);
	}
	//Loading and saving should be moved to Game
	if(ImGui::Button("Save"))
	{
		//Perhaps do saving a different thread and show a sw::loadingbar onscreen!
		//SerialiseTrack
		std::string HeaderString,TrackString,GridString;
		std::string Data = "";
		Data = "Version: " + std::to_string(Version) + "\nName: " + TrackName + "\nWidth : " + std::to_string(Grid.getGrid()->Width) + "\nHeight : " + std::to_string(Grid.getGrid()->Height) + "\n";
		
		try
		{
			Yaml::Parse(root, Data);
		}
		catch (const Yaml::Exception e)
		{
			std::cout << "Exception " << e.Type() << ": " << e.what() << std::endl;
			return;
		}
		Yaml::Serialize(root, HeaderString);
		track.Serialise(root);
		Yaml::Serialize(root, TrackString);
		Grid.Serialise(root);
		Yaml::Serialize(root, GridString);
		//std::string filename = TrackName+ ".yml";
		std::ofstream file;
		file.open(TrackName+".yml");
		file << HeaderString << "\n" << TrackString << "\n" << GridString;
		file.close(); 

	}
	//if(ImGui::Button("Load"))
	// grid.LoadFromFile("temp.xml");
	ImGui::End();
	if(GameState == State::eDraw)
		Grid.Input(window.GetMouse());
	else if(GameState == State::eTrack)
		track.Input(window.GetMouse());
}
void Game::EarlyUpdate()
{
	
}
void Game::LateUpdate()
{
	
}
void Game::Render()
{
	window.BeginDraw(sf::Color(40,40,40));	
	
	Grid.Render(&window);
	
	
	if(GameState == State::eTrack)
		track.Render(&window);
	
	window.EndDraw();
}


