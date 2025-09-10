#include<iostream>
#include<string>
#include<fstream>
#include <cstring>   
#include <iomanip>
#include <cmath>  
using namespace std;

class progress {
private:
    // Choose a fixed capacity. 400 covers more than a year of daily entries.
    static const int MAX_ENTRIES = 400;

    // Max length for date strings stored in records (e.g., "2025-09-10").
    static const int DATE_LEN = 16;

    // ----------------------------- STORAGE ------------------------------------------
    // Parallel fixed-size arrays (no vectors) to store daily progress.
    // Each index i corresponds to the same day across arrays.
    char dates[MAX_ENTRIES][DATE_LEN];  // stored as C-strings for compact binary I/O
    int  calories[MAX_ENTRIES];         // daily calories (from Nutrition)
    int  workoutMinutes[MAX_ENTRIES];   // daily workout minutes (from Workout)
    double weights[MAX_ENTRIES];        // optional daily weight log

    // Count of entries actually used in arrays.
    int count;

    // ----------------------------- GOALS --------------------------------------------
    // User goals that help compute status and streaks.
    int    calorieGoal;   // target calories (e.g., 2000). Lower may be better for "deficit".
    int    workoutGoal;   // target workout minutes per day (e.g., 30).
    double targetWeight;  // target body weight.

    // ----------------------------- UTILITIES -----------------------------------------
    // Record used ONLY for file persistence; mirrors our arrays.
    struct Record {
        char date[DATE_LEN];
        int  cal;
        int  mins;
        double w;
    };

    // Scale long values down for bar graphs so they fit on console gracefully.
    int scaleForBar(int value, int maxStars) const {
        if (value <= 0) 
            return 0;
        // Find a divisor such that "value / divisor" fits into maxStars.
        int divisor = 1;
        while (value / divisor > maxStars) divisor *= 2;
        return (value + divisor - 1) / divisor; // ceil division-ish to avoid zeroing small numbers
    }

    // Basic validation to ensure date fits and count within bounds.
    bool validateAndNormalizeDate(const string& d, char out[DATE_LEN]) const {
        if (d.empty())
            return false;
        // Trim or pad: copy up to DATE_LEN-1 chars and null terminate.
        strncpy(out, d.c_str(), DATE_LEN - 1);
        out[DATE_LEN - 1] = '\0';
        return true;
    }

    // Find index of a date if it already exists (linear search; arrays only).
    int findByDate(const string& d) const {
        for (int i = 0; i < count; ++i) {
            if (strncmp(dates[i], d.c_str(), DATE_LEN) == 0) 
                return i;
        }
        return -1;
    }

    // Swap two indices (used for sorting).
    void swapAt(int i, int j) {
        char tmpDate[DATE_LEN];
        strncpy(tmpDate, dates[i], DATE_LEN);
        strncpy(dates[i], dates[j], DATE_LEN);
        strncpy(dates[j], tmpDate, DATE_LEN);

        int tmpCal = calories[i];
        calories[i] = calories[j];
        calories[j] = tmpCal;

        int tmpMin = workoutMinutes[i];
        workoutMinutes[i] = workoutMinutes[j];
        workoutMinutes[j] = tmpMin;

        double tmpW = weights[i];
        weights[i] = weights[j];
        weights[j] = tmpW;
    }

    // Simple bubble sort by date string (lexicographic; YYYY-MM-DD sorts chronologically).
    void sortByDate() {
        for (int i = 0; i < count - 1; ++i) {
            for (int j = 0; j < count - i - 1; ++j) {
                if (strncmp(dates[j], dates[j + 1], DATE_LEN) > 0) {
                    swapAt(j, j + 1);
                }
            }
        }
    }

    // Print a horizontal bar (e.g., "Calories  | **** (1234)")
    void drawBar(const string& label, int value, int maxStars = 50) const {
        int stars = scaleForBar(value, maxStars);
        cout << setw(15) << left << label << " | ";
        for (int i = 0; i < stars; ++i)
            cout << '*';
        cout << " (" << value << ")\n";
    }

