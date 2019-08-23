//
//  FPS.hpp
//  SFGameEngine
//
//  Created by Daniel Harvey on 09/06/2019.
//  Copyright © 2019 Daniel Harvey. All rights reserved.
//

#ifndef FPS_hpp
#define FPS_hpp

#include <SFML/Graphics.hpp>

class FPS
{
public:
	/// @brief Constructor with initialization.
	///
	FPS() : mFrame(0), mFps(0) {}
	
	/// @brief Update the frame count.
	///
	void update()
	{
		if(mClock.getElapsedTime().asSeconds() >= 1.f)
		{
			mFps = mFrame;
			mFrame = 0;
			mClock.restart();
		}
		
		++mFrame;
	}
	
	/// @brief Get the current FPS count.
	/// @return FPS count.
	const unsigned int getFPS() const { return mFps; }
	
private:
	unsigned int mFrame;
	unsigned int mFps;
	sf::Clock mClock;
};

#endif /* FPS_hpp */
