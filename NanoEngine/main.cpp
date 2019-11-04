//
//  main.cpp
//
//  Created by william herrera.
//  Copyright © 2019 william herrera. All rights reserved.
//

#include <iostream>
#include <string>

#include "nano_engine.h"

int main(int argc, char *argv[])
{    
    Nano_Init();
    
    Nano_CreateRenderer("window", 100, 100, 640, 480);
    
    Nano_Texture * tex = Nano_LoadTexture("Assets/blue_solid.bmp");
    
    bool isquit = false;

	Nano_Rect rect = { 0, 0, 49, 49 };

	Nano_Event event;
    while (!isquit)
	{
        if (Nano_PollEvent(&event))
		{
            if (Nano_QuitEvent(&event)) {
                isquit = true;
            }
			int scancode = 0;
			if (Nano_KeyDownEvent(&event, &scancode))
			{				
				switch (scancode) {
				case SDL_SCANCODE_RIGHT:
					rect.x += 1;
					break;
				case SDL_SCANCODE_LEFT:
					rect.x -= 1;
					break;
				case SDL_SCANCODE_UP:
					rect.y += 1;
					break;
				case SDL_SCANCODE_DOWN:
					rect.y -= 1;
					break;
				}
			}
        }
        
        Nano_RenderClear();
        
		Nano_RenderCopy(tex, NULL, &rect);

        Nano_RenderPresent();
    }
    
    return 0;
}
