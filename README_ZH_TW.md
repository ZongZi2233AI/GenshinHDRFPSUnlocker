# 原神FPS解鎖器 (支援HDR) v10270

[English](README.md) | [简体中文](README_ZH.md) | **繁體中文(台灣)** | [繁體中文(香港)](README_ZH_HK.md) | [日本語](README_JA.md)

---

## ?? 專案簡介

這是一個**全面增強和現代化**的原神FPS解鎖器，專為提升遊戲體驗而設計。

**核心特色：**
- ?? **120FPS** - 徹底移除60幀率上限
- ?? **原生HDR支援** - 自動配置HDR登錄檔值
- ?? **6語言介面** - 完整多語言支援
- ?? **即時快捷鍵** - 右Ctrl + 方向鍵調整FPS
- ?? **自動偵測** - 智慧識別中文版和國際版
- ?? **即時回饋** - 顯示FPS和HDR狀態
- ?? **設定保存** - 自動保存設定
- ?? **雙版本支援** - 同時支援YuanShen.exe和GenshinImpact.exe

**當前版本:** v10270  
**授權條款:** Apache License 2.0

---

## ?? 主要功能

| 功能 | 說明 |
|------|------|
| FPS解鎖 | 完全移除遊戲幀率限制 |
| HDR啟用 | 自動識別顯示器並配置HDR模式 |
| 多語言 | 支援中英日繁體簡體 |
| 快捷鍵 | Right Ctrl + 方向鍵即時調整 |
| 自動啟動 | 首次配置後自動啟動遊戲 |
| 設定持久化 | 記錄遊戲路徑和FPS設定 |

---

## ?? 安裝使用

### 第一步：下載
從[發布頁面](../../releases)下載最新版本 v10270

### 第二步：執行
以**系統管理員身份**執行程式

### 第三步：首次配置（僅需一次）
1. 程式會提示找不到設定檔
2. **手動啟動你的遊戲**
3. 程式會自動擷取遊戲路徑和程序資訊
4. 手動關閉遊戲
5. 程式會自動重啟

### 第四步：正常使用
之後每次執行程式，遊戲會**自動啟動**

---

## ?? 快捷鍵說明

在遊戲執行時使用：

```
右Ctrl + ↑  →  FPS增加20
右Ctrl + ↓  →  FPS減少20
右Ctrl + →  →  FPS增加2
右Ctrl + ←  →  FPS減少2
END        →  喺60 FPS和上一個值之間切換
```

---

## ?? 技術特性

### HDR自動配置
- 自動偵測遊戲版本（原神/國際版）
- 在對應登錄檔路徑寫入HDR配置
- 無需手動修改登錄檔

**配置路徑：**
- 原神: `HKEY_CURRENT_USER\Software\miHoYo\原神\WINDOWS_HDR_ON_h3132281285 = 1`
- 國際版: `HKEY_CURRENT_USER\Software\miHoYo\Genshin Impact\WINDOWS_HDR_ON_h3132281285 = 1`

### 內存即時修補
- 直接修改遊戲內存中的FPS值
- 通過shellcode注入實現
- 支援遊戲執行時動態調整

---

## ?? 語言支援

| 語言 | 支援狀態 | 文件連結 |
|------|--------|--------|
| 英文 (English) | ? 完整 | [README.md](README.md) |
| 簡體中文 | ? 完整 | [README_ZH.md](README_ZH.md) |
| 繁體中文(台灣) | ? 完整 | [README_ZH_TW.md](README_ZH_TW.md) |
| 繁體中文(香港) | ? 完整 | [README_ZH_HK.md](README_ZH_HK.md) |
| 繁體中文(新加坡) | ? 完整 | [README.md](README.md) |
| 日文 (日本語) | ? 完整 | [README_JA.md](README_JA.md) |

---

## ?? 重要說明

### 風險聲明
- 本工具會修改遊戲內存和Windows登錄檔
- 使用前請做好備份
- 使用風險完全由使用者自行承擔

### 法律聲明
- 與HoYoverse或miHoYo無任何從屬關係
- 可能違反遊戲《服務條款》
- 不保證帳號安全，請謹慎使用

---

## ?? 常見問題

### Q1: 遊戲無法自動啟動
**A:** 檢查 `fps_config.ini` 中的遊戲路徑是否正確且檔案存在

### Q2: HDR不顯示效果
**A:** 
1. 確認顯示器支援HDR
2. 喺Windows設定中啟用HDR
3. 確保遊戲設定中也啟用了HDR

### Q3: 按快捷鍵FPS不變化
**A:**
1. 重啟遊戲
2. 確保控制台視窗在後台執行
3. 嘗試多按幾次快捷鍵

---

## ?? 授權及致謝

### 授權條款
本專案採用 **Apache License 2.0**

### 原專案致謝
本專案靈感來自並基於以下專案的概念：
- https://github.com/xiaonian233/genshin-fps-unlock
- https://github.com/34736384/genshin-fps-unlock

完整致謝資訊請查看 [ATTRIBUTION.md](ATTRIBUTION.md)

---

**感謝使用 - Made with ?? for Genshin Impact Players**
