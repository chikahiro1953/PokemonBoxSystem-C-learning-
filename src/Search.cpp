#include <array>
#include <iostream>
#include <string>
#include <vector>

#include "../include/BoxStrage.h"
#include "../include/ConsoleUI.h"
#include "../include/Search.h"
#include "../include/Box.h"
#include <algorithm>
#include <iomanip>

int find_pokemon_count = 0;
int box_list_num = 0;
int box_num = 0;
int find_pokemon_box_num = 0;
int user_first_select_num = 0;
int user_select_pokemon_num = 0;
extern PokemonDepositSystem users_data;
PokemonData search_pokemon = users_data.pokemon_deposit_system.box_list[0].pokemon_box[0];
PokemonData& find_pokemon = users_data.pokemon_deposit_system.box_list[box_list_num].pokemon_box[box_num];
std::vector<FindPokemonData> find_pokemon_list;

const std::array<std::string, 16> kana_row = {
	"ア行", "カ行", "サ行", "タ行", "ナ行",
	"ハ行", "マ行", "ヤ行", "ラ行", "ワ行",
    "ガ行", "ザ行", "ダ行", "バ行", "パ行",
    "小文字",
};

const std::array<std::string, 18> type_list = {
    "ノーマル", "ほのお", "みず", "でんき", "くさ", "こおり",
    "かくとう", "どく", "じめん", "ひこう", "エスパー", "むし",
    "いわ", "ゴースト", "ドラゴン", "あく", "はがね", "フェアリー"
};

const std::array<std::array<std::string, 5>, 16> all_kana_list = {{
    {"ア", "イ", "ウ", "エ", "オ"}, {"カ", "キ", "ク", "ケ", "コ"},
	{"サ", "シ", "ス", "セ", "ソ"}, {"タ", "チ", "ツ", "テ", "ト"}, 
	{"ナ", "ニ", "ヌ", "ネ", "ノ"}, {"ハ", "ヒ", "フ", "ヘ", "ホ"},
	{"マ", "ミ", "ム", "メ", "モ"}, {"ヤ", "ユ", "ヨ", " ", " ",},
	{"ラ", "リ", "ル", "レ", "ロ"}, {"ワ", "ヲ", "ン", " ", " ",},
    {"ガ", "ギ", "グ", "ゲ", "ゴ"}, {"ザ", "ジ", "ズ", "ゼ", "ゾ"},
    {"ダ", "ヂ", "ヅ", "デ", "ド"}, {"バ", "ビ", "ブ", "ベ", "ボ"}, 
    {"パ", "ピ", "プ", "ペ", "ポ"}, {"ャ", "ュ", "ョ", "ッ", ""},
}};

const std::array<std::string, 10> level_list = {"1~10", "11~20", "21~30", "31~40", "41~50", "51~60", "61~70", "71~80", "81~90", "91~100"};

void NameSearch(){
    FindPokemonListReset();
    std::cout << "=== 名前検索 ===" << std::endl;
    std::cout << "ポケモンに含まれる文字を選択してください"  << std::endl;
    for(int first_list_up_num = 0; first_list_up_num < std::size(kana_row); first_list_up_num++){
        std::cout << first_list_up_num + 1 << ":[" << kana_row[first_list_up_num] << "] ";
        if(first_list_up_num == 8){
            std::cout << std::endl;
        }
    }

    while (true) {
        std::cin >> user_input;
        if (user_input >= 1 && user_input <= static_cast<int>(std::size(kana_row))) {
            user_first_select_num = user_input - 1;
            break;
        }
        ErrorTextLoad();
    }

    for(int second_list_up_num = 0; second_list_up_num < std::size(all_kana_list[user_first_select_num]); second_list_up_num++){
        if(all_kana_list[user_first_select_num][user_input] != " "){
            std::cout << second_list_up_num + 1 << ":[" << all_kana_list[user_first_select_num][second_list_up_num] << "] ";
        }
    }

    while(true){
        std::cin >> user_input;
        if(user_input < 0 || user_input > std::size(all_kana_list[user_first_select_num]) || std::cin.fail()){
            ErrorTextLoad();
        } else {
            break;
        }
    }

    for(box_list_num = 0; box_list_num < BOX_COUNT; box_list_num++){
        for(box_num = 0; box_num < CAPACITY; box_num++){
            PokemonData& find_pokemon = users_data.pokemon_deposit_system.box_list[box_list_num].pokemon_box[box_num];
            if (find_pokemon.name.find(all_kana_list[user_first_select_num][user_input - 1]) != std::string::npos) {
                find_pokemon_list.push_back({find_pokemon, box_list_num});
                ListUpPokemonView();
            }
        }
    }
    FindPokemonListEmpty();
}

