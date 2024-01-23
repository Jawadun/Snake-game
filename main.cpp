#include <SDL2/SDL.h>
#include <iostream>
#include<vector>
#include<algorithm>
#include<deque>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>

using namespace std;
int dir = 0;
int run = 1;
int snakeSize = 20;
int score = 0, High, c=0; 
bool img = true;
deque <SDL_Rect> rq;
vector<SDL_Rect> food;
vector<SDL_Rect> Bonus;
SDL_Rect head {400,300,20,20};


SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
TTF_Font *font = nullptr;
Mix_Music* bgm;

int initializeWindow() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        cerr << "SDL initialization error: " << SDL_GetError() << endl;
        return 0;
    }

    TTF_Init();
    Mix_Init(MIX_INIT_MP3);
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 1, 1024);
    bgm = Mix_LoadMUS("bgm.mp3");
    
    window = SDL_CreateWindow(NULL , SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_BORDERLESS);
    if (!window) {
        cerr << "Error creating SDL window: " << SDL_GetError() << endl;
        return 0;
    }

    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer) {
        cerr << "Error creating renderer: " << SDL_GetError() << endl;
        return 0;
    }
    SDL_Rect initialFoodRect{rand() % 750, rand() % 550, 20, 20};
    food.emplace_back(initialFoodRect);
    
    return 1;
}
void startscreen()
{
    IMG_Init(IMG_INIT_JPG);
    SDL_RenderClear(renderer);
    SDL_Surface* imgS = IMG_Load("start.jpg");
    if(imgS == NULL) cout << SDL_GetError() << endl;
    SDL_Texture* imgTex = SDL_CreateTextureFromSurface(renderer, imgS);
    if(imgTex == NULL) cout << SDL_GetError() << endl;
    SDL_RenderCopy(renderer, imgTex, NULL, NULL);
    SDL_RenderPresent(renderer);
}
void gOverScreen() {

    IMG_Init(IMG_INIT_JPG);
    SDL_RenderClear(renderer);
    SDL_Surface* imgS = IMG_Load("bg.jpg");
    if(imgS == NULL) cout << SDL_GetError() << endl;
    SDL_Texture* imgTex = SDL_CreateTextureFromSurface(renderer, imgS);
    if(imgTex == NULL) cout << SDL_GetError() << endl;
    SDL_RenderCopy(renderer, imgTex, NULL, NULL);
    SDL_RenderPresent(renderer);
    SDL_Delay(2000);
}

void processInput() {
    SDL_Event event;
    SDL_PollEvent(&event);

   switch(event.type)
	{
		case SDL_QUIT:
		run = 0;
		break;
		case SDL_KEYDOWN:
		if(event.key.keysym.sym == SDLK_ESCAPE)
		run = 0;
		if(event.key.keysym.sym==SDLK_UP)
	 {
           if(dir!=2){ dir = 1;
		}
     }
		if(event.key.keysym.sym==SDLK_DOWN)
		{
            if(dir!=1){
            dir = 2;
		}
        }
		if(event.key.keysym.sym==SDLK_LEFT)
		{
            if(dir!=4)
            {
            dir = 3;
		}
        }
		if(event.key.keysym.sym==SDLK_RIGHT)
		{
            if(dir!=3)
            {
            dir = 4;
		}
        }
        if(event.key.keysym.sym==SDLK_RETURN)
        {
            img = false;
        }
		break;
	}
    
   
}

