// Copyright (c) 2024 Dylan Figueredo
// Distributed under the MIT license. See the LICENSE file in the project root for more information
#pragma comment(lib, "engine.lib")

#define TEST_ENITTY_COMPONENTS 1

#if TEST_ENITTY_COMPONENTS
#include "TestEntityComponents.h"
#else
#error One of the tests needs to be enabled
#endif

int main() {
#if _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
	engine_test test{};

	if (test.init()) {
		test.run();
	}

	test.shutdown();
}