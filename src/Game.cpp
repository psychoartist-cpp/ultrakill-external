#include "Game.h"

Game::Game(std::wstring_view procName)
{
    const auto throw_procerror = [procName](const std::string& error) {
        logging::Error(error);
        throw InvalidProcessError(procName, error.c_str());
        };

	// Look up the process
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnapshot != INVALID_HANDLE_VALUE) {
        PROCESSENTRY32 pe32;
        pe32.dwSize = sizeof(PROCESSENTRY32);
        if (Process32First(hSnapshot, &pe32)) {
            do {
                if (procName == pe32.szExeFile) {
                    this->m_pid = pe32.th32ProcessID;
                    this->m_hProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, m_pid);
                    if (this->m_hProc == NULL) {
                        throw_procerror("Failed to open process! Make sure to run the program as admin!");
                    } 
                    else {
                        logging::Success("Found process!");
                    }
                    return;
                }
            } while (Process32Next(hSnapshot, &pe32));
        }
        CloseHandle(hSnapshot);
    }
    else {
        throw_procerror("Failed to create snapshot for iterating over processes!");
    }
    if (this->m_hProc == NULL || this->m_hProc == INVALID_HANDLE_VALUE) {
        throw_procerror("Failed to find target process!");
    }
}

Game::~Game()
{
    CloseHandle(m_hProc);
}

std::expected<uintptr_t, std::string_view> Game::GetModuleBase(const std::wstring& moduleName) const
{
    std::string targetModuleStr = utilities::ConvertWstring(moduleName);
    logging::Info("Looking for module " + targetModuleStr + "...");
    HANDLE hModuleSnap = INVALID_HANDLE_VALUE;
    MODULEENTRY32 me32;

    hModuleSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, m_pid);
    if (hModuleSnap == INVALID_HANDLE_VALUE)
    {
        std::string_view error = "Failed to get snapshot for looking up modules!";
        logging::Error(std::string(error));
        return std::unexpected(error);
    }

    me32.dwSize = sizeof(MODULEENTRY32);


    // Walk the module list, check if name is there
    if (!Module32First(hModuleSnap, &me32))
    {
        std::string error = "Failed to get information about first module of process!";
        logging::Error(error);
        return std::unexpected(error);
    }
    
    do
    {
        std::string moduleNameStr = utilities::ConvertWstring(me32.szModule);

        uintptr_t moduleAddr = reinterpret_cast<uintptr_t>(me32.modBaseAddr);
        logging::Debug("Module " + moduleNameStr + ", address: " + utilities::StringifyUintptr(moduleAddr));
        if (targetModuleStr == moduleNameStr) {
            // Cast address into uintptr_t, log and return it

            logging::Success("Found target module " + moduleNameStr +  " at " + utilities::StringifyUintptr(moduleAddr) + '!');
            return reinterpret_cast<uintptr_t>(me32.modBaseAddr);
        }
    } while (Module32Next(hModuleSnap, &me32));

    CloseHandle(hModuleSnap);
    
    return std::unexpected("No module found!");
}
