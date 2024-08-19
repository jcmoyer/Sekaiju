/******************************************************************************/
/*                                                                            */
/*  『世界树8.1』请首先阅读                               (C)2002-2024  kuzu  */
/*                                                                            */
/******************************************************************************/

感谢您在百忙中下载了“世界树8.1”，非常感谢您的下载。这个文件描述“世界树8.1”的
特点，基本用法，注意事项等。请首先阅读本文件。此外，如果你想了解详细的操作方法，
请阅读docs文件夹里的Sekaiju_chs.pdf。

■特点

世界树是自由且开源的MIDI音序器软件。可以记录MIDI键盘上的演奏到电脑，在电脑上可以
作曲，而且用MIDI音源或合成器可以实时演奏MIDI音乐。因为可以编辑全类型的MIDI事件，
和有无限制的撤消和重做功能，这个软件也可以使用作为强大的MIDI编辑器。把每个MIDI通
道消息同时输入到分离轨道的实时输入功能也是好评。

・采用复数文件系统，所以可以同时打开多个MIDI数据，而且可以即刻切换演奏中的MIDI数据。
・有轨道列表窗口，钢琴卷窗口，事件列表窗口，乐谱窗口。
・每个窗口有打印预览功能和打印功能。
・一边儿放演奏乐曲，一边儿可以输入数据，编辑，保存等的操作。
・可以编辑全类型的MIDI事件，包括元事件和系统排他的事件。
・有无限制的撤消和重做功能。
・有把事件的轨道，时刻，键号码，力度，长短，值，信道号码等成批变更的编辑功能。
・有对准音符的时刻，碎裂音符和做颤音，扫描拍子和调整拍速度，挪动和弦的时刻的编辑功能。
・对应于可以做用户定义编辑功能的外部扩展程序SAL (Sekaiju Application Language)。
・TPQN格式对应于分辨率1到1920，SMPTE格式对应于分辨率1到255，可以转换基格式。
・可以读取/保存世界树序列文件(*.skj)。
・可以读取旧Cakewalk序列文件(*.wrk)。
・可以读取/保存Cherry序列文件(*.chy)。
・可以读取/保存标准MIDI文件(*.mid)格式0/1/2。
・可以读取/保存MIDICSV文件(*.csv)。
・可以读取洛奇MML文件(*.mmml)。
・有自动保存功能(1～120分钟间隔)。
・MIDI输入端口和MIDI输出端口，最大同时16个端口可以分别使用。
・有多轨道的同时输入可能的实时输入功能(与节拍器功能)。
・有CC#111循环功能，可以开始从乐曲的中间(RPG制作系统)。
・有loopStart-loopEnd循环功能，可以开始从乐曲的中间(FINAL FANTASY VII系统)。
・有智能演奏功能，可以正常演奏即使从乐曲的中间。
・有同步录音启动功能，可以开始记录在同一时间开始演奏。
・有MIDI同步功能，可以接收或者发送MIDI时钟。
・仪器定义文件是可相容的跟Cakewalk仪器定义文件(*.ins)。
・可以使用简单的，只解压ZIP文件。不用安装。
・用户界面和用户手册对应于日文和英文和中文。
・用户界面对应于 WindowsXP / Vista / 7 / 8.1 的主题。
・对应于 SMF with Lyrics (RP-026) 和 YAMAHA XF 格式。
・对应于 Unicode。


■工作条件

・OS　　　　　　：Microsoft Windows 7 / 8.1 / 10 / 11。64bit version only。
・CPU 　　　　　：Intel Core i3 以上 / AMD Ryzen 3 以上。
・存储器　　　　：4GB以上。
・硬盘　　　　　：100MB以上。
・显示器　　　　：1024×768像素或更高分辨率的全彩色显示器。
・打印机　　　　：A4以上打印机(可选项非必须)。
・MIDI音源　　　：外部MIDI音源或合成器。
・MIDI键盘　　　：外部MIDI键盘(可选项非必须)。
・其他　　　　　：声音环境(功放器・扬声器或耳机)。


■内容

