//
//  mySpline.hpp
//  BaseProject
//
//  Created by Daniel Harvey on 26/07/2019.
//  Copyright © 2019 Daniel Harvey. All rights reserved.
//

#ifndef mySpline_hpp
#define mySpline_hpp

#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include "SfMath.hpp"
#include "Window.hpp"

struct Point
{
	float x,y;
};

struct mySpline
{
	std::vector<Point> points;
    float Length = 0.0f;
    bool Loop = true;
	
	void AddPoint(sf::Vector2f point)
	{
		points.push_back(Point{point.x,point.y});
	}
    
    sf::Vector2f GetSplinePoint(float t)
    {
        int p0,p1,p2,p3;
        if(!Loop)
        {
            p1 = (int)t+1;
            p2 = p1 + 1;
            p3 = p2 + 1;
            p0 = p1 - 1;
        }
        else
        {
            p1 = (int)t;
            p2 = (p1 + 1) % points.size();
            p3 = (p2 + 1) % points.size();
            p0 = p1 >= 1 ? p1 - 1 : (int)points.size() - 1;
        }
        t = t - (int)t;
        
        float tt = t * t;
        float ttt = tt * t;
        
        float q1 = -ttt + 2.0f*tt - t;
        float q2 = 3.0f*ttt - 5.0f*tt + 2.0f;
        float q3 = -3.0f*ttt + 4.0f*tt + t;
        float q4 = ttt - tt;
        
        float tx = 0.5f * (points[p0].x * q1 + points[p1].x * q2 + points[p2].x * q3 + points[p3].x * q4);
        float ty = 0.5f * (points[p0].y * q1 + points[p1].y * q2 + points[p2].y * q3 + points[p3].y * q4);
        
        return{ tx, ty };
    }
    sf::Vector2f GetSplineGradient(float t)
    {
        int p0, p1, p2, p3;
        if (!Loop)
        {
            p1 = (int)t + 1;
            p2 = p1 + 1;
            p3 = p2 + 1;
            p0 = p1 - 1;
        }
        else
        {
            p1 = (int)t;
            p2 = (p1 + 1) % points.size();
            p3 = (p2 + 1) % points.size();
            p0 = p1 >= 1 ? p1 - 1 : (int)points.size() - 1;
        }
        
        t = t - (int)t;
        
        float tt = t * t;
        //float ttt = tt * t;
        
        float q1 = -3.0f * tt + 4.0f*t - 1;
        float q2 = 9.0f*tt - 10.0f*t;
        float q3 = -9.0f*tt + 8.0f*t + 1.0f;
        float q4 = 3.0f*tt - 2.0f*t;
        
        float tx = 0.5f * (points[p0].x * q1 + points[p1].x * q2 + points[p2].x * q3 + points[p3].x * q4);
        float ty = 0.5f * (points[p0].y * q1 + points[p1].y * q2 + points[p2].y * q3 + points[p3].y * q4);
        
        return{ tx, ty };
    }
    float CalculateSegmentLength(int node)
    {
        float fLength = 0.0f;
        float fStepSize = 0.005;
        
        sf::Vector2f old_point, new_point;
        old_point = GetSplinePoint((float)node);
        
        for (float t = 0; t < 1.0f; t += fStepSize)
        {
            new_point = GetSplinePoint((float)node + t);
            fLength += sqrtf((new_point.x - old_point.x)*(new_point.x - old_point.x)
                             + (new_point.y - old_point.y)*(new_point.y - old_point.y));
            old_point = new_point;
        }
        
        return fLength;
    }
    
    float GetNormalisedOffset(float p)
    {
        // Which node is the base?
        int i = 0;
        while (p > sf::getLength(points[i]))
        {
            p -= sf::getLength(points[i]);
            i++;
        }
        
        // The fractional is the offset
        return (float)i + (p / sf::getLength(points[i]));
    }
    void UpdateSplineProperties()
    {
        // Use to cache local spline lengths and overall spline length
        Length = 0.0f;
        
        if (Loop)
        {
            // Each node has a succeeding length
            for (int i = 0; i < points.size(); i++)
            {
                Length +=  CalculateSegmentLength(i);
            }
        }
        else
        {
            for (int i = 1; i < points.size() - 2; i++)
            {
               Length +=  CalculateSegmentLength(i);
            }
        }
    }
    void DrawSelf(Window *window, sf::Color col = sf::Color::White)
    {
        sf::RectangleShape tri;
        tri.setFillColor(col);
        tri.setSize(sf::Vector2f(8,8));
        
        if(Loop)
        {
            for(float t{0}; t<(float)points.size();t+=0.005f)
            {
                auto pos = GetSplinePoint(t);
                tri.setPosition(pos);
                window->draw(tri);
            }
        }
        else
        {
            for(float t{0}; t<(float)points.size()-3;t+=0.005f)
            {
                auto pos = GetSplinePoint(t);
                tri.setPosition(pos);
                window->draw(tri);
            }
        }
    }
    std::vector<sf::Vector2f> getSplineLine()
    {
        std::vector<sf::Vector2f> splinePoints;
        if(Loop)
        {
            for(float t{0}; t<(float)points.size();t+=0.005f)
            {
                auto pos = GetSplinePoint(t);
                splinePoints.push_back(pos);
            }
        }
        else
        {
            for(float t{0}; t<(float)points.size()-3;t+=0.005f)
            {
                auto pos = GetSplinePoint(t);
                splinePoints.push_back(pos);
            }
        }
        return splinePoints;
    }

};



#endif /* mySpline_hpp */
