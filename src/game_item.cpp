

#include <game_item.h>
#include <lcf/data.h>
#include <lcf/reader_util.h>



std::unordered_map<int, int> Game_Item::idToUniqueIDMap; // Map vide au départ
std::unordered_map<int, int> Game_Item::idCounters;      // Compteurs des IDs


Game_Item::Game_Item(lcf::rpg::SaveUniqueItems* item) {
	itemSave = new lcf::rpg::SaveUniqueItems;

	itemSave->ID = item->ID;
	itemSave->name = item->name;
	itemSave->description = item->description;
	itemSave->type = item->type;
	itemSave->price = item->price;
	itemSave->uses = item->uses;
	itemSave->atk_points1 = item->atk_points1;
	itemSave->def_points1 = item->def_points1;
	itemSave->spi_points1 = item->spi_points1;
	itemSave->agi_points1 = item->agi_points1;
	itemSave->two_handed = item->two_handed;
	itemSave->sp_cost = item->sp_cost;
	itemSave->hit = item->hit;
	itemSave->critical_hit = item->critical_hit;
	itemSave->animation_id = item->animation_id;
	itemSave->preemptive = item->preemptive;
	itemSave->dual_attack = item->dual_attack;
	itemSave->attack_all = item->attack_all;
	itemSave->ignore_evasion = item->ignore_evasion;
	itemSave->prevent_critical = item->prevent_critical;
	itemSave->raise_evasion = item->raise_evasion;
	itemSave->half_sp_cost = item->half_sp_cost;
	itemSave->no_terrain_damage = item->no_terrain_damage;
	itemSave->cursed = item->cursed;
	itemSave->entire_party = item->entire_party;
	itemSave->recover_hp_rate = item->recover_hp_rate;
	itemSave->recover_hp = item->recover_hp;
	itemSave->recover_sp_rate = item->recover_sp_rate;
	itemSave->recover_sp = item->recover_sp;
	itemSave->occasion_field1 = item->occasion_field1;
	itemSave->ko_only = item->ko_only;
	itemSave->max_hp_points = item->max_hp_points;
	itemSave->max_sp_points = item->max_sp_points;
	itemSave->atk_points2 = item->atk_points2;
	itemSave->def_points2 = item->def_points2;
	itemSave->spi_points2 = item->spi_points2;
	itemSave->agi_points2 = item->agi_points2;
	itemSave->using_message = item->using_message;
	itemSave->skill_id = item->skill_id;
	itemSave->switch_id = item->switch_id;
	itemSave->occasion_field2 = item->occasion_field2;
	itemSave->occasion_battle = item->occasion_battle;
	//itemSave->actor_set = item->actor_set;
	//itemSave->state_set = item->state_set;
	//itemSave->attribute_set = item->attribute_set;
	itemSave->state_chance = item->state_chance;
	itemSave->reverse_state_effect = item->reverse_state_effect;
	itemSave->weapon_animation = item->weapon_animation;
	itemSave->use_skill = item->use_skill;
	itemSave->class_set = item->class_set;
	itemSave->ranged_trajectory = item->ranged_trajectory;
	itemSave->ranged_target = item->ranged_target;
	itemSave->easyrpg_using_message = item->easyrpg_using_message;
	itemSave->easyrpg_max_count = item->easyrpg_max_count;
	itemSave->quantity = item->quantity;
	itemSave->force_unique = item->force_unique;

	itemSave->number_of_upgrade = 0;

	if (idCounters.find(item->ID) == idCounters.end()) {
		idCounters[item->ID] = 1;
	}
	NextUID(IsUnique());
	idToUniqueIDMap[item->ID] = item->uniqueID + 1;
	idCounters[item->ID] = item->uniqueID + 1;
	uniqueID = item->uniqueID;
}