    // Prints a "pseudo line chart" for weight by printing rising/descending offsets.
    void drawWeightLine() const {
        if (count == 0) {
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "              No data to draw weight line.\n";
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            return;
        }
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        cout << "              ~~~~~~~~~~~~~~~~~ Weight (pseudo-line) ~~~~~~~~~~~~~~~~~\n";
        // Normalize weights to small offsets
        double minW = weights[0], maxW = weights[0];
        for (int i = 1; i < count; ++i) {
            if (weights[i] < minW) minW = weights[i];
            if (weights[i] > maxW) maxW = weights[i];
        }
        double span = (maxW - minW);
        if (span == 0.0) span = 1.0; // avoid division by zero; will render a flat line

        for (int i = 0; i < count; ++i) {
            int offset = (int)round(((weights[i] - minW) / span) * 40.0); // 0..40 spaces
            cout << setw(12) << left << dates[i] << " ";
            for (int s = 0; s < offset; ++s) cout << ' ';
            cout << "* " << fixed << setprecision(1) << weights[i] << "kg\n";
        }
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
    }

    // Safe mean calculation (integer array)
    double averageInt(const int arr[], int n) const {
        if (n <= 0)
            return 0.0;
        long long sum = 0;
        for (int i = 0; i < n; ++i) 
            sum += arr[i];
        return (double)sum / (double)n;
    }

    // Safe mean calculation (double array)
    double averageDouble(const double arr[], int n) const {
        if (n <= 0) 
            return 0.0;
        long double sum = 0;
        for (int i = 0; i < n; ++i) 
            sum += arr[i];
        return (double)(sum / (long double)n);
    }

    // Compute moving average for an integer array (window W), printing inline.
    void printMovingAverageInt(const char* title, const int arr[], int n, int W) const {
        if (n <= 0 || W <= 1) {
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "              " << title << " moving average: insufficient data/window.\n";
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            return;
        }
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        cout << "              " << title << " " << W << "-day moving averages\n";
        for (int i = 0; i <= n - W; ++i) {
            long long s = 0;
            for (int k = i; k < i + W; ++k) s += arr[k];
            double mv = (double)s / (double)W;
            cout << "              " << setw(10) << left << dates[i + W - 1]
                << " -> " << fixed << setprecision(2) << mv << "\n";
        }
        cout << "              ---------------------------------------------------------\n";
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
    }

    // Compute moving average for a double array (window W), printing inline.
    void printMovingAverageDouble(const char* title, const double arr[], int n, int W) const {
        if (n <= 0 || W <= 1) {
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "              " << title << " moving average: insufficient data/window.\n";
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            return;
        }
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        cout << "              " << title << " " << W << "-day moving averages\n";
        for (int i = 0; i <= n - W; ++i) {
            long double s = 0;
            for (int k = i; k < i + W; ++k) s += arr[k];
            double mv = (double)(s / (long double)W);
            cout << "              " << setw(10) << left << dates[i + W - 1];
             cout   << " -> " << fixed << setprecision(2) << mv << "\n";
        }
        cout << "              ---------------------------------------------------------\n";
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
    }

    // Count streak of days meeting a condition on an int array.
    int longestStreakAtLeast(const int arr[], int n, int threshold) const {
        int best = 0, cur = 0;
        for (int i = 0; i < n; ++i) {
            if (arr[i] >= threshold) {
                ++cur;
                if (cur > best) 
                    best = cur;
            }
            else {
                cur = 0;
            }
        }
        return best;
    }

    // Count days under or equal to a certain cap (useful for calorie "deficit" tracking).
    int countDaysAtMost(const int arr[], int n, int cap) const {
        int c = 0;
        for (int i = 0; i < n; ++i) 
            if (arr[i] <= cap) 
                ++c;
        return c;
    }

public:
    progress() {
        memset(dates, 0, sizeof(dates));
        for (int i = 0; i < MAX_ENTRIES; ++i) {
            calories[i] = 0;
            workoutMinutes[i] = 0;
            weights[i] = 0.0;
        }
        count = 0;
        calorieGoal = 2000;
        workoutGoal = 30;
        targetWeight = 70.0;
    }

