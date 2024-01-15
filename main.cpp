#include <SDL2/SDL.h>
#include <iostream>
#include<vector>
#include<algorithm>
#include<deque>
#include <SDL2/SDL_ttf.h>

using namespace std;
int dir = 0;
int run = 1;
int snakeSize = 20;
int score = 0, High = 0; 
deque<SDL_Rect> rq;
vector<SDL_Rect> food;
SDL_Rect head {400,300,20,20};


SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
TTF_Font *font = nullptr; 
int initializeWindow() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        cerr << "SDL initialization error: " << SDL_GetError() << endl;
        return 0;
    }

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
            dir = 1;
		}
		if(event.key.keysym.sym==SDLK_DOWN)
		{
            dir = 2;
		}
		if(event.key.keysym.sym==SDLK_LEFT)
		{
            dir = 3;
		}
		if(event.key.keysym.sym==SDLK_RIGHT)
		{
            dir = 4;
		}
		break;
	}
    
   
}

void update() {
    if(dir ==4)
    {
    head.x++;
    
    SDL_SetRenderDrawColor(renderer, 100, 200, 50, 255);
    SDL_RenderFillRect(renderer, &head);
    SDL_Delay(5);
    }
    if(dir ==3)
    {
    head.x--;
    
    SDL_SetRenderDrawColor(renderer, 100, 200, 50, 255);
    SDL_RenderFillRect(renderer, &head);
    SDL_Delay(5);
    }
    if(dir ==2)
    {
    head.y++;
    
    SDL_SetRenderDrawColor(renderer, 100, 200, 50, 255);
    SDL_RenderFillRect(renderer, &head);
    SDL_Delay(5);
    }
    if(dir ==1)
    {
    head.y--;
    
    SDL_SetRenderDrawColor(renderer, 100, 200, 50, 255);
    SDL_RenderFillRect(renderer, &head);
    SDL_Delay(5);
    }
   for (auto it = food.begin(); it != food.end(); ) {
        if (head.x < it->x + it->w &&
            head.x + head.w > it->x &&
            head.y < it->y + it->h &&
            head.y + head.h > it->y) {
            ::snakeSize += 20;
            score += 1; 
            
            it = food.erase(it);
            SDL_Rect newFoodRect{rand() % 780, rand() % 580, 20, 20};
            food.emplace_back(newFoodRect);
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
        
    }

});
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
}
rq.push_front(head);
while(rq.size() > snakeSize)
rq.pop_back();


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

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    for_each(food.begin(), food.end(), [&](auto &foodRect) {
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
    

    
    while (run) {
        processInput();
        update();
        render();
    }
     

    destroyWindow();
    return 0;
}
