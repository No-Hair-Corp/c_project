# VARIABLES
OPTIONS = -g -std=c++11

SRC_DIRS = Dot Simulator Tests Json
SRCS = $(shell find $(SRC_DIRS) -name "*.cpp")

GLOBAL_OBJS = $(addprefix output/, Help.o)
DOT_OBJS = $(addprefix output/, SchematicObject.o Token.o Dot.o)
JSON_OBJS = $(addprefix output/, Json.o Signals.o Stimulus.o)
SIMULATOR_OBJS = $(addprefix output/, Simulator.o Gate.o Stimulus.o)
GATES_OBJS = $(addprefix output/, $(patsubst %.hpp, %.o, $(notdir $(wildcard Simulator/Gates/*.hpp))))

# all
all: output/main.o $(SIMULATOR_OBJS) $(GATES_OBJS) $(JSON_OBJS) $(DOT_OBJS) $(GLOBAL_OBJS)
	g++ $(OPTIONS) $? -o run_simulator

# UTILS 
output/%.o: %.cpp
	@mkdir -p output
	g++ $(OPTIONS) -c $< -o $@

output/%.o: Help/%.cpp
	@mkdir -p output
	g++ $(OPTIONS) -c $< -o $@

output/%.o: Dot/%.cpp
	@mkdir -p output
	g++ $(OPTIONS) -c $< -o $@

output/RSJparser.o: Json/RSJparser.tcc
	@mkdir -p output
	g++ $(OPTIONS) -c $< -o $@

output/%.o: Json/%.cpp
	@mkdir -p output
	g++ $(OPTIONS) -c $< -o $@

output/%.o: Simulator/%.cpp
	@mkdir -p output
	g++ $(OPTIONS) -c $< -o $@

output/%.o: Simulator/Gates/%.cpp
	@mkdir -p output
	g++ $(OPTIONS) -c $< -o $@

output/%.o: Tests/%.cpp
	@mkdir -p output
	g++ $(OPTIONS) -c $< -o $@


# RULES
test_dot: output/test_dot.o output/Test.o $(DOT_OBJS) $(GLOBAL_OBJS)
	g++ $(OPTIONS) $? -o output/test_dot

test_json: output/test_json.o output/Test.o $(JSON_OBJS) $(GLOBAL_OBJS)
	g++ $(OPTIONS) $? -o output/test_json

test_simulator: output/test_simulator.o output/Test.o $(SIMULATOR_OBJS) $(GATES_OBJS) $(JSON_OBJS) $(DOT_OBJS) $(GLOBAL_OBJS)
	g++ $(OPTIONS) $? -o output/test_simulator

test_all: output/test_all.o output/Test.o $(SIMULATOR_OBJS) $(GATES_OBJS) $(JSON_OBJS) $(DOT_OBJS) $(GLOBAL_OBJS)
	g++ $(OPTIONS) $? -o output/test_all

clean:
	rm -rf output/* run_simulator