    void resetAll() {
        memset(dates, 0, sizeof(dates));
        for (int i = 0; i < MAX_ENTRIES; ++i) {
            calories[i] = 0;
            workoutMinutes[i] = 0;
            weights[i] = 0.0;
        }
        count = 0;
    }

    // ----------------------------- GOALS API -----------------------------------------
    void setCalorieGoal(int goal) { 
        if (goal > 0)
            calorieGoal = goal; }
    void setWorkoutGoal(int goal) {
        if (goal > 0)
            workoutGoal = goal; }
    void setTargetWeight(double w) {
        if (w > 0) 
            targetWeight = w; }

    int    getCalorieGoal() const {
        return calorieGoal; }
    int    getWorkoutGoal() const { 
        return workoutGoal; }
    double getTargetWeight() const {
        return targetWeight; }

    // ----------------------------- DATA ENTRY ----------------------------------------
    // Adds or updates a daily entry. If the date already exists, it is updated in place.
    void add_or_update_day(const string& dateYYYYMMDD, int dayCalories, int dayWorkoutMins, double dayWeightKg) {
        if (count >= MAX_ENTRIES) {
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "              Reached max capacity of stored progress entries.\n";
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            return;
        }
        char d[DATE_LEN];
        if (!validateAndNormalizeDate(dateYYYYMMDD, d)) {
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "              Invalid date supplied.\n";
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            return;
        }

        // If entry exists, update it; else append.
        int idx = 0;
        idx=findByDate(dateYYYYMMDD);
        if (idx >= 0) {
            // Update existing
            calories[idx] = (dayCalories >= 0 ? dayCalories : calories[idx]);
            workoutMinutes[idx] = (dayWorkoutMins >= 0 ? dayWorkoutMins : workoutMinutes[idx]);
            if (dayWeightKg > 0.0) weights[idx] = dayWeightKg;
        }
        else {
            // Append a new one
            strncpy(dates[count], d, DATE_LEN);
            calories[count] = (dayCalories >= 0 ? dayCalories : 0);
            workoutMinutes[count] = (dayWorkoutMins >= 0 ? dayWorkoutMins : 0);
            weights[count] = (dayWeightKg > 0.0 ? dayWeightKg : 0.0);
            ++count;
        }

        // Always keep entries sorted by date for consistent visualizations.
        sortByDate();
    }

    // ----------------------------- PERSISTENCE ---------------------------------------
    // Binary append: write ALL current entries to file (optionally truncating first).
    void save_to_file(const string& filename = "progress_data.bin", bool truncate = false) {
        ios::openmode mode = ios::binary | ios::out;
        if (!truncate) mode |= ios::app;
        ofstream out(filename.c_str(), mode);
        if (!out) {
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "              Couldn't open file for writing: " << filename << "\n";
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            return;
        }
        for (int i = 0; i < count; ++i) {
            Record r;
            strncpy(r.date, dates[i], DATE_LEN);
            r.cal = calories[i];
            r.mins = workoutMinutes[i];
            r.w = weights[i];
            out.write(reinterpret_cast<char*>(&r), sizeof(Record));
        }
        out.close();
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        cout << "              Saved " << count << " entries to " << filename << ".\n";
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
    }

    // Binary read: load all records from file, replacing current in-memory arrays.
    void load_from_file(const string& filename = "progress_data.bin") {
        ifstream in(filename.c_str(), ios::binary | ios::in);
        if (!in) {
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "              Couldn't open file for reading: " << filename << "\n";
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            return;
        }
        resetAll();
        Record r;
        while (in.read(reinterpret_cast<char*>(&r), sizeof(Record))) {
            if (count >= MAX_ENTRIES) break;
            strncpy(dates[count], r.date, DATE_LEN);
            calories[count] = r.cal;
            workoutMinutes[count] = r.mins;
            weights[count] = r.w;
            ++count;
        }
        in.close();
        // Keep sorted after loading
        sortByDate();
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        cout << "              Loaded " << count << " entries from " << filename << ".\n";
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
    }

    // Truncate binary file safely.
    void delete_file(const string& filename = "progress_data.bin") {
        ofstream d(filename.c_str(), ios::binary | ios::trunc);
        d.close();
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        cout << "              Cleared file: " << filename << "\n";
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
    }

