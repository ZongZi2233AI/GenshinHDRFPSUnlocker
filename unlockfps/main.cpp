/*
* Genshin Impact FPS Unlocker with HDR Support v10270 Release
 * 
 * MIT License
 * 
 * Copyright (c) 2025 ZongZi2333
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 * 
 * Open Source Credits:
 * - Original FPS unlocker concept: https://github.com/xiaonian233/genshin-fps-unlock
 * - Shellcode and memory manipulation: Credit to winTEuser
 * - Contributors: xiaonian233, 34736384
 */

#define KEY_TOGGLE VK_END
#define KEY_INCREASE VK_UP
#define KEY_INCREASE_SMALL VK_RIGHT
#define KEY_DECREASE VK_DOWN
#define KEY_DECREASE_SMALL VK_LEFT
#define FPS_TARGET 120

#include <Windows.h>
#include <TlHelp32.h>
#include <vector>
#include <string>
#include <thread>
#include <Psapi.h>
#include <dxgi1_6.h>
#include <algorithm>
#include <imm.h>
#include "inireader.h"
#include "localization.h"

#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "imm32.lib")

std::string GamePath{};
int FpsValue = FPS_TARGET;

// 游戏版本类型
enum class GameVersion
{
    UNKNOWN = 0,
    YUANSHEN = 1,      // 原神（中文版）
    GENSHIN_IMPACT = 2  // Genshin Impact（国际版）
};

