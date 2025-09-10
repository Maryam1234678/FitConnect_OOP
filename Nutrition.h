
#include<iostream>
#include<string>
#include<fstream>
#include<iomanip>
using namespace std;

class Nutrition {
private:
	string mealName;
	int calories;
	int proteins;
	int carbohydrates;
	int fats;
	string fitness_goal;
public:
	Nutrition() {//constructor
		mealName = "";
		calories = 0;
		proteins = 0;
		carbohydrates = 0;
		fats = 0;
		fitness_goal = "";
	}
	void deletion_nutrition() {
		//deleting the data form the file
		ofstream d("NutritonTrack.bin", ios::binary | ios::trunc);
		d.close();
	}
	void log_your_meal_enter_details() {

		system("cls");
		cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
		cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
		cout << "              Enter your meal Name :(breakfast,lunch,dinner)" << endl;
		cout << "              "; cin >> mealName;
		cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
		cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
		cout << "              Enter your Calories" << endl;
		cout << "              "; cin >> calories;
		cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
		cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
		cout << "              Enter your Protein" << endl;
		cout << "              "; cin >> proteins;
		cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
		cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
		cout << "              Enter your carbohydrates" << endl;
		cout << "              "; cin >> carbohydrates;
		cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
		cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
		cout << "              Enter your fats" << endl;
		cout << "              "; cin >> fats;
		cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
		cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
		cout << "              Enter your fitness goals(lose_weight, build_muscle,  overall_health,)" << endl;
		cout << "              "; cin >> fitness_goal;

	}
	void Draw_nutrition_horizontal_graph(const string& lab, int num)
	{
		
			cout << setw(15) << left << lab << " |  ";
			while (num > 50)
				num /= 2;
			for (int i = 0; i < num; i++) {
				cout << "*";
			}
			cout << endl;
	}
	void show_graph() {
		cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
		cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
		Draw_nutrition_horizontal_graph("Calories ", calories);
		cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
		cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
		Draw_nutrition_horizontal_graph("Proteins", proteins);
		cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
		cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
		Draw_nutrition_horizontal_graph("Carbohydrates", carbohydrates);
		cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
		cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
		Draw_nutrition_horizontal_graph("Fats", fats);
		cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
		cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
	}
	void recommendations_based_on_meal_taken()
	{
		if (fitness_goal == "lose_weight")
		{
			cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
			cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
			cout << "	           To lose weight effectively :" << endl;
			cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
			cout << "              Monitor calorie intake, aiming for a deficit." << endl;
			cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
			cout << "              Limit consumption of high - fat and high - calorie foods." << endl;
			cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
			cout << "              Opt for complex carbohydrates over simple sugars." << endl;
			cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
			cout << "              Balance macronutrients for sustainable weight loss." << endl;
			cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
			cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
		}
		else if (fitness_goal == "build_muscle")
		{
			cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
			cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
			cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
			cout << "              For muscle building :" << endl;
			cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
			cout << "              Increase calorie intake to support muscle growth and repair. " << endl;
			cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
			cout << "              Focus on consuming adequate protein for muscle synthesis." << endl;
			cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
			cout << "              Incorporate complex carbohydrates to fuel workouts and replenish glycogen stores." << endl;
			cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
			cout << "           	Balance macronutrients to optimize energy levels and promote muscle recovery." << endl;
			cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
			cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
			cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
		}
		else if (fitness_goal == "overall_health")
		{
			cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
			cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
			cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
			cout << "             To enhance overall health :" << endl;
			cout << "             Consume a balanced diet rich in nutrients, including vitamins, minerals, and antioxidants." << endl;
			cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
			cout << "             Be mindful of calorie intake to maintain a healthy weight and energy balance." << endl;
			cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
			cout << "             Include a variety of complex carbohydrates for sustained energy and fiber to support digestive health." << endl;
			cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
			cout << "             Prioritize whole, unprocessed foods while minimizing intake of added sugars and unhealthy fats for optimal health outcomes." << endl;
			cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
			cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
			cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;

		}
	}
	void writing_data_in_database()
	{
		ofstream f("NutritonTrack.bin", ios::binary | ios::app);
		if (!f)
		{
			cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
			cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
			cout << "Couldn't open the file." << endl;
			cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
			cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
			return;
		}
		f.write("Meal Name: ", sizeof("Meal Name: "));
		f.write((char*)(&mealName), sizeof(mealName));
		f.write("Calories: ", sizeof("Calories: "));
		f.write((char*)(&calories), sizeof(calories));
		f.write("Proteins: ", sizeof("Proteins: "));
		f.write((char*)(&proteins), sizeof(proteins));
		f.write("Carbohydrates: ", sizeof("Carbohydrates: "));
		f.write((char*)(&carbohydrates), sizeof(carbohydrates));
		f.write("Fats: ", sizeof("Fats: "));
		f.write((char*)(&fats), sizeof(fats));

		f.close();
	}
	void track_most_effective_nutrition()
	{
			double carbRatio = carbohydrates / calories;
			double fatRatio = fats / calories;
			double proteinRatio = proteins / calories;
			//on the basis of user intake of nutrients and fitness goals i am telling the user which nutrient is most effective for him or her
			if (fitness_goal == "overall_health") {
				//balanced intake of nutrients is required
				if (carbRatio >= 0.45 && carbRatio <= 0.65 &&
					fatRatio >= 0.20 && fatRatio <= 0.35 &&
					proteinRatio >= 0.10 && proteinRatio <= 0.35) {
					cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
					cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
					cout<< "              Balanced intake of carbs, fats, and proteins is effective for improving health.";
					cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
					cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
				}
				else {
					cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
					cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
					cout << "              Consider adjusting macronutrient ratios for a balanced diet to improve health.";
					cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
					cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
				}
			}
			else if (fitness_goal == "lose_weight") {
				// less calories and adequate protein is required
				if (calories < 2000 && proteinRatio >= 0.15) {
					cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
					cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
					cout << "              Moderate protein intake and calorie deficit are effective for weight loss.";
					cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
					cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
				}
				else {
					cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
					cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
					cout << "              Consider reducing calorie intake and increasing protein consumption for weight loss.";
					cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
					cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
				}
			}
			else if (fitness_goal == "build_muscle") {
				// higher levels of protein and calorie are required
				if (proteinRatio >= 0.25 && calories > 2500) {
					cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
					cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
					cout << "              High protein intake and calorie surplus are effective for muscle building.";
					cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
					cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
				}
				else {
					cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
					cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
					cout << "              Consider increasing protein intake and calorie consumption for muscle building.";
					cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
					cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
				}
			}
			else {
				cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
				cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
				cout << "              Invalid fitness goal. ";
				cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
				cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
			}
	}
	void calorie_consumption_graph() {
		cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
		int cal = calories;
		while (calories > 20) {
			calories -= 5;
		}
		bool upward = calories >= 0;
		int absVal = abs(calories);
		for (int i = 1; i <= absVal; i++) {
			int spaces ;
			if (upward)
				spaces = i - 1;
			else
				spaces = absVal - i;
			for (int j = 0; j < spaces; j++) {
				cout << " ";
			}
			cout << "*" << endl;
		}
		cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
	}
};
