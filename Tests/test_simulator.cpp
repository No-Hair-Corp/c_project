#include "Test.hpp"
#include "../Dot/SchematicObject.hpp"
#include "../Simulator/Simulator.hpp"
#include "../Simulator/Gates/Input.hpp"
#include "../Simulator/Gates/Output.hpp"
#include "../Simulator/Gates/Not.hpp"
#include "../Simulator/Gates/And.hpp"

using namespace std;

int main() {


    // A --|>o--+----\.
    //          | AND |--- Q
    // B -------+----/.


    // SchematicObject A_so();
    // A_so.setGateType("input");
    // SchematicObject U1_so();
    // SchematicObject Q_so();
    

    Stimulus A_values("A", "010x1101xx1");
    Input A(&A_values);

    Stimulus B_values("B", "10x00x1001x");
    Input B(&B_values);

    map<string, Gate*> U0_inputs;
    U0_inputs["in"] = &A;
    Not U0(&U0_inputs); // input -> A


    map<string, Gate*> U1_inputs;
    U1_inputs["i0"] = &U0;
    U1_inputs["i1"] = &B;
    And U1(&U1_inputs, 2); // input -> A


    map<string, Gate*> Q_inputs;
    Q_inputs["in"] = &U1;
    Output Q(&Q_inputs); // input -> U0

    string output, Ab;

    cout << "input A: " << A_values.getValue() << endl << endl;
    for(unsigned int i = 0; i < A_values.getValue().length(); i++) {
        int tmp, not_tmp;

        Q.getValue(i, &tmp);
        U0.getValue(i, &not_tmp);

        if(tmp == -1)
            output.push_back( 'x' );
        else
            output.push_back( tmp + '0' );
        
        if(not_tmp == -1)
            Ab.push_back( 'x' );
        else
            Ab.push_back( not_tmp + '0' );
    }
    cout << " Not  A: " << Ab << endl;
    cout << "input B: " << B_values.getValue() << endl;
    cout << " output: " << output << endl;





    return 0;
}