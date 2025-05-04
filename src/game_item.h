#ifndef EP_GAME_ITEM_H
#define EP_GAME_ITEM_H

// Headers
#include <string>
#include <lcf/rpg/item.h>
#include <stdint.h>
#include <vector>
#include "lcf/dbbitarray.h"
#include "lcf/dbstring.h"
#include "lcf/enum_tags.h"
#include "lcf/rpg/battleranimationitemskill.h"
#include "lcf/context.h"
#include <ostream>
#include <type_traits>
#include <lcf/rpg/saveuniqueitems.h>

class Game_Item
{
private :
	static std::unordered_map<int, int> idToUniqueIDMap;  // Map pour associer chaque ID à un compteur unique
	static std::unordered_map<int, int> idCounters;       // Map des compteurs par ID

public :

	Game_Item(int id);
	Game_Item(lcf::rpg::SaveUniqueItems* item);
	//Game_Item(lcf::rpg::SaveUniqueItems item);

	void NextUID(bool unique);

	int uniqueID = 0;

	bool IsUnique() const;

	bool SameItem(Game_Item* item) const;

	//bool operator==(const Game_Item& other) const {
	//	if (IsUnique()) {
	//		return itemSave->ID == other.itemSave->ID && uniqueID == other.uniqueID;
	//	}
	//	if (other.IsUnique()) {
	//		return itemSave->ID == other.itemSave->ID && uniqueID == other.uniqueID;
	//	}
	//	return itemSave->ID == other.itemSave->ID;
	//}
	bool operator==(const Game_Item& other) const {
		if (!itemSave || !other.itemSave)
			return false;
		if (other.IsUnique()) {
			return
				itemSave->ID == other.itemSave->ID &&
				itemSave->uniqueID == other.uniqueID &&
				itemSave->name == other.itemSave->name &&
				itemSave->description == other.itemSave->description &&
				itemSave->type == other.itemSave->type &&
				itemSave->price == other.itemSave->price &&
				itemSave->uses == other.itemSave->uses &&
				itemSave->atk_points1 == other.itemSave->atk_points1 &&
				itemSave->def_points1 == other.itemSave->def_points1 &&
				itemSave->spi_points1 == other.itemSave->spi_points1 &&
				itemSave->agi_points1 == other.itemSave->agi_points1 &&
				itemSave->two_handed == other.itemSave->two_handed &&
				itemSave->sp_cost == other.itemSave->sp_cost &&
				itemSave->hit == other.itemSave->hit &&
				itemSave->critical_hit == other.itemSave->critical_hit &&
				itemSave->animation_id == other.itemSave->animation_id &&
				itemSave->preemptive == other.itemSave->preemptive &&
				itemSave->dual_attack == other.itemSave->dual_attack &&
				itemSave->attack_all == other.itemSave->attack_all &&
				itemSave->ignore_evasion == other.itemSave->ignore_evasion &&
				itemSave->prevent_critical == other.itemSave->prevent_critical &&
				itemSave->raise_evasion == other.itemSave->raise_evasion &&
				itemSave->half_sp_cost == other.itemSave->half_sp_cost &&
				itemSave->no_terrain_damage == other.itemSave->no_terrain_damage &&
				itemSave->cursed == other.itemSave->cursed &&
				itemSave->entire_party == other.itemSave->entire_party &&
				itemSave->recover_hp_rate == other.itemSave->recover_hp_rate &&
				itemSave->recover_hp == other.itemSave->recover_hp &&
				itemSave->recover_sp_rate == other.itemSave->recover_sp_rate &&
				itemSave->recover_sp == other.itemSave->recover_sp &&
				itemSave->occasion_field1 == other.itemSave->occasion_field1 &&
				itemSave->ko_only == other.itemSave->ko_only &&
				itemSave->max_hp_points == other.itemSave->max_hp_points &&
				itemSave->max_sp_points == other.itemSave->max_sp_points &&
				itemSave->atk_points2 == other.itemSave->atk_points2 &&
				itemSave->def_points2 == other.itemSave->def_points2 &&
				itemSave->spi_points2 == other.itemSave->spi_points2 &&
				itemSave->agi_points2 == other.itemSave->agi_points2 &&
				itemSave->using_message == other.itemSave->using_message &&
				itemSave->skill_id == other.itemSave->skill_id &&
				itemSave->switch_id == other.itemSave->switch_id &&
				itemSave->occasion_field2 == other.itemSave->occasion_field2 &&
				itemSave->occasion_battle == other.itemSave->occasion_battle &&
				itemSave->state_chance == other.itemSave->state_chance &&
				itemSave->reverse_state_effect == other.itemSave->reverse_state_effect &&
				itemSave->weapon_animation == other.itemSave->weapon_animation &&
				itemSave->use_skill == other.itemSave->use_skill &&
				itemSave->ranged_trajectory == other.itemSave->ranged_trajectory &&
				itemSave->ranged_target == other.itemSave->ranged_target &&
				itemSave->easyrpg_using_message == other.itemSave->easyrpg_using_message &&
				itemSave->easyrpg_max_count == other.itemSave->easyrpg_max_count &&
				itemSave->number_of_use == other.itemSave->number_of_use &&
				itemSave->number_of_upgrade == other.itemSave->number_of_upgrade;
		}
		return
			itemSave->ID == other.itemSave->ID &&
			itemSave->name == other.itemSave->name &&
			itemSave->description == other.itemSave->description &&
			itemSave->type == other.itemSave->type &&
			itemSave->price == other.itemSave->price &&
			itemSave->uses == other.itemSave->uses &&
			itemSave->atk_points1 == other.itemSave->atk_points1 &&
			itemSave->def_points1 == other.itemSave->def_points1 &&
			itemSave->spi_points1 == other.itemSave->spi_points1 &&
			itemSave->agi_points1 == other.itemSave->agi_points1 &&
			itemSave->two_handed == other.itemSave->two_handed &&
			itemSave->sp_cost == other.itemSave->sp_cost &&
			itemSave->hit == other.itemSave->hit &&
			itemSave->critical_hit == other.itemSave->critical_hit &&
			itemSave->animation_id == other.itemSave->animation_id &&
			itemSave->preemptive == other.itemSave->preemptive &&
			itemSave->dual_attack == other.itemSave->dual_attack &&
			itemSave->attack_all == other.itemSave->attack_all &&
			itemSave->ignore_evasion == other.itemSave->ignore_evasion &&
			itemSave->prevent_critical == other.itemSave->prevent_critical &&
			itemSave->raise_evasion == other.itemSave->raise_evasion &&
			itemSave->half_sp_cost == other.itemSave->half_sp_cost &&
			itemSave->no_terrain_damage == other.itemSave->no_terrain_damage &&
			itemSave->cursed == other.itemSave->cursed &&
			itemSave->entire_party == other.itemSave->entire_party &&
			itemSave->recover_hp_rate == other.itemSave->recover_hp_rate &&
			itemSave->recover_hp == other.itemSave->recover_hp &&
			itemSave->recover_sp_rate == other.itemSave->recover_sp_rate &&
			itemSave->recover_sp == other.itemSave->recover_sp &&
			itemSave->occasion_field1 == other.itemSave->occasion_field1 &&
			itemSave->ko_only == other.itemSave->ko_only &&
			itemSave->max_hp_points == other.itemSave->max_hp_points &&
			itemSave->max_sp_points == other.itemSave->max_sp_points &&
			itemSave->atk_points2 == other.itemSave->atk_points2 &&
			itemSave->def_points2 == other.itemSave->def_points2 &&
			itemSave->spi_points2 == other.itemSave->spi_points2 &&
			itemSave->agi_points2 == other.itemSave->agi_points2 &&
			itemSave->using_message == other.itemSave->using_message &&
			itemSave->skill_id == other.itemSave->skill_id &&
			itemSave->switch_id == other.itemSave->switch_id &&
			itemSave->occasion_field2 == other.itemSave->occasion_field2 &&
			itemSave->occasion_battle == other.itemSave->occasion_battle &&
			itemSave->state_chance == other.itemSave->state_chance &&
			itemSave->reverse_state_effect == other.itemSave->reverse_state_effect &&
			itemSave->weapon_animation == other.itemSave->weapon_animation &&
			itemSave->use_skill == other.itemSave->use_skill &&
			itemSave->ranged_trajectory == other.itemSave->ranged_trajectory &&
			itemSave->ranged_target == other.itemSave->ranged_target &&
			itemSave->easyrpg_using_message == other.itemSave->easyrpg_using_message &&
			itemSave->easyrpg_max_count == other.itemSave->easyrpg_max_count &&
			itemSave->number_of_use == other.itemSave->number_of_use &&
			itemSave->number_of_upgrade == other.itemSave->number_of_upgrade;
	}