DWORD StartPriority = 0;
const std::vector<DWORD> PrioityClass = {
   REALTIME_PRIORITY_CLASS,
   HIGH_PRIORITY_CLASS,
   ABOVE_NORMAL_PRIORITY_CLASS,
   NORMAL_PRIORITY_CLASS,
   BELOW_NORMAL_PRIORITY_CLASS,
   IDLE_PRIORITY_CLASS
};
//credit by winTEuser
const BYTE _shellcode_genshin_Const[] =
{
    0x00, 0x00, 0x00, 0x00,                         //uint32_t unlocker_pid              _shellcode_genshin[0]
    0x00, 0xC0, 0x9C, 0x66,                         //uint32_t shellcode_timestamp       _shellcode_genshin[4]  //2024-07-21 16:00:00
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //uint64_t unlocker_FpsValue_addr    _shellcode_genshin[8]
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //uint64_t API_OpenProcess           _shellcode_genshin[16]
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //uint64_t API_ReadProcessmem        _shellcode_genshin[24]
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //uint64_t API_Sleep                 _shellcode_genshin[32]
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //uint64_t API_MessageBoxA           _shellcode_genshin[40]
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //uint64_t API_CloseHandle           _shellcode_genshin[48]
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //FREE                               _shellcode_genshin[56]
    //int3
    0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC,
    0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC,
    //int3
    0x48, 0x83, 0xEC, 0x38,                  //sub rsp,0x38                              _shellcode_genshin[80] _sync_thread
    0x8B, 0x05, 0xA6, 0xFF, 0xFF, 0xFF,      //mov eax,dword[unlocker_pid]
    0x85, 0xC0,                              //test eax, eax
    0x74, 0x5C,                              //jz return
    0x41, 0x89, 0xC0,                        //mov r8d, eax
    0x33, 0xD2,                              //xor edx, edx
    0xB9, 0xFF, 0xFF, 0x1F, 0x00,            //mov ecx,1FFFFF
    0xFF, 0x15, 0xA2, 0xFF, 0xFF, 0xFF,      //call [API_OpenProcess]
    0x85, 0xC0,                              //test eax, eax
    0x74, 0x48,                              //jz return
    0x89, 0xC6,                              //mov esi, eax
    0x48, 0x8B, 0x3D, 0x8D, 0xFF, 0xFF, 0xFF,//mov rdi,qword[unlocker_FpsValue_addr]
    0x0F, 0x1F, 0x44, 0x00, 0x00,            //nop
    0x89, 0xF1,                              //mov ecx, esi          //Read_tar_fps
    0x48, 0x89, 0xFA,                        //mov rdx, rdi
    0x4C, 0x8D, 0x05, 0x08, 0x01, 0x00, 0x00,//lea r8, qword:[Readmem_buffer]
    0x41, 0xB9, 0x04, 0x00, 0x00, 0x00,      //mov r9d, 4
    0x31, 0xC0,                              //xor eax, eax
    0x48, 0x89, 0x44, 0x24, 0x20,            //mov qword ptr ss:[rsp+20],rax
    0xFF, 0x15, 0x79, 0xFF, 0xFF, 0xFF,      //call [API_ReadProcessmem]
    0x85, 0xC0,                              //test eax, eax
    0x74, 0x12,                              //jz Show msg and closehandle
    0xB9, 0xF4, 0x01, 0x00, 0x00,            //mov ecx,0x1F4     (500ms)
    0xFF, 0x15, 0x72, 0xFF, 0xFF, 0xFF,      //call [API_Sleep]
    0xE8, 0x5D, 0x00, 0x00, 0x00,            //call Sync_auto
    0xEB, 0xCB,                              //jmp Read_tar_fps
    0xE8, 0x76, 0x00, 0x00, 0x00,            //call Show Errormsg and CloseHandle
    0x48, 0x83, 0xC4, 0x38,                  //add rsp,0x38
    0xC3,                                    //return
    //int3
    0xCC,
    0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC,
    0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC,
    //int3
    0x89, 0x0D, 0xBA, 0x00, 0x00, 0x00,     //mov [Game_Current_set], ecx           //hook_fps_set      _shellcode_genshin[0xD0]
    0x31, 0xC0,                             //xor eax, eax       
    0x83, 0xF9, 0x1E,                       //cmp ecx, 0x1E 
    0x74, 0x0E,                             //je set 60
    0x83, 0xF9, 0x2D,                       //cmp ecx, 0x2D
    0x74, 0x15,                             //je Sync_buffer
    0x2E, 0xB9, 0xE8, 0x03, 0x00, 0x00,     //mov ecx, 0x3E8                    
    0xEB, 0x06,                             //jmp set
    0xCC, //int3                            
    0xB9, 0x3C, 0x00, 0x00, 0x00,           //mov ecx, 0x3C                     
    0x89, 0x0D, 0x0B, 0x00, 0x00, 0x00,     //mov [hook_fps_get+1], ecx        //set
    0xC3,                                   //ret
    0x8B, 0x0D, 0x97, 0x00, 0x00, 0x00,     //mov ecx, dword[Readmem_buffer]   //Sync_buffer
    0xEB, 0xF1,                             //jmp set
    0xCC,
    //int3
    0xB8, 0x78, 0x00, 0x00, 0x00,           //mov eax,0x78                          //hook_fps_get      _shellcode_genshin[0xF0]
    0xC3,                                   //ret
    //int3
    0xCC, 0xCC,
    0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC,
    //int3
    0x8B, 0x05, 0x7A, 0x00, 0x00, 0x00,     //mov eax, dword[Game_Current_set]      //Sync_auto
    0x83, 0xF8, 0x2D,                       //cmp eax, 0x2D
    0x75, 0x0C,                             //jne return
    0x8B, 0x05, 0x73, 0x00, 0x00, 0x00,     //mov eax, dword[Readmem_buffer]
    0x89, 0x05, 0xDA, 0xFF, 0xFF, 0xFF,     //mov dword[hook_fps_get + 1], eax
    0xC3,                                   //ret
    //int3
    0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC,
    //int3
    0x48, 0x83, 0xEC, 0x28,                  //sub rsp, 0x28                        //Show Errormsg and closehandle
    0x31, 0xC9,                              //xor ecx, ecx 
    0x48, 0x8D, 0x15, 0x33, 0x00, 0x00, 0x00,//lea rdx, qword:["Sync failed!"]
    0x4C, 0x8D, 0x05, 0x3C, 0x00, 0x00, 0x00,//lea r8, qword:["Error"]
    0x41, 0xB9, 0x10, 0x00, 0x00, 0x00,      //mov r9d, 0x10 
    0xFF, 0x15, 0xD8, 0xFE, 0xFF, 0xFF,      //call [API_MessageBoxA] 
    0x89, 0xF1,                              //mov ecx, esi 
    0xFF, 0x15, 0xD8, 0xFE, 0xFF, 0xFF,      //call [API_CloseHandle] 
    0x48, 0x83, 0xC4, 0x28,                  //add rsp, 0x28
    0xC3,                                    //ret
    //int3
    0xCC, 0xCC, 0xCC,
    0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC,
    0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC,
    'S','y','n','c',' ','f','a','i','l','e','d','!', 0x00, 0x00, 0x00, 0x00,
    'E','r','r','o','r', 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,             //uint32_t Game_Current_set  
    0x00, 0x00, 0x00, 0x00,             //uint32_t Readmem_buffer    
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};


// 特征搜索 winTEuser
static uintptr_t PatternScan_Region(uintptr_t startAddress, size_t regionSize, const char* signature)
{
    auto pattern_to_byte = [](const char* pattern)
    {
        std::vector<int> bytes;
        const char* start = pattern;
        const char* end = pattern + strlen(pattern);

        for (const char* current = start; current < end; ++current) {
            if (*current == '?') {
                ++current;
                if (*current == '?')
                    ++current;
                bytes.push_back(-1);
            }
            else {
                bytes.push_back(strtoul(current, const_cast<char**>(&current), 16));
            }
        }
        return bytes;
    };

    std::vector<int> patternBytes = pattern_to_byte(signature);
    auto scanBytes = reinterpret_cast<std::uint8_t*>(startAddress);

    for (size_t i = 0; i < regionSize - patternBytes.size(); ++i)
    {
        bool found = true;
        for (size_t j = 0; j < patternBytes.size(); ++j) {
            if (scanBytes[i + j] != patternBytes[j] && patternBytes[j] != -1) {
                found = false;
                break;
            }
        }
        if (found) {
            return (uintptr_t)&scanBytes[i];
        }
    }
    return 0;
}