void TypeSearch(){
    FindPokemonListReset();
    std::cout << "=== タイプ検索 ===" << std::endl;
    std::cout << "ポケモンのタイプを選択してください"  << std::endl;
    for(int first_list_up_num = 0; first_list_up_num < std::size(type_list); first_list_up_num++){
        std::cout << first_list_up_num + 1 << ":[" << type_list[first_list_up_num] << "] ";
        if(first_list_up_num == 8){
            std::cout << std::endl;
        }
    }

    while(true){
        std::cin >> user_input;
        user_first_select_num = user_input - 1;
       if(user_input < 1 || user_input > std::size(type_list) || std::cin.fail()){
            ErrorTextLoad();
        } else {
            break;
        }
    }

    std::cout << "[" << type_list[user_first_select_num] << "] " << std::endl;
    std::cout << "2つ目のタイプを選択してください"  << std::endl;
    for(int second_list_up_num = 0; second_list_up_num < std::size(type_list); second_list_up_num++){
        if (second_list_up_num < user_first_select_num){
            std::cout << second_list_up_num + 1 << ":[" << type_list[second_list_up_num] << "] ";
        } else if (second_list_up_num == std::size(type_list) - 1){
            std::cout << std::size(type_list) << ":[" << type_list[user_first_select_num] << "のみ" << "]" << std::endl;
        } else {
            std::cout << second_list_up_num + 1 << ":[" << type_list[second_list_up_num + 1] << "] ";
        }

        if(second_list_up_num == 8 || second_list_up_num == std::size(type_list)){
            std::cout << std::endl;
        }
    }

    while(true){
        std::cin >> user_input;
        if(user_input <= 0 || user_input > std::size(type_list) || std::cin.fail()){
            ErrorTextLoad();
        } else {
            break;
        }
    }

    for(box_list_num = 0; box_list_num < BOX_COUNT; box_list_num++){
        for(box_num = 0; box_num < CAPACITY; box_num++){
            PokemonData& find_pokemon = users_data.pokemon_deposit_system.box_list[box_list_num].pokemon_box[box_num];
            if (find_pokemon.id == 0) {
                continue;
            }
            const std::string type1 = find_pokemon.types.size() > 0 ? find_pokemon.types[0] : "";
            const std::string type2 = find_pokemon.types.size() > 1 ? find_pokemon.types[1] : "";
            if(user_input == 18){
                if (type1 == type_list[user_first_select_num] &&
                    find_pokemon.types.size() == 1) {
                    find_pokemon_list.push_back({find_pokemon, box_list_num});
                    ListUpPokemonView();  
                }
            }
            if(user_input >= 1 && user_input <= 17){
                if (type1 == type_list[user_first_select_num] ||
                    type1 == type_list[user_input] ||
                    type2 == type_list[user_first_select_num] ||
                    type2 == type_list[user_input]) {
                    find_pokemon_list.push_back({find_pokemon, box_list_num});
                    ListUpPokemonView();       
                }
            } 
            if(user_input < 1 || user_input > std::size(type_list) || std::cin.fail()){
                ErrorTextLoad();
                continue;
            }
        }
    }
    FindPokemonListEmpty();
};

