//
// Created by lactosis on 8.11.17.
//

#ifndef TEXAUTOMATA_DFAAUTOMATON_H
#define TEXAUTOMATA_DFAAUTOMATON_H


#include "Automaton.h"

class DFAAutomaton : Automaton {
private:
    vector<vector<int>> statesTable;
    int initial;
    vector<int> finals;

    //region Constructors
    void interactiveGetStatesSigma();

    void interactiveGetStatesTable();
    //endregion



public:
    //region Getters
    /**
     * @return NULL if error, name of the target state else
     */
    const string &fromBy(string state, string letter);
    //endregion

    //region Constructors
    /**
     * Used for interactive mode construction
     */
    DFAAutomaton();


    /**
    * Used primarily to define DFA automatons
    */
    DFAAutomaton(
            vector<string> states,
            vector<string> letters,
            map<string, map<string, string>>
            stateTransitions,
            string startingState,
            vector<string>
            finishingStates
    );

    /**
     * Shorter way to define DFA automatons
     */
    DFAAutomaton(
            map<string, map<string, string>>
            stateTransitions,
            string startingState,
            vector<string>
            finishingStates
    );
    //endregion


    bool isReduced();

    void reduce();


    void interactiveLoadStateRow(int i);


    void interactiveGetStartingFinal();


};


#endif //TEXAUTOMATA_DFAAUTOMATON_H