Game_Item::Game_Item(int i) {
	item = lcf::ReaderUtil::GetElement(lcf::Data::items, i);
	if (!item)
		return;

	itemSave = new lcf::rpg::SaveUniqueItems();

	itemSave->ID = item->ID;
	itemSave->name = item->name;
	itemSave->description = item->description;
	itemSave->type = item->type;
	itemSave->price = item->price;
	itemSave->uses = item->uses;
	itemSave->atk_points1 = item->atk_points1;
	itemSave->def_points1 = item->def_points1;
	itemSave->spi_points1 = item->spi_points1;
	itemSave->agi_points1 = item->agi_points1;
	itemSave->two_handed = item->two_handed;
	itemSave->sp_cost = item->sp_cost;
	itemSave->hit = item->hit;
	itemSave->critical_hit = item->critical_hit;
	itemSave->animation_id = item->animation_id;
	itemSave->preemptive = item->preemptive;
	itemSave->dual_attack = item->dual_attack;
	itemSave->attack_all = item->attack_all;
	itemSave->ignore_evasion = item->ignore_evasion;
	itemSave->prevent_critical = item->prevent_critical;
	itemSave->raise_evasion = item->raise_evasion;
	itemSave->half_sp_cost = item->half_sp_cost;
	itemSave->no_terrain_damage = item->no_terrain_damage;
	itemSave->cursed = item->cursed;
	itemSave->entire_party = item->entire_party;
	itemSave->recover_hp_rate = item->recover_hp_rate;
	itemSave->recover_hp = item->recover_hp;
	itemSave->recover_sp_rate = item->recover_sp_rate;
	itemSave->recover_sp = item->recover_sp;
	itemSave->occasion_field1 = item->occasion_field1;
	itemSave->ko_only = item->ko_only;
	itemSave->max_hp_points = item->max_hp_points;
	itemSave->max_sp_points = item->max_sp_points;
	itemSave->atk_points2 = item->atk_points2;
	itemSave->def_points2 = item->def_points2;
	itemSave->spi_points2 = item->spi_points2;
	itemSave->agi_points2 = item->agi_points2;
	itemSave->using_message = item->using_message;
	itemSave->skill_id = item->skill_id;
	itemSave->switch_id = item->switch_id;
	itemSave->occasion_field2 = item->occasion_field2;
	itemSave->occasion_battle = item->occasion_battle;
	itemSave->actor_set = item->actor_set;
	itemSave->state_set = item->state_set;
	itemSave->attribute_set = item->attribute_set;
	itemSave->state_chance = item->state_chance;
	itemSave->reverse_state_effect = item->reverse_state_effect;
	itemSave->weapon_animation = item->weapon_animation;
	itemSave->use_skill = item->use_skill;
	itemSave->class_set = item->class_set;
	itemSave->ranged_trajectory = item->ranged_trajectory;
	itemSave->ranged_target = item->ranged_target;
	itemSave->easyrpg_using_message = item->easyrpg_using_message;
	itemSave->easyrpg_max_count = item->easyrpg_max_count;
	
	itemSave->number_of_upgrade = 0;

	if (idCounters.find(i) == idCounters.end()) {
		idCounters[i] = 1;
	}
	NextUID(IsUnique());
	

}

void Game_Item::NextUID(bool unique) {
	int i = itemSave->ID;
	if (idCounters.find(i) == idCounters.end()) {
		idCounters[i] = 1;
	}
	if (unique) {
		uniqueID = idCounters[i]++;
	}
	else {
		uniqueID = 0;
	}
	idToUniqueIDMap[i] = uniqueID;
	itemSave->uniqueID = uniqueID;
}

