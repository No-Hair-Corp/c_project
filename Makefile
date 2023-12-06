
output/Test.o:
	g++ -c Tests/Test.cpp -o output/Test.o

output/test_dot: output/Test.o
	g++ -c Tests/test_dot.cpp -o output/test_dot.o

tests: output/test_dot
	g++ output/Test.o output/test_dot.o -o output/test

clean:
	rm -rf output/*