void update() {
    if(dir ==4)
    {
    head.x++;
    
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(renderer, &head);
    SDL_Delay(5);
    }
    if(dir ==3)
    {
    head.x--;
    
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(renderer, &head);
    SDL_Delay(5);
    }
    if(dir ==2)
    {
    head.y++;
    
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(renderer, &head);
    SDL_Delay(5);
    }
    if(dir ==1)
    {
    head.y--;
    
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(renderer, &head);
    SDL_Delay(5);
    }
   for (auto it = food.begin(); it != food.end(); ) {
        if (head.x < it->x + it->w &&
            head.x + head.w > it->x &&
            head.y < it->y + it->h &&
            head.y + head.h > it->y) {
            ::snakeSize += 20;
            score ++;
            c+= 1;

            if (score != 0 && score % 7 == 0) {
                ::snakeSize += 40;
                score += 10;

                
                SDL_Rect newBonusRect{rand() % 780, rand() % 580, 40, 40};
                Bonus.emplace_back(newBonusRect);
            }

            it = food.erase(it);
            SDL_Rect newFoodRect{rand() % 780, rand() % 580, 20, 20};
            food.emplace_back(newFoodRect);
        } else {
            ++it;
        }
    }
    for (auto it = Bonus.begin(); it != Bonus.end(); ) {
        if (head.x < it->x + it->w &&
            head.x + head.w > it->x &&
            head.y < it->y + it->h &&
            head.y + head.h > it->y) {
            ::snakeSize += 40;
            score += 10;

            it = Bonus.erase(it);

        } else {
            ++it;
        }
    }


    


for_each(rq.begin(), rq.end(), [&](auto &snake_segment) {
    if (head.x == snake_segment.x && head.y == snake_segment.y) {
        ::snakeSize = 20; 
        head.x = 400;
        head.y = 300;
        dir = 0;
        if(score!=0)
          gOverScreen();
    }

});
for (auto it = food.begin(); it != food.end(); ) {
        if (score!=0 && score%7 ==0) {
         
            
            it = food.erase(it);
            SDL_Rect newFoodRect{rand() % 780, rand() % 580, 40, 40};
            food.emplace_back(newFoodRect);
        } else {
            ++it;
        }
    }
    SDL_Rect wallRect1{300, 200, 20, 200};
    SDL_Rect wallRect2{300, 200, 200, 20};
    SDL_Rect wallRect3{500, 200, 20, 200};

    if (head.x < wallRect1.x + wallRect1.w &&
        head.x + head.w > wallRect1.x &&
        head.y < wallRect1.y + wallRect1.h &&
        head.y + head.h > wallRect1.y) {
        ::snakeSize = 20;
        head.x = 400;
        head.y = 300;
        dir = 0;
        cout << " Score: " << score << endl;
        if(High < score)
        {
            High = score;
        }
        cout << "High score: " << High << endl;
        score = 0;
        gOverScreen();
    }

    if (head.x < wallRect2.x + wallRect2.w &&
        head.x + head.w > wallRect2.x &&
        head.y < wallRect2.y + wallRect2.h &&
        head.y + head.h > wallRect2.y) {
        ::snakeSize = 20;
        head.x = 400;
        head.y = 300;
        dir = 0;
        cout << " Score: " << score << endl;
         if(High < score)
        {
            High = score;
        }
        cout << "High score: " << High << endl;
         score = 0;
        gOverScreen();
    }

    if (head.x < wallRect3.x + wallRect3.w &&
        head.x + head.w > wallRect3.x &&
        head.y < wallRect3.y + wallRect3.h &&
        head.y + head.h > wallRect3.y) {
        ::snakeSize = 20;
        head.x = 400;
        head.y = 300;
        dir = 0;
        cout << " Score: " << score << endl;
         if(High < score)
        {
            High = score;
        }
        cout << "High score: " << High << endl;
         score = 0;
        gOverScreen();
    }
    for (auto it = food.begin(); it != food.end(); ) {
        bool collisionWithWall = false;

        if(it ->x >=780 || it->x <=20 || it->y >= 580 || it->y <=20)
        {
            collisionWithWall = true;
        }

    
        if (it->x < wallRect1.x + wallRect1.w &&
            it->x + it->w > wallRect1.x &&
            it->y < wallRect1.y + wallRect1.h &&
            it->y + it->h > wallRect1.y) {
            collisionWithWall = true;
        }

        if (it->x < wallRect2.x + wallRect2.w &&
            it->x + it->w > wallRect2.x &&
            it->y < wallRect2.y + wallRect2.h &&
            it->y + it->h > wallRect2.y) {
            collisionWithWall = true;
        }

        if (it->x < wallRect3.x + wallRect3.w &&
            it->x + it->w > wallRect3.x &&
            it->y < wallRect3.y + wallRect3.h &&
            it->y + it->h > wallRect3.y) {
            collisionWithWall = true;
        }


        if (collisionWithWall) {
            it = food.erase(it);
            SDL_Rect newFoodRect{rand() % 780, rand() % 580, 20, 20};
            food.emplace_back(newFoodRect);
        } else {
            ++it;
        }
    }
    for (auto it = Bonus.begin(); it != Bonus.end(); ) {
        if (score!=0 && score%7==0) { 
            
            it = Bonus.erase(it);
            SDL_Rect newFoodRect{rand() % 780, rand() % 580, 40, 40};
            Bonus.emplace_back(newFoodRect);
        } else {
            ++it;
        }
    }

if(head.x == 780 || head.x == 20 || head.y == 20 || head.y == 580)
{
    ::snakeSize = 20; 
        head.x = 400;
        head.y = 300;
        dir = 0;
         cout << " Score: " << score << endl;
          if(High < score)
        {
            High = score;
        }
        cout << "High score: " << High << endl;
          score = 0;
          gOverScreen();
}

rq.push_front(head);
while(rq.size() > snakeSize)
rq.pop_back();


}

