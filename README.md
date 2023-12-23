# C++ Project : Logic gates simulator
The aim of this project is to create a logic gate simulator that takes as input a DOT file describing the logic circuit and a WaveJSON file describing the input stimuli. The final output will be a WaveJSON file of the simulation results. The WaveJSON is a simplified JSON of [WaveDrom](https://wavedrom.com/).

## Building
### Requirements
- C++11: We developed the program using C++11. This is also the case of the JSON library we use ([RSJp-cpp](https://github.com/subh83/RSJp-cpp)) 

### Simulator
If you want to use the simulator, you simply need to use make :
```bash
make
```
This will generate a `run_simulator`executable.

### Tests
You can run the several tests we wrote, for this you must build them thanks to our make file. We have 4 test benches :
- `test_dot`: which tests the Dot's lexer and parser
- `test_json`: which tests the JSON part which process the WaveJSON
- `test_simulator`: which test the several functions of the simulator
- `test_all`: which combines Dot and JSON files to check the whole program behaviour

Each testbench has it's own Make rule, you can simply run `make <test>`. For example: `make test_json`. This will generate an executable in the `output` folder. You can now run the tests with `./output/<test>` for example: `./output/test_json`.

## Usage
You can also find these information with the `-h` option:
```bash
./run_simulator -h
```

Command to run a simulation:
```bash
./run_simulator <-j json_file> <-d dot_file> <-o output_file> [-f] [-i max_iteration] [-a output ...] [-v verbose_level]
```
*<>: mandatory options* *\[\]: optional options*

### Example
```bash
./run_simulator -j full_adder.json -d full_adder.dot -o full_adder_simu.json -f -a A -a B -a C_in -v 4 -i 20
```

This example will simulate the full_adder circuit with his stimuli and print the result in `full_adder_simu.json`. If the output file already exist, it will be overwritten (`-f`). In addition to the circuit outputs, we will save to output JSON the specified signals A, B and C_in (`-a` options).

### Options
- `--help`/`-h`: Print the command usage.
- `--json`/`-j`: Specifies the path to the WaveJSON file, containing the input signals.
- `--dot`/`-d`: Specifies the path to the Dot file, containing the circuit.
- `--output`/`-o`: Specifies the output WaveJSON file, containing the output signals (and additional signals if `--add`option specified).
- `--force`/`-f`: Overwrite the output file if it already exists. The simulator will throw an error if the output file already exists and this option is not specified.
- `--add`/`-a`: Allows to add an non output signal to the output WaveJSON. This option might be specified several times.
- `--verbose`/`-v`: Changes the verbose level (from `0` only fatal error to `5` debug messages). Default is 4.
- `--iteration`/`-i`:  Set the max number of iteration with loop. Default is `20`.

## Credit
### Authors
CASENOVE Raphaël ([@RafaC66](https://github.com/RafaC66)) - LUITOT Adrien ([@adrienluitot](https://github.com/adrienluitot)) - TALARMAIN Arthur ([@Arthuuuuroo](https://github.com/Arthuuuuroo))

### Used Libraries
- [RSJp-cpp](https://github.com/subh83/RSJp-cpp): A very simple JSON parser