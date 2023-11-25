#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>

std::string runFile(std::string path) {
  std::ifstream inputFile(path);

  if (!inputFile.is_open()) {
    std::cerr << "Error opening the file " << path << std::endl;
  }

  std::stringstream buffer;
  buffer << inputFile.rdbuf();

  return buffer.str();
}

std::string runPrompt() {
  std::string path;
  std::cin >> path;

  std::ifstream ifs{path};
  if (!ifs.is_open()) {
    std::cerr << "Error: Cannot open file " << path;
  }

  std::string source{std::istreambuf_iterator<char>(ifs),
                     std::istreambuf_iterator<char>()};

  return source;
}

void run(std::string source) {
  std::istringstream iss(source);

  std::string token;
  while (std::getline(iss, token, ' ')) {
    std::cout << token << std::endl;
  }
}

int main(int argc, char *argv[]) {
  if (argc > 2) {
    std::cerr << "Error usage";
    return 1;
  } else if (argc == 2) {
    std::string source = runFile(argv[1]);
    run(source);
  } else if (argc == 0) {
    std::string source = runPrompt();
  }
}
