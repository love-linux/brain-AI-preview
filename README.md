# brain AI v2

SHARP の電子辞書 Brain で動く、日本語の対話 AI アプリです。
インターネットに接続せず、本体と SD カードの中だけで動作します。
Windows PC で試せる PC 版も同梱しています。


## できること

- **日本語の対話**: 本体だけでオフラインで会話できます。
- **モデルの切り替え**: 用途に合わせて 3 種類から選べます。
- **計算と時刻**: 関数電卓による計算と、現在時刻の確認ができます。
- **メモ**: 内容を端末に保存し、あとから読み出せます。
- **百科事典の検索**: 辞書ファイル `kb.tsv` を入れると使えます。
- **画像の文字読み取り (OCR)**: BMP 画像の中の文字をテキストにします。
- **画像認識**: 画像に写っているものを約 250 種類の中から推定します。
- **C プログラミング**: Brain 上で C のプログラムをコンパイルして実行できます。サンプルは `brain AI v2/tcc/examples/` にあります。
- **スクリプト言語**: Lua、JavaScript、Ruby の実行環境を同梱しています。
- **アプリの起動**: 登録した呼び名で「〜を開いて」と頼むと、そのアプリを起動します。
- **フィードバック**: 返事を「よい答え」「よくない答え」で評価して記録できます。

C コンパイラとスクリプト言語は Brain 専用です。PC 版では使えません。

## モデル

| 名前 | 用途 |
|---|---|
| `v2` | 普段の会話 |
| `coderv1` | コード生成 |
| `v2flash` | 応答速度を優先した高速版 |

配布時点では `v2` が選択されています。

## 動作環境

- **Brain 版**: Windows CE ベースの SHARP Brain
- **PC 版**: 64 ビット版 Windows

第 4 世代の Brain は、SB5〜7 を除き、そのままではアプリを起動できない場合があります。

## インストール

### Brain

1. `brain AI v2` フォルダを、SD カードの `アプリ` フォルダにコピーします。
2. 百科事典を使う場合は、下記の辞書ファイルを `RAG` フォルダに置きます。
3. Brain のアプリ一覧から起動します。

### PC

`brain AI v2` フォルダ内の `brainai_pc.exe` を実行します。

## 辞書ファイル (kb.tsv)

百科事典の機能には、辞書ファイル `kb.tsv`（約 412MB）が必要です。
サイズが大きいため、このリポジトリには含めていません。

- **入手先**: Hugging Face リポジトリ [`yamada2wasabi/brain-ai-v2-preview`](https://huggingface.co/yamada2wasabi/brain-ai-v2-preview)
- **置き場所**: `brain AI v2/RAG/kb.tsv`（`AppMain.exe` と同じフォルダにも置けます）

辞書ファイルがなくても、百科事典の検索以外の機能は使えます。

## 使い方のヒント

- **画像の文字を読む**: 画像を `画像` フォルダに入れ、メニューの「画像の文字を読む」を選びます。
- **アプリを登録する**: `ショートカット/定義.txt` に、ファイル名と呼び名を書きます。書き方はファイル内の説明を参照してください。
- **フィードバックを残す**: 手順は `フィードバックの残し方.txt` を参照してください。

## 保存されるデータ

会話の記録、フィードバック、設定はアプリのフォルダ内に保存されます。

| 保存先 | 内容 |
|---|---|
| `chats` | 会話の記録 |
| `feedback` | 評価と、教えた正しい答え |
| `settings.txt` | 返事の長さや文字の大きさなどの設定 |

記録を消したいときは、該当するファイルを削除してください。

## 現在の制限

- AI の回答や OCR の結果には誤りが含まれることがあります。重要な内容は別の資料で確認してください。
- OCR の開発時の測定値は、正解率 92.5%、文字誤り率 11.88% です。
- C コンパイラの動作確認は Windows CE エミュレーターで行いました。
- OCR、画像認識、スクリプト言語は、Brain 実機での動作確認が完了していません。

## 同梱ソフトウェアと出典

- [TinyCC](https://bellard.org/tcc/)（C コンパイラ）
- [Lua](https://www.lua.org/) 5.4.7
- [QuickJS](https://bellard.org/quickjs/)（JavaScript）
- [mruby](https://mruby.org/)（Ruby）
- 百科事典のデータは、[Wikipedia](https://ja.wikipedia.org/)（CC BY-SA）の見出しと本文冒頭をもとに作成しています。

## 作者とライセンス

作者: **love-linux**
配布元: https://github.com/love-linux/brain-AI-preview

再配布するときは、作者名「love-linux」とこのリポジトリのリンクを必ず明記し、`NOTICE.txt` とライセンスのファイルを一緒に配布してください。

- **アプリ本体**（`AppMain.exe`、`AppMain_dbg.exe`、`brainai_pc.exe`）: [LICENSE-APP.txt](LICENSE-APP.txt)。無料で使え、改変していないものは再配布できます。改変版の配布には love-linux の許可が必要です。
- **モデルと辞書**（`v2`、`coderv1`、`v2flash`、`ocr.bin`、`kb.tsv`）: [CC BY-SA 4.0](https://creativecommons.org/licenses/by-sa/4.0/deed.ja) で公開しています。使うときは作者として「love-linux」の表示を残し、改変した場合は同じライセンスで公開してください。
- **TinyCC**: GNU Lesser General Public License（LGPL）2.1 以降。Brain 向けに改造したソースコードは [tinycc-brain](https://github.com/love-linux/tinycc-brain) で公開しています。
- **Lua / QuickJS / mruby**: それぞれ MIT ライセンスで配布されているものを同梱しています。
- 同梱ソフトウェアのライセンス本文は [THIRD-PARTY-LICENSES.txt](THIRD-PARTY-LICENSES.txt) にあります。
