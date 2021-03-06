//
//  Tool.hpp
//  GeneticRaceEditor
//
//  Created by Daniel Harvey on 25/08/2019.
//  Copyright © 2019 Daniel Harvey. All rights reserved.
//
#include <SFML/Graphics.hpp>
#include "Canvas.hpp"
#include "Window.hpp"
#ifndef Tool_hpp
#define Tool_hpp

struct PaintOptions
{
    int BrushSize = 10;
    sf::Color MainBrushColour = sf::Color::Red;    
    sf::CircleShape shape;
};
class ToolType
{
public:
    virtual void OnMouseDown(sf::Vector2i MousePos, Canvas& canvas,  PaintOptions &options) = 0;
    virtual void OnMouseUp(sf::Vector2i MousePos, Canvas& canvas,  PaintOptions &options) = 0;
    virtual void OnMouseMove(sf::Vector2i MousePos, Canvas& canvas,  PaintOptions &options) = 0;
    virtual void RenderPreview(Window &window){};
    virtual ~ToolType(){};
};

class BrushToolType : public ToolType
{
public:
    void OnMouseDown(sf::Vector2i MousePos, Canvas& canvas,  PaintOptions &options) override;
    void OnMouseUp(sf::Vector2i MousePos, Canvas& canvas,  PaintOptions &options) override;
    void OnMouseMove(sf::Vector2i MousePos, Canvas& canvas,  PaintOptions &options) override;
};

class FillToolType : public ToolType
{
public:
    void OnMouseDown(sf::Vector2i MousePos, Canvas& canvas,  PaintOptions &options) override;
    void OnMouseUp(sf::Vector2i MousePos, Canvas& canvas,  PaintOptions &options) override;
    void OnMouseMove(sf::Vector2i MousePos, Canvas& canvas,  PaintOptions &options) override;
};

class EraserToolType : public ToolType
{
public:
    void OnMouseDown(sf::Vector2i MousePos, Canvas& canvas,  PaintOptions &options) override;
    void OnMouseUp(sf::Vector2i MousePos, Canvas& canvas,  PaintOptions &options) override;
    void OnMouseMove(sf::Vector2i MousePos, Canvas& canvas,  PaintOptions &options) override;
};
class SprayToolType : public ToolType
{
public:
    void OnMouseDown(sf::Vector2i MousePos, Canvas& canvas,  PaintOptions &options) override;
    void OnMouseUp(sf::Vector2i MousePos, Canvas& canvas,  PaintOptions &options) override;
    void OnMouseMove(sf::Vector2i MousePos, Canvas& canvas,  PaintOptions &options) override;
};
class PickerToolType : public ToolType
{
public:
    void OnMouseDown(sf::Vector2i MousePos, Canvas& canvas,  PaintOptions &options) override;
    void OnMouseUp(sf::Vector2i MousePos, Canvas& canvas,  PaintOptions &options) override;
    void OnMouseMove(sf::Vector2i MousePos, Canvas& canvas,  PaintOptions &options) override;
};
class NullToolType : public ToolType
{
public:
    void OnMouseDown(sf::Vector2i MousePos, Canvas& canvas,  PaintOptions &options) override;
    void OnMouseUp(sf::Vector2i MousePos, Canvas& canvas,  PaintOptions &options) override;
    void OnMouseMove(sf::Vector2i MousePos, Canvas& canvas,  PaintOptions &options) override;
};

#endif /* Tool_hpp */

