#include<iostream>
#include<string>

string trainers[50][2];
class Trainer :public User
{
    int numTrainer;
private:
public:
    Trainer()
    {
        numTrainer = 0;
        ReadFromFile();
    }
    void selecting_a_trainer()
    {
        bool select = false;
        string ide;
        cout << "              Enter the id of trainer you want to select"; cin >> ide; cout << endl;

        for (int i = 0; i < 50; i++)
        {
            if (trainers[i][1] == id)
            {
                cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
                cout << "              Your request has been sent to trainer" << endl;
                cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
                select = true;
            }
        }
        if (select == false)
        {
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "               Trainer with this id does not exist" << endl;
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        }

    }
    void changing_a_trainer()
    {
        bool select = false;
        string id;
        cout << "Enter the id of trainer you want to be change and then select" << endl;
        cin >> id;
        for (int i = 0; i < 50; i++)
        {
            if (trainers[i][1] == id)
            {
                cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
                cout << "               Your request has been sent to trainer" << endl;
                cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
                select = true;
            }
        }
        if (select == false) {
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "               Trainer with this id does not exist" << endl;
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        }

    }
    void shareexperience()
    {
        string exper;
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        cout << "                Enter your experience:"; cin >> exper; cout << endl;
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        cout << "                Thank you for sharing your experience " << endl;
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
    }
    void shareSuccessStory()
    {
        string exper;
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        cout << "                Enter your success story:"; cin >> exper; cout << endl;
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        cout << "                Thank you for sharing your stories with us  " << endl;
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
    }
    bool checktrainerpresence(string trainer_id)
    {
        for (int i = 0; i < 50; i++)
        {
            if (trainers[i][1] == trainer_id)
            {
                return true;
            }
            return false;
        }
    }
    void resetpaasword() {
        string x;
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        cout << "              Are there chances that you may forget paasword then reset password (yes/no)"; cin >> x; cout << endl;
        if (x == "yes")
        {
            cout << "              Enter new paasword "; enterpassword();
        }
    }
    void Register()
    {
        system("cls");//cls is a command used to clear all the screen
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        cout << "               Enter your First name: ";
        enterfirstname();
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        cout << "               Enter your Last name: ";
        enterlastname();
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        cout << "               Enter your Gender [F/M]: ";
        entergender();
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        cout << "               Enter the Password:  ";
        enterpassword();
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        cout << "               Enter your Weight: ";
        enterweight();
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        cout << "               Enter your Height: ";
        enterheight();
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        cout << "               Enter your Age: ";
        enterage();
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        cout << "               Enter your ID: ";
        enterid();
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        cout << "              You have been successfully Registered, Trainer " << endl;
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        resetpaasword();
        Write_File();
        ReadFromFile();
    }
    void Login()
    {//prompting the user to enter id and paasword with which he has registered and printing corresponding statements if its id and paas word does not matches
        string pass;
        string id;
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        cout << "               Enter your id: ";
        cin >> id;
        for (int i = 0; i < 50; i++)
        {
            if (trainers[i][1] == id)
            {
                cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
                cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
                cout << "               Enter the password ";
                cin >> pass;
                if (trainers[i][0] == pass)
                {
                    break;
                }
                else
                {
                    cout << "                    ";
                    cout << endl << "              Incorrect Password" << endl;
                    Login();
                    break;
                }
            }
            else
            {
                cout << "                        ";
                cout << endl << "              User with this id doesnot exist" << endl;
                Login();
                break;
            }
        }

    }
    void ReadFromFile()
    {
        ifstream infile("TrainerDetails.bin", ios::binary);
        if (!infile)
        {
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "File doesn't exist. Creating a new file." << endl;
            ofstream createFile("TrainerDetails.bin");
            createFile.close();

            // Retry opening the file
            infile.open("TrainerDetails.bin", ios::binary);
            if (!infile)
            {
                cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
                cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
                cout << "Oops. Couldn't open the file even after creation." << endl;
                cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
                cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
                return;
            }
        }

        // Now proceed with reading the file
        int num = 40;
        while (numTrainer < 50 && infile >> trainers[numTrainer][0] >> trainers[numTrainer][1])
        {
            // Read the rest of the user data from the file
            string password, id, lastName, firstName;
            char gender;
            double weight, height;
            int age;

            infile >> password >> id >> lastName >> firstName >> gender >> weight >> age >> height;

            // Update the admin array with the read data
            trainers[num][1] = id;
            trainers[num][0] = password;
            num++;
        }

        infile.close();
    }
    void AddTrainer(const string& username, const string& password) {
        if (numTrainer < 50) {
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "Oops file." << endl;
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            trainers[numTrainer][0] = username;
            trainers[numTrainer][1] = password;
            numTrainer++;
        }
        else {
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cerr << "                Max number of admins reached!" << endl;
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        }
    }
    void Write_File() {

        ofstream outfile("TrainerDetails.bin", ios::binary | ios::app);
        if (!outfile)
        {
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "Couldn't open the file." << endl;
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            return;
        }
        string password = getPassword();
        outfile.write("Password: ", sizeof("Password: "));
        outfile.write((char*)(&password), sizeof(password));
        string id = getId();
        trainers[numTrainer][1] = id;
        trainers[numTrainer][0] = password;
        numTrainer++;
        outfile.write((char*)(&id), sizeof(id));
        string lastName = getLastName();
        outfile.write("Last Name: ", sizeof("Last Name: "));
        outfile.write((char*)(&lastName), sizeof(lastName));
        string firstName = getFirstName();
        outfile.write("First Name: ", sizeof("First Name: "));
        outfile.write((char*)(&firstName), sizeof(firstName));
        char gender = getGender();
        outfile.write("Gender: ", sizeof("Gender: "));
        outfile.write((char*)(&gender), sizeof(gender));
        double weight = getWeight();
        outfile.write("Weight: ", sizeof("Weight: "));
        outfile.write((char*)(&weight), sizeof(weight));
        int age = getAge();
        outfile.write("Age: ", sizeof("Age: "));
        outfile.write((char*)(&age), sizeof(age));
        double height = getHeight();
        outfile.write("Height: ", sizeof("Height: "));
        outfile.write((char*)(&height), sizeof(height));

        outfile.close();
    }
};
