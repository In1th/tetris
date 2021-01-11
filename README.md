# Tetris project
### Version 1.0 
### Done by Mateusz Kruk 
### E-mail: krukm634@gmail.com

## Description
This project had a goal of replicating a game called Tetris as a final project for the C subject. It was trying to imitate the Gameboy Classic [version](https://en.wikipedia.org/wiki/Tetris_(Game_Boy_video_game)) from 1989, but it's not a faithful replication of that version of the game because of the lack of information about certain mechanics or different implementation of functions. The project in this version is fully operational, but in the future it's going to be expanded on new features.

**[NOTE!]** THe author does not claim any rights to the Tetris game and this project is only for educational purposes. 

## Getting started
In order to compile the code, the project requires Allegro-5 library to work. If you are using **Ubuntu 18.04+** or derivatives of it, firstly add the Allegro PPA:
```
sudo add-apt-repository ppa:allegro/5.2
```
Then install Allegro:
```
sudo apt-get install liballegro*5.2 liballegro*5-dev
```  
For other operating system please refer to the Allebro library [github page](github.com/liballeg/allegro_wiki/wiki/Quickstart).

## Compiling
To compile the code, you may be unable to compile it using gcc. Please make sure you are using this flag while compiling:
```
$(pkg-config allegro-5 allegro_font-5 allegro_ttf-5 allegro_image-5 allegro_primitives-5 --libs --cflags)
```
File **tetris.c** is the main file.

## Running the code
The project support main function arguments for opening built-in gamemodes of the game. If you are launching it without any arguments, it'll run game A with default arguments (level 0).
```
./[executeable_name]
```

You can choose the gamemode by typing the letter of the mode ("A" or "B") as a second argument after the executeable name. It'll run chosen gamemodes with default values (level 0 for game A or level 0 and high 0 for game B)
```
./[executeable_name] [gamemode]
```

Then, depending on the mode you can add additional arguments to the mode:
- for game A: level from [0,20]
- for game B: level from [0,20] and high from [0,5]

```
./[executeable_name] A [level]
./[executeable_name] B [level] [high]
```

## Gamemodes
In the current version of the game there are 2 modes:

#### Game A
It's called a marathon. The player completes the lines almost indefinitley, getting points for landing the blocks and clearing the lines. The level is increasing by 1 when a certain number of lines have been cleared, when makes the Tetriminos fall faster on their own. Game ends when the starting position of the Tetrimino gets blocks by the other one.

#### Game B
Player has to clear at least 25 lines with lines containing random number of cells, determined by the high. The game end the same way as in Game A, but when the player clear those 25 lines, a score with a breakdown of specific line numbers cleared at the same time.

## Controls
- **left arrow/right arrom** - moves the Tetrimino one cell to the left/right
- **down arrow** - makes the Tetrimino fall faster
- **Z/X** - rotates the Tetrimino to the left (Z) or to the right (X)
- **space** -  reverses the block

## Upcoming features

- main function incorrect values handling
- music
- UI
- animations
- better sprites
