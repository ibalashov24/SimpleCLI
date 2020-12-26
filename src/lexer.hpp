#include <vector>
#include <string>

namespace Shell {
class Lexer {
public:
    /**
     * Separates given string into vector of lexems.
     *
     * @param line Line to be handled.
     * @returns Vector of lexems.
     */
    static std::vector<std::string> handle_line(const std::string &line);
};
}
