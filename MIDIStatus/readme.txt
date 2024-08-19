/******************************************************************************/
/*                                                                            */
/*  MIDIStatusライブラリ「はじめにお読みください」         (C)2002-2024 くず  */
/*                                                                            */
/******************************************************************************/

　このたびは、MIDIStatusライブラリをダウンロードしていただき、又はお受け取りに
なっていただき、誠にありがとうございます。

　MIDIStatusライブラリは、フリーでオープンソースの、MIDI音源の状態保持・参照用ラ
イブラリです。このライブラリは、MIDI音源の各鍵盤の押され具合、コントローラーやプ
ログラムナンバーやピッチベンドなどの状態、マスターボリューム・マスターリバーブ・
マスターコーラスなどの状態を記憶する構造体を管理し、いつでも状態を設定・参照する
ことができます。リアルタイムで状態を記録するには、MIDIStatusオブジェクトに対して
MIDIメッセージを与えるだけです。MIDIStatusオブジェクトは、MIDI1.0/GM/GM2/GS/XGで
定義されるほとんどのMIDIメッセージ(システムエクスクルーシブ含む)を認識できます。


【添付ファイル】

MIDIStatus
├readme.txt                  はじめにお読みください(このファイル)
├license.txt                 ライセンス(原文・英語)
├MIDIStatus.c                Cソースファイル
├MIDIStatus.h                C/C++用ヘッダーファイル
├MIDIStatus.def              C/C++用モジュール定義ファイル(dllを作るときに必要)
├MIDIStatus.sln              Visual Studio 2022 Community 用ソリューションファイル
├MIDIStatus.vcxproj          Visual Studio 2022 Community 用プロジェクトファイル
├MIDIStatus.vcxproj.filter   Visual Studio 2022 Community 用プロジェクトファイル
├MIDIStatus.vcxproj.user     Visual Studio 2022 Community 用プロジェクトファイル
├MIDIStatus.bas              Visual Basic 4.0/5.0/6.0用インポートモジュール
├Debug
│├MIDIStatusd.lib           オブジェクトライブラリモジュール(デバッグ用)(32bit)
│└MIDIStatusd.dll           ダイナミックリンクライブラリ(デバッグ用)(32bit)
├Release
│├MIDIStatus.lib            オブジェクトライブラリモジュール(リリース用)(32bit)
│└MIDIStatus.dll            ダイナミックリンクライブラリ(リリース用)(32bit)
├x64
│├Debug
││├MIDIStatusd.lib         オブジェクトライブラリモジュール(デバッグ用)(64bit)
││└MIDIStatusd.dll         ダイナミックリンクライブラリ(デバッグ用)(64bit)
│└Release
│　├MIDIStatus.lib          オブジェクトライブラリモジュール(リリース用)(64bit)
│　└MIDIStatus.dll          ダイナミックリンクライブラリ(リリース用)(64bit)
└docs
　├MIDIStatus.html           公式ガイドブック
　└MIDIStatus_Fig1-1-1.gif   公式ガイドブックで使われている図


【使用方法】

・すべてのファイルを解凍してください。
・MIDIStatus.hをVisualC++をインストールしたフォルダ内のincludeフォルダ内にコピーしてください。
・MIDIStatus.libをVisualC++をインストールしたフォルダ内のlibフォルダ内にコピーしてください。
・MIDIStatus.dll(32bit)とMIDIStatusd.dll(32bit)ファイルをc:\windows\SysWOW64\内にコピーしてください。
・MIDIStatus.dll(64bit)とMIDIStatusd.dll(64bit)ファイルをc:\windows\System32\内にコピーしてください。
・MIDIStatusライブラリを使用するソースでは、#include "MIDIStatus.h"※を行ってください。
・MIDIStatusライブラリを使用するプロジェクトでは、Visual Studio 2022をご使用の場合、
　「デバッグ(D)」-「(プロジェクト名)のプロパティ」から「(プロジェクト名)のプロパティページ」という
　ダイアログを表示させ、その中の「構成とプロパティ」の「リンカ」の「入力」の中に、
　「追加の依存ファイル」という項目があるので、そこにMIDIStatud.lib※又はMIDIStatus.lib※を追加してください。
・アプリケーションを配布する際には、MIDIStatus.dllをexeファイルと同じフォルダに添付してください。
・詳しくは、おーぷんMIDIぷろじぇくとの資料又はFAQのページを参照してください。
※パスはご使用の環境に合わせて記述してください。

【ライセンス】

　このライブラリは、GNU 劣等一般公衆利用許諾契約書(LGPL)に基づいて配布されます。
・あなたはこのライブラリを、LGPLに基づき、複製・転載・配布することができます。
・あなたはこのライブラリを改変することができ、それをLGPLに基づき配布することができます。
・あなたはこのライブラリのDLLを利用して(ダイナミックリンクに限る)、あなた独自の
　ライセンスのアプリケーションを製作・配布することができます。
・いずれの場合も作者に許可を得る必要はありません。
・このライブラリは全くの無保証です。
　このライブラリを使用した結果生じた損害につきまして作者は一切責任を負いません。
　あらかじめご了承ください。
※詳しくは、LGPLの日本語訳(http://www.opensource.gr.jp/lesser/lgpl.ja.html)をご参照ください。

【連絡先】

・メールアドレス(仮) ee65051@yahoo.co.jp
・プロジェクトホームページ https://openmidiproject.opal.ne.jp/

