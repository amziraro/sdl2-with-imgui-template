#include <SDL.h>

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cmath>

#include <imgui.h>
// This will have to change for mainline imgui
#include <imgui_impl_sdl2.h>
#include <imgui_impl_sdlrenderer2.h>

#include <nlohmann/json.hpp>
using json = nlohmann::json;

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

int main(int argc, char *argv[]) 
{
	argc = argc; 
	
	// SDL SETUP
	bool quit = false;
	SDL_Window * window = SDL_CreateWindow("Triangle Example", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI);
	if (window == nullptr)
	{
		printf("Error with SDL_CreateWindow(): %s\n", SDL_GetError());
		return 1;
	}
	
	SDL_Renderer * renderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED);
	if (renderer == nullptr)
	{
		printf("Error with SDL_CreateRenderer(): %s\n", SDL_GetError());
		return 2;
	}
	
	//SDL_RendererInfo info;
	//SDL_GetRendererInfo(renderer, &info);
	//SDL_Log("Current SDL_Renderer: %s", info.name);
	
	// Disable DPI stuff
	SDL_SetHint("SDL_VIDEO_HIGHDPI_DISABLED", "1");
	
	// IMGUI SETUP
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	// Setup Dear ImGui style
	ImGui::StyleColorsClassic();
	// Setup Platform/Renderer backends
	ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
	ImGui_ImplSDLRenderer2_Init(renderer);
	//io.FontGlobalScale = 2.0f;
	//ImGui::GetStyle().ScaleAllSizes(2.0f);
	//io.Fonts->AddFontFromFileTTF("./3rdParty/imgui/misc/fonts/DroidSans.ttf", 24);
	
	//std::ifstream infile(argv[1]);
	//json jin = json::parse(infile);
	
	// FPS Stuff;
	uint64_t oldtime = 0;
	uint64_t currenttime = 0;
	uint64_t frames = 0;
	uint64_t fixedupdate = 0;
	
	// Use this to lock the mouse to the screen
	//SDL_SetRelativeMouseMode(SDL_TRUE);
	
	uint64_t perf_now = SDL_GetPerformanceCounter();
	uint64_t perf_last = 0;
	double deltatime = 0;
	
	float mouse_x, mouse_y;
	
	const uint8_t * sdl_keymap = SDL_GetKeyboardState(nullptr);
	
	SDL_Event event;
	while (!quit)
	{
		// Deltatime - not my normal style but I got it from here:
		// https://gamedev.stackexchange.com/questions/110825/how-to-calculate-delta-time-with-sdl
		perf_last = perf_now;
		perf_now = SDL_GetPerformanceCounter();
		deltatime = (double)((perf_now - perf_last)*1000 / (double)SDL_GetPerformanceFrequency() );
		
		while(SDL_PollEvent(&event))
		{
			ImGui_ImplSDL2_ProcessEvent(&event);
			
			switch(event.type)
			{
				case SDL_QUIT: 
					quit = true;
				break;
				
				case SDL_MOUSEMOTION:
					if(!io.WantCaptureMouse)
					{
						mouse_x = event.motion.x;
						mouse_y = event.motion.y;
						
						if(event.motion.state == SDL_BUTTON_LMASK)
						{
							//camera.x += event.motion.xrel;
							//camera.y += event.motion.yrel;
						}
					}
				break;
			}
		}
		
		frames++;
		currenttime = SDL_GetTicks64();
		if(currenttime - oldtime > 1000)
		{
			printf("Frames in last second = %ld, avg frametime = %f\n", frames, (1000.0f / frames));
			oldtime = currenttime;
			frames = 0;
		}
		
		ImGui_ImplSDLRenderer2_NewFrame();
		ImGui_ImplSDL2_NewFrame();
		ImGui::NewFrame();

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		
		if(currenttime - fixedupdate > 10)
		{
			// 100Hz update
			
		}
		
		// render level geometry
					
		// render character
		
		// etc
		
		// render UI
		ImGui::ShowDemoWindow();
		
		ImGui::Render();
		SDL_RenderSetScale(renderer, io.DisplayFramebufferScale.x, io.DisplayFramebufferScale.y);
		ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), renderer);
		SDL_RenderPresent(renderer);
		//SDL_Delay(15);
	}
	
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	
	SDL_Quit();
	return 0;
}
