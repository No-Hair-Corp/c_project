# VARIABLES
OPTIONS = "-std=c++0x"

SRC_DIRS = Dot Simulator Tests Json
SRCS = $(shell find $(SRC_DIRS) -name "*.cpp")

DOT_OBJS = $(addprefix output/, SchematicObject.o Token.o Dot.o)
JSON_OBJS = $(addprefix output/, Json.o Signals.o Stimulus.o)


# UTILS 
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

output/%.o: Tests/%.cpp
	@mkdir -p output
	g++ $(OPTIONS) -c $< -o $@


# RULES
tests: output/test_dot.o output/Test.o $(DOT_OBJS)
	g++ $(OPTIONS) $? -o output/test_dot 

test_json: output/test_json.o $(JSON_OBJS)
	g++ $(OPTIONS) $? -o output/test_json

clean:
	rm -rf output/*