    // ----------------------------- SUMMARY / STATS -----------------------------------
    double average_daily_calories() const {
        return averageInt(calories, count); }
    double average_daily_workout_mins() const {
        return averageInt(workoutMinutes, count); }
    double average_weight() const { 
        return averageDouble(weights, count); }

    int min_calories() const {
        if (count == 0) 
            return 0;
        int m = 0;
        m = calories[0];
        for (int i = 1; i < count; ++i) 
            if (calories[i] < m) 
                m = calories[i];
        return m;
    }
    int max_calories() const {
        if (count == 0) 
            return 0;
        int m = 0;
        m=calories[0];
        for (int i = 1; i < count; ++i) 
            if (calories[i] > m) 
                m = calories[i];
        return m;
    }
    int min_workout_mins() const {
        if (count == 0) 
            return 0;
        int m = 0;
        m=workoutMinutes[0];
        for (int i = 1; i < count; ++i) 
            if (workoutMinutes[i] < m)
                m = workoutMinutes[i];
        return m;
    }
    int max_workout_mins() const {
        if (count == 0) 
            return 0;
        int m = 0;
        m = workoutMinutes[0];
        for (int i = 1; i < count; ++i) 
            if (workoutMinutes[i] > m) 
                m = workoutMinutes[i];
        return m;
    }

    // ----------------------------- GOAL CHECKS ---------------------------------------
    // How many days met the workout goal?
    int days_meeting_workout_goal() const {
        return longestStreakAtLeast(workoutMinutes, count, workoutGoal); // Using same helper for count purposes
    }
    // Longest streak of hitting workout goal
    int longest_workout_streak() const {
        return longestStreakAtLeast(workoutMinutes, count, workoutGoal);
    }
    // Days at/under calorie goal (i.e., "deficit days").
    int deficit_days() const {
        return countDaysAtMost(calories, count, calorieGoal);
    }

    // ----------------------------- ASCII VISUALS -------------------------------------
    // These four were originally placeholders. Now they show real data using arrays.

    // Trends in workout effectiveness: show bars for last N workout minutes with moving average.
    void trackin_trends_effective_workout(int lastNDays = 14, int movingAvgWindow = 7) {
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        cout << "              ~~~~~~~~~~~~~~~~~ Workout Trends ~~~~~~~~~~~~~~~~~\n";
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        if (count == 0) {
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "              No workout data available.\n";
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
            return;
        }
        int num = 0;
        // Display last N days (or all if fewer)
        int start = 0;
        start=(count > lastNDays) ? count - lastNDays : 0;
        for (int i = start; i < count; ++i) {
            string lab = string(dates[i]) + "m";
            drawBar(lab, workoutMinutes[i], 40);
        }
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        cout << "              --------------------------------------------------\n";
        // Moving average (if enough samples)
        int window = (movingAvgWindow < 2 ? 2 : movingAvgWindow);
        if (count - start >= window) {
            // Print MA for just the visible window for clarity
            printMovingAverageInt("Workout mins", &workoutMinutes[start], count - start, window);
        }
        cout << "              Longest workout streak meeting goal (" << workoutGoal << "m): ";
        cout    << longest_workout_streak() << " day(s)\n";
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
    }

    // Trends in nutrition effectiveness: show bars for last N calories with moving average.
    void tracking_trends_effective_nutrition(int lastNDays = 14, int movingAvgWindow = 7) {
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        cout << "              ~~~~~~~~~~~~~~~~ Nutrition (Calories) Trends ~~~~~~~~~~~~~~~~\n";
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        if (count == 0) {
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "              No calorie data available.\n";
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
            return;
        }
        int start = 0;
        start=(count > lastNDays) ? count - lastNDays : 0;
        for (int i = start; i < count; ++i) {
            string lab = string(dates[i]) + "c";
            drawBar(lab, calories[i], 40);
        }
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        cout << "              --------------------------------------------------------------\n";
        int window = (movingAvgWindow < 2 ? 2 : movingAvgWindow);
        if (count - start >= window) {
            printMovingAverageInt("Calories", &calories[start], count - start, window);
        }
        cout << "              Deficit days (<= " << calorieGoal << " kcal): ";
         cout   << deficit_days() << "\n";
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
    }

