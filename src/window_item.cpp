/*
 * This file is part of EasyRPG Player.
 *
 * EasyRPG Player is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * EasyRPG Player is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with EasyRPG Player. If not, see <http://www.gnu.org/licenses/>.
 */

// Headers
#include <iomanip>
#include <sstream>
#include "window_item.h"
#include "game_party.h"
#include "bitmap.h"
#include "font.h"
#include <lcf/reader_util.h>
#include "game_battle.h"
#include "output.h"
#include "game_strings.h"

Window_Item::Window_Item(int ix, int iy, int iwidth, int iheight, int equipped_varID) :
	Window_Selectable(ix, iy, iwidth, iheight) {
	column_max = 2;

	equipped_varValue = "";
	if (equipped_varID > 0) {
		equipped_varValue = Main_Data::game_strings->Get(equipped_varID).data();
	}
}

const lcf::rpg::Item* Window_Item::GetItem() const {
	if (index < 0) {
		return nullptr;
	}

	return lcf::ReaderUtil::GetElement(lcf::Data::items, data[index]);
}

Game_Item* Window_Item::GetItemU() {
	if (index < 0 || index >= items.size()) {
		return nullptr;
	}

	return items[index];
}

bool Window_Item::CheckInclude(int item_id) {
	 if (items.size() == 0 && item_id == 0) {
		return true;
	}
	else {
		return (item_id > 0);
	}
}

bool Window_Item::CheckInclude(Game_Item* item) {
	if (items.size() == 0 && !item) {
		return true;
	}
	else {
		return item;
	}
}


bool Window_Item::CheckEnableU(Game_Item* item) {
	if (!item) {
		return false;
	}
	if (item->GetItemSave()->type == lcf::rpg::Item::Type_medicine
		&& (!Game_Battle::IsBattleRunning() || !item->GetItemSave()->occasion_field1)) {
		return true;
	}
	return Main_Data::game_party->IsItemUsable(item->GetItemSave()->ID, actor);
}

bool Window_Item::CheckEnable(int item_id) {
	auto* item = lcf::ReaderUtil::GetElement(lcf::Data::items, item_id);
	if (!item) {
		return false;
	}
	if (item->type == lcf::rpg::Item::Type_medicine
			&& (!Game_Battle::IsBattleRunning() || !item->occasion_field1)) {
		return true;
	}
	return Main_Data::game_party->IsItemUsable(item_id, actor);
}

void Window_Item::Refresh() {
	std::vector<int> party_items;

	data.clear();

	items.clear();
	for (auto item : Main_Data::game_party->items) {
		if (item->GetItemSave()->quantity > 0) {
			if (this->CheckInclude(item)) {
				items.push_back(item);
			}
		}
	}
	if (equipped_varValue != "")
		for (auto actor : Main_Data::game_party->GetActors()) {
			for (int i = 0;i < actor->GetWholeEquipmentU().size();i++) {
				auto item = actor->GetWholeEquipmentU()[i];
				if (item.ID != 0) {
					Game_Item* g_i = new Game_Item(0);
					g_i->Link(item, actor->GetId(), i);
					g_i->SetEquipped(true);
					items.push_back(g_i);
				}
			}
		}

	if (false) {
		Main_Data::game_party->GetItems(party_items);

		for (size_t i = 0; i < party_items.size(); ++i) {
			if (this->CheckInclude(party_items[i])) {
				data.push_back(party_items[i]);
			}
		}

		if (Game_Battle::IsBattleRunning()) {
			// Include equipped accessories that invoke skills in sorted order.
			if (actor) {
				for (int i = 1; i <= 5; ++i) {
					const lcf::rpg::Item* item = actor->GetEquipment(i);
					if (item && item->use_skill && item->skill_id > 0) {
						auto iter = std::lower_bound(data.begin(), data.end(), item->ID);
						if (iter == data.end() || *iter != item->ID) {
							data.insert(iter, item->ID);
						}
					}
				}
			}
		}
	}

	if (CheckInclude(0)) {
		//data.push_back(0);
		items.push_back(nullptr);
	}

	item_max = items.size();

	CreateContents();

	SetIndex(index);

	contents->Clear();

	for (int i = 0; i < item_max; ++i) {
		DrawItem(i);
	}
}

void Window_Item::DrawItem(int index) {
	Rect rect = GetItemRect(index);
	contents->ClearRect(rect);

	auto item = items[index];
	if (!item)
		return;

	int item_id = item->GetItemSave()->ID;

	if (item_id > 0) {
		int number = Main_Data::game_party->GetItemCount(item);

		bool enabled = CheckEnableU(item);
		DrawItemName(items[index]->GetItemSave(), rect.x, rect.y, enabled);

		Font::SystemColor color = enabled ? Font::ColorDefault : Font::ColorDisabled;
		if (item->IsEquipped()) {
			contents->TextDraw(rect.x + rect.width - 24, rect.y, color, equipped_varValue);
		} else
			contents->TextDraw(rect.x + rect.width - 24, rect.y, color, fmt::format("{}{:3d}", lcf::rpg::Terms::TermOrDefault(lcf::Data::terms.easyrpg_item_number_separator, ":"), number));
	}
}

void Window_Item::UpdateHelp() {
	help_window->SetText(GetItemU() == nullptr ? "" : ToString(GetItemU()->GetItemSave()->description));
}

void Window_Item::SetActor(Game_Actor * actor) {
	this->actor = actor;
}
