#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define TOTAL_SLOTS 10
#define RATE 20

struct Vehicle {
    char number[20];
    int occupied;
};

struct Vehicle parking[TOTAL_SLOTS];

void vehicleEntry();
void vehicleExit();
void showAvailability();
void searchVehicle();
void showAllVehicles();

int findVehicle(char number[]) {
    int i;

    for(i = 0; i < TOTAL_SLOTS; i++) {
        if(parking[i].occupied &&
           strcmp(parking[i].number, number) == 0) {
            return i;
        }
    }

    return -1;
}

int findFreeSlot() {
    int i;

    for(i = 0; i < TOTAL_SLOTS; i++) {
        if(parking[i].occupied == 0) {
            return i;
        }
    }

    return -1;
}

int readNumber(char message[]) {
    char input[100];
    char *end;
    long value;

    while(1) {
        printf("%s", message);
        fgets(input, sizeof(input), stdin);

        value = strtol(input, &end, 10);

        while(isspace((unsigned char)*end))
            end++;

        if(input[0] != '\0' && *end == '\0' &&
           value >= 0 && value <= 2147483647L) {
            return (int)value;
        }

        printf("Invalid input! Enter a valid number.\n");
    }
}

void vehicleEntry() {
    char number[20];
    int slot, i;

    printf("\n--- VEHICLE ENTRY ---\n");

    printf("Enter vehicle number: ");
    fgets(number, sizeof(number), stdin);

    number[strcspn(number, "\n")] = '\0';

    if(strlen(number) == 0) {
        printf("Invalid vehicle number!\n");
        return;
    }

    for(i = 0; number[i] != '\0'; i++) {
        if(isspace((unsigned char)number[i])) {
            printf("Please enter registration without spaces.\n");
            return;
        }

        number[i] = toupper((unsigned char)number[i]);
    }

    if(findVehicle(number) != -1) {
        printf("Vehicle already parked!\n");
        return;
    }

    slot = findFreeSlot();

    if(slot == -1) {
        printf("Parking is FULL!\n");
        return;
    }

    strcpy(parking[slot].number, number);
    parking[slot].occupied = 1;

    printf("\nVehicle successfully parked!\n");
    printf("Vehicle Number: %s\n", number);
    printf("Assigned Slot: %d\n", slot + 1);
    printf("Available Slots: ");

    for(i = 0; i < TOTAL_SLOTS; i++) {
        if(parking[i].occupied == 0)
            printf("%d ", i + 1);
    }

    printf("\n");
}

void vehicleExit() {
    char number[20];
    int slot, hours;
    long long fee;

    printf("\n--- VEHICLE EXIT ---\n");

    printf("Enter vehicle number: ");
    fgets(number, sizeof(number), stdin);

    number[strcspn(number, "\n")] = '\0';

    for(int i = 0; number[i] != '\0'; i++)
        number[i] = toupper((unsigned char)number[i]);

    slot = findVehicle(number);

    if(slot == -1) {
        printf("Vehicle not found!\n");
        return;
    }

    hours = readNumber("Enter parking duration in hours: ");

    if(hours <= 0) {
        printf("Invalid duration!\n");
        return;
    }

    fee = (long long)hours * RATE;

    printf("\n========== PARKING BILL ==========\n");
    printf("Vehicle Number: %s\n", number);
    printf("Parking Slot: %d\n", slot + 1);
    printf("Duration: %d hours\n", hours);
    printf("Rate: Rs. %d/hour\n", RATE);
    printf("----------------------------------\n");
    printf("TOTAL FEE: Rs. %lld\n", fee);
    printf("==================================\n");

    parking[slot].occupied = 0;
    parking[slot].number[0] = '\0';

    printf("Vehicle exited successfully!\n");
    printf("Slot %d is now available.\n", slot + 1);
}

void showAvailability() {
    int i, occupied = 0;

    printf("\n--- PARKING STATUS ---\n");

    for(i = 0; i < TOTAL_SLOTS; i++) {
        if(parking[i].occupied) {
            printf("Slot %d: OCCUPIED (%s)\n",
                   i + 1, parking[i].number);
            occupied++;
        }
        else {
            printf("Slot %d: AVAILABLE\n", i + 1);
        }
    }

    printf("\nTotal Slots: %d\n", TOTAL_SLOTS);
    printf("Occupied: %d\n", occupied);
    printf("Available: %d\n", TOTAL_SLOTS - occupied);
}

void searchVehicle() {
    char number[20];
    int slot;

    printf("\nEnter vehicle number: ");
    fgets(number, sizeof(number), stdin);

    number[strcspn(number, "\n")] = '\0';

    for(int i = 0; number[i] != '\0'; i++)
        number[i] = toupper((unsigned char)number[i]);

    slot = findVehicle(number);

    if(slot == -1) {
        printf("Vehicle not found!\n");
    }
    else {
        printf("\nVehicle Found!\n");
        printf("Registration: %s\n", number);
        printf("Parking Slot: %d\n", slot + 1);
    }
}

void showAllVehicles() {
    int i, found = 0;

    printf("\n--- PARKED VEHICLES ---\n");

    for(i = 0; i < TOTAL_SLOTS; i++) {
        if(parking[i].occupied) {
            printf("Slot %d: %s\n",
                   i + 1, parking[i].number);
            found = 1;
        }
    }

    if(!found)
        printf("No vehicles currently parked.\n");
}

int main() {
    int choice;

    for(int i = 0; i < TOTAL_SLOTS; i++) {
        parking[i].occupied = 0;
    }

    printf("\n");
    printf("====================================\n");
    printf("     SMART CAMPUS PARKING SYSTEM    \n");
    printf("====================================\n");

    while(1) {

        printf("\n");
        printf("1. Vehicle Entry\n");
        printf("2. Vehicle Exit & Generate Bill\n");
        printf("3. Check Parking Availability\n");
        printf("4. Search Vehicle\n");
        printf("5. View All Vehicles\n");
        printf("0. Exit Program\n");

        printf("------------------------------------\n");

        choice = readNumber("Enter your choice: ");

        switch(choice) {

            case 1:
                vehicleEntry();
                break;

            case 2:
                vehicleExit();
                break;

            case 3:
                showAvailability();
                break;

            case 4:
                searchVehicle();
                break;

            case 5:
                showAllVehicles();
                break;

            case 0:
                printf("\nThank you for using our system!\n");
                return 0;

            default:
                printf("Invalid choice! Try again.\n");
        }
    }

    return 0;
}