    // Compare daily workout graph: prints a compact bar for ALL logged workout minutes.
    void compare_daily_workout_graph() {
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        cout << "              ~~~~~~~~~~~~~~~~~ Compare: Workout Minutes ~~~~~~~~~~~~~~~~~~\n";
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        if (count == 0) {
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "              No workout data available.\n";
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
            return;
        }
        for (int i = 0; i < count; ++i) {
            drawBar(dates[i], workoutMinutes[i], 50);
        }

        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        cout << "              Min: ";
        cout<< min_workout_mins();
        cout << "  Max: ";
        cout<< max_workout_mins();
         cout   << "  Avg: " << fixed << setprecision(2) << average_daily_workout_mins() << " mins\n";
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
    }

    // Compare daily nutrition graph: prints a compact bar for ALL logged calories.
    void compare_nutrition_graph() {
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        cout << "              ~~~~~~~~~~~~~~~~ Compare: Daily Calories ~~~~~~~~~~~~~~~~~~~~\n";
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        if (count == 0) {
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "              No calorie data available.\n";
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl; 
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            return;
        }
        for (int i = 0; i < count; ++i) {
            drawBar(dates[i], calories[i], 50);
        }
        cout << "              Min: " << min_calories();
        cout << "  Max: " << max_calories();
         cout   << "  Avg: " << fixed << setprecision(2) << average_daily_calories() << " kcal\n";
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
    }

    // Calorie consumption “graph”: show last N as a diagonal-ish sparkline.

    void calorie_consumption_graph(int lastNDays = 20) {
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        cout << "              ~~~~~~~~~~~~~~ Calorie Consumption Sparkline ~~~~~~~~~~~~~~~~\n";
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        if (count == 0) {
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "              No calorie data available.\n";
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            return;
        }

        int start = 0;
        start=(count > lastNDays) ? count - lastNDays : 0;

        // Normalize calories in the window to 0..40 to create diagonal steps
        int localMin = calories[start], localMax = calories[start];
        for (int i = start; i < count; ++i) {
            if (calories[i] < localMin) 
                localMin = calories[i];
            if (calories[i] > localMax) 
                localMax = calories[i];
        }
        int span = (localMax - localMin);
        if (span == 0)
            span = 1;

        for (int i = start; i < count; ++i) {
            int spaces = (int)round(((double)(calories[i] - localMin) / (double)span) * 40.0);
            cout << setw(12) << left << dates[i] << " ";
            for (int s = 0; s < spaces; ++s) 
                cout << ' ';
            cout << "* " << calories[i] << " kcal\n";
        }
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
    }

    // ----------------------------- COMPARISONS ---------------------------------------
    // Compare last week vs the week before (calories and workout minutes).
    void compare_last_7_vs_prev_7() {
        if (count < 14) {
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "              Need at least 14 days of data to compare last 7 vs previous 7.\n";
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            return;
        }
        int startPrev = count - 14;
        int startLast = count - 7;

        long long calPrev = 0, calLast = 0;
        long long minPrev = 0, minLast = 0;
        for (int i = 0; i < 7; ++i) {
            calPrev += calories[startPrev + i];
            calLast += calories[startLast + i];
            minPrev += workoutMinutes[startPrev + i];
            minLast += workoutMinutes[startLast + i];
        }

        double avgCalPrev = calPrev / 7.0;
        double avgCalLast = calLast / 7.0;
        double avgMinPrev = minPrev / 7.0;
        double avgMinLast = minLast / 7.0;
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        cout << "              ~~~~~~~~~~ 7-Day Comparison (Last vs Previous) ~~~~~~~~~~~~~\n";
        cout << "              Calories: last=" << fixed << setprecision(2) << avgCalLast
            << " | prev=" << avgCalPrev
            << " | diff=" << (avgCalLast - avgCalPrev) << "\n";
        cout << "              Workout : last=" << fixed << setprecision(2) << avgMinLast
            << " | prev=" << avgMinPrev
            << " | diff=" << (avgMinLast - avgMinPrev) << "\n";
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
    }

