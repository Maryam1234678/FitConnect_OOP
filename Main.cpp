#include<iostream>
#include<string>
#include<fstream>
#include<iomanip>
#include<conio.h>
#include<cstring>
#include"user.h"
#include"admin.h"
#include"regularuser.h"
#include"trainer.h"

using namespace std;

class Menu {
private:
    Admin A;
    RegularUser U;
    Trainer T;
    bool logged;
public:
    Menu() {
        logged = false;
    }
    void MainMenu()
    {
        int option;
        do
        {
            system("cls");
            cout << "\033[37m";
            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
            cout << "\033[31m";
            cout << "              Welcome to FitConnect: Fitness Tracking Application" << endl;
            cout << "\033[37m";
            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;
            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~<< MENU >>~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "               Regular User                              [1]" << endl;
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "               Admin                                     [2]" << endl;
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "               Trainer                                   [3]" << endl;
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "               Exit                                      [4]" << endl;
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "Option: ";
            cout << "\033[0m";
            cin >> option;
            switch (option)
            {
            case 1:
            {
                CustomerMenu();
                break;
            }
            case 2:
            {
                AdminMenu();
                break;
            }
            case 3:
            {
                TrainerMenu();
                break;
            }
            case 4:
            {
                exit(0);
            }
            default:
            {
                cout << "Invalid Option! Try Again! Choose some other opwtion" << endl << endl;;
                break;
            }
            }
        } while (option > 4 || option < 1);

    }
    void CustomerMenu() {
        bool feedback = false;
        int regularoption;
        do {
            system("cls");
            cout << "\033[37m";
            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;
            cout << "\033[34m";
            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~<< Customer VIEW >>~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;
            cout << "\033[37m";;
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "               Login                                     [1]" << endl;
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "               Register                                  [2]" << endl;
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "               Main Menu                                 [3]" << endl;
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "               Logout                                    [4]" << endl;
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "               Exit                                      [5]" << endl;
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "Option: ";
            cout << "\033[0m";
            cin >> regularoption;
        } while (regularoption > 5 || regularoption < 1);
        switch (regularoption) {
        case 1:
        {
            if (logged == false)
            {
                U.Login();
                logged = true;
                subcustomerMenu();
            }
            else {
                U.Login();
                logged = true;
                subcustomerMenu();
            }
            break;
        }
        case 2:
        {
            U.Register();
            CustomerMenu();
            logged = true;
            break;
        }
        case 3:
        {
            MainMenu();
            break;
        }
        case 4:
        {
            logged = false;
            CustomerMenu();
            break;
        }
        case 5:
        {
            exit(0);
        }
        }

    }
    void subcustomerMenu() {
        int regularoption;
        do {
            system("cls");
            cout << "\033[37m";
            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;
            cout << "\033[34m";
            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~<< Sub Customer VIEW >>~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;
            cout << " \033[37m";
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "               Main Menu                                 [1]" << endl;
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "               Track Workout                             [2]" << endl;
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "               Track Nutrition                           [3]" << endl;
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "               Social Interaction                        [4]" << endl;
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "               Logout                                    [5]" << endl;
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "               Exit                                      [6]" << endl;
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "               Submit Feedback of trainers               [7]" << endl;
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "               Location based Features                   [8]" << endl;
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "               Challenges and Competitions               [9]" << endl;
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "                Select a trainer                         [10]               " << endl;
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "                Changing trainer                         [11]               " << endl;
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~              " << endl;
            cout << "Option: ";

            cin >> regularoption;
        } while (regularoption > 11 || regularoption < 1);
        switch (regularoption)
        {
        case 1:
        {
            MainMenu();
            break;
        }
        case 2:
        {
            string y;
            U.workout_tracking();
            cout << "               Enter yes to go back to sub customer menu " << endl;
            cin >> y;
            if (y == "yes" || y == "Yes")
                subcustomerMenu();
            break;
        }
        case 3:
        {

            U.track_nutrition();
            cout << "               Enter yes to go back to sub customer menu " << endl;
            string x;
            cin >> x;
            if (x == "yes" || x == "Yes")
                subcustomerMenu();
            break;
        }
        case 4:
        {
            string x;
            U.social();
            cout << "               Enter yes to go back to sub customer menu " << endl;
            cin >> x;
            if (x == "yes" || x == "Yes")
                subcustomerMenu();
            break;
        }
        case 5:
        {
            logged = false;
            CustomerMenu();
            break;
        }
        case 6:
        {
            exit(0);
        }
        case 7:
        {
            system("cls");
            char array[40];
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "              Enter the id of trainer whose feedback you want to submit" << endl;
            string id;
            cin >> id;
            if (T.checktrainerpresence(id) == true) {
                cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
                cout << "              Enter the feedback for the trainer :";   cin >> array; cout << endl;
                A.writing_feedback_of_trainers_to_file(array, 40);
                cout << "              Thank you for recording the feed back. Your feedback is successfully saved and recorded and admin can view it " << endl;
            }
            else {
                cout << "               Trainer of id " << id << " does not exist " << endl;
            }
            cout << "               Enter yes to go back to sub customer menu " << endl;
            string x;
            cin >> x;
            if (x == "yes" || x == "Yes")
                subcustomerMenu();
            subcustomerMenu();
            break;
        }
        case 8:
        {
            U.location_based_features();
            cout << "               Enter yes to go back to sub customer menu " << endl;
            string x;
            cin >> x;
            if (x == "yes" || x == "Yes")
                subcustomerMenu();
            break;
        }
        case 9:
        {
            U.challenges_competitions();
            cout << "               Enter yes to go back to sub customer menu " << endl;
            string x;
            cin >> x;
            if (x == "yes" || x == "Yes")
                subcustomerMenu();
            break;
        }
        case 10:
        {
            T.selecting_a_trainer();
            cout << "               Enter yes to go back to sub customer menu " << endl;
            string x;
            cin >> x;
            if (x == "yes" || x == "Yes")
                subcustomerMenu();
            break;

        }
        case 11:
        {
            T.changing_a_trainer();
            cout << "               Enter yes to go back to sub customer menu " << endl;
            string x;
            cin >> x;
            if (x == "yes" || x == "Yes")
                subcustomerMenu();
            break;

        }
        }
    }
    void AdminMenu() {
        int regularoption;
        do {
            system("cls");
            cout << "\033[37m";
            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;
            cout << "\033[34m";
            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~<< Admin VIEW >>~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;
            cout << "\033[37m";
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "               Login                                     [1]" << endl;
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "               Register                                  [2]" << endl;
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "               Main Menu                                 [3]" << endl;
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "               Logout                                    [5]" << endl;
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "               Exit                                      [6]" << endl;
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "Option: ";
            cout << "\033[0m";
            cin >> regularoption;
        } while (regularoption > 5 || regularoption < 1);
        switch (regularoption) {
        case 1:
        {
            if (logged == false)
            {
                A.Login();
                logged = true;
                SubAdminMenu();
            }
            else {
                A.Login();
                logged = true;
                SubAdminMenu();
            }
            break;
        }
        case 2:
        {
            A.Register();
            AdminMenu();
            logged = true;
            break;
        }
        case 3:
        {
            MainMenu();
            break;
        }
        case 4:
        {
            logged = false;
            AdminMenu();
            break;
        }

        case 5:
        {
            exit(0);
        }
        }
    }
    void TrainerMenu() {
        int regularoption;
        do {
            system("cls");
            cout << "\033[37m";
            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;
            cout << "\033[34m";
            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~<< Trainer VIEW >>~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;
            cout << "\033[37m";

            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "               Login                                     [1]" << endl;
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "               Register                                  [2]" << endl;
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "               Main Menu                                 [3]" << endl;
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "               Logout                                    [4]" << endl;
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "               Exit                                      [5]" << endl;
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "Option: ";
            cout << "\033[0m";
            cin >> regularoption;
        } while (regularoption > 5 || regularoption < 1);
        switch (regularoption) {
        case 1:
        {
            if (logged == false)
            {
                T.Login();
                logged = true;
                subTrainerMenu();
            }
            break;
        }
        case 2:
        {
            T.Register();
            TrainerMenu();
            logged = true;
            break;
        }
        case 3:
        {
            MainMenu();
            break;
        }
        case 4:
        {
            logged = false;
            TrainerMenu();
            break;
        }

        case 5:
        {
            exit(0);
        }
        }
    }
    void SubAdminMenu()
    {
        int regularoption;
        do {
            system("cls");
            cout << "\033[37m";
            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;
            cout << "\033[34m";
            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~<<Sub Admin VIEW >>~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;
            cout << "\033[37m";
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "               View customer details                     [1]" << endl;
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "               View feedback of clients to trainers      [2]" << endl;
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "               Logout                                    [3]" << endl;
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "               Exit                                      [4]" << endl;
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "Option: ";
            cout << "\033[0m";
            cin >> regularoption;
        } while (regularoption > 4 || regularoption < 1);
        switch (regularoption) {
        case 1:
        {
            //A.view_details_customers();
            U.view_all_details();
            string x;
            cout << "Enter yes to go back to sub admin menu " << endl;
            cin >> x;
            if (x == "yes" || x == "Yes")
                SubAdminMenu();
            break;
        }
        case 2:
        {
            A.view_trainers_feedback_from_clients_read_file();
            string x;
            cout << "Enter yes to go back to sub admin menu " << endl;
            cin >> x;
            if (x == "yes" || x == "Yes")
                SubAdminMenu();
            break;
        }
        case 3:
        {
            logged = false;
            AdminMenu();
            break;
        }
        case 4:
        {

            exit(0);

        }

        }
    };
    void subTrainerMenu()
    {
        int regularoption;
        do {
            system("cls");
            cout << "\033[37m";
            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;
            cout << "\033[34m";
            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~<<Sub Trainer VIEW >>~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;
            cout << "\033[37m";
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "               Share your experience                     [1]" << endl;
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "               share you success stories                 [2]" << endl;
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "               Logout                                    [3]" << endl;
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "               Exit                                      [4]" << endl;
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "               Trainer Menu                              [5]" << endl;
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "Option: ";
            cout << "\033[0m";
            cin >> regularoption;
        } while (regularoption > 4 || regularoption < 1);
        switch (regularoption) {
        case 1:
        {
            T.shareexperience();
            string x;
            cout << "              Enter yes to go back to sub tariner menu " << endl;
            cin >> x;
            if (x == "yes" || x == "Yes")
                subTrainerMenu();
            break;
        }
        case 2:
        {
            T.shareSuccessStory();
            string x;
            cout << "              Enter yes to go back to sub trainer menu " << endl;
            cin >> x;
            if (x == "yes" || x == "Yes")
                subTrainerMenu();
            break;
        }
        case 3:
        {
            logged = false;
            TrainerMenu();
            break;
        }
        case 4:
        {

            exit(0);
            break;

        }
        case 5:
        {
            TrainerMenu();
            break;
        }
        }
    }
};

int main()
{
    Menu object;
    object.MainMenu();
    return 0;
}


