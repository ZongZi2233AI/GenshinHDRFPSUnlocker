#ifndef __LOCALIZATION_H__
#define __LOCALIZATION_H__

#include <Windows.h>
#include <string>

// 支持的语言类型
enum class Language
{
    ENGLISH = 0,
    SIMPLIFIED_CHINESE = 1,
    TRADITIONAL_CHINESE_TAIWAN = 2,      // 台湾繁体
    TRADITIONAL_CHINESE_HONGKONG = 3,    // 香港澳门繁体
    TRADITIONAL_CHINESE_SINGAPORE = 4,   // 新加坡繁体
    JAPANESE = 5
};

// 获取系统语言设置
static Language GetSystemLanguage()
{
    LANGID langId = GetUserDefaultLangID();
    WORD primaryLang = PRIMARYLANGID(langId);
    WORD subLang = SUBLANGID(langId);

    // 检测语言
    if (primaryLang == LANG_CHINESE)
    {
        // 简体中文
        if (subLang == SUBLANG_CHINESE_SIMPLIFIED)
            return Language::SIMPLIFIED_CHINESE;
        // 繁体中文 - 按地区区分
        else if (subLang == SUBLANG_CHINESE_TRADITIONAL)
            return Language::TRADITIONAL_CHINESE_TAIWAN;
        else if (subLang == SUBLANG_CHINESE_HONGKONG)
            return Language::TRADITIONAL_CHINESE_HONGKONG;
        else if (subLang == SUBLANG_CHINESE_MACAU)
            return Language::TRADITIONAL_CHINESE_HONGKONG;  // 澳门与香港同语
        else if (subLang == SUBLANG_CHINESE_SINGAPORE)
            return Language::TRADITIONAL_CHINESE_SINGAPORE;
    }
    else if (primaryLang == LANG_JAPANESE)
    {
        return Language::JAPANESE;
    }

    // 默认返回英文
    return Language::ENGLISH;
}

// 多语言字符串定义
class Localization
{
private:
    static Language currentLanguage;

public:
    static void InitLanguage()
    {
        currentLanguage = GetSystemLanguage();
    }

    static Language GetCurrentLanguage()
    {
        return currentLanguage;
    }

    // 所有需要翻译的字符串
    static const char* GetString(int stringId);
};

// 字符串ID定义
enum StringId
{
    // 主程序信息
    STR_TITLE,                                    // 0
    STR_HDR_STATUS,                               // 1
    STR_GAME_RUNNING,                             // 2
    STR_MANUAL_START_WARNING,                     // 3
    STR_CLOSE_GAME_INSTRUCTION,                   // 4
    STR_CREATE_PROCESS_FAILED,                    // 5
    STR_PROCESS_PID,                              // 6
    STR_GET_BASE_MODULE_TIMEOUT,                  // 7
    STR_GET_UNITY_MODULE_TIMEOUT,                 // 8
    STR_UNITY_PLAYER_ADDR,                        // 9
    STR_ALLOC_PE_BUFFER_FAILED,                   // 10
    STR_READ_PE_BUFFER_FAILED,                    // 11
    STR_INVALID_PE_HEADER,                        // 12
    STR_ALLOC_TEXT_FAILED,                        // 13
    STR_READ_TEXT_FAILED,                         // 14
    STR_SEARCHING_PATTERN,                        // 15
    STR_OUTDATED_PATTERN,                         // 16
    STR_FPS_OFFSET,                               // 17
    STR_INJECT_PATCH_FAILED,                      // 18
    STR_DONE,                                     // 19
    STR_HOTKEY_INSTRUCTIONS,                      // 20
    STR_HOTKEY_UP,                                // 21
    STR_HOTKEY_DOWN,                              // 22
    STR_HOTKEY_LEFT,                              // 23
    STR_HOTKEY_RIGHT,                             // 24
    STR_UPDATING_REGISTRY,                        // 25
    STR_LOADING_CONFIG,                           // 26
    STR_CONFIG_NOT_FOUND,                         // 27
    STR_DO_NOT_CLOSE_CONSOLE,                     // 28
    STR_ONLY_DONE_ONCE,                           // 29
    STR_WAITING_GAME_STARTUP,                     // 30
    STR_OPEN_PROCESS_FAILED,                      // 31
    STR_CONFIG_PATH_CHANGED,                      // 32
    STR_RECONFIGURING,                            // 33
    STR_CREATE_FILE_FAILED,                       // 34
    STR_CREATE_REMOTE_THREAD_FAILED,              // 35
    STR_INJECT_SHELLCODE_FAILED,                  // 36
    STR_ALLOC_SHELLCODE_SPACE_FAILED,             // 37
    STR_BUFFER_ALLOC_FAIL,                        // 38
    STR_FPS_STATUS,                               // 39
    STR_ON,                                       // 40
    STR_OFF,                                      // 41
};

