/******************************************************************************/
/*                                                                            */
/*  MIDIClockライブラリ「はじめにお読みください」          (C)2002-2024 くず  */
/*                                                                            */
/******************************************************************************/

　このたびは、MIDIClockライブラリをダウンロードしていただき、又はお受け取りにな
っていただき、誠にありがとうございます。

　MIDIClockライブラリは、フリーでオープンソースの、MIDI時刻計測用ライブラリです。
このライブラリは、MIDIクロックのスタート・ストップ、テンポの取得・設定、経過ティ
ック数の取得・設定、経過時刻の取得・設定など、MIDIのタイミングを取り扱う上で必要
不可欠な機能を提供します。

【特徴】

1.多彩なタイムベースとテンポに対応。
　タイムベースはTPQNベース(分解能=1～32767)とSMPTE24ベース(24フレーム/秒)・SMPTE25
ベース(25フレーム/秒)・SMPTE29ベース(29.97フレーム/秒)・SMPTE30ベース(30フレーム
/秒)に対応し、TPQNベースの場合のテンポは1～60000000[μ秒/4分音符]に対応。これら
の設定値はリアルタイムに取得・変更できます。時刻は経過ティック値と経過ミリ秒値の
両方をリアルタイムに取得・設定できます。

2.高精度なティックジェネレータを搭載
　1ミリ秒単位のマルチメディアタイマーの採用、ティック計算誤差加算アルゴリズムの
採用により、高い精度を実現しています。

3.スレーブモードにも対応。
　自分自身で時刻を進行させるのではなく、MIDIタイミングクロックやSMPTE/MTCを認識
させることによって時刻を進行させるスレーブモードも搭載。外部機器をマスタークロッ
クとする機能をもったアプリケーションが製作できます。

【添付ファイル】

MIDIClock
├readme.txt                  はじめにお読みください(このファイル)
├license.txt                 ライセンス(原文・英語)
├MIDIClock.c                 Cソースファイル
├MIDIClock.h                 C/C++用ヘッダーファイル
├MIDIClock.def               C/C++用モジュール定義ファイル(dllを作るときに必要)
├MIDIClock.sln               Visual Studio 2022 Community 用ソリューションファイル
├MIDIClock.vcxproj           Visual Studio 2022 Community 用プロジェクトファイル
├MIDIClock.vcxproj.filter    Visual Studio 2022 Community 用プロジェクトファイル
├MIDIClock.vcxproj.user      Visual Studio 2022 Community 用プロジェクトファイル
├MIDIClock.bas               Visual Basic 4.0/5.0/6.0用インポートモジュール
├Debug
│├MIDIClockd.lib            オブジェクトライブラリモジュール(デバッグ用)(32bit)
│└MIDIClockd.dll            ダイナミックリンクライブラリ(デバッグ用)(32bit)
├Release
│├MIDIClock.lib             オブジェクトライブラリモジュール(リリース用)(32bit)
│└MIDIClock.dll             ダイナミックリンクライブラリ(リリース用)(32bit)
├.x64
│├Debug
││├MIDIClockd.lib          オブジェクトライブラリモジュール(デバッグ用)(64bit)
││└MIDIClockd.dll          ダイナミックリンクライブラリ(デバッグ用)(64bit)
│└Release
│　├MIDIClock.lib           オブジェクトライブラリモジュール(リリース用)(64bit)
│　└MIDIClock.dll           ダイナミックリンクライブラリ(リリース用)(64bit)
└docs
　├MIDIClock.html            公式ガイドブック
　├MIDIClock_master.gif      公式ガイドブックで使われている図
　├MIDIClock_slave.gif       公式ガイドブックで使われている図
　├MIDIClock_o01.gif         公式ガイドブックで使われている図
　├MIDIClock_o02.gif         公式ガイドブックで使われている図
　├MIDIClock_o02f.gif        公式ガイドブックで使われている図
　├MIDIClock_o04.gif         公式ガイドブックで使われている図
　├MIDIClock_o04f.gif        公式ガイドブックで使われている図
　├MIDIClock_o08.gif         公式ガイドブックで使われている図
　├MIDIClock_o08d.gif        公式ガイドブックで使われている図
　├MIDIClock_o16.gif         公式ガイドブックで使われている図
　├MIDIClock_o16f.gif        公式ガイドブックで使われている図
　├MIDIClock_o32.gif         公式ガイドブックで使われている図
　└MIDIDR02.gif              公式ガイドブックで使われている図


【使用方法】

・すべてのファイルを解凍してください。
・MIDIClock.hをVisualC++をインストールしたフォルダ内のincludeフォルダ内にコピーしてください。
・MIDIClock.libをVisualC++をインストールしたフォルダ内のlibフォルダ内にコピーしてください。
・MIDIClock.dll(32bit)とMIDIClockd.dll(32bit)ファイルをc:\windows\SysWOW64\内にコピーしてください。
・MIDIClock.dll(64bit)とMIDIClockd.dll(64bit)ファイルをc:\windows\System32\内にコピーしてください。
・MIDIClockライブラリを使用するソースでは、#include "MIDIClock.h"※を行ってください。
・MIDIClockライブラリを使用するプロジェクトでは、Visual Studio 2022をご使用の場合、
　「デバッグ(D)」-「(プロジェクト名)のプロパティ」から「(プロジェクト名)のプロパティページ」という
　ダイアログを表示させ、その中の「構成とプロパティ」の「リンカ」の「入力」の中に、
　「追加の依存ファイル」という項目があるので、そこにMIDIClockd.lib※又はMIDIClock.lib※を追加してください。
・アプリケーションを配布する際には、MIDIClock.dllをexeファイルと同じフォルダに添付してください。
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


