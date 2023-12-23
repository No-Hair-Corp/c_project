#ifndef _HELP_H_
#define _HELP_H_

#include <map>
#include <iostream>

using namespace std;

enum debug_part { TEST_DEBUG, GENERAL_DEBUG, JSON_DEBUG, DOT_DEBUG, SIMULATOR_DEBUG };
enum debug_level { FATAL_ERROR_DEBUG, ERROR_DEBUG, WARNING_DEBUG, INFO_DEBUG, SUCCESS_DEBUG, DEBUG_DEBUG  };

class Help {

    private:
        static debug_level verbose_level;
        static map<debug_level, string> debug_level_color;
        static map<debug_level, string> debug_level_text;
        static map<debug_part, string> debug_part_text;


    public:
        // =======  CONSTRUCTOR / DESTRUCTOR =======
        // Help(); // no need for real constructor, pure virtual
        virtual ~Help() = 0;



        // =======  GETTERS / SETTERS =======
        static void setVerboseLevel(debug_level level);
        static debug_level getVerboseLevel(void);



        // =======  OTHER FUNCTIONS =======
        static void debug(debug_part part, debug_level level, string message);

};

#endif
