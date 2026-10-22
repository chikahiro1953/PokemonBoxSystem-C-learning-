#pragma once
#include "Box.h"
#include "Pokemon.h"
#include "Scout.h"

void HomeMenuLoad();
void ScoutMenuLoad();
void BoxMenuLoad(int current_box_index);
void SearchMenuLoad();
void StatusSearch();
void ViewPokemonStatus(PokemonData& target_pokemon);
void SelectPokemonMenu();
void ShowAllPokemon();
void CarryTargetPokemon(PokemonData& target_pokemon, int current_box_index, int select_box_index);
void RangeCarrySelection();
void PokemonRangeSelectView();
void ErrorTextLoad();


extern int current_box_index;
extern int previous_box_index;
extern int next_box_index;
extern int user_input;
extern const char *range_carry_user_input;