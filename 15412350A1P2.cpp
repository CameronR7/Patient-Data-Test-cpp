

#include <iostream>
#include <fstream>
#include <queue>
#include <ctime>
#include <cstdlib>

using namespace std;

// Defining a structure to represent each patient
struct Patient {
    char speciality; // 'W' for wound, 'A' for adult, 'C' for children
    int processingTime; // Time the patient spends with the nurse
};

// Function to process patients
void processPatients(queue<Patient>& woundQueue, queue<Patient>& adultQueue, queue<Patient>& childrenQueue, int currentTime) {
    srand(time(0)); // Seed for random number generator

    // Check if there are patients in any of the queues
    if (!woundQueue.empty()) {
        cout << "1 (" << woundQueue.front().processingTime << ")";
        woundQueue.front().processingTime--; // Decrease processing time
        if (woundQueue.front().processingTime == 0) {
            woundQueue.pop(); // Remove patient if processing time is finished
        }
    }
    else {
        cout << "1";
    }

    cout << "\t";

    if (!adultQueue.empty()) {
        cout << "1 (" << adultQueue.front().processingTime << ")";
        adultQueue.front().processingTime--;
        if (adultQueue.front().processingTime == 0) {
            adultQueue.pop();
        }
    }
    else {
        cout << "1";
    }

    cout << "\t";

    if (!childrenQueue.empty()) {
        cout << "1 (" << childrenQueue.front().processingTime << ")";
        childrenQueue.front().processingTime--;
        if (childrenQueue.front().processingTime == 0) {
            childrenQueue.pop();
        }
    }
    else {
        cout << "1";
    }

    cout << "\t" << currentTime << endl;
}

int main() {
    queue<Patient> woundQueue, adultQueue, childrenQueue;
    ifstream inputFile("C:\\Data\\dataclient.txt"); // Adjusted file path

    if (!inputFile.is_open()) {
        cout << "Error: Unable to open the file." << endl;
        return 1; // Exit the program with an error code
    }

    int timeCount, currentTime = 0;
    char nurse;
    int processingTime;

    cout << "Wound\tAdult\tChildren\tTime count" << endl;

    while (inputFile >> timeCount >> nurse >> processingTime) {
        while (currentTime < timeCount) {
            processPatients(woundQueue, adultQueue, childrenQueue, currentTime);
            currentTime++;
        }

        // Add patient to respective queue based on nurse speciality
        Patient newPatient = { nurse, processingTime };
        switch (nurse) {
        case 'W':
            woundQueue.push(newPatient);
            break;
        case 'A':
            adultQueue.push(newPatient);
            break;
        case 'C':
            childrenQueue.push(newPatient);
            break;
        default:
            break;
        }
    }

    // Process remaining patients after simulation ends
    while (!woundQueue.empty() || !adultQueue.empty() || !childrenQueue.empty()) {
        processPatients(woundQueue, adultQueue, childrenQueue, currentTime);
        currentTime++;
    }

    inputFile.close();
    return 0;
}
