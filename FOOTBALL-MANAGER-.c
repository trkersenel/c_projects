#include <stdio.h>
#include <string.h>

#define MAX_PLAYERS 50
#define MAX_STR 100

/* Struct representing a player */
struct Player {
    char name[MAX_STR];
    char pos[MAX_STR];
    int number;
    int age;
};

/* Struct representing a team */
struct Team {
    struct Player players[MAX_PLAYERS];
    int countPlayers;
};

/*
 * Function: add_player
 * --------------------
 * Adds a new player to the given team.
 *
 * team: pointer to the Team struct
 *
 * returns: void
 */
void add_player(struct Team *team){
    if(team->countPlayers >= MAX_PLAYERS){
        printf("Team full!\n");
        return;
    }

    getchar(); /* clear input buffer */

    printf("Name: ");
    fgets(team->players[team->countPlayers].name, MAX_STR, stdin);
    team->players[team->countPlayers].name[
        strcspn(team->players[team->countPlayers].name,"\n")] = 0;

    printf("Position: ");
    fgets(team->players[team->countPlayers].pos, MAX_STR, stdin);
    team->players[team->countPlayers].pos[
        strcspn(team->players[team->countPlayers].pos,"\n")] = 0;

    printf("Number: ");
    scanf("%d", &team->players[team->countPlayers].number);

    printf("Age: ");
    scanf("%d", &team->players[team->countPlayers].age);

    team->countPlayers++;
    printf("Player added!\n");
}

/*
 * Function: display_players
 * -------------------------
 * Prints all players in the team.
 *
 * team: Team struct (passed by value)
 *
 * returns: void
 */
void display_players(struct Team team){
    if(team.countPlayers == 0){
        printf("No players.\n");
        return;
    }

    for(int i=0; i<team.countPlayers; i++){
        printf("%d) %s | %s | #%d | Age %d\n",
               i+1,
               team.players[i].name,
               team.players[i].pos,
               team.players[i].number,
               team.players[i].age);
    }
}

/*
 * Function: search_player
 * -----------------------
 * Searches for a player by number.
 *
 * team: Team struct (passed by value)
 *
 * returns: void
 */
void search_player(struct Team team){
    int num;
    printf("Enter player number to search: ");
    scanf("%d", &num);

    for(int i=0; i<team.countPlayers; i++){
        if(team.players[i].number == num){
            printf("Found → %s | %s | #%d | Age %d\n",
                   team.players[i].name,
                   team.players[i].pos,
                   team.players[i].number,
                   team.players[i].age);
            return;
        }
    }

    printf("Player not found.\n");
}

/*
 * Function: save_file
 * -------------------
 * Saves all team players to "players.txt".
 *
 * team: Team struct (passed by value)
 *
 * returns: void
 */
void save_file(struct Team team){
    FILE *f = fopen("players.txt","w");
    if(!f){
        printf("Cannot open file!\n");
        return;
    }

    for(int i=0; i<team.countPlayers; i++){
        fprintf(f,"%s,%s,%d,%d\n",
                team.players[i].name,
                team.players[i].pos,
                team.players[i].number,
                team.players[i].age);
    }

    fclose(f);
    printf("Players saved.\n");
}

/*
 * Function: load_file
 * -------------------
 * Loads all players from "players.txt" into the team.
 *
 * team: pointer to Team struct
 *
 * returns: void
 */
void load_file(struct Team *team){
    FILE *f = fopen("players.txt","r");
    if(!f){
        printf("No file found.\n");
        return;
    }

    team->countPlayers = 0;

    while(fscanf(f,"%99[^,],%99[^,],%d,%d\n",
                 team->players[team->countPlayers].name,
                 team->players[team->countPlayers].pos,
                 &team->players[team->countPlayers].number,
                 &team->players[team->countPlayers].age) == 4){

        team->countPlayers++;
        if(team->countPlayers >= MAX_PLAYERS)
            break;
    }

    fclose(f);
    printf("Players loaded (%d).\n", team->countPlayers);
}

/*
 * Function: show_menu
 * -------------------
 * Prints the main menu.
 *
 * returns: void
 */
void show_menu(){
    printf("\n--- FOOTBALL TEAM MANAGER ---\n");
    printf("1. Add Player\n");
    printf("2. Display Players\n");
    printf("3. Search by Number\n");
    printf("4. Save to File\n");
    printf("5. Load from File\n");
    printf("6. Exit\n");
    printf("Choice: ");
}

/*
 * Main function
 * -------------
 * High-level overview of the program execution.
 */
int main(){
    struct Team team;
    team.countPlayers = 0;
    int choice;

    do{
        show_menu();
        scanf("%d", &choice);

        switch(choice){
            case 1:
                add_player(&team);
                break;
            case 2:
                display_players(team);
                break;
            case 3:
                search_player(team);
                break;
            case 4:
                save_file(team);
                break;
            case 5:
                load_file(&team);
                break;
            case 6:
                printf("Exiting...\n");
                break;
            default:
                printf("Enter a number 1-6!\n");
        }

    } while(choice != 6);

    return 0;
}
