# AI_trash_can

## 目次

1. [1-OpenCVの環境構築(Windows)](#1-OpenCVの環境構築)

<br>

### 1-OpenCVの環境構築
Windowsには```MSVC```と```MinGW```という2つのC++のコンパイラがあります。\
```MSVC```は，Visual Studioに付属するコンパイラで、```MinGW```はGCCのWindowsへの移植版です。
今回は、```MinGW```をinstallします。

<br>

#### MinGW
---

下記にあるMinGWのリンクに飛び、```Release of 13.2.0-rt_v11-rev0```の```x86_64-13.2.0-release-posix-seh-msvcrt-rt_v11-rev0.7z```をクリックします。

[MinGW](https://github.com/niXman/mingw-builds-binaries/releases "MinGW")

<br>

#### Make
---

Makeをinstallします。下記にあるリンクに飛び、Complete package, except sourcesの列の```Setup```をクリックします。

[Make](https://gnuwin32.sourceforge.net/packages/make.htm "Make")

<br>

#### cmake
---

cmakeをinstallします。下記にあるリンクに飛び、Windows x64 installerと書かれてある列の```cmake-3.30.0-rc3-windows:x86 64msi```をクリックします。

[cmake](https://cmake.org/download/ "cmake")

<br>

#### 環境変数の設定
---

インストールしたものにPATHを通します。\
PowershellでPATHを通すコマンドは以下になります。

```powershell
[Environment]::SetEnvironmentVariable(
  "Path",
  $env:Path + ";C:\Users\hogehoge\mingw64\bin;C:\Program Files (x86)\GnuWin32\bin;C:\Program Files\CMake\bin",
  [EnvironmentVariableTarget]::User
)
```
実行後、再起動して```echo $env:Path```でPathがあるかを確認してください．

<br>

>PATHを通すとは、コマンドを実行するときにそのプログラムを探しに行くディレクトリを教えることです。

<br>

>binとは、binary(実行可能ファイル)の略称で.exe等が置かれているフォルダです。

<br>

#### OpenCVのコード取得
---

Opencvのコードを取得します。下記にあるリンクに飛び、version-4.9.0の```Sources```をクリックしてください。

[Opencv](https://opencv.org/releases/ "Opencv")

ダウンロード後、Opencvディレクトリ内に```build```ディレクトリを作成します。



<br>

### 参考資料
---

[MinGWでOpenCVを使う](https://qiita.com/JuvenileTalk9/items/c29dfa8e77a11919c4b7 "MinGWでOpenCVを使う")

