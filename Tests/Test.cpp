#include "Test.hpp"
#include <iostream>

unsigned int Test::nb_testcases = 0;

// =======  CONSTRUCTOR / DESTRUCTOR =======
Test::Test(string name):
name(name), nb_asserts(0), nb_checks(0), nb_failed_checks(0) {
    nb_testcases++;
}
Test::~Test() {
    if(this->nb_failed_checks == 0) {
        cout << "Test case [" << this->name << "] PASSED with " <<
            this->nb_checks << " checks and " << this->nb_asserts << " asserts."
            << endl;
    } else {
        cout << "Test case [" << this->name << "] has " << this->nb_failed_checks
            << "/" << this->nb_checks << " FAILED checks and " << this->nb_asserts
            << " asserts passed." << endl;
    }
}



// =======  GETTERS / SETTERS =======
unsigned int Test::getNbTestCases(void) {
    return Test::nb_testcases;
}



// =======  OTHER FUNCTIONS =======
int Test::assert(bool test_result) {
    this->nb_asserts++;

    if(!test_result) {
        cout << "Test case [" << this->name << "] failed at Assert " <<
            this->nb_asserts << ". Exiting program..." << endl;
        exit(1);
    }
    return 0;
}

int Test::check(bool test_result) {
    this->nb_checks++;

    if(!test_result) {
        this->nb_failed_checks++;
        cout << "Test case [" << this->name << "] failed at Check " <<
            this->nb_checks << "." << endl;
        return 1;
    }
    return 0;
}