//bool Game_Item::SameItem(Game_Item* item) const {
//	return itemSave->ID == item->itemSave->ID && uniqueID == item->itemSave->uniqueID;
//}
bool Game_Item::SameItem(Game_Item* item) const {
	if (!itemSave || !item || !item->itemSave)
		return false;

	return
		itemSave->ID == item->itemSave->ID &&
		itemSave->name == item->itemSave->name &&
		itemSave->description == item->itemSave->description &&
		itemSave->type == item->itemSave->type &&
		itemSave->price == item->itemSave->price &&
		itemSave->uses == item->itemSave->uses &&
		itemSave->atk_points1 == item->itemSave->atk_points1 &&
		itemSave->def_points1 == item->itemSave->def_points1 &&
		itemSave->spi_points1 == item->itemSave->spi_points1 &&
		itemSave->agi_points1 == item->itemSave->agi_points1 &&
		itemSave->two_handed == item->itemSave->two_handed &&
		itemSave->sp_cost == item->itemSave->sp_cost &&
		itemSave->hit == item->itemSave->hit &&
		itemSave->critical_hit == item->itemSave->critical_hit &&
		itemSave->animation_id == item->itemSave->animation_id &&
		itemSave->preemptive == item->itemSave->preemptive &&
		itemSave->dual_attack == item->itemSave->dual_attack &&
		itemSave->attack_all == item->itemSave->attack_all &&
		itemSave->ignore_evasion == item->itemSave->ignore_evasion &&
		itemSave->prevent_critical == item->itemSave->prevent_critical &&
		itemSave->raise_evasion == item->itemSave->raise_evasion &&
		itemSave->half_sp_cost == item->itemSave->half_sp_cost &&
		itemSave->no_terrain_damage == item->itemSave->no_terrain_damage &&
		itemSave->cursed == item->itemSave->cursed &&
		itemSave->entire_party == item->itemSave->entire_party &&
		itemSave->recover_hp_rate == item->itemSave->recover_hp_rate &&
		itemSave->recover_hp == item->itemSave->recover_hp &&
		itemSave->recover_sp_rate == item->itemSave->recover_sp_rate &&
		itemSave->recover_sp == item->itemSave->recover_sp &&
		itemSave->occasion_field1 == item->itemSave->occasion_field1 &&
		itemSave->ko_only == item->itemSave->ko_only &&
		itemSave->max_hp_points == item->itemSave->max_hp_points &&
		itemSave->max_sp_points == item->itemSave->max_sp_points &&
		itemSave->atk_points2 == item->itemSave->atk_points2 &&
		itemSave->def_points2 == item->itemSave->def_points2 &&
		itemSave->spi_points2 == item->itemSave->spi_points2 &&
		itemSave->agi_points2 == item->itemSave->agi_points2 &&
		itemSave->using_message == item->itemSave->using_message &&
		itemSave->skill_id == item->itemSave->skill_id &&
		itemSave->switch_id == item->itemSave->switch_id &&
		itemSave->occasion_field2 == item->itemSave->occasion_field2 &&
		itemSave->occasion_battle == item->itemSave->occasion_battle &&
		itemSave->state_chance == item->itemSave->state_chance &&
		itemSave->reverse_state_effect == item->itemSave->reverse_state_effect &&
		itemSave->weapon_animation == item->itemSave->weapon_animation &&
		itemSave->use_skill == item->itemSave->use_skill &&
		itemSave->ranged_trajectory == item->itemSave->ranged_trajectory &&
		itemSave->ranged_target == item->itemSave->ranged_target &&
		itemSave->easyrpg_using_message == item->itemSave->easyrpg_using_message &&
		itemSave->easyrpg_max_count == item->itemSave->easyrpg_max_count &&
		itemSave->number_of_use == item->itemSave->number_of_use &&
		itemSave->number_of_upgrade == item->itemSave->number_of_upgrade;
}


bool Game_Item::IsUnique() const {
	if (itemSave->type == lcf::rpg::Item::Type_weapon || itemSave->type == lcf::rpg::Item::Type_shield ||
		itemSave->type == lcf::rpg::Item::Type_armor || itemSave->type == lcf::rpg::Item::Type_helmet ||
		itemSave->type == lcf::rpg::Item::Type_accessory)
		return true;
	return itemSave->force_unique && itemSave->uniqueID >= 0;
}

lcf::rpg::SaveUniqueItems* Game_Item::GetItemSave() {
	return itemSave;
}

void Game_Item::SetItemSave(lcf::rpg::SaveUniqueItems* i) {
	itemSave = i;
}

std::string Game_Item::GetOriginalName() {
	auto item = lcf::ReaderUtil::GetElement(lcf::Data::items, itemSave->ID);
	return item->name.data();
}

