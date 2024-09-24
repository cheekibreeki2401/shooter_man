#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "csv_parse.h"

typedef struct gun{
	int ammo;
	int damage;
	enum type{PISTOL, SHOTGUN, GATLING, ROCKET, SPECIAL}type;
}gun;

typedef struct shooter{
	int x;
	int y;
	int health;
	gun *equipped_gun;
	struct shooter *next_shooter;
	int id;
}shooter;

void start_game();
shooter* addNewShooter(shooter *head);
void makeNewShooter( int id, shooter *player, char *line);

int main(){
	start_game();
	return 0;
}

void start_game(){
	FILE * stream = fopen("shooters.csv", "r");
	if(stream == NULL){
		printf("Error opening file");
		return;
	}
	char line[256];
	int count = 0;
	shooter *player;
	player = malloc(sizeof(shooter));
	while(fgets(line, sizeof(line), stream)!=NULL){
		if(count==1){
			char *endptr;
			player->id = 0;
			player->x = strtol(getfield(strdup(line), 4), &endptr, 10);
			player->y = strtol(getfield(strdup(line), 5), &endptr, 10);
			player->health = strtol(getfield(strdup(line), 3), &endptr, 10);
			gun *fir_pis;
			fir_pis = malloc(sizeof(gun));
			fir_pis->type = PISTOL;
			fir_pis->ammo = 30;
			fir_pis->damage = 25;
			count+=1;
		} else {
			if(count>1){
				int id = count-1;
				makeNewShooter(id, player, line);
			}
			count+=1;
		}
	}
	fclose(stream);
	shooter *tmp =  malloc(sizeof(shooter));
	tmp = player->next_shooter;
	free(player);
	while(tmp != NULL){
		free(tmp->equipped_gun);
		shooter *tmp2 = malloc(sizeof(shooter));
		tmp2 = tmp;
		tmp = tmp->next_shooter;
		free(tmp2);
	}
	return;
}

shooter* addNewShooter(shooter *head){
	shooter *tmp;
	shooter *new_shooter;
	tmp = malloc(sizeof(shooter));
	new_shooter = malloc(sizeof(shooter));
	tmp = head;
	while(tmp->next_shooter != NULL){
		tmp = tmp->next_shooter;
	}
	tmp -> next_shooter = new_shooter;
	return new_shooter;
}

void makeNewShooter(int id, shooter *player, char *line){
	char *endptr;
	shooter *new_shooter = addNewShooter(player);
	new_shooter->id = id;
	new_shooter->x = strtol(getfield(strdup(line), 4), &endptr, 10);
	new_shooter->y = strtol(getfield(strdup(line), 5), &endptr, 10);
	new_shooter->health = strtol(getfield(strdup(line), 3), &endptr, 10);
	gun *equ_wep;
	equ_wep = malloc(sizeof(gun));
	int weapon_id = strtol(getfield(strdup(line), 2), &endptr, 10);//1=PISTOL, 2=shotgun, 3=gatling, 4=rocket, 5=special
	switch(weapon_id){
		case 1:
			equ_wep->type = PISTOL;
			equ_wep->ammo = 30;
			equ_wep->damage = 25;
			break;
		case 2:
			equ_wep->type = SHOTGUN;
			equ_wep->ammo = 10;
			equ_wep->damage = 30;
			break;
		case 3:
			equ_wep->type = GATLING;
			equ_wep->ammo = 90;
			equ_wep->damage=10;
			break;
		case 4:
			equ_wep->type = ROCKET;
			equ_wep->ammo = 5;
			equ_wep->damage=100;
			break;
		case 5:
			equ_wep->type = SPECIAL;
			equ_wep->ammo = 1;
			equ_wep->damage = 0;
			break;
		default:
			printf("This should not be printed weapon id: %d \n", weapon_id);

	}
	new_shooter->equipped_gun = equ_wep;
	printf("Created entity with id %d \n", new_shooter->id);
	return;
}