    // ----------------------------- WEIGHT VISUAL -------------------------------------
    // Draw a pseudo line chart for weight and show delta to target.
    void show_weight_trend_and_delta() {
        drawWeightLine();
        if (count > 0) {
            double lastW = weights[count - 1];
            double delta = lastW - targetWeight;
            cout << "              Current vs Target: " << fixed << setprecision(1);
            cout << lastW << "kg vs " << targetWeight << "kg  (";
             cout   << (delta >= 0 ? "+" : "") << delta << "kg)\n";
             cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
             cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "              Tip: small steady changes (0.25–0.5kg/week) are sustainable.\n";
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        }
    }

    // ----------------------------- REPORT EXPORT -------------------------------------
    // Export a compact human-readable summary to a text file.
    void export_text_report(const string& filename = "progress_report.txt") {
        ofstream out(filename.c_str());
        if (!out) {
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "              Couldn't open file for writing: " << filename << "\n";
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            return;
        }
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        out << "========================== FitConnect Progress Report ==========================\n";
        out << "Entries recorded: " << count << "\n";
        out << "Goals: calories<=" << calorieGoal << " | workout>=" << workoutGoal
            << " | target weight=" << targetWeight << "kg\n\n";

        out << "Averages\n";
        out << " - Calories: " << fixed << setprecision(2) << average_daily_calories() << " kcal\n";
        out << " - Workout : " << fixed << setprecision(2) << average_daily_workout_mins() << " mins\n";
        out << " - Weight  : " << fixed << setprecision(2) << average_weight() << " kg\n\n";

        out << "Extremes\n";
        out << " - MinCalories: " << min_calories() << " | MaxCalories: " << max_calories() << "\n";
        out << " - MinWorkout : " << min_workout_mins() << " | MaxWorkout : " << max_workout_mins() << "\n\n";

        out << "Streaks & Compliance\n";
        out << " - Longest workout-goal streak (>= " << workoutGoal << "m): "
            << longest_workout_streak() << " day(s)\n";
        out << " - Deficit days (<= " << calorieGoal << " kcal): "
            << deficit_days() << "\n\n";

        out << "Recent Entries (up to 10)\n";
        int start = (count > 10) ? count - 10 : 0;
        for (int i = start; i < count; ++i) {
            out << " - " << dates[i]
                << " | kcal=" << calories[i]
                << " | mins=" << workoutMinutes[i]
                << " | w=" << fixed << setprecision(1) << weights[i] << "kg\n";
        }
        out << "===============================================================================\n";
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        out.close();
        cout << "              Wrote summary report to " << filename << ".\n";
    }

    // ----------------------------- DEBUG/UTILITY VIEW -------------------------------
    void print_all_entries() const {
        if (count == 0) {
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "              No entries to show.\n";
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
            return;
        }
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        cout << "              ~~~~~~~~~~~~~~~~~~~~~ All Progress Entries ~~~~~~~~~~~~~~~~~~~~\n";
        cout << left << setw(12) << "Date" << setw(10) << "Calories" << setw(10) << "Minutes" << setw(10) << "Weight\n";
        cout << "              ---------------------------------------------------------------\n";
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        for (int i = 0; i < count; ++i) {
            cout << "              " << left << setw(12) << dates[i];
            cout << setw(10) << calories[i];
            cout << setw(10) << workoutMinutes[i];
            cout    << setw(10) << fixed << setprecision(1) << weights[i] << "\n";
        }
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
        cout << "              ---------------------------------------------------------------\n";
        cout << "              ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~               " << endl;
    }

    // ----------------------------- SAFE ACCESSORS -----------------------------------
    int size() const { return count; }

    // Getters for arrays (read-only style prints for external checks)
    void get_entry_at(int index, string& dateOut, int& calOut, int& minsOut, double& wOut) const {
        if (index < 0 || index >= count) {
            dateOut = "";
            calOut = minsOut = 0;
            wOut = 0.0;
            return;
        }
        dateOut = string(dates[index]);
        calOut = calories[index];
        minsOut = workoutMinutes[index];
        wOut = weights[index];
    }
};
