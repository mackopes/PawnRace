# PawnRace with AI

## Installation
Simply download the repository and in repo folder run _make_ command.

## Usage
Game can be started with
``` ./pawnrace ```
This starts game with default settings (Two Minimax AIs against each other)
Change settings with flags. 
### Help
```
./pawnrace -h
```
### Change players
You can choose between multiple types of players: Human player, AI Player and Random player. To choose which type of player will play for each side use flags _-w_ for white player and _-b_ for black player followed by name of player (human, ai, random).
Example: Run game with Human as white and AI as black
```
./pawnrace -w human -b ai
```
### AI _thinking_ time
Default value for _thinking_ time for AI is 5s.
To change the amount of time for AI to _think_ use flag _--ai-timeout_ followed by number of miliseconds. To avoid unexpected behaviour of the AI use values greater than 1000.
Example: Run game with Human as white and AI as black with _thinking_ time for AI 8s
```
./pawnrace -w human -b ai --ai-timeout 8000
```
### GamePlay
When playing as human simply enter 4 characters (letter-number-letter-number) of source and destination tile you are moving. Example: move pawn from tile D2 to tile D3
```
Your move: d2d3
```
![Move Example](/imgs/move_example.png)

## Notes
This project uses https://github.com/vietjtnguyen/argagg to parse command line arguments.
