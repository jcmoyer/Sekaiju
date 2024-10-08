set(CMAKE_MFC_FLAG 2)

add_executable(Sekaiju WIN32)

# https://gitlab.kitware.com/cmake/cmake/-/issues/21202
target_compile_definitions(Sekaiju PRIVATE _AFXDLL _UNICODE UNICODE)
target_link_options(Sekaiju PRIVATE "/entry:wWinMainCRTStartup")

target_link_libraries(Sekaiju PRIVATE MIDIIO)
target_link_libraries(Sekaiju PRIVATE MIDIData)
target_link_libraries(Sekaiju PRIVATE MIDIClock)
target_link_libraries(Sekaiju PRIVATE MIDIStatus)
target_link_libraries(Sekaiju PRIVATE MIDIInstrument)
target_link_libraries(Sekaiju PRIVATE IniData)

target_sources(
    Sekaiju

    PRIVATE

    "src/Sekaiju.rc"

    "src/AboutDlg.cpp"
    "src/AutoSaveDlg.cpp"
    "src/ChildFrame.cpp"
    "src/ColorfulCheckListBox.cpp"
    "src/ColorfulComboBox.cpp"
    "src/ColorOptionPage.cpp"
    "src/ColorSelectComboBox.cpp"
    "src/common.c"
    "src/ControlChangeListBox.cpp"
    "src/EditBeatScanDlg.cpp"
    "src/EditBreakupAndTrillDlg.cpp"
    "src/EditChannelDlg.cpp"
    "src/EditDurationDlg.cpp"
    "src/EditInsertMeasureDlg.cpp"
    "src/EditKeyDlg.cpp"
    "src/EditQuantizeDlg.cpp"
    "src/EditRemoveMeasureDlg.cpp"
    "src/EditStrokeDlg.cpp"
    "src/EditTempoDlg.cpp"
    "src/EditTimeDlg.cpp"
    "src/EditTimeSmpDlg.cpp"
    "src/EditTrackDlg.cpp"
    "src/EditValueDlg.cpp"
    "src/EditVelocityDlg.cpp"
    "src/EventKindListBox.cpp"
    "src/EventListFrame.cpp"
    "src/EventListIndexPropertyView.cpp"
    "src/EventListIndexScaleView.cpp"
    "src/EventListOptionPage.cpp"
    "src/EventListPrintView.cpp"
    "src/EventListPropertyScaleView.cpp"
    "src/EventListScaleView.cpp"
    "src/FilePropertyDlg.cpp"
    "src/FontOptionPage.cpp"
    "src/GeneralOptionPage.cpp"
    "src/GraphKindListBox.cpp"
    "src/HistoryRecord.cpp"
    "src/HistoryUnit.cpp"
    "src/InplaceEdit.cpp"
    "src/InplaceListBox.cpp"
    "src/LanguageDlg.cpp"
    "src/MainFrame.cpp"
    "src/MetronomeDlg.cpp"
    "src/MIDIDeviceSheet.cpp"
    "src/MIDIInDevicePage.cpp"
    "src/MIDIInstDefDrumPage.cpp"
    "src/MIDIInstDefNormPage.cpp"
    "src/MIDIInSyncModePage.cpp"
    "src/MIDIOutDevicePage.cpp"
    "src/MIDIOutSyncModePage.cpp"
    "src/MIDISyncModeSheet.cpp"
    "src/MIDIThruPage.cpp"
    "src/MusicalScoreFrame.cpp"
    "src/MusicalScoreOptionPage.cpp"
    "src/MusicalScorePrintView.cpp"
    "src/MusicalScoreScaleView.cpp"
    "src/MusicalScoreTimeScaleView.cpp"
    "src/MusicalScoreTrackScaleView.cpp"
    "src/MusicalScoreTrackTimeView.cpp"
    "src/OptionSheet.cpp"
    "src/PianoRollFrame.cpp"
    "src/PianoRollKeyScaleView.cpp"
    "src/PianoRollKeyTimeView.cpp"
    "src/PianoRollOptionPage.cpp"
    "src/PianoRollPrintView.cpp"
    "src/PianoRollScaleView.cpp"
    "src/PianoRollTimeScaleView.cpp"
    "src/PianoRollVelScaleView.cpp"
    "src/PianoRollVelTimeView.cpp"
    "src/PropertyKeySignatureDlg.cpp"
    "src/PropertyMarkerDlg.cpp"
    "src/PropertyNoteDlg.cpp"
    "src/PropertyTempoDlg.cpp"
    "src/PropertyTimeSignatureDlg.cpp"
    "src/SekaijuApp.cpp"
    "src/SekaijuDoc.cpp"
    "src/SekaijuDocManager.cpp"
    "src/SekaijuDocTemplate.cpp"
    "src/SekaijuFileDlg.cpp"
    "src/SekaijuPreviewView.cpp"
    "src/SekaijuStatusBar.cpp"
    "src/SekaijuToolBar.cpp"
    "src/SekaijuView.cpp"
    "src/SelectVoiceDlg.cpp"
    "src/stdafx.cpp"
    "src/TextFile.cpp"
    "src/TrackListBox.cpp"
    "src/TrackListFrame.cpp"
    "src/TrackListModeScaleView.cpp"
    "src/TrackListOption1Page.cpp"
    "src/TrackListOption2Page.cpp"
    "src/TrackListPrintView.cpp"
    "src/TrackListScaleView.cpp"
    "src/TrackListTimeScaleView.cpp"
    "src/TrackListTrackModeView.cpp"
    "src/TrackListTrackScaleView.cpp"
    "src/TrackListTrackTimeView.cpp"

    "src/AboutDlg.h"
    "src/AutoSaveDlg.h"
    "src/ChildFrame.h"
    "src/ColorfulCheckListBox.h"
    "src/ColorfulComboBox.h"
    "src/ColorOptionPage.h"
    "src/ColorSelectComboBox.h"
    "src/common.h"
    "src/ControlChangeListBox.h"
    "src/EditBeatScanDlg.h"
    "src/EditBreakupAndTrillDlg.h"
    "src/EditChannelDlg.h"
    "src/EditDurationDlg.h"
    "src/EditInsertMeasureDlg.h"
    "src/EditKeyDlg.h"
    "src/EditQuantizeDlg.h"
    "src/EditRemoveMeasureDlg.h"
    "src/EditStrokeDlg.h"
    "src/EditTempoDlg.h"
    "src/EditTimeDlg.h"
    "src/EditTimeSmpDlg.h"
    "src/EditTrackDlg.h"
    "src/EditValueDlg.h"
    "src/EditVelocityDlg.h"
    "src/EventKindListBox.h"
    "src/EventListFrame.h"
    "src/EventListIndexPropertyView.h"
    "src/EventListIndexScaleView.h"
    "src/EventListOptionPage.h"
    "src/EventListPrintView.h"
    "src/EventListPropertyScaleView.h"
    "src/EventListScaleView.h"
    "src/FilePropertyDlg.h"
    "src/FontOptionPage.h"
    "src/GeneralOptionPage.h"
    "src/GraphKindListBox.h"
    "src/HistoryRecord.h"
    "src/HistoryUnit.h"
    "src/InplaceEdit.h"
    "src/InplaceListBox.h"
    "src/LanguageDlg.h"
    "src/MainFrame.h"
    "src/MetronomeDlg.h"
    "src/MusicalScoreFrame.h"
    "src/MusicalScoreOptionPage.h"
    "src/MusicalScorePrintView.h"
    "src/MusicalScoreScaleView.h"
    "src/MusicalScoreTimeScaleView.h"
    "src/MusicalScoreTrackScaleView.h"
    "src/MusicalScoreTrackTimeView.h"
    "src/OptionSheet.h"
    "src/PianoRollFrame.h"
    "src/PianoRollKeyScaleView.h"
    "src/PianoRollKeyTimeView.h"
    "src/PianoRollOptionPage.h"
    "src/PianoRollPrintView.h"
    "src/PianoRollScaleView.h"
    "src/PianoRollTimeScaleView.h"
    "src/PianoRollVelScaleView.h"
    "src/PianoRollVelTimeView.h"
    "src/PropertyKeySignatureDlg.h"
    "src/PropertyMarkerDlg.h"
    "src/PropertyNoteDlg.h"
    "src/PropertyTempoDlg.h"
    "src/PropertyTimeSignatureDlg.h"
    "src/Resource.h"
    "src/SAL.h"
    "src/SekaijuApp.h"
    "src/SekaijuDoc.h"
    "src/SekaijuDocManager.h"
    "src/SekaijuDocTemplate.h"
    "src/SekaijuFileDlg.h"
    "src/SekaijuPreviewView.h"
    "src/SekaijuStatusBar.h"
    "src/SekaijuToolBar.h"
    "src/SekaijuView.h"
    "src/stdafx.h"
    "src/targetver.h"
    "src/TextFile.h"
    "src/TrackListBox.h"
    "src/TrackListFrame.h"
    "src/TrackListModeScaleView.h"
    "src/TrackListOption1Page.h"
    "src/TrackListOption2Page.h"
    "src/TrackListPrintView.h"
    "src/TrackListScaleView.h"
    "src/TrackListTimeScaleView.h"
    "src/TrackListTrackModeView.h"
    "src/TrackListTrackScaleView.h"
    "src/TrackListTrackTimeView.h"
)

add_subdirectory("SekaijuRes")