std::string GetLastErrorAsString(DWORD code)
{
    LPSTR buf = nullptr;
    FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL, code, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&buf, 0, NULL);
    std::string ret = buf;
    LocalFree(buf);
    return ret;
}

static bool GetModule(DWORD pid, std::string ModuleName, PMODULEENTRY32 pEntry)
{
    if (!pEntry)
        return false;

    MODULEENTRY32 mod32{};
    mod32.dwSize = sizeof(mod32);
    HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pid);
    bool temp = Module32First(snap, &mod32);
    if (temp)
    {
        do
        {
            if (mod32.th32ProcessID != pid)
            {
                break;
            }
            if (mod32.szModule == ModuleName)
            {
                *pEntry = mod32;
                CloseHandle(snap);
                return 1;
            }

        } while (Module32Next(snap, &mod32));

    }
    CloseHandle(snap);
    return 0;
}
// 通过进程名搜索进程ID
DWORD GetPID(std::string ProcessName)
{
    DWORD pid = 0;
    PROCESSENTRY32 pe32{};
    pe32.dwSize = sizeof(pe32);
    HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    
    if (snap == INVALID_HANDLE_VALUE)
        return 0;
    
    for (BOOL bRet = Process32First(snap, &pe32); bRet; bRet = Process32Next(snap, &pe32))
    {
        if (pe32.szExeFile == ProcessName)
        {
            pid = pe32.th32ProcessID;
            break;  // 找到后立即跳出，不继续遍历
        }
    }
    CloseHandle(snap);
    return pid;
}

bool WriteConfig(std::string GamePath, int fps)
{
    HANDLE hFile = CreateFileA("fps_config.ini", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL | FILE_ATTRIBUTE_HIDDEN, nullptr);
    if (hFile == INVALID_HANDLE_VALUE)
    {
        DWORD code = GetLastError();
        printf(_(STR_CREATE_FILE_FAILED), code, GetLastErrorAsString(code).c_str());
        return false;
    }

    std::string content{};
    content = "[Setting]\n";
    content += "Path=" + GamePath + "\n";
    content += "FPS=" + std::to_string(fps);

    DWORD written = 0;
    WriteFile(hFile, content.data(), content.size(), &written, nullptr);
    CloseHandle(hFile);
    return true;
}

// Forward declaration of HDR detection function
bool IsHDREnabled();

// 检测游戏版本（原神或国际版）
static GameVersion DetectGameVersion(const std::string& processPath)
{
    // 获取可执行文件名
    size_t lastSlash = processPath.find_last_of("\\");
    std::string exeName = (lastSlash != std::string::npos) ? 
                         processPath.substr(lastSlash + 1) : processPath;
    
    // 转为小写进行比较
    std::string exeNameLower = exeName;
    std::transform(exeNameLower.begin(), exeNameLower.end(), exeNameLower.begin(), ::tolower);
    
    if (exeNameLower == "yuanshen.exe")
    {
        return GameVersion::YUANSHEN;
    }
    else if (exeNameLower == "genshinimpact.exe")
    {
        return GameVersion::GENSHIN_IMPACT;
    }
    
    return GameVersion::UNKNOWN;
}