	lcf::rpg::SaveUniqueItems* GetItemSave();
	void SetItemSave(lcf::rpg::SaveUniqueItems*);
	std::string ToString();
	std::string GetOriginalName();

	// DBString
	void SetName(const std::string& op, const std::string& value);
	void SetDescription(const std::string& op, const std::string& value);
	void SetEasyrpgUsingMessage(const std::string& op, const std::string& value);

	// int32_t
	void SetType(const std::string& op, int value);
	void SetPrice(const std::string& op, int value);
	void SetUses(const std::string& op, int value);
	void SetAtk_points1(const std::string& op, int value);
	void SetDef_points1(const std::string& op, int value);
	void SetSpi_points1(const std::string& op, int value);
	void SetAgi_points1(const std::string& op, int value);
	void SetSp_cost(const std::string& op, int value);
	void SetHit(const std::string& op, int value);
	void SetCritical_hit(const std::string& op, int value);
	void SetAnimation_id(const std::string& op, int value);
	void SetRecover_hp_rate(const std::string& op, int value);
	void SetRecover_hp(const std::string& op, int value);
	void SetRecover_sp_rate(const std::string& op, int value);
	void SetRecover_sp(const std::string& op, int value);
	void SetMax_hp_points(const std::string& op, int value);
	void SetMax_sp_points(const std::string& op, int value);
	void SetAtk_points2(const std::string& op, int value);
	void SetDef_points2(const std::string& op, int value);
	void SetSpi_points2(const std::string& op, int value);
	void SetAgi_points2(const std::string& op, int value);
	void SetUsing_message(const std::string& op, int value);
	void SetSkill_id(const std::string& op, int value);
	void SetSwitch_id(const std::string& op, int value);
	void SetState_chance(const std::string& op, int value);
	void SetWeapon_animation(const std::string& op, int value);
	void SetRanged_trajectory(const std::string& op, int value);
	void SetRanged_target(const std::string& op, int value);
	void SetEasyrpg_max_count(const std::string& op, int value);
	void SetNumber_of_use(const std::string& op, int value);
	void SetQuantity(const std::string& op, int value);
	void SetUniqueID(const std::string& op, int value);
	void SetNumber_of_upgrade(const std::string& op, int value);

	// bool
	void SetTwo_handed(const std::string& op, bool value);
	void SetPreemptive(const std::string& op, bool value);
	void SetDual_attack(const std::string& op, bool value);
	void SetAttack_all(const std::string& op, bool value);
	void SetIgnore_evasion(const std::string& op, bool value);
	void SetPrevent_critical(const std::string& op, bool value);
	void SetRaise_evasion(const std::string& op, bool value);
	void SetHalf_sp_cost(const std::string& op, bool value);
	void SetNo_terrain_damage(const std::string& op, bool value);
	void SetCursed(const std::string& op, bool value);
	void SetEntire_party(const std::string& op, bool value);
	void SetOccasion_field1(const std::string& op, bool value);
	void SetKo_only(const std::string& op, bool value);
	void SetOccasion_field2(const std::string& op, bool value);
	void SetOccasion_battle(const std::string& op, bool value);
	void SetReverse_state_effect(const std::string& op, bool value);
	void SetUse_skill(const std::string& op, bool value);
	void SetForce_Unique(const std::string& op, bool value);

private:

	lcf::rpg::Item* item;
	lcf::rpg::SaveUniqueItems* itemSave;

};

#endif
