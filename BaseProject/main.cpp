//
//  main.cpp
//  BaseProject
//
//  Created by Daniel Harvey on 15/06/2019.
//  Copyright © 2019 Daniel Harvey. All rights reserved.
//


#include <vector>
#include <iostream>
#include "Game.hpp"
#include <stdlib.h>     /* srand, rand */
#include <time.h>


int main()
{
    srand ((unsigned int)time(NULL));
    Game g;
    g.Start();
    g.Update();
    return 0;	
}
