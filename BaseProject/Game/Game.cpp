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
    font.loadFromFile("Roboto-Black.ttf");
    track.Start(window.ScreenWidth(), window.ScreenHeight());
    
    bar.setBackgroundColor(sf::Color(128,128,128));
    bar.setColor(sf::Color::White);
    bar.setPosition(0, window.ScreenHeight()-50);
    bar.setSize(sf::Vector2f(window.ScreenWidth(),50));
    savingtext.setFont(font);
    savingtext.setCharacterSize(30);
    savingtext.setPosition(window.GetCentre().x-30, window.ScreenHeight()-80);
    savingtext.setString("");
}

void Game::Update()
{
    int frame = 0;
    const float frameDuration = 20;
    const int maxTimePerFrame = 100;
    float accumulatedTime = 0;
    std::thread mythread(&Game::LoadSaveThread,this);
    
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
    mythread.join();
}
void Game::Input()
{
    if(GameState != eSave && GameState != eLoad)
    {
        ImGuiWindowFlags window_flags = 0;
        window_flags |= ImGuiWindowFlags_NoTitleBar;
        window_flags |= ImGuiWindowFlags_MenuBar;
        window_flags |= ImGuiWindowFlags_NoMove;
        //window_flags |= ImGuiWindowFlags_NoResize;
        ImGui::Begin("menu",NULL,window_flags);

        ImGui::InputTextWithHint("TrackName", "Input TrackName", &TrackName);
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
            GameState = eSave;
        }
        if(ImGui::Button("Load"))
        {
            GameState = eLoad;
        }
        ImGui::End();
        if(GameState == State::eDraw)
            Grid.Input(window.GetMouse());
        else if(GameState == State::eTrack)
            track.Input(window.GetMouse());
    }
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
    
    if(GameState == eSave || GameState == eLoad)
    {
        bar.setShowBar(true);
        window.draw(bar);
        window.draw(savingtext);
    }
    
    Grid.Render(&window);
    
    if(GameState == State::eTrack)
        track.Render(&window);
    
    
    window.EndDraw();
}
void Game::LoadSaveThread()
{
    while (true)
    {
        if(GameState == eSave)
        {
            Save();
        }
        else if (GameState == eLoad)
        {
            Load(TrackName+".yml");
        }
    }
}
void Game::Save()
{
    savingtext.setString("Saving... Writing File Header");
    bar.setPercentage(0.f);
    
    //SerialiseTrack
    std::string HeaderString,TrackString,CanvasString,Data{""};
    Data = "Version: " + std::to_string(Version) + "\nName: " + TrackName + "\nWidth : " + std::to_string(Grid.getCanvas()->Width) + "\nHeight : " + std::to_string(Grid.getCanvas()->Height) + "\n";
    
    try
    {
        Yaml::Parse(root, Data);
    }
    catch (const Yaml::Exception e)
    {
        std::cout << "Exception " << e.Type() << ": " << e.what() << std::endl;
        return;
    }
    bar.setPercentage(10.f);
    Yaml::Serialize(root, HeaderString);
    savingtext.setString("Saving... Getting Track Data");
    bar.setPercentage(20.f);
    track.Serialise(root);
    bar.setPercentage(30.f);
    savingtext.setString("Saving... Writing Track Data");
    Yaml::Serialize(root, TrackString);
    savingtext.setString("Saving... Getting Grid Data");
    bar.setPercentage(40.f);
    Grid.Serialise(root,bar,TrackName+".png");
    bar.setPercentage(50.f);
    savingtext.setString("Saving... Writing Grid Data");
    Yaml::Serialize(root, CanvasString);
    bar.setPercentage(60.f);
    savingtext.setString("Saving... Finished Writing Data");
    
    std::ofstream file;
    file.open(TrackName+".yml");
    bar.setPercentage(65.f);
    file << HeaderString;
    bar.setPercentage(70.f);
    file << "\n" << TrackString;
    bar.setPercentage(80.f);
    file << "\n" << CanvasString;;
    bar.setPercentage(90.f);
    file.close();
    bar.setPercentage(100.f);
    GameState = eNull;
    savingtext.setString("");
}

void Game::Load(std::string filename)
{
    if(GameState == eLoad)
        try
    {
        bar.setPercentage(0.f);
        savingtext.setString("Parsing File");
        Yaml::Parse(root, filename.data());
        bar.setPercentage(20.f);
        savingtext.setString("Finished Parsing File");
    }
    catch (const Yaml::Exception e)
    {
        std::cout << "Exception " << e.Type() << ": " << e.what() << std::endl;
        GameState = eNull;
        return;
    }
    savingtext.setString("Loading Basic Data");
    int height,width;
    std::string filepath;
    u_int32_t BackgroundColour;    
    TrackName = root["Name"].As<std::string>();
    bar.setPercentage(bar.getPercentage()+1);
    height = root["Height"].As<int>();
    bar.setPercentage(bar.getPercentage()+1);
    width = root["Width"].As<int>();
    bar.setPercentage(bar.getPercentage()+1);
    filepath = root["ImagePath"].As<std::string>();
    bar.setPercentage(bar.getPercentage()+1);
    BackgroundColour = root["Background Colour"].As<u_int32_t>();
    bar.setPercentage(bar.getPercentage()+1);
    savingtext.setString("Setting Up Grid");
    Grid.Start(400,0, filepath);

    savingtext.setString("Loading Track");
    int numnodes{root["NumNodes"].As<int>()},Sector1{root["Sector1"].As<int>()},Sector2{root["Sector2"].As<int>()},Sector3{root["Sector3"].As<int>()},Start{root["StartLine"].As<int>()},Finish{root["FinishLine"].As<int>()};
    float TrackWidth{root["TrackWidth"].As<float>()};
        
    float Tx,Ty;
    std::string name;
    std::vector<sf::Vector2f> points;
    for(int i{0};i<numnodes;i++)
    {
        name = "Node" + std::to_string(i);
        savingtext.setString("Setting Track" + name);
        Tx = root[name + "_X"].As<int>();
        Ty = root[name + "_Y"].As<int>();
       points.push_back(sf::Vector2f(Tx,Ty));
    }
    track.StartFromData(window.ScreenWidth(), window.ScreenHeight(), points, Sector1,Sector2,Sector3,Start,Finish,TrackWidth);
    savingtext.setString("Finished");
    GameState = eNull;
    savingtext.setString("");
}
