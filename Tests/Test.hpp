#ifndef _TEST_H_
#define _TEST_H_

#include <string>
#include <map>
#include <vector>

using namespace std;

class Test {
    private:
        static unsigned int nb_testcases;

        string name;
        unsigned int nb_asserts;
        unsigned int nb_checks;
        unsigned int nb_failed_checks;

    public:
        // =======  CONSTRUCTOR / DESTRUCTOR =======
        Test(string name);
        ~Test();



        // =======  GETTERS / SETTERS =======

        /** @brief Renvoie le nombre de testcases créés
         * @return unsigned int: nombre de testcases créés **/
        static unsigned int getNbTestCases(void);



        // =======  OTHER FUNCTIONS =======

        /** @brief Incrémente le nombre d'assert du TC. Si le test est incorrect,
         * affiche une erreur et arrête le programme
         * @param bool test_result : résultat du test
         * @return int: 0 si pas d'erreur, 1 si erreur **/
        int assert(bool test_result);

        /** @brief Incrémente le nombre d'assert du TC. Si le test est incorrect,
         * affiche une erreur
         * @param bool test_result: résultat du test
         * @return int: 0 si pas d'erreur, 1 si erreur **/
        int check(bool test_result);
};

#endif