#include<iostream>
#include<string>
#include<fstream>
using namespace std;

struct Experience 
{
	string name;
	string experience;
};

class socialinteraction
{
private:
	Experience* exp;
    char message[20];
	int num_of_experiences;
    int count;
public:
	socialinteraction() {
        exp = nullptr;
		num_of_experiences = 0;
        count = 0;
        for (int i = 0; i < 20; i++)
            message[i] = ' ';
	}
    ~socialinteraction() {
        delete[] exp;
       
    }
    void write_direct_messages_to_file() {
        ofstream f("messages.bin", ios::binary | ios::app);
        if (!f) {
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "Oops, Couldn't open the file." << endl;
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            return;
        }
        f.write((char*)(&message), sizeof(message));
        f.close();
    }
    void shareExperience(string& name,  string& mge) {
        if (num_of_experiences >= count)
        {
            int newCount;
            if (count == 0)
                newCount = 1;
            else
                newCount = count * 2;
            Experience* newExp = new Experience[newCount];
            for (int i = 0; i < num_of_experiences; i++) {
                newExp[i] =exp[i];
            }
            delete[] exp;
            exp = newExp;
            count = newCount;
        }
        exp[num_of_experiences++] ={ name, mge };
        writeToBinaryFile();
    }
    void deleteExperience() 
    {
        if (num_of_experiences > 0) {
            num_of_experiences--;
            writeToBinaryFile();
            cout << "Your experience is deleted from the database successfully." << endl;
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        }
        else {
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "              No experiences to delete." << endl;
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        }
    }
    void direct_messages()
    {
       
        system("cls");
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        cout << "               Interact Socially, Make friends, Have fun" << endl;
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        display_past_messages();
        cout << "                Enter Message: "; 
        cin.ignore();
        cin.getline(message, sizeof(message));
        cout << endl;
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        write_direct_messages_to_file();
    }
    void updateExperience( string& mge ) {
        
            exp[num_of_experiences-1].experience = mge;
            writeToBinaryFile();
    }
    void writeToBinaryFile() {
        ofstream f("experiences.bin", ios::binary|ios::app);
        if (!f) {
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "Couldn't open the file." << endl;
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            return;
        }
        for (int i = 0; i < num_of_experiences; i++) {
            f.write(( char*)(&exp[i]), sizeof(Experience));
        }
        f.close();
    }
    void displayAllExperiences() {
        ifstream f("experiences.bin", ios::binary);
        if (!f) {
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "Unable to open file." << endl;
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            return;
        }

        Experience exp;
        while (f.read((char*)(&exp), sizeof(Experience))) 
        {
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "              Name: " << exp.name << endl;
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "              Experience: " << exp.experience << endl;
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        }
        f.close();
        
    }

    void display_past_messages() 
    {
        ifstream file("messages.bin", ios::binary);
        if (!file) {
            cout << "Unable to open file." << endl;
            return;
        }
        int messageCount = 1;
        while (file.read((char*)(&message), sizeof(message))) {
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "              Message " << messageCount++<<" : "<< message << endl;
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        }

        file.close();
    }

};
