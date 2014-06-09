#include "world.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#define SCREEN_WIDTH 1380
#define SCREEN_HEIGHT 600
using namespace std;

list<Actor*>::iterator it;
list<Actor*>::iterator it2;
list<Pea*>::iterator itPea;

World::World(){
	peaImagePH = NULL;
	peaShadowImagePH = NULL;
	sunImagePH = NULL;
	shopSprite = NULL;
	numbersSpite = NULL;
    gameOverScreen = NULL;
    winnerScreen = NULL;
    Background = NULL;
    ScreenSurface = NULL;

    zombieWavesLength = 300;
    zombieWaves = NULL;

    peaSpeed = 0;

    sunSpawnTime = 5; // it saves time whale testing, should be 15 change it if its bothering you.
    sunCurrency = 300;
    //init the shop struct
    clickedOnShop = false;
    ShopItem[PEASHOOTER].cost = 100;
    ShopItem[SUNFLOWER].cost = 50;
    ShopItem[WALLNUT].cost = 50;
    for (int i = 0; i<ALL_SHOP_ITEMS; i++){
        ShopItem[i].x = 15+(70*i);
        ShopItem[i].y = 15;
        ShopItem[i].sideX = ShopItem[i].x + 65;
        ShopItem[i].bottomY = ShopItem[i].y + 90;
        ShopItem[i].clicked = false;
    }
}

World::~World(){
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            for(it=grid[i][j].begin();it!=grid[i][j].end();it++) {
                delete (*it);
            }
        }
    }

    for(itPea=peas.begin();itPea!=peas.end();itPea++) {
		delete (*itPea);
    }

    delete [] zombieWaves;
}
void World::readData(){
    // zombie waves

    ifstream zombiesFile("../bin/data/zombieWave.txt");
    if (!zombiesFile.fail()){
        string s;
        char buf;
        getline(zombiesFile,s);
        istringstream sec(s);
        while(sec>>buf) {
            if (buf==':') {
                int bufLen;
                sec>>bufLen;
                // primerno do 5000 sec max, ako ima gre6ka v dannite 300 po default
                if (bufLen > 0 && bufLen < 5000){ zombieWavesLength = bufLen;}
                break;
            }
        }
        zombieWaves = new vector<int> [zombieWavesLength+1];
        while(getline(zombiesFile,s)){
            int sec,pos;
            istringstream ss(s);
            ss>>sec;
            ss>>buf; // ':' (??)
            while(ss>>pos){
                if (sec<=zombieWavesLength && sec>=0 && pos>=0 && pos<M) zombieWaves[sec].push_back(pos);
            }
        }
    }
    zombiesFile.close();

    // pea speed
     ifstream peaFile("../bin/data/peaSpeed.txt");
    if (!peaFile.fail()){
        string s;
        getline(peaFile,s);
        istringstream ss(s);
        char buf;
        int spd;
        while (ss>>buf) {
            if(buf==':') {ss>>spd;break;}
        }
        peaSpeed = spd;
    }
    peaFile.close();
}

