#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <optional>
#include <ostream>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>

enum class TokenType {
    RETURN,
    INT_LITERAL,
    SEMICOLON,
};

struct Token {
    TokenType type;
    std::optional<std::string> value;
};

std::vector<Token> tokenize(std::string_view str_view) {
    for (char chr : str_view) {
        std::cout << chr << "\n";
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Error: Missing source code."
                  << "\n";
        return EXIT_FAILURE;
    }

    std::string source_code = argv[1];
    std::cout << "Compile file: " << source_code << "\n";

    if (!std::filesystem::exists(source_code)) {
        std::cerr << "Error: File not found.\n";
        return EXIT_FAILURE;
    }

    std::ifstream source_code_file(source_code);
    if (!source_code_file.is_open()) {
        std::cerr << "Error: Unable to open file.\n";
        return EXIT_FAILURE;
    }

    std::stringstream buffer;
    buffer << source_code_file.rdbuf();

    source_code_file.close();

    std::string contents = buffer.str();

    std::cout << "Filesize: " << contents.length() << "\n";

    std::string_view contents_view(contents.data(), contents.size());
    tokenize(contents_view);

    return EXIT_SUCCESS;
}
