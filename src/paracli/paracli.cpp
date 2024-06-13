#include <fstream>
#include <paracli/paracli.hpp>
using namespace paracl::interpreter;

int main(int argc, char **argv) {

  if (argc != 2)
    throw std::logic_error("Wrong command line params.");

  std::ifstream inputFile(argv[1]);

  Interpreter i(inputFile, true);

  i.run();

  return 0;
}
