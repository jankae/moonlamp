# moonlamp
An AVR based moonlamp which always lights up just as the real moon.

<p align="left">
  <img src="/images/IMG_1856.jpg?size=200" width="350"/>
</p>

Using a RTC and pre-programmed full-moon dates this lamp shows the moon in its current phase. Which also means you can't turn it on at all on a new moon ;)

## Operation
Touch the metal part to turn it on and off. The brightness can be conrolled by touching it for a longer time.

## Compiling & Flashing
The makefile is set up in such a way that the program is always (re-)compiled before flashing it. During this compiler-run, date and time will be hard-coded in the programm and written to the RTC at first startup. Thus, it is not necessary to set the RTC manually.

1. Adjust the makefile to your programmer
2. Setting fuses:

  ```
  cd software/moonlamp
  make fuses
  ```
3. Flash the program:

  ```
  make flash
  ```
