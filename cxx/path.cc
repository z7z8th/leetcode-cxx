#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

namespace fs = std::filesystem;


void print_contents_of(std::string const& path)
{
  std::ifstream ifs(path);
  std::cout << ifs.rdbuf();
}


int main(int argc, char** argv)
{
  char const* const envroot = "/fileserver/";
  fs::path const root{ envroot };
  std::string const request{ argc > 1 ? argv[1] : "" };
  std::error_code error;
  fs::path const file{
    fs::canonical(
      fs::absolute(
        fs::path(request), root), error) };

  if (error)
  {
    std::cerr << "Error: " << error.value() << " " << error.message() << std::endl;
    return 1;
  }

  print_contents_of(file.string());

  return 0;
}