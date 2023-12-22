#ifndef _SCHEMATIC_OBJECT_H_
#define _SCHEMATIC_OBJECT_H_

#include <string>
#include <list>
#include <map>
#include <vector>
#include <iostream>

using namespace std;

class SchematicObject {
    private:
        string gate_type;
        string gate_id;
        map<string, string> inputList;
        vector<string> outputList;
        map<string, string> additionnalOptions;

    public:
        // =======  CONSTRUCTOR / DESTRUCTOR =======
        SchematicObject();
        SchematicObject(string gateID, string gateType);
        SchematicObject(string gateID, string gateType, map<string, string> additionnalOptions);
        ~SchematicObject();


        // =======  GETTER / SETTER =======
        /** @brief get the gate type
         * @return string: gate type **/
        string getGateType() const;

        /** @brief set the gate type
         * @param const string&: gate type **/
        void setGateType(const string& type);

        /** @brief get the gate iD
         * @return string: gate iD **/
        string getGateId() const;

        /** @brief set the gate iD
         * @param const string&: gate iD **/
        void setGateId(const string& id);

        /** @brief get the inputs list (map)
         * @return map<string, string>&: gate inputs list **/
        const map<string, string>& getInputs() const;

        /** @brief add input in the inputs list
         * @param const string&: key corresponding to the gate ID
         * @param const string&: input **/
        void addInputs(const string& key, const string& inputs);

        /** @brief get the outputs list (vector)
         * @return map<string, string>&: gate outputs list **/
        const vector<string>& getOutputs() const;

        /** @brief add output in the outputs list
         * @param const string&: key corresponding to the gate ID
         * @param const string&: output **/
        void addOutputs(const string& outputs);

        /** @brief get the additionnal options list (map)
         * @return map<string, string>&: gate additionnal options list **/
        const map<string, string>& getAdditionnalOptions() const;

        /** @brief add option in the options list
         * @param const string&: key corresponding to the gate ID
         * @param const string&: option **/
        void addAdditionnalOptions(const string& key, const string& options);

        /** @brief print object and his atrributs  **/
        void print();
};

#endif
