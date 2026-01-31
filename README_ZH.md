# 原神帧率及HDR解锁器 v10270

[English](README.md) | **简体中文** | [繁體中文(台灣)](README_ZH_TW.md) | [繁體中文(香港)](README_ZH_HK.md) | [日本語](README_JA.md)

---

## ?? 项目简介

这是一个**全面增强和现代化**的原神FPS解锁器，专为提升游戏体验而设计。

**核心特色：**
- ?? **120FPS** - 彻底移除60帧率上限
- ?? **原生HDR支持** - 自动配置HDR注册表值
- ?? **6语言界面** - 完整多语言支持
- ?? **实时快捷键** - 右Ctrl + 方向键调整FPS
- ?? **自动检测** - 智能识别中文版和国际版
- ?? **即时反馈** - 显示FPS和HDR状态
- ?? **配置保存** - 自动保存设置
- ?? **双版本支持** - 同时支持YuanShen.exe和GenshinImpact.exe

**当前版本:** v10270  
**许可证:** Apache License 2.0

---

## ?? 主要功能

| 功能 | 说明 |
|------|------|
| FPS解锁 | 完全移除游戏60帧率限制 |
| HDR启用 | 自动识别显示器并配置HDR模式 |
| 多语言 | 支持中英日繁体简体 |
| 快捷键 | Right Ctrl + 方向键实时调整 |
| 自动启动 | 首次配置后自动启动游戏 |
| 配置持久化 | 记录游戏路径和FPS设置 |

---

## ?? 安装使用

### 第一步：下载
从[发布页面](../../releases)下载最新版本 v10270

### 第二步：运行
以**管理员身份**运行程序

### 第三步：首次配置（仅需一次）
1. 程序会提示找不到配置文件
2. **手动启动你的游戏**
3. 程序会自动捕获游戏路径和进程信息
4. 手动关闭游戏
5. 程序会自动重启

### 第四步：正常使用
之后每次运行程序，游戏会**自动启动**

---

## ?? 快捷键说明

在游戏运行时使用：

```
右Ctrl + ↑  →  FPS增加20
右Ctrl + ↓  →  FPS减少20
右Ctrl + →  →  FPS增加2
右Ctrl + ←  →  FPS减少2
END        →  在60 FPS和上一个值之间切换
```

---

## ?? 技术特性

### HDR自动配置
- 自动检测游戏版本（原神/国际版）
- 在对应注册表路径写入HDR配置
- 无需手动修改注册表

**配置路径：**
- 原神: `HKEY_CURRENT_USER\Software\miHoYo\原神\WINDOWS_HDR_ON_h3132281285 = 1`
- 国际版: `HKEY_CURRENT_USER\Software\miHoYo\Genshin Impact\WINDOWS_HDR_ON_h3132281285 = 1`

### 内存实时修补
- 直接修改游戏内存中的FPS值
- 通过shellcode注入实现
- 支持游戏运行时动态调整

### 配置文件管理
程序自动创建 `fps_config.ini`：
```ini
[Setting]
Path=C:\Games\Genshin Impact\GenshinImpact.exe
FPS=120
```

---

## ?? 语言支持

| 语言 | 支持状态 | 文档链接 |
|------|--------|--------|
| 英文 (English) | ? 完整 | [README.md](README.md) |
| 简体中文 | ? 完整 | [README_ZH.md](README_ZH.md) |
| 繁体中文(台湾) | ? 完整 | [README_ZH_TW.md](README_ZH_TW.md) |
| 繁体中文(香港) | ? 完整 | [README_ZH_HK.md](README_ZH_HK.md) |
| 繁体中文(新加坡) | ? 完整 | [README.md](README.md) |
| 日文 (日本語) | ? 完整 | [README_JA.md](README_JA.md) |

---

## ?? 重要说明

### 风险声明
- 本工具会修改游戏内存和Windows注册表
- 使用前请做好备份
- 使用风险完全由用户自行承担

### 法律声明
- 与HoYoverse或miHoYo无任何从属关系
- 可能违反游戏《服务条款》
- 不保证账号安全，请谨慎使用

---

## ?? 常见问题

### Q1: 游戏无法自动启动
**A:** 检查 `fps_config.ini` 中的游戏路径是否正确且文件存在

### Q2: HDR不显示效果
**A:** 
1. 确认显示器支持HDR
2. 在Windows设置中启用HDR
3. 确保游戏设置中也启用了HDR

### Q3: 按快捷键FPS不变化
**A:**
1. 重启游戏
2. 确保控制台窗口在后台运行
3. 尝试多按几次快捷键

### Q4: 能否通过更改代码支持其他版本？
**A:** 可以，代码开源。详见[ATTRIBUTION.md](ATTRIBUTION.md)的贡献指南

---

## ?? 贡献指南

欢迎提交Issue和Pull Request！

### 如何贡献：
1. Fork本仓库
2. 创建特性分支 (`git checkout -b feature/YourFeature`)
3. 提交更改 (`git commit -am 'Add YourFeature'`)
4. 推送到分支 (`git push origin feature/YourFeature`)
5. 提交Pull Request

### 贡献方向：
- ?? bug修复
- ?? 新语言支持
- ?? 文档改进
- ? 性能优化
- ?? 功能增强

---

## ?? 许可证和致谢

### 许可证
本项目采用 **Apache License 2.0**

### 原项目致谢
本项目灵感来自并基于以下项目的概念：
- https://github.com/xiaonian233/genshin-fps-unlock
- https://github.com/34736384/genshin-fps-unlock

完整致谢信息请查看 [ATTRIBUTION.md](ATTRIBUTION.md)

---

## ?? 获取帮助

- ?? **报告Bug:** [提交Issue](../../issues)
- ?? **讨论功能:** [Discussions](../../discussions)
- ?? **其他问题:** 通过Issue联系

---

**感谢使用 - Made with ?? for Genshin Impact Players**
