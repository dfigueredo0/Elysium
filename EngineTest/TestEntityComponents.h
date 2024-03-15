// Copyright (c) 2024 Dylan Figueredo
// Distributed under the MIT license. See the LICENSE file in the project root for more information
#pragma once
#include "Test.h"
#include "..\Engine\Components\Entity.h"
#include "..\Engine\Components\Transform.h"

#include <iostream>
#include <ctime>

using namespace elysium;

class engine_test : public test {
public:
	bool init() override {
		srand((uint32_t)time(nullptr));
		return true;
	}

	void run() override { 
		do
		{
			for (uint32_t i{ 0 }; i < 10000; i++) {
				create_random();
				remove_random();
				_num_entities = (uint32_t)_entities.size();
			}
			printr();
		} while (getchar() != 'e');
	}

	void shutdown() override {  }

private:
	utl::vector<game_entity::entity> _entities;

	void create_random() {
		uint32_t count = rand() % 20;
		if (_entities.empty())
			count = 1000;
		transform::init_info transform_info{};
		game_entity::entity_info entity_info{ &transform_info };
		
		while (count > 0) {
			++_added;
			game_entity::entity entity{ game_entity::create_game_entity(entity_info) };
			assert(entity.is_valid() && id::is_valid(entity.get_id()));
			_entities.push_back(entity);
			assert(game_entity::is_alive(entity));
			--count;
		}
	}

	void remove_random() {
		uint32_t count1 = rand() % 20;
		if (_entities.size() < 1000)
			return;
		while (count1 > 0)
		{
			uint32_t index{ (uint32_t)rand() % (uint32_t)_entities.size() };
			game_entity::entity entity{_entities[index]};
			assert(entity.is_valid() && id::is_valid(entity.get_id()));
			if (entity.is_valid())
			{
				game_entity::destroy_game_entity(entity);
				_entities.erase(_entities.begin() + index);
				assert(!game_entity::is_alive(entity));
				++_removed;
			}
			
			--count1;
		}
	}

	void printr() {
		std::cout << "Entities Created: " << _added << "\n";
		std::cout << "Entities Deleted: " << _added << "\n";
	}

	uint32_t _added{ 0 };
	uint32_t _removed{ 0 };
	uint32_t _num_entities{ 0 };
};
