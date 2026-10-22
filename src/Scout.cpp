#include <string>
#include <vector>
#include <array>
#include <iostream>
#include <limits>

#include "../include/Pokemon.h"
#include "../include/Box.h"
#include "../include/BoxStrage.h"
#include "../include/ConsoleUI.h"

extern const PokemonDataBase pokemon_data;
extern PokemonDepositSystem users_data;
int box_index = 0; // 現在のボックスのインデックスを保持する変数
int chosen_pokemon_index = 0; // 選択されたポケモンのインデックスを保持する変数
int multiple_scout_count = 151; // 大量スカウトの回数を保持する変数

void ScoutPokemon() {
    std::vector<PokemonData> scout_list = {}; // スカウトリストを格納する配列    
    std::vector<bool> selected_ids(pokemon_data.pokemon_list.size(), false);

    //ポケモンの抽選処理
    for(int i = 0; i < 10; ++i){
        int scout_pokemon_id;
        do {
            scout_pokemon_id = rand() % pokemon_data.pokemon_list.size() + 1;
        } while (selected_ids[scout_pokemon_id - 1]);

        selected_ids[scout_pokemon_id - 1] = true;
        scout_list.push_back(pokemon_data.pokemon_list[scout_pokemon_id - 1]); // ランダムなポケモンをスカウトリストに追加
        if(i == 6){
            std::cout << i + 1 << ":[" << scout_list[i].name << "] " << std::endl;
        } else {
            std::cout << i + 1 << ":[" << scout_list[i].name << "] ";
        }
    }

    //スカウトするポケモンの選択処理
    while(true){
        std::cout << "ポケモンを選択してください (1-10): ";
        std::cin >> chosen_pokemon_index;
        if(chosen_pokemon_index < 1 || chosen_pokemon_index > std::size(scout_list) || std::cin.fail()) {
            ErrorTextLoad();
            for(int i = 0; i < 10; ++i){
                if(i == 6){
                    std::cout << i + 1 << ":[" << scout_list[i].name << "] " << std::endl;
                } else{
                    std::cout << i + 1 << ":[" << scout_list[i].name << "] ";
                }
            }

        } else {
            chosen_pokemon_index = scout_list[chosen_pokemon_index - 1].id; // 選択したポケモンのIDを取得
            AddPokemonToBox(users_data, chosen_pokemon_index); // 選択したポケモンをボックスに追加
            HomeMenuLoad(); // ホームメニューに戻る
            break;
        }
    }
}

void MultupleScout() {
    std::vector<PokemonData> scout_list; // スカウトリストを格納する配列    
    std::vector<bool> selected_ids(pokemon_data.pokemon_list.size(), false);

    //ポケモンの抽選処理
    for(int i = 0; i < multiple_scout_count; ++i){
        int scout_pokemon_id;
        do {
            scout_pokemon_id = rand() % pokemon_data.pokemon_list.size() + 1;
        } while (selected_ids[scout_pokemon_id - 1]);

            selected_ids[scout_pokemon_id - 1] = true;
            scout_list.push_back(pokemon_data.pokemon_list[scout_pokemon_id - 1]); // ランダムなポケモンをスカウトリストに追加
            chosen_pokemon_index = scout_list[i].id; // 選択したポケモンのIDを取得
            AddPokemonToBox(users_data, chosen_pokemon_index); // 選択したポケモンをボックスに追加
    }
    HomeMenuLoad(); // ホームメニューに戻る
}