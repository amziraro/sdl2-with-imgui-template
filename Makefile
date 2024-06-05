CC =  gcc
CXX = g++

TARGET = tri
PLATFORM = LINUX

# Need a working Linux build for -fsanitize=address,undefined
# -Wdouble-promotion -Wconversion -fanalyzer -Wstrict-prototypes -Wmissing-prototypes
# Because slow -pedantic -fanalyzer -fanalyzer-transitivity

CFLAGS = -g3 -Wall -Wextra -Wshadow -Wvla -pedantic -isystem /usr/include/SDL2 -D_REENTRANT -isystem ./3rdParty/imgui -isystem ./3rdParty/imgui/backends -isystem ./3rdParty/
LDFLAGS = -lSDL2 -fuse-ld=mold

IMGUI_OBJ = 3rdParty/imgui/imgui.o 3rdParty/imgui/imgui_demo.o 3rdParty/imgui/imgui_draw.o 3rdParty/imgui/backends/imgui_impl_sdl2.o 3rdParty/imgui/backends/imgui_impl_sdlrenderer2.o 3rdParty/imgui/imgui_tables.o 3rdParty/imgui/imgui_widgets.o

OBJ = src/main.o $(IMGUI_OBJ)

%.o: %.cpp
	$(CXX) -c -o $@ $< $(CFLAGS)
	
bin/$(TARGET)$(SUF): $(OBJ)
	$(CXX) $(OBJ) $(CFLAGS) $(LDFLAGS) -o $(TARGET)

clean:
	$(RM) tri
	$(RM) src/*.o
	$(RM) 3rdParty/imgui/*.o
	$(RM) 3rdParty/imgui/backends/*.o

