#include <iostream>
#include <sstream>
#include <climits>
#include <vector>
#include <map>
#include <iomanip>
#include <fstream>

using namespace std;
int numStates, numLetters;
vector<string> states, letters;
map<int, map<int, vector<int>>> statesTable;
vector<int> initials;
vector<int> finals;

vector<int> maxLen;


void loadLetters();

void loadStates();

string getTikzCode();

void loadStateDefinitions();

bool checkStatesValid(vector<string> toCheck);

void loadStateDescription(int i);

void printTable();

map<int, vector<int>> translateStateLineToIndexes(map<string, vector<string>> oldLine);

int findIndexOfState(string str);

int findIndexOfLetter(string basic_string);

void loadFinalsInitials();

bool isFinal(int i);

bool isInitial(int i);

void mainMenu();

void saveToFile();

string getTikzHeader();

string getTikzStates();

string getTikzState(int i);

string getTikzEdges();

string getTikzEdge(int i);

string findAttributesOfEdge(int state, int letter);

bool hasEdgeTo(int target, int state);

void displayInstructions() {
    cout << "Instructions: Input number of states and length of sigma. Then input letter names and sigma names. "
         << endl <<
         "After that you will be asked to input states line by line, while all states will be checked for validity. "
         << endl <<
         "If some letter doesnt have a clear edge (It is not DFA), input - instead of state name." << endl << endl;
}

void loadDefinition() {
    cout << "Number of states: ";
    cin >> numStates;
    if (numStates <= 0) {
        cerr << "Number of states has to be positive!";
        exit(-1);
    }
    cout << "Number of letters: ";
    cin >> numLetters;
    if (numLetters <= 0) {
        cerr << "Number of letters has to be positive!";
        exit(-1);
    }

    loadLetters();
    loadStates();
    loadStateDefinitions();

    loadFinalsInitials();
}

void loadFinalsInitials() {
    int initialCount;
    cout << "How many initial states? ";
    cin >> initialCount;

    int finalCount;
    cout << "How many final states? ";
    cin >> finalCount;

    cout << "Enter initial states names separated by ' ': ";
    string s;
    for (int i = 0; i < initialCount; ++i) {
        cin >> s;
        initials.push_back(findIndexOfState(s));
    }

    std::cin.clear();
    std::cin.ignore(INT_MAX, '\n');

    cout << "Enter final states names separated by ' ': ";
    for (int i = 0; i < finalCount; ++i) {
        cin >> s;
        finals.push_back(findIndexOfState(s));
    }

    std::cin.clear();
    std::cin.ignore(INT_MAX, '\n');
}

void loadStateDefinitions() {
    cout
            << "Input states line by line, separate by space, if there is no connection, use -, if there are multiple of connections "
            << endl <<
            "use , to delimit states:" << endl;

    for (int i = 0; i < numStates; ++i) {
        loadStateDescription(i);
    }
}

void loadStateDescription(int i) {
    //Print state name
    cout << states[i] << " ";
    string s;
    map<string, vector<string>> stateLine;
    for (int j = 0; j < numLetters; ++j) {
        cin >> s;
        std::stringstream data(s);
        std::string token;
        vector<string> tokens;
        while (std::getline(data, token, ',')) {
            tokens.push_back(token);
        }

        if (!checkStatesValid(tokens)) return loadStateDescription(i);

        int len = 0;
        for (int k = 0; k < tokens.size(); ++k) {
            len += tokens[k].length() + 1;
        }

        if (maxLen.size() <= i) {
            maxLen.push_back(len);
        } else {
            maxLen[i] = max(maxLen[i], len);
        }

        stateLine[letters[j]] = tokens;
    }


    statesTable[i] = translateStateLineToIndexes(stateLine);
}

map<int, vector<int>> translateStateLineToIndexes(map<string, vector<string>> oldLine) {
    map<int, vector<int>> result;
    string from;
    vector<string> to;
    for (const auto &p : oldLine) {
        from = p.first;
        to = p.second;

        vector<int> newTo;
        for (int i = 0; i < to.size(); ++i) {
            if (to[i] == "-") continue;
            newTo.push_back(findIndexOfState(to[i]));
        }
        result[findIndexOfLetter(from)] = newTo;
    }
    return result;
}

int findIndexOfLetter(string basic_string) {
    for (int i = 0; i < numLetters; ++i) {
        if (letters[i] == basic_string) return i;
    }
    return -1;
}

int findIndexOfState(string str) {
    for (int i = 0; i < numStates; ++i) {
        if (states[i] == str) return i;
    }

    return -1;
}

bool checkStatesValid(vector<string> toCheck) {
    for (int i = 0; i < toCheck.size(); ++i) {
        bool found = false;
        if (toCheck[i] == "-") continue;
        for (int j = 0; j < states.size(); ++j) {
            if (states[j] == toCheck[i]) {
                found = true;
                break;
            }
        }
        if (!found) {
            cerr << "State " << toCheck[i] << " was not found in states! Enter this line again!" << endl;
            return false;
        }
    }
    return true;
}

void loadStates() {
    cout << "Input state names separated by spaces in order: ";
    string s;
    for (int i = 0; i < numStates; ++i) {
        cin >> s;
        states.push_back(s);
    }

    std::cin.clear();
    std::cin.ignore(INT_MAX, '\n');

    cout << "States loaded are: ";
    cout << states[0];
    for (int i = 1; i < numStates; ++i) {
        cout << "," << states[i];
    }
    cout << endl;
}

