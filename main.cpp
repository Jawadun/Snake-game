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
int score = 0; 
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
    /* if (TTF_Init() != 0) {
        cerr << "SDL_ttf initialization error: " << TTF_GetError() << endl;
        SDL_Quit();
        return 0;
    }*/

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
    SDL_Rect initialFoodRect{rand() % 780, rand() % 580, 20, 20};
    food.emplace_back(initialFoodRect);
    /* font = TTF_OpenFont("path/to/your/font.ttf", 24);  // Provide the path to your TTF font
    if (!font) {
        cerr << "Error loading font: " << TTF_GetError() << endl;
        TTF_Quit();
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 0;
    }*/


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
        //score += 10; 
        head.x = 400;
        head.y = 300;
        dir = 0; 
    }

});
if(head.x == 800 || head.x == 0 || head.y == 0 || head.y == 600)
{
    ::snakeSize = 20; 
        head.x = 400;
        head.y = 300;
        dir = 0;
}
rq.push_front(head);
while(rq.size() > snakeSize)
rq.pop_back();

}
/*void renderText(const string &text, const SDL_Color &color, int x, int y) {
    SDL_Surface *surface = TTF_RenderText_Solid(font, text.c_str(), color);
    if (!surface) {
        cerr << "Error rendering text: " << TTF_GetError() << endl;
        return;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) {
        cerr << "Error creating texture from surface: " << SDL_GetError() << endl;
        SDL_FreeSurface(surface);
        return;
    }

    SDL_Rect textRect = {x, y, surface->w, surface->h};
    SDL_RenderCopy(renderer, texture, nullptr, &textRect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}*/

void render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    for_each(food.begin(), food.end(), [&](auto &foodRect) {
        SDL_RenderFillRect(renderer, &foodRect);
    });

    SDL_SetRenderDrawColor(renderer, 100, 200, 50, 255);
    for_each(rq.begin(), rq.end(), [&](auto &snake_segment) {
        SDL_RenderFillRect(renderer, &snake_segment);
    });
   /*   SDL_Color textColor = {255, 255, 255};
    string scoreText = "Score: " + to_string(score);
    renderText(scoreText, textColor, 10, 10);
*/
    SDL_RenderPresent(renderer);
}



void destroyWindow() {
   // TTF_CloseFont(font);
   // TTF_Quit();
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