// 实现字符串获取函数
inline const char* Localization::GetString(int stringId)
{
    if (currentLanguage == Language::SIMPLIFIED_CHINESE)
    {
        // 简体中文
        switch (stringId)
        {
            case STR_TITLE: return "原神帧率及原生高动态范围模式解锁器 x64 v10270\n\n已检测到配置文件，游戏将自动运行\n";
            case STR_HDR_STATUS: return "高动态范围 %s\n\n";
            case STR_GAME_RUNNING: return "游戏已在运行！\n";
            case STR_MANUAL_START_WARNING: return "手动启动游戏将导致故障\n";
            case STR_CLOSE_GAME_INSTRUCTION: return "请手动关闭游戏 - 解锁器将自动启动它\n";
            case STR_CREATE_PROCESS_FAILED: return "创建进程 失败 (%d): %s";
            case STR_PROCESS_PID: return "进程ID: %d\n";
            case STR_GET_BASE_MODULE_TIMEOUT: return "获取基础模块超时！ \n";
            case STR_GET_UNITY_MODULE_TIMEOUT: return "获取团结引擎模块超时！ \n";
            case STR_UNITY_PLAYER_ADDR: return "团结引擎: %X%X\n";
            case STR_ALLOC_PE_BUFFER_FAILED: return "VirtualAlloc 失败! (PE_buffer)";
            case STR_READ_PE_BUFFER_FAILED: return "读取内存失败! (PE_buffer)";
            case STR_INVALID_PE_HEADER: return "无效的PE头!";
            case STR_ALLOC_TEXT_FAILED: return "VirtualAlloc 失败! (Text)";
            case STR_READ_TEXT_FAILED: return "读取内存失败! (text)";
            case STR_SEARCHING_PATTERN: return "正在搜索特征码...\n";
            case STR_OUTDATED_PATTERN: return "已过时的特征码\n";
            case STR_FPS_OFFSET: return "帧率 偏移: %X\n";
            case STR_INJECT_PATCH_FAILED: return "注入补丁失败!\n\n";
            case STR_DONE: return "完成\n\n";
            case STR_HOTKEY_INSTRUCTIONS: return "使用右Control + 方向键更改帧率限制:\n";
            case STR_HOTKEY_UP: return "  右控制键 + 上: +20\n";
            case STR_HOTKEY_DOWN: return "  右控制键 + 下: -20\n";
            case STR_HOTKEY_LEFT: return "  右控制键 + 左: -2\n";
            case STR_HOTKEY_RIGHT: return "  右控制键 + 右: +2\n\n";
            case STR_UPDATING_REGISTRY: return "注入状态检测%d/2 ";
            case STR_LOADING_CONFIG: return "正在加载配置...\n";
            case STR_CONFIG_NOT_FOUND: return "正在初始化中\n初次启动 未找到配置文件\n首次启动程序请手动启动游戏以捕获游戏文件位置及进程\n下次启动仅需运行本程序-将自动为您启动游戏";
            case STR_DO_NOT_CLOSE_CONSOLE: return "\n正在等待游戏启动...\n";
            case STR_ONLY_DONE_ONCE: return "仅需执行一次\n";
            case STR_WAITING_GAME_STARTUP: return "等待游戏启动...\n";
            case STR_OPEN_PROCESS_FAILED: return "启动进程 失败 (%d): %s";
            case STR_CONFIG_PATH_CHANGED: return "配置路径已更改 - 正在重新配置\n";
            case STR_RECONFIGURING: return "重新配置中\n";
            case STR_CREATE_FILE_FAILED: return "CreateFileA 失败 (%d): %s\n";
            case STR_CREATE_REMOTE_THREAD_FAILED: return "创建游戏内同步线程失败! ";
            case STR_INJECT_SHELLCODE_FAILED: return "注入shellcode失败! ";
            case STR_ALLOC_SHELLCODE_SPACE_FAILED: return "申请shellcode空间失败! ";
            case STR_BUFFER_ALLOC_FAIL: return "缓冲区分配失败! \n";
            case STR_FPS_STATUS: return "当前帧率: %d - %s    ";
            case STR_ON: return "开启";
            case STR_OFF: return "关闭";
            default: return "";
        }
    }
    else if (currentLanguage == Language::TRADITIONAL_CHINESE_TAIWAN)
    {
        // 繁体中文（台湾） - 使用台湾用语
        switch (stringId)
        {
            case STR_TITLE: return "原神FPS解鎖器 (支援HDR) x64 v10270\n\n偵測到設定檔，遊戲會自動執行\n";
            case STR_HDR_STATUS: return "HDR %s\n\n";
            case STR_GAME_RUNNING: return "遊戲已在執行！\n";
            case STR_MANUAL_START_WARNING: return "手動啟動遊戲將導致故障\n";
            case STR_CLOSE_GAME_INSTRUCTION: return "請手動關閉遊戲 - 解鎖器將自動啟動它\n";
            case STR_CREATE_PROCESS_FAILED: return "建立程序 失敗 (%d): %s";
            case STR_PROCESS_PID: return "程序 ID: %d\n";
            case STR_GET_BASE_MODULE_TIMEOUT: return "取得基礎模組逾時！ \n";
            case STR_GET_UNITY_MODULE_TIMEOUT: return "取得 Unity 模組逾時！ \n";
            case STR_UNITY_PLAYER_ADDR: return "UnityPlayer: %X%X\n";
            case STR_ALLOC_PE_BUFFER_FAILED: return "VirtualAlloc 失敗! (PE_buffer)";
            case STR_READ_PE_BUFFER_FAILED: return "讀取記憶體失敗! (PE_buffer)";
            case STR_INVALID_PE_HEADER: return "無效的 PE 標頭!";
            case STR_ALLOC_TEXT_FAILED: return "VirtualAlloc 失敗! (Text)";
            case STR_READ_TEXT_FAILED: return "讀取記憶體失敗! (text)";
            case STR_SEARCHING_PATTERN: return "正在搜尋特徵碼...\n";
            case STR_OUTDATED_PATTERN: return "已過時的特徵碼\n";
            case STR_FPS_OFFSET: return "FPS 位移: %X\n";
            case STR_INJECT_PATCH_FAILED: return "注入補丁失敗!\n\n";
            case STR_DONE: return "完成\n\n";
            case STR_HOTKEY_INSTRUCTIONS: return "使用右 Ctrl + 方向鍵變更 FPS 限制:\n";
            case STR_HOTKEY_UP: return "  右 Ctrl + 上: +20\n";
            case STR_HOTKEY_DOWN: return "  右 Ctrl + 下: -20\n";
            case STR_HOTKEY_LEFT: return "  右 Ctrl + 左: -2\n";
            case STR_HOTKEY_RIGHT: return "  右 Ctrl + 右: +2\n\n";
            case STR_UPDATING_REGISTRY: return "更新登錄檔值 (更新 %d/2)...\n";
            case STR_LOADING_CONFIG: return "正在載入設定...\n";
            case STR_CONFIG_NOT_FOUND: return "正在初始化\n第一次啟動 找不到設定檔\n初次啟動程式時，請手動啟動遊戲，以便擷取遊戲檔案的位置及處理程序\n下次啟動只要執行這個程式，就會自動幫您啟動遊戲。\n";
            case STR_DO_NOT_CLOSE_CONSOLE: return "\n正在等待遊戲啟動...\n";
            case STR_ONLY_DONE_ONCE: return "僅需執行一次\n";
            case STR_WAITING_GAME_STARTUP: return "等待遊戲啟動...\n";
            case STR_OPEN_PROCESS_FAILED: return "開啟程序 失敗 (%d): %s";
            case STR_CONFIG_PATH_CHANGED: return "設定檔路徑已變更 - 正在重新設定\n";
            case STR_RECONFIGURING: return "重新設定中\n";
            case STR_CREATE_FILE_FAILED: return "CreateFileA 失敗 (%d): %s\n";
            case STR_CREATE_REMOTE_THREAD_FAILED: return "建立遊戲內同步執行緒失敗! ";
            case STR_INJECT_SHELLCODE_FAILED: return "注入 shellcode 失敗! ";
            case STR_ALLOC_SHELLCODE_SPACE_FAILED: return "配置 shellcode 空間失敗! ";
            case STR_BUFFER_ALLOC_FAIL: return "緩衝區配置失敗! \n";
            case STR_FPS_STATUS: return "FPS: %d - %s    ";
            case STR_ON: return "開啟";
            case STR_OFF: return "關閉";
            default: return "";
        }
    }
    else if (currentLanguage == Language::TRADITIONAL_CHINESE_HONGKONG)
    {
        // 繁体中文（香港/澳门） - 使用港澳用语
        switch (stringId)
        {
            case STR_TITLE: return "原神幀數解鎖器 (支援 HDR) x64 v10270\n\n偵測到設定檔，遊戲將會自動執行\n";
            case STR_HDR_STATUS: return "HDR %s\n\n";
            case STR_GAME_RUNNING: return "遊戲已喺執行！\n";
            case STR_MANUAL_START_WARNING: return "手動啟動遊戲會導致故障\n";
            case STR_CLOSE_GAME_INSTRUCTION: return "請手動關閉遊戲 - 解鎖器會自動啟動佢\n";
            case STR_CREATE_PROCESS_FAILED: return "建立程序 失敗 (%d): %s";
            case STR_PROCESS_PID: return "行程 ID: %d\n";
            case STR_GET_BASE_MODULE_TIMEOUT: return "取得基礎模組逾時！ \n";
            case STR_GET_UNITY_MODULE_TIMEOUT: return "取得 Unity 模組逾時！ \n";
            case STR_UNITY_PLAYER_ADDR: return "UnityPlayer: %X%X\n";
            case STR_ALLOC_PE_BUFFER_FAILED: return "VirtualAlloc 失敗! (PE_buffer)";
            case STR_READ_PE_BUFFER_FAILED: return "讀取記憶體失敗! (PE_buffer)";
            case STR_INVALID_PE_HEADER: return "無效嘅 PE 標頭!";
            case STR_ALLOC_TEXT_FAILED: return "VirtualAlloc 失敗! (Text)";
            case STR_READ_TEXT_FAILED: return "讀取記憶體失敗! (text)";
            case STR_SEARCHING_PATTERN: return "正喺搵特徵碼...\n";
            case STR_OUTDATED_PATTERN: return "已過時嘅特徵碼\n";
            case STR_FPS_OFFSET: return "幀數位移: %X\n";
            case STR_INJECT_PATCH_FAILED: return "注入補丁失敗!\n\n";
            case STR_DONE: return "完成\n\n";
            case STR_HOTKEY_INSTRUCTIONS: return "使用右控制鍵 + 方向鍵改變幀數上限:\n";
            case STR_HOTKEY_UP: return "  右控制鍵 + 上: +20\n";
            case STR_HOTKEY_DOWN: return "  右控制鍵 + 下: -20\n";
            case STR_HOTKEY_LEFT: return "  右控制鍵 + 左: -2\n";
            case STR_HOTKEY_RIGHT: return "  右控制鍵 + 右: +2\n\n";
            case STR_UPDATING_REGISTRY: return "更新登錄檔值 (更新 %d/2)...\n";
            case STR_LOADING_CONFIG: return "正喺載入設定...\n";
            case STR_CONFIG_NOT_FOUND: return "正在初始化\n首次啟動：未找到設定檔\n初次啟動程式請手動開啟遊戲\n以擷取遊戲檔案位置及處理程序\n下次啟動只需運行本程式\n便會自動為您啟動遊戲。\n";
            case STR_DO_NOT_CLOSE_CONSOLE: return "\n正喺等待遊戲啟動...\n";
            case STR_ONLY_DONE_ONCE: return "淨係需要做一次\n";
            case STR_WAITING_GAME_STARTUP: return "等待遊戲啟動...\n";
            case STR_OPEN_PROCESS_FAILED: return "開啟程序 失敗 (%d): %s";
            case STR_CONFIG_PATH_CHANGED: return "設定檔路徑已改變 - 正喺重新設定\n";
            case STR_RECONFIGURING: return "重新設定中\n";
            case STR_CREATE_FILE_FAILED: return "CreateFileA 失敗 (%d): %s\n";
            case STR_CREATE_REMOTE_THREAD_FAILED: return "建立遊戲內同步執行緒失敗! ";
            case STR_INJECT_SHELLCODE_FAILED: return "注入 shellcode 失敗! ";
            case STR_ALLOC_SHELLCODE_SPACE_FAILED: return "配置 shellcode 空間失敗! ";
            case STR_BUFFER_ALLOC_FAIL: return "緩衝區配置失敗! \n";
            case STR_FPS_STATUS: return "實時幀數上限: %d - %s    ";
            case STR_ON: return "開啟";
            case STR_OFF: return "關閉";
            default: return "";
        }
    }
    else if (currentLanguage == Language::TRADITIONAL_CHINESE_SINGAPORE)
    {
        // 繁体中文（新加坡） - 使用新加坡用语
        switch (stringId)
        {
            case STR_TITLE: return "原神 FPS 解鎖器 (支援 HDR) x64 v10270\n\n已检测到配置文件，游戏会自动运行";
            case STR_HDR_STATUS: return "HDR %s\n\n";
            case STR_GAME_RUNNING: return "遊戲已在執行！\n";
            case STR_MANUAL_START_WARNING: return "手動啟動遊戲將導致故障\n";
            case STR_CLOSE_GAME_INSTRUCTION: return "請手動關閉遊戲 - 解鎖器將自動啟動它\n";
            case STR_CREATE_PROCESS_FAILED: return "建立程序 失敗 (%d): %s";
            case STR_PROCESS_PID: return "進程 ID: %d\n";
            case STR_GET_BASE_MODULE_TIMEOUT: return "取得基礎模組逾時！ \n";
            case STR_GET_UNITY_MODULE_TIMEOUT: return "取得 Unity 模組逾時！ \n";
            case STR_UNITY_PLAYER_ADDR: return "UnityPlayer: %X%X\n";
            case STR_ALLOC_PE_BUFFER_FAILED: return "VirtualAlloc 失敗! (PE_buffer)";
            case STR_READ_PE_BUFFER_FAILED: return "讀取記憶體失敗! (PE_buffer)";
            case STR_INVALID_PE_HEADER: return "無效的 PE 標頭!";
            case STR_ALLOC_TEXT_FAILED: return "VirtualAlloc 失敗! (Text)";
            case STR_READ_TEXT_FAILED: return "讀取記憶體失敗! (text)";
            case STR_SEARCHING_PATTERN: return "正在搜尋特徵碼...\n";
            case STR_OUTDATED_PATTERN: return "已過時的特徵碼\n";
            case STR_FPS_OFFSET: return "FPS 位移: %X\n";
            case STR_INJECT_PATCH_FAILED: return "注入補丁失敗!\n\n";
            case STR_DONE: return "完成\n\n";
            case STR_HOTKEY_INSTRUCTIONS: return "使用右 Ctrl + 方向鍵改變 FPS 限制:\n";
            case STR_HOTKEY_UP: return "  右 Ctrl + 上: +20\n";
            case STR_HOTKEY_DOWN: return "  右 Ctrl + 下: -20\n";
            case STR_HOTKEY_LEFT: return "  右 Ctrl + 左: -2\n";
            case STR_HOTKEY_RIGHT: return "  右 Ctrl + 右: +2\n\n";
            case STR_UPDATING_REGISTRY: return "更新登錄表值 (更新 %d/2)...\n";
            case STR_LOADING_CONFIG: return "正在載入設定...\n";
            case STR_CONFIG_NOT_FOUND: return "正在初始化\n首次启动：未找到配置文件\n第一次启动程序请手动启动游戏以捕获游戏文件位置和进程\n下次启动只需运行本程序，就会自动为您启动游戏\n";
            case STR_DO_NOT_CLOSE_CONSOLE: return "\n正在等待遊戏啟动...\n";
            case STR_ONLY_DONE_ONCE: return "僅需執行一次\n";
            case STR_WAITING_GAME_STARTUP: return "等待遊戏啟动...\n";
            case STR_OPEN_PROCESS_FAILED: return "開啟程序 失敗 (%d): %s";
            case STR_CONFIG_PATH_CHANGED: return "設定檔路徑已改變 - 正在重新設定\n";
            case STR_RECONFIGURING: return "重新設定中\n";
            case STR_CREATE_FILE_FAILED: return "CreateFileA 失敗 (%d): %s\n";
            case STR_CREATE_REMOTE_THREAD_FAILED: return "建立遊戲內同步執行緒失敗! ";
            case STR_INJECT_SHELLCODE_FAILED: return "注入 shellcode 失敗! ";
            case STR_ALLOC_SHELLCODE_SPACE_FAILED: return "配置 shellcode 空間失敗! ";
            case STR_BUFFER_ALLOC_FAIL: return "緩衝區配置失敗! \n";
            case STR_FPS_STATUS: return "FPS: %d - %s    ";
            case STR_ON: return "開啟";
            case STR_OFF: return "關閉";
            default: return "";
        }
    }
    else if (currentLanguage == Language::JAPANESE)
    {
        // 日語
        switch (stringId)
        {
            case STR_TITLE: return "原神FPSアンロッカー (HDR対応) x64 v10270\n\n設定ファイルが検出されました。ゲームが自動的に起動します\n";
            case STR_HDR_STATUS: return "HDR %s\n\n";
            case STR_GAME_RUNNING: return "ゲームは既に実行中です！\n";
            case STR_MANUAL_START_WARNING: return "ゲームを手動で起動すると機能障害が発生します\n";
            case STR_CLOSE_GAME_INSTRUCTION: return "ゲームを手動で終了してください - アンロッカーが自動的に起動します\n";
            case STR_CREATE_PROCESS_FAILED: return "プロセス作成失敗 (%d): %s";
            case STR_PROCESS_PID: return "プロセスID: %d\n";
            case STR_GET_BASE_MODULE_TIMEOUT: return "基本モジュール取得タイムアウト！\n";
            case STR_GET_UNITY_MODULE_TIMEOUT: return "UnityPlayer モジュール取得タイムアウト！\n";
            case STR_UNITY_PLAYER_ADDR: return "UnityPlayer: %X%X\n";
            case STR_ALLOC_PE_BUFFER_FAILED: return "VirtualAlloc失敗! (PE_buffer)";
            case STR_READ_PE_BUFFER_FAILED: return "メモリ読み込み失敗! (PE_buffer)";
            case STR_INVALID_PE_HEADER: return "無効なPEヘッダ!";
            case STR_ALLOC_TEXT_FAILED: return "VirtualAlloc失敗! (Text)";
            case STR_READ_TEXT_FAILED: return "メモリ読み込み失敗! (text)";
            case STR_SEARCHING_PATTERN: return "パターン検索中...\n";
            case STR_OUTDATED_PATTERN: return "パターンが古いか見つかりません\n";
            case STR_FPS_OFFSET: return "FPSオフセット: %X\n";
            case STR_INJECT_PATCH_FAILED: return "パッチ注入失敗!\n\n";
            case STR_DONE: return "完了\n\n";
            case STR_HOTKEY_INSTRUCTIONS: return "右Ctrl + 矢印キーでFPS制限を調整:\n";
            case STR_HOTKEY_UP: return "  右Ctrl + 上: +20\n";
            case STR_HOTKEY_DOWN: return "  右Ctrl + 下: -20\n";
            case STR_HOTKEY_LEFT: return "  右Ctrl + 左: -2\n";
            case STR_HOTKEY_RIGHT: return "  右Ctrl + 右: +2\n\n";
            case STR_UPDATING_REGISTRY: return "レジストリ値を更新中 (更新 %d/2)...\n";
            case STR_LOADING_CONFIG: return "設定を読み込み中...\n";
            case STR_CONFIG_NOT_FOUND: return "初期化中...\n初回起動：設定ファイルが見つかりません\nゲームを手動で起動して、そのパスとプロセスを記録してください\n次回起動時は自動的にゲームが起動します\n";
            case STR_DO_NOT_CLOSE_CONSOLE: return "\nゲーム起動を待機中...\n";
            case STR_ONLY_DONE_ONCE: return "初回のみ実行が必要です\n";
            case STR_WAITING_GAME_STARTUP: return "ゲーム起動を待機中...\n";
            case STR_OPEN_PROCESS_FAILED: return "プロセス開始失敗 (%d): %s";
            case STR_CONFIG_PATH_CHANGED: return "設定パスが変更されました - 再設定中\n";
            case STR_RECONFIGURING: return "再設定中...\n";
            case STR_CREATE_FILE_FAILED: return "ファイル作成失敗 (%d): %s\n";
            case STR_CREATE_REMOTE_THREAD_FAILED: return "リモートスレッド作成失敗! ";
            case STR_INJECT_SHELLCODE_FAILED: return "シェルコード注入失敗! ";
            case STR_ALLOC_SHELLCODE_SPACE_FAILED: return "シェルコード領域の割り当て失敗! ";
            case STR_BUFFER_ALLOC_FAIL: return "バッファ割り当て失敗! \n";
            case STR_FPS_STATUS: return "現在のFPS: %d - %s    ";
            case STR_ON: return "有効";
            case STR_OFF: return "無効";
            default: return "";
        }
    }

    // 英文（默认）
    switch (stringId)
    {
        case STR_TITLE: return "Genshin Impact FPS Unlocker with HDR Support x64 v10270\n\nConfiguration file detected, game will launch automatically\n";
        case STR_HDR_STATUS: return "HDR %s\n\n";
        case STR_GAME_RUNNING: return "Game is already running!\n";
        case STR_MANUAL_START_WARNING: return "Manual game startup will cause malfunction\n";
        case STR_CLOSE_GAME_INSTRUCTION: return "Please manually close the game - the unlocker will start it automatically\n";
        case STR_CREATE_PROCESS_FAILED: return "Create process failed (%d): %s";
        case STR_PROCESS_PID: return "Process ID: %d\n";
        case STR_GET_BASE_MODULE_TIMEOUT: return "Failed to get base module - timeout! \n";
        case STR_GET_UNITY_MODULE_TIMEOUT: return "Failed to get UnityPlayer module - timeout! \n";
        case STR_UNITY_PLAYER_ADDR: return "UnityPlayer: %X%X\n";
        case STR_ALLOC_PE_BUFFER_FAILED: return "VirtualAlloc failed! (PE_buffer)";
        case STR_READ_PE_BUFFER_FAILED: return "ReadProcessMemory failed! (PE_buffer)";
        case STR_INVALID_PE_HEADER: return "Invalid PE header!";
        case STR_ALLOC_TEXT_FAILED: return "VirtualAlloc failed! (Text)";
        case STR_READ_TEXT_FAILED: return "ReadProcessMemory failed! (text)";
        case STR_SEARCHING_PATTERN: return "Searching for pattern...\n";
        case STR_OUTDATED_PATTERN: return "Pattern outdated or not found\n";
        case STR_FPS_OFFSET: return "FPS offset: %X\n";
        case STR_INJECT_PATCH_FAILED: return "Patch injection failed!\n\n";
        case STR_DONE: return "Done\n\n";
        case STR_HOTKEY_INSTRUCTIONS: return "Use Right Ctrl + Arrow Keys to adjust FPS limit:\n";
        case STR_HOTKEY_UP: return "  Right Ctrl + Up Arrow: +20\n";
        case STR_HOTKEY_DOWN: return "  Right Ctrl + Down Arrow: -20\n";
        case STR_HOTKEY_LEFT: return "  Right Ctrl + Left Arrow: -2\n";
        case STR_HOTKEY_RIGHT: return "  Right Ctrl + Right Arrow: +2\n\n";
        case STR_UPDATING_REGISTRY: return "Updating registry values (Update %d/2)...\n";
        case STR_LOADING_CONFIG: return "Loading configuration...\n";
        case STR_CONFIG_NOT_FOUND: return "Initializing...\nFirst launch: Configuration file not found\nPlease manually launch the game to capture its file path and process\nNext launch will automatically start the game for you\n";
        case STR_DO_NOT_CLOSE_CONSOLE: return "\nWaiting for game to launch...\n";
        case STR_ONLY_DONE_ONCE: return "This only needs to be done once\n";
        case STR_WAITING_GAME_STARTUP: return "Waiting for game startup...\n";
        case STR_OPEN_PROCESS_FAILED: return "Open process failed (%d): %s";
        case STR_CONFIG_PATH_CHANGED: return "Configuration path changed - reconfiguring\n";
        case STR_RECONFIGURING: return "Reconfiguring...\n";
        case STR_CREATE_FILE_FAILED: return "CreateFile failed (%d): %s\n";
        case STR_CREATE_REMOTE_THREAD_FAILED: return "Create remote thread failed! ";
        case STR_INJECT_SHELLCODE_FAILED: return "Shellcode injection failed! ";
        case STR_ALLOC_SHELLCODE_SPACE_FAILED: return "Failed to allocate shellcode space! ";
        case STR_BUFFER_ALLOC_FAIL: return "Buffer allocation failed! \n";
        case STR_FPS_STATUS: return "Current FPS: %d - %s    ";
        case STR_ON: return "ON";
        case STR_OFF: return "OFF";
        default: return "";
    }
}

// 静态成员初始化
Language Localization::currentLanguage = Language::ENGLISH;

// 便捷宏定义
#define _(stringId) Localization::GetString(stringId)

#endif // __LOCALIZATION_H__
