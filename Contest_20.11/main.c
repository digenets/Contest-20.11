#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define SIZE 20
#define SIZE1 10000
#define SIZE2 100

struct stack{
    char name[SIZE];
    int games,
        homeGames,
        wonGames,
        fallGames,
        goals,
        fallGoals,
        fighters;
    struct stack *next;
};

struct stack *create (struct stack *head);
struct stack *create1(struct stack *head, bool IsTeam1Won, bool IsDraw, int team1_count, int team2_count, char* name);
struct stack *create2(struct stack *head, bool IsTeam2Won, bool IsDraw, int team1_count, int team2_count, char* name);
int pow(int x, int y);

int main(){
    FILE * inp = fopen("/home/datsky-prince/CLionProjects/Contest_20.11/input.txt", "rt");
    FILE * out = fopen("/home/datsky-prince/CLionProjects/Contest_20.11/output.txt", "wt");
    struct stack *head;
    head = NULL;
    char string[1000] = {0};
    char team_name[100] = {0};
    int c = 0;
//    head = create(head);


    while(!feof(inp)) {

        fgets(string, 100, inp);
        char curSymb         = 0;
        int c                = 0;
        int k                = 0;
        char team1_name[100] = {0};
        char team2_name[100] = {0};
        int team1_count      = 0;
        int team2_count      = 0;
        while (curSymb != 32) {
            curSymb = string[k];
            team1_name[c] = curSymb;
            c++;
            k++;
        }
        team1_name[c - 1] = 0;
        c = 0;
        k += 2;
        curSymb = string[k];
        while (curSymb != 32) {
            curSymb = string[k];
            team2_name[c] = curSymb;
            c++;
            k++;
        }
        team2_name[c - 1] = 0;
        char curent = string[k];
        int z = 0, x = 0;
        char arrTeam1[SIZE2] = {0};
        char arrTeam2[SIZE2] = {0};
        while (curent != 58){
            arrTeam1[z] = curent;
            z++;
            k++;
            curent = string[k];
        }
        z--;
        int i = 0;
        while (arrTeam1[i]!= '\0'){
            team1_count = team1_count + (arrTeam1[z-i]-48) * pow(10, i);
            i++;
        }
        z=0;
        k+=1;
        curent = string[k];
        while ((curent != '\n') && (curent != '\0')){
            arrTeam2[z] = curent;
            z++;
            k++;
            curent = string[k];
        }
        i=0;
        z--;
        while (arrTeam2[i]!= '\0'){
            team2_count = team2_count + (arrTeam2[z-i]-48) * pow(10, i);
            i++;
        }

        bool IsTeam1Won = (team1_count > team2_count) ? 1 : 0;
        bool IsTeam2Won = (team1_count < team2_count) ? 1 : 0;
        bool IsDraw     = (team1_count == team2_count) ? 1 : 0;

        struct stack *temp = head;
        bool struct_with_such_team1_exists = 0;
        while ((temp != NULL) && (struct_with_such_team1_exists == 0)){
            struct_with_such_team1_exists = !strcmp(team1_name, temp->name) ? 1 : 0;
            if (struct_with_such_team1_exists)
                break;
            temp = temp->next;
        }
        if (!struct_with_such_team1_exists){
            head = create1(head, IsTeam1Won, IsDraw, team1_count, team2_count, team1_name);
        }
        else if (struct_with_such_team1_exists){
            temp->goals     += team1_count;
            temp->homeGames ++;
            if (strcmp(team1_name, team2_name) != 0){ // если неодинаковые
                temp->fighters ++;
            }
            temp->fallGoals += team2_count;
            if (IsTeam1Won)
                temp->wonGames ++;
            else if (!IsDraw)
                temp->fallGames++;
            temp->games += 1;
        }

        temp = head;
        bool struct_with_such_team2_exists = 0;
        while ((temp != NULL) && (struct_with_such_team2_exists == 0)){
            struct_with_such_team2_exists = !strcmp(team2_name, temp->name) ? 1 : 0;
            if (struct_with_such_team2_exists)
                break;
            temp = temp->next;
        }
        if (!struct_with_such_team2_exists){
            head = create2(head, IsTeam2Won, IsDraw, team1_count, team2_count, team2_name);
        }
        else{
            if (IsTeam2Won)
                temp->wonGames ++;
            else if (!IsDraw)
                temp->fallGames ++;
            temp->games ++;
            if (strcmp(team1_name, team2_name) != 0){ // если неодинаковые
                temp->fighters ++;
            }
            temp->goals += team2_count;
            temp->fallGoals += team1_count;
        }
    }
    while(head != NULL)
    {
        fputs(head->name, out);
        fputc(' ', out);
        fprintf(out, "%d", head->games);
        fputc(' ', out);
        fprintf(out, "%d", head->homeGames);
        fputc(' ', out);
        fprintf(out, "%d", head->wonGames);
        fputc(' ', out);
        fprintf(out, "%d", head->fallGames);
        fputc(' ', out);
        fprintf(out, "%d", head->goals);
        fputc(' ', out);
        fprintf(out, "%d", head->fallGoals);
        fputc(' ',out);
        fprintf(out, "%d", head->fighters);
        fputc('\n', out);
        struct stack* temp;
        temp = head;
        head = head->next;
        free(temp);
    }
    fclose(inp);
    fclose(out);
    return 0;
}


struct stack *create(struct stack *head) {
    struct stack *element; // указатель на новую структуру
    element = (struct stack *)malloc(sizeof(struct stack)); // выделяем память
    element->next = head;
    return element;
}

struct stack *create1(struct stack *head, bool IsTeam1Won, bool IsDraw, int team1_count, int team2_count, char* teamname) {
    struct stack *element; // указатель на новую структуру
    element = (struct stack *)malloc(sizeof(struct stack)); // выделяем память
    element->next      = head;
    element->games     = 1;
    element->fallGames = (IsTeam1Won || IsDraw) ? 0 : 1;
    element->wonGames  = (IsTeam1Won && !IsDraw) ? 1 : 0;
    element->goals     = team1_count;
    element->fallGoals = team2_count;
    element->fighters  = 1;
    element->homeGames = 1;
    strcpy(element->name, teamname);
    return element;
}

struct stack *create2(struct stack *head, bool IsTeam2Won, bool IsDraw, int team1_count, int team2_count, char* teamname) {
    struct stack *element; // указатель на новую структуру
    element = (struct stack *) malloc(sizeof(struct stack)); // выделяем память
    element->next = head;
    element->games = 1;
    element->fallGames = (IsTeam2Won || IsDraw) ? 0 : 1;
    element->wonGames = (IsTeam2Won && !IsDraw) ? 1 : 0;
    element->goals = team2_count;
    element->fallGoals = team1_count;
    element->fighters = 1;
    element->homeGames = 0;
    strcpy(element->name, teamname);
    return element;
}

int pow(int x, int y){
    int temp = x;
    if (y==0)
        return 1;
    else {
        while(y!=1) {
            x = x * temp;
            y--;
        }
        return x;
    }
}
