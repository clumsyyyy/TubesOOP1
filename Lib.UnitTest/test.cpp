#include "pch.h"
#include <string>
#include <vector>
#include "../Lib/core/all_headers.hpp"


// "AS IT SHOULD BE" TESTING 

TEST(CRAFTING, EMPTY_SLOT) {
	EXPECT_ANY_THROW(Lib::CraftingHandler());
}

TEST(CRAFTING, BIRCH_PLANK) {
	Lib::GiveHandler("BIRCH_LOG", 1);
	std::vector<std::string> sd = { "C0" };
	Lib::MoveHandler("I0", 1, sd);
	EXPECT_NO_THROW(Lib::CraftingHandler());
	std::string slot = "I0";
	Lib::DiscardHandler(stoi(slot.substr(1, slot.length() - 1)), 4);
}

TEST(CRAFTING, DIAMOND_AXE) {
	Lib::GiveHandler("DIAMOND", 3);
	Lib::GiveHandler("STICK", 2);
	std::vector<std::string> sd = { "C0", "C1", "C3"};
	Lib::MoveHandler("I0", 3, sd);
	sd = { "C4", "C7" };
	Lib::MoveHandler("I1", 2, sd);
	EXPECT_NO_THROW(Lib::CraftingHandler());
	std::string slot = "I0";
	Lib::DiscardHandler(stoi(slot.substr(1, slot.length() - 1)), 1);
}

TEST(CRAFTING, DIAMOND_PICKAXE) {
	Lib::GiveHandler("DIAMOND", 3);
	Lib::GiveHandler("STICK", 2);
	std::vector<std::string> sd = { "C0", "C1", "C2" };
	Lib::MoveHandler("I0", 3, sd);
	sd = { "C4", "C7" };
	Lib::MoveHandler("I1", 2, sd);
	EXPECT_NO_THROW(Lib::CraftingHandler());
	std::string slot = "I0";
	Lib::DiscardHandler(stoi(slot.substr(1, slot.length() - 1)), 1);
}

TEST(CRAFTING, DIAMOND_SWORD) {
	Lib::GiveHandler("DIAMOND", 2);
	Lib::GiveHandler("STICK", 1);
	std::vector<std::string> sd = { "C1", "C4" };
	Lib::MoveHandler("I0", 2, sd);
	sd = {"C7"};
	Lib::MoveHandler("I1", 1, sd);
	EXPECT_NO_THROW(Lib::CraftingHandler());
	std::string slot = "I0";
	Lib::DiscardHandler(stoi(slot.substr(1, slot.length() - 1)), 1);
}

TEST(CRAFTING, IRON_AXE) {
	Lib::GiveHandler("IRON_INGOT", 3);
	Lib::GiveHandler("STICK", 2);
	std::vector<std::string> sd = { "C0", "C1", "C3" };
	Lib::MoveHandler("I0", 3, sd);
	sd = { "C4", "C7" };
	Lib::MoveHandler("I1", 2, sd);
	EXPECT_NO_THROW(Lib::CraftingHandler());
	std::string slot = "I0";
	Lib::DiscardHandler(stoi(slot.substr(1, slot.length() - 1)), 1);
}

TEST(CRAFTING, IRON_INGOT) {
	Lib::GiveHandler("IRON_NUGGET", 9);
	std::vector<std::string> sd = { "C0", "C1", "C2", "C3", "C4", "C5", "C6", "C7", "C8" };
	Lib::MoveHandler("I0", 9, sd);
	EXPECT_NO_THROW(Lib::CraftingHandler());
	std::string slot = "I0";
	Lib::DiscardHandler(stoi(slot.substr(1, slot.length() - 1)), 1);
}

TEST(CRAFTING, IRON_NUGGET) {
	Lib::GiveHandler("IRON_INGOT", 1);
	std::vector<std::string> sd = { "C0" };
	Lib::MoveHandler("I0", 1, sd);
	EXPECT_NO_THROW(Lib::CraftingHandler());
	std::string slot = "I0";
	Lib::DiscardHandler(stoi(slot.substr(1, slot.length() - 1)), 9);
}

TEST(CRAFTING, IRON_PICKAXE) {
	Lib::GiveHandler("IRON_INGOT", 3);
	Lib::GiveHandler("STICK", 2);
	std::vector<std::string> sd = { "C0", "C1", "C2" };
	Lib::MoveHandler("I0", 3, sd);
	sd = { "C4", "C7" };
	Lib::MoveHandler("I1", 2, sd);
	EXPECT_NO_THROW(Lib::CraftingHandler());
	std::string slot = "I0";
	Lib::DiscardHandler(stoi(slot.substr(1, slot.length() - 1)), 1);
}

TEST(CRAFTING, IRON_SWORD) {
	Lib::GiveHandler("IRON_INGOT", 2);
	Lib::GiveHandler("STICK", 1);
	std::vector<std::string> sd = { "C1", "C4" };
	Lib::MoveHandler("I0", 2, sd);
	sd = { "C7" };
	Lib::MoveHandler("I1", 1, sd);
	EXPECT_NO_THROW(Lib::CraftingHandler());
	std::string slot = "I0";
	Lib::DiscardHandler(stoi(slot.substr(1, slot.length() - 1)), 1);
}

