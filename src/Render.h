#pragma once

#include <SDL.h>
#include <iostream>
#include <functional>

int ALG_RenderDrawCircle(SDL_Renderer* renderer, int x0, int y0, int radius, bool filled = false)
{
	// not my code
	int f = 1 - radius;
	int ddF_x = 0;
	int ddF_y = -2 * radius;
	int x = 0;
	int y = radius;

	if (filled)
	{
		SDL_RenderDrawLine(renderer,
			x0, y0 + radius,
			x0, y0 - radius);
		SDL_RenderDrawPoint(renderer, x0 + radius, y0);
		SDL_RenderDrawPoint(renderer, x0 - radius, y0);
	}
	else
	{
		SDL_RenderDrawPoint(renderer, x0, y0 + radius);
		SDL_RenderDrawPoint(renderer, x0, y0 - radius);
		SDL_RenderDrawPoint(renderer, x0 + radius, y0);
		SDL_RenderDrawPoint(renderer, x0 - radius, y0);
	}

	while (x < y)
	{
		if (f >= 0)
		{
			y--;
			ddF_y += 2;
			f += ddF_y;
		}
		x++;
		ddF_x += 2;
		f += ddF_x + 1;
		
		if (filled)
		{
			SDL_RenderDrawLine(renderer,
				x0 + x, y0 + y,
				x0 + x, y0 - y);
			if (x != 0) SDL_RenderDrawLine(renderer, 
				x0 - x, y0 + y,
				x0 - x, y0 - y);
			if (x != y)
			{
				SDL_RenderDrawLine(renderer,
					x0 + y, y0 + x,
					x0 + y, y0 - x);
				if (y != 0) SDL_RenderDrawLine(renderer,
					x0 - y, y0 + x,
					x0 - y, y0 - x);
			}
		}
		else
		{
			SDL_RenderDrawPoint(renderer, x0 + x, y0 + y);
			if (x != 0) SDL_RenderDrawPoint(renderer, x0 - x, y0 + y);
			if (y != 0) SDL_RenderDrawPoint(renderer, x0 + x, y0 - y);
			if (x != 0 || y != 0) SDL_RenderDrawPoint(renderer, x0 - x, y0 - y);
			if (x != y)
			{
				SDL_RenderDrawPoint(renderer, x0 + y, y0 + x);
				if (y != 0) SDL_RenderDrawPoint(renderer, x0 - y, y0 + x);
				if (x != 0) SDL_RenderDrawPoint(renderer, x0 + y, y0 - x);
				if (x != 0 || y != 0) SDL_RenderDrawPoint(renderer, x0 - y, y0 - x);
			}
		}
	}

	return 0;
}