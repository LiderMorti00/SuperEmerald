#!/bin/sh
# Super Emerald: full Sinnoh import (one-time; see the notes in each script).
set -e
cd "$(dirname "$0")/../../.."
python3 tools/sfr/sinnoh/import_sections.py
python3 tools/sfr/sinnoh/import_tilesets.py
python3 tools/sfr/sinnoh/import_gfx.py
python3 tools/sfr/sinnoh/import_music.py
python3 tools/sfr/sinnoh/import_maps.py
python3 tools/sfr/sinnoh/gen_sinnoh_league.py
python3 tools/sfr/sinnoh/import_trainer_gfx.py
python3 tools/sfr/sinnoh/wire_build.py
python3 tools/sfr/sinnoh/gen_sinnoh_state.py
python3 tools/sfr/sinnoh/patch_sinnoh.py
python3 tools/sfr/sinnoh/wire_build.py
