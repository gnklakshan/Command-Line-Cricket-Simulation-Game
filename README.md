							Command-Line Cricket Simulation Game

Introduction  

Cricket is one of the most popular and widely followed sports in the world, known for its intricate rules and strategies. The Command-Line Cricket Simulation Game is a text-based, interactive program implemented in C++. It aims to provide users with a simplified yet engaging experience of playing or simulating a cricket match within the constraints of a console environment. This game allows cricket enthusiasts to immerse themselves in the excitement of batting, bowling, and making strategic decisions in a virtual cricket match.

Game Overview

The Command-Line Cricket Simulation Game allows you to:

1. Select Teams: At the start of the game, you have the option to choose two cricket teams from a predefined dataset. Each team consists of players with varying batting and bowling skills. You can customize the game further by editing the team data in an input file.
2. Toss: A virtual coin toss is simulated to determine which team will have the opportunity to choose whether to bat or bowl first. The toss outcome adds an element of unpredictability to the game.
3. Batting and Bowling: The game proceeds with a simulated cricket match, where one team bats, and the other team bowls. Players take turns to bat and bowl. Batsmen attempt to score runs by hitting the ball, while bowlers aim to take wickets and restrict the batting team's runs. The game simulates various ball states, such as normal deliveries, wides, and no-balls.
4. Wickets and Runs: As the game progresses, batsmen accumulate runs, hit fours and sixes, and may get dismissed (out) based on a simulated probability. Bowlers strive to take wickets and keep the batting team's run rate in check.
5. Strategic Decisions: You, as the player, can make strategic decisions such as choosing which bowler to bowl, which batsman to send in, and when to declare an innings or chase a target. These decisions can significantly impact the outcome of the match.
6. Target and Victory: The game continues until the batting team's innings are completed, or the target score set by the bowling team is achieved or surpassed. The team that scores the most runs wins the match. The game displays the result along with key statistics.
7. Customization: The game is highly customizable. You can edit the input file to define your own teams with different players, skills, and strategies. Additionally, you can adjust the probabilities, ball states, and other game parameters in the code to fine-tune the game's difficulty and realism.

  Code Structure
The code is organized into several classes, each responsible for specific aspects of the game. Let's dive into the details of each class:

 1. `rule` Class
- Purpose: The `rule` class contains utility functions for parsing data from a file. It's used to read team data from an input file.

 2. `amphire` Class
- Purpose: The `amphire` class simulates an umpire and handles tasks related to the toss, ball state, and player dismissal.

 3. `player` Class
- Purpose: The `player` class serves as the base class for all players in the game, including batsmen, bowlers, and all-rounders. It stores the player's name and runs scored.

 4. `batsman` Class
- Purpose: The `batsman` class represents a batsman in the game. It includes batting-related attributes and methods.

 5. `bowler` Class
- Purpose: The `bowler` class represents a bowler in the game. It includes attributes and methods related to bowling.

 6. `all_rounder` Class
- Purpose: The `all_rounder` class represents an all-rounder player who can both bat and bowl. It inherits from both the `batsman` and `bowler` classes.

 7. `team` Class
- Purpose: The `team` class represents a cricket team and contains players (batsmen, bowlers, all-rounders) and manages the game state, including wickets, runs, and overs.

 8. `main` Function
- Purpose: The `main` function serves as the entry point of the program. It initializes the game, sets up the teams, and simulates the match.

  How to Run the Game

To play the game, follow these steps:

1. Compile the code using a C++ compiler. For example: `g++ cricket_game.cpp -o cricket_game`.
2. Run the compiled executable: `./cricket_game`.

 Game Flow

The game follows these steps:

1. Reads team data from an input file.
2. Simulates a coin toss to determine which team will bat first.
3. The batting team faces deliveries from the bowling team.
4. Players take their turns to bat, and bowlers bowl deliveries.
5. The game continues until a team's batting is completed, or the target is achieved or surpassed.
6. The game displays the match result.

 Customization

You can customize the game by modifying the data in the input file or adjusting probabilities and skills in the code. Additionally, you can extend the game by adding more features or rules to make it more complex and realistic.


