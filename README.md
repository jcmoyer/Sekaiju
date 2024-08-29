# Sekaiju

This repository hosts an *unofficial* mono-repo version of Sekaiju, an open
source MIDI sequencer. You can find more information at the [project
website](https://openmidiproject.opal.ne.jp/Sekaiju_en.html).

This repository is *NOT* an official source and is *NOT* affiliated with
openmidiproject.

This repository differs from upstream in that it aims to provide an easy way to
build Sekaiju and its dependencies and to produce a distribution.

The `upstream` branch is a mirror of upstream without MSVC projects, docs, or
binaries. The sources are unmodified and this branch uses cmake to build
instead.

The `master` branch additionally includes the following QOL features:

- Ctrl+Up/Down transposes selected notes by an octave
- Shift+Up/Down transposes selected notes chromatically by one semitone
- Shift+Left/Right shifts selected notes by the current snap amount
- Alt+Up/Down transposes selected notes diatonically based on MIDI key
  signature events
- F vertically flips selected notes
- Shift+F horizontally flips selected notes
- Roland SC-55 instrument file is included as part of the distribution

# Building

Requires MSVC, MFC, ATL, and cmake.

To produce a complete working build of Sekaiju at `<path>`:

```
git clone git@github.com:jcmoyer/Sekaiju.git && cd Sekaiju
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build .
cmake --install . --prefix=<path>
```

# Steps for merging upstream

## Sekaiju

Download from https://openmidiproject.opal.ne.jp/Sekaiju_en.html.

Extract the folder to our root directory and remove the version number (e.g.
Sekaiju8.1 becomes Sekaiju).

## MIDIIO

Download from https://openmidiproject.opal.ne.jp/MIDIIOLibrary_en.html.

Extract the folder to our root directory and remove the suffix and version
number (e.g. MIDIIOLib8.0 becomes MIDIIO).

## MIDIDataLibrary

Download from https://openmidiproject.opal.ne.jp/MIDIDataLibrary_en.html.

Extract the folder to our root directory and remove the suffix and version
number (e.g. MIDIDataLib8.0 becomes MIDIData).

## MIDIClockLibrary

Download from https://openmidiproject.opal.ne.jp/MIDIClockLibrary_en.html.

Extract the folder to our root directory and remove the suffix and version
number (e.g. MIDIClockLib8.0 becomes MIDIClock).

## MIDIStatusLibrary

Download from https://openmidiproject.opal.ne.jp/MIDIStatusLibrary_en.html.

Extract the folder to our root directory and remove the suffix and version
number (e.g. MIDIStatus8.0 becomes MIDIStatus).

## MIDIInstrumentLibrary

Download from https://openmidiproject.opal.ne.jp/MIDIInstrumentLibrary_en.html.

Extract the folder to our root directory and remove the suffix and version
number (e.g. MIDIInstrument8.0 becomes MIDIInstrument).

## IniDataLibrary

Download from https://openmidiproject.opal.ne.jp/IniDataLibrary_en.html.

Extract the folder to our root directory and remove the suffix and version
number (e.g. IniDataLib8.1 becomes IniData).
