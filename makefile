CXX=g++ -std=c++14
LDFLAGS=-Wall -O3
CXXFLAGS=-Wall -c -O3
BUILD_DIR=./build
PLAYERS=random_player.cpp human_player.cpp minimax_player.cpp
PLAYERS_PREFIX=players
SOURCES=main.cpp move.cpp game.cpp bitboard.cpp board.cpp utility.cpp \
        $(addprefix $(PLAYERS_PREFIX)/,$(PLAYERS))
OBJECTS=$(SOURCES:%.cpp=$(BUILD_DIR)/%.o)
EXECUTABLE=pawnrace
DEPS = $(OBJECTS:.o=.d)

all: $(EXECUTABLE)

$(EXECUTABLE): $(BUILD_DIR)/$(EXECUTABLE)

$(BUILD_DIR)/$(EXECUTABLE): $(OBJECTS)
	@# Create build directories - same structure as sources.
	@mkdir -p $(@D)
	@# Just link all the object files.
	$(CXX) $(LDFLAGS) $^ -o $(EXECUTABLE)

-include $(DEPS)

$(BUILD_DIR)/%.o : %.cpp
	@mkdir -p $(@D)
	@# The -MMD flags additionaly creates a .d file with
	@# the same name as the .o file.
	$(CXX) $(CXXFLAGS) -MMD -c $< -o $@

clean:
	-rm $(OBJECTS) $(DEPS)
	-rm $(EXECUTABLE)
