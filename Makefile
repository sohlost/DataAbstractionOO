CXX = g++
CXXFLAGS = -std=c++20 -Wall -I.

# Targets
TARGETS = assignment_usecase demo_functional demo_generic

all: $(TARGETS)

# Assignment Use Case
assignment_usecase: assignment_usecase.cpp
	$(CXX) $(CXXFLAGS) -o assignment_usecase assignment_usecase.cpp

# Demos
demo_functional: demo_containers_functional.cpp
	$(CXX) $(CXXFLAGS) -o demo_functional demo_containers_functional.cpp

demo_generic: demo_generic.cpp
	$(CXX) $(CXXFLAGS) -o demo_generic demo_generic.cpp

clean:
	rm -f $(TARGETS) main demo *.o

run: assignment_usecase
	./assignment_usecase

.PHONY: all clean run
