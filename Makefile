SHELL := pwsh.exe 
.SHELLFLAGS := -NoProfile -Command 

CXX := g++
CXXFLAGS := -Wall -std=c++11 -g
#  LINKER := -I ../header/ -L ../source/ -lraylib -lopengl32 -lgdi32 -lwinmm 

output:
	$(CXX) $(CXXFLAGS) main.cpp -o output.exe  

run: 
	start cmd "/c ; output & pause"

clean:
	rm *.o, output.exe