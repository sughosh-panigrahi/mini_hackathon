#include <stdio.h>
#include <string.h>
#define MAX 10

struct Vehicle {
    char number[20];
    int duration;
    int occupied;
};

struct Vehicle parking[MAX];

void showStatus() {
    int occupied = 0;

    for (int i = 0; i < MAX; i++) {
        if (parking[i].occupied == 1)
            occupied++;
    }

    printf("\nTotal Spaces     : %d", MAX);
    printf("\nOccupied Spaces  : %d", occupied);
    printf("\nAvailable Spaces : %d\n", MAX - occupied);
}

void vehicleEntry() {
    char number[20];
    int freeSlot = -1;

    printf("\nEnter vehicle registration number: ");
    scanf("%s", number);

    // Check duplicate entry
    for (int i = 0; i < MAX; i++) {
        if (parking[i].occupied == 1 &&
            strcmp(parking[i].number, number) == 0) {
            printf("Vehicle is already parked!\n");
            return;
        }
    }

    // Find empty parking space
    for (int i = 0; i < MAX; i++) {
        if (parking[i].occupied == 0) {
            freeSlot = i;
            break;
        }
    }

    if (freeSlot == -1) {
        printf("Parking area is FULL!\n");
        return;
    }

    strcpy(parking[freeSlot].number, number);
    parking[freeSlot].occupied = 1;

    printf("Vehicle parked successfully.\n");
    printf("Parking Slot: %d\n", freeSlot + 1);
}

void vehicleExit() {
    char number[20];
    int duration;
    float fee;
    int found = 0;

    printf("\nEnter vehicle registration number: ");
    scanf("%s", number);

    for (int i = 0; i < MAX; i++) {
        if (parking[i].occupied == 1 &&
            strcmp(parking[i].number, number) == 0) {

            printf("Enter parking duration (hours): ");
            scanf("%d", &duration);

            if (duration <= 0) {
                printf("Invalid duration!\n");
                return;
            }

            // Parking charge = Rs. 20 per hour
            fee = duration * 20;

            printf("\nVehicle Number : %s", number);
            printf("\nDuration       : %d hours", duration);
            printf("\nParking Fee    : Rs. %.2f\n", fee);

            parking[i].occupied = 0;
            found = 1;

            printf("Vehicle exited successfully.\n");
            break;
        }
    }

    if (found == 0)
        printf("Vehicle not found!\n");
}

void searchVehicle() {
    char number[20];

    printf("\nEnter vehicle number: ");
    scanf("%s", number);

    for (int i = 0; i < MAX; i++) {
        if (parking[i].occupied == 1 &&
            strcmp(parking[i].number, number) == 0) {
            printf("Vehicle is parked in Slot %d.\n", i + 1);
            return;
        }
    }

    printf("Vehicle is not in the parking area.\n");
}

int main() {
    int choice;

    while (1) {
        printf("\n==============================");
        printf("\n SMART CAMPUS PARKING SYSTEM");
        printf("\n==============================");
        printf("\n1. Vehicle Entry");
        printf("\n2. Vehicle Exit");
        printf("\n3. Check Parking Availability");
        printf("\n4. Search Vehicle");
        printf("\n5. Exit Program");
        printf("\n==============================");
        printf("\nEnter your choice: ");

        scanf("%d", &choice);

        switch (choice) {
            case 1:
                vehicleEntry();
                break;

            case 2:
                vehicleExit();
                break;

            case 3:
                showStatus();
                break;

            case 4:
                searchVehicle();
                break;

            case 5:
                printf("\nThank you for using the Parking System.\n");
                return 0;

            default:
                printf("\nInvalid choice! Try again.\n");
        }
    }

    return 0;
}

