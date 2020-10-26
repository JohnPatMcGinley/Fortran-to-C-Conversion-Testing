#include <fem.hpp> // Fortran EMulation library of fable module

namespace placeholder_please_replace {

using namespace fem::major_types;

using fem::common;

//Crogram hello
void
program_unnamed(
  int argc,
  char const* argv[])
{
  common cmn(argc, argv);
  common_write write(cmn);
  write(6, star), "Hello World!";
}

} // namespace placeholder_please_replace

int
main(
  int argc,
  char const* argv[])
{
  return fem::main_with_catch(
    argc, argv,
    placeholder_please_replace::program_unnamed);
}
