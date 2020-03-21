
#include "game.hpp"
#include "board.hpp"
#include "game_options.hpp"
#include "game_solver.hpp"
#include "input.hpp"
#include "main_menu.hpp"
#include <bulls_and_cows_lib\random.cpp>
#include <chrono>
#include <fstream>
#include <iostream>
#include <thread>
#include <vector>

using namespace std;

namespace bulls_and_cows {

    void user_plays_against_computer(const GameOptions& game_options)
    {
        unsigned int cpt_attempt = 0;
        vector<char> attempt;
        vector<char> code = generate_secret_code(game_options);
        unsigned int bulls = 0;
        unsigned int cows = 0;

        vector<vector<char>> attempt_historic;
        vector<int> bulls_historic;
        vector<int> cows_historic;

        do
        {
            cpt_attempt++;

            print_vector_char(code);
            attempt = do_attempt(game_options);
            attempt_historic.push_back(attempt);

            bulls = count_bull(attempt, code);
            cows = count_cow(attempt, code);

            bulls_historic.push_back(bulls);
            cows_historic.push_back(cows);

            display_board(attempt_historic, bulls_historic, cows_historic, cpt_attempt, game_options);
        } while (cpt_attempt < game_options.max_number_of_attempts + 1 &&
                 !(bulls == game_options.number_of_characters_per_code));

        if (bulls == game_options.number_of_characters_per_code)
        {
            cout << "You have win! :)";
        }
        else
        {
            cout << "You have reach the maximum number of attempts allowed, you have loose :(";
        }
    }

    // Return true if the user has win => the code is the same than the attempt
    /*bool win_condition(vector<char> const& attempt, vector<char> const& code)
    {
        if (attempt.size() == code.size())
        {
            for (int i = 0; i < code.size(); i++)
            {
                if (attempt[i] != code[i])
                {
                    return false;
                }
            }
        }
        else
        {
            return false;
        }
        return true;
    }*/

    // Count and return the number of bulls in the attempt
    unsigned int count_bull(vector<char> const& attempt, vector<char> const& code)
    {
        unsigned int bull = 0;
        for (int i = 0; i < code.size(); i++)
        {
            if (attempt[i] == code[i])
            {
                bull++;
            }
        }
        return bull;
    }

    // Count and return the number of cows in the attempt
    unsigned int count_cow(vector<char> const& attempt, vector<char> const& code)
    {
        unsigned int cow = 0;
        for (int i = 0; i < code.size(); i++)
        {
            for (int j = 0; j < attempt.size(); j++)
            {
                if (attempt[j] == code[i] && i != j)
                {
                    cow++;
                }
            }
        }
        return cow;
    }

    // Return true if the is no duplicate in the current code (vector)
    bool check_duplicates(vector<char> const& code, int current_index)
    {
        if (current_index == 0)
        {
            return true;
        }
        for (int i = 0; i < current_index; i++)
        {
            if (code[current_index] == code[i])
            {
                return false;
            }
        }
        return true;
    }

    //Display a vector of int
    void print_vector_int(vector<int> const& vector)
    {
        for (int i = 0; i < vector.size(); i++)
        {
            cout << vector[i] << " ";
        }
        cout << "\n";
    }

    // Return a vector of char containing random different char with the length defined in the options
    vector<char> generate_secret_code(const GameOptions& game_options)
    {
        int code_length = game_options.number_of_characters_per_code;
        vector<char> code(code_length);
        for (int i = 0; i < code_length; i++)
        {
            do
            {
                code[i] = generate_random_character(game_options.minimum_allowed_character,
                                                    game_options.maximum_allowed_character);
            } while (!check_duplicates(code, i));
        }
        return code;
    }

    vector<char> do_attempt(const GameOptions& game_options)
    {
        int code_length = game_options.number_of_characters_per_code;
        vector<char> attempt_vector(code_length);
        string attempt = "";
        do
        {
            cout << "Enter your new attempt (length of " << code_length << " and character between "
                 << game_options.minimum_allowed_character << " and " << game_options.maximum_allowed_character
                 << ") :";
            cin >> attempt;

        } while (!check_input(attempt, game_options));
        for (int i = 0; i < code_length; i++)
        {
            attempt_vector[i] = attempt[i];
        }
        return attempt_vector;
    }

    // Function to check if the input of the user for a attempt is right : length, characters allowed, duplicates
    bool check_input(string const& attempt, const GameOptions& game_options)
    {
        // Check for the number of characters
        if (attempt.size() != game_options.number_of_characters_per_code)
        {
            cout << "Wrong number of characters. Try again\n";
            return false;
        }

        // Check for the duplicates
        for (int i = 0; i < attempt.size(); i++)
        {
            for (int j = 0; j < attempt.size(); j++)
            {
                if (attempt[i] == attempt[j] && i!=j)
                {
                    cout << "There is at least one duplicate in your input. Try again\n";
                    return false;
                }
            }
            // Check for characters allowed
            if (attempt[i] < game_options.minimum_allowed_character ||
                attempt[i] > game_options.maximum_allowed_character)
            {
                cout << "Character(s) not allowed in your attempt. Try again\n";
                return false;
            }
        }
        return true;
    }

    void computer_plays_against_computer(const GameOptions& game_options)
    {
        std::cout
            << "TODO:\n"
               "    Create a board with a randomly generated secret code\n"
               "    Generate the list of all the possible codes\n"
               "    DO\n"
               "       Display the board and the list of attempts so far\n"
               "       Display the number of remaining possible codes so far\n"
               "       Wait for 2 seconds\n"
               "       Pick a random attempt among in the list of remaining possible codes\n"
               "       Compare the computer's attempt with the secret code and deduce the number of bulls and cows\n"
               "       Add the computer's attempt to the list of attempts of the board\n"
               "       Remove all the codes that are incompatible with the attempt's feedback from the list of "
               "possible codes\n"
               "    WHILE not end of game\n"
               "    Display the board and the list of attempts so far\n"
               "    Display a message telling if the computer won or lost\n";
    }

    void configure_game_options(GameOptions& game_options)
    {
        cout << "TODO:\n"
                "    DO\n"
                "       Display the current game options\n"
                "       Display the game options menu\n"
                "       Ask the user to type its choice\n"
                "       Treat the user's choice\n"
                "    UNTIL user's choice is to go back to main menu\n";
    }

    void play_game()
    {
        GameOptions game_options{};

        while (true)
        {
            cout << "\n#################################\n";
            display_main_menu(cout);

            const auto user_choice = ask_main_menu_choice(cin);
            switch (user_choice)
            {
            case MainMenuChoice::Quit:
                cout << "\nBye bye!\n";
                return;
            case MainMenuChoice::UserPlaysAgainstComputer:
                user_plays_against_computer(game_options);
                break;
            case MainMenuChoice::ComputerPlaysAgainstComputer:
                computer_plays_against_computer(game_options);
                break;
            case MainMenuChoice::ConfigureOptions:
                configure_game_options(game_options);
                break;
            case MainMenuChoice::Error:
                cout << "\nYou did not enter a valid choice, please try again\n";
                break;
            }
        }
    }

} // namespace bulls_and_cows