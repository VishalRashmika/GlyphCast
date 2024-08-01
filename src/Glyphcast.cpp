# include <iostream>
# include <fstream> 
# include <sstream>

inline std::string slurp (const std::string& path) {
    std::ostringstream buf; 
    std::ifstream input (path.c_str()); 
    buf << input.rdbuf(); 
    return buf.str();
}

void runFile(std::string file_path){
    std::string content;
    content = slurp(file_path);
    std::cout << content << std::endl;

    // end point 
}

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
        // runPrompt();
        return 0;
    }
    return 0;
}