#include <string>

#include "environment.hpp"

namespace Shell {
class Preprocessor {
public:
    /**
     *  Unfolds environment variables in given line.
     *
     *  @param env Pointer to the console environment.
     *  @param line Line to be handled.
     *  @returns Given line with all correct and defined variables unfolded.
     */
    static std::string unfold(
            const Environment *env, 
            const std::string &line);
};

}