std::string Game_Item::ToString() {
	if (!itemSave) return "";

	std::string r;
	r += std::to_string(itemSave->ID) + "\n";
	r += std::to_string(itemSave->number_of_upgrade) + "\n";
	r += itemSave->name.data();
	r += "\n";
	r += itemSave->description.data();
	r += "\n";
	r += std::to_string(itemSave->type) + "\n";
	r += std::to_string(itemSave->price) + "\n";
	r += std::to_string(itemSave->uses) + "\n";
	r += std::to_string(itemSave->atk_points1) + "\n";
	r += std::to_string(itemSave->def_points1) + "\n";
	r += std::to_string(itemSave->spi_points1) + "\n";
	r += std::to_string(itemSave->agi_points1) + "\n";
	r += (itemSave->two_handed ? "true" : "false") + std::string("\n");
	r += std::to_string(itemSave->sp_cost) + "\n";
	r += std::to_string(itemSave->hit) + "\n";
	r += std::to_string(itemSave->critical_hit) + "\n";
	r += std::to_string(itemSave->animation_id) + "\n";
	r += (itemSave->preemptive ? "true" : "false") + std::string("\n");
	r += (itemSave->dual_attack ? "true" : "false") + std::string("\n");
	r += (itemSave->attack_all ? "true" : "false") + std::string("\n");
	r += (itemSave->ignore_evasion ? "true" : "false") + std::string("\n");
	r += (itemSave->prevent_critical ? "true" : "false") + std::string("\n");
	r += (itemSave->raise_evasion ? "true" : "false") + std::string("\n");
	r += (itemSave->half_sp_cost ? "true" : "false") + std::string("\n");
	r += (itemSave->no_terrain_damage ? "true" : "false") + std::string("\n");
	r += (itemSave->cursed ? "true" : "false") + std::string("\n");
	r += (itemSave->entire_party ? "true" : "false") + std::string("\n");
	r += std::to_string(itemSave->recover_hp_rate) + "\n";
	r += std::to_string(itemSave->recover_hp) + "\n";
	r += std::to_string(itemSave->recover_sp_rate) + "\n";
	r += std::to_string(itemSave->recover_sp) + "\n";
	r += (itemSave->occasion_field1 ? "true" : "false") + std::string("\n");
	r += (itemSave->ko_only ? "true" : "false") + std::string("\n");
	r += std::to_string(itemSave->max_hp_points) + "\n";
	r += std::to_string(itemSave->max_sp_points) + "\n";
	r += std::to_string(itemSave->atk_points2) + "\n";
	r += std::to_string(itemSave->def_points2) + "\n";
	r += std::to_string(itemSave->spi_points2) + "\n";
	r += std::to_string(itemSave->agi_points2) + "\n";
	r += std::to_string(itemSave->using_message) + "\n";
	r += std::to_string(itemSave->skill_id) + "\n";
	r += std::to_string(itemSave->switch_id) + "\n";
	r += (itemSave->occasion_field2 ? "true" : "false") + std::string("\n");
	r += (itemSave->occasion_battle ? "true" : "false") + std::string("\n");
	r += std::to_string(itemSave->state_chance) + "\n";
	r += (itemSave->reverse_state_effect ? "true" : "false") + std::string("\n");
	r += std::to_string(itemSave->weapon_animation) + "\n";
	r += (itemSave->use_skill ? "true" : "false") + std::string("\n");
	r += std::to_string(itemSave->ranged_trajectory) + "\n";
	r += std::to_string(itemSave->ranged_target) + "\n";
	r += itemSave->easyrpg_using_message.data();
	r += "\n";
	r += std::to_string(itemSave->easyrpg_max_count) + "\n";
	r += std::to_string(itemSave->number_of_use) + "\n";
	r += std::to_string(itemSave->quantity) + "\n";
	r += std::to_string(itemSave->uniqueID) + "\n";

	return r;
}



// DBString setters
void Game_Item::SetName(const std::string& op, const std::string& value) {
	if (!itemSave) return;
	std::string str = itemSave->name.data();

	if (op == "=") str = value;
	else if (op == "+=") str += value;
	else if (op == "-=") {
		auto pos = str.rfind(value);
		if (pos != std::string::npos && pos + value.size() == str.size()) {
			str.erase(pos, value.size());
		}
	}

	itemSave->name = lcf::DBString(str);
}

