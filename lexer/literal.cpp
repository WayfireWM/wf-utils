#include "literal.hpp"

#include <stdexcept>
#include <string>
#include <variant>

literal_t::literal_t(const std::string &text) : type(type_t::STRING), value(text)
{
    // Deal with char literal
    if ((text.front() == '\'') && (text.back() == '\''))
    {
        char c = text.at(1);
        if (c == '\\')
        {
            if (text.size() != 4)
            {
                std::string error = "Literal parser error. Text could not be converted to char. text:";
                error.append(text);
                throw std::runtime_error(error);
            }

            switch (text.at(2))
            {
            case 'a': // bell
                c = '\a';
                break;
            case 'b': // backspace
                c = '\b';
                break;
            case 'e': // escape
                c = 0x1b;
                break;
            case 'f': // form feed
                c = '\f';
                break;
            case 'n': // newline
                c = '\n';
                break;
            case 'r': // carriage return
                c = '\r';
                break;
            case 't': // tab
                c = '\t';
                break;
            case 'v': // vertical tab
                c = '\v';
                break;
            case '\\': // backslash
                c = '\\';
                break;
            case '\'': // apostrophe
                c = '\'';
                break;
            case '\"': // quotation mark
                c = '\"';
                break;
            case '\?': // question mark
                c = '\?';
                break;
            }
        }
        else
        {
            if (text.size() != 3)
            {
                std::string error = "Literal parser error. Text could not be converted to char. text:";
                error.append(text);
                throw std::runtime_error(error);
            }
        }

        type = type_t::CHAR;
        value = c;
        return;
    }

    // Deal with boolean literal.
    if ((text == "true") || (text == "TRUE") || (text == "True"))
    {
        type = type_t::BOOL;
        value = true;
        return;
    }
    if ((text == "false") || (text == "FALSE") || (text == "False"))
    {
        type = type_t::BOOL;
        value = false;
        return;
    }

    // Deal with float or double here.
    if (text.find('.') != std::string::npos)
    {
        // Float or Double.
        if ((text.find('f') != std::string::npos) || (text.find('F') != std::string::npos))
        {
            // Float.
            try
            {
                type = type_t::FLOAT;
                value = std::stof(text);
                return;
            }
            catch (std::logic_error &)
            {
                std::string error = "Literal parser error. Text could not be converted to float. text:";
                error.append(text);
                throw std::runtime_error(error);
            }
        }
        else
        {
            // Double.
            try
            {
                type = type_t::DOUBLE;
                value = std::stod(text);
                return;
            }
            catch (std::logic_error &)
            {
                std::string error = "Literal parser error. Text could not be converted to double. text:";
                error.append(text);
                throw std::runtime_error(error);
            }
        }
    }

    // Assume literal will be an integer and test the assumption by looking at all characters.
    auto integer = true;
    auto first = true;
    for (const auto &c : text)
    {
        auto digit = std::isdigit(c);
        auto hyphen = (c == '-');

        if (first)
        {
            first = false;
            if (!(digit | hyphen))
            {
                integer = false;
                break;
            }
        }
        else
        {
            if (!(digit))
            {
                integer = false;
                break;
            }
        }
    }
    if (integer)
    {
        try
        {
            type = type_t::INT;
            value = std::stoi(text);
            return;
        }
        catch (std::logic_error &)
        {
            std::string error = "Literal parser error. Text could not be converted to int. text:";
            error.append(text);
            throw std::runtime_error(error);
        }
    }
}

std::string literal_t::to_string() const
{
    std::string out;
    out.append("Literal: type=");
    switch (type)
    {
    case type_t::INT:
        out.append("INT, value=[").append("int,").append(std::to_string(std::get<int>(value))).append("]");
        break;
    case type_t::BOOL:
        out.append("BOOL, value=[").append("bool,").append(std::to_string(std::get<bool>(value))).append("]");
        break;
    case type_t::CHAR:
        out.append("CHAR, value=[").append("char,").append(std::to_string(static_cast<int>(std::get<char>(value)))).append("]");
        break;
    case type_t::FLOAT:
        out.append("FLOAT, value=[").append("float,").append(std::to_string(std::get<float>(value))).append("]");
        break;
    case type_t::DOUBLE:
        out.append("DOUBLE, value=[").append("double,").append(std::to_string(std::get<double>(value))).append("]");
        break;
    case type_t::STRING:
        out.append("STRING, value=[").append("string,").append(std::get<std::string>(value)).append("]");
        break;
    }

    return out;
}
