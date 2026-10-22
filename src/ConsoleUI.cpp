#include <iostream>
#include <limits>
#include <string>
#define NOMINMAX
#include <windows.h>

#include "../include/ConsoleUI.h"
#include "../include/BoxStrage.h"
#include "../include/Pokemon.h"
#include "../include/Search.h"
#include <consoleapi2.h>
#include <wingdi.h>
#include <iomanip>

extern PokemonDepositSystem users_data;
extern std::vector<FindPokemonData> find_pokemon_list;
extern int find_pokemon_count;

int current_box_index = 0;
int previous_box_index = 0;
int next_box_index = 0;
int user_input = 0;

void SetTextColor(WORD color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

std::string PadDisplayWidth(const std::string& text, int display_width) {
	int width = 0;
	for (std::size_t index = 0; index < text.size();) {
		const unsigned char character = static_cast<unsigned char>(text[index]);
		if ((character & 0x80) == 0) {
			++width;
			++index;
		} else if ((character & 0xE0) == 0xC0) {
			width += 2;
			index += 2;
		} else if ((character & 0xF0) == 0xE0) {
			width += 2;
			index += 3;
		} else {
			width += 2;
			index += 4;
		}
	}

	if (width < display_width) {
		return text + std::string(display_width - width, ' ');
	}
	return text;
}

void HomeMenuLoad() {
	std::cout << "=== ポケモンボックスシステム ===" << std::endl;
	std::cout << "1:ポケモンをスカウトする" << std::endl;
	std::cout << "2:ボックス預かりシステム" << std::endl;
	while(true){
		std::cin >> user_input;
		switch (user_input) {
			case 1:
				ScoutMenuLoad();
				break;
			case 2:
				BoxMenuLoad(current_box_index);
				break;
			default :
				ErrorTextLoad();
		}
	}
}

void ScoutMenuLoad() {
	if(users_data.pokemon_deposit_system.getCurrentPokemonCount() >= users_data.pokemon_deposit_system.MaxPokemonCount()) {
		std::cout << "ボックスが満杯です。" << std::endl;
		HomeMenuLoad();
	}
	std::cout << "=== ポケモンスカウト ===" << std::endl;
	std::cout << "1:スカウトする\t2:大量スカウトする\t3:ホームに戻る" << std::endl;
	while(true){
	std::cin >> user_input;
		switch (user_input) {
			case 1:
				ScoutPokemon();
				break;
			case 2:
				MultupleScout();
				break;
			case 3:
				HomeMenuLoad();
				break;
			default:
				ErrorTextLoad();
		}
	}
}

void BoxMenuLoad(int current_box_index) {
	while (true) {
		std::cout << "ボックス " << current_box_index + 1 << ":" << std::endl;
		for (int i = 0; i < CAPACITY; ++i) {
			const PokemonData& pokemon = users_data.pokemon_deposit_system.box_list[current_box_index].pokemon_box[i];
			const std::string& display_name = pokemon.name;
			const int& display_level = pokemon.level;
			if(i < 9){
				std::cout << "[ " << i + 1;
			} else {
				std::cout << "[" << i + 1;
			}
			if(pokemon.id > 0){
				std::cout << ":Lv" << std::setw(2) << pokemon.level << " " << PadDisplayWidth(display_name, 10) << "]";
			} else {
				std::cout << PadDisplayWidth(display_name, 16) << "]";
			}
			if (i % 6 == 5) {
				std::cout << std::endl;
			}
		}

		std::cout << "1:前のボックス\t2:次のボックス"	 << std::endl;
		std::cout << "3:ポケモンを選択\t4:ポケモンを検索する" << std::endl;
		std::cout << "5:ポケモンを範囲選択\t6:ホームに戻る" << std::endl;
		std::cin >> user_input;

		switch (user_input) {
			case 1:
				if(current_box_index == 0){
					current_box_index = BOX_COUNT - 1;
					break;
				} else {
					current_box_index--;
					break;
				}
			case 2:
				if(current_box_index == BOX_COUNT - 1){
					current_box_index = 0;
					break;
				} else {
					current_box_index++;
					break;
				}
			case 3:
				SelectPokemonMenu();
				break;	
			case 4:
				SearchMenuLoad();
				break;
			case 5:
				RangeCarrySelection();
				break;
			case 6:
				HomeMenuLoad();
				break;
			default:
				ErrorTextLoad();
		}
	}
}

void SearchMenuLoad(){
    std::cout << "=== ポケモンボックス検索 ===" << std::endl;
    std::cout << "1:名前検索\t2:タイプ検索\t3:レベル検索"<< std::endl;
	std::cout << "4:つよさ検索\t5:全ポケモン表示\t6:ホームに戻る"  << std::endl;
    while (true) {
        std::cin >> user_input;
        switch (user_input) {
			case 1:
				NameSearch();
				break;
			case 2:
				TypeSearch();
				break;
			case 3:
				LevelSearch();
				break;
			case 4:
				StatusSearch();
				break;
			case 5:
				ShowAllPokemon();
				break;
			case 6:
				HomeMenuLoad();
			default:
				ErrorTextLoad();
		}
	}
}

void SelectPokemonMenu(){
	std::cout << "ポケモンを選んでください" <<std::endl;
	int select_box_index;
	while(true){
        std::cin >> user_input;
		select_box_index = user_input - 1;
        if(user_input <= 0 || user_input > CAPACITY || std::cin.fail()){
            ErrorTextLoad();
		} else if(users_data.pokemon_deposit_system.box_list[current_box_index].pokemon_box[user_input - 1].id == 0) {
			std::cout << "選択された場所にポケモンがいません。" << std::endl;
			SelectPokemonMenu();
        } else {
            break;
        }
    }

	PokemonData& target_pokemon = users_data.pokemon_deposit_system.box_list[current_box_index].pokemon_box[user_input - 1];
	std::cout << "[Lv" << std::setw(2) << target_pokemon.level << ":" << std::setw(10) << target_pokemon.name << "] " << std::endl;
	while(true){
		std::cout << "1:強さを見る\t2:移動させる\t3:戻る" << std::endl;
		std::cin >> user_input;
		switch (user_input) {
			case 1:
				ViewPokemonStatus(target_pokemon);
				break;
			case 2:
				CarryTargetPokemon(target_pokemon, current_box_index, select_box_index);
				break;
			case 3:
				SelectPokemonMenu();
				break;
			default:
				ErrorTextLoad();
		}
	}
}

void ShowAllPokemon(){
	FindPokemonListReset();
	std::cout << "=== 全ポケモン表示 ===" << std::endl;
	for(int box_list_num = 0; box_list_num < BOX_COUNT; box_list_num++){
		for(int box_num = 0; box_num < CAPACITY; box_num++){
			PokemonData& find_pokemon = users_data.pokemon_deposit_system.box_list[box_list_num].pokemon_box[box_num];
			if (find_pokemon.id == 0) {
				continue;
			}
			find_pokemon_list.push_back({find_pokemon, box_list_num});
			ListUpPokemonView();
		}
	}
	FindPokemonListEmpty();
}

void CarryTargetPokemon(PokemonData& target_pokemon, int current_box_index, int select_box_index) {
	int user_select;
	int previous_box_index = current_box_index;
	std::cout << "どのボックスに移動させますか?" << std::endl;
	while (true) {
		std::cout << "ボックス " << current_box_index + 1 << ":" << std::endl;
		for (int i = 0; i < CAPACITY; ++i) {
			const PokemonData& pokemon = users_data.pokemon_deposit_system.box_list[current_box_index].pokemon_box[i];
			const std::string& display_name = pokemon.name;
			const int& display_level = pokemon.level;
			if(i < 9){
				std::cout << "[ " << i + 1;
			} else {
				std::cout << "[" << i + 1;
			}
			if(pokemon.id > 0){
				std::cout << ":Lv" << std::setw(2) << pokemon.level << " " << PadDisplayWidth(display_name, 10) << "]";
			} else {
				std::cout << PadDisplayWidth(display_name, 16) << "]";
			}
			if (i % 6 == 5) {
				std::cout << std::endl;
			}
		}

		std::cout << "1:前のボックス\t2:次のボックス"	 << std::endl;
		std::cout << "3:このボックスに移動させる\t4:戻る" << std::endl;
		std::cin >> user_input;
		switch (user_input) {
		case 1:
			if(current_box_index == 0){
				current_box_index = BOX_COUNT - 1;
				break;
			} else {
				current_box_index--;
				break;
			}
		case 2:
			if(current_box_index == BOX_COUNT - 1){
				current_box_index = 0;
				break;
			} else {
				current_box_index++;
				break;
			}
		case 3:
			std::cout << "どこに移動させますか?" << std::endl;
				while(true){
				std::cin >> user_input;
				if(user_input <= 0 || user_input > CAPACITY || std::cin.fail()){
					ErrorTextLoad();
				}
				std::cout << "ボックス" << current_box_index + 1 << "の" << user_input << "に移動させますか?" << std::endl;
				std::cout << "1:はい\t2:いいえ" << std::endl;
				while(true){
					std::cin >> user_select;
					if(user_select == 1){
						PokemonData& switch_pokemon = users_data.pokemon_deposit_system.box_list[current_box_index].pokemon_box[user_input -1];
						PokemonData TempPokemon = {};
						if(switch_pokemon.id == 0){
							const std::string target_pokemon_name = target_pokemon.name;
							users_data.pokemon_deposit_system.box_list[current_box_index].pokemon_box[user_input - 1] = target_pokemon;
							users_data.pokemon_deposit_system.box_list[previous_box_index].pokemon_box[select_box_index] = TempPokemon;
							std::cout << "[" << target_pokemon_name << "] " << "をボックス" << current_box_index + 1 << "に移動させました。" << std::endl;
							BoxMenuLoad(current_box_index);
							break;
						} else {
							TempPokemon = switch_pokemon;
							users_data.pokemon_deposit_system.box_list[current_box_index].pokemon_box[user_input - 1] = target_pokemon;
							users_data.pokemon_deposit_system.box_list[previous_box_index].pokemon_box[select_box_index] = TempPokemon;
							std::cout << "[" << target_pokemon.name << "] " << "をボックス" << current_box_index + 1 << "に移動させました。" << std::endl;
							std::cout << "[" << switch_pokemon.name << "] " << "をボックス" << previous_box_index + 1 << "に移動させました。" << std::endl;
							BoxMenuLoad(current_box_index);
						}
						break;
					} else if(user_select == 2){
						std::cout << "どこに移動させますか?" << std::endl;
						break;
					} else {
						ErrorTextLoad();
					}
				}
			}
			break;	
		case 4:
			CarryTargetPokemon(target_pokemon, current_box_index, select_box_index);
			break;
		default:
			ErrorTextLoad();
		}
	}
}

void RangeCarrySelection() {
	int cursor_row = 0;
	int cursor_col = 0;
	int start_row = 0;
	int start_col = 0;
	int source_box_index = current_box_index;
	std::string input;
	bool selection_started = false;

	auto draw_box = [&](int box_index, int active_row, int active_col, bool draw_range) {
		std::cout << "ボックス " << box_index + 1 << ":" << std::endl;
		for (int row = 0; row < 5; ++row) {
			for (int col = 0; col < 6; ++col) {
				const PokemonData& pokemon = users_data.pokemon_deposit_system.box_list[box_index].pokemon_box[row * 6 + col];
				const bool in_range = draw_range &&
					row >= std::min(start_row, active_row) && row <= std::max(start_row, active_row) &&
					col >= std::min(start_col, active_col) && col <= std::max(start_col, active_col);
				if (in_range || (row == active_row && col == active_col)) {
					SetTextColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
				} else {
					SetTextColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
				}
				if (row * 6 + col < 9) {
					std::cout << "[ " << row * 6 + col + 1;
				} else {
					std::cout << "[" << row * 6 + col + 1;
				}
				if (pokemon.id != 0) {
					std::cout << ":Lv" << std::setw(2) << pokemon.level << " " << PadDisplayWidth(pokemon.name, 10) << "]";
				} else {
					std::cout << PadDisplayWidth(pokemon.name, 16) << "]";
				}
				if (col == 5) {
					std::cout << std::endl;
				}
			}
		}
		SetTextColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	};

	while (true) {
		draw_box(current_box_index, cursor_row, cursor_col, selection_started);
		std::cout << (selection_started ? "4:範囲を確定" : "1:前のボックス\t2:次のボックス\t3:選択を開始") << std::endl;
		std::cout << "カーソル移動 W:↑ A:← S:↓ D:→\t5:ボックスメニューへ戻る" << std::endl;
		std::cin >> input;
		if (std::cin.fail() || input.empty()) {
			ErrorTextLoad();
			continue;
		}

		switch (input[0]) {
		case '1':
			if (!selection_started) {
				current_box_index = current_box_index == 0 ? BOX_COUNT - 1 : current_box_index - 1;
				cursor_row = cursor_col = 0;
			} else {
				ErrorTextLoad();
			}
			break;
		case '2':
			if (!selection_started) {
				current_box_index = current_box_index == BOX_COUNT - 1 ? 0 : current_box_index + 1;
				cursor_row = cursor_col = 0;
			} else {
				ErrorTextLoad();
			}
			break;
		case '3':
			if (!selection_started) {
				source_box_index = current_box_index;
				start_row = cursor_row;
				start_col = cursor_col;
				selection_started = true;
			} else {
				ErrorTextLoad();
			}
			break;
		case '4': {
			if (!selection_started) {
				ErrorTextLoad();
				break;
			}
			std::vector<PokemonData> selected_pokemon;
			for (int row = std::min(start_row, cursor_row); row <= std::max(start_row, cursor_row); ++row) {
				for (int col = std::min(start_col, cursor_col); col <= std::max(start_col, cursor_col); ++col) {
					const PokemonData& pokemon = users_data.pokemon_deposit_system.box_list[source_box_index].pokemon_box[row * 6 + col];
					if (pokemon.id != 0) {
						selected_pokemon.push_back(pokemon);
					}
				}
			}
			if (selected_pokemon.empty()) {
				std::cout << "選択範囲にポケモンがいません。" << std::endl;
				break;
			}

			const int selection_end_row = cursor_row;
			const int selection_end_col = cursor_col;
			int destination_box_index = source_box_index;
			cursor_row = cursor_col = 0;
			while (true) {
				draw_box(destination_box_index, cursor_row, cursor_col, false);
				std::cout << "移動先を選択してください" << std::endl;
				std::cout << "1:前のボックス\t2:次のボックス\t3:移動先を確定\t5:戻る" << std::endl;
				std::cin >> input;
				if (std::cin.fail() || input.empty()) {
					ErrorTextLoad();
					continue;
				}
				if (input[0] == '1') {
					destination_box_index = destination_box_index == 0 ? BOX_COUNT - 1 : destination_box_index - 1;
					cursor_row = cursor_col = 0;
				} else if (input[0] == '2') {
					destination_box_index = destination_box_index == BOX_COUNT - 1 ? 0 : destination_box_index + 1;
					cursor_row = cursor_col = 0;
				} else if (input[0] == '3') {
					int empty_count = 0;
					for (const PokemonData& pokemon : users_data.pokemon_deposit_system.box_list[destination_box_index].pokemon_box) {
						if (pokemon.id == 0) {
							++empty_count;
						}
					}
					if (destination_box_index == source_box_index) {
						empty_count += static_cast<int>(selected_pokemon.size());
					}
					if (empty_count < static_cast<int>(selected_pokemon.size())) {
						std::cout << "選択したポケモンの数以上の空きがないため、選択できません。" << std::endl;
						continue;
					}

					for (int row = std::min(start_row, selection_end_row); row <= std::max(start_row, selection_end_row); ++row) {
						for (int col = std::min(start_col, selection_end_col); col <= std::max(start_col, selection_end_col); ++col) {
							users_data.pokemon_deposit_system.box_list[source_box_index].pokemon_box[row * 6 + col] = {};
						}
					}
					for (PokemonData& pokemon : users_data.pokemon_deposit_system.box_list[destination_box_index].pokemon_box) {
						if (pokemon.id == 0 && !selected_pokemon.empty()) {
							pokemon = selected_pokemon.front();
							selected_pokemon.erase(selected_pokemon.begin());
						}
					}
					current_box_index = destination_box_index;
					BoxMenuLoad(current_box_index);
					return;
				} else if (input[0] == '5') {
					break;
				} else if (input[0] == 'W' || input[0] == 'w') {
					cursor_row = std::max(0, cursor_row - 1);
				} else if (input[0] == 'A' || input[0] == 'a') {
					cursor_col = std::max(0, cursor_col - 1);
				} else if (input[0] == 'S' || input[0] == 's') {
					cursor_row = std::min(4, cursor_row + 1);
				} else if (input[0] == 'D' || input[0] == 'd') {
					cursor_col = std::min(5, cursor_col + 1);
				} else {
					ErrorTextLoad();
				}
			}
			break;
		}
		case 'W':
		case 'w':
			cursor_row = std::max(0, cursor_row - 1);
			break;
		case 'A':
		case 'a':
			cursor_col = std::max(0, cursor_col - 1);
			break;
		case 'S':
		case 's':
			cursor_row = std::min(4, cursor_row + 1);
			break;
		case 'D':
		case 'd':
			cursor_col = std::min(5, cursor_col + 1);
			break;
		case '5':
			BoxMenuLoad(current_box_index);
			return;
		default:
			ErrorTextLoad();
		}
	}
}

void PokemonRangeSelectView(){
	int box_row = 0;
	int box_col = 0;
	int cursor_row = 0;
	int cursor_col = 0;
	int start_row = 0;
	int start_col = 0;
	int previous_box_index = current_box_index;
	bool selection_started = false;
	std::string range_carry_user_input;
	std::array<std::array<PokemonData, 6>, 5> box_grid_pokemon_data;
	std::array<std::array<PokemonData, 6>, 5> temp_grid_pokemon_data;
	const bool is_in_selected_range = selection_started &&
				box_row >= std::min(start_row, cursor_row) &&
				box_row <= std::max(start_row, cursor_row) &&
				box_col >= std::min(start_col, cursor_col) &&
				box_col <= std::max(start_col, cursor_col);
	const bool is_cursor_position = box_row == cursor_row && box_col == cursor_col;

	std::cout << "ボックス " << current_box_index + 1 << ":" << std::endl;
	for (box_row = 0; box_row < 5; ++box_row) {
		for (box_col = 0; box_col < 6; ++box_col) {
			const PokemonData& pokemon = users_data.pokemon_deposit_system.box_list[current_box_index].pokemon_box[box_row * 6 + box_col];
			const std::string& display_name = pokemon.name;
			const int& display_level = pokemon.level;
			box_grid_pokemon_data[box_row][box_col] = users_data.pokemon_deposit_system.box_list[previous_box_index].pokemon_box[box_row * 6 + box_col];
			temp_grid_pokemon_data[box_row][box_col] = users_data.pokemon_deposit_system.box_list[current_box_index].pokemon_box[box_row * 6 + box_col];
				
			if (box_row == cursor_row && box_col == cursor_col) {
				SetTextColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			} else {
				SetTextColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			}
			if(box_row * 6 + box_col < 9){
				std::cout << "[ " << box_row * 6 + box_col + 1;
			} else {
				std::cout << "[" << box_row * 6 + box_col + 1;
			}
			if(pokemon.id > 0){
				std::cout << ":Lv" << std::setw(2) << pokemon.level << " " << PadDisplayWidth(display_name, 10) << "]";
			} else {
				std::cout << PadDisplayWidth(display_name, 16) << "]";
			}
			if (box_col % 6 == 5) {
				std::cout << std::endl;
			}
			SetTextColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		}
	}
}

void ViewPokemonStatus(PokemonData& target_pokemon) {
	std::cout << "Lv" << std::setw(2) << target_pokemon.level << " " << target_pokemon.name << std::endl;
	std::cout << "タイプ: ";
	for (const auto& type : target_pokemon.types) {
		std::cout << type << " ";
	}
	std::cout << std::endl;
	std::cout << "HP: " << target_pokemon.hp << " / " << target_pokemon.hp << std::endl;
	std::cout << "こうげき: " << target_pokemon.attack << std::endl;
	std::cout << "ぼうぎょ: " << target_pokemon.defense << std::endl;
	std::cout << "ANY KEY ENTER:戻る" << std::endl;
	std::cin >> user_input;
	find_pokemon_count = 0;
	for(int i = 0; i < find_pokemon_list.size(); i++){
		ListUpPokemonView();
	}
	SearchResult();
}

void ErrorTextLoad() {
	std::cout << "無効な値です。" << std::endl;
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
}