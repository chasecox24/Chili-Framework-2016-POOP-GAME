/******************************************************************************************
 *	Chili DirectX Framework Version 16.07.20											  *
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd)
{
}

void Game::Go()
{
	gfx.BeginFrame(); // begin drawing a new frame
	UpdateModel(); // update the game logic
	ComposeFrame(); // draw the frame
	gfx.EndFrame(); // show the frame we just drew
}

// GAME LOGIC ONLY, NO DRAWING
void Game::UpdateModel() 
{
	//RIGHT
	if (wnd.kbd.KeyIsPressed(VK_RIGHT))
	{
		if (inhitbitRight)
		{
		}
		else
		{
			vx = vx + 1;
			inhitbitRight = true;
		}
	}
	else
	{
		inhitbitRight = false;
	}

	//LEFT
	if (wnd.kbd.KeyIsPressed(VK_LEFT))
	{
		if (inhitbitLeft)
		{
		}
		else
		{
			vx = vx - 1;
			inhitbitLeft = true;
		}
	}
	else 
	{
		inhitbitLeft = false;
	}

	//UP
	if (wnd.kbd.KeyIsPressed(VK_UP))
	{
		if (inhitbitUp)
		{
		}
		else
		{
			vy = vy - 1;
			inhitbitUp = true;
		}
	}
	else
	{
		inhitbitUp = false;
	}

	//DOWN
	if (wnd.kbd.KeyIsPressed(VK_DOWN))
	{
		if (inhitbitDown)
		{
		}
		else
		{
			vy = vy + 1;
			inhitbitDown = true;
		}
	}
	else
	{
		inhitbitDown = false;
	}

	// SPACE // STOP THE MOVEMENT
	if (wnd.kbd.KeyIsPressed(VK_SPACE))
	{
		vx = 0;
		vy = 0;
	}

	//UPDATE THE POSITION WITH VELOCITY
	x = x + vx;
	y = y + vy;


	//PREVENT THE CROSSHAIR FROM GOING OFF THE SCREEN AND CHANGE ITS VELOCITY TO 0 IF IT HITS THE EDGE OF THE SCREEN
	//RIGHT
	if (x + 5 >= gfx.ScreenWidth) // x+5 is the furthest right pixel of the crosshair
	{
		x = gfx.ScreenWidth - 6; // - 6 because we want to put the furthest right pixel of the crosshair at the edge of the screen
		vx = 0; // velocity becomes 0 to prevent having to spam the opposite key to move it again
	}
	//LEFT
	if (x - 5 <= 0) // furthest left pixel of the crosshair
	{
		x = 6;
		vx = 0;
	}
	//UP
	if (y + 5 >= gfx.ScreenHeight) // furthest up pixel of the crosshair
	{
		y = gfx.ScreenHeight - 6;
		vy = 0;
	}
	//DOWN
	if (y - 5 <= 0) // furthest down pixel of the crosshair
	{
		y = 6;
		vy = 0;
	}

	// CONTROL // COLOR CHANGER
	controlIsPressed = wnd.kbd.KeyIsPressed(VK_CONTROL);
	controlIsPressed = false; 

	//CREATE AN AREA THAT CHANGES PIXELS
	if (x > 200 && x < 300) // (! (x > 200 && x < 300) ) to flip the condition
	{ 
		controlIsPressed = true; // can do !true to flip it
	}

	// CHANGE THE COLOR OF THE PIXELS
	if (controlIsPressed)
	{
		gb = 0;
	}
	else
	{
		gb = 255;
	}

	// CHANGE THE SHAPE
	shapeIsChanged = wnd.kbd.KeyIsPressed(VK_SHIFT); // this will be true if the shift key is pressed, false otherwise
	shapeIsChanged = false; // default is to draw a crosshair

	if (x > 500 && x < 700 && y > 20 && y < 580) // create an area that changes the shape
	{
		shapeIsChanged = true;
	}
	else
	{
		shapeIsChanged = false;
	}
}

// THIS IS IN A WHILE LOOP INSIDE WIN MAIN SO IT WILL RUN FOREVER UNTIL THE USER QUITS THE PROGRAM (60 TIMES A SECOND)

void Game::ComposeFrame() // DRAWLING FUNCTION

//  SHIFT+ CTR + SPACE // GIVE TOOLTIPS
//  CTRL + K THEN CTRL + D // FORMATS CODE

{				//800x, 600y    RGB      
	//gfx.PutPixel(695, 500, 255,gb,gb); // put a pixel on the screen

	// Set variables have a lifespan called scope (LESSON 7)
	// moved variables from local function scope to member variable scope so they can live as long as the program is running (LESSON 8)
	/*int x = 400;
	int y = 300;*/

	const int boxWidth = 10;
	const int boxHeight = 10;
	
	//object.member.function(parameter)
//const bool condition = wnd.kbd.KeyIsPressed( VK_UP); // this will stay true as long as the up arrow key is pressed

	if (shapeIsChanged) // this is a branch that will execute depending on the value of the condition
	{
		// Draw the box outline using a for loop // I was lazy to not put the pixels one by one
		for (int i = 0; i < boxWidth; i++) {
			gfx.PutPixel(x + i, y, 255, gb, gb);           // top edge
			gfx.PutPixel(x + i, y + boxHeight - 1, 255, gb, gb); // bottom edge
		}

		for (int j = 0; j < boxHeight; j++) {
			gfx.PutPixel(x, y + j, 255, gb, gb);           // left edge
			gfx.PutPixel(x + boxWidth - 1, y + j, 255, gb, gb); // right edge
		}
	}
	else // default is to draw a crosshair
	{
		// left and right
		gfx.PutPixel(-5 + x, y, 255, gb, gb);
		gfx.PutPixel(-4 + x, y, 255, gb, gb);
		gfx.PutPixel(-3 + x, y, 255, gb, gb);
		gfx.PutPixel(3 + x, y, 255, gb, gb);
		gfx.PutPixel(4 + x, y, 255, gb, gb);
		gfx.PutPixel(5 + x, y, 255, gb, gb);

		//// top and bottom
		gfx.PutPixel(x, -5 + y, 255, gb, gb);
		gfx.PutPixel(x, -4 + y, 255, gb, gb);
		gfx.PutPixel(x, -3 + y, 255, gb, gb);
		gfx.PutPixel(x, 3 + y, 255, gb, gb);
		gfx.PutPixel(x, 4 + y, 255, gb, gb);
		gfx.PutPixel(x, 5 + y, 255, gb, gb); // 3D graphics transfer vertices in order to move graphics
		//  SHIFT+ CTR + SPACE // GIVE TOOLTIPS
	}
}
