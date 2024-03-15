// Copyright (c) 2024 Dylan Figueredo
// Distributed under the MIT license. See the LICENSE file in the project root for more information
#pragma once
#include "CommonHeaders.h"

namespace elysium::id {

	using id_type = uint32_t;

	namespace internal {
		constexpr uint32_t generation_bits{ 10 };
		constexpr uint32_t index_bits{ sizeof(id_type) * 8 - generation_bits };
		constexpr id_type index_mask{ (id_type{1} << index_bits) - 1 };
		constexpr id_type generation_mask{ (id_type{1} << generation_bits) - 1 };
	}
	constexpr id_type invalid_id{ id_type(-1) };
	constexpr uint32_t min_deleted_elements{ 1024 };

	using generation_type = std::conditional_t<internal::generation_bits <= 16, std::conditional_t<internal::generation_bits <= 8, uint8_t, uint16_t>, uint32_t>;

	static_assert(sizeof(generation_type) * 8 >= internal::generation_bits);
	static_assert((sizeof(id_type) - sizeof(generation_type)) > 0);

	constexpr bool
		is_valid(id_type id)
	{
		return id != invalid_id;
	}

	constexpr id_type
		index(id_type id)
	{
		id_type index{ id & internal::index_mask };
		assert(index != internal::index_mask);
		return index;
	}

	constexpr id_type
		generation(id_type id) {
		return (id >> internal::index_bits) & internal::generation_mask;
	}

	constexpr id_type
		new_generation(id_type id) {
		const id_type generation{ id::generation(id) + 1 };
		assert(generation < ((uint64_t)1 << internal::generation_bits) - 1);
		return index(id) | (generation << internal::index_bits);
	}

#if _DEBUG
	namespace internal {
		struct id_base
		{
			constexpr explicit id_base(id_type id) : _id{ id } {}
			constexpr operator id_type() const { return _id; }

		private:
			id_type _id;

		};
	}


#define DEFINE_TYPED_ID(name)										\
	struct name final : id::internal::id_base						\
	{																\
		constexpr explicit name(id::id_type id) : id_base{id} {}	\
		constexpr name() : id_base{ id::invalid_id } {}				\
	};
#else
#define DEFINE_TYPE_ID(name) using name = id::id_type;
#endif
}