TEST(CRAFTING, OAK_PLANK) {
	Lib::GiveHandler("OAK_LOG", 1);
	std::vector<std::string> sd = { "C0" };
	Lib::MoveHandler("I0", 1, sd);
	EXPECT_NO_THROW(Lib::CraftingHandler());
	std::string slot = "I0";
	Lib::DiscardHandler(stoi(slot.substr(1, slot.length() - 1)), 4);
}

TEST(CRAFTING, SPRUCE_PLANK) {
	Lib::GiveHandler("SPRUCE_LOG", 1);
	std::vector<std::string> sd = { "C0" };
	Lib::MoveHandler("I0", 1, sd);
	EXPECT_NO_THROW(Lib::CraftingHandler());
	std::string slot = "I0";
	Lib::DiscardHandler(stoi(slot.substr(1, slot.length() - 1)), 4);
}

TEST(CRAFTING, STICK) {
	Lib::GiveHandler("OAK_PLANK", 2);
	std::vector<std::string> sd = { "C0", "C3"};
	Lib::MoveHandler("I0", 2, sd);
	EXPECT_NO_THROW(Lib::CraftingHandler());
	std::string slot = "I0";
	Lib::DiscardHandler(stoi(slot.substr(1, slot.length() - 1)), 4);
}

TEST(CRAFTING, STONE_AXE) {
	Lib::GiveHandler("COBBLESTONE", 3);
	Lib::GiveHandler("STICK", 2);
	std::vector<std::string> sd = { "C0", "C1", "C3" };
	Lib::MoveHandler("I0", 3, sd);
	sd = { "C4", "C7" };
	Lib::MoveHandler("I1", 2, sd);
	EXPECT_NO_THROW(Lib::CraftingHandler());
	std::string slot = "I0";
	Lib::DiscardHandler(stoi(slot.substr(1, slot.length() - 1)), 1);
}

TEST(CRAFTING, STONE_PICKAXE) {
	Lib::GiveHandler("COBBLESTONE", 3);
	Lib::GiveHandler("STICK", 2);
	std::vector<std::string> sd = { "C0", "C1", "C2" };
	Lib::MoveHandler("I0", 3, sd);
	sd = { "C4", "C7" };
	Lib::MoveHandler("I1", 2, sd);
	EXPECT_NO_THROW(Lib::CraftingHandler());
	std::string slot = "I0";
	Lib::DiscardHandler(stoi(slot.substr(1, slot.length() - 1)), 1);
}

TEST(CRAFTING, STONE_SWORD) {
	Lib::GiveHandler("COBBLESTONE", 2);
	Lib::GiveHandler("STICK", 1);
	std::vector<std::string> sd = { "C1", "C4" };
	Lib::MoveHandler("I0", 2, sd);
	sd = { "C7" };
	Lib::MoveHandler("I1", 1, sd);
	EXPECT_NO_THROW(Lib::CraftingHandler());
	std::string slot = "I0";
	Lib::DiscardHandler(stoi(slot.substr(1, slot.length() - 1)), 1);
}

TEST(CRAFTING, WOODEN_AXE) {
	Lib::GiveHandler("OAK_PLANK", 3);
	Lib::GiveHandler("STICK", 2);
	std::vector<std::string> sd = { "C0", "C1", "C2" };
	Lib::MoveHandler("I0", 3, sd);
	sd = { "C4", "C7" };
	Lib::MoveHandler("I1", 2, sd);
	EXPECT_NO_THROW(Lib::CraftingHandler());
	std::string slot = "I0";
	Lib::DiscardHandler(stoi(slot.substr(1, slot.length() - 1)), 1);
}

TEST(CRAFTING, WOODEN_PICKAXE) {
	Lib::GiveHandler("OAK_PLANK", 2);
	Lib::GiveHandler("STICK", 1);
	std::vector<std::string> sd = { "C1", "C4" };
	Lib::MoveHandler("I0", 2, sd);
	sd = { "C7" };
	Lib::MoveHandler("I1", 1, sd);
	EXPECT_NO_THROW(Lib::CraftingHandler());
	std::string slot = "I0";
	Lib::DiscardHandler(stoi(slot.substr(1, slot.length() - 1)), 1);
}

TEST(CRAFTING, WOODEN_SWORD) {
	Lib::GiveHandler("OAK_PLANK", 2);
	Lib::GiveHandler("STICK", 1);
	std::vector<std::string> sd = { "C1", "C4" };
	Lib::MoveHandler("I0", 2, sd);
	sd = { "C7" };
	Lib::MoveHandler("I1", 1, sd);
	EXPECT_NO_THROW(Lib::CraftingHandler());
	std::string slot = "I0";
	Lib::DiscardHandler(stoi(slot.substr(1, slot.length() - 1)), 1);
}