void loadLetters() {
    cout << "Input letter names separated by spaces in order: ";
    string s;
    for (int i = 0; i < numLetters; ++i) {
        cin >> s;
        letters.push_back(s);
    }

    std::cin.clear();
    std::cin.ignore(INT_MAX, '\n');

    cout << "Letters loaded are: ";
    cout << letters[0];
    for (int i = 1; i < numLetters; ++i) {
        cout << "," << letters[i];
    }
    cout << endl;
}


int main() {
    std::cout << "Welcome to automata code generator for TIKZ in TEX" << std::endl;

    displayInstructions();
    loadDefinition();

    cout.flush();

    printTable();

    mainMenu();

    return 0;
}

void mainMenu() {
    cout << "1: Save to file" << endl << "2: Print to console" << endl << "3: New automaton" << endl << "4: Exit"
         << endl;
    int res;
    cin >> res;
    switch (res) {
        case 1:
            saveToFile();
            mainMenu();
            break;
        case 2:
            cout << getTikzCode() << endl;
            mainMenu();
            break;
        case 3:
            main();
            return;
        case 4:
            exit(0);
        default:
            cerr << "Unknown option: " << res << endl;
            mainMenu();
    }
}

void saveToFile() {
    cout << "Input filename: ";
    string name;
    cin >> name;

    ofstream myfile;
    myfile.open(name);
    string result = getTikzCode();
    myfile << result;
    //myfile << "Writing this to a file.\n";
    myfile.close();
}


void printTable() {
    cout << endl;
    //Print header
    int maxim = 0;
    for (int j = 0; j < states.size(); ++j) {
        maxim = max(maxim, (const int &) states[j].length());
    }
    maxim += 2;

    for (int k = 0; k < maxim + 1; ++k) {
        cout << " ";
    }

    for (int i = 0; i < numLetters; ++i) {
        cout << setw(maxLen[i]) << letters[i];
    }
    cout << endl;

    //Print body
    for (int i = 0; i < numStates; ++i) {
        //Print state name:
        string name = "";
        if (isFinal(i)) {
            name += "<";
        }
        if (isInitial(i)) {
            name += ">";
        }

        name += states[i];
        cout << setw(maxim) << name << " ";

        //Print it:
        for (int j = 0; j < numLetters; ++j) {
            string s = "";
            vector<int> rels = statesTable[i][j];
            if (rels.size() != 0) s = states[rels[0]];
            for (int k = 1; k < rels.size(); ++k) {
                s += "," + states[rels[k]];
            }
            s += " ";
            cout << setw(maxLen[j]) << s;
        }
        cout << endl;
    }

}

bool isInitial(int i) {
    for (int j = 0; j < initials.size(); ++j) {
        if (initials[j] == i) return true;
    }
    return false;
}

bool isFinal(int i) {
    for (int j = 0; j < finals.size(); ++j) {
        if (finals[j] == i) return true;
    }
    return false;
}

string getTikzCode() {
    string result = "";
    string a = getTikzHeader();
    result += a;
    a = getTikzStates();
    result += a;
    a = getTikzEdges();
    result += a;

    result += "\\end{tikzpicture} \n"
            "\\end{document}";

    return result;
}

string getTikzEdges() {
    string result = "     \\path\n";
    for (int i = 0; i < numStates; ++i) {
        result += getTikzEdge(i);
    }
    result += ";\n";
    return result;
}

string getTikzEdge(int i) {
    string result = "       (" + to_string(i) + ")\n";

    for (int j = 0; j < numLetters; ++j) {
        vector<int> connections = statesTable[i][j];
        for (int k = 0; k < connections.size(); ++k) {
            result += "            ";
            result += "edge " + findAttributesOfEdge(i, connections[k]) + " node {" + letters[j] + "} (" +
                      to_string(connections[k]) + ")\n";
        }
    }
    return result;
}

string getTikzStates() {
    string result = "";
    for (int i = 0; i < numStates; ++i) {
        result += "     " + getTikzState(i) + "\n";
    }
    return result;
}

string getTikzState(int i) {
    string result = "\\node[";
    if (isInitial(i)) result += "initial,";
    result += "state";
    if (isFinal(i)) result += ",accepting";
    result += "]    (";
    result += to_string(i);
    result += ")";
    if (i != 0) {
        result += " [right of=";
        result += to_string(i - 1);
        result += "] ";
    } else {
        result += "               ";
    }

    result += "{$" + states[i] + "$};";

    return result;
}

string getTikzHeader() {
    string result = "\\usepackage{pgfplots}\n"
            "\\usepackage{tikz}\n"
            "\\usepackage{amssymb}\n"
            "\\usetikzlibrary{shapes, angles, calc, quotes,arrows,automata}\n"
            "\\usepackage[makeroom]{cancel}\n"
            "\\usepackage{amsmath}\n"
            "\\usepackage{pgf}\n"
            "\\usepackage{txfonts}";
    result += "\n\n\\begin{document}";
    result += "\n\n%Here is the code for the automaton: \n\n";
    result += "\\begin{tikzpicture}[->,>=stealth',shorten >=1pt,auto,node distance=2.8cm,semithick]\n";

    return result;
}

string findAttributesOfEdge(int state, int target) {
    if (state == target) {
        //It is a loop!
        return "[loop above]";
    }

    if (hasEdgeTo(target, state)) {
        return "[bend left]";
    }
    return "";
}

bool hasEdgeTo(int state, int target) {
    for (int i = 0; i < numLetters; ++i) {
        for (int j = 0; j < statesTable[state][i].size(); ++j) {
            if (statesTable[state][i][j] == target) return true;
        }
    }
    return false;
}