void Game_Item::SetDescription(const std::string& op, const std::string& value) {
	if (!itemSave) return;
	std::string str = itemSave->description.data();

	if (op == "=") str = value;
	else if (op == "+=") str += value;
	else if (op == "-=") {
		auto pos = str.rfind(value);
		if (pos != std::string::npos && pos + value.size() == str.size()) {
			str.erase(pos, value.size());
		}
	}

	itemSave->description = lcf::DBString(str);
}

void Game_Item::SetEasyrpgUsingMessage(const std::string& op, const std::string& value) {
	if (!itemSave) return;
	std::string str = itemSave->easyrpg_using_message.data();

	if (op == "=") str = value;
	else if (op == "+=") str += value;
	else if (op == "-=") {
		auto pos = str.rfind(value);
		if (pos != std::string::npos && pos + value.size() == str.size()) {
			str.erase(pos, value.size());
		}
	}

	itemSave->easyrpg_using_message = lcf::DBString(str);
}

// int32_t setters
void Game_Item::SetType(const std::string& op, int value) {
	if (!itemSave) return;
	if (op == "=") itemSave->type = value;
	else if (op == "+=") itemSave->type += value;
	else if (op == "-=") itemSave->type -= value;
}

void Game_Item::SetPrice(const std::string& op, int value) {
	if (!itemSave) return;
	if (op == "=") itemSave->price = value;
	else if (op == "+=") itemSave->price += value;
	else if (op == "-=") itemSave->price -= value;
}

void Game_Item::SetUses(const std::string& op, int value) {
	if (!itemSave) return;
	if (op == "=") itemSave->uses = value;
	else if (op == "+=") itemSave->uses += value;
	else if (op == "-=") itemSave->uses -= value;
}

void Game_Item::SetAtk_points1(const std::string& op, int value) {
	if (!itemSave) return;
	if (op == "=") itemSave->atk_points1 = value;
	else if (op == "+=") itemSave->atk_points1 += value;
	else if (op == "-=") itemSave->atk_points1 -= value;
}

void Game_Item::SetDef_points1(const std::string& op, int value) {
	if (!itemSave) return;
	if (op == "=") itemSave->def_points1 = value;
	else if (op == "+=") itemSave->def_points1 += value;
	else if (op == "-=") itemSave->def_points1 -= value;
}

void Game_Item::SetSpi_points1(const std::string& op, int value) {
	if (!itemSave) return;
	if (op == "=") itemSave->spi_points1 = value;
	else if (op == "+=") itemSave->spi_points1 += value;
	else if (op == "-=") itemSave->spi_points1 -= value;
}

void Game_Item::SetAgi_points1(const std::string& op, int value) {
	if (!itemSave) return;
	if (op == "=") itemSave->agi_points1 = value;
	else if (op == "+=") itemSave->agi_points1 += value;
	else if (op == "-=") itemSave->agi_points1 -= value;
}

void Game_Item::SetSp_cost(const std::string& op, int value) {
	if (!itemSave) return;
	if (op == "=") itemSave->sp_cost = value;
	else if (op == "+=") itemSave->sp_cost += value;
	else if (op == "-=") itemSave->sp_cost -= value;
}

void Game_Item::SetHit(const std::string& op, int value) {
	if (!itemSave) return;
	if (op == "=") itemSave->hit = value;
	else if (op == "+=") itemSave->hit += value;
	else if (op == "-=") itemSave->hit -= value;
}

void Game_Item::SetCritical_hit(const std::string& op, int value) {
	if (!itemSave) return;
	if (op == "=") itemSave->critical_hit = value;
	else if (op == "+=") itemSave->critical_hit += value;
	else if (op == "-=") itemSave->critical_hit -= value;
}

void Game_Item::SetAnimation_id(const std::string& op, int value) {
	if (!itemSave) return;
	if (op == "=") itemSave->animation_id = value;
	else if (op == "+=") itemSave->animation_id += value;
	else if (op == "-=") itemSave->animation_id -= value;
}

void Game_Item::SetRecover_hp_rate(const std::string& op, int value) {
	if (!itemSave) return;
	if (op == "=") itemSave->recover_hp_rate = value;
	else if (op == "+=") itemSave->recover_hp_rate += value;
	else if (op == "-=") itemSave->recover_hp_rate -= value;
}

