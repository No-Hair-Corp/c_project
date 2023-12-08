SRC_DIRS = Dot Simulator Tests # Json
SRCS = $(shell find $(SRC_DIRS) -name "*.cpp")

DOT_OBJS = $(addprefix output/, SchematicObject.o Token.o Dot.o)


output/%.o: Dot/%.cpp
	@mkdir -p output
	g++ -c $< -o $@

output/%.o: Json/%.cpp
	@mkdir -p output
	g++ -c $< -o $@

output/%.o: Simulator/%.cpp
	@mkdir -p output
	g++ -c $< -o $@

output/%.o: Tests/%.cpp
	@mkdir -p output
	g++ -c $< -o $@

tests: output/test_dot.o output/Test.o $(DOT_OBJS)
	g++ $? -o output/test_dot 

clean:
	rm -rf output/*