// Mechanical Turk
//
// Written by Kel Ho and Wanting Liu
// Last updated 18 May 2016

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <math.h>

#include "Game.h"
#include "mechanicalTurk.h"

// Board information
#define NUM_VERTEXES 54
#define NUM_ARCS 72
#define NUM_HEX_COL1 3
#define NUM_HEX_COL2 4
#define NUM_HEX_COL3 5
#define NUM_HEX_COL4 4
#define NUM_HEX_COL5 3

// Student Disciplines
#define NUM_DISCIPLINES 6


// Need to know if there is adj campus
// If other campuses are on vertex
// If player owns an ARC grant connected to vertex
int possibleToBuildCampus (Game g, int currentPlayer) {
	int result = TRUE;
	return result;
}


// Determine if enough students to build a campus
int enoughStudentsForCampus (Game g, int currentPlayer) {
	int result = FALSE;

	if (getStudents (g, currentPlayer, STUDENT_BPS) >= 1 &&
		getStudents (g, currentPlayer, STUDENT_BQN) >= 1 &&
		getStudents (g, currentPlayer, STUDENT_MJ) >= 1 &&
		getStudents (g, currentPlayer, STUDENT_MTV) >= 1) {
		result = TRUE;
    }
    return result;
}

// Function to convert students
void convertStudents (Game g, int studentFrom, int studentTo, 
	int numToCreate) {
	action a;
	a.actionCode = RETRAIN_STUDENTS;
	a.disciplineFrom = studentFrom;
	a.disciplineTo = studentTo;

	int count = 0;
	while (count < numToCreate) {
		if (isLegalAction (g, a)) {
			makeAction(g, a);
		}
		count ++;
	}
}

// Retrain students to build campus
void retrainStudentsForCampus (Game g, int currentPlayer) {

	int rateBPS = getExchangeRate (g, currentPlayer, STUDENT_BPS, 
		STUDENT_BPS);
	int rateBQN = getExchangeRate (g, currentPlayer, STUDENT_BQN,
		STUDENT_BQN);
	int rateMJ = getExchangeRate (g, currentPlayer, STUDENT_MJ,
		STUDENT_MJ);
	int rateMTV = getExchangeRate (g, currentPlayer, STUDENT_MTV,
		STUDENT_MTV);
	int rateMMONEY = getExchangeRate (g, currentPlayer, STUDENT_MMONEY,
		STUDENT_MMONEY);
	int rateTHD = getExchangeRate (g, currentPlayer, STUDENT_THD,
		STUDENT_THD);

	int numBPS = getStudents (g, currentPlayer, STUDENT_BPS);
	int numBQN = getStudents (g, currentPlayer, STUDENT_BQN);
	int numMJ = getStudents (g, currentPlayer, STUDENT_MJ);
	int numMTV = getStudents (g, currentPlayer, STUDENT_MTV);
	int numMMONEY = getStudents (g, currentPlayer, STUDENT_MMONEY);
	int numTHD = getStudents (g, currentPlayer, STUDENT_THD);

	if (numBPS <= 0) {
		if (numBQN > rateBQN) {
			convertStudents (g, STUDENT_BQN, STUDENT_BPS, 1);
			numBQN = numBQN - rateBQN;
			numBPS++;
		} else if (numMJ > rateMJ) {
			convertStudents (g, STUDENT_MJ, STUDENT_BPS, 1);
			numMJ = numMJ - rateMJ;
			numBPS++;
		} else if (numMTV > rateMTV) {
			convertStudents (g, STUDENT_MTV, STUDENT_BPS, 1);
			numMTV = numMTV - rateMTV;
			numBPS++;
		} else if (numMMONEY >= rateMMONEY) {
			convertStudents (g, STUDENT_MMONEY, STUDENT_BPS, 1);
			numMMONEY = numMMONEY - rateMMONEY;
			numBPS++;
		} else if (numTHD >= rateTHD) {
			convertStudents (g, STUDENT_THD, STUDENT_BPS, 1);
			numTHD = numTHD - rateTHD;
			numBPS++;
		}
	}

	if (numBQN <= 0) {
		if (numBPS > rateBPS) {
			convertStudents (g, STUDENT_BPS, STUDENT_BQN, 1);
			numBPS = numBPS - rateBPS;
			numBQN++;
		} else if (numMJ > rateMJ) {
			convertStudents (g, STUDENT_MJ, STUDENT_BQN, 1);
			numMJ = numMJ - rateMJ;
			numBQN++;
		} else if (numMTV > rateMTV) {
			convertStudents (g, STUDENT_MTV, STUDENT_BQN, 1);
			numMTV = numMTV - rateMTV;
			numBQN++;
		} else if (numMMONEY >= rateMMONEY) {
			convertStudents (g, STUDENT_MMONEY, STUDENT_BQN, 1);
			numMMONEY = numMMONEY - rateMMONEY;
			numBQN++;
		} else if (numTHD >= rateTHD) {
			convertStudents (g, STUDENT_THD, STUDENT_BQN, 1);
			numTHD = numTHD - rateTHD;
			numBQN++;
		}
	}

	if (numMJ <= 0) {
		if (numBPS > rateBPS) {
			convertStudents (g, STUDENT_BPS, STUDENT_MJ, 1);
			numBPS = numBPS - rateBPS;
			numMJ++;
		} else if (numBQN > rateBQN) {
			convertStudents (g, STUDENT_BQN, STUDENT_MJ, 1);
			numBQN = numBQN - rateBQN;
			numMJ++;
		} else if (numMTV > rateMTV) {
			convertStudents (g, STUDENT_MTV, STUDENT_MJ, 1);
			numMTV = numMTV - rateMTV;
			numMJ++;
		} else if (numMMONEY >= rateMMONEY) {
			convertStudents (g, STUDENT_MMONEY, STUDENT_MJ, 1);
			numMMONEY = numMMONEY - rateMMONEY;
			numMJ++;
		} else if (numTHD >= rateTHD) {
			convertStudents (g, STUDENT_THD, STUDENT_MJ, 1);
			numTHD = numTHD - rateTHD;
			numMJ++;
		}
	}

	if (numMTV >= 0) {
		if (numBPS > rateBPS) {
			convertStudents (g, STUDENT_BPS, STUDENT_MTV, 1);
			numBPS = numBPS - rateBPS;
			numMTV++;
		} else if (numBQN > rateBQN) {
			convertStudents (g, STUDENT_BQN, STUDENT_MTV, 1);
			numBQN = numBQN - rateBQN;
			numMTV++;
		} else if (numMJ > rateMJ) {
			convertStudents (g, STUDENT_MJ, STUDENT_MTV, 1);
			numMJ = numMJ - rateMJ;
			numMTV++;
		} else if (numMMONEY >= rateMMONEY) {
			convertStudents (g, STUDENT_MMONEY, STUDENT_MTV, 1);
			numMMONEY = numMMONEY - rateMMONEY;
			numMTV++;
		} else if (numTHD >= rateTHD) {
			convertStudents (g, STUDENT_THD, STUDENT_MTV, 1);
			numTHD = numTHD - rateTHD;
			numMTV++;
		}
	}
}

