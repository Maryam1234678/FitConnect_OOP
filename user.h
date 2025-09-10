
#include<iostream>
#include<string>
using namespace std;

class User {
protected:
    string firstname;
    string lastname;
    char gender;
    char password[8];
    string id;
    int age;
    int weight;
    float height;
public:
    User() {
        firstname = "";
        lastname = "";
        gender = 'M';
        for (int i = 0; i < 8; i++)
            password[i] = '*';
        id = "";
        age = 0;
        weight = 0;
        height = 0;
    }
    void enterfirstname()
    {
        cin >> firstname;
    }
    void enterpassword()
    {
        int passwordlength = 8;
        bool islowercase = false;
        bool isuppercase = false;
        bool isspecialchar = false;
        bool isnumeric = false;
        int i = 0;
        while (i < 30)
        {
            char c = _getch();
            if (c != '\r')
            {  // Normal character entered
                password[i] = c;
                if (c > 65 && c < 91 && isuppercase == false)
                {
                    isuppercase = true;

                }

                else if (c > 96 && c < 123 && islowercase == false)
                {
                    islowercase = true;
                }

                else if (c > 47 && c < 58 && isnumeric == false)
                {
                    isnumeric = true;
                }

                else if ((c > 31 && c < 47) || (c > 57 && c < 65) || (c > 90 && c < 97) || (c > 122 && c < 127) && isspecialchar == false)
                {
                    isspecialchar = true;
                }

                cout << '*';
            }
            else
            {  // Enter key pressed
                cout << endl;
                if ((isuppercase == false) || (islowercase == false) || (isspecialchar == false) || (isnumeric == false) || (i != 8))
                {
                    cout << endl << "                    ---------Incorrect Password---------- " << endl;
                }
                if (isuppercase == false)
                {
                    cout << "               The password must contain atleast one uppercase" << endl;
                }
                if (islowercase == false)
                {
                    cout << "               The password must contain atleast one lowercase" << endl;

                }
                if (isspecialchar == false)
                {
                    cout << "               The password must contain atleast one special character" << endl;

                }
                if (isnumeric == false)
                {
                    cout << "               The password must contain atleast one numeric digit" << endl;
                }
                if (i != 8)
                {
                    cout << "               The password must be 8 charcters long" << endl;
                    break;
                }

                if (islowercase && isuppercase && isspecialchar && isnumeric && i == 8)
                {
                    password[i] = '\0';  // Terminate password string
                    return;
                }
                break;
            }
            i++;
        }
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        cout << "               Enter the Password:  ";
        enterpassword();
    }
    void enterlastname()
    {
        cin >> lastname;
    }
    //input validation is done asking user to enter the datils again if paasword is not correct or age ,weight and height are less than 0
    void enterweight() {
        cin >> weight;
       
        if (weight < 0) {
            cout << "Incorrect weight." << endl;
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "               Enter your Weight: ";
            enterweight();
        }
    }
    void enterheight() {
        cin >> height;
        if (height < 0) {
            cout << "Incorrect height." << endl;
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "               Enter your height: ";
            enterheight();
        }
    }
    void entergender()
    {
        cin >> gender;
        if ((gender != 'F') && (gender != 'f') && (gender != 'm') && (gender != 'M'))
        {
            cout << endl << "                      ---------Incorrect Gender---------- " << endl;
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "               Enter your Gender [F/M]: ";
            entergender();
        }
    }
    void enterid()
    {
        cin >> id;
        int i = firstname.length();
        if (i > 30)
        {
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "               The length of the id is very long" << endl;
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        }
    }
    void enterage()
    {
        cin >> age;
        if (age < -1)
        {
            cout << "Incorrect age." << endl;
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "               Enter your Age: ";
            enterage();
        }
    }
    string getFirstName() const
    {
        return firstname;
    }
    void setFirstName(const string& fname)
    {
        firstname = fname;
    }
    string getLastName() const
    {
        return lastname;
    }
    void setLastName(const string& lname)
    {
        lastname = lname;
    }
    char getGender() const
    {
        return gender;
    }
    void setGender(const char& g)
    {
        gender = g;
    }
    string getPassword() const
    {
        return password;
    }
    void setPassword(const string& pass)
    {
        // Copy the string into the char array
        strcpy_s(password, pass.c_str());

    }
    void setWeight(int w) {
        weight = w;
    }
    void setHeight(float h) {
        height = h;
    }
    float getHeight()const {
        return height;
    }
    int getWeight() const {
        return weight;
    }
    string getId() const
    {
        return id;
    }
    void setId(const string& uname)
    {
        id = uname;
    }
    int getAge() const
    {
        return age;
    }
    void setAge(const int& a)
    {
        age = a;
    }
};
