#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>


int main(int argc, char** argv)
{

	int max_value = 9;
	int level_value = 0;
	int record = 3;
	bool custom_level = false;
	if (argc >= 2)
	{
		std::string arg1_value{ argv[1] };
		//if parameter -max
		if (arg1_value == "-max")
		{

			if (argc < 3)
			{
				std::cout << "Wrong usage! The argument '-max' requires some value!" << std::endl;
				return -1;
			}
			max_value = std::stoi(argv[2]);
			custom_level = true;
		}
		//if parameter -level
		if (arg1_value == "-level")
		{

			if (argc < 3)
			{
				std::cout << "Wrong usage! The argument '-level' requires some value!" << std::endl;
				return -1;
			}
			level_value = std::stoi(argv[2]);
			if (level_value >= 4)
			{
				std::cout << "Wrong usage! The argument '-level' requires value from 1 to 3!" << std::endl;
				return -1;
			}
			
		}
	}
//level switch-case logic
	
	if (level_value != 0) 
	{
		switch (level_value)
		{
		case 1:
			max_value = 19;
			record = 5;
			break;

		case 2:
			max_value = 99;
			record = 10;
			break;

		case 3:
			max_value = 999;
			record = 20;
			break;

		default:
			return -1;

		}
	}
// custom level warning
if(custom_level== true)
	{
	int record = 0;
	std::cout << "You start game with -max, write to leaderboard disabled" << std::endl;
    }
// random 
	std::srand(std::time(nullptr));

	const int random_value = std::rand() % max_value;

// enter username
	std::cout << "Hi! Enter your name, please:" << std::endl;
	std::string user_name;
	std::cin >> user_name;

	
// game logic
	const int target_value = random_value;
	int current_value = 0;
	int attempts_count = 0;
	std::cout << "Enter your guess" << std::endl;
	do {
		attempts_count++;
		std::cin >> current_value;
		if (current_value < 0) 
		{
			std::cout << "must be > 0" << std::endl;
		}

		else if (current_value > target_value) 
		{
			std::cout << "less than " << current_value << std::endl;
		}
		else if (current_value < target_value) 
		{
			std::cout << "greater than " << current_value << std::endl;
		}
		else 
		{
			std::cout << user_name << ", you win for " << attempts_count <<  " attempts!" << std::endl;
			if (attempts_count <= record and custom_level==false) 
			{
				std::cout << "This is record!" << std::endl;
            }
			break;
		}

	} while (true);

	const std::string high_scores_filename = "high_scores.txt";
	// if custom level == 0
	if (custom_level == false)
	{
		//leaderboard write to file


		std::ofstream out_file{ high_scores_filename, std::ios_base::app };
		if (!out_file.is_open()) {
			std::cout << "Failed to open file for write: " << high_scores_filename << "!" << std::endl;
			return -1;
		}
		out_file << user_name << ' ';
		out_file << level_value << ' ';
		out_file << attempts_count;
		out_file << std::endl;
	}
	std::ifstream in_file{ high_scores_filename };
	if (!in_file.is_open()) {
		std::cout << "Failed to open file for read: " << high_scores_filename << "!" << std::endl;
		return -1;
	}
// leaderboard read from file and print
	std::string username;
	int high_score = 0;
	int levelvalue = 0;
	std::cout << "_____________LEADERBOARD________________" << std::endl;
	std::cout << "Name            Level           Att     " << std::endl;
	while (true) {
		in_file >> username;
		in_file >> levelvalue;
		in_file >> high_score;
		in_file.ignore();

		if (in_file.fail()) {
			break;
		}
//if record, print user data
		if (high_score <= record)
		{
			std::cout << username << '\t' << '\t' << levelvalue << '\t' << '\t' << high_score << std::endl;
		}
	}
	return 0;

}


