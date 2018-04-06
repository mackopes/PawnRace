# PawnRace with AI

## Installation
Simply download the repository and in repo dir run `make` command.

## Usage
Game can be started with
` ./pawnrace `
This starts game with default settings (Two Minimax AIs against each other)
Change settings with flags. 
### Help
```
$ ./pawnrace -h
```
### Change players
You can choose between multiple types of players: Human player, AI Player and Random player. To choose which type of player will play for each side use flags `-w` for white player and `-b` for black player followed by name of player (_human, ai, random_).
Example: Run game with Human as white and AI as black
```
$ ./pawnrace -w human -b ai
```
### AI _thinking_ time
Default value for _thinking_ time for AI is 5s.
To change the amount of time for AI to _think_ use flag `--ai-timeout_` followed by number of milliseconds.
Example: Run game with Human as white and AI as black with _thinking_ time for AI 8s
```
$ ./pawnrace -w human -b ai --ai-timeout 8000
```
### Benchmark mode
To run benchmark mode use `--benchmark`
In benchmark mode first two moves by each side are made by Random Player and then by Player
### Specify number of threads
To specify number of thread that will be used to simulate the games use `--n-threads` followed by _number_ of threads. Default value is 1.
Example: Run benchmark of two AIs with 50 games and 8 threads
```
$ ./pawnrace -w ai -b ai -n 50 --n-threads 8 --benchmark
```
### Switch starting player
During benchmark you may want to start every second game with black player (to make it fair).
To do this use `-s`.
Example: Run benchmark of two AIs with 50 games and 8 threads and switch starting player every second game
```
$ ./pawnrace -w ai -b ai -n 50 --n-threads 8 --benchmark -s
```
### GamePlay
When playing as human simply enter 4 characters (letter-number-letter-number) of source and destination tile you are moving. Example: move pawn from tile D2 to tile D3
```
Your move: d2d3
```
![Move Example](/imgs/move_example.png)

## Notes
This project uses https://github.com/vietjtnguyen/argagg to parse command line arguments.