Sekiaju8.1
├license.txt           许可证(文本)
├mfc140u.dll           MFC运行库(为Unicode)★
├mfc140chs.dll         MFC的中文资源DLL★
├mfc140enu.dll         MFC的英文资源DLL★
├mfc140jpn.dll         MFC的日文资源DLL★
├vcruntime140.dll      Visual Studio 2022 C/C++ 运行库★
├vcruntime1401.dll     Visual Studio 2022 C/C++ 运行库★
├MIDIIO.dll            动态链接库(MIDI消息输入输出)★
├MIDIData.dll          动态链接库(MIDI数据作成编辑)★
├MIDIClock.dll         动态链接库(MIDI时刻计测)★
├MIDIStatus.dll        动态链接库(MIDI音源状态管理)★
├MIDIInstrument.dll    动态链接库(MIDI乐器定义文件)★
├IniData.dll           动态链接库(Ini文件编辑)★
├Sekaiju.exe           世界树软件★
├Sekaiju.ini           世界树配置文件(文本)★
├Sekaiju.sln           Visual Studio 2022 Community 的解决方案文件
├Sekaiju.vcxproj       Visual Studio 2022 Community 的项目文件
├Sekaiju.vcxproj.filters  Visual Studio 2022 Community 的项目文件
├Sekaiju.vcxproj.user  Visual Studio 2022 Community 的项目文件
├SekaijuChs.dll        世界树的中文资源DLL★
├SekaijuEnu.dll        世界树的英文资源DLL★
├SekaijuJpn.dll        世界树的日文资源DLL★
├readme.txt            请首先阅读(日文)
├readme_en.txt         请首先阅读(英文)
├readme_ch.txt         请首先阅读(中文)
├src                   C/C++源文件・头文件・资源脚本夹
│├AboutDlg.cpp
│├AboutDlg.h
│├AutoSaveDlg.cpp
│├AutoSaveDlg.h
│├BeatScanDlg.cpp
│├BeatScanDlg.h
│├BreakupAndTrillScanDlg.cpp
│├BreakupAndTrillScanDlg.h
│├ChildFrame.cpp
│├ChildFrame.h
│├ColorfulCheckListBox.cpp
│├ColorfulCheckListBox.h
│├ColorfulComboBox.cpp
│├ColorfulComboBox.h
│├ColorOptionPage.cpp
│├ColorOptionPage.h
│├ColorSelectComboBox.cpp
│├ColorSelectComboBox.h
│├ControlChangeListBox.cpp
│├ControlChangeListBox.h
│├common.c
│├common.h
│├EditChannelDlg.cpp
│├EditChannelDlg.h
│├EditDurationDlg.cpp
│├EditDurationDlg.h
│├EditInsertMeasureDlg.cpp
│├EditInsertMeasureDlg.h
│├EditKeyDlg.cpp
│├EditKeyDlg.h
│├EditQuantizeDlg.cpp
│├EditQuantizeDlg.h
│├EditRemoveMeasureDlg.cpp
│├EditRemoveMeasureDlg.h
│├EditTempoDlg.cpp
│├EditTempoDlg.h
│├EditTimeDlg.cpp
│├EditTimeDlg.h
│├EditTimeSmpDlg.cpp
│├EditTimeSmpDlg.h
│├EditTrackDlg.cpp
│├EditTrackDlg.h
│├EditValueDlg.cpp
│├EditValueDlg.h
│├EditVelocityDlg.cpp
│├EditVelocityDlg.h
│├EventKindListBox.cpp
│├EventKindListBox.h
│├EventListFrame.cpp
│├EventListFrame.h
│├EventListIndexPropertyView.cpp
│├EventListIndexPropertyView.h
│├EventListIndexScaleView.cpp
│├EventListIndexScaleView.h
│├EventListOptionPage.cpp
│├EventListOptionPage.h
│├EventListPrintView.cpp
│├EventListPrintView.h
│├EventListPropertyScaleView.cpp
│├EventListPropertyScaleView.h
│├EventListScaleView.cpp
│├EventListScaleView.h
│├FilePropertyDlg.cpp
│├FilePropertyDlg.h
│├FontOptionPage.cpp
│├FontOptionPage.h
│├GeneralOptionPage.cpp
│├GeneralOptionPage.h
│├GraphKindListBox.cpp
│├GraphKindListBox.h
│├HistoryRecord.cpp
│├HistoryRecord.h
│├HistoryUnit.cpp
│├HistoryUnit.h
│├InplaceEdit.cpp
│├InplaceEdit.h
│├InplaceListBox.cpp
│├InplaceListBox.h
│├LanguageDlg.cpp
│├LanguageDlg.h
│├MainFrame.cpp
│├MainFrame.h
│├MetronomeDlg.cpp
│├MetronomeDlg.h
│├MIDIDeviceSheet.cpp
│├MIDIDeviceSheet.h
│├MIDIInDevicePage.cpp
│├MIDIInDevicePage.h
│├MIDIInstDefDrumPage.cpp
│├MIDIInstDefDrumPage.h
│├MIDIInstDefNormPage.cpp
│├MIDIInstDefNormPage.h
│├MIDIInSyncModePage.cpp
│├MIDIInSyncModePage.h
│├MIDIOutDevicePage.cpp
│├MIDIOutDevicePage.h
│├MIDIOutSyncModePage.cpp
│├MIDIOutSyncModePage.h
│├MIDISyncModeSheet.cpp
│├MIDISyncModeSheet.h
│├MIDIThruPage.cpp
│├MIDIThruPage.h
│├MusicalScoreFrame.cpp
│├MusicalScoreFrame.h
│├MusicalScoreOptionPage.cpp
│├MusicalScoreOptionPage.h
│├MusicalScorePrintView.cpp
│├MusicalScorePrintView.h
│├MusicalScoreTrackScaleView.cpp
│├MusicalScoreTrackScaleView.h
│├MusicalScoreTrackTimeView.cpp
│├MusicalScoreTrackTimeView.h
│├MusicalScaleView.cpp
│├MusicalScaleView.h
│├MusicalScoreTimeScaleView.cpp
│├MusicalScoreTimeScaleView.h
│├OptionSheet.cpp
│├OptionSheet.h
│├PianoRollFrame.cpp
│├PianoRollFrame.h
│├PianoRollKeyScaleView.cpp
│├PianoRollKeyScaleView.h
│├PianoRollKeyTimeView.cpp
│├PianoRollKeyTimeView.h
│├PianoRollOptionPage.cpp
│├PianoRollOptionPage.h
│├PianoRollPrintView.cpp
│├PianoRollPrintView.h
│├PianoRollScaleView.cpp
│├PianoRollScaleView.h
│├PianoRollTimeScaleView.cpp
│├PianoRollTimeScaleView.h
│├PianoRollVelScaleView.cpp
│├PianoRollVelScaleView.h
│├PianoRollVelTimeView.cpp
│├PianoRollVelTimeView.h
│├PropertyKeySignature.cpp
│├PropertyKeySignature.h
│├PropertyMarker.cpp
│├PropertyMarker.h
│├PropertyNote.cpp
│├PropertyNote.h
│├PropertyTempo.cpp
│├PropertyTempo.h
│├PropertyTimeSignature.cpp
│├PropertyTimeSignature.h
│├Resource.h
│├Sekaiju.rc
│├SekaijuApp.cpp
│├SekaijuApp.h
│├SekaijuDoc.cpp
│├SekaijuDoc.h
│├SekaijuDocManager.cpp
│├SekaijuDocManager.h
│├SekaijuDocTemplate.cpp
│├SekaijuDocTemplate.h
│├SekaijuFileDlg.cpp
│├SekaijuFileDlg.h
│├SekaijuPreviewView.cpp
│├SekaijuPreviewView.h
│├SekaijuStatusBar.cpp
│├SekaijuStatusBar.h
│├SekaijuToolBar.cpp
│├SekaijuToolBar.h
│├SekaijuView.cpp
│├SekaijuView.h
│├stdafx.cpp
│├stdafx.h
│├targetver.h
│├TextFile.cpp
│├TextFile.h
│├TrackListBox.cpp
│├TrackListBox.h
│├TrackListFrame.cpp
│├TrackListFrame.h
│├TrackListModeScaleView.cpp
│├TrackListModeScaleView.h
│├TrackListOption1Page.cpp
│├TrackListOption1Page.h
│├TrackListOption2Page.cpp
│├TrackListOption2Page.h
│├TrackListPrintView.cpp
│├TrackListPrintView.h
│├TrackListScaleView.cpp
│├TrackListScaleView.h
│├TrackListTimeScaleView.cpp
│├TrackListTimeScaleView.h
│├TrackListTrackModeView.cpp
│├TrackListTrackModeView.h
│├TrackListTrackScaleView.cpp
│├TrackListTrackScaleView.h
│├TrackListTrackTimeView.cpp
│└TrackListTrackTimeView.h
├res                   资源保存文件夹
│├Draw.cur            笔光标
│├Eraser.cur          橡皮光标
│├EvenList1.bmp       工具栏(事件列表)的按钮的画
│├Icon1.ico           世界树用图标2
│├Icon2.ico           世界树用图标2
│├Line.cur            直線光标
│├MainFrame.ico       主框架窗口的图标
│├MusicalScore1.bmp   工具栏(譜面)的按钮的画
│├Pan.cur             移动光标
│├PianoRoll1.bmp      工具栏(钢琴卷)的画
│├ResizeAll.cur       大小変更用光标(全方向)
│├ResizeNS.cur        大小変更用光标(上下方向)
│├ResizeWE.cur        大小変更用光标(左右方向)
│├Sekaiju.ico         主框架窗口的图标
│├SekaijuType.ico     孩子们框架窗口的图标
│├Select.cur          选择光标
│├SelectAdd.cur       追加选择光标
│├SizeAllCopy.cur     复写光标
│├Speaker.cur         试听光标
│├Toolbar1.bmp        工具栏1的按钮的絵
│├Toolbar2.bmp        工具栏2的按钮的絵
│├TrackList1.bmp      工具栏(轨道列表)的按钮的画
│└Zoom.cur            放大光标(垂直方向)
├SekaijuRes            世界树的语言别资源脚本
│├SekaijuEnu.rc       世界树的英文资源脚本(文本)
│├SekaijuJpn.rc       世界树的日文资源脚本(文本)
│├SekaijuChs.rc       世界树的中文资源脚本(文本)
│├SekaijuRes.rc       世界树的资源脚本(文本)
│├SekaijuRes.sln      世界树的资源Visual Studio 2022 Community 的解决方案文件
│├SekaijuRes.vcxproj  世界树的资源Visual Studio 2022 Community 的项目文件
│├SekaijuRes.vcxproj.filter  世界树的资源Visual Studio 2022 Community 的项目文件
│└SekaijuRes.vcxproj.user  世界树的资源Visual Studio 2022 Community 的项目文件
├instrument            乐器定义文件夹☆
│├GM1_GM2.ins         GM1/GM2乐器定义文件(文本)
│├Micrsoft_GS_Wavetable_Synth.ins Microsoft GS Wavetable Synth乐器定义文件(文本)☆
│├YAMAHA_MU1000_MU2000.ins YAMAHA MU1000/MU2000乐器定义文件(文本)
│├Roland_SC-8850.ins  Roland SC-8850乐器定义文件(文本)
│└KORG_KROME.ins      KORG KROME乐器定义文件(文本)
├docs                  用户手册文件夹
│├Sekaiju.odt         用户手册(日文)(为Libre Office)
│├Sekaiju.pdf         用户手册(日文)(为Adobe Reader)
│├Sekaiju_en.odt      用户手册(英文)(为Libre Office)
│├Sekaiju_en.pdf      用户手册(英文)(为Adobe Reader)
│├Sekaiju_chs.odt     用户手册(中文)(为Libre Office)
│└Sekaiju_chs.pdf     用户手册(中文)(为Adobe Reader)
├autosave              自动保存文件夹