bool SetRegistryDWORDValue()
{
    // 首先检测HDR是否启用
    if (!IsHDREnabled())
    {
        return true;  // 返回true表示这不是一个错误，只是跳过操作
    }

    // 检测游戏版本
    GameVersion gameVersion = DetectGameVersion(GamePath);
    
    HKEY hKey = nullptr;
    LONG result = ERROR_SUCCESS;
    DWORD dwValue = 1;
    const wchar_t valueName[] = L"WINDOWS_HDR_ON_h3132281285";
    
    if (gameVersion == GameVersion::YUANSHEN)
    {
        // 原神版本路径
        const wchar_t subKeyPath[] = L"Software\\miHoYo\\\u539F\u795E";
        
        result = RegOpenKeyExW(HKEY_CURRENT_USER, subKeyPath, 0, KEY_WRITE, &hKey);
        if (result != ERROR_SUCCESS)
        {
            result = RegCreateKeyExW(HKEY_CURRENT_USER, subKeyPath, 0, NULL, 0, KEY_WRITE, NULL, &hKey, NULL);
            if (result != ERROR_SUCCESS)
            {
                return false;
            }
        }
    }
    else if (gameVersion == GameVersion::GENSHIN_IMPACT)
    {
        // 国际版路径
        const wchar_t subKeyPath[] = L"Software\\miHoYo\\Genshin Impact";
        
        result = RegOpenKeyExW(HKEY_CURRENT_USER, subKeyPath, 0, KEY_WRITE, &hKey);
        if (result != ERROR_SUCCESS)
        {
            result = RegCreateKeyExW(HKEY_CURRENT_USER, subKeyPath, 0, NULL, 0, KEY_WRITE, NULL, &hKey, NULL);
            if (result != ERROR_SUCCESS)
            {
                return false;
            }
        }
    }
    else
    {
        // 未知版本，尝试两个都设置
        bool yuanshenSuccess = false;
        bool genshinSuccess = false;
        
        // 尝试设置原神
        const wchar_t yuanShenPath[] = L"Software\\miHoYo\\\u539F\u795E";
        result = RegOpenKeyExW(HKEY_CURRENT_USER, yuanShenPath, 0, KEY_WRITE, &hKey);
        if (result != ERROR_SUCCESS)
        {
            result = RegCreateKeyExW(HKEY_CURRENT_USER, yuanShenPath, 0, NULL, 0, KEY_WRITE, NULL, &hKey, NULL);
        }
        if (result == ERROR_SUCCESS)
        {
            result = RegSetValueExW(hKey, valueName, 0, REG_DWORD, (const BYTE*)&dwValue, sizeof(DWORD));
            yuanshenSuccess = (result == ERROR_SUCCESS);
            RegCloseKey(hKey);
        }
        
        // 尝试设置国际版
        const wchar_t genshinPath[] = L"Software\\miHoYo\\Genshin Impact";
        result = RegOpenKeyExW(HKEY_CURRENT_USER, genshinPath, 0, KEY_WRITE, &hKey);
        if (result != ERROR_SUCCESS)
        {
            result = RegCreateKeyExW(HKEY_CURRENT_USER, genshinPath, 0, NULL, 0, KEY_WRITE, NULL, &hKey, NULL);
        }
        if (result == ERROR_SUCCESS)
        {
            result = RegSetValueExW(hKey, valueName, 0, REG_DWORD, (const BYTE*)&dwValue, sizeof(DWORD));
            genshinSuccess = (result == ERROR_SUCCESS);
            RegCloseKey(hKey);
        }
        
        return yuanshenSuccess || genshinSuccess;
    }

    // 设置 DWORD 值
    result = RegSetValueExW(hKey, valueName, 0, REG_DWORD, (const BYTE*)&dwValue, sizeof(DWORD));
    if (result != ERROR_SUCCESS)
    {
        RegCloseKey(hKey);
        return false;
    }

    RegCloseKey(hKey);
    return true;
}