void Game_Item::SetRecover_hp(const std::string& op, int value) {
	if (!itemSave) return;
	if (op == "=") itemSave->recover_hp = value;
	else if (op == "+=") itemSave->recover_hp += value;
	else if (op == "-=") itemSave->recover_hp -= value;
}

void Game_Item::SetRecover_sp_rate(const std::string& op, int value) {
	if (!itemSave) return;
	if (op == "=") itemSave->recover_sp_rate = value;
	else if (op == "+=") itemSave->recover_sp_rate += value;
	else if (op == "-=") itemSave->recover_sp_rate -= value;
}

void Game_Item::SetRecover_sp(const std::string& op, int value) {
	if (!itemSave) return;
	if (op == "=") itemSave->recover_sp = value;
	else if (op == "+=") itemSave->recover_sp += value;
	else if (op == "-=") itemSave->recover_sp -= value;
}

void Game_Item::SetMax_hp_points(const std::string& op, int value) {
	if (!itemSave) return;
	if (op == "=") itemSave->max_hp_points = value;
	else if (op == "+=") itemSave->max_hp_points += value;
	else if (op == "-=") itemSave->max_hp_points -= value;
}

void Game_Item::SetMax_sp_points(const std::string& op, int value) {
	if (!itemSave) return;
	if (op == "=") itemSave->max_sp_points = value;
	else if (op == "+=") itemSave->max_sp_points += value;
	else if (op == "-=") itemSave->max_sp_points -= value;
}

void Game_Item::SetAtk_points2(const std::string& op, int value) {
	if (!itemSave) return;
	if (op == "=") itemSave->atk_points2 = value;
	else if (op == "+=") itemSave->atk_points2 += value;
	else if (op == "-=") itemSave->atk_points2 -= value;
}

void Game_Item::SetDef_points2(const std::string& op, int value) {
	if (!itemSave) return;
	if (op == "=") itemSave->def_points2 = value;
	else if (op == "+=") itemSave->def_points2 += value;
	else if (op == "-=") itemSave->def_points2 -= value;
}

void Game_Item::SetSpi_points2(const std::string& op, int value) {
	if (!itemSave) return;
	if (op == "=") itemSave->spi_points2 = value;
	else if (op == "+=") itemSave->spi_points2 += value;
	else if (op == "-=") itemSave->spi_points2 -= value;
}

void Game_Item::SetAgi_points2(const std::string& op, int value) {
	if (!itemSave) return;
	if (op == "=") itemSave->agi_points2 = value;
	else if (op == "+=") itemSave->agi_points2 += value;
	else if (op == "-=") itemSave->agi_points2 -= value;
}

void Game_Item::SetUsing_message(const std::string& op, int value) {
	if (!itemSave) return;
	if (op == "=") itemSave->using_message = value;
	else if (op == "+=") itemSave->using_message += value;
	else if (op == "-=") itemSave->using_message -= value;
}

void Game_Item::SetSkill_id(const std::string& op, int value) {
	if (!itemSave) return;
	if (op == "=") itemSave->skill_id = value;
	else if (op == "+=") itemSave->skill_id += value;
	else if (op == "-=") itemSave->skill_id -= value;
}

void Game_Item::SetSwitch_id(const std::string& op, int value) {
	if (!itemSave) return;
	if (op == "=") itemSave->switch_id = value;
	else if (op == "+=") itemSave->switch_id += value;
	else if (op == "-=") itemSave->switch_id -= value;
}

void Game_Item::SetState_chance(const std::string& op, int value) {
	if (!itemSave) return;
	if (op == "=") itemSave->state_chance = value;
	else if (op == "+=") itemSave->state_chance += value;
	else if (op == "-=") itemSave->state_chance -= value;
}

void Game_Item::SetWeapon_animation(const std::string& op, int value) {
	if (!itemSave) return;
	if (op == "=") itemSave->weapon_animation = value;
	else if (op == "+=") itemSave->weapon_animation += value;
	else if (op == "-=") itemSave->weapon_animation -= value;
}

void Game_Item::SetRanged_trajectory(const std::string& op, int value) {
	if (!itemSave) return;
	if (op == "=") itemSave->ranged_trajectory = value;
	else if (op == "+=") itemSave->ranged_trajectory += value;
	else if (op == "-=") itemSave->ranged_trajectory -= value;
}