void LevelSearch(){
    FindPokemonListReset();
    std::cout << "=== レベル検索 ===" << std::endl;
    std::cout << "ポケモンのレベルを選択してください"  << std::endl;
    for(int i = 0; i < std::size(level_list); i++){
        std::cout << i + 1 << ":[" << level_list[i] << "] ";
        if(i == 4){
            std::cout << std::endl;
        }
    }
    while(true){
        std::cin >> user_input;
        if(user_input <= 0 || user_input > std::size(level_list) || std::cin.fail()){
            ErrorTextLoad();
        } else {
            break;
        }
    }
    for(box_list_num = 0; box_list_num < BOX_COUNT; box_list_num++){
        for(box_num = 0; box_num < CAPACITY; box_num++){
            PokemonData& find_pokemon = users_data.pokemon_deposit_system.box_list[box_list_num].pokemon_box[box_num];
            switch(user_input){
                case 1:
                    if(find_pokemon.level >= 1 && find_pokemon.level <= 10){
                        find_pokemon_list.push_back({find_pokemon, box_list_num});
                        ListUpPokemonView();
                    }
                    break;
                case 2:
                    if(find_pokemon.level >= 11 && find_pokemon.level <= 20){
                        find_pokemon_list.push_back({find_pokemon, box_list_num});
                        ListUpPokemonView();
                    }
                    break;
                case 3:
                    if(find_pokemon.level >= 21 && find_pokemon.level <= 30){
                        find_pokemon_list.push_back({find_pokemon, box_list_num});
                        ListUpPokemonView();
                    }
                    break;
                case 4:
                    if(find_pokemon.level >= 31 && find_pokemon.level <= 40){
                        find_pokemon_list.push_back({find_pokemon, box_list_num});
                        ListUpPokemonView();
                    }
                    break;
                case 5:
                    if(find_pokemon.level >= 41 && find_pokemon.level <= 50){
                        find_pokemon_list.push_back({find_pokemon, box_list_num});
                        ListUpPokemonView();
                    }
                    break;
                case 6:
                    if(find_pokemon.level >= 51 && find_pokemon.level <= 60){
                        find_pokemon_list.push_back({find_pokemon, box_list_num});
                        ListUpPokemonView();
                    }
                    break;
                case 7:
                    if(find_pokemon.level >= 61 && find_pokemon.level <= 70){
                        find_pokemon_list.push_back({find_pokemon, box_list_num});
                        ListUpPokemonView();
                    }
                    break;
                case 8:
                    if(find_pokemon.level >= 71 && find_pokemon.level <= 80){
                        find_pokemon_list.push_back({find_pokemon, box_list_num});
                        ListUpPokemonView();
                    }
                    break;
                case 9:
                    if(find_pokemon.level >= 81 && find_pokemon.level <= 90){
                        find_pokemon_list.push_back({find_pokemon, box_list_num});
                        ListUpPokemonView();
                    }
                    break;
                case 10:
                    if(find_pokemon.level >= 91 && find_pokemon.level <= 100){
                        find_pokemon_list.push_back({find_pokemon, box_list_num});
                        ListUpPokemonView();
                    }
                    break;
                default:
                    ErrorTextLoad();
            }
        }
    }
    FindPokemonListEmpty();
}

void StatusSearch(){
    FindPokemonListReset();
    int search_status_min = 0;
    int search_status_max = 0;
    std::cout << "=== つよさ検索 ===" << std::endl;
    std::cout << "どのステータスを調べますか?" << std::endl;
    std::cout << "1:HP  2:こうげき  3:ぼうぎょ" << std::endl;
    while(true){
        std::cin >> user_input;
        if(user_input < 1 || user_input > 3 || std::cin.fail()){
            ErrorTextLoad();
            continue;
        }
        break;
    }
    std::cout << "最小値: ";
    while(true){
        std::cin >> search_status_min;
        if(search_status_min < 0 || std::cin.fail()){
            ErrorTextLoad();
            continue;
        }
        break;
    }
    std::cout << "最大値: ";
    while(true){
    std::cin >> search_status_max;
        if(search_status_max < search_status_min || std::cin.fail()){
            ErrorTextLoad();
            continue;
        }
        break;
    }

    for(box_list_num = 0; box_list_num < BOX_COUNT; box_list_num++){
        for(box_num = 0; box_num < CAPACITY; box_num++){
            PokemonData& find_pokemon = users_data.pokemon_deposit_system.box_list[box_list_num].pokemon_box[box_num];
            switch (user_input) {
                case 1:
                    if(find_pokemon.hp >= search_status_min && find_pokemon.hp <= search_status_max){
                        find_pokemon_list.push_back({find_pokemon, box_list_num});
                        ListUpPokemonView();
                    }
                    break;
                case 2:
                    if(find_pokemon.attack >= search_status_min && find_pokemon.attack <= search_status_max){
                        find_pokemon_list.push_back({find_pokemon, box_list_num});
                        ListUpPokemonView();
                    }
                    break;
                case 3:
                    if(find_pokemon.defense >= search_status_min && find_pokemon.defense <= search_status_max){
                        find_pokemon_list.push_back({find_pokemon, box_list_num});
                        ListUpPokemonView();
                    }
                    break;
                default:
                    ErrorTextLoad();
            }
        }
    }
    FindPokemonListEmpty();
}

