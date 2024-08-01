# include <iostream>
# include <fstream> 
# include <sstream>
# include <string>
# include <vector>

// Protoyping
void runFile(std::string file_path);
inline std::string slurp (const std::string& path);
void runPrompt();
void run(std::string source);
void report(int line, std::string where, std::string message);
void error(int line, std::string message);

// glob var
bool hadError = false;

int main(int argc, char** argv){

    if (argc > 2){
        std::cout << "Usage Glyphcast <Source_File>" << std::endl;
        exit(64);
    }
    else if (argc == 2){
        // TODO: check for the extension
        runFile(argv[1]);
    }
    else{
        runPrompt();
        return 0;
    }
    return 0;
}

void run(std::string source){
    // scanner class needed
    Scanner scanner {source};
    std::vector<Token> tokens = scanner.scanTokens();

    for (/* every token in tokens */){
        std::cout << "print every token" << std::endl;
    }
}

void error(int line, std::string message){
    report(line, "", message);
}

void report(int line, std::string where, std::string message){
    std::cerr << "[line " <<  line << "] Error" << where << ": " << message << std::endl;
    hadError = true;
}

void runFile(std::string file_path){
    std::string content;
    content = slurp(file_path);
    std::cout << content << std::endl;
    run(content);
    if (hadError) {
        exit(65);
    }
}

void runPrompt(){
    while (true){
        std::string code;
        std::cout << "> ";
        if (std::getline(std::cin, code)){
            run(code);
            std::cout << code << std::endl;
            hadError = false;
        } else {
            std::cout << "\n" << std::endl;
            break;
        }
    }
}


inline std::string slurp (const std::string& path) {
    std::ostringstream buf; 
    std::ifstream input (path.c_str()); 
    buf << input.rdbuf(); 
    return buf.str();
}