　★：为了启动软件，是必不可少的(如果失去，则不能启动)。
　!注意! 由于Windows的设置，可能不显示DLL文件。
　explorer或my computer的「工具(T)」-「选项(O)...」的「显示」页面里，
　把「显示全部文件夹和文件」请设置开启。
　如果不显示扩展名，在相同页面里，把「不显示常用扩展名」请设置关闭。


■安装・启动方法

这个软件没有安装程序。你只要解压缩zip文件。

(1)请右点击Sekaiju8.1.zip，选择“属性”，复选“常规”的“安全：此文件来自其他计算机，
　　　　　可能被阻止以帮助保护该计算机。”的“解除锁定(&K)”

(2)请解压缩Sekaiju8.1.zip。
　!警告!　如果忘解压缩，则不能启动。
　!警告!　不要把程序放在c:\program files或c:\program files(x86)或c:\windows文件夹里，
　　　　　因为Windows有用户帐户控制(UAC)功能，设置文件等不能保存。
　　　　　请把程序放在上述以外的文件夹里。

(3)为了启动，请双击Sekaiju.exe。
　!警告!　不要启动从联网电脑上。
　!警告!　在最近的Windows上，由于"SmartScreen"功能，“Windows保护了PC”消息可能出来了，
　　　　　从互联网下载的exe文件可能无法启动。如果此消息出来了，通过一单击“详细信息”
　　　　　然后单击“运行”，就会启动。请注意，您可能在虚拟站点上下载了假冒产品。
　!警告!　启动之前，请务必解压缩zip文件。