void SearchResult(){
    std::cout << std::endl;
    std::cout << "1:[一覧からポケモンを選択]        2:[検索画面に戻る]" << std::endl;
    std::cout << "3:[ポケモンを並べ替える]          4:[ホームに戻る]" << std::endl;
    while(true){
        std::cin >> user_input;
        switch(user_input){
            case 1:
                FindPokemonSelectMenu();
                break;
            case 2:
                SearchMenuLoad();
                break;
            case 3:
                SortPokemonList();
                break;
            case 4:
                HomeMenuLoad();
                break;
            default:
                ErrorTextLoad();
                continue;
        }
    }
}


void ListUpPokemonView(){
    find_pokemon_count += 1;
    std::cout << find_pokemon_count << ":[Lv" << std::setw(2) << find_pokemon_list[find_pokemon_count - 1].find_pokemon.level
        << ":"<< find_pokemon_list[find_pokemon_count - 1].find_pokemon.types[0] << std::setw(15) << find_pokemon_list[find_pokemon_count - 1].find_pokemon.name << "] " << std::endl;
        
}

void FindPokemonListEmpty(){
    if(find_pokemon_list.empty()){
        std::cout << "条件を満たすポケモンはいませんでした。" << std::endl;
        SearchMenuLoad();
    } else {
        SearchResult();
    }
}

void FindPokemonListReset(){
    find_pokemon_count = 0;
    find_pokemon_list.clear();
}

void FindPokemonSelectMenu(){
    std::cout << "ポケモンを選択してください" << std::endl;
    while(true){
        std::cin >> user_input;
        user_select_pokemon_num = user_input;
        if(user_input <= 0 || user_input > find_pokemon_list.size()|| std::cin.fail()){
            ErrorTextLoad();
            continue;
        } else {
           break;
        }
    } 

    std::cout << "[Lv" <<  find_pokemon_list[user_select_pokemon_num - 1].find_pokemon.level << find_pokemon_list[user_input - 1].find_pokemon.name << "] " << std::endl;
    std::cout << "1:つよさを見る  2:ボックスへ移動  3:ホームへ戻る" << std::endl;
    while(true){
		std::cin >> user_input;
		switch (user_input) {
			case 1:
				ViewPokemonStatus(find_pokemon_list[user_select_pokemon_num - 1].find_pokemon);
                break;
			case 2:
                BoxMenuLoad(find_pokemon_list[user_select_pokemon_num - 1].box_number);
                break;
            case 3:
                HomeMenuLoad();
			default :
				ErrorTextLoad();
                continue;
		}
	}
}

