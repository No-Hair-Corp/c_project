#include "Help.hpp"

debug_level Help::verbose_level = WARNING_DEBUG;
map<debug_level, string> Help::debug_level_color = {
    {INFO_DEBUG, "1;37"},
    {WARNING_DEBUG, "1;33"},
    {ERROR_DEBUG, "1;31"},
    {FATAL_ERROR_DEBUG, "1;37;41"},
};
map<debug_level, string> Help::debug_level_text = {
    {INFO_DEBUG, "Info"},
    {WARNING_DEBUG, "Warning"},
    {ERROR_DEBUG, "Error"},
    {FATAL_ERROR_DEBUG, "Fatal Error"},
};
map<debug_part, string> Help::debug_part_text = {
    {GENERAL_DEBUG, "General"},
    {JSON_DEBUG, "JSON"},
    {DOT_DEBUG, "Dot"},
    {SIMULATOR_DEBUG, "Simulator"},
};


// =======  CONSTRUCTOR / DESTRUCTOR =======



// =======  GETTERS / SETTERS =======
void Help::setVerboseLevel(debug_level level) {
    Help::verbose_level = level;
}
debug_level Help::getVerboseLevel(void) {
    return Help::verbose_level;
}



// =======  OTHER FUNCTIONS =======
void Help::debug(debug_part part, debug_level level, string message) {
    cout << "[" << Help::debug_part_text[part] << "] ";
    cout << "\033[" << Help::debug_level_color[level] << "m" << Help::debug_level_text[level] << "\033[0m: ";
    cout << message << endl;
}