int possibleToBuildARC (Game g, int currentPlayer) {
	int result = TRUE;
	return result;
}

// Determine if enough students to build an ARC
int enoughStudentsForARC (Game g, int currentPlayer) {
	int result = FALSE;

	if (getStudents (g, currentPlayer, STUDENT_BQN) >= 1 && 
		getStudents (g, currentPlayer, STUDENT_BPS >= 1)) {
		result = TRUE;
	}

	return result;
}

// Retrain students to build ARC
void retrainStudentsForARC (Game g, int currentPlayer) {

	int rateBPS = getExchangeRate (g, currentPlayer, STUDENT_BPS, 
		STUDENT_BPS);
	int rateBQN = getExchangeRate (g, currentPlayer, STUDENT_BQN,
		STUDENT_BQN);
	int rateMJ = getExchangeRate (g, currentPlayer, STUDENT_MJ,
		STUDENT_MJ);
	int rateMTV = getExchangeRate (g, currentPlayer, STUDENT_MTV,
		STUDENT_MTV);
	int rateMMONEY = getExchangeRate (g, currentPlayer, STUDENT_MMONEY,
		STUDENT_MMONEY);
	int rateTHD = getExchangeRate (g, currentPlayer, STUDENT_THD,
		STUDENT_THD);

	int numBPS = getStudents (g, currentPlayer, STUDENT_BPS);
	int numBQN = getStudents (g, currentPlayer, STUDENT_BQN);
	int numMJ = getStudents (g, currentPlayer, STUDENT_MJ);
	int numMTV = getStudents (g, currentPlayer, STUDENT_MTV);
	int numMMONEY = getStudents (g, currentPlayer, STUDENT_MMONEY);
	int numTHD = getStudents (g, currentPlayer, STUDENT_THD);

	if (numBPS <= 0) {
		if (numBQN > rateBQN) {
			convertStudents (g, STUDENT_BQN, STUDENT_BPS, 1);
			numBQN = numBQN - rateBQN;
			numBPS++;
		} else if (numMJ > rateMJ) {
			convertStudents (g, STUDENT_MJ, STUDENT_BPS, 1);
			numMJ = numMJ - rateMJ;
			numBPS++;
		} else if (numMTV > rateMTV) {
			convertStudents (g, STUDENT_MTV, STUDENT_BPS, 1);
			numMTV = numMTV - rateMTV;
			numBPS++;
		} else if (numMMONEY >= rateMMONEY) {
			convertStudents (g, STUDENT_MMONEY, STUDENT_BPS, 1);
			numMMONEY = numMMONEY - rateMMONEY;
			numBPS++;
		} else if (numTHD >= rateTHD) {
			convertStudents (g, STUDENT_THD, STUDENT_BPS, 1);
			numTHD = numTHD - rateTHD;
			numBPS++;
		}
	}

	if (numBQN <= 0) {
		if (numBPS > rateBPS) {
			convertStudents (g, STUDENT_BPS, STUDENT_BQN, 1);
			numBPS = numBPS - rateBPS;
			numBQN++;
		} else if (numMJ > rateMJ) {
			convertStudents (g, STUDENT_MJ, STUDENT_BQN, 1);
			numMJ = numMJ - rateMJ;
			numBQN++;
		} else if (numMTV > rateMTV) {
			convertStudents (g, STUDENT_MTV, STUDENT_BQN, 1);
			numMTV = numMTV - rateMTV;
			numBQN++;
		} else if (numMMONEY >= rateMMONEY) {
			convertStudents (g, STUDENT_MMONEY, STUDENT_BQN, 1);
			numMMONEY = numMMONEY - rateMMONEY;
			numBQN++;
		} else if (numTHD >= rateTHD) {
			convertStudents (g, STUDENT_THD, STUDENT_BQN, 1);
			numTHD = numTHD - rateTHD;
			numBQN++;
		}
	}
}