void World::createWorld(){
    fstream read_file;
    string work_string;
    read_file.open("../bin/data/Image_Names.txt");
    readData();
    Window = SDL_CreateWindow("Plants Vs Zombies", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    ScreenSurface = SDL_GetWindowSurface(Window);
    getline(read_file, work_string);
    Background = SDL_LoadBMP(work_string.c_str());
    getline(read_file, work_string);
    gameOverScreen = SDL_LoadBMP("../bin/media/gameOver.bmp");
    winnerScreen = SDL_LoadBMP("../bin/media/winnerScreen.bmp");
    SDL_BlitSurface(Background, NULL, ScreenSurface, NULL);
    SDL_UpdateWindowSurface(Window);
    getline(read_file, work_string);
    sunImagePH = SDL_LoadBMP(work_string.c_str());
    SDL_SetColorKey(sunImagePH, SDL_TRUE, SDL_MapRGB(sunImagePH->format, 255, 255, 255));
    getline(read_file, work_string);
    numbersSpite= SDL_LoadBMP(work_string.c_str());
    getline(read_file, work_string);
    shopSprite= SDL_LoadBMP(work_string.c_str());
    getline(read_file, work_string);
    peaImagePH = SDL_LoadBMP(work_string.c_str());
    SDL_SetColorKey(peaImagePH, SDL_TRUE, SDL_MapRGB(peaImagePH->format, 255, 255, 255));
    getline(read_file, work_string);
    peaShadowImagePH = SDL_LoadBMP(work_string.c_str());
    SDL_SetColorKey(peaShadowImagePH, SDL_TRUE, SDL_MapRGB(peaImagePH->format, 255, 255, 255));
    images_factory(Creature_images);
    sound_factory(Sounds);
}


void World::destroyWorld(){
    SDL_DestroyWindow(Window);
    SDL_FreeSurface(gameOverScreen);
    SDL_FreeSurface(winnerScreen);
    SDL_FreeSurface(Background);
    SDL_FreeSurface(peaImagePH);
    SDL_FreeSurface(peaShadowImagePH);
    SDL_FreeSurface(sunImagePH);
}

void World::draw(int currTime)
{
    SDL_BlitSurface(Background, NULL, ScreenSurface, NULL);

// pea shadow

    for(itPea=peas.begin();itPea!=peas.end();itPea++) {

        int peaShadowPosX = (*itPea)->getCurrPeaPos(currTime);
        int peaShadowPosY = offset_y*((*itPea)->y)+offset_y/2+gridStartY;
		apply_surface(peaShadowPosX, peaShadowPosY, peaShadowImagePH, ScreenSurface);
    }
//-------


    for(int i=0; i<N; i++)
    {
        for(int j=0; j<M; j++)
        {
            for(list<Actor*>::iterator it = grid[i][j].begin(); it != grid[i][j].end(); it++)
            {
                if((*it)->getAct() != DIE)
                    (*it)->draw_self(j, i, Creature_images[(*it)->getType()], ScreenSurface, currTime);
            }
        }
    }
    // Samir's part:


    //using sprite sheet for the numbers 0-9
    SDL_Rect source;
    SDL_Rect destination;
    source.y = 0;
    source.w = 18;
    source.h = 20;
    destination.y = 0;
    int number;
    int digitNumber=0; // used to know witch digit we are getting from right to left.
    int sunCurrencyTMP = sunCurrency;
    //do loop extracts the right digit and prints it on the screen,
    //uses the remaining numbers to extra the right digit and to print it
    //left of the first digit extracted;
    do{
        number = sunCurrencyTMP % 10;
        source.x = 2+(16*number);
        destination.x = 54-(18*digitNumber); // digits printed from right to left.
        digitNumber++;
        sunCurrencyTMP = sunCurrencyTMP / 10;

    SDL_BlitSurface(numbersSpite, &source, ScreenSurface, &destination);
    } while (sunCurrencyTMP>0);



    for (int i = 0; i < ALL_SHOP_ITEMS; i++){
        destination.x = ShopItem[i].x;
        source.x = 35+(70*i);
        destination.y = 20;
        source.y = 130;
        source.w = 65;
        source.h = 90;
        int x,y;
        SDL_GetMouseState(&x,&y);
        // if shopitem[i] clicked 95%
        if (ShopItem[i].clicked){
            destination.x += 2;
            source.y = 408;
            source.x -= 2*i;
            source.w = 63;
            source.h = 83;
        }
        // if Shopitem[i] noMoney draw no money img
        else if ( ShopItem[i].cost > sunCurrency ){
            source.y = 316;
        }
        // if shopiteem[i] mouseOver draw 105%
        else if (ShopItem[i].mouseOver()){
            destination.x -= 2;
            source.x += i*2;
            source.y += 92;
            source.w += 2;
            source.h += 2;
        }
        // else draw normal

        SDL_BlitSurface(shopSprite, &source, ScreenSurface, &destination);
    }

    for (unsigned int currentSun = 0; currentSun < suns.size(); currentSun++){

        double changeY = 50;
        int currentTime = SDL_GetTicks();
        int timePassed = 0;
        timePassed = currentTime - suns[currentSun]->timeCreated;
       // cout << timePassed << endl;
       // if (timePassed<1000){
        changeY = changeY*(sin((timePassed)*3.14));
       // cout << changeY << endl;
      //  }
        apply_surface(suns[currentSun]->x,suns[currentSun]->y,sunImagePH,ScreenSurface);
    }
    for (unsigned int currentSun = 0; currentSun < naturalSuns.size(); currentSun++){

       apply_surface(naturalSuns[currentSun]->x,naturalSuns[currentSun]->y,sunImagePH,ScreenSurface);
    }
    for (unsigned int currentSun = 0; currentSun < collectedSuns.size(); currentSun++){

        apply_surface(collectedSuns[currentSun]->x,collectedSuns[currentSun]->y,sunImagePH,ScreenSurface);
    }

// pea

    for(itPea=peas.begin();itPea!=peas.end();itPea++) {

        int peaPosX = (*itPea)->getCurrPeaPos(currTime);
        int peaPosY = offset_y*((*itPea)->y)+gridStartY;
		apply_surface(peaPosX, peaPosY, peaImagePH, ScreenSurface);
    }
// ----------
    SDL_UpdateWindowSurface(Window);
}

void World::update(int currTime){


    Sounds.start_game_music();
    int clock = (currTime/1000);
    // if won level!
    if (clock > zombieWavesLength){
        bool winner = true;
        for(int i=0; i<N && winner; i++){
            for(int j=0; j<M; j++){
               if (!grid[i][j].empty() && grid[i][j].back()->getType() == ZOMBIE){
                        winner = false;
                        break;
                }
            }
        }
        if (winner) gameOver(true);
    }

	for(int i=0; i<N; i++){
		for(int j=0; j<M; j++){
		    it=grid[i][j].begin();
            while(it!=grid[i][j].end()){
		// --- vreme za umirane:
				if( (*it)->getHP() <= 0){
					if((*it)->getAct()!=DIE) {(*it)->setAct(DIE);it++;}
					else if( (*it)->timeToAct() ){ // ... && (*it)->getAct()==DIE
						delete (*it);
						it=grid[i][j].erase(it);
					}
					else { (*it)->incCounter(); it++;}
					continue;
				}
		//---------------------

		// I. ako e zombie:
				if ( (*it)->getType()==ZOMBIE){

					bool flowerExists = false;
					Actor* enemy=grid[i][j].front();
           // 1. atakuva (enemy na sy6toto kvadrat4e)
					if( ((enemy->getType())!=ZOMBIE) && (enemy->getAct()!=DIE) ) {
						flowerExists = true;
						Sounds.play_zombie_eat();
						if ((*it)->timeToAct()){
                            enemy->addHP( -((*it)->getDamage()) );
						}
						if( (*it)->getAct()!=ATTACK){
							(*it)->setAct(ATTACK);
						}
					}
					if(!flowerExists){
					    // ako ve4e ne atakuva
					    if((*it)->getAct()==ATTACK) {
					        (*it)->setAct(MOVE,currTime);
                            it++;
                            continue;
                        }
			//  2. stignalo e do kraq
						if(j==0){
							if ((*it)->timeToAct()){
								gameOver(false);
                                break;
							}
						}
			//  3. mesti se
						else {  //  j!=0
							if( (*it)->timeToAct()) {
								(*it)->setAct(MOVE,currTime);
								grid[i][j-1].push_back((*it));
								it=grid[i][j].erase(it);
								continue; //za da prodylji s novata stoinost na it..
							}
						}
					}
				}
	// II. ako e cvete:
				else {
					if ((*it)->getType()==PEASHOOTER){
                        bool zombieExists = false;
            // 1. ako ima pred nego v sy6toto kvadrat4e, no ne strelq :
                        for((it2=it)++; it2!=grid[i][j].end(); it2++){ //it2 =it+1 za da po4ne da gleda sled nego (cveteto vinagi e na pyrvo mqsto i e !)
                            if ( ((*it2)->getType()==ZOMBIE) && ((*it2)->getAct()!=DIE) ) {
                                zombieExists = true;

                                if( (*it)->getAct()!=ATTACK ) {(*it)->setAct(ATTACK);}

                                else {
                                    if ( (*it)->timeToAct() ){
                                    // v slu4aq kogato sa na edno kvadrat4e -> PS vzima jivot na zombito, ne grah4eto
                                      	Sounds.play_peashooter_shoot();
                                        (*it2)->addHP(-((*it)->getDamage()) );
                                    }
                                }
                                break; // namerilo e enemy, spira da tyrsi
                            }
                        }
                        if(!zombieExists){
        // 2. tyrsi v predni kvadrat4eta i strelq (samo ako ima po kogo...)
                            for(int k=j+1;(k<M);k++){
                                for(it2=grid[i][k].begin(); it2!=grid[i][k].end(); it2++){
                                    if ( ((*it2)->getType()==ZOMBIE) && ((*it2)->getAct()!=DIE) ){
                                        zombieExists = true;
                                        if((*it)->getAct()!=ATTACK) {(*it)->setAct(ATTACK);}
                                        else{
                                            if((*it)->timeToAct()){
                                    // grah4eta
                                                peas.push_back(new Pea( peaSpeed, (*it)->getPosX(), i, *it2, *it, currTime ));
                                                Sounds.play_peashooter_shoot();
                                    // --------
                                            }
                                        }
                                        break; // break na obhojdaneto na teku6toto kvadrat4e
                                    }
                                }
                                if(zombieExists) break; // namerilo e enemy, spira da tyrsi
                            }
                        }
                        // ako ve4e ne napada:
                        if(!zombieExists && (*it)->getAct()==ATTACK) {(*it)->setAct(STAY);}
					}
					else if ((*it)->getType()==SUNFLOWER){
						if((*it)->timeToAct()) {
							suns.push_back(new Sun( (gridStartX+((j+1)*offset_x)-70),(gridStartY+((i+1)*offset_y)-SUN_SIZE),
                            (gridStartX+(j+1)*offset_x)+5 ,(gridStartY+((i+1)*offset_y)-SUN_SIZE)));
						}
					}
					else{}
				}
				(*it)->incCounter();
				it++;
			}
		}
	}
    itPea=peas.begin();
	while(itPea!=peas.end()) {

	    if((*itPea)->enemyIsDead()) { (*itPea)->aim = NULL; }
	    //looking for new enemy
        if((*itPea)->aim == NULL){
            int i = (*itPea)->y;
            int j = (*itPea)->getPlace(currTime);
            for(int k=j;(k<M) && (*itPea)->aim == NULL;k++){
                for(it2=grid[i][k].begin(); it2!=grid[i][k].end(); it2++){
                    if ( ((*it2)->getType()==ZOMBIE) && ((*it2)->getAct()!=DIE) && ((*itPea)->getCurrPeaPos(currTime) <= (*it2)->getPosX(currTime)) ){
                        (*itPea)->aim = (*it2);
                        break;
                    }
                }
            }
        }
        itPea++;
	}

    if (clock <= zombieWavesLength){
        if(!zombieWaves[clock].empty()){
            for(unsigned int i=0; i<zombieWaves[clock].size(); i++){
                grid[(zombieWaves[clock][i])][M-1].push_back(new Zombie(currTime));
            }
        }
    }

}

void World::peaShooting(int currTime){
	itPea=peas.begin();
	while(itPea!=peas.end()) {

		// ako: 1) grah4eto e stignalo zombito
		if ( (*itPea)->reachedAim(currTime) ) {
		    ((*itPea)->aim)->addHP(-(((*itPea)->creator)->getDamage()) );
			delete (*itPea);
			itPea=peas.erase(itPea);
		}

		// 2) grah4eto e stignalo do kraq na grida
		else if ( (*itPea)->getPlace(currTime) > M ){
            delete (*itPea);
			itPea=peas.erase(itPea);
		}
		else itPea++;
    }


}


void World::gameOver(bool win){
    if (win){
        // apply_surface(380, 190, winnerScreen, ScreenSurface);
        Mix_PauseMusic();
        Sounds.play_win_sound();
    }
    else{
        apply_surface(380, 190, gameOverScreen, ScreenSurface);
        Mix_PauseMusic();
        Sounds.play_lose_sound();
    }
    SDL_UpdateWindowSurface(Window);
    SDL_Delay(4500);
    quit=true;
}

void World::apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination)
{
    SDL_Rect offset;
    offset.x = x;
    offset.y = y;
    SDL_BlitSurface( source, NULL, destination, &offset );
}

