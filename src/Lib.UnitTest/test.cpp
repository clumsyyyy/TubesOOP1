#include "pch.h"
#include <string>
#include <vector>
#include "../Lib/core/all_headers.hpp"


// "AS IT SHOULD BE" TESTING 

TEST(CRAFTING, EMPTY_SLOT) {
	EXPECT_NO_THROW(Lib::CraftingHandler());
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

// COMMAND TEST

TEST(RIGHTCOMMAND, SHOW) {
	cout << Lib::gm.crftab;
	cout << Lib::gm.inv;
}

TEST(RIGHTCOMMAND, GIVE) {
	Lib::GiveHandler("OAK_PLANK", 2);
	Lib::GiveHandler("STICK", 1);
}

TEST(RIGHTCOMMAND, MOVE) {
	std::vector<std::string> sd = { "C1", "C4" };
	Lib::MoveHandler("I0", 2, sd);
	sd = { "C7" };
	Lib::MoveHandler("I1", 1, sd);
}

TEST(RIGHTCOMMAND, CRAFT) {
	Lib::CraftingHandler();
}

TEST(RIGHTCOMMAND, DISCARD) {
	EXPECT_NO_THROW(Lib::DiscardHandler(0, 1));
}

TEST(RIGHTCOMMAND, EXPORT) {
	Lib::ExportHandler("test.txt");
}

// BERANTEM TESTING

TEST(WRONGCOMMAND, DISCARD_EMPTY) {
	std::string slot = "I0";
	EXPECT_NO_THROW(Lib::DiscardHandler(stoi(slot.substr(1, slot.length() - 1)), 10000));
}

TEST(WRONGCOMMAND, DISCARD_MORE_THAN_AVAILABLE) {
	Lib::GiveHandler("DIAMOND", 6);
	std::string slot = "I0";
	EXPECT_NO_THROW(Lib::DiscardHandler(stoi(slot.substr(1, slot.length() - 1)), 10000));
	Lib::DiscardHandler(stoi(slot.substr(1, slot.length() - 1)), 6);
}

TEST(WRONGCOMMAND, GIVE_MORE_THAN_AVAILABLE) {
	EXPECT_NO_THROW(Lib::GiveHandler("STICK", 27 * 64 + 1)); cout << endl;
}

TEST(WRONGCOMMAND, MOVE_ALLSTR) {
	std::vector<std::string> sd = { "A", "B", "C", "D", "E"};
	EXPECT_ANY_THROW(Lib::MoveHandler("C0", 5, sd));
}

TEST(WRONGCOMMAND, USE_EMPTY_INV) {
	EXPECT_NO_THROW(Lib::UseHandler("I0"));
}

TEST(WRONGCOMMAND, USE_NONEXISTENT) {
	EXPECT_NO_THROW(Lib::UseHandler("CRINGE"));
}

TEST(WRONGCOMMAND, USE_CRAFTINGTABLE) {
	Lib::GiveHandler("DIAMOND_SWORD", 1);
	std::vector<std::string> sd = { "C0"};
	Lib::MoveHandler("I0", 1, sd);
	EXPECT_NO_THROW(Lib::UseHandler("C0"));
	sd = { "I0" };
	Lib::MoveHandler("C0", 1, sd);
	Lib::DiscardHandler(0, 2);
}