#include<iostream>
#include<string>
#include<fstream>
using namespace std;


class challenge_compete
{
private:
	
	string name;
	string challenge_name;
	int score;
public:
	challenge_compete()
	{
		name = "";
		challenge_name = "";
		score = 0;
	}
	void join_challenge()
	{
		
		system("cls");
		int opt;
		cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
		cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
		cout << "                        <<Join Challenge>>                                  " << endl;
		cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
		cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
		cout << "                Step challenge                            [1]" << endl;
		cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
		cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
		cout << "                 30-Day Plank Challenge                   [2]" << endl;
		cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
		cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
		cout << "                 Couch to 5K Running Challenge            [3]" << endl;
		cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
		cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
		cout << "                 NO deset month challenge                 [4]" << endl;
		cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
		cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
		cout << "                  Challenge name : ";
		cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
		cin >> challenge_name; cout << endl;
		cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
		cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
		cout << "                Enter your name "; cin >> name; cout << endl;
		cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
		cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;

		score += 10;
		//writing the data in file as well
		ofstream outFile("compete.bin", ios::binary | ios::app);
		if (!outFile) {
			cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
			cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
			cout << "Couldn't open the file." << endl;
			cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
			cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
			return;
		}
		outFile.write((char*)(this), sizeof(*this));
		outFile.close();
	}
	void score_board() {
		ifstream file("compete.bin", ios::binary | ios::in);
		if (!file) {
			cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
			cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
			cout << "Couldn't open file." << endl;
			cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
			cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
			return;
		}
		challenge_compete exp;
		//readign the data from the file and displaying on console
		while (file.read((char*)(&exp), sizeof(exp)))
		{
			cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
			cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
			cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
			cout << "              User: " << exp.name << endl;
			cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
			cout << "              Challenge: " << exp.challenge_name << endl;
			cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
			cout << "              Score: " << exp.score << endl;
			cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
			cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
			cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
		}
		file.close();
	}
	void view_batches()
	{
		bool won;
		string r;
		//giving gold medals if certail conditions are met else dispalying you won nothing
		if (score > 50)
		{
			cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
			cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
			cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
			cout << "              You won a gold medal for joining and competing the challenge " << challenge_name << endl;
			cout << "              Congrats!!!" << endl;
			cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
			cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
			cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
		}
		else
		{
			cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
			cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
			cout << "              You have won no batches" << endl;
			cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
			cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
		}

	}
	~challenge_compete() {
		
	}
};