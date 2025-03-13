#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Room {
    int roomNumber;
    int isAvailable;
    char guestName[50];
    struct Room* next;
};

struct Hotel {
    struct Room* rooms;
};

struct Room* createRoom(int roomNumber) {
    struct Room* newRoom = (struct Room*)malloc(sizeof(struct Room));
    newRoom->roomNumber = roomNumber;
    newRoom->isAvailable = 1;
    strcpy(newRoom->guestName, "None");
    newRoom->next = NULL;
    return newRoom;
}

void initializeRooms(struct Hotel* hotel, int maxRooms) {
    hotel->rooms = NULL;
    for (int i = 1; i <= maxRooms; i++) {
        struct Room* newRoom = createRoom(i);
        newRoom->next = hotel->rooms;
        hotel->rooms = newRoom;
    }
}

struct Room* findRoom(struct Hotel* hotel, int roomNumber) {
    struct Room* current = hotel->rooms;
    while (current != NULL) {
        if (current->roomNumber == roomNumber) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void checkIn(struct Hotel* hotel) {
    int roomNumber;
    char guestName[50];

    printf("Enter room number to check-in: ");
    scanf("%d", &roomNumber);

    struct Room* room = findRoom(hotel, roomNumber);
    if (room == NULL) {
        printf("Invalid room number!\n");
        return;
    }

    if (!room->isAvailable) {
        printf("Sorry, room %d is already occupied.\n", roomNumber);
        return;
    }

    printf("Enter guest name: ");
    getchar();
    fgets(guestName, sizeof(guestName), stdin);
    guestName[strcspn(guestName, "\n")] = 0;

    room->isAvailable = 0;
    strcpy(room->guestName, guestName);
    printf("Checked in successfully! Room %d is now occupied by %s.\n", roomNumber, guestName);
}

void checkOut(struct Hotel* hotel) {
    int roomNumber;

    printf("Enter room number to check-out: ");
    scanf("%d", &roomNumber);

    struct Room* room = findRoom(hotel, roomNumber);
    if (room == NULL) {
        printf("Invalid room number!\n");
        return;
    }

    if (room->isAvailable) {
        printf("Room %d is already vacant.\n", roomNumber);
        return;
    }

    room->isAvailable = 1;
    strcpy(room->guestName, "None");
    printf("Checked out successfully! Room %d is now vacant.\n", roomNumber);
}

void displayRooms(struct Hotel* hotel) {
    printf("\nRoom Status:\n");
    printf("Room No. | Status   | Guest Name\n");
    printf("--------------------------------\n");

    struct Room* current = hotel->rooms;
    while (current != NULL) {
        printf("%8d | %-8s | %s\n", current->roomNumber, 
               current->isAvailable ? "Available" : "Occupied", 
               current->guestName);
        current = current->next;
    }
}

int main() {
    struct Hotel hotel;
    int choice;
    int maxRooms = 10;

    initializeRooms(&hotel, maxRooms);

    do {
        printf("\nHotel Management System\n");
        printf("1. Check-in\n");
        printf("2. Check-out\n");
        printf("3. Display room status\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                checkIn(&hotel);
                break;
            case 2:
                checkOut(&hotel);
                break;
            case 3:
                displayRooms(&hotel);
                break;
            case 4:
                printf("Exiting system...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 4);

    return 0;
}