(4)请设置MIDI输入设备，MIDI输出设备，MIDI乐器定义(通常)，MIDI乐器定义(鼓)。
　!警告!　如果忘记选择MIDI输出设备，声音不能出来。

(5)Cakewalk仪器定义文件(*.ins)是可用的。如果你使用别的音源，
  如果搜索跟“Cakewalk instrument definition file”，就可以发现大部分的仪器定义文件。
  为了追加仪器定义，把ins文件放在ins夹里，然后重新启动Sekaiju.exe。

■语言的变更方法

因为世界树在日本制作了，默认语言是日文。用户界面语言可以选择日文或英文或中文。
为了变更语言，有两个方法，(a)用世界树的菜单栏，(b)用文本编辑软件。

(a) 从设置(S)-语言(L)请打开语言对话框，选择语言，按确定，然后重新启动世界树。
　你也打开语言对话框，以按键盘的[Alt]+[S]→[Alt]+[L]。

(b) 用文本编辑软件请打开Sekaiju.ini，变更"UserInterface=Japanese"成
　"UserInterface=English"或"UserInterface=Chinese"，保存，然后启动Sekaiju.exe。


■卸载方法

这个软件没有卸载程序。你要只删除Sekaiju8.1文件夹。

■许可证

(1)这个软件基于MPL2.0(Mozilla Public License 2.0)条款发布了。

(2)这个软件没有任何保证。作者不承担任何责任。

(3)这个软件动态链接下面的动态链接库。
　・SekaijuJpn.dll       (c)2024 kuzu / 开源MIDI项目  许可证 = MPL2.0
　・SekaijuEnu.dll       (c)2024 kuzu / 开源MIDI项目  许可证 = MPL2.0
　・SekaijuChs.dll       (c)2024 kuzu / 开源MIDI项目  许可证 = MPL2.0
　・MIDIIO.dll           (c)2024 kuzu / 开源MIDI项目  许可证 = GNU LGPL
　・MIDIData.dll         (c)2024 kuzu / 开源MIDI项目  许可证 = GNU LGPL
　・MIDIClock.dll        (c)2024 kuzu / 开源MIDI项目  许可证 = GNU LGPL
　・MIDIStatus.dll       (c)2021 kuzu / 开源MIDI项目  许可证 = GNU LGPL
　・MIDIInstrument.dll   (c)2024 kuzu / 开源MIDI项目  许可证 = GNU LGPL
　・IniData.dll          (c)2024 kuzu / 开源MIDI项目  许可证 = GNU LGPL
　・vcruntime140.dll     (c)2022 Microsoft Corporation  许可证 = 非自由
　・vcruntime140_1.dll   (c)2022 Microsoft Corporation  许可证 = 非自由
　・mfc140u.dll          (c)2022 Microsoft Corporation  许可证 = 非自由
　・mfc140jpn.dll        (c)2022 Microsoft Corporation  许可证 = 非自由
　・mfc140enu.dll        (c)2022 Microsoft Corporation  许可证 = 非自由
　・mfc140chs.dll        (c)2022 Microsoft Corporation  许可证 = 非自由

