#include "lexer.hpp"
#include "quote_parser.hpp"

#include <algorithm>

std::vector<std::string> 
Shell::Lexer::handle_line(const std::string &line)
{
    QuoteParser quote_parser;

    std::vector<std::string> lexems;
    auto pos = line.begin();
    while (pos != line.end())
    {
        quote_parser.update(*pos); 

        pos = std::find_if_not(pos, line.end(), [](char c) { return c == ' '; }); 

        std::string lexem = "";
        bool is_found_equality = false;
        while (pos != line.end() && (*pos != ' ' || quote_parser.is_quote())) {
            // Handling assignment operator
            if (!quote_parser.is_quote() && *pos == '=' && !is_found_equality) {
                lexems.push_back(lexem);
                lexem = "";

                is_found_equality = true;
            }

            // Quote-part of the lexem is concatenared with 
            // other parts (like in real Bash)
            // Example: foo"bar"baz == foobarbaz
            if (!quote_parser.is_delimiter()) {
               lexem += *pos; 
            }       

            ++pos; 
            quote_parser.update(*pos);
        }
        if (!lexem.empty()) {
            lexems.push_back(lexem);
        }
    }

    return lexems;
}
