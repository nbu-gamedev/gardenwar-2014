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
	sunImagePH = NULL;
	shopSprite = NULL;
	numbersSpite = NULL;
    game_over = NULL;
    Window = NULL;
    Background = NULL;
    ScreenSurface = NULL;
    peaSpeed = 0;
    peaDrawSpeed = 0;
    sunSpawnTime = 5; // it saves time whale testing, should be 15 change it if its bothering you.
    sunCurrency = 50;
    apply_surface_pointer = &World::apply_surface;
    //init the shop struct
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
}
void World::readData(){
    // zombie waves
    ifstream zombiesFile("../bin/data/zombieWave.txt");
    if (!zombiesFile.fail()){
        string s;
        while(getline(zombiesFile,s)){
            istringstream ss(s);
            int sec,pos;
            ss>>sec;
            char buf;
            ss>>buf; // ':' (??)
            while(ss>>pos){
                if (pos<=300) zombieWaves[sec].push_back(pos);
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
        peaDrawSpeed = peaSpeed/10;
    }
    peaFile.close();
}

void World::createWorld(){
    SDL_Init(SDL_INIT_EVERYTHING);
    readData();
    Window = SDL_CreateWindow("Plants Vs Zombies", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    ScreenSurface = SDL_GetWindowSurface(Window);
    Background = SDL_LoadBMP("../bin/media/background.bmp");
    game_over = SDL_LoadBMP("../bin/media/gameOver.bmp");
    SDL_BlitSurface(Background, NULL, ScreenSurface, NULL);
    SDL_UpdateWindowSurface(Window);
    sunImagePH = SDL_LoadBMP("../bin/media/sun.bmp");
    SDL_SetColorKey(sunImagePH, SDL_TRUE, SDL_MapRGB(sunImagePH->format, 255, 255, 255));
    if ( sunImagePH == NULL){ cout<<"Loading sun failed!!!"<< endl; }
    numbersSpite= SDL_LoadBMP("../bin/media/numberSpite.bmp");
    if ( numbersSpite == NULL){ cout<<"Loading numberSpite failed!!!"<< endl; }
    shopSprite= SDL_LoadBMP("../bin/media/shopSprite.bmp");
    if ( shopSprite == NULL){ cout<<"Loading shopSprite failed!!!"<< endl; }
    peaImagePH = SDL_LoadBMP("../bin/media/pea.bmp");
    SDL_SetColorKey(peaImagePH, SDL_TRUE, SDL_MapRGB(peaImagePH->format, 255, 255, 255));
    if ( peaImagePH == NULL){ cout<<"Error!/.../"<< endl; }
    Images.push_back(SDL_LoadBMP("../bin/media/Peashooter_attack.bmp"));
    SDL_SetColorKey(Images[0], SDL_TRUE, SDL_MapRGB(Images[0]->format, 255, 255, 255));
    Images.push_back(SDL_LoadBMP("../bin/media/Sunflower_animation.bmp"));
    SDL_SetColorKey(Images[1], SDL_TRUE, SDL_MapRGB(Images[1]->format, 255, 255, 255));
    Images.push_back(SDL_LoadBMP("../bin/media/Wallnut_animation.bmp"));
    SDL_SetColorKey(Images[2], SDL_TRUE, SDL_MapRGB(Images[2]->format, 255, 255, 255));
    Images.push_back(SDL_LoadBMP("../bin/media/Zombie_move_animation.bmp"));
    SDL_SetColorKey(Images[3], SDL_TRUE, SDL_MapRGB(Images[3]->format, 0, 255, 0 ) );
    Images.push_back(SDL_LoadBMP("../bin/media/Zombie_eat_animation.bmp"));
    SDL_SetColorKey(Images[4], SDL_TRUE, SDL_MapRGB(Images[4]->format, 255, 255, 255));
}

void World::destroyWorld(){
    SDL_DestroyWindow(Window);
    SDL_FreeSurface( game_over );
    SDL_FreeSurface(Background);
    SDL_FreeSurface(peaImagePH);
    SDL_FreeSurface(sunImagePH);
    for(unsigned int i=0; i<Images.size(); i++)
    {
        SDL_FreeSurface(Images[i]);
    }
}

void World::draw()
{
    SDL_BlitSurface(Background, NULL, ScreenSurface, NULL);

    for(int i=0; i<N; i++)
    {
        for(int j=0; j<M; j++)
        {
            for(it=grid[i][j].begin();it!=grid[i][j].end();it++)
            {
                {
                    (*it)->draw_self(j, i, Images[(*it)->getType()], ScreenSurface);
                }
            }
        }
    }
    // Samir's part:
    for (unsigned int currentSun = 0; currentSun < suns.size(); currentSun++){

        apply_surface(suns[currentSun]->getX(),suns[currentSun]->getY(),sunImagePH,ScreenSurface);
    }
    //using sprite sheet for the numbers 0-9
    SDL_Rect source;
    SDL_Rect destination;
    source.y = 0;
    source.w = 18;
    source.h = 20;
    destination.y = 20;
    int number;
    int digitNumber=0; // used to know witch digit we are getting from right to left.
    int sunCurrencyTMP = sunCurrency;
    //do loop extracts the right digit and prints it on the screen,
    //uses the remaining numbers to extra the right digit and to print it
    //left of the first digit extracted;
    do{
        number = sunCurrencyTMP % 10;
        source.x = 2+(16*number);
        destination.x = 1100-(18*digitNumber); // digits printed from right to left.
        digitNumber++;
        sunCurrencyTMP = sunCurrencyTMP / 10;

    SDL_BlitSurface(numbersSpite, &source, ScreenSurface, &destination);
    } while (sunCurrencyTMP>0);



    for (int i = 0; i < ALL_SHOP_ITEMS; i++){
        destination.x = ShopItem[i].x;
        source.x = 35+(70*i);
        destination.y = 15;
        source.y = 130;
        source.w = 65;
        source.h = 90;
        int x,y;
        SDL_GetMouseState(&x,&y);

        // if Shopitem[i] noMoney draw no money img
        if ( ShopItem[i].cost > sunCurrency ){
            source.y = 316;
        }
        // if shopitem[i] clicked 95%


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


	 //Kari:
	for(itPea=peas.begin();itPea!=peas.end();itPea++) {
		apply_surface(((*itPea)->x + (*itPea)->br), offset_y*((*itPea)->y)+gridStartY, peaImagePH, ScreenSurface);
		(*itPea)->br+=peaDrawSpeed;
    }
	// ----------

    SDL_UpdateWindowSurface(Window);
}

void World::update(int clock){

	for(itPea=peas.begin();itPea!=peas.end();itPea++) {
		(*itPea)->move(peaSpeed);
    }
	for(int i=0; i<N; i++){
		for(int j=0; j<M; j++){
		    it=grid[i][j].begin();
            while(it!=grid[i][j].end()){

		// --- vreme za umirane:
				if( (*it)->getHP() <=0){
					if((*it)->getAct()!=DIE) {(*it)->setAct(DIE);}
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
						enemy->addHP( -((*it)->getDamage()) );
						if( (*it)->getAct()!=ATTACK){
							(*it)->setAct(ATTACK);
						}
					}
					if(!flowerExists){
			//  2. stignalo e do kraq
						if(j==0){
							if ((*it)->timeToAct()){
								gameOver();
                                break;
							}
						}
			//  3. mesti se
						else {  //  j!=0

						// 3.1. dosega se e dvijelo; prodyljava dvijenie
							if( (*it)->timeToAct()) {
								(*it)->setAct(MOVE);
								grid[i][j-1].push_back((*it));
								it=grid[i][j].erase(it);
								continue; //za da prodylji s novata stoinost na it..
							}
						//3.2 dosega e atakuvalo
							else if ((*it)->getAct()!=MOVE){
								(*it)->setAct(MOVE);
								it++;
								continue; //za da ne increase-ne counter na (*it), ot 0 na 1 i da propusne stypka
							}
							else{}
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
                                if((*it)->getAct()==STAY || (*it)->timeToAct()){
                                    (*it2)->addHP(-((*it)->getDamage()) );
                                    if((*it)->getAct()!=ATTACK) {(*it)->setAct(ATTACK);}
                                }
                                break; // namerilo e enemy, spira da tyrsi
                            }
                        }
                        if(!zombieExists){
        // 2. tyrsi v predni kvadrat4eta i strelq
                            for(int k=j+1;(k<M);k++){
                                for(it2=grid[i][k].begin(); it2!=grid[i][k].end(); it2++){
                                    if ( ((*it2)->getType()==ZOMBIE) && ((*it2)->getAct()!=DIE) ){
                                        zombieExists =true;
                                        if((*it)->getAct()==STAY || (*it)->timeToAct()){
                                    // grah4eta
                                            peas.push_back(new Pea( (*it)->getPosX(), i, *it2 ));
                                    // --------
                                            (*it2)->addHP(-((*it)->getDamage()) );
                                            if((*it)->getAct()!=ATTACK) {(*it)->setAct(ATTACK);}
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
							suns.push_back(new Sun( (gridStartX+((j+1)*offset_x)-20),(gridStartY+((i+1)*offset_y)-SUN_SIZE) ));
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

		if ((*itPea)->enemyIsDead()) {(*itPea)->aim=NULL;}

		// ako: 1) grah4eto e stignalo zombito 2) grah4eto e stignalo do kraq na grida
		if ( (*itPea)->reachedAim() || ((*itPea)->getPlace() > M) ) {
			delete (*itPea);
			itPea=peas.erase(itPea);
		}
		else itPea++;
    }

    clock = (clock/1000)%300;
    if(!zombieWaves[clock].empty()){
        for(unsigned int i=0; i<zombieWaves[clock].size(); i++){
            grid[(zombieWaves[clock][i])][M-1].push_back(new Zombie());
        }
    }

}


void World::gameOver(){
    apply_surface(380, 190, game_over, ScreenSurface);
    SDL_UpdateWindowSurface(Window);
    SDL_Delay(1500);
    quit=true;
}

void World::apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination)
{
    SDL_Rect offset;
    offset.x = x;
    offset.y = y;
    SDL_BlitSurface( source, NULL, destination, &offset );
}

void World::createSun() {
    //placing new sun in the vector "suns" in world.
    suns.push_back(new Sun(rand() %gridSizeX + gridStartX , rand() %gridSizeY + gridStartY));
    cout << "Total suns: " << suns.size() <<  endl;
}

void World::createPeashooter(SDL_Event event){
    int row = 0;
    int column = 0;

    // Place Peashooter at clicked grid location
    column = (event.button.x - base_x)/offset_x;
    row = (event.button.y - base_y)/offset_y;
 //   cout << "column:" << column << " row:" << row << " address:"
 //   << grid[row][column] << endl; //6te mahna testovete kato sam naprava i Sun.

    if ((grid[row][column].empty()) || ((grid[row][column].front()->getType() == ZOMBIE))) {
            grid[row][column].push_front (new Peashooter(column));
        cout << "Placed new peashooter" << endl; //6te mahna testovete kato sam naprava i Sun.
    }
}

bool ItemsInShop::mouseOver(){
    int mouseX,mouseY;
    SDL_GetMouseState(&mouseX,&mouseY);
    if ( (mouseX > x) && (mouseX < sideX) &&
         (mouseY > y) && (mouseY < bottomY)){
        return true;
    }else
        return false;
}
