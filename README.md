# Projet C++ : Simulateur de porte logique

The aim of this project is to create a logic gate simulator that takes as input a DOT file describing the logic circuit and a JSON file describing our input stimuli. The final output will be a JSON file of the simulation results.

## Building

### Requirements
C++11

### Compilation

```bash
make
```
If you want to remove generated files, use :
```bash
make clean
```

## Usage

### Helper command

```bash
./run_simulator -h
```
### Run a simulation

```bash
./run_simulator -j `json_file` -d `dot_file` -o `output_file`
```
#### Simulation exemple

```bash
./run_simulator -j full_adder.json -d full_adder.dot -o full_adder_simu -f -add A B C_in 
```
This example will simulate the full_adder circuit with his stimuli and print the result in full_adder_simu. If the output file already exist, it will be overwritted (-f). In addition of the circuit outputs, we will print additionnal signals A, B and C_in (-a).

### Run test
```bash
./run_simulator ?????
```
## Authors

LUITOT Adrien\
CASENOVE Raphaël \
TALARMAIN Arthur