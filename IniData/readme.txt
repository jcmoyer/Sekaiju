/******************************************************************************/
/*                                                                            */
/*  IniDataライブラリ「はじめにお読みください」            (C)2002-2024 くず  */
/*                                                                            */
/******************************************************************************/

このたびは、IniDataライブラリをダウンロードしていただき、又はお受け取りになって
いただき、誠にありがとうございます。

『IniDataライブラリ』は、フリーでオープンソースの、iniファイル作成・編集用ライブ
ラリです。このライブラリは、*.iniファイルへの高速な入出力、スペース終了文字列の
正常な設定・取得、UTF-16LE(BOM付)・UTF8への対応、64bitへの対応を実現すべく、従来
の GetPrivateProfileString / GetPrivateProfileInt / WritePrivateProfileString の
代替関数を提供し、IniData_Loadで一括読み込み、IniData_Save
で一括保存する機能を有します。

本ライブラリは、C言語で記述されており、無制限のセクション数・項目数のiniファイル
に対応しております。簡便のため、コメントの読み込みと保存は省略しています。BOMなし
iniファイルは、ANSIではなくUTF-8として取り扱います。


【添付ファイル】

IniData
├readme.txt                はじめにお読みください(日本語)
├license.txt               ライセンス(原文・英語)
├PtrArray.c                可変長ポインタ配列用Cソースファイル
├PtrArray.h                可変長ポインタ配列用C/C++用ヘッダーファイル
├IniData.c                 Cソースファイル
├IniData.h                 C/C++用ヘッダーファイル
├IniData.def               C/C++用モジュール定義ファイル(dllを作るときに必要)
├IniData.sln               Visual Studio 2022 Community 用ソリューションファイル
├IniData.vcxproj           Visual Studio 2022 Community 用プロジェクトワークスペース
├IniIData.vcxproj.filter   Visual Studio 2022 Community 用プロジェクトワークスペース
├IniData.vcxproj.user      Visual Studio 2022 Community 用プロジェクトワークスペース
├Debug
│├IniDatad.lib            オブジェクトライブラリモジュール(デバッグ用)(32bit)
│└IniDatad.dll            ダイナミックリンクライブラリ(デバッグ用)(32bit)
├Release
│├IniData.lib             オブジェクトライブラリモジュール(リリース用)(32bit)
│└IniData.dll             ダイナミックリンクライブラリ(リリース用)(32bit)
├x64
│├Debug
││├IniDatad.lib          オブジェクトライブラリモジュール(デバッグ用)(64bit)
││└IniDatad.dll          ダイナミックリンクライブラリ(デバッグ用)(64bit)
│└Release
│　├IniData.lib           オブジェクトライブラリモジュール(リリース用)(64bit)
│　└IniData.dll           ダイナミックリンクライブラリ(リリース用)(64bit)
└docs
　└IniData.html            公式ガイドブック(日本語)

【使用方法】

・すべてのファイルを解凍してください。
・IniData.hをVisualC++をインストールしたフォルダ内のincludeフォルダ内にコピーしてください。
・IniData.libをVisualC++をインストールしたフォルダ内のlibフォルダ内にコピーしてください。
・IniData.dll(32bit)とIniDatad.dll(32bit)ファイルをc:\windows\SysWOW64\内にコピーしてください。
・IniData.dll(64bit)とIniDatad.dll(64bit)ファイルをc:\windows\System32\内にコピーしてください。
・IniDataライブラリを使用するソースでは、#include "IniData.h"※を行ってください。
・IniDataライブラリを使用するプロジェクトでは、Visual Studio 2022をご使用の場合、
　「デバッグ(D)」-「(プロジェクト名)のプロパティ」から「(プロジェクト名)のプロパティページ」という
　ダイアログを表示させ、その中の「構成とプロパティ」の「リンカ」の「入力」の中に、
　「追加の依存ファイル」という項目があるので、そこにIniDatad.lib※又はIniData.lib※を追加してください。
・アプリケーションを配布する際には、IniData.dllをexeファイルと同じフォルダに添付してください。
※パスはご使用の環境に合わせて記述してください。

【ライセンス】

・このライブラリは、GNU 劣等一般公衆利用許諾契約書(LGPL)に基づいて配布されます。
・このライブラリは全くの無保証です。
・このライブラリを使用した結果生じた損害につきまして作者は一切責任を負いません。
　あらかじめご了承ください。
※詳しくは、LGPLの日本語訳(http://www.opensource.gr.jp/lesser/lgpl.ja.html)をご参照ください。

【連絡先】

・メールアドレス(仮) ee65051@yahoo.co.jp
・プロジェクトウェブサイト https://openmidiproject.opal.ne.jp/