　!注意! 这些DLL被包括在Sekaiju8.1文件里。
　!注意! 如果消除这些DLL，或如果使用不同版本的DLL，世界树不能启动。
　!注意! 其他的DLL(例：api-ms-crt-runtime-l1-1-0.dll等)被由Windows Update自动地提供了。
　       或，请手动地加载并安装 Visual C++ Redistributable Package (vc_redist.x64.exe)。


■更新历史

2007/12/31 Sekaiju0.1alpha (开发中版本) Release.

2008/03/31 Sekaiju0.2alpha (开发中版本) Release.

2008/07/26 Sekaiju0.3alpha (开发中版本) Release.

2008/08/14 Sekaiju0.4alpha (开发中版本) Release.

2008/08/23 Sekaiju0.5alpha (开发中版本) Release.

2008/10/04 Sekaiju0.6alpha (开发中版本) Release.

2008/11/03 Sekaiju0.7alpha (开发中版本) Release.

2008/12/13 Sekaiju0.8alpha (开发中版本) Release.

2008/12/20 Sekaiju0.9alpha (开发中版本) Release.

2008/12/27 Sekaiju1.0 Release.

2009/01/17 Sekaiju1.1 Release.

2009/07/05 Sekaiju1.2 Release.

2009/07/14 Sekaiju1.3 Release.

2009/09/06 Sekaiju1.4 Release.

2009/12/19 Sekaiju1.5 Release.

2010/01/03 Sekaiju1.6 Release.

2010/01/31 Sekaiju1.7 Release.

2010/02/02 Sekaiju1.7 Release again

2010/02/28 Sekaiju1.8 Release

2010/05/04 Sekaiju1.9 Release

2010/06/06 Sekaiju2.0 Release

2010/07/30 Sekaiju2.1 Release

2011/02/05 Sekaiju2.2 Release

2011/03/06 Sekaiju2.3 Release

2011/05/08 Sekaiju2.4 Release

2011/06/05 Sekaiju2.5 Release

2011/11/06 Sekaiju2.6 Release

2012/01/10 Sekaiju2.7 Release

2012/02/10 Sekaiju2.8 Relase

2012/03/04 Sekaiju2.9 Relase

2012/04/22 Sekaiju3.0 Release

2012/07/07 Sekaiju3.1 Release

2012/08/19 Sekaiju3.2 Release

2012/09/30 Sekaiju3.3 Release

2012/12/02 Sekaiju3.4 Release

2013/03/03 Sekaiju3.5 Release

2013/05/05 Sekaiju3.6 Release

2013/09/16 Sekaiju3.7 Release
・开发环境从Viual C++4.0过渡到Visual C++ 2008 Standard Edition SP1。
・用户界面增加了对WindowsXP/ Vista/ 7 /8.1的主题的支持。
・「文件(F)」-「打开(O)...」对话框和「文件(F)」-「保存为(A)...」对话框
　对应于Windows XP / Vista / 7 / 8.1的风格。 
・修正了程序错误，不寻常的字符显示在空字符串。
・用户手册的屏幕截图变成了Windows7的风格。

2013/11/10 Sekaiju3.8 Release
・在钢琴卷窗口的图形区域上，追加了曲线输入功能。
　拖移时，如果右键点击，就变化直线，二次曲线起点是水平，二次曲线终点是水平。
・追加了「编辑(E)...」-「挪动音符的时刻...」对话框。
　挪动音符的时刻功能检测同时发音的音符，音符时刻升序或降序顶替。
・「选项(O)...」-「MIDI设备和乐器...」对话框里追加了MIDIThru页，
　可以选择输出或没输出从每个输入端口来的MIDI消息。
・修正了程序错误，通过拍速度变更，拍子标记变更，调性标记变更，文字标记变更对话框设定时，
　即使没变更時刻，事件的序列被乱套了。
・修正了程序错误，实时输入时，第一节拍器的音没出来了。
・修正了程序错误，以半角空格结束名称的MIDI设备不能打开。
・修正了程序错误，Cherry序列文件(*.chy)载入错误。
・修正了程序错误，Cherry序列文件(*.chy)保存错误。
・更新了MIDIData库到版本2.9。

2013/11/19 Sekaiju3.9 Release
・修正了程序错误，不能拖移位置滚动条。