void SortPokemonList() {
    std::cout << "並べ替えの条件を選択してください" << std::endl;
    std::cout << "1:名前順  2:レベル順  3:図鑑番号順" << std::endl;
    std::cout << "4:HP順    5:攻撃順    6:防御順" << std::endl;
    while(true){
        std::cin >> user_input;
        switch(user_input){
        case 1:
            std::cout << "1:降順で表示 2:昇順で表示" << std::endl;
                while(true){
                    std::cin >> user_input;
                    if(user_input == 1) {
                        std::sort(find_pokemon_list.begin(), find_pokemon_list.end(), [](const FindPokemonData& a, const FindPokemonData& b) {
                            return a.find_pokemon.name > b.find_pokemon.name;
                        });
                        break;
                    } else if(user_input == 2) {
                        std::sort(find_pokemon_list.begin(), find_pokemon_list.end(), [](const FindPokemonData& a, const FindPokemonData& b) {
                            return a.find_pokemon.name < b.find_pokemon.name;
                        });
                        break;
                    } else {
                        ErrorTextLoad();
                    }
                }
                find_pokemon_count = 0;
                for(int i = 0; i < find_pokemon_list.size(); i++){
                    ListUpPokemonView();
                }
        break;
        case 2:
            std::cout << "1:降順で表示 2:昇順で表示" << std::endl;
                while(true){
                    std::cin >> user_input;
                    if(user_input == 1) {
                        std::sort(find_pokemon_list.begin(), find_pokemon_list.end(), [](const FindPokemonData& a, const FindPokemonData& b) {
                            return a.find_pokemon.level > b.find_pokemon.level;
                        });
                        break;
                    } else if(user_input == 2) {
                        std::sort(find_pokemon_list.begin(), find_pokemon_list.end(), [](const FindPokemonData& a, const FindPokemonData& b) {
                            return a.find_pokemon.level < b.find_pokemon.level;
                        });
                        break;
                    } else {
                        ErrorTextLoad();
                    }
                }
                find_pokemon_count = 0;
                for(int i = 0; i < find_pokemon_list.size(); i++){
                    ListUpPokemonView();
                }
        break;
        case 3:
            std::cout << "1:降順で表示 2:昇順で表示" << std::endl;
                while(true){
                    std::cin >> user_input;
                    if(user_input == 1) {
                        std::sort(find_pokemon_list.begin(), find_pokemon_list.end(), [](const FindPokemonData& a, const FindPokemonData& b) {
                            return a.find_pokemon.id > b.find_pokemon.id;
                        });
                        break;
                    } else if(user_input == 2) {
                        std::sort(find_pokemon_list.begin(), find_pokemon_list.end(), [](const FindPokemonData& a, const FindPokemonData& b) {
                            return a.find_pokemon.id < b.find_pokemon.id;
                        });
                        break;
                    } else {
                        ErrorTextLoad();
                    }
                }
                find_pokemon_count = 0;
                for(int i = 0; i < find_pokemon_list.size(); i++){
                    ListUpPokemonView();
                }
        break;
        case 4:
            std::cout << "1:降順で表示 2:昇順で表示" << std::endl;
                while(true){
                    std::cin >> user_input;
                    if(user_input == 1) {
                        std::sort(find_pokemon_list.begin(), find_pokemon_list.end(), [](const FindPokemonData& a, const FindPokemonData& b) {
                            return a.find_pokemon.hp > b.find_pokemon.hp;
                        });
                        break;
                    } else if(user_input == 2) {
                        std::sort(find_pokemon_list.begin(), find_pokemon_list.end(), [](const FindPokemonData& a, const FindPokemonData& b) {
                            return a.find_pokemon.hp < b.find_pokemon.hp;
                        });
                        break;
                    } else {
                        ErrorTextLoad();
                    }
                }
                find_pokemon_count = 0;
                for(int i = 0; i < find_pokemon_list.size(); i++){
                    ListUpPokemonView();
                }
        break;
        case 5:
            std::cout << "1:降順で表示 2:昇順で表示" << std::endl;
                while(true){
                    std::cin >> user_input;
                    if(user_input == 1) {
                        std::sort(find_pokemon_list.begin(), find_pokemon_list.end(), [](const FindPokemonData& a, const FindPokemonData& b) {
                            return a.find_pokemon.attack > b.find_pokemon.attack;
                        });
                        break;
                    } else if(user_input == 2) {
                        std::sort(find_pokemon_list.begin(), find_pokemon_list.end(), [](const FindPokemonData& a, const FindPokemonData& b) {
                            return a.find_pokemon.attack < b.find_pokemon.attack;
                        });
                        break;
                    } else {
                        ErrorTextLoad();
                    }
                }
                find_pokemon_count = 0;
                for(int i = 0; i < find_pokemon_list.size(); i++){
                    ListUpPokemonView();
                }
        break;
        case 6:
            std::cout << "1:降順で表示 2:昇順で表示" << std::endl;
                while(true){
                    std::cin >> user_input;
                    if(user_input == 1) {
                        std::sort(find_pokemon_list.begin(), find_pokemon_list.end(), [](const FindPokemonData& a, const FindPokemonData& b) {
                            return a.find_pokemon.defense > b.find_pokemon.defense;
                        });
                        break;
                    } else if(user_input == 2) {
                        std::sort(find_pokemon_list.begin(), find_pokemon_list.end(), [](const FindPokemonData& a, const FindPokemonData& b) {
                            return a.find_pokemon.defense < b.find_pokemon.defense;
                        });
                        break;
                    } else {
                        ErrorTextLoad();
                    }
                }
                find_pokemon_count = 0;
                for(int i = 0; i < find_pokemon_list.size(); i++){
                    ListUpPokemonView();
                }
        break;
        default:
            ErrorTextLoad();
            continue;
        }
        return SearchResult();
    }
}