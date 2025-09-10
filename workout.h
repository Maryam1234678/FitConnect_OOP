
#include<iostream>
#include<string>
#include<fstream>

using namespace std;

class workout
{
	
private:
	string workout_type;
	int duration;
	double calories;
	string intensity;
	string timestamp;
public:
	workout(string type = "", int durat = 0, string intense = "", string times = "")
	{
		workout_type = type;
		duration = durat;
		intensity = intense;//intensity is either moderate, high or low
		timestamp = times;
		calories = 0.0;
	}
	void Draw_workout_horizontal_graph(const string& lab, int num)
	{

		cout << setw(15) << left << lab << " |  ";
		while (num > 50)
			num /= 2;
		for (int i = 0; i < num; i++) {
			cout << "*";
		}
		cout << endl;
	}
	void most_effective_workout() {
		cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
		cout << "              Enter fitness goal so that we can recommend you the most effective workout that suits your body ( improve_health,lose_weight,build_muscle )" << endl;
		cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
		string fitness;
		cout << "              Fitness: "; cin >> fitness; cout << endl;
		if (fitness == "improve_health") {
			cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
			cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
			cout << "              For improving health, focus on a combination of aerobic exercises (e.g., walking, cycling) and strength training (e.g., bodyweight exercises, resistance training). Aim for at least 150 minutes of moderate-intensity aerobic activity or 75 minutes of vigorous-intensity aerobic activity per week, along with muscle-strengthening activities on two or more days per week." << endl;
			cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
			cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
		}
		else if (fitness == "lose_weight") {
			cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
			cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
			cout << "              For weight loss, prioritize cardiovascular exercises (e.g., running, swimming, cycling) to burn calories and increase heart rate. High-intensity interval training (HIIT) and circuit training are effective for maximizing calorie burn and boosting metabolism. Combine cardio workouts with strength training exercises to build lean muscle mass and enhance fat loss." << endl;
			cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
		
			cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
		}
		else if (fitness == "build_muscle") {
			cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
			cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
			cout << "              To build muscle, focus on resistance training exercises such as weightlifting, bodyweight exercises, and resistance band workouts. Target major muscle groups with compound exercises (e.g., squats, deadlifts, bench presses) and include isolation exercises to target specific muscles. Incorporate progressive overload by gradually increasing weights and reps to stimulate muscle growth." << endl;
			cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
			cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
		}
		else {
			cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
			cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
			cout << "              Invalid fitness goal" << endl;
			cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
			cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
		}
	}
	void enterworkoutdetails()
	{
		system("cls");
		cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
		cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
		cout << "              Enter the type of workout you have done "; cin >> workout_type; cout << endl;
		cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
		cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
		cout << "              Enter the duration in the minutes "; cin >> duration; cout << endl;
		cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
		cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
		cout << "              Enter the intensity of your workout(high,low,moderate) "; cin >> intensity; cout << endl;
		cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
		cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
		cout << "              Enter the timestamp for your workout "; cin >> timestamp; cout << endl;
		cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
		cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
		cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
	}
	void compare_daily_workout_graph()
	{
		Draw_workout_horizontal_graph(workout_type, 10);
	}
	void View_workout_and_log_workout() {
		if (intensity == "low" || intensity == "Low")
		{
			calories = 4 * (duration) * 0.016;
		}
		else if (intensity == "medium" || intensity == "moderate" || intensity == "Moderate" || intensity == "Medium")
		{
			calories = 7 * (duration ) * 0.016;
		}
		else if (intensity == "high" || intensity == "High")
		{
			calories = 10 * (duration ) * 0.016;
		}
		cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
		cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
		cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
		cout << "                Workout Type :" << workout_type << endl;
		cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
		cout << "                Duration : " << duration << endl;
		cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
		cout << "                Intensity : " << intensity << endl;
		cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
		cout << "                Timestamp : " << timestamp << endl;
		cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
		cout << "                You have burned" << " Calories: " << calories << endl;
		cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
		cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
		cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
	}
	void writing_data_in_database()
	{
		ofstream file("WorkoutDetails.bin", ios::binary | ios::app);
		if (!file)
		{
			cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
			cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
			cout << "Couldn't open the file." << endl;
			cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
			cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
			return;
		}
		file.write("WorkoutType: ", sizeof("WorkoutType: "));
		file.write(reinterpret_cast<const char*>(&workout_type), sizeof(workout_type));
		file.write("Duration: ", sizeof("Duration: "));
		file.write(reinterpret_cast<const char*>(&duration), sizeof(duration));
		file.write("Intensity: ", sizeof("Intensity: "));
		file.write(reinterpret_cast<const char*>(&intensity), sizeof(intensity));
		file.write("Timestamp: ", sizeof("Timestamp: "));
		file.write(reinterpret_cast<const char*>(&timestamp), sizeof(timestamp));
		file.write("Calories: ", sizeof("Calories: "));
		file.write(reinterpret_cast<const char*>(&calories), sizeof(calories));

		file.close();
	}
	void deletion_workout() {
		ofstream d("WorkoutDetails.bin", ios::binary | ios::trunc);
		d.close();
	}
};
