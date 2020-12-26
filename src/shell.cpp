#include "shell.hpp"
#include "preprocessor.hpp"

Shell::CommandShell::CommandShell(
        std::istream &in,
        std::ostream &out,
        std::ostream &err) : 
    in(in), out(out), err(err)
{
    this->env = std::make_unique(new Environment());
}

void Shell::CommandShell::start()
{
    auto return_code = new ReturnCode();
    while (return_code.is_ok()) {
        std::string command_line;
        std::getline(this->in, command_line);
        
        auto commands_parsed = Parser::handle_lexems(
                                    Lexer::handle_line(
                                        Preprocessor::unfold(this->env.get(), command_line)));
        
        for (auto &command : commands_parsed) {
            return_code = command.execute(
                    this->env, 
                    this->in, 
                    this->out, 
                    this->err);
        }
    }
}
