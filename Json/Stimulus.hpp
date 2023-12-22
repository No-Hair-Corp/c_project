#ifndef _STIMULUS_H_
#define _STIMULUS_H_

#include <fstream>
#include <iostream>

using namespace std;

class Stimulus {
    private:

        string name;
        string value;

    public:
        // =======  CONSTRUCTOR / DESTRUCTOR =======
        Stimulus(string name, string value);
        ~Stimulus();


        // =======  GETTERS / SETTERS =======
        string getName(void) const;
        void setName(string &name);
        
        string getValue(void) const;
        void setValue(string &value);

};

#endif