void Game_Item::SetRanged_target(const std::string& op, int value) {
	if (!itemSave) return;
	if (op == "=") itemSave->ranged_target = value;
	else if (op == "+=") itemSave->ranged_target += value;
	else if (op == "-=") itemSave->ranged_target -= value;
}

void Game_Item::SetEasyrpg_max_count(const std::string& op, int value) {
	if (!itemSave) return;
	if (op == "=") itemSave->easyrpg_max_count = value;
	else if (op == "+=") itemSave->easyrpg_max_count += value;
	else if (op == "-=") itemSave->easyrpg_max_count -= value;
}

void Game_Item::SetNumber_of_use(const std::string& op, int value) {
	if (!itemSave) return;
	if (op == "=") itemSave->number_of_use = value;
	else if (op == "+=") itemSave->number_of_use += value;
	else if (op == "-=") itemSave->number_of_use -= value;
}

void Game_Item::SetNumber_of_upgrade(const std::string& op, int value) {
	if (!itemSave) return;
	if (op == "=") itemSave->number_of_upgrade = value;
	else if (op == "+=") itemSave->number_of_upgrade += value;
	else if (op == "-=") itemSave->number_of_upgrade -= value;
}

void Game_Item::SetQuantity(const std::string& op, int value) {
	if (!itemSave) return;
	if (op == "=") itemSave->quantity = value;
	else if (op == "+=") itemSave->quantity += value;
	else if (op == "-=") itemSave->quantity -= value;
}

void Game_Item::SetUniqueID(const std::string& op, int value) {
	if (!itemSave) return;
	if (op == "=") itemSave->uniqueID = value;
	else if (op == "+=") itemSave->uniqueID += value;
	else if (op == "-=") itemSave->uniqueID -= value;
}

// bool setters
void Game_Item::SetTwo_handed(const std::string&, bool value) { if (itemSave) itemSave->two_handed = value; }
void Game_Item::SetPreemptive(const std::string&, bool value) { if (itemSave) itemSave->preemptive = value; }
void Game_Item::SetDual_attack(const std::string&, bool value) { if (itemSave) itemSave->dual_attack = value; }
void Game_Item::SetAttack_all(const std::string&, bool value) { if (itemSave) itemSave->attack_all = value; }
void Game_Item::SetIgnore_evasion(const std::string&, bool value) { if (itemSave) itemSave->ignore_evasion = value; }
void Game_Item::SetPrevent_critical(const std::string&, bool value) { if (itemSave) itemSave->prevent_critical = value; }
void Game_Item::SetRaise_evasion(const std::string&, bool value) { if (itemSave) itemSave->raise_evasion = value; }
void Game_Item::SetHalf_sp_cost(const std::string&, bool value) { if (itemSave) itemSave->half_sp_cost = value; }
void Game_Item::SetNo_terrain_damage(const std::string&, bool value) { if (itemSave) itemSave->no_terrain_damage = value; }
void Game_Item::SetCursed(const std::string&, bool value) { if (itemSave) itemSave->cursed = value; }
void Game_Item::SetEntire_party(const std::string&, bool value) { if (itemSave) itemSave->entire_party = value; }
void Game_Item::SetOccasion_field1(const std::string&, bool value) { if (itemSave) itemSave->occasion_field1 = value; }
void Game_Item::SetKo_only(const std::string&, bool value) { if (itemSave) itemSave->ko_only = value; }
void Game_Item::SetOccasion_field2(const std::string&, bool value) { if (itemSave) itemSave->occasion_field2 = value; }
void Game_Item::SetOccasion_battle(const std::string&, bool value) { if (itemSave) itemSave->occasion_battle = value; }
void Game_Item::SetReverse_state_effect(const std::string&, bool value) { if (itemSave) itemSave->reverse_state_effect = value; }
void Game_Item::SetUse_skill(const std::string&, bool value) { if (itemSave) itemSave->use_skill = value; }
void Game_Item::SetForce_Unique(const std::string&, bool value) { if (itemSave) itemSave->force_unique = value; }
