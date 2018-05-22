CXX=g++ -std=c++14
LDFLAGS=-Wall -O3 -pthread
CXXFLAGS=-Wall -c -O3 -pthread
BUILD_DIR=./build
PLAYERS=random_player/random_player.cpp human_player/human_player.cpp \
	minimax_player/minimax_player.cpp benchmark_player/benchmark_player.cpp \
	minimax_player_experiment/minimax_player_experimental.cpp
PLAYERS_PREFIX=players
SOURCES_DIR=srcs
SOURCES=$(addprefix $(SOURCES_DIR)/,main.cpp move.cpp game.cpp bitboard.cpp \
board.cpp utility.cpp game_worker.cpp argsparsing.cpp $(addprefix $(PLAYERS_PREFIX)/,$(PLAYERS)))
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
