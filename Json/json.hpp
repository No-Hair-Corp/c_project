#ifndef _JSON_H_
#define _JSON_H_

#include "RSJparser.tcc"
#include <regex>
#include <set>
#include <vector>
#include <fstream>
#include <iostream>
#include <cctype>
#include "Signals.hpp"

using namespace std;

class Json {

    private:
        string file_path;
        RSJresource *json_dict;
        vector<RSJresource> json_clean_array;
        Signals *signals;

    public:
        // =======  CONSTRUCTOR / DESTRUCTOR =======
        Json(string file_path);
        ~Json();



        // =======  OTHER FUNCTIONS =======

        /** @brief Vérifie qu'il y a les éléments minimum au wavedrom **/
        void assertJsonIntegrity(void);

        /** @brief Stock le json dans la map `json_clean_array` sans tous les 
         * éléments inutiles **/
        void simplifyJson(RSJresource &array);

        /** @brief Vérifie les durée de clock de tous les signaux, and prepare
         * signals for the simulator **/
        int consistencyAndPrepare(void);

        /** @brief Simplifie les valeurs des signaux pour la simulation et les
         * ajoute à `signals`. **/
        int simplifyWaves(void);

};

#endif
