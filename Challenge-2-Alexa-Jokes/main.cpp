
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <random>
using namespace std;

int main() {
    vector<string> jokes;
    ifstream file("randomJokes.txt");
    string line;

    // Read jokes from the text file
    if (!file.is_open()) {
        cout << "Error: Could not open randomJokes.txt\n";
        return 1;
    }

    while (getline(file, line)) {
        if (line.find('?') != string::npos) {
            jokes.push_back(line);
        }
    }
    file.close();

    if (jokes.empty()) {
        cout << "No valid jokes found.\n";
        return 1;
    }

    // Set up random joke selection
    random_device rd;
    mt19937 generator(rd());
    uniform_int_distribution<int> randomIndex(0, jokes.size() - 1);

    cout << "===== ALEXA JOKE GENERATOR =====\n";
    cout << "Type 'Alexa, tell me a joke' or 'quit' to exit.\n";

    string input;

    while (true) {
        cout << "\nYou: ";
        getline(cin, input);

        if (input == "quit") {
            cout << "Alexa: Goodbye!\n";
            break;
        }

        if (input == "Alexa, tell me a joke") {
            string joke = jokes[randomIndex(generator)];
            size_t separator = joke.find('?');

            string setup = joke.substr(0, separator + 1);
            string punchline = joke.substr(separator + 1);

            cout << "\nAlexa: " << setup << "\n";
            cout << "Press Enter to hear the punchline...";
            getline(cin, input);

            cout << "Alexa:" << punchline << "\n";
        } else {
            cout << "Please say 'Alexa, tell me a joke'.\n";
        }
    }

    return 0;
}
