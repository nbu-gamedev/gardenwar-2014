#include "menu.h"
#define SCREEN_WIDTH 1380
#define SCREEN_HEIGHT 600
#define PI 3.14159265

Menu::Menu()
{
    instructions = NULL;
    title_screen = NULL;
    ScreenSurface = NULL;
}

void menu_factory(Menu &Game)
{
    Game.instructions = SDL_LoadBMP("../bin/media/instructions.bmp");
    Game.title_screen = SDL_LoadBMP("../bin/media/Menu_Screen.bmp");
    Game.ScreenSurface = NULL;
    Game.Window = SDL_CreateWindow("Plants Vs Zombies", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    Game.menu_music = Mix_LoadMUS("../bin/media/Sounds/menu.wav");
}

void Menu::handle_menu()
{
    bool quit = false;
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Event event;

    Window = SDL_CreateWindow("Plants Vs Zombies", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    ScreenSurface = SDL_GetWindowSurface(Window);

    bool show_inst = false;

    while(!quit)
    {
		while(SDL_PollEvent(&event) != 0)
		{
            int mouseX, mouseY;
            if(event.type == SDL_QUIT)
            {
                quit = true;
            }

            if(event.type == SDL_MOUSEBUTTONUP)
            {
                SDL_GetMouseState(&mouseX,&mouseY);
                if(mouseX >= 125 && mouseX <= 350 && mouseY >= 400 && mouseY <= 475)
                {
                    SDL_Quit();SDL_LoadBMP("../bin/media/Menu_Screen.bmp");
                    start_game();
                }
                if(mouseX >= 1100 && mouseX <= 1325 && mouseY >= 400 && mouseY <= 475)
                {
                    SDL_Quit();
                    return;
                }
                if(mouseX >= 1200 && mouseX <= 1385 && mouseY >= 25 && mouseY <= 100 && show_inst == false)
                {
                    show_inst = true;
                }
                else if(show_inst == true)
                {
                    show_inst = false;
                }
            }
            SDL_BlitSurface(title_screen, NULL, ScreenSurface, NULL);
            if(show_inst == true)
                show_instructions();
            SDL_UpdateWindowSurface(Window);

            if(Mix_PlayingMusic() == 0)
            {
                Mix_PlayMusic(menu_music, -1);
            }
		}
    }
    SDL_Quit();
}

void Menu::start_game()
{
     World level = World();
	level.createWorld();
	SDL_Event event;
    bool clickedOnSun = false;
    int timeToSun = level.sunSpawnTime;
    unsigned int lastTime = 0, lastTimeDraw = 0, currentTime, lastTimeMoved = 0;
    currentTime = 0;
    level.grid[3][2].push_back(new Sunflower(2));

	while( !World::quit ){
        currentTime = SDL_GetTicks();
		while( SDL_PollEvent( &event ) != 0 ) {
            if( event.type == SDL_QUIT){//} || (event.key.keysym.sym)== SDLK_ESCAPE){
                World::quit = true;
            }
		    if (event.type == SDL_MOUSEBUTTONUP){
                // if player clicks on sun -> collect it
                clickedOnSun = false;
                for (unsigned int i=0 ; i < level.suns.size(); i++) {
                    if ( (event.button.x > level.suns[i]->x) && (event.button.x < level.suns[i]->rightX ) &&
                         (event.button.y > level.suns[i]->y) && (event.button.y < level.suns[i]->bottomY ) ) {
                        // level.setSunCurrency(level.suns[i]->getSunValue());
                        // cout << "$$$: " << level.getSunCurrency() << endl;
                        level.collectedSuns.push_back(new Sun(level.suns[i]->x,level.suns[i]->y,5,5));
                        delete level.suns[i];
                        level.suns.erase(level.suns.begin() + i);
                        clickedOnSun = true;
                        break;
                    }
                }
                 for (unsigned int i=0 ; i < level.naturalSuns.size(); i++) {
                    if ( (event.button.x > level.naturalSuns[i]->x) && (event.button.x < level.naturalSuns[i]->rightX ) &&
                         (event.button.y > level.naturalSuns[i]->y) && (event.button.y < level.naturalSuns[i]->bottomY ) ) {
                        //level.setSunCurrency(level.naturalSuns[i]->getSunValue());
                        // cout << "$$$: " << level.getSunCurrency() << endl;
                        level.collectedSuns.push_back(new Sun(level.naturalSuns[i]->x,level.naturalSuns[i]->y,5,5));
                        delete level.naturalSuns[i];
                        level.naturalSuns.erase(level.naturalSuns.begin() + i);
                        clickedOnSun = true;
                        break;
                    }
                }
                if ( ( !clickedOnSun ) && (level.clickedOnShop) &&
                     (event.button.x > gridStartX) && (event.button.x < gridEndX) &&
                     (event.button.y > gridStartY) && (event.button.y < gridEndY) ) {
                    level.createDefender(event);
                    break;
                }
                for (int i = 0; i < ALL_SHOP_ITEMS ; i++){
                    level.ShopItem[i].clicked = (level.ShopItem[i].mouseOver() && level.canAfford(level.ShopItem[i]) );
                    level.clickedOnShop = true;
                }

            }

        }

        if (currentTime >= lastTimeMoved +30) {
            for (unsigned int i=0 ; i < level.suns.size(); i++) {
                if (level.suns[i]->x <= level.suns[i]->destinationX && level.suns[i]->y <= level.suns[i]->destinationY ) {
                    double distancePast = (currentTime - level.suns[i]->timeCreated) / level.suns[i]->timeToTravel;
                    level.suns[i]->y = level.suns[i]->startY - ((arc)*(sin(distancePast * PI)));
                    level.suns[i]->x += 3;
                    level.suns[i]->rightX += 3;
                }
            }
            for (unsigned int i=0 ; i < level.naturalSuns.size(); i++) {
                if ( level.naturalSuns[i]->y <= level.naturalSuns[i]->destinationY )
                    level.naturalSuns[i]->y += 3;
                    level.naturalSuns[i]->bottomY += 3;

            }
            for (unsigned int i=0 ; i < level.collectedSuns.size(); i++) {
                double distancePast = (currentTime - level.collectedSuns[i]->timeCreated) / level.collectedSuns[i]->timeToTravel;
                if (level.collectedSuns[i]->y >= level.collectedSuns[i]->destinationY-arc+5 ) {
                   // level.collectedSuns[i]->y -= 3;
                   level.collectedSuns[i]->y = level.collectedSuns[i]->startY-(distancePast* level.collectedSuns[i]->startY)-arc*sin(distancePast*PI);
                    cout << level.collectedSuns[i]->y << endl;
                }
                if (level.collectedSuns[i]->x >= level.collectedSuns[i]->destinationX ) {
                  //  level.collectedSuns[i]->x -= 3;

                   level.collectedSuns[i]->x = level.collectedSuns[i]->startX - (distancePast* level.collectedSuns[i]->startX);
                }
                if (level.collectedSuns[i]->x <= level.collectedSuns[i]->destinationX &&
                    level.collectedSuns[i]->y <= level.collectedSuns[i]->destinationY ) {

                    level.setSunCurrency(level.collectedSuns[i]->getSunValue());
                    delete level.collectedSuns[i];
                    level.collectedSuns.erase(level.collectedSuns.begin() + i);
                }
            }
            lastTimeMoved = currentTime;
        }

      //  if (currentTime >= lastTimeDraw + 100)
      //  {
            level.peaShooting(currentTime);
      //      lastTimeDraw = currentTime;
            level.draw(currentTime);
       // }
        if (currentTime >= lastTime + 1000)
        {
            lastTime += 1000;
			level.update(currentTime);
			timeToSun--;
			if (timeToSun<=0){
                level.createNaturalSun();
                timeToSun = level.sunSpawnTime;
			}
		}
	}

	level.destroyWorld();
	SDL_Quit();
}

void Menu::show_instructions()
{
    SDL_Rect destination;
    SDL_Rect image;
    destination.x = 415;
    destination.y = 150;
    destination.h = 0;
    destination.w = 0;
    image.h = 300;
    image.w = 550;
    image.x = 0;
    image.y = 0;
    SDL_SetColorKey(instructions, SDL_TRUE, SDL_MapRGB(instructions->format, 255, 255, 255));
    SDL_BlitSurface(instructions, &image, ScreenSurface, &destination);
}
