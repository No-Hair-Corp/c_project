#include "Test.hpp"

using namespace std;

int main() {

    Test tc1("testAND");
    tc1.check(1 == 3);
    tc1.assert(1 == 1);
}