2014/05/25 Sekaiju4.0 Release
・对应了Unicode编码。文件名或者文本事件等可以使用全字码了。
・对应了下面的文本编码，可以在语言对话框中选择。 
　・874-Thai
　・932-Japanese Shift-JIS(日本語)
　・936-Chinese Simplified(简体中文)
　・950-Traditional Chinese(繁體中文)
　・1250-Central European
　・1251-Cyrillic
　・1252-Western Latin-1
　・1253-Greek
　・1254-Turkish
　・1255-Hebrew
　・1256-Arabic
　・1257-Baltic
　・1258-Vietnamese
　・1200-Unicode UTF-16LE
　・1201-Unicode UTF-16BE
・在每个文本事件等，可以指定四种类的文本编码。
　一旦指定了文本编码，就适用于同轨道上的随后的同种类的事件。
　如果没指定了文本编码，在语言对话框中指定的文本编码就被适用。
　"{@ UTF-16LE}"和"{@ UTF-16BE}"被保留了作为{0xFF，0xFE}和{0xFE，0xFF}在MIDI文件中。 
　・开头"{@LATIN}" : 1252-Western Latin-1
　・开头"{@JP}" : 932-Japanese Shift-JIS
　・开头"{@UTF-16LE}" : 1200-Unicode UTF-16LE
　・开头"{@UTF-16BE}" : 1201-Unicode UTF-16BE
・为了保存全字符，Sekaiju.ini的字符代码变更成UTF-16LE格式。
・修改了用户界面的字体。
　・用户界面=日文 : MS P Gothic > MS UI Gothic
　・用户界面=英文 : MS Sans Serif > Microsoft Sans Serif
・在选择项对话框中，追加了字体页，为数据显示和打印，可以使用更好的字体。
・修正了演奏结束的时候第二工具栏上的[时:分:秒:毫秒]和[小节:拍:滴答]显示错误。
・在钢琴卷窗口的键盘部上，如果一个键扩大了到超过12个像素，可以显示音符名。
・在钢琴卷窗口上，选取了很很短的音符事件，也可以扩展音长。
・追加了"编辑(E)"-"变更事件的拍速度..."对话框，可以一总更改拍速度事件的值。
・修正了CC#64(保持踏板)等控制变更的阈值成为在63和64之间。
・更新了MIDIIO库到版本1.1。
・更新了MIDIData库到版本3.1。
・更新了MIDIClock库到版本1.0。
・更新了MIDIStatus库到版本0.9。
・更新了MIDIInstrument库到版本0.7。

2014/06/08 Sekaiju4.1 Release
・修正了程序错误，在特定的环境中，属性页的布局打乱。
・追加了下面的文本编码，可以在语言对话框中选择。 
　・949-Korean

2014/09/07 Sekaiju4.2 Release
・修正了程序错误，在轨道列表窗口上，默认情况下，选择工具不能使用。

2014/11/23 Sekaiju4.3 Release
・修正了程序错误，轨道列表窗口或者事件列表窗口列表的txt/csv保存功能输出错误的文件。
・修正了写错误，从“录音”改为“实时输入”

2015/01/25 Sekaiju4.4 Release
・用户界面增加了中文版本。
・用户手册增加了中文版本。
・更新了msvcr90.dll到版本9.00.30729.6161.
・更新了mfc90.dll到版本9.00.30729.6161.
・更新了mfc90u.dll到版本9.00.30729.6161.
・更新了mfc90enu.dll到版本9.00.30729.6161.
・更新了mfc90jpn.dll到版本9.00.30729.6161.
・追加了mfc90chs.dll的版本9.00.30729.6161.

2015/05/04 Sekaiju4.5 Release
・增加支持Windows10 Insider Preview 10074。
・加强了标准MIDI文件(*.mid)的读取能。
・修正了程序错误，在乐曲的结束时候，SMPTE/MTC发送错误。
・更新了MIDIData库到版本3.2。

2016/01/17 Sekaiju4.6 Release
・修正了程序错误，"编辑-事件的值变更"为绝对指定使用时，弯音值变更成错的值。
・在事件列表上，追加了"移动一个事件上边儿"按钮和"移动一个事件下边儿"按钮。
・修正了程序错误，在事件列表上，当前焦点闪烁的程序错误。
・追加了"演奏中，一变更程序变更･控制变更･弯音･RPN･NRPN，就马上更新"的功能。
・修正了Sekaiju.ini文件的写出方法。
・修正了一些中文的翻译错误。

2016/04/17 Sekaiju4.7 Release
・支持Windows10。
・0-Windows Control Panel's ANSI Code Page 追加了作为默认文本编码。
・修正了一些中文的翻译错误。
・更新了MIDIIO库到版本1.1。
・更新了MIDIData库到版本3.3。

2016/05/08 Sekaiju4.8 Release
・修正了程序错误，文本事件等的文本编码指定是工作错误的。
・更新了MIDIData库到版本3.4。

2016/12/04 Sekaiju4.9 Release
・修正了程序错误，在事件列表上点击右侧区域比值3的时候世界树导致冻结错误。
・调整了钢琴卷窗口的滚动条移动速度。

2017/05/28 Sekaiju5.0 Release
・修正了程序错误，在"编辑-变更事件的时刻"，"插入小节"，"除去小节"，
　同时刻的事件的顺序每每串换的错误。

