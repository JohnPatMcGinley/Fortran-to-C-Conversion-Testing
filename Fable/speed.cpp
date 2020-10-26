#include <fem.hpp> // Fortran EMulation library of fable module

namespace placeholder_please_replace {

using namespace fem::major_types;

void
dot_product(...)
{
  throw std::runtime_error(
    "Missing function implementation: dot_product");
}

void
random_number(...)
{
  throw std::runtime_error(
    "Missing function implementation: random_number");
}

void
sum(...)
{
  throw std::runtime_error(
    "Missing function implementation: sum");
}

using fem::common;

//Crogram speed
//C
//C    program to time 3 different methods of calculating
//C    the dot product of long vectors
//C
void
program_unnamed(
  int argc,
  char const* argv[])
{
  common cmn(argc, argv);
  common_write write(cmn);
  //C
  //C    Use the Fortran 90 Intrinsic Subroutine to load
  //C    the vectors with random numbers
  //C
  float dotpro = 0.f;
  const int nc = 1000;
  arr<float> a(dimension(nc), fem::fill0);
  random_number(a);
  arr<float> b(dimension(nc), fem::fill0);
  random_number(b);
  //C
  //C    Use the Fortran 90 Intrinsic Subroutine to determine
  //C    the current time in clock ticks (icount2), the clock
  //C    rate in clicks per second, and the largest possible
  //C    count before the clock resets.
  //C
  //C    CAUTION:  On this and probably most Unix work stations
  //C    this clock is measuring real time, not time your program
  //C    spends running.  If you are sharing the machine with others
  //C    you will count the time they have the CPU also.  USE the
  //C    unix "users" command to check for a situation when you are
  //C    the only user on the machine before running the program.
  //C    To filter out system activity run the program many times
  //C    and select results with the lowest total times.
  //C
  int irate = fem::int0;
  write(6, star), "clock rate = ", irate, " ticks per second";
  //C
  //C     The "1000" loop just makes sure that I do lots of work
  //C     to get good statistics.  Note that coding is set so
  //C     results of each pass through the loop are a little
  //C     different.  Without the "+.00001*dotpro" optimization
  //C     features on many compilers will only execute the loop
  //C     once.
  //C
  int i = fem::int0;
  FEM_DO_SAFE(i, 1, 10000) {
    //C     <a name=4><font color=FF0000>
    dotpro = dot_product(a, b) + .00001f * dotpro;
    //C     </font>
  }
  //C
  int icount3 = fem::int0;
  int icount2 = fem::int0;
  float fem::time = fem::real(icount3 - icount2) / fem::real(irate);
  write(6, star), "Time for DOT_PRODUCT(a,b) = ", fem::time, " seconds";
  FEM_DO_SAFE(i, 1, 10000) {
    //C     <a name=3><font color=FF0000>
    dotpro = sum(a * b) + .00001f * dotpro;
    //C     </font>
  }
  //C
  int icount4 = fem::int0;
  fem::time = fem::real(icount4 - icount3) / fem::real(irate);
  write(6, star), "Time for SUM(a*b) = ", fem::time, " seconds";
  //C<a name="do"><font color="FF0000">
  int j = fem::int0;
  FEM_DO_SAFE(i, 1, 10000) {
    //C</a></font>
    FEM_DO_SAFE(j, 1, nc) {
      dotpro += a(j) * b(j);
    }
    //C        dotpro=dotpro+.00001*dotpro
  }
  //C     <a name=1><font color=FF0000>
  //C
  //C     </font> </a>
  int icount5 = fem::int0;
  fem::time = fem::real(icount5 - icount4) / fem::real(irate);
  write(6, star), "DO Loop dot product = ", fem::time, " seconds";
  write(6, star), dotpro;
  FEM_STOP(0);
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
