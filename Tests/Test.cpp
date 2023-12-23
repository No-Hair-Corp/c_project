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
        Help::debug(TEST_DEBUG, SUCCESS_DEBUG, "Test case [" + this->name + "] PASSED with "
            + to_string(this->nb_checks) + " checks and " + to_string(this->nb_asserts) + " asserts.");
    } else {
        Help::debug(TEST_DEBUG, ERROR_DEBUG, "Test case [" + this->name + "] has " + to_string(this->nb_failed_checks)
            + "/" + to_string(this->nb_checks) + " FAILED checks and " + to_string(this->nb_asserts)
            + " asserts passed.");
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
        Help::debug(TEST_DEBUG, ERROR_DEBUG,  "Test case [" + this->name + "] failed at Assert "
            + to_string(this->nb_asserts) + ". Exiting program...");
        exit(1);
    }
    return 0;
}

int Test::check(bool test_result) {
    this->nb_checks++;

    if(!test_result) {
        this->nb_failed_checks++;
        Help::debug(TEST_DEBUG, WARNING_DEBUG,  "Test case [" + this->name + "] failed at Check "
            + to_string(this->nb_checks) + ".");
        return 1;
    }
    return 0;
}