2017/12/17 Sekaiju5.1 Release
・修正了程序错误，在"编辑"-"碎裂音符和做颤音..."，最下的音符不做颤音的错误。
・修正了程序错误，在"拍子标记的属性"对话框确定时，种数/四分音符和三十二分音符数/四分音符设定错误。
・对应了于外部扩展程序SAL(世界树程序语言)。
・更新了MIDIData库到版本3.5。
・LGPL许可证变更了成MPL2.0。

2018/02/25 Sekaiju5.2 Release
・修正了程序错误，在演奏中插入或变更或删除拍速度事件，马上拍速度不被更新的在错误。
・在乐谱窗口，追加了连结线按钮。
・对应了于SAL的sendMIDI命令。

2018/04/15 Sekaiju5.3 Release
・追加了功能，在轨道列表窗口如果使用时刻+或键+或力度+，为标准MIDI文件(*.mid)保存的时候，把这个值可以适用于每个事件的功能。
・修正了程序错误，在轨道列表窗口，后变更输出端口，撤消和重做不能正常工作的错误。
・修正了程序错误，设置-选项-颜色对话框，每个颜色组合框不能打开的错误。
・追加了快捷键Ctrl+F1，为实施SAL。
・对应了于读取旧Cakewalk序列文件(*.wrk)。
・更新了MIDIData库到版本3.6。

2018/06/03 Sekaiju5.4 Release
・默认用户界面语言就自动认识了。
・追加了功能，主模键转移。
・修正了程序错误，在每个轨道变更键+，旧键音剩了的错误。
・修正了程序错误，在Windows高反差模式，每个窗口的左部分不会看的错误。
・修正了程序错误，项目网点的地址是错误。

2018/07/23 Sekaiju5.5 Release
・修正了程序错误，MIDI输入的时候，音符开{0x9n 0xkk 0x00}成乱码音符关{0x9n 0xkk 0x01}所以音符就不止的错误。
・在乐谱窗口，改进了比八分音符短音符的连旗的视图。
・在乐谱窗口，追加了填充功能和修剪功能。

2019/01/03 Sekaiju5.6 Release
・修正了程序错误，对音长是0的音符把音符时刻或长短变更功能使用的时候，间或导致崩溃的错误。
・更新了MIDIData库到版本3.7。

2019/05/19 Sekaiju5.7 Release
・追加了loopStart-loopEnd循环功能，可以开始从乐曲的中间(FINAL FANTASY VII系统)。
・对应了于读取洛奇MML文件(*.mmml)。
・修正了程序错误，在乐谱窗口上，写音符的时候，错误信道的声音听来的错误。
・更新了MIDIData库到版本3.8。
・修正了英语版的用户手册错误。

2019/11/17 Sekaiju5.8 Release
・在轨道列表窗口和事件列表窗口的右点击菜单，追加了"音色的搜索和选择"对话筐。
・在事件列表窗口的右点击菜单，追加了读取和保存系统排他的事件(*.syx)。
・扩大了文本系事件，音序器特有的事件，系统排他的事件的最大长度。
・修正了程序错误，异常元事件(例：长度0的端口前缀)读取的时候，导致崩溃的错误。
・修正了程序错误，试听工具使用的时候，同时刻的音符关和音符开会错误的顺序地送信的错误。
・更新了MIDIData库到版本3.9。

2020/01/05 Sekaiju5.9 Release
・修正了程序错误，在输入信道是n/a的轨道，不会实施输入系统排他消息的错误。
・修正了程序错误，在MIDI数据没打开的状态，变更主键盘移位的时候，导致崩溃的错误。
・修正了程序错误，在第一轨道是出力off(静音)的状态，演奏的时候，拍速度事件或loopEnd标记被无视了的错误。
・扩大了把系统排他的消息的最大输入/输出尺寸1024→4096bytes。
・对应了于UTF-8字符代码在文本关系事件(对应了{@UTF-8}标签)。
・对应了于用中点击普适卷屏。
・更新了MIDIIO库到版本1.2。
・更新了MIDIData库到版本4.0。

2020/11/29 Sekaiju6.0 Release
・修正了程序错误，把拍速度事件插入或变更或删除的时候，演奏拍速度不会自动地更新了的错误。
・为分辨率是960而拍子标记4/1的MIDI数据，用键盘你可以输入的最大滴答值被增加了到3839。
・更新了MIDIData库到版本4.1。
・更新了MIDIStatus库到版本1.0。

2020/12/31 Sekaiju6.1 Release
・在事件列表窗口，作为第四视面，新追加了控制变更列表框，CC#别地滤过成可能了。
・追加了危机按钮，这把音符开强制地发送于所有的端口的所有的通道的所有的键。
・修正了演奏停止的时候，把音符开强制地发送于发音中的所有的键。
・修正了"设置" - "选项" 对话框的"适用" 扣是无效了的程序错误。
・修正了"设置" - "选项" 对话框的的色选择组合框的色列表没表示了的程序错误。
・修正了如果复数的钢琴卷窗口或事件列表窗口或乐谱窗口被开了按确定的时候轨道列表框的所有复选框成复选了的程序错误。
・为了再演奏的时候RPN/NRPN的设置正确地复原，修正了把RPN/NRPN的设置不管系统排他的事件的独立地保持。
・更新了MIDIStatus库到版本1.1。

