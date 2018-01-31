#include "Memory.hpp"
#include <iostream>

int main() {
    SetConsoleTitle("Memory Class Test");
    std::string TARGET_PROCESS_NAME = "League of Legends.exe";
    
    //////////////////////////////////////////////////////////////////////////////////
    /* Note: These pointers/offsets are probably outdated by the time you read this */
    
    int GAME_VERSION_MODULE_OFFSET = 0x2A1D738;
    
    int PLAYERS_MODULE_OFFSET = 0x1DAAED4;
        int HEALTH_OFFSET = 0x124;
        int MANA_OFFSET = 0x190;
        
    //////////////////////////////////////////////////////////////////////////////////
    
    Memory Memory;
    Memory.GetDebugPrivileges();
    const char* TARGET_PROCESS_NAME2 = TARGET_PROCESS_NAME.c_str();
    DWORD processId = Memory.GetProcessId(TARGET_PROCESS_NAME2);
    HANDLE processHandle = OpenProcess(PROCESS_ALL_ACCESS, false, processId);
    
    long baseAddress = Memory.GetModuleBase(processHandle, TARGET_PROCESS_NAME);
    std::cout << "Base address for module \"" << TARGET_PROCESS_NAME << "\" is " << baseAddress << " (in dec)..." << std::endl;
    
    long playersAddress =     baseAddress + PLAYERS_MODULE_OFFSET;
    long gameVersionAddress = baseAddress + GAME_VERSION_MODULE_OFFSET;
    
    int ptrOffset[] = {0x0}; //0x0 offset is for player one. 0x4 would be player 2 etc
    long playerOneAddress = Memory.ReadPointerInt(processHandle, playersAddress, ptrOffset, 1);
    
    float playerOneHealth = Memory.ReadFloat(processHandle, playerOneAddress + HEALTH_OFFSET);
    float playerOneMana =   Memory.ReadFloat(processHandle, playerOneAddress + MANA_OFFSET);
    
    std::string gameVersion = Memory.ReadText(processHandle, gameVersionAddress);
    
    std::cout << "Game version: " << gameVersion << std::endl;
    std::cout << "Player one has " << playerOneHealth << " health!" << std::endl;
    std::cout << "Player one has " << playerOneMana << " mana!" << std::endl;
    
    std::cin.get();
    return 0;
}
