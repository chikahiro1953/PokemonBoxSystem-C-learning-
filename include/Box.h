#pragma once

#include <array>
#include <string>
#include <vector>
#include "Pokemon.h"

static constexpr std::size_t CAPACITY = 30;
static constexpr std::size_t BOX_COUNT = 8;

struct PokemonBox {
    std::array<PokemonData, CAPACITY> pokemon_box;
};

struct BoxList {
    std::array<PokemonBox, BOX_COUNT> box_list;

    std::size_t MaxPokemonCount() const {
        return box_list.size() * CAPACITY;
    }

    std::size_t getCurrentPokemonCount() const {
        std::size_t count = 0;
        for (const auto& box : box_list) {
            for (const auto& pokemon : box.pokemon_box) {
                if (pokemon.id != 0) {
                    ++count;
                }
            }
        }
        return count;
    }
};

struct PokemonDepositSystem {
    BoxList pokemon_deposit_system;
};

extern BoxList box_system;
extern const int MAX_POKEMON_COUNT;