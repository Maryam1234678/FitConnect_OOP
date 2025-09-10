#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class Location_Activity{
private:
    string activity_name;
    string location;
    string details_of_activity;

public:
    Location_Activity()
    {
        activity_name = "";
        location = "";
        details_of_activity="";
    }

    void set_name( string& name) 
    { 
        activity_name = name; 
    }
    void set_location( string& locat)
    {
        location = locat;
    }
    void set_details( string& detail) 
    { 
        details_of_activity = detail;
    }
    string getActivityName() const 
    { 
        return activity_name;
    }
    string getLocation() const 
    { 
        return location;
    }
    string getDetails() const 
    { 
        return details_of_activity;
    }
    void addActivity_based_on_location() 
    {
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        cout << "                Enter activity name: "; cin >> activity_name; cout << endl;
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        cout << "                Enter location: "; cin >> location; cout << endl;
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        cout << "                Enter details of activity: "; cin >> details_of_activity; cout << endl;
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;

        ofstream outFile("LocationBasedActivities.bin", ios::binary | ios::app);
        if (!outFile) {
            cout << "Couldn't open the file." << endl;
            return;
        }
        outFile.write((char*)(this), sizeof(*this));
        outFile.close();
    }
    void update_activity_based_on_location() 
    {
        ofstream d("LocationBasedActivities.bin", ios::binary | ios::trunc);
        d.close();
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        cout << "                Enter updated activity name: "; cin >> activity_name; cout << endl;
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        cout << "                Enter updated location: "; cin >> location; cout << endl;
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        cout << "                Enter updated details of activity: "; cin >> details_of_activity; cout << endl;
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;

        ofstream outFile("LocationBasedActivities.bin", ios::binary | ios::app);
        if (!outFile) {
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "Couldn't open the file." << endl;
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            return;
        }
        outFile.write((char*)(this), sizeof(*this));
        outFile.close();
    }
    void deleteActivity_based_on_location() 
    {
        ofstream d("LocationBasedActivities.bin", ios::binary | ios::trunc);
        d.close();
    }
    void display_activities()
    {
        ifstream e("LocationBasedActivities.bin", ios::binary|ios::in);
        if (!e) {
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "Couldn't open the file." << endl;
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            return;
        }

        Location_Activity disp;
        while (e.read((char*)(&disp), sizeof(disp))) 
        {
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "               Activity Name: " << disp.getActivityName() << endl;
            cout << "               Location: " << disp.getLocation() << endl;
            cout << "               Details: " << disp.getDetails() << endl;
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        }

        e.close();
    }
};

