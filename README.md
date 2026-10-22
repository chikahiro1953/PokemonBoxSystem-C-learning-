# PokemonBox

C++で作成したポケモンボックス管理プログラムです。
ポケモンのスカウト、ボックスへの追加、ボックスの切り替え、ポケモンの検索を行えます。

## 主な機能

- ポケモンのスカウト
- 10匹の候補からポケモンを選択
- 選択したポケモンをボックスへ追加
- ボックス内のポケモンとレベルを表示
- 前後のボックスへ移動
- ボックス内のポケモンを検索する機能

## プロジェクト構成

```text
PokemonBox/
├─ include/              ヘッダーファイル
│  ├─ Box.h
│  ├─ BoxStrage.h
│  ├─ ConsoleUI.h
│  ├─ Pokemon.h
│  ├─ Scout.h
│  └─ Search.h
├─ src/                  ソースファイル
│  ├─ main.cpp
│  ├─ Box.cpp
│  ├─ BoxStrage.cpp
│  ├─ ConsoleUI.cpp
│  ├─ Scout.cpp
│  └─ Search.cpp
└─ .vscode/              VS Code設定
```

## 必要な環境

- Windows
- Visual Studio または Build Tools
- MSVC (`cl.exe`)
- Visual Studio Code
- VS Code C/C++拡張機能

`cl.exe` を使用するため、ビルド前に「Developer PowerShell for VS」または「x64 Native Tools Command Prompt for VS」を起動してください。

## VS Codeでビルドする方法

1. PokemonBoxフォルダーをVS Codeで開きます。
2. `Ctrl + Shift + B` を押します。
3. `PokemonBox: cl.exe 全体ビルド` を選択します。
4. `src/PokemonBox.exe` が生成されます。

## PowerShellでビルドする方法

プロジェクトのルートフォルダーで次のコマンドを実行します。

```powershell
cl.exe /nologo /EHsc /utf-8 /Iinclude `
  src\main.cpp `
  src\Box.cpp `
  src\BoxStrage.cpp `
  src\ConsoleUI.cpp `
  src\Scout.cpp `
  src\Search.cpp `
  /Fesrc\PokemonBox.exe
```

## 起動方法

ビルド後、次のコマンドを実行します。

```powershell
.\src\PokemonBox.exe
```

または、VS Codeで `F5` を押すと、全体ビルド後に起動できます。

## 操作方法

### ホーム画面

```text
1: ポケモンをスカウトする
2: ボックス預かりシステム
```

### スカウト画面

```text
1: スカウトする
2: ホームに戻る
```

スカウトを選ぶと10匹の候補が表示されます。`1` から `10` の番号を入力してポケモンを選択します。

### ボックス画面

```text
1: 前のボックス
2: 次のボックス
3: ホームに戻る
4: ポケモンを検索する
```

ボックスは8個あり、各ボックスには30匹まで保存できます。

## 注意事項

- 日本語を正しく表示するため、プログラム起動時にコンソールをUTF-8へ設定しています。
- `src/PokemonBox.exe` はビルド時に生成されるファイルです。