void World::createNaturalSun() {
    //placing new sun in the vector "suns" in world.
    int x = rand() % gridSizeX + gridStartX;
    int y = rand() % gridSizeY + gridStartY;
    naturalSuns.push_back(new Sun( x , y-1000, x ,y ));

    cout << "Total Natural suns: " << naturalSuns.size() <<  endl;
}

void World::updateSuns() {


}

void World::createDefender(SDL_Event &event){
    if (ShopItem[PEASHOOTER].clicked){
        createPeashooter(event);
        return;
    }
    else if (ShopItem[SUNFLOWER].clicked){
        createSunflower(event);
        return;
    }
    else if (ShopItem[WALLNUT].clicked){
        createWallnut(event);
        return;
    }

}

void World::createPeashooter(SDL_Event &event){
    int row = 0;
    int column = 0;
    // Place Peashooter at clicked grid location
    column = (event.button.x - base_x)/offset_x;
    row = (event.button.y - base_y)/offset_y;

    if ((grid[row][column].empty()) || ((grid[row][column].front()->getType() == ZOMBIE))) {
        grid[row][column].push_front (new Peashooter(column));
        ShopItem[PEASHOOTER].clicked = false;
        sunCurrency -= ShopItem[PEASHOOTER].cost;

    }
}

void World::createSunflower(SDL_Event &event){
    int row = 0;
    int column = 0;
    // Place Peashooter at clicked grid location
    column = (event.button.x - base_x)/offset_x;
    row = (event.button.y - base_y)/offset_y;

    if ((grid[row][column].empty()) || ((grid[row][column].front()->getType() == ZOMBIE))) {
            grid[row][column].push_front (new Sunflower(column));
        ShopItem[SUNFLOWER].clicked = false;
        sunCurrency -= ShopItem[SUNFLOWER].cost;

    }
}

void World::createWallnut(SDL_Event &event){
    int row = 0;
    int column = 0;
    // Place Peashooter at clicked grid location
    column = (event.button.x - base_x)/offset_x;
    row = (event.button.y - base_y)/offset_y;

    if ((grid[row][column].empty()) || ((grid[row][column].front()->getType() == ZOMBIE))) {
            grid[row][column].push_front (new Wallnut(column));
        ShopItem[WALLNUT].clicked = false;
        sunCurrency -= ShopItem[WALLNUT].cost;

    }
}

bool ItemsInShop::mouseOver(){
    int mouseX,mouseY;
    SDL_GetMouseState(&mouseX,&mouseY);
    return ( (mouseX > x) && (mouseX < sideX) &&
             (mouseY > y) && (mouseY < bottomY));
}

bool World::canAfford(ItemsInShop item){
return (sunCurrency >= item.cost);
}
