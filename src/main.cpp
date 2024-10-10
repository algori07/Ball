#include <SDL.h>


#include <iostream>
#include "Render.h"
#include "Vector.h"
#include "Ball.h"
#include "Core.h"

#include <vector>


const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

const double MGRAVITY = 9.80665; // m/s
const double PIXELS_PER_METER = 4; // pixel/m

const int MSCREEN_WIDTH = SCREEN_WIDTH / PIXELS_PER_METER;
const int MSCREEN_HEIGHT = SCREEN_HEIGHT / PIXELS_PER_METER;

const int FPS = 29;
const int TICKS_PER_FRAME = 1000 / FPS;

const double PGRAVITY = MGRAVITY * PIXELS_PER_METER; // pixel/s

#define ALG_RenderDrawBall(renderer,ball) \
	SDL_SetRenderDrawColor(renderer,ball.colorR,ball.colorG,ball.colorB,255); \
	ALG_RenderDrawCircle(renderer, \
		ball.pos.at(0) * PIXELS_PER_METER, \
		ball.pos.at(1) * PIXELS_PER_METER, \
		ball.radius * PIXELS_PER_METER, true)

void collisionHandle(Ball& ballA, Ball& ballB);

int main(int argc,char **argv)
{
	if (0 != SDL_Init(SDL_INIT_VIDEO)) return -1;
	

	SDL_Window* window;
	if (NULL == (window = SDL_CreateWindow("Ball", 
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN))) return -3;

	SDL_Renderer* renderer;
	if (NULL == (renderer = SDL_CreateRenderer(window, -1,
		SDL_RENDERER_SOFTWARE))) return -4;
	// in my computer, using SDL_RENDERER_SOFTWARE is faster than SDL_RENDERER_ACCELERATED
	
	int fpscount = 0;
	int fpstick = SDL_GetTicks64();


	srand(time(0));

	std::vector<Ball> balls;
	//balls.push_back(Ball(0.5, { 5,5.0000001 }, { 0,0 }, { 0,MGRAVITY }));
	//balls.push_back(Ball(1,   { 5,5 }, { 0,0 }, { 0,MGRAVITY }));


	int timetick = SDL_GetTicks64();

	

	SDL_Event event;
	bool quit=false;

	int gentick = SDL_GetTicks64();
	bool isgen = false;


	while (!quit)
	{
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				quit = true;
				break;
			case SDL_MOUSEBUTTONDOWN:
				
				isgen = true;
				break;
			case SDL_MOUSEBUTTONUP:
				isgen = false;
				break;
			}
		}

		if (isgen)
		{
			if (SDL_GetTicks64() - gentick > 150)
			{
				gentick = SDL_GetTicks64();
				int tx, ty;
				SDL_GetMouseState(&tx, &ty);
				double x = tx / PIXELS_PER_METER;
				double y = ty / PIXELS_PER_METER;
				balls.push_back(Ball(randint(60, 100) / (double)100, { x,y }, { randint(-5,5),randint(-8,-5) }, { 0,MGRAVITY }, randint(64, 255), randint(64, 255), randint(64, 255)));
			}
		}

		
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);



		double time = (SDL_GetTicks64() - timetick) / double(1000);
		// double time=0/double(1000);
		timetick = SDL_GetTicks64();

		for (Ball &ball : balls)
		{
			{// check invalid position
				if (ball.pos.at(0) - ball.radius < 0) ball.pos.at(0) = ball.radius;
				if (ball.pos.at(1) - ball.radius < 0) ball.pos.at(1) = ball.radius;
				if (ball.pos.at(0) + ball.radius > MSCREEN_WIDTH) ball.pos.at(0) = MSCREEN_WIDTH - ball.radius;
				if (ball.pos.at(1) + ball.radius > MSCREEN_HEIGHT) ball.pos.at(1) = MSCREEN_HEIGHT - ball.radius;
			}
			ALG_RenderDrawBall(renderer, ball);

			{// check if the ball is bounching to edge of screen
				// x = x0 + v0*t + 1/2*a*t^2
				Vector newpos = ball.pos + ball.vel * time + ball.acc * time * time / 2;
				// v = v0 + a*t
				Vector newvel = ball.vel + ball.acc * time;


				if (newpos.at(0) - ball.radius < 0)
				{
					std::pair<double, double> ans = findXInQuadraticEquation(ball.acc.at(0) / 2, ball.vel.at(0), ball.pos.at(0) - ball.radius);
					double time2 = ans.first;

					// x = x0 + v0*t + 1/2*a*t^2
					//Vector newpos = ball.pos + ball.vel * time + ball.acc * time * time / 2;
					newpos.at(0) = ball.radius;
					// v = v0 + a*t
					newvel.at(0) = ball.vel.at(0) + ball.acc.at(0) * time2;
					newvel.at(0) *= -1;

					double time3 = time - time2;
					// x = x0 + v0*t + 1/2*a*t^2
					newpos.at(0) += newvel.at(0) * time3 + ball.acc.at(0) * time3 * time3 / 2;
					// v = v0 + a*t
					newvel.at(0) += ball.acc.at(0) * time3;
				}
				if (newpos.at(1) - ball.radius < 0)
				{
					std::pair<double, double> ans = findXInQuadraticEquation(ball.acc.at(1) / 2, ball.vel.at(1), ball.pos.at(1) - ball.radius);
					double time2 = ans.first;

					// x = x0 + v0*t + 1/2*a*t^2
					//Vector newpos = ball.pos + ball.vel * time + ball.acc * time * time / 2;
					newpos.at(1) = ball.radius;
					// v = v0 + a*t
					newvel.at(1) = ball.vel.at(1) + ball.acc.at(1) * time2;
					newvel.at(1) *= -1;

					double time3 = time - time2;
					// x = x0 + v0*t + 1/2*a*t^2
					newpos.at(1) += newvel.at(1) * time3 + ball.acc.at(1) * time3 * time3 / 2;
					// v = v0 + a*t
					newvel.at(1) += ball.acc.at(1) * time3;
				}
				if (newpos.at(0) + ball.radius > MSCREEN_WIDTH)
				{
					std::pair<double, double> ans = findXInQuadraticEquation(ball.acc.at(0) / 2, ball.vel.at(0), ball.pos.at(0) - MSCREEN_WIDTH + ball.radius);
					double time2 = ans.second;

					// x = x0 + v0*t + 1/2*a*t^2
					//Vector newpos = ball.pos + ball.vel * time + ball.acc * time * time / 2;
					newpos.at(0) = MSCREEN_WIDTH - ball.radius;
					// v = v0 + a*t
					newvel.at(0) = ball.vel.at(0) + ball.acc.at(0) * time2;
					newvel.at(0) *= -1;

					double time3 = time - time2;
					// x = x0 + v0*t + 1/2*a*t^2
					newpos.at(0) += newvel.at(0) * time3 + ball.acc.at(0) * time3 * time3 / 2;
					// v = v0 + a*t
					newvel.at(0) += ball.acc.at(0) * time3;
				}
				if (newpos.at(1) + ball.radius > MSCREEN_HEIGHT)
				{
					std::pair<double, double> ans = findXInQuadraticEquation(ball.acc.at(1) / 2, ball.vel.at(1), ball.pos.at(1) - MSCREEN_HEIGHT + ball.radius);
					double time2 = ans.second;

					// x = x0 + v0*t + 1/2*a*t^2
					//Vector newpos = ball.pos + ball.vel * time + ball.acc * time * time / 2;
					newpos.at(1) = MSCREEN_HEIGHT - ball.radius;
					// v = v0 + a*t
					newvel.at(1) = ball.vel.at(1) + ball.acc.at(1) * time2;
					newvel.at(1) *= -1;

					double time3 = time - time2;
					// x = x0 + v0*t + 1/2*a*t^2
					newpos.at(1) += newvel.at(1) * time3 + ball.acc.at(1) * time3 * time3 / 2;
					// v = v0 + a*t
					newvel.at(1) += ball.acc.at(1) * time3;
				}


				ball.pos = newpos;
				ball.vel = newvel;

			} // check if bounching
		} // for each ball in balls

		if (balls.size() != 0)
		{
			for (int i = 0; i < balls.size() - 1; i++)
			{
				for (int j = i + 1; j < balls.size(); j++)
				{
					collisionHandle(balls[i], balls[j]);
				}
			}
		} // check collision


		/*
		
		x>h
		x-h=kc
		h-kc
		*/

		SDL_RenderPresent(renderer);



		if (SDL_GetTicks64() - fpstick > 1000)
		{
			fpstick = SDL_GetTicks64();

			std::cout << "Time: " << time << std::endl;
			std::cout << "Number of balls: " << balls.size() << std::endl;
			std::cout << "Max fps: " << fpscount << std::endl;
			fpscount = 0;
		}
		fpscount++;
		//SDL_Delay(1);

	}

	return 0;
}


