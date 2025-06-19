#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;

// Candidate record
struct Candidate {
    float gpa;
    int dsa_score;
    int projects;
    int internships;
    bool selected; // 1 if selected, 0 otherwise
};

// Training dataset (synthetic)
vector<Candidate> trainingData = {
    {8.5, 80, 3, 1, true},
    {7.0, 65, 2, 0, false},
    {9.0, 85, 4, 2, true},
    {6.5, 50, 1, 0, false},
    {8.0, 75, 3, 1, true},
    {7.5, 70, 2, 1, true},
    {6.0, 55, 1, 0, false},
    {9.5, 90, 5, 2, true},
    {8.2, 78, 3, 1, true},
    {7.1, 60, 2, 0, false}
};

// Threshold-based matching logic
bool matches(Candidate c, Candidate input) {
    return (
        (abs(c.gpa - input.gpa) <= 1.0) &&
        (abs(c.dsa_score - input.dsa_score) <= 10) &&
        (abs(c.projects - input.projects) <= 1) &&
        (abs(c.internships - input.internships) <= 1)
    );
}

float predictSelectionProbability(Candidate input) {
    int matchCount = 0;
    int selectedCount = 0;

    for (Candidate c : trainingData) {
        if (matches(c, input)) {
            matchCount++;
            if (c.selected) selectedCount++;
        }
    }

    if (matchCount == 0) return 0.5f; // Neutral guess if no match found

    return static_cast<float>(selectedCount) / matchCount;
}

int main() {
    Candidate input;

    cout << "Enter Candidate Details:\n";
    cout << "GPA (out of 10): ";
    cin >> input.gpa;
    cout << "DSA Score (out of 100): ";
    cin >> input.dsa_score;
    cout << "Number of Projects: ";
    cin >> input.projects;
    cout << "Number of Internships: ";
    cin >> input.internships;

    float probability = predictSelectionProbability(input);

    cout << "\n🔍 Predicted Probability of Selection: " << probability * 100 << "%\n";

    if (probability > 0.7)
        cout << "✅ High chance of selection!\n";
    else if (probability > 0.4)
        cout << "🟡 Moderate chance of selection.\n";
    else
        cout << "❌ Low chance of selection. Consider improving profile.\n";

    return 0;
}
