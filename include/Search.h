#include "Box.h"
#include "Pokemon.h"
#include "BoxStrage.h"

struct FindPokemonData {
    PokemonData find_pokemon;
    int box_number;
};

extern std::vector<FindPokemonData> find_pokemon_list;

void NameSearch();
void TypeSearch();
void LevelSearch();
void StatusSearch();
void SearchResult();
void ListUpPokemonView();
void FindPokemonListEmpty();
void FindPokemonSelectMenu();
void FindPokemonListReset();
void SortPokemonList();