//
//  nano_engine.h
//
//  Created by william herrera
//  Copyright © 2019 william herrera. All rights reserved.
//

#ifndef nano_engine_h
#define nano_engine_h

#define SDL_MAIN_HANDLED

#include <stdio.h>
#include <SDL.h>

    #ifdef __cplusplus
    extern "C" { 
		// only need to export C interface if
        // used by C++ source code
    #endif

        struct Nano_Texture;        
        typedef struct Nano_Texture Nano_Texture;

		/* Cast to SDL_Event */
		typedef union Nano_Event
		{
			uint32_t type;
			uint8_t padding[56];
		} Nano_Event;
        
        /* Copy of SDL_Rect */
        typedef struct Nano_Rect
        {
            int x, y;
            int w, h;
        } Nano_Rect;
        
        /* initialized SDL subsystem */
        int Nano_Init(void);

		/* Poll Events */
		int Nano_PollEvent(Nano_Event *event);

		/* Is Event a Quit */
		int Nano_QuitEvent(Nano_Event *event);

		/* Key Down Event */
		int Nano_KeyDownEvent(Nano_Event *event, int *scancode);

		/* Sleep */
		void Nano_Sleep(unsigned int ms);
        
        /* initialize window and create render surface */
        int Nano_CreateRenderer(const char *title,
                                 int x, int y, int width,
                                 int height);
        
        /* load a bmp texture into memory */
        Nano_Texture* Nano_LoadTexture(const char *file_path);
        
        /* copy texture to current render target */
        void Nano_RenderCopy(Nano_Texture * texture,
                              const Nano_Rect * srcrect,
                              const Nano_Rect * dstrect);

        /* clear renderer with current color */
        void Nano_RenderClear(void);
        
        /* update screen */
        void Nano_RenderPresent(void);
        
        /* shutdown SDL subsystem */
        void Nano_Shutdown(void);
        
    #ifdef __cplusplus
    }
    #endif
#endif /* nano_engine_h */
