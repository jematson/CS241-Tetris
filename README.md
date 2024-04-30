**Bitris** 

By Jenae Matson & Elliott Lewandowski 

CS 241 Final Project
-------------------------------------

Bitris is a simple game similar to Tetris. The player is in control of a bitrimino (a game block made up of two pixels in various configurations). 
The bitrimino automatically moves downwards on the screen, and the player can move it side to side and downwards using buttons. 
The goal is to place bitriminos to fill rows. A full row is removed from the board and the player receives one point. 
The game ends when the pile of bitrimino debris reaches the top of the screen and no more can be placed*.

This code is structured to be run on two separate arduinos. It should be compatible with both Arduino Unos and Arduino Nanos (We used an Uno for the main game code and a Nano for the sound effects).

- The bitris_main directory contains the code for the main game. The bitris_main.ino file (which contains the main game loop) should be flashed to one Arduino. 
The rest of the code is organized into header files that handle various aspects of the game. 
- The bitris_sounds directory contains code for running sound effects and music on an Arduino Nano via a simple buzzer. The bitris_sounds.ino file should be flashed to an Arduino Nano.

More information including a wiring diagram can be found at the following [link](https://docs.google.com/document/d/1QBtyzqwLe1GX5251M2EsWPSDQCTKFuFrcr5R6hfstds/edit?usp=sharing)

*Alternate ways of winning include reaching a score of 36,767 to overflow the points variable, or playing for 45 days straight to overflow the timing variable, thus causing a spire of bitriminos to appear in the middle of the screen