//////////////////////////action code/////////////////////////////

action decideAction (Game g) {
	action nextAction;

	int currentPlayer = getWhoseTurn(g);
	int myCampus = 0;
	int myG08s = 0;
	int myARCs = 0;

	if (currentPlayer == UNI_A) {
		myCampus = CAMPUS_A;
		myG08s = GO8_A;
		myARCs = ARC_A;
	} else if (currentPlayer == UNI_B) {
		myCampus = CAMPUS_B;
		myG08s = GO8_B;
		myARCs = ARC_B;
	} else if (currentPlayer == UNI_C) {
		myCampus = CAMPUS_C;
		myG08s = GO8_C;
		myARCs = ARC_C;
	}

	if (getCampuses (g, currentPlayer) < 6) {
		if (possibleToBuildCampus (g, currentPlayer)) {
			if (enoughStudentsForCampus (g, currentPlayer)) {
				nextAction.actionCode = BUILD_CAMPUS;
			}
		} else if (possibleToBuildARC (g, currentPlayer)) {
			if (enoughStudentsForARC (g, currentPlayer)) {
				nextAction.actionCode = OBTAIN_ARC;
			}
		}
	} else if (getStudents(g, currentPlayer, STUDENT_MJ) > 0 && 
      getStudents(g, currentPlayer, STUDENT_MTV) > 0 &&
      getStudents(g, currentPlayer, STUDENT_MMONEY) > 0) {
        nextAction.actionCode = START_SPINOFF;
    } else {
    	nextAction.actionCode = PASS;
    }

    return nextAction;
}


/*
	if (getCampuses (g, currentPlayer) < 6) {
		if (possibleToBuildCampus (g, currentPlayer)) {
			if (enoughStudentsForCampus (g, currentPlayer)) {
				nextAction.actionCode = BUILD_CAMPUS;
			} else {
				nextAction = 
				retrainStudentsForCampus (g, currentPlayer);
			}
		} else if (possibleToBuildARC (g, currentPlayer)) {
			if (enoughStudentsForARC (g, currentPlayer)) {
				nextAction.actionCode = OBTAIN_ARC;
			} else {
				nextAction = 
				retrainStudentsForARC (g, currentPlayer);
			}
		}
	} else if (getStudents(g, currentPlayer, STUDENT_MJ) > 0 && 
      getStudents(g, currentPlayer, STUDENT_MTV) > 0 &&
      getStudents(g, currentPlayer, STUDENT_MMONEY) > 0) {
        nextAction.actionCode = START_SPINOFF;
    } else {
    	nextAction.actionCode = PASS;
    }

    return nextAction;
*/