void collisionHandle(Ball& ballA, Ball& ballB)
{
	if (ballA.pos.distance(ballB.pos) < ballA.radius + ballB.radius)
	{
		bool quit = false;
		// xu ly neu 2 qua bong trung nhau
		Vector AB = ballB.pos - ballA.pos;
		if (AB.length() <= 0)
		{
			ballA.pos += {0, -ballA.radius};
			ballB.pos += {0, ballB.radius};
			quit = true;
		}
		else
		{
			double tmp = ballA.radius + ballB.radius - ballA.pos.distance(ballB.pos);
			Vector middle = ballA.pos + (ballA.radius - tmp / 2) * AB.unit();
			Vector distanceA = ballA.pos - middle;
			Vector distanceB = ballB.pos - middle;
			if (distanceA.length() <= 0 || distanceB.length() <= 0)
			{
				ballA.pos += {0, -ballA.radius};
				ballB.pos += {0, ballB.radius};
				quit = true;
			}
			else
			{
				ballA.pos += distanceA.unit() * (ballA.radius - ballA.pos.distance(middle));
				ballB.pos += distanceB.unit() * (ballB.radius - ballB.pos.distance(middle));
			}
		}

		if (quit) return;

		Vector forceA;
		Vector forceB;

		{
			Vector bottom = ballB.pos - ballA.pos;
			forceA = (bottom * ballA.vel.dot(bottom) / bottom.dot(bottom));
		}
		{
			Vector bottom = ballA.pos - ballB.pos;
			forceB = (bottom * ballB.vel.dot(bottom) / bottom.dot(bottom));
		}

		double massA = ballA.mass();
		double massB = ballB.mass();

		Vector forceAafter = (forceA * (massA - massB) + forceB * 2 * massB) / (massA + massB);
		Vector forceBafter = (forceB * (massB - massA) + forceA * 2 * massA) / (massB + massA);

		ballA.vel += forceAafter - forceA;
		ballB.vel += forceBafter - forceB;
	}
}