void showScore() {
    font = TTF_OpenFont ("arial.ttf", 20);
    string scr = "Score: ";
    scr = scr + to_string(score);
    SDL_Surface* score = TTF_RenderText_Solid(font, scr.c_str(), {0, 0, 255});
    SDL_Texture* Score = SDL_CreateTextureFromSurface(renderer, score);
    SDL_Rect scrRect = {400-score->w/2, 0, score->w, score->h};
    SDL_RenderCopy(renderer, Score, NULL, &scrRect);
    //SDL_RenderPresent();
}

void render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    int borderWidth = 20;

    SDL_Rect topBorderRect{0, 0, 800, borderWidth};
    SDL_RenderFillRect(renderer, &topBorderRect);

    
    SDL_Rect bottomBorderRect{0, 600 - borderWidth, 800, borderWidth};
    SDL_RenderFillRect(renderer, &bottomBorderRect);

    
    SDL_Rect leftBorderRect{0, 0, borderWidth, 600};
    SDL_RenderFillRect(renderer, &leftBorderRect);

    SDL_Rect rightBorderRect{800 - borderWidth, 0, borderWidth, 600};
    SDL_RenderFillRect(renderer, &rightBorderRect);

    SDL_Rect wallRect1{300, 200, 20, 200};
    SDL_Rect wallRect2{300, 200, 200, 20};
    SDL_Rect wallRect3{500, 200, 20, 200};

    SDL_SetRenderDrawColor(renderer, 150, 150, 150, 255);
    SDL_RenderFillRect(renderer, &wallRect1);
    SDL_RenderFillRect(renderer, &wallRect2);
    SDL_RenderFillRect(renderer, &wallRect3);

    showScore();
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    for_each(food.begin(), food.end(), [&](auto &foodRect) {
        SDL_RenderFillRect(renderer, &foodRect);
    });
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    for_each(Bonus.begin(), Bonus.end(), [&](auto &foodRect) {
        SDL_RenderFillRect(renderer, &foodRect);
    });

    SDL_SetRenderDrawColor(renderer, 100, 200, 50, 255);
    for_each(rq.begin(), rq.end(), [&](auto &snake_segment) {
        SDL_RenderFillRect(renderer, &snake_segment);
    });
    
   
    

   
    SDL_RenderPresent(renderer);
}



void destroyWindow() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int main(int argc, char* argv[]) {
    run = initializeWindow();
    Mix_PlayMusic(bgm, -1);
   
    
    while (run) {
        processInput();
         while(img)
    {
         SDL_Event event;
    SDL_PollEvent(&event);

   switch(event.type)
	{
		case SDL_KEYDOWN:
        if(event.key.keysym.sym==SDLK_RETURN)
        {
            img = false;
        }
		break;
	}
 
        startscreen();
        
    }
        update();
        render();
    }
     

    destroyWindow();
    return 0;
}
