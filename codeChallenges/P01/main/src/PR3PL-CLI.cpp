#include <cassert>
#include <cstring>

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

#include <iostream>
#include <string>
#include <string_view>

#include <readline/readline.h>
#include <readline/history.h>

#include <PR3PL.hpp>

#define GREEN std::string{"\e[32m"}
#define RED std::string{"\e[31m"}
#define GREEN_BOLD std::string{"\e[1;92m"}
#define RED_BOLD std::string{"\e[1;91m"}
#define COLOR_OFF std::string{"\e[0m"}

std::string get_input_prompt(size_t i)
{
    return GREEN + "Input [" + GREEN_BOLD + std::to_string(i) + GREEN + "]:" + COLOR_OFF + " ";
}

std::string get_output_prompt(size_t i)
{
    return RED + "Output[" + RED_BOLD + std::to_string(i) + RED + "]:" + COLOR_OFF + " ";
}

std::string get_error_prompt(const std::string& error_type)
{
    return RED 
        + "-------------------------------------------------------------------------------"
        + '\n' + error_type + COLOR_OFF + ": ";
}

std::string_view trim(std::string_view str)
{
    size_t start = 0;
    size_t end = str.size();

    while (start < end && std::isspace(str[start]))
    {
        ++start;
    }

    while (end > start && std::isspace(str[end - 1]))
    {
        --end;
    }

    return str.substr(start, end - start);
}

char* words_generator(const char* text, int state)
{
    static int list_index, len;
    const char* name;

    if (!state)
    {
        list_index = 0;
        len = strlen(text);
    }

    static const char* words[] = {
        "isunit",
        "pair",
        "fst",
        "snd",
        "iflesser",
        "val",
        "var",
        "let",
        "fun",
        "call",
        "+",
        "-",
        "*",
        "/",
        "%",
        "exit",
        nullptr
    };

    while ((name = words[list_index++]))
    {
        if (strncmp(name, text, len) == 0)
        {
            return strdup(name);
        }
    }

    return nullptr;
}

char** completion(const char* text, int start, int end)
{
    rl_attempted_completion_over = 1;
    return rl_completion_matches(text, words_generator);
}

int main()
{
    std::cout << "Command Line Interface for PR3 Programming Language\n"
              << "If yo want to quit, type exit and enter or press ctrl+D\n\n";

    rl_attempted_completion_function = completion;

    size_t counter = 1;

    Environment env;

    while (true)
    {
        std::string prompt = get_input_prompt(counter);

        char* line = readline(prompt.c_str());

        if (line == nullptr)
        {
            break;
        }

        std::string prog = line;

        free(line);

        if (trim(prog) == "exit")
        {
            break;
        }

        std::shared_ptr<Expression> expression = nullptr;

        try
        {
            expression = Parser::parse(prog);
            auto result = expression->eval(env);
            std::cout << get_output_prompt(counter) + result->to_string() << "\n\n";
            ++counter;
            add_history(prog.c_str());
        }
        catch (const BadProgram& e)
        {
            std::cerr << get_error_prompt("Error parsing expression") << e.what() << "\n\n";
        }
        catch (const TypeError& e)
        {
            std::cerr << get_error_prompt("Type error") << e.what() << "\n\n";
        }
        catch (const NotFoundError& e)
        {
            std::cerr << get_error_prompt("Not found error") << e.what() << "\n\n";
        }
        catch (const std::exception& e)
        {
            std::cerr << get_error_prompt("Unknown error") << e.what() << "\n\n";
        }
    }

    return 0;
};
