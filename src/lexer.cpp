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

        if (quote_parser.is_quote()) {
            auto quote_begin = pos;
            // Handling quotes.
            pos = std::find_if(pos + 1, line.end(), [](const auto &e) 
                    {
                        quote_parser.update(*pos);
                        return !quote_parser.is_quote();
                    });
            
            // If quote has reached the end of line, assuming 
            // the quote is finished.
            if (pos == line.end()) {
                lexems.push_back(std::string(quote_begin, line.end()));
            } else {
                lexems.push_back(std::string(quote_begin, pos - 1));
            }

            ++pos;
        } else if (*pos == ' ') {
            ++pos;
        } else {
            auto lexem_begin = pos;
            // Position of equality sign (of assignment operation).
            auto equality_pos = line.end();

            while (pos != line.end() && (*pos != ' ' || quote_parser.is_open())) {
                if (!quote_parser.is_open() && *pos == '=') {
                   equality_pos = pos;
                }
    
                ++pos;
            }
    
            if (equality_pos != line.end()) {
                lexems.push_back(std::string(lexem_begin, equality_pos));
                lexems.push_back("=");
                lexems.push_back(std::string(equality_pos, pos));
            } else {
                lexems.push_back(std::string(lexem_begin, pos));
            }
        }
    }

    return lexems;
}
