#ifndef _JSON_H_
#define _JSON_H_

#include "RSJparser.tcc"
#include <regex>
#include <set>
#include <vector>
#include <fstream>
#include <iostream>
#include <cctype>
#include <algorithm>
#include "Signals.hpp"

using namespace std;

enum JsonErrorCodes { SUCCESS, FILE_READ_ERROR, INTEGRITY_ERROR, NB_SIGNAL_ERROR, PREPARE_ERROR, SIMPLIFY_ERROR};

class Json {

    private:
        JsonErrorCodes error_code;

        string file_path;
        RSJresource *json_dict;
        vector<RSJresource> json_clean_array;
        Signals *signals;

    public:
        // =======  CONSTRUCTOR / DESTRUCTOR =======
        Json(string file_path);
        ~Json();



        // =======  GETTERS / SETTERS =======
        JsonErrorCodes getErrorCode(void) const;

        const string& getFilePath(void) const;
        int setFilePath(string& new_file_path);

        RSJresource* getJsonDict(void) const;

        vector<RSJresource> getJsonCleanArray(void) const;
        void eraseJsonCleanArray(void);

        Signals* getSignals(void) const;
        int setSignals(Signals *new_signals);



        // =======  OTHER FUNCTIONS =======

        /** @brief Vérifie qu'il y a les éléments minimum au wavedrom **/
        int assertJsonIntegrity(void);

        /** @brief Stock le json dans le vector `json_clean_array` sans tous les 
         * éléments inutiles **/
        void simplifyJson(RSJresource &array);

        /** @brief Vérifie les durée de clock de tous les signaux, and prepare
         * signals for the simulator **/
        int consistencyAndPrepare(void);

        /** @brief Simplifie les valeurs des signaux pour la simulation et les
         * ajoute à `signals`. **/
        int simplifyWaves(void);

        /** @brief Sauvegarde le fichier json à partir d'une map de stimuli. **/
        static int printJson(const string& file_path, set<Stimulus*> stimuli);

};

#endif
