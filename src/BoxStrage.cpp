#include <iostream>

#include "../include/BoxStrage.h"
#include <iomanip>

extern const PokemonDataBase pokemon_data;
PokemonDepositSystem users_data;

void AddPokemonToBox(PokemonDepositSystem& users_data, int chosen_pokemon_index) {
	for (std::size_t box_index = 0; box_index < BOX_COUNT; ++box_index) {
		for (std::size_t pokemon_index = 0; pokemon_index < CAPACITY; ++pokemon_index) {
			if (users_data.pokemon_deposit_system.box_list[box_index].pokemon_box[pokemon_index].id == 0) {
				users_data.pokemon_deposit_system.box_list[box_index].pokemon_box[pokemon_index] =
					pokemon_data.pokemon_list[chosen_pokemon_index - 1];
				std::cout << "[" << std::setw(13) << pokemon_data.pokemon_list[chosen_pokemon_index - 1].name
						  << "]をボックスに追加しました。" << std::endl;
				return;
			}
		}
	}
}