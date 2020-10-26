program speed
c
c    program to time 3 different methods of calculating
c    the dot product of long vectors
c
      parameter (nc=1000)
      dimension a(nc),b(nc),c(nc)
c
c    Use the Fortran 90 Intrinsic Subroutine to load
c    the vectors with random numbers
c
      dotpro=0.
      call random_number (a)
      call random_number(b)
c
c    Use the Fortran 90 Intrinsic Subroutine to determine
c    the current time in clock ticks (icount2), the clock
c    rate in clicks per second, and the largest possible
c    count before the clock resets.
c
c    CAUTION:  On this and probably most Unix work stations
c    this clock is measuring real time, not time your program
c    spends running.  If you are sharing the machine with others
c    you will count the time they have the CPU also.  USE the
c    unix "users" command to check for a situation when you are
c    the only user on the machine before running the program.
c    To filter out system activity run the program many times
c    and select results with the lowest total times.
c
      call system_clock(icount2,irate,icmax)
c
      print *, 'clock rate = ',irate, ' ticks per second'
c
c     The "1000" loop just makes sure that I do lots of work
c     to get good statistics.  Note that coding is set so
c     results of each pass through the loop are a little
c     different.  Without the "+.00001*dotpro" optimization
c     features on many compilers will only execute the loop
c     once.
c
      do 1000 i = 1,10000
c     <a name=4><font color=FF0000>
         dotpro = dot_product(a,b)+.00001*dotpro
c     </font>
 1000 continue
      call system_clock(icount3,irate,icmax)
      time = real(icount3-icount2)/real(irate)
      print *, 'Time for DOT_PRODUCT(a,b) = ', time,
     $ ' seconds'
      do 1001 i = 1,10000
c     <a name=3><font color=FF0000>
         dotpro = sum(a*b) +.00001*dotpro
c     </font>
 1001    continue
      call system_clock(icount4,irate,icmax)
      time = real(icount4-icount3)/real(irate)
      print *, 'Time for SUM(a*b) = ', time,
     $ ' seconds'
c<a name="do"><font color="FF0000">
      do 1002 i = 1,10000
c</a></font>
         do 100 j=1,nc
  100       dotpro=dotpro+a(j)*b(j)
c        dotpro=dotpro+.00001*dotpro
 1002 continue
c     <a name=1><font color=FF0000>
      call system_clock(icount5,irate,icmax)
c     </font> </a>
      time = real(icount5-icount4)/real(irate)
      print *, 'DO Loop dot product = ', time,
     $ ' seconds'
      print *, dotpro
      stop
      end