#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to store cab booking information
struct Booking {
    int bookingID;
    char customerName[50];
    char pickupLocation[100];
    char dropLocation[100];
    int cabType;  // Changed to int for cab type
    float fare;  // Added fare field
    struct Booking* next;
};

// Function to create a new booking node
struct Booking* createBooking(int id, char name[], char pickup[], char drop[], float fare, int cabType) {
    struct Booking* newBooking = (struct Booking*)malloc(sizeof(struct Booking));
    newBooking->bookingID = id;
    strcpy(newBooking->customerName, name);
    strcpy(newBooking->pickupLocation, pickup);
    strcpy(newBooking->dropLocation, drop);
    newBooking->cabType = cabType;  // Store cab type as int
    newBooking->fare = fare;  // Store fare
    newBooking->next = NULL;
    return newBooking;
}

// Function to calculate fare based on distance (in km) and cab type (using integers)
float calculateFare(float distance, int cabType) {
    float ratePerKm;

    switch (cabType) {
        case 1:  // Standard
            ratePerKm = 10;
            break;
        case 2:  // Sedan
            ratePerKm = 15;
            break;
        case 3:  // SUV
            ratePerKm = 20;
            break;
        case 4:  // Luxury
            ratePerKm = 30;
            break;
        default:
            printf("\t\tInvalid cab type! Defaulting to Standard.\n");
            ratePerKm = 10;  // Default to Standard
    }

    return distance * ratePerKm;
}

// Function to add a booking at the end of the queue (linked list)
void addBooking(struct Booking** head, int id, char name[], char pickup[], char drop[], float fare, int cabType) {
    struct Booking* newBooking = createBooking(id, name, pickup, drop, fare, cabType);
    if (*head == NULL) {
        *head = newBooking;
    } else {
        struct Booking* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newBooking;
    }
    printf("\t\tBooking ID %d added successfully with fare %.2f!\n", id, fare);
}

// Function to process the first booking i.e delete of node from beginning
void processBooking(struct Booking** head) {
    if (*head == NULL) {
        printf("\t\tNo bookings to process!\n");
        return;
    }
    struct Booking* temp = *head;
    printf("\t\tProcessing booking ID %d: %s\n\t\tFare: %.2f\n", temp->bookingID, temp->customerName, temp->fare);
    *head = (*head)->next;
    free(temp);
}

// Function to display all bookings
void viewBookings(struct Booking* head) {
    if (head == NULL) {
        printf("\t\tNo bookings available!\n");
        return;
    }
    struct Booking* temp = head;
    while (temp != NULL) {
        printf("\n\t\t****Booking Details****\n");
        printf("\t\tBooking ID: %d\n\t\tCustomer: %s\n\t\tPickup: %s\n\t\tDrop: %s\n\t\tCab Type: %d\n\t\tFare: %.2f\n\n",
               temp->bookingID, temp->customerName, temp->pickupLocation, temp->dropLocation, temp->cabType, temp->fare);
        temp = temp->next;
    }
}

// Function to cancel a booking based on booking ID
void cancelBooking(struct Booking** head, int id) {
    struct Booking* temp = *head, *prev = NULL;

    if (temp != NULL && temp->bookingID == id) {
        *head = temp->next;
        free(temp);
        printf("\t\tBooking ID %d canceled successfully!\n", id);
        return;
    }

    while (temp != NULL && temp->bookingID != id) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("\t\tBooking ID %d not found!\n", id);
        return;
    }

    prev->next = temp->next;
    free(temp);
    printf("\t\tBooking ID %d canceled successfully!\n", id);
}

// Function to display cab types with prices and drivers in a table format
void displayCabTypes() {
    printf("\t\tAvailable Cab Types with Rates and Driver Names:\n");
    printf("\t\t+----------------+----------------+----------------+\n");
    printf("\t\t|    Cab Type    | Rate (Rupees/km)|   Driver Name  |\n");
    printf("\t\t+----------------+----------------+----------------+\n");
    printf("\t\t|    1. Standard |        10       |     Ramesh     |\n");
    printf("\t\t|    2. Sedan    |        15       |     Suresh     |\n");
    printf("\t\t|    3. SUV      |        20       |     Mahesh     |\n");
    printf("\t\t|    4. Luxury   |        30       |     Rajesh     |\n");
    printf("\t\t+----------------+----------------+----------------+\n");
}

// Main function
int main() {
    struct Booking* head = NULL;
    int choice, id, cabType;
    char name[50], pickup[100], drop[100];
    float distance, fare;
    printf("\n\t* * * * * * * * * * * * * * * * * * * * * * * *\n");
    printf("\t*                                             *\n");
    printf("\t*           WELCOME TO CAB BOOKING            *\n");
    printf("\t*                 CENTRE                      *\n");
    printf("\t*                                             *\n");
    printf("\t* * * * * * * * * * * * * * * * * * * * * * * *\n");
    while (1) {
        printf("\t\t         VS CAB RENTAL            \n");
        printf("\t\t+--------+-----------------------+\n");
        printf("\t\t|    CHOOSE YOUR CHOICE          |\n");
        printf("\t\t+--------+-----------------------+\n");
        printf("\t\t|   1    |    Add Booking        |\n");
        printf("\t\t|   2    |    View Bookings      |\n");
        printf("\t\t|   3    |    Process Booking    |\n");
        printf("\t\t|   4    |    Cancel Booking     |\n");
        printf("\t\t|   5    |    View Cab Types     |\n");
        printf("\t\t|   6    |    Exit               |\n");
        printf("\t\t+--------+-----------------------+\n");
        printf("\t\tEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("\t\tEnter Booking ID: ");
                scanf("%d", &id);
                getchar();  // To consume newline
                printf("\t\tEnter Customer Name: ");
                scanf(" %[^\n]", name);  // Reads the full line including spaces

                printf("\t\tEnter Pickup Location: ");
                scanf(" %[^\n]", pickup);

                printf("\t\tEnter Drop Location: ");
                scanf(" %[^\n]", drop);

                displayCabTypes();  // Display cab options
                printf("\t\tChoose Cab Type (1-4): ");
                scanf("%d", &cabType);

                printf("\t\tEnter distance between Pickup and Drop (in km): ");
                scanf("%f", &distance);

                // Calculate the fare based on distance and cab type
                fare = calculateFare(distance, cabType);
                printf("\t\tThe fare for this ride is: %.2f\n", fare);

                // Add booking
                addBooking(&head, id, name, pickup, drop, fare, cabType);
                break;

            case 2:
                viewBookings(head);
                break;

            case 3:
                processBooking(&head);
                break;

            case 4:
                printf("\t\tEnter Booking ID to cancel: ");
                scanf("%d", &id);
                cancelBooking(&head, id);
                break;

            case 5:
                displayCabTypes();
                break;

            case 6:
                printf("\t\tExiting...\n");
                exit(0);

            default:
                printf("\t\tInvalid choice! Please try again.\n");
        }
    }

    return 0;
}
