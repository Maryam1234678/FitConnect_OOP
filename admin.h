#pragma once
#include<iostream>
#include<string>

string admins[50][2];

class Admin :public User
{
    int numAdmins;
private:
public:
    Admin() {
        numAdmins = 0;
        ReadFromFile();
    }
    void view_details_customers() {
        ifstream infile("RegularUserDetails.bin", ios::binary | ios::in);
        if (!infile) {
            cout << "Couldn't open the file" << endl;
            return;
        }
        char ch;
        while (infile.read((char*)&ch, sizeof(ch))) {
            cout << ch;
        }
        infile.close();
    }
    void view_trainers_feedback_from_clients_read_file() {
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;

        ifstream feedback_file("feedback.bin", ios::binary);
        if (!feedback_file) {
            cout << "Couldn't open the file." << endl;
            return;
        }

        char feedback[40];
        while (feedback_file.read(feedback, sizeof(feedback))) {
            cout << "              Feedback: " << feedback << endl;
        }

        feedback_file.close();
    }
    void resetpaasword()
    {
        string x;
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        cout << "              Are there chances that you may forget paasword then reset password (yes/no)"; cin >> x; cout << endl;
        if (x == "yes")
        {
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "              Enter new paasword "; enterpassword();
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        }
    }
    void Register()
    {
        system("cls");
        //cls is a command used to clear all the screen
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
        cout << "              You have been successfully Registered, Admin " << endl;
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl; 
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        resetpaasword();
        WriteToFile();
        ReadFromFile();
    }
    void Login()
    {
        string pass;
        string id;
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        cout << "               Enter your id: ";
        cin >> id;
        for (int i = 0; i < 50; i++)
        {
            if (admins[i][1] == id)
            {
                cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
                cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
                cout << "               Enter the password ";
                cin >> pass;
                if (admins[i][0] == pass)
                {

                    break;
                }
                else
                {
                    cout << "                    ";
                    cout << endl << "              Incorrect Password" << endl;
                    cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
                    Login();
                    break;
                }
            }
            else
            {
                cout << "                        ";
                cout << endl << "              User with this id doesnot exist" << endl;
                cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
                Login();
                break;
            }
        }

    }
    void ReadFromFile()
    {
        ifstream infile("AdminDetails.bin", ios::binary);
        if (!infile)
        {
            cout << "File doesn't exist. Creating a new file." << endl;
            ofstream createFile("AdminDetails.bin");
            createFile.close();

            // Retry opening the file
            infile.open("AdminDetails.bin", ios::binary);
            if (!infile)
            {
                cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
                cout << "Oops. Couldn't open the file even after creation." << endl;
                cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
                return;
            }
        }

        // Now proceed with reading the file
        int num = 40;
        while (numAdmins < 50 && infile >> admins[numAdmins][0] >> admins[numAdmins][1])
        {
            // Read the rest of the user data from the file
            string password, id, lastName, firstName;
            char gender;
            double weight, height;
            int age;

            infile >> password >> id >> lastName >> firstName >> gender >> weight >> age >> height;

            // Update the admin array with the read data
            admins[num][0] = id;
            admins[num][1] = password;
            num++;
        }

        infile.close();
    }
    void AddAdmin(const string& username, const string& password) {
        if (numAdmins < 50) {
            cout << "Oops file." << endl;

            admins[numAdmins][0] = username;
            admins[numAdmins][1] = password;
            numAdmins++;
        }
        else {
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cerr << "Max number of admins reached!" << endl;
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        }
    }
    void WriteToFile() {

        ofstream outfile("AdminDetails.bin", ios::binary | ios::app);
        if (!outfile)
        {
            cout << "Couldn't open the file." << endl;
            return;
        }
        string password = getPassword();
        outfile.write("Password: ", sizeof("Password: "));
        outfile.write(reinterpret_cast<const char*>(&password), sizeof(password));
        string id = getId();
        admins[numAdmins][1] = id;
        admins[numAdmins][0] = password;
        numAdmins++;
        outfile.write(reinterpret_cast<const char*>(&id), sizeof(id));
        string lastName = getLastName();
        outfile.write("Last Name: ", sizeof("Last Name: "));
        outfile.write(reinterpret_cast<const char*>(&lastName), sizeof(lastName));
        string firstName = getFirstName();
        outfile.write("First Name: ", sizeof("First Name: "));
        outfile.write(reinterpret_cast<const char*>(&firstName), sizeof(firstName));
        char gender = getGender();
        outfile.write("Gender: ", sizeof("Gender: "));
        outfile.write(reinterpret_cast<const char*>(&gender), sizeof(gender));
        double weight = getWeight();
        outfile.write("Weight: ", sizeof("Weight: "));
        outfile.write(reinterpret_cast<const char*>(&weight), sizeof(weight));
        int age = getAge();
        outfile.write("Age: ", sizeof("Age: "));
        outfile.write(reinterpret_cast<const char*>(&age), sizeof(age));
        double height = getHeight();
        outfile.write("Height: ", sizeof("Height: "));
        outfile.write(reinterpret_cast<const char*>(&height), sizeof(height));

        outfile.close();
    }
    void writing_feedback_of_trainers_to_file(char array[], int size)
    {
        char feed[40];
        for (int i = 0; i < 40; i++)
            feed[i] = array[i];
        ofstream feedb("feedback.bin", ios::binary | ios::app);
        if (!feedb) {
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl; 
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "Oops, Couldn't open the file." << std::endl;
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            return;
        }
        feedb.write(array, size);
        feedb.close();
    }
};