//
//  Window.cpp
//  SFGameEngine
//
//  Created by Daniel Harvey on 27/05/2019.
//  Copyright © 2019 Daniel Harvey. All rights reserved.
//

#include "Window.hpp"
#include <iostream>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>


Window::Window(const std::string& windowName): SFwindow{sf::VideoMode(1920, 1080), windowName, sf::Style::Default}
{  
    SFwindow.setFramerateLimit(60);
	rendertexture.create(SFwindow.getSize().x,SFwindow.getSize().y);
	ImGui::SFML::Init(SFwindow);
    CalculateDT();
}

void Window::Update()
{
	fps.update();
    ImGui::SFML::Update(SFwindow, sf::seconds(deltatime));
    sf::Event event;
    if (SFwindow.pollEvent(event))
    {
		 ImGui::SFML::ProcessEvent(event);
        if (event.type == sf::Event::Closed)
        {
            SFwindow.close();
        }
    }
	SetTitle(std::to_string(fps.getFPS()));
}

void Window::BeginDraw(sf::Color colour)
{
    SFwindow.clear(colour);
    if(RenderToTexture)
        rendertexture.clear(colour);
}
float Window::ScreenHeight()
{
    return SFwindow.getSize().y;
}
float Window::ScreenWidth()
{
    return SFwindow.getSize().x;
}
void Window::draw(const sf::Drawable& drawable)
{
    if(RenderToTexture)
        rendertexture.draw(drawable);
    else
        SFwindow.draw(drawable);
}

void Window::EndDraw()
{
    ImGui::EndFrame();
	if(RenderToTexture)
    {
		Process();    
        rendertexture.display();
    }

    ImGui::SFML::Render(SFwindow);
	 SFwindow.display();
    CalculateDT();
    
}
void Window::CalculateDT()
{
    deltatime = clock.restart().asSeconds();
}
void Window::Close()
{
	SFwindow.close();
}
bool Window::IsOpen() const
{
    return SFwindow.isOpen();
}
sf::Vector2u Window::GetCentre()
{
	unsigned int x = SFwindow.getSize().x/2;
	unsigned int y = SFwindow.getSize().y/2;
	
	return sf::Vector2u(x,y);
}
sf::Vector2i Window::GetMouse()
{
    return sf::Mouse::getPosition(SFwindow);
}
void Window::Process()
{
	windowtexture.setTexture(rendertexture.getTexture());
	
	windowtexture.setOrigin(windowtexture.getTextureRect().width/2, windowtexture.getTextureRect().height/2);
	
	windowtexture.setPosition(sf::Vector2f(GetCentre()));
	
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
	{
		//windowtexture.setColor(sf::Color(128,128,128));
		windowtexture.scale(1.01, 1.01);
	}

	
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift))
	{
		//windowtexture.setColor(sf::Color::Blue);
		windowtexture.scale(0.99, 0.99);
	}

	sf::Texture texture = *windowtexture.getTexture();
	
	//texture.setRepeated(true);
	//texture.setSmooth(true);
	windowtexture.setTexture(texture);
	
	SFwindow.draw(windowtexture);
}
void Window::SetTitle(std::string title)
{
	SFwindow.setTitle(title);
}
float Window::getDT()
{
    return deltatime; 
}


/*
 image = texture.copyToImage();
 std::vector<sf::Uint8> pixels;
 for(int y  = 0; y<600;y++)
 {
 for(int x  = 0; x<800;x++)
 {
 pixels.push_back(sf::Color(image.getPixel(x,y)).r);
 pixels.push_back(sf::Color(image.getPixel(x,y)).g);
 pixels.push_back(sf::Color(image.getPixel(x,y)).b);
 pixels.push_back(sf::Color(image.getPixel(x,y)).a);
 }
 }
 
 image.create(800, 600, pixels.data());
 texture.loadFromImage(image);
 */
