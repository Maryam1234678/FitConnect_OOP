#include<iostream>
#include<string>
#include"workout.h"
#include"Nutrition.h"
#include"Socialinteraction.h"
#include"Location.h"
#include"Challenges.h"
string users[50][2];

class RegularUser :public User
{

    workout obj;
    string feedback;
    Nutrition o;
    socialinteraction e;
    Location_Activity l;
    challenge_compete cha;
    int numUsers;

public:
    RegularUser() {
        numUsers = 0;
        ReadFromFile();

    }
    void view_all_details() {
        ifstream file("RegularUserDetails.bin", ios::binary | ios::in);
        if (!file) {
            cout << "Couldn't open file." << endl;
            return;
        }
        RegularUser exp;
        while (file.read((char*)(&exp), sizeof(exp)))
        {

            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "              First Name: " << exp.firstname << endl;
            cout << "              Last Name: " << exp.lastname << endl;
            cout << "              Gender: " << exp.gender << endl;
            cout << "              Height: " << exp.height << endl;
            cout << "              ID: " << exp.id << endl;
            cout << "              Weight: " << exp.weight << endl;
            cout << "              Age: " << exp.age << endl;
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        }
        file.close();
    }
    void challenges_competitions() {
        int opt = 0;
        system("cls");
        cout << "\033[37m";
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        cout << "                         <<Challenges Menu>>                                " << endl;
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        cout << "                Join challenge                            [1]               " << endl;
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        cout << "                Score Board                               [2]               " << endl;
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        cout << "                View Batches                              [3]               " << endl;
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        cout << "                Exit                                      [4]               " << endl;
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        cout << "Option : ";
        cout << "\033[0m";
        cin >> opt;
        switch (opt)
        {
        case 1:
        {
            cha.join_challenge();
            cout << "              Enter yes if you want to see Challenges Menu  again " << endl;
            string permit;
            cin >> permit;
            if (permit == "yes")
                challenges_competitions();
            break;
        }
        case 2:
        {
            cha.score_board();
            string p;
            cout << "              Enter yes if you want to see Challenges Menu again "; cin >> p; cout << endl;
            if (p == "yes")
                challenges_competitions();
            break;
        }
        case 3:
        {
            cha.view_batches();
            cout << "               Enter yes if you want to see Challenges Menu again " << endl;
            string permit;
            cin >> permit;
            if (permit == "yes")
                challenges_competitions();
            break;
        }
        case 4:
        {
            exit(0);
            break;
        }
        default:
        {
            exit(0);
        }
        }
    }
    void social()
    {
        int opt = 0;
        system("cls");
        cout << "\033[36m";
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        cout << "                         <<Social Interaction Menu>>                        " << endl;
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        cout << "                Share Experience                          [1]               " << endl;
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        cout << "                Update EXperience                         [2]               " << endl;
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        cout << "                Delete EXperience                         [3]               " << endl;
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        cout << "                View all Experiences                      [4]               " << endl;
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        cout << "                Direct Messaging                          [5]               " << endl;
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        cout << "                Exit                                      [6]               " << endl;
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        cout << "Option : ";
        cout << "\033[0m";
        cin >> opt;
        switch (opt)
        {
        case 1:
        {
            string name;
            string message;
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "              Enter name: "; cin >> name; cout << endl;
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "              Enter EXperience in Fitness: "; cin >> message; cout << endl;
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            e.shareExperience(name, message);
            cout << "              Enter yes if you want to see social interaction menu again " << endl;
            string permit;
            cin >> permit;
            if (permit == "yes")
                social();
            break;
        }
        case 2:
        {
            string p;
            string message;
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "              Enter your updated Experience in Fitness: "; cin >> message; cout << endl;
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            e.updateExperience(message);
            cout << "              Enter yes if you want to see social interaction menu again "; cin >> p; cout << endl;
            if (p == "yes")
                social();
            break;
        }
        case 3:
        {
            e.deleteExperience();
            cout << "               Enter yes if you want to see social interaction menu again " << endl;
            string permit;
            cin >> permit;
            if (permit == "yes")
                social();
            break;
        }
        case 4:
        {

            e.displayAllExperiences();
            cout << "              Enter yes if you want to see social interaction menu again " << endl;
            string permit;
            cin >> permit;
            if (permit == "yes")
                social();

            break;
        }
        case 5:
        {

            e.direct_messages();
            cout << "              Enter yes if you want to see social interaction menu again " << endl;
            string permit;
            cin >> permit;
            if (permit == "yes")
                social();
            break;
        }
        case 6:
        {
            exit(0);
            break;
        }
        default:
        {
            exit(0);
        }

        }

    }
    void location_based_features()
    {
        int opt = 0;
        system("cls");
        cout << "\033[38;2;255;215;0m";
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        cout << "                      <<Location's Activities Menu>>                        " << endl;
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        cout << "                Add Activity based on location            [1]               " << endl;
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        cout << "                Update Activity based on location         [2]               " << endl;
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        cout << "                Delete Activity based on location         [3]               " << endl;
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        cout << "                View all Details                          [4]               " << endl;
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        cout << "                Exit                                      [5]               " << endl;
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        cout << "Option : ";
        cout << "\033[0m";
        cin >> opt;
        switch (opt)
        {
        case 1:
        {
            l.addActivity_based_on_location();
            cout << "              Enter yes if you want to see Location's Activities Menu again " << endl;
            string permit;
            cin >> permit;
            if (permit == "yes")
                location_based_features();
            break;
        }
        case 2:
        {
            string p;
            l.update_activity_based_on_location();
            cout << "              Enter yes if you want to see Location's Activities Menu again "; cin >> p; cout << endl;
            if (p == "yes")
                location_based_features();
            break;
        }
        case 3:
        {
            l.deleteActivity_based_on_location();
            cout << "               Enter yes if you want to see Location's Activities Menu again " << endl;
            string permit;
            cin >> permit;
            if (permit == "yes")
                location_based_features();
            break;
        }
        case 4:
        {
            l.display_activities();
            cout << "              Enter yes if you want to see Location's Activities Menu again " << endl;
            string permit;
            cin >> permit;
            if (permit == "yes")
                location_based_features();
            break;
        }
        case 5:
        {
            exit(0);
            break;
        }
        default:
        {
            exit(0);
        }
        }
    }
    void track_nutrition() {
        int opt = 0;
        system("cls");
        cout << "\033[36m";
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        cout << "                           <<Nutrition Track Menu>>                         " << endl;
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        cout << "                Enter nutrtion                            [1]               " << endl;
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        cout << "                Update nutrtion                           [2]               " << endl;
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        cout << "                Recommendation based on meal taken        [3]               " << endl;
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        cout << "                Deletion of nutrtion                      [4]               " << endl;
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        cout << "                View nutritious graph                     [5]               " << endl;
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        cout << "                Most effective nutrtion advices           [6]               " << endl;
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        cout << "               Calorie Consumption graph                  [7]               " << endl;
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        cout << "                Exit                                      [8]               " << endl;
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        cout << "Option : ";
        cout << "\033[0m";
        cin >> opt;
        switch (opt)
        {
        case 1:
        {
            o.log_your_meal_enter_details();
            o.writing_data_in_database();
            cout << "             Enter yes if you want to see nutrition track menu again " << endl;
            string permit;
            cin >> permit;
            if (permit == "yes")
                track_nutrition();
            break;
        }
        case 2:
        {
            o.log_your_meal_enter_details();
            o.writing_data_in_database();
            cout << "              Enter yes if you want to see nutrition track menu again " << endl;
            string permit;
            cin >> permit;
            if (permit == "yes")
                track_nutrition();
            break;
        }
        case 3:
        {
            o.recommendations_based_on_meal_taken();
            cout << "               Enter yes if you want to see nutrition track menu again " << endl;
            string permit;
            cin >> permit;
            if (permit == "yes")
                track_nutrition();
            break;
        }
        case 4:
        {
            o.deletion_nutrition();
            cout << "              Your workout nutrtiton recorde are deleted from the database" << endl;
            cout << "              Enter yes if you want to see nutrition track menu again " << endl;
            string permit;
            cin >> permit;
            if (permit == "yes")
                track_nutrition();
            break;
        }
        case 5: {
            o.show_graph();
            cout << "              Enter yes if you want to see nutrition track menu again " << endl;
            string permit;
            cin >> permit;
            if (permit == "yes")
                track_nutrition();
            break;
        }
        case 6:
        {
            o.track_most_effective_nutrition();
            cout << "              Enter yes if you want to see nutrition track menu again " << endl;
            string permit;
            cin >> permit;
            if (permit == "yes")
                track_nutrition();
            break;
        }
        case 7:
        {
            o.calorie_consumption_graph();
            cout << "              Enter yes if you want to see nutrition track menu again " << endl;
            string permit;
            cin >> permit;
            if (permit == "yes")
                track_nutrition();
            break;
        }
        case 8:
        {
            exit(0);
            break;
        }
        default:
        {
            exit(0);
        }
        }


    }
    void entertrainerfeedback()
    {
        cin >> feedback;
    }
    void resetpaasword() {
        string x;
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        cout << "              Are there chances that you may forget paasword then reset password (yes/no)"; cin >> x; cout << endl;
        if (x == "yes")
        {
            cout << "              Enter new paasword "; enterpassword();
        }
    }
    void workout_tracking() {
        int opt = 0;
        system("cls");
        cout << "\033[36m";
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        cout << "                           <<Workout Track Menu>>                           " << endl;
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        cout << "                Enter, Update daily workouts                   [1]               " << endl;
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        cout << "                Deletion of workout                            [2]               " << endl;
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~                " << endl;
        cout << "                Most effective workout based on fitness goals  [3]               " << endl;
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        cout << "                View workout and log workout                   [4]               " << endl;
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        cout << "                tracking trends in workout                     [5]               " << endl;
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        cout << "Option : ";
        cout << "\033[0m";
        cin >> opt;
        switch (opt)
        {
        case 1:
        {
            obj.enterworkoutdetails();
            obj.writing_data_in_database();
            cout << "              Enter yes if you want to see workout track menu again " << endl;
            string permit;
            cin >> permit;
            if (permit == "yes")
                workout_tracking();
            break;
        }

        case 2:
        {
            obj.deletion_workout();
            cout << "              Your workout recorde are deleted from the database" << endl;
            cout << "              Enter yes if you want to see workout track menu again " << endl;
            string permit;
            cin >> permit;
            if (permit == "yes")
                workout_tracking();
            break;
        }
        case 3:
        {
            obj.most_effective_workout();
            cout << "              Enter yes if you want to see workout track menu again " << endl;
            string permit;
            cin >> permit;
            if (permit == "yes")
                workout_tracking();
            break;
        }
        case 4:
        {
            obj.View_workout_and_log_workout();
            cout << "              Enter yes if you want to see workout track menu again " << endl;
            string permit;
            cin >> permit;
            if (permit == "yes")
                workout_tracking();
            break;
        }
        case 5:
        {
            obj.compare_daily_workout_graph();
            cout << "              Enter yes if you want to see workout track menu again " << endl;
            string permit;
            cin >> permit;
            if (permit == "yes")
                workout_tracking();
            break;
        }
        default:
        {
            exit(0);
        }
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
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        cout << "              You have been successfully Registered, Regular user" << endl;
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
            if (users[i][1] == id)
            {
                cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
                cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
                cout << "               Enter the password ";
                cin >> pass;
                if (users[i][0] == pass)
                {

                    break;
                }
                else
                {
                    string forgot;
                    cout << "                    ";
                    cout << endl << "Incorrect Password" << endl;
                    cout << " Forgot Paasword (yes/no)"; cin >> forgot; cout << endl;
                    if (forgot == "yes")
                    {
                        break;
                    }
                    Login();
                    break;
                }
            }
            else
            {
                cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
                cout << "                        ";
                cout << endl << "User with this id doesnot exist" << endl;
                cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
                Login();
                break;
            }
        }

    }
    void ReadFromFile()
    {
        ifstream infile("RegularUserDetails.bin", ios::binary);
        if (!infile)
        {
            cout << "File doesn't exist. Creating a new file." << endl;
            ofstream createFile("RegularUserDetails.bin");
            createFile.close();

            infile.open("RegularUserDetails.bin", ios::binary);
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
        int i = 40;
        while (numUsers < 50 && infile >> users[numUsers][0] >> users[numUsers][1])
        {

            string password, id, lastName, firstName;
            char gender;
            double weight, height;
            int age;

            infile >> password >> id >> lastName >> firstName >> gender >> weight >> age >> height;

            users[i][0] = id;
            users[i][1] = password;
            i++;
        }

        infile.close();
    }
    void WriteToFile()
    {
        ofstream outfile("RegularUserDetails.bin", ios::binary | ios::app);
        if (!outfile)
        {
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "Couldn't open the file." << endl;
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            return;
        }

        string id = getId();
        string lastName = getLastName();
        string firstName = getFirstName();
        char gender = getGender();
        double weight = getWeight();
        int age = getAge();
        double height = getHeight();
        string password = getPassword();
        users[numUsers][1] = id;
        users[numUsers][0] = password;
        numUsers++;
        outfile.write((char*)(this), sizeof(*this));
        outfile.close();
    }

};