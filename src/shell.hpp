#include <iostream>
#include <memory>

namespace Shell {
/**
 *
 *
 */
class CommandShell {
private:
    /** Console input stream */
    std::istream &in;

    /** Console output stream */
    std::ostream &out;

    /** Console error stream */
    std::ostream &err;

    /** Console environment variables */
    std::unique_ptr<Environment> env;
public:
    /** Creates new instance of CommandShell 
     *  
     *  @param in Console input stream
     *  @param out Console output stream
     *  @param err Console error stream
     */
    CommandShell(std::istream &in, std::ostream &out, std::ostream &err);    

    /**
     * Launches console
     */
    void start();
};
}
