#include <cctype>
#include <memory>

#include "preprocessor.hpp"

std::string
Shell::Preprocessor::unfold(
        const Environment *env,
        const std::string &line)
{
    QuoteParser quote_parser;

    std::string result_line = "";
    auto pos = line.begin();
    while (pos != line.end()) {
       quote_parser.update(*pos);     
    
       if (!quote_parser.is_quote() && *pos == '$') {
            auto unfold_begin = pos;
           
            ++pos;
            // Variable name can begin with letter or underscore
            if (pos != line.end() && (isalpha(*pos) || *pos == '_')) {
                // All another chars could be numeric as well
                while (pos != line.end() && (isalnum(*pos) || *pos == '_')) {
                    ++pos;
                }

                auto variable = std::string(unfold_begin + 1, pos);
                if (env->find(variable) != env->end()) {
                    result_line += env->at(variable);
                } else {
                   result_line += '$' + variable;
                }
            } 
        } else {
           result_line += *pos;
           ++pos;
        }
    }

    return result_line;
}
