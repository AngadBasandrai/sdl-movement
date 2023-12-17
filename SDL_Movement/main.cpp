#define SDL_MAIN_HANDLED


#include <SDL.h>
#include <stdio.h>
#include <cstdlib>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;


bool init();
bool loadMedia();
void clear();
bool checkCollision(SDL_Rect* obj1, SDL_Rect* obj2);

//The window object
SDL_Window* window = NULL;

//The surface of window
SDL_Surface* screenSurface = NULL;

//The image
SDL_Surface* rBoid = NULL;
//The wall
SDL_Surface* w1 = NULL;
//The conveyor
SDL_Surface* c1 = NULL;

int main(int argc, char* args[])
{
	bool quit = false;

	int prevMoveX = 0;
	int prevMoveY = 0;

	//Event Handler

	SDL_Event eh;

	if (!init())
	{
		return 0;
	}
	if (!loadMedia())
	{
		return 0;
	}

	//Define an array to hold all rectangles
	SDL_Rect* rects[101];
	int effects[101];

	SDL_Rect emptyR;

	for (int i = 0; i < 101; i++)
	{
		rects[i] = &emptyR;
		effects[i] = 0;
	}

	double triRectX = 0, triRectY = 56;

	// A Rectangle
	SDL_Rect triRectP;
	triRectP.x = (int)triRectX;
	triRectP.y = (int)triRectY;
	triRectP.w = 16;
	triRectP.h = 16;
	rects[0] = &triRectP;


#pragma region Wall

	// Define a wall
	SDL_Rect wall;
	wall.x = (int)250;
	wall.y = (int)56;
	wall.w = 16;
	wall.h = 16;

	// Add pointer of wall's rect to rects array
	rects[1] = &wall;
	effects[1] = 1;

#pragma endregion

#pragma region Wall

	// Define a wall
	SDL_Rect wall2;
	wall2.x = (int)234;
	wall2.y = (int)56;
	wall2.w = 16;
	wall2.h = 16;

	// Add pointer of wall's rect to rects array
	rects[2] = &wall2;
	effects[2] = 1;

#pragma endregion

#pragma region Wall

	// Define a wall
	SDL_Rect wall3;
	wall3.x = (int)266;
	wall3.y = (int)56;
	wall3.w = 16;
	wall3.h = 16;

	// Add pointer of wall's rect to rects array
	rects[3] = &wall3;
	effects[3] = 0;

#pragma endregion



	while (!quit)
	{

		//Handle events on queue
		while (SDL_PollEvent(&eh) != 0)
		{
			prevMoveX = 0;
			prevMoveY = 0;
			//User requests quit
			if (eh.type == SDL_QUIT)
			{
				quit = true;
			}

			//User presses some arrow

			if (eh.key.keysym.sym == SDLK_RIGHT)
			{
				//Move forward
				triRectP.x += 3;
				prevMoveX += 3;
				//Iterate all elements in objects
				for (int i = 0; i < 101; i++)
				{
					SDL_Rect* obj = rects[i];
					if (i != 0 && obj->w != 0) {
						//Check Collision
						if (checkCollision(obj, &triRectP))
						{
							if (effects[i] == 0) {
								//Move back
								triRectP.x -= 3;
								prevMoveX -= 3;
								break;
							}
							else if (effects[i] == 1) {
								triRectP.x += obj->w * 2;
								prevMoveX += obj->w * 2;
							}
						}
					}
				}
			}
			if (eh.key.keysym.sym == SDLK_LEFT)
			{
				//Move forward
				triRectP.x -= 3;
				prevMoveX -= 3;
				//Iterate all elements in objects
				for (int i = 0; i < 101; i++)
				{
					SDL_Rect* obj = rects[i];
					if (i != 0 && obj->w != 0) {
						//Check Collision
						if (checkCollision(obj, &triRectP))
						{
							if (effects[i] == 0) {
								//Move back
								triRectP.x += 3;
								prevMoveX += 3;
								break;
							}
							else if (effects[i] == 1) {
								triRectP.x -= obj->w * 2;
								prevMoveX -= obj->w * 2;
							}
						}
					}
				}
			}
			if (eh.key.keysym.sym == SDLK_UP)
			{
				//Move forward
				triRectP.y -= 3;
				prevMoveY -= 3;
				//Iterate all elements in objects
				for (int i = 0; i < 101; i++)
				{
					SDL_Rect* obj = rects[i];
					if (i != 0 && obj->w != 0) {
						//Check Collision
						if (checkCollision(obj, &triRectP))
						{
							if (effects[i] == 0) {
								//Move back
								triRectP.y += 3;
								prevMoveY += 3;
								break;
							}
							else if (effects[i] == 1) {
								triRectP.y -= obj->h * 2;
								prevMoveY -= obj->h * 2;
							}
						}
					}
				}
			}
			if (eh.key.keysym.sym == SDLK_DOWN)
			{
				//Move forward
				triRectP.y += 3;
				prevMoveY += 3;
				//Iterate all elements in objects
				for (int i = 0; i < 101; i++)
				{
					SDL_Rect* obj = rects[i];
					if (i != 0 && obj->w != 0) {
						//Check Collision
						if (checkCollision(obj, &triRectP))
						{
							if (effects[i] == 0) {
								//Move back
								triRectP.y -= 3;
								prevMoveY -= 3;
								break;
							}
							else if (effects[i] == 1) {
								triRectP.y += obj->h * 2;
								prevMoveY += obj->h * 2;
							}
						}
					}
				}
			}
		}

		//Fill the surface white
		//args = [surface, rect to fill {NULL means full surface}, color {args = [format, r, g, b]}]
		SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));

		//Apply the image
		//args = [image, imageCrop, screen, imagePos]
		SDL_BlitSurface(rBoid, NULL, screenSurface, &triRectP);
		//SDL_BlitSurface(c1, NULL, screenSurface, &wall);
		SDL_BlitSurface(c1, NULL, screenSurface, &wall);
		SDL_BlitSurface(c1, NULL, screenSurface, &wall2);
		SDL_BlitSurface(w1, NULL, screenSurface, &wall3);

		//Update the surface
		//args = [the window whose surface has to be updated]
		SDL_UpdateWindowSurface(window);
	}

	clear();

	return 0;
}

/// <summary>
/// Tries to initialize SDL
/// </summary>
/// <returns>true when SDL was initialized and false otherwise</returns>
bool init()
{
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Create window
		//args = [window caption, x pos of win, y pos of win, width, height, creation flags{SDL_WINDOW_SHOWN means the window is shown when created}]
		window = SDL_CreateWindow("Basic Physics", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Get window surface
			screenSurface = SDL_GetWindowSurface(window);
		}
	}

	return success;
}

/// <summary>
/// Loads media
/// </summary>
/// <returns>true if media was loaded and false otherwise</returns>
bool loadMedia()
{
	bool success = true;

	//Load an image
	//args = [img to load]
	rBoid = SDL_LoadBMP("resources/boid.bmp");
	w1 = SDL_LoadBMP("resources/boid.bmp");
	c1 = SDL_LoadBMP("resources/boid.bmp");

	if (rBoid == NULL || w1 == NULL || c1 == NULL)
	{
		printf("Unable to load media! SDL Error: %s\n", SDL_GetError());
		success = false;
	}

	SDL_FillRect(rBoid, NULL, SDL_MapRGB(rBoid->format, 0xFF, 0x00, 0x00));
	SDL_FillRect(w1, NULL, SDL_MapRGB(w1->format, 0x00, 0x00, 0xFF));
	SDL_FillRect(c1, NULL, SDL_MapRGB(c1->format, 0x00, 0xFF, 0x00));

	return success;
}

/// <summary>
/// Clears SDL objects from memory and shuts SDL subsystems down
/// </summary>
void clear()
{
	//Deallocate surface
	SDL_FreeSurface(rBoid);
	rBoid = NULL;

	//Destroy window
	SDL_DestroyWindow(window);
	window = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}

/// <summary>
/// Check for collision between 2 SDL_Rects
/// </summary>
/// <param name="obj1">Object 1</param>
/// <param name="obj2">Object 2</param>
/// <returns></returns>
bool checkCollision(SDL_Rect* obj1, SDL_Rect* obj2) {
	// Check if mod of difference of x coordinates is less than equal to average of widths of both objects and similarly
	// with y coordinates and heights, if both are less than equal to than collision is true
	if (abs(obj1->x - obj2->x) <= (obj1->w + obj2->w) / 2 && abs(obj1->y - obj2->y) <= (obj1->h + obj2->h) / 2) return true;
	return false;
}