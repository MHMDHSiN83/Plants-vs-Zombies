#include <iostream>

const int ROWS = 3;
const int COLS = 3;

void modifyArray(int (&arr)[ROWS][COLS]);

// Function to modify a 2D array using a reference
void modifyArray(int (&arr)[ROWS][COLS]) {
    // Modify the array
    for(int i = 0; i < ROWS; ++i) {
        for(int j = 0; j < COLS; ++j) {
            arr[i][j] = i * COLS + j;
        }
    }
}

// Function to display a 2D array
void displayArray(const int (&arr)[ROWS][COLS]) {
    // Display the array
    for(int i = 0; i < ROWS; ++i) {
        for(int j = 0; j < COLS; ++j) {
            std::cout << arr[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

int main() {
    int myArray[ROWS][COLS];

    // Call the function to modify the array
    modifyArray(myArray);

    // Call the function to display the modified array
    displayArray(myArray);

    return 0;
}
