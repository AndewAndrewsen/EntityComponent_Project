#define SFML_DYNAMIC

#include "Core.h"
#include "Entity.h"
#include "SpriteComponent.h"
#include "MovableComponent.h"
#include "ColisionComponent.h"
#include "InputComponent.h"
#include "PhysicsComponent.h"
#include "ImageCache.h"	// Loading and storing unique image files
#include "UI.h"
#include "ClickableComponent.h"	
#include "resources.h"

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <time.h>
#include <sstream>
#include <fstream>
#include <string>
#include <iostream>

#if !defined(_DEBUG)
#	pragma comment(lib, "sfml-system.lib")
#	pragma comment(lib, "sfml-graphics.lib")
#	pragma comment(lib, "sfml-window.lib")
#else
#	pragma comment(lib, "sfml-system-d.lib")
#	pragma comment(lib, "sfml-graphics-d.lib")
#	pragma comment(lib, "sfml-window-d.lib")
#endif

Core::Core(void)
{
	quit = false;
	window = NULL;
}
void Core::initialize() 
{
	sf::WindowSettings Settings; //skapa ett SFML fönster
	Settings.AntialiasingLevel = AAlevel;
	window = new sf::RenderWindow(sf::VideoMode(windowWidth, windowHeight, 32), "Forever Alone", sf::Style::Close, Settings);
	
	
	view = new sf::View(sf::FloatRect(0, 0, windowWidth, windowHeight));
	view->SetCenter(windowWidth / 2, windowHeight / 2);
	window->SetView(*view);
}

