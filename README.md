## gameoflife-arduino

An Arduino implementation of Conway's game. Used as an excuse to learn basic electrical engineering. This widget will hopefully evolve into a compact desk toy that plays the Game of Life over and over again forever.

###Important Points Checklist:
  * Make an Arduino program to control an 8x8 LED matrix
  * Simulate a random board of GoL
  * Count the number of generations until the board either dies or stagnates
  * Save a copy of every board and the number of generations it lasted
  * ~~Install an SD card reader~~
  * Implement a local storage system on the SD card
  * Intstall a 4x4 button matrix
  * Program each button to control a 2x2 sector of LEDs
  * Write a system to gracefully handle user interaction
  * Install an external power source
  * Transfer ATMEGA328P and entire project to a permanent PCB
  * Design and print a custom enclosure for finished product
  
The project should allow the user to press the buttons to influence the currently running game. A button press should pause the simulation for an amount of time before resuming.
The user-altered game should still be considered as a valid board, but the initial random board is considered invalid and should be deleted from storage.
There should be a switch to safely turn off the device
There should be a switch to toggle edge-wrapping vs empty edges. Any board that switches modes mid-simulation should be discarded and stored from its current position
Each board in storage should indicate its initial setup and its edge mode, either through its filename or location (~\wrapped vs ~\finite)

####Skills to learn
  * Basic electrical engineering
  * Arduino programming with shields
  * Minimal user interface design
  * PCB design + soldering
  * 3D modeling for production
  
####Parts needed to reproduce
  * Arduino Uno
  * SD card shield (I used a Catalex MicroSD Card Adapter v1.0 11/01/2013)
  * 8x8 LED matrix
  * Some other stuff. I'll fill this in as I go

####Progress and notes
200112 - Got the SD card working and saving files without too much difficulty. Followed the example at http://educ8s.tv/arduino-sd-card-tutorial/ Not too difficult, but the example code already takes up 37% of the Arduino storage space. Hopefully it's just the libraries and more code won't fill it up too fast. Waiting on more components to arrive before continuing.