2021/08/15 Sekaiju7.0 Release
・开发环境移行了于Microsoft Visual Studio 2015 Community SP3。
・Windows SDK移行了于10.0.240.0 (c:\program files(x86)\Windows Kits\10\include\10.0.240.0\ucrt\)。
・Windows 64bit版本 EXE 准据了。
・采用了清晰字体。
・TPQN的最大分辨率成1920。
・在选项对话框，追加了复位按钮。
・在系统排他输入文本框中，即使输入错误的字符，世界树也会尽可能读取。
・修正了在Microsoft Print to PDF上打印的时候，世界树导致崩溃的错误。
・修正了把MIDI设备和仪器或MIDI同步模式或选项对话框显示的时候，世界树可能会导致崩溃的错误。
・更新了MIDIIO库到版本7.0。
・更新了MIDIData库到版本7.0。
・更新了MIDIClock库到版本7.0。
・更新了MIDIStatus库到版本7.0。
・更新了MIDIInstrument库到版本7.0。

2021/09/26 Sekaiju7.1 Release
・对应了于125%等的高DPI显示模式。
・修正了程序错误，插入小节或删除小节的时候，世界树导致崩溃的错误。
・更新了MIDIData库到版本7.1。

2021/10/24 Sekaiju7.2 Release
・追加了演奏时节拍器功能。
・修正了程序错误，节拍器声音立即消失或声音太小的程序错误。
・修正了程序错误，钢琴卷的音符键与鼠标y坐标不匹配的程序错误。
・修正了部分翻译。

2022/01/30 Sekaiju7.3 Release
・修正了程序错误，在乐谱窗口，自动页面更新无法正常工作的错误。
・修正了程序错误，在事件列表窗口中在第一个轨道，如果选择拍速度，拍子标记或调号标记，世界树可能会导致崩溃的错误。

2022/02/13 Sekaiju7.4 Release
・在轨道列表窗口・钢琴卷窗口・事件列表窗口・乐谱窗口，对应了于实时输入时候的实时显示更新。
・修正了程序错误，在钢琴卷窗口中，如果高DPI显示模式，音符键名无法正常显示的错误。


2022/04/17 Sekaiju7.5 Release
・修正了程序错误，发送或接受一个长系统排他的消息可能会导致崩溃的错误。
・修正了程序错误，复制或粘贴一个长MIDI事件可能会导致崩溃的错误。
・更新了MIDIIO库到版本7.1。
・更新了MIDIStatus库到版本7.1。

2022/11/06 Sekaiju7.6 Release
・支持了加载和保存*.midi扩展文件。
・修正了程序错误，在事件列表窗口中，无法正常地输入任意系统排他数据的问题。
・修正了程序错误，在加载或保存标准MIDI文件时，如果使用很大增量时间，可能会导致崩溃的错误。
・修正了程序错误，即使取消选中MIDIThru，系统排他消息也会通过的错误。
・更新了MIDIData库到版本7.2。

2023/01/09 Sekaiju7.7 Release
・修正了SMPTE25的MIDI数据在状态栏中显示为“SMPTE24”的错误。
・修正了事件列表窗口中显示多个轨道时，向上移动第一个事件导致崩溃的错误。
・修正了程序错误，在事件列表窗口中，如果序器特有的事件或系统排他的事件，在时间栏中输入“:”被禁用的错误。
・修正了程序错误，在事件列表窗口中，如果序器特有的事件或系统排他的事件，在编辑值时，使用Ctrl+Z/X/C/V/A被禁用的错误。
・修正了程序错误，在轨道列表窗口中，如果轨道的输出通道是“n/a”，修改CC#或程序变更时，则不会修改第一个事件，而是插入一个新事件的错误。
・修正了程序错误，在轨道列表窗口中，如果轨道的输出通道是“n/a”，插入CC#或程序变更时，事件的通道被坏的错误。

2023/02/12 Sekaiju7.8 Release
・追加了脚步输入模式。
・在自动保存对话框中，成为可选择一自动保存了，是否删除旧自动保存了的文件。

2023/07/02 Sekaiju7.9 Release

・修正了程序错误，在对话框中，通过Enter键确定不会工作的错误。
・修正了程序错误，在轨道列表窗口中，上移轨道或下移轨道会使历史记录损坏的错误。
・修正了程序错误，在轨道列表窗口中，打印包含文本相关事件的视图会导致崩溃的错误。

2024/01/21 Sekaiju8.0 Release
・开发环境移行了于Microsoft Visual Studio 2022 Community。
・更新了MIDIIO库到版本8.0。
・更新了MIDIData库到版本8.0。
・更新了MIDIClock库到版本8.0。
・更新了MIDIStatus库到版本8.0。
・更新了MIDIInstrument库到版本8.0。

2024/03/24 Sekaiju8.1 Release
・修正了程序错误，检测无效的CC#0和CC#32时世界树导致崩溃的错误。
・引入了IniData库，使启动和终止更快，更安全。


■联系信息

邮件地址(暂时): ee65051@yahoo.co.jp
项目网站: https://openmidiproject.opal.ne.jp/



