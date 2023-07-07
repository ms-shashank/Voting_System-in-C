#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a structure for the candidate node
struct candidate {
    char name[50];
    char party[50];
    int votes;
    struct candidate *next;
};

// Define a structure for the voter ID node
struct voter_id {
    int id;
    struct voter_id *next;
};

// Declare the functions for the program
void add_candidate(struct candidate **head);
void cast_vote(struct candidate **head, struct voter_id **voter_head, int voter_id);
void display_results(struct candidate *head);
void display_menu();

int main() {
    int choice, voter_id;
    struct candidate *head = NULL;
    struct voter_id *voter_head = NULL;

    // Display the menu and get the user's choice
    do {
        display_menu();
        scanf("%d", &choice);
        char password[20];
        switch(choice) {
            case 1:
                // Add a new candidate to the list
                add_candidate(&head);
                break;

            case 2:
                // Cast a vote for a candidate
                do{
                printf("Enter your USN :1SI21CS ");
                scanf("%d", &voter_id);
                //Casting a vote for specific range from  1 to 30 more than will be prompted again
                if (voter_id < 1 || voter_id > 30) {
                    printf("Error: Enter a valid USN ID.\n");
                }else{
                    cast_vote(&head, &voter_head, voter_id);
                }
                }while(voter_id < 1 || voter_id > 30);
                break;

            case 3:
                // Display the current results of the election
                printf("Enter you password :\n");  // Setting a passcode, so that only the owner can access 
                scanf("%s", password);
                if(strcmp(password, "Password") == 0){  // Comparing the entered String with the entered password,  for the current program  its "Password" 
                    display_results(head);
                }else{
                    printf("You do not have persmission to access this option\n");  //returning "only admins can access"
                }
                break;
                

            case 4:
                // Quit the program
                printf("Exiting...\n");
                break;

            default:
                // Handle invalid input
                printf("Invalid choice. Please try again.\n");
                break;
        }
    } while(choice != 4);

    // Free the memory used by the candidate and voter ID lists
    struct candidate *curr_candidate = head;
    while (curr_candidate != NULL) {
        struct candidate *temp_candidate = curr_candidate;
        curr_candidate = curr_candidate->next;
        free(temp_candidate);
    }
    struct voter_id *curr_voter = voter_head;
    while (curr_voter != NULL) {
        struct voter_id *temp_voter = curr_voter;
        curr_voter = curr_voter->next;
        free(temp_voter);
    }

    return 0;
}

void add_candidate(struct candidate **head) {
    // Allocate memory for a new candidate node
    struct candidate *new_candidate = (struct candidate*)malloc(sizeof(struct candidate));
    if (new_candidate == NULL) {
        printf("Error: Memory allocation failed.\n");
        return;
    }

    // Get the candidate information from the user
    printf("Enter the candidate's name: ");
    scanf("%s", new_candidate->name);
    printf("Enter the candidate's party affiliation: ");
    scanf("%s", new_candidate->party);
    new_candidate->votes = 0;

    // Insert the new candidate at the beginning of the list
    new_candidate->next = *head;
    *head = new_candidate;

    printf("Candidate %s (%s) added successfully.\n", new_candidate->name, new_candidate->party);
}

void cast_vote(struct candidate **head, struct voter_id **voter_head, int voter_id) {
    // Check if the voter has already cast their vote
    struct voter_id *curr_voter = *voter_head;
    while (curr_voter != NULL) {
        if (curr_voter->id == voter_id) {
            printf("Error: You have already cast your vote.\n");
            return;
        }
        curr_voter = curr_voter->next;
    }

    // Get the candidate choice from the user
   
    // Display the candidates and get the user's choice
    printf("Candidates:\n");
    struct candidate *curr_candidate = *head;
    int candidate_count = 0;
    while (curr_candidate != NULL) {
        candidate_count++;
        printf("%d. %s (%s)\n", candidate_count, curr_candidate->name, curr_candidate->party);
        curr_candidate = curr_candidate->next;
    }
    int choice;
    printf("Enter the number of the candidate you want to vote for: ");
    scanf("%d", &choice);

    // Find the chosen candidate in the list
    curr_candidate = *head;
    for (int i = 1; i < choice; i++) {
        if (curr_candidate == NULL) {
            printf("Error: Invalid choice.\n");
            return;
        }
        curr_candidate = curr_candidate->next;
    }

    // Increment the candidate's vote count and add the voter ID to the list
    curr_candidate->votes++;
    struct voter_id *new_voter = (struct voter_id*)malloc(sizeof(struct voter_id));
    if (new_voter == NULL) {
        printf("Error: Memory allocation failed.\n");
        return;
    }
    new_voter->id = voter_id;
    new_voter->next = *voter_head;
    *voter_head = new_voter;

    printf("Thank you for voting.\n");
}

void display_results(struct candidate *head) {
    // Display the results of the election
    printf("Results:\n");
    struct candidate *curr_candidate = head;
    while (curr_candidate != NULL) {
        printf("%s (%s): %d vote(s)\n", curr_candidate->name, curr_candidate->party, curr_candidate->votes);
        curr_candidate = curr_candidate->next;
    }
}

void display_menu() {
    // Display the program menu
    printf("Online Voting System\n");
    printf("--------------------\n");
    printf("1. Add a candidate\n");
    printf("2. Cast a vote\n");
    printf("3. Display results\n");
    printf("4. Quit\n");
    printf("Enter your choice: ");
}