void Core::execute()
{	
	sf::Clock ticks;
	int lastTick = 0;
	
	Entity girl;
	girl.add(new SpriteComponent(&girl));
	girl.add(new PhysicsComponent(&girl));
	girl.add(new MovableComponent(&girl));

	resources res;
	if(!res.open("DATA.resf")) {
		std::cout << "Couldn't open the file DATA.resf" << std::endl;
	}

	sf::Image tjejImg = res.getImage("data\\tjej.png");
	dynamic_cast<SpriteComponent*>(girl.get("SpriteComponent"))->setImage(tjejImg);
	girl.position().x = windowWidth/2 - dynamic_cast<SpriteComponent*>(girl.get("SpriteComponent"))->size().x / 2;
	girl.position().y = (windowHeight/2 - dynamic_cast<SpriteComponent*>(girl.get("SpriteComponent"))->size().y / 2) + 300;
	bool girlSprint = false;

	

	Entity player;
	player.add(new SpriteComponent(&player));
	player.add(new MovableComponent(&player));
	player.add(new ColisionComponent(&player));
	player.add(new PhysicsComponent(&player));
	player.setHealth(100);
	UI playerHealth;
	playerHealth.setFont(res.getFont("data\\arial.ttf"));
	playerHealth.setPosition(0, 0);

	sf::Image gubbeImg = res.getImage("data\\gubbe.png");
	dynamic_cast<SpriteComponent*>(player.get("SpriteComponent"))->setImage(gubbeImg);
	player.position().x = windowWidth/2 - dynamic_cast<SpriteComponent*>(player.get("SpriteComponent"))->size().x / 2;
	player.position().y = windowHeight/2 - dynamic_cast<SpriteComponent*>(player.get("SpriteComponent"))->size().y / 2;


	Entity goalLine;
	goalLine.add(new SpriteComponent(&goalLine));
	sf::Image goalImg = res.getImage("data\\goal.png");
	dynamic_cast<SpriteComponent*>(goalLine.get("SpriteComponent"))->setImage(goalImg);
	goalLine.position().x = 20000;
	goalLine.position().y = (windowHeight/2 - dynamic_cast<SpriteComponent*>(goalLine.get("SpriteComponent"))->size().y / 2) + 300;


	Entity startButton;
	startButton.add(new SpriteComponent(&startButton));
	startButton.add(new ClickableComponent(&startButton));
	sf::Image startImg = res.getImage("data\\startbutton.png");
	dynamic_cast<SpriteComponent*>(startButton.get("SpriteComponent"))->setImage(startImg);
	startButton.position().x = 200;
	startButton.position().y = 300;
	



	
	std::vector<Entity*> stoneList;
	
	srand(time(0));
	sf::Image stoneImg = res.getImage("data\\stone.png");
	for(int i = 0; i < 20; i++)
	{
		Entity *stone = new Entity();
		stone->add(new SpriteComponent(stone));
		//stone->add(new ColisionComponent(stone));
		
		dynamic_cast<SpriteComponent*>(stone->get("SpriteComponent"))->setImage(stoneImg);
		stone->position().x = (rand() % 20000 + 50);
		stone->position().y = 700 - dynamic_cast<SpriteComponent*>(stone->get("SpriteComponent"))->getSpriteHeight();
		stoneList.push_back(stone);
	}




	UI ui;
	ui.setFont(res.getFont("data\\arial.ttf"));
	ui.setPosition((windowWidth/2), 380);
	ui.write("INIT!");
	


	UI debugText;
	debugText.setFont(res.getFont("data\\arial.ttf"));
	debugText.setPosition(300, 300);

	
	

	bool started = false;		
	while ( window->IsOpened() )
	{

		while(!started)
		{
					window->Display();
					startButton.update(window->GetFrameTime(), *window);
					if(dynamic_cast<ClickableComponent*>(startButton.get("ClickableComponent"))->getState())
					{
						started = true;
					}
						
					
		}


		// Capture all events gathered since last frame
		MovableComponent* player_movement = dynamic_cast<MovableComponent*>(player.get("MovableComponent"));
	
		sf::Event frameEvent;
		while ( window->GetEvent(frameEvent) )
		{
			// If the window is asked to be closed, close it
			if ( frameEvent.Type == sf::Event::Closed )
				window->Close();

			if(frameEvent.Type == sf::Event::KeyPressed) {
				if(frameEvent.Key.Code == sf::Key::A) {
					player_movement->setMoveLeft(true);
				}
				if(frameEvent.Key.Code == sf::Key::D) {
					player_movement->setMoveRight(true);					
				}
				if(frameEvent.Key.Code == sf::Key::Space) {
					if(!player_movement->jumping && !player_movement->jumpingPhaseTwo)
						player_movement->jumping = true;
				}

				if(frameEvent.Key.Code == sf::Key::Z)
				{
					std::ofstream saveFile;
					saveFile.open("save.sav");
					for(int i = 0; i <= stoneList.size()-1; i++)
					{
						saveFile << stoneList[i]->position().x << "\n";
						saveFile << stoneList[i]->position().y << "\n";
					}

						saveFile << player.position().x << "\n";
						saveFile << player.position().y << "\n";
						saveFile << player.getHealth() << "\n";

						saveFile << girl.position().x << "\n";
						saveFile << girl.position().y << "\n";
					
						saveFile.close();
				}


				if(frameEvent.Key.Code == sf::Key::X)
				{
					std::string line;
					std::ifstream saveFile ("save.sav", std::ios::app);
					int i = 0;
					
					int hp = 0;
					if(saveFile.is_open()) {
						saveFile >> stoneList[0]->position().x >> stoneList[0]->position().y >> stoneList[1]->position().x >> stoneList[1]->position().y >> stoneList[2]->position().x >> stoneList[2]->position().y >> stoneList[3]->position().x >> stoneList[3]->position().y >> stoneList[4]->position().x >> stoneList[4]->position().y >> stoneList[5]->position().x >> stoneList[5]->position().y >> stoneList[6]->position().x >> stoneList[6]->position().y >> stoneList[7]->position().x >> stoneList[7]->position().y >> stoneList[8]->position().x >> stoneList[8]->position().y >> stoneList[9]->position().x >> stoneList[9]->position().y >> stoneList[10]->position().x >> stoneList[10]->position().y >> stoneList[11]->position().x >> stoneList[11]->position().y >> stoneList[12]->position().x >> stoneList[12]->position().y >> stoneList[13]->position().x >> stoneList[13]->position().y >> stoneList[14]->position().x >> stoneList[14]->position().y >> stoneList[15]->position().x >> stoneList[15]->position().y >> stoneList[16]->position().x >> stoneList[16]->position().y >> stoneList[17]->position().x >> stoneList[17]->position().y >> stoneList[18]->position().x >> stoneList[18]->position().y >> stoneList[19]->position().x >> stoneList[19]->position().y >> player.position().x >> player.position().y >> hp >> girl.position().x >> girl.position().y;
						player.setHealth(hp);
				/*		while(saveFile.good()) {
							std::getline (saveFile, line);
							


							}
							i++;
						
						}
						saveFile.close();
						}*/
					}
				}

			}
			// Close the window if the user presses the 'escape'-key
			if ( frameEvent.Type == sf::Event::KeyReleased )
			{
				if(frameEvent.Key.Code == sf::Key::A) {
					player_movement->setMoveLeft(false);

				}
				if(frameEvent.Key.Code == sf::Key::D) {
					player_movement->setMoveRight(false);

				}				

				if(frameEvent.Key.Code == sf::Key::Space) {
					
				}

				
				if ( frameEvent.Key.Code == sf::Key::Escape )
					window->Close();
			}
		
		}
		// Clear the screen to black.
		window->Clear(sf::Color(152, 217, 234));
	
		view->SetCenter(player.position().x, player.position().y);
		//Update
		
		

			
			int t = ticks.GetElapsedTime();	
			if((t - lastTick) > 0.25f)	{
				
				
			for(int i = 0; i < stoneList.size(); i++)
			{

				if(stoneList[i]->position().x > (view->GetCenter().x - (windowWidth / 2)) && stoneList[i]->position().x < (view->GetCenter().x + (windowWidth/2)))
				{
				
					if(stoneList[i]->position().x > player.position().x && stoneList[i]->position().x < (player.position().x + dynamic_cast<SpriteComponent*>(player.get("SpriteComponent"))->getSpriteWidth()) &&
						(player.position().y + dynamic_cast<SpriteComponent*>(player.get("SpriteComponent"))->getSpriteHeight()) > stoneList[i]->position().y)
					{
					
					
						debugText.write("TRUE");
						girlSprint = true;
						player.setHealth(player.getHealth()-10);
						break;
						//debugText.write("GirlSpring: True");
					
					} else {
						girlSprint = false;
						debugText.write("FALSE");	
					}
				
				

				/*
					if(stoneList.size() > 1) {
						if(stoneList[i]->position().x < player.position().x)
						{
							stoneList.erase(stoneList.begin() + i);
						}
					}*/
				
				}
				lastTick = ticks.GetElapsedTime();	
	
				}
				
			
		
		
			}

			for(int i = 0; i < stoneList.size(); i++)
				stoneList[i]->update(window->GetFrameTime(), *window);


		//ui.update(*window, *view);
			if(player.getHealth() >= 0)
			{
				int pixelsLeft = 20000 - player.position().x;
				std::stringstream ss;
				ss << "Pixels left: ";
				ss << pixelsLeft;
				ss << " | ";

				ss << "Player Health: ";
				ss << player.getHealth();
				ui.write(ss.str());
				playerHealth.write(ss.str());
				ui.update(*window, *view);
			}
			else
			{
				ui.write("DEAD");
				ui.update(*window, *view);
			}
		debugText.update(*window, *view);
		//window->Draw(ui.getText());
		
		goalLine.update(window->GetFrameTime(), *window);
		

		if(girlSprint)
		{
			dynamic_cast<MovableComponent*>(player.get("MovableComponent"))->speed() = 0.2f;
			girl.position().x += 2.0f;
		}
		else
		{
			dynamic_cast<MovableComponent*>(player.get("MovableComponent"))->speed() = 0.5f;
			girl.position().x += 0.4f;
		}
		player.update(window->GetFrameTime(), *window);
		girl.update(window->GetFrameTime(), *window);
		
		
		// on ending.
		if(player.getHealth() <= 0) 
		{
			UI gameOverUi;
			gameOverUi.setFont(res.getFont("data\\arial.ttf"));
			gameOverUi.write("You died by stepping on too many rocks!\nThat girl you raced are also dead because of you.. :'(");
			gameOverUi.setPosition(50, 100);
			gameOverUi.update(*window, *view);
			window->Display();
			sf::Sleep(3.0f);
			break;
		}

		if((20000 - player.position().x) <= 0) 
		{
			UI gameOverUi;
			gameOverUi.setFont(res.getFont("data\\arial.ttf"));
			gameOverUi.write("You won! GZ..");
			gameOverUi.setPosition(50, 100);
			gameOverUi.update(*window, *view);
			window->Display();
			sf::Sleep(3.0f);
			break;
		}
		

		if((20000 - girl.position().x) <= 0) 
		{
			UI gameOverUi;
			gameOverUi.setFont(res.getFont("data\\arial.ttf"));
			gameOverUi.write("You lost! :'(");
			gameOverUi.setPosition(50, 100);
			gameOverUi.update(*window, *view);
			window->Display();
			sf::Sleep(3.0f);
			break;
		}
		
		// Flip the back-buffer with the front-buffer.
		window->Display();
	}
}


//HANDLE LATER:
Core::~Core(void){deinitialize();}
void Core::deinitialize(){}