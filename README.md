# Wheel of Quotes
Wheel of Quotes is a command-line game inspired by the classic "Wheel of Fortune." Players are challenged to guess letters in famous quotes, aiming to solve the complete quote before running out of attempts.

## Dataset
We utilized the Quotes 500K Dataset from Kaggle. The raw data has been processed into smaller, easily parsable .txt files, located in the cmake-build-debug directory of the project.

## Features
- Game Modes: We sorted the data into the top ten categories in the dataset, and allowed players to choose a genre for their randomized quote. 
- Play the Game: Test your knowledge and guessing skills with famous quotes.
- Comparative Algorithms: View and compare the performance of different algorithms used in the game.
### Gameplay Mechanics:
- 10 Attempts: You have 10 tries to guess unique consonants in the hidden quote.
- Vowel Penalty: Guessing a vowel counts as 2 attempts due to their frequency.
- Guess the Quote: Input ! at any time to guess the entire quote.
- Correct guess: You win!
- Incorrect guess: You lose.
- User-Friendly Interface: Simple menu-driven CLI for easy navigation.

## How to Play
Playing the Game:
- You'll see a quote with missing characters.
- Enter letters to guess the missing characters.
- Consonants deduct 1 attempt.
- Vowels deduct 2 attempts.
- You have a total of 10 attempts.
- To guess the entire quote, input !.
- If correct, you win.
- If incorrect, the game ends.
- After the game concludes:
  - Input 1: Restart the game.
  - Input 2: Return to the main menu.

## Installation and Setup
Running the game is straightforward. Follow these steps:
- Clone the Repository
- Cmkae build

Using an IDE:
- Open the project in your preferred IDE.
- Build the project using the IDE's build tools.
  
Run the Game:
- Execute the compiled binary.

No additional files or downloads are required.

## Dependencies
- Programming Language: The game is written in C++.
- Compiler: Ensure you have a C++11 compatible compiler installed (e.g., GCC, Clang, MSVC).

Thank you! :p