//Hotpatch
static DWORD64 inject_patch(LPVOID text_buffer, DWORD text_size, DWORD64 _text_baseaddr, uint64_t _ptr_fps, HANDLE Tar_handle)
{
    if (text_buffer == 0 || text_size == 0 || _text_baseaddr == 0 || _ptr_fps == 0 || Tar_handle == 0)
        return 0;

    DWORD64 Module_TarSec_RVA = (DWORD64)text_buffer;
    DWORD Module_TarSec_Size = text_size;

    DWORD64 address = 0;
    DWORD64 Hook_addr_fpsget = 0;   //in buffer
    DWORD64 Hook_addr_tar_fpsget = 0;
    DWORD64 Hook_addr_fpsSet = 0;   //in buffer
    DWORD64 Hook_addr_tar_fpsSet = 0;
    DWORD64 _addr_tar_fpsget_TarFun = 0;
    DWORD64 _addr_tar_fpsSet_TarFun = 0;
	
__Get_fpsSet_addr:
    uint64_t _shellcode_buffer = (uint64_t)VirtualAlloc(0, 0x1000, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    if (_shellcode_buffer == 0)
    {
        printf_s(_(STR_BUFFER_ALLOC_FAIL));
        return 0;
    }
    memcpy((void*)_shellcode_buffer, &_shellcode_genshin_Const, sizeof(_shellcode_genshin_Const));

    uint64_t _Addr_OpenProcess = (uint64_t)(&OpenProcess);
    uint64_t _Addr_ReadProcessmem = (uint64_t)(&ReadProcessMemory);
    uint64_t _Addr_Sleep = (uint64_t)(&Sleep);
    uint64_t _Addr_MessageBoxA = (uint64_t)(&MessageBoxA);
    uint64_t _Addr_CloseHandle = (uint64_t)(&CloseHandle);
    *(uint32_t*)_shellcode_buffer = GetCurrentProcessId();       //unlocker PID
    *(uint64_t*)(_shellcode_buffer + 8) = (uint64_t)(&FpsValue); //unlocker fps ptr
    *(uint64_t*)(_shellcode_buffer + 16) = _Addr_OpenProcess;
    *(uint64_t*)(_shellcode_buffer + 24) = _Addr_ReadProcessmem;
    *(uint64_t*)(_shellcode_buffer + 32) = _Addr_Sleep;
    *(uint64_t*)(_shellcode_buffer + 40) = _Addr_MessageBoxA;
    *(uint64_t*)(_shellcode_buffer + 48) = _Addr_CloseHandle;
    *(uint32_t*)(_shellcode_buffer + 0xE4) = 1000;
    *(uint32_t*)(_shellcode_buffer + 0xEC) = 60;

    *(uint64_t*)(_shellcode_buffer + 0x110) = 0xB848;                //mov rax, game_pfps
    *(uint64_t*)(_shellcode_buffer + 0x118) = 0x741D8B0000;          //mov ebx, dword[Readmem_buffer]
    *(uint64_t*)(_shellcode_buffer + 0x120) = 0xCCCCCCCCCCC31889;    //mov [rax], ebx 
    *(uint64_t*)(_shellcode_buffer + 0x112) = _ptr_fps;              //ret
    *(uint64_t*)(_shellcode_buffer + 0x15C) = 0x5C76617E8834858;    //keep thread
    *(uint64_t*)(_shellcode_buffer + 0x164) = 0xE0FF21EBFFFFFF16;

    LPVOID __Tar_proc_buffer = VirtualAllocEx(Tar_handle, 0, 0x1000, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
    if (__Tar_proc_buffer)
    {
        if (WriteProcessMemory(Tar_handle, __Tar_proc_buffer, (void*)_shellcode_buffer, sizeof(_shellcode_genshin_Const), 0))
        {
            VirtualFree((void*)_shellcode_buffer, 0, MEM_RELEASE);
            HANDLE temp = CreateRemoteThread(Tar_handle, 0, 0, (LPTHREAD_START_ROUTINE)((uint64_t)__Tar_proc_buffer + 0x50), 0, 0, 0);
            if (temp)
            {
                CloseHandle(temp);
            }
            else
            {
                printf_s(_(STR_CREATE_REMOTE_THREAD_FAILED));
                return 0;
            }
            return ((uint64_t)__Tar_proc_buffer + 0x194);
        }
        printf_s(_(STR_INJECT_SHELLCODE_FAILED));
        VirtualFree((void*)_shellcode_buffer, 0, MEM_RELEASE);
        return 0;
    }
    else
    {
        printf_s(_(STR_ALLOC_SHELLCODE_SPACE_FAILED));
        return 0;
    }
}

void LoadConfig()
{
    if (GetFileAttributesA("config") != INVALID_FILE_ATTRIBUTES)
        DeleteFileA("config");

    INIReader reader("fps_config.ini");
    if (reader.ParseError() != 0)
    {
        printf(_(STR_CONFIG_NOT_FOUND));
        printf(_(STR_DO_NOT_CLOSE_CONSOLE));

        DWORD pid = 0;
        while (!(pid = GetPID("YuanShen.exe")) && !(pid = GetPID("GenshinImpact.exe")))
            std::this_thread::sleep_for(std::chrono::milliseconds(200));

        // Get process handle
        HANDLE hProcess = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION | SYNCHRONIZE | PROCESS_TERMINATE, FALSE, pid);
        if (!hProcess)
        {
            DWORD code = GetLastError();
            printf(_(STR_OPEN_PROCESS_FAILED), code, GetLastErrorAsString(code).c_str());
            return;
        }

        char szPath[MAX_PATH]{};
        DWORD length = sizeof(szPath);
        QueryFullProcessImageNameA(hProcess, 0, szPath, &length);

        GamePath = szPath;
        WriteConfig(GamePath, FpsValue);

        HWND hwnd = nullptr;
        while (!(hwnd = FindWindowA("UnityWndClass", nullptr)))
            std::this_thread::sleep_for(std::chrono::milliseconds(200));

        DWORD ExitCode = STILL_ACTIVE;
        while (ExitCode == STILL_ACTIVE)
        {
            SendMessageA(hwnd, WM_CLOSE, 0, 0);
            GetExitCodeProcess(hProcess, &ExitCode);
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }

        // wait for the game to close then continue
        WaitForSingleObject(hProcess, -1);
        CloseHandle(hProcess);

        system("cls");
        return;
    }

    GamePath = reader.Get("Setting", "Path", "");
    FpsValue = reader.GetInteger("Setting", "FPS", FpsValue);

    if (GetFileAttributesA(GamePath.c_str()) == INVALID_FILE_ATTRIBUTES)
    {
        printf(_(STR_CONFIG_PATH_CHANGED));
        DeleteFileA("config.ini");
        LoadConfig();
    }
}

// 检测系统是否启用了HDR
bool IsHDREnabled()
{
    // 方法1: 通过DXGI检测HDR支持
    IDXGIFactory1* pFactory = nullptr;
    IDXGIAdapter* pAdapter = nullptr;
    IDXGIOutput* pOutput = nullptr;
    IDXGIOutput6* pOutput6 = nullptr;
    bool hdrSupported = false;

    do
    {
        // 创建DXGI工厂
        if (FAILED(CreateDXGIFactory1(__uuidof(IDXGIFactory1), (void**)&pFactory)))
        {
            break;
        }

        // 获取第一个适配器（显卡）
        if (FAILED(pFactory->EnumAdapters(0, &pAdapter)))
        {
            break;
        }

        // 获取第一个输出（显示器）
        if (FAILED(pAdapter->EnumOutputs(0, &pOutput)))
        {
            break;
        }

        // 查询IDXGIOutput6接口来检测HDR
        if (SUCCEEDED(pOutput->QueryInterface(__uuidof(IDXGIOutput6), (void**)&pOutput6)))
        {
            // 获取显示模式信息
            DXGI_OUTPUT_DESC1 desc;
            if (SUCCEEDED(pOutput6->GetDesc1(&desc)))
            {
                // DXGI_COLOR_SPACE_RGB_FULL_G22_NONE_P709 = 0
                // DXGI_COLOR_SPACE_RGB_FULL_G10_NONE_P709 = 1 (HDR)
                // DXGI_COLOR_SPACE_RGB_FULL_G2084_NONE_P2020 = 2 (HDR)
                if (desc.ColorSpace == DXGI_COLOR_SPACE_RGB_FULL_G10_NONE_P709 ||
                    desc.ColorSpace == DXGI_COLOR_SPACE_RGB_FULL_G2084_NONE_P2020 ||
                    desc.ColorSpace == 3 ||  // DXGI_COLOR_SPACE_YCBCR_FULL_G2084_LEFT_P2020
                    desc.ColorSpace == 4)    // DXGI_COLOR_SPACE_YCBCR_FULL_G2084_TOPLEFT_P2020
                {
                    hdrSupported = true;
                }
            }
        }
    } while (false);

    // 清理DXGI资源
    if (pOutput6)
        pOutput6->Release();
    if (pOutput)
        pOutput->Release();
    if (pAdapter)
        pAdapter->Release();
    if (pFactory)
        pFactory->Release();

    if (hdrSupported)
    {
        return true;
    }

    // 方法2: 通过注册表检测（备选方案）
    HKEY hKey = nullptr;
    LONG result = RegOpenKeyExW(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced", 0, KEY_READ, &hKey);
    
    if (result == ERROR_SUCCESS)
    {
        DWORD hdrEnabled = 0;
        DWORD cbData = sizeof(DWORD);
        
        // Windows 11中HDR状态存储的注册表项
        LONG queryResult = RegQueryValueExW(hKey, L"EnableHDR", NULL, NULL, (LPBYTE)&hdrEnabled, &cbData);
        
        RegCloseKey(hKey);
        
        if (queryResult == ERROR_SUCCESS && hdrEnabled == 1)
        {
            return true;
        }
    }

    return false;
}

//热键线程
DWORD __stdcall Thread1(LPVOID p)
{
    if (!p)
        return 0;

    int* pTargetFPS = (int*)p;
    int fps = *pTargetFPS;
    int prev = fps;
    int lastPrintedFps = -1;  // 记录上次打印的FPS值
    
    while (true)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
        if (GetAsyncKeyState(KEY_DECREASE) & 1 && GetAsyncKeyState(VK_RCONTROL) & 0x8000)
            fps -= 20;
        if (GetAsyncKeyState(KEY_DECREASE_SMALL) & 1 && GetAsyncKeyState(VK_RCONTROL) & 0x8000)
            fps -= 2;
        if (GetAsyncKeyState(KEY_INCREASE) & 1 && GetAsyncKeyState(VK_RCONTROL) & 0x8000)
            fps += 20;
        if (GetAsyncKeyState(KEY_INCREASE_SMALL) & 1 && GetAsyncKeyState(VK_RCONTROL) & 0x8000)
            fps += 2;
        if (GetAsyncKeyState(KEY_TOGGLE) & 1)
            fps = fps != 60 ? 60 : prev;
        if (prev != fps)
        {
            WriteConfig(GamePath, fps);
            lastPrintedFps = -1;  // 重置，强制打印
        }
        if (fps > 60)
            prev = fps;
        if (fps < 60)
            fps = 60;
        
        // 仅在FPS值变化时打印，减少 printf 调用
        if (lastPrintedFps != fps)
        {
            printf("\rFPS: %d - %s    ", fps, fps > 60 ? _(STR_ON) : _(STR_OFF));
            fflush(stdout);
            lastPrintedFps = fps;
        }
        
        *pTargetFPS = fps;
    }

    return 0;
}
int main(int argc, char** argv)
{
    std::atexit([] {
        system("pause");
    });

    SetConsoleTitleA("");
    
    // 禁用IME输入法候选框
    HWND hConsole = GetConsoleWindow();
    if (hConsole)
    {
        ImmAssociateContext(hConsole, nullptr);
    }
    
    // 初始化语言系统
    Localization::InitLanguage();

    std::string CommandLine{};
    if (argc > 1)
    {
        for (int i = 1; i < argc; i++)
            CommandLine += argv[i] + std::string(" ");
    }

    // 读取配置
    LoadConfig();
    int TargetFPS = FpsValue;
    std::string ProcessPath = GamePath;
    std::string ProcessDir{};

    if (ProcessPath.length() < 8)
        return 0;

    printf(_(STR_TITLE));
    printf(_(STR_HDR_STATUS), IsHDREnabled() ? _(STR_ON) : _(STR_OFF));
    
    ProcessDir = ProcessPath.substr(0, ProcessPath.find_last_of("\\"));
    std::string procname = ProcessPath.substr(ProcessPath.find_last_of("\\") + 1);

    DWORD pid = GetPID(procname);
    if (pid)
    {
        printf(_(STR_GAME_RUNNING));
        printf(_(STR_MANUAL_START_WARNING));
        printf(_(STR_CLOSE_GAME_INSTRUCTION));
        return 0;
    }

    SetRegistryDWORDValue();

    STARTUPINFOA si{};
    PROCESS_INFORMATION pi{};
    if (!CreateProcessA(ProcessPath.c_str(), (LPSTR)CommandLine.c_str(), nullptr, nullptr, FALSE, 0, nullptr, ProcessDir.c_str(), &si, &pi))
    {
        DWORD code = GetLastError();
        printf(_(STR_CREATE_PROCESS_FAILED), code, GetLastErrorAsString(code).c_str());
        return 0;
    }

    CloseHandle(pi.hThread);
    printf(_(STR_PROCESS_PID), pi.dwProcessId);
    Sleep(200);
    StartPriority = PrioityClass[1];
    SetPriorityClass(pi.hProcess, StartPriority);
    // 等待UnityPlayer.dll加载和获取DLL信息
    MODULEENTRY32 hUnityPlayer{};
    {
        DWORD times = 1000;
        while (times != 0)
        {
            if (GetModule(pi.dwProcessId, procname, &hUnityPlayer))
            {
                goto __get_procbase_ok;
            }
            Sleep(50);
            times -= 5;
        }
        printf(_(STR_GET_BASE_MODULE_TIMEOUT));
        CloseHandle(pi.hProcess);
        return (int)-1;
    }
    {
        DWORD times = 1000;
        while (!GetModule(pi.dwProcessId, "UnityPlayer.dll", &hUnityPlayer))
        {
            Sleep(50);
            times -= 5;
            if (GetModule(pi.dwProcessId, "unityplayer.dll", &hUnityPlayer))
            {
                goto __get_procbase_ok;
            }
            if (times == 0)
            {
                printf(_(STR_GET_UNITY_MODULE_TIMEOUT));
                CloseHandle(pi.hProcess);
                return (int)-1;
            }
        }
    }
    printf(_(STR_UNITY_PLAYER_ADDR), (uintptr_t)hUnityPlayer.modBaseAddr >> 32 & -1, hUnityPlayer.modBaseAddr);
__get_procbase_ok:
    LPVOID _mbase_PE_buffer = VirtualAlloc(NULL, 0x1000, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    if (_mbase_PE_buffer == 0)
    {
        printf_s(_(STR_ALLOC_PE_BUFFER_FAILED));
        CloseHandle(pi.hProcess);
        return (int)-1;
    }
    if (hUnityPlayer.modBaseAddr == 0)
        return (int)-1;
    if (ReadProcessMemory(pi.hProcess, hUnityPlayer.modBaseAddr, _mbase_PE_buffer, 0x1000, 0) == 0)
    {
        printf_s(_(STR_READ_PE_BUFFER_FAILED));
        VirtualFree(_mbase_PE_buffer, 0, MEM_RELEASE);
        CloseHandle(pi.hProcess);
        return (int)-1;
    }
    BYTE search_sec[8] = ".text";//max 8 byte
    uint64_t tar_sec = *(uint64_t*)&search_sec;
    uintptr_t WinPEfileVA = (uintptr_t)_mbase_PE_buffer + 0x3c; //dos_header
    uintptr_t PEfptr = (uintptr_t)_mbase_PE_buffer + *(uint32_t*)WinPEfileVA; //get_winPE_VA

    _IMAGE_NT_HEADERS64 _FilePE_Nt_header = *(_IMAGE_NT_HEADERS64*)PEfptr;
    _IMAGE_SECTION_HEADER _sec_temp{};
    uintptr_t Text_Remote_RVA;
    uint32_t Text_Vsize;
    if (_FilePE_Nt_header.Signature == 0x00004550)
    {
        DWORD sec_num = _FilePE_Nt_header.FileHeader.NumberOfSections;//获得指定节段参数
        DWORD num = sec_num;
        DWORD target_sec_VA_start = 0;
        while (num)
        {
            _sec_temp = *(_IMAGE_SECTION_HEADER*)(PEfptr + 264 + (40 * (static_cast<unsigned long long>(sec_num) - num)) );

            //printf_s("sec_%d_is:  %s\n", sec_num - num, _sec_temp.Name);

            if (*(uint64_t*)(_sec_temp.Name) == tar_sec)
            {
                target_sec_VA_start = _sec_temp.VirtualAddress;
                Text_Vsize = _sec_temp.Misc.VirtualSize;
                Text_Remote_RVA = (uintptr_t)hUnityPlayer.modBaseAddr + target_sec_VA_start;
                goto __Get_target_sec;
            }
            num--;
        }
    }
    else
    {
        printf_s(_(STR_INVALID_PE_HEADER));
        VirtualFree(_mbase_PE_buffer, 0, MEM_RELEASE);
        CloseHandle(pi.hProcess);
        return (int)-1;
    }
__Get_target_sec:
    // 在本进程内申请代码段大小的内存 - 用于特征搜索
    LPVOID Copy_Text_VA = VirtualAlloc(0, Text_Vsize, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    if (Copy_Text_VA == NULL)
    {
        printf(_(STR_ALLOC_TEXT_FAILED));
        CloseHandle(pi.hProcess);
        return (int)-1;
    }
    // 把整个模块读出来
    if (ReadProcessMemory(pi.hProcess, (void*)Text_Remote_RVA, Copy_Text_VA, Text_Vsize, 0) == 0)
    {
        printf(_(STR_READ_TEXT_FAILED));
        VirtualFree(Copy_Text_VA, 0, MEM_RELEASE);
        CloseHandle(pi.hProcess);
        return (int)-1;
    }

    printf(_(STR_SEARCHING_PATTERN));

	//credit by winTEuser
    uintptr_t address = PatternScan_Region((uintptr_t)Copy_Text_VA, Text_Vsize, "8B 0D ?? ?? ?? ?? 66 0F 6E C9 0F 5B C9"); 
    if (!address)
    {
        printf(_(STR_OUTDATED_PATTERN));
        return 0;
    }

    // 计算相对地址 (FPS)
    uintptr_t pfps = 0;
    {
        uintptr_t rip = address;
        rip += 2;
        rip += *(int32_t*)(rip)+4;
        pfps = rip - (uintptr_t)Copy_Text_VA + Text_Remote_RVA;
        printf(_(STR_FPS_OFFSET), pfps);
        goto __offset_ok;
    }
__offset_ok:
    uintptr_t Patch_ptr = 0;
    {
        Patch_ptr = inject_patch(Copy_Text_VA, Text_Vsize, Text_Remote_RVA, pfps, pi.hProcess);//patch inject 
        if (Patch_ptr == NULL)
        {
            printf_s(_(STR_INJECT_PATCH_FAILED));
        }
    }

    VirtualFree(_mbase_PE_buffer, 0, MEM_RELEASE);
    VirtualFree(Copy_Text_VA, 0, MEM_RELEASE);
    printf(_(STR_DONE));
    printf(_(STR_HOTKEY_INSTRUCTIONS));
    printf(_(STR_HOTKEY_UP));
    printf(_(STR_HOTKEY_DOWN));
    printf(_(STR_HOTKEY_LEFT));
    printf(_(STR_HOTKEY_RIGHT));

    // 创建热键线程
    HANDLE hThread = CreateThread(nullptr, 0, Thread1, &TargetFPS, 0, nullptr);
    if (hThread)
        CloseHandle(hThread);

    // 最小化控制台窗口
    HWND hConsoleWnd = GetConsoleWindow();
    if (hConsoleWnd)
    {
        ShowWindow(hConsoleWnd, SW_MINIMIZE);
    }

    DWORD dwExitCode = STILL_ACTIVE;
    auto lastRegistryUpdateTime = std::chrono::steady_clock::now();
    const int REGISTRY_UPDATE_INTERVAL_SECONDS = 10;
    int registryUpdateCount = 0;
    int lastFpsValue = -1;  // 缓存上次读取的FPS值

    while (dwExitCode == STILL_ACTIVE)
    {
        GetExitCodeProcess(pi.hProcess, &dwExitCode);

        // 仅在前两次更新注册表
        if (registryUpdateCount < 2)
        {
            auto currentTime = std::chrono::steady_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(currentTime - lastRegistryUpdateTime).count();
            
            if (elapsed >= REGISTRY_UPDATE_INTERVAL_SECONDS)
            {
                registryUpdateCount++;
                printf(_(STR_UPDATING_REGISTRY), registryUpdateCount);
                SetRegistryDWORDValue();
                lastRegistryUpdateTime = currentTime;
            }
        }

        // 每两秒检查一次FPS
        std::this_thread::sleep_for(std::chrono::seconds(2));
        int fps = 0;
        if (ReadProcessMemory(pi.hProcess, (LPVOID)pfps, &fps, sizeof(fps), nullptr))
        {
            if (fps != -1 && fps != lastFpsValue)
            {
                lastFpsValue = fps;
                if (fps != TargetFPS)
                {
                    WriteProcessMemory(pi.hProcess, (LPVOID)pfps, &TargetFPS, sizeof(TargetFPS), nullptr);
                    // 热修补循环
                    WriteProcessMemory(pi.hProcess, (LPVOID)Patch_ptr, &TargetFPS, 4, nullptr);
                }
            }
        }
    }

    CloseHandle(pi.hProcess);
    TerminateProcess((HANDLE)-1, 0);

    return 0;
}
