# Super Emerald audit coverage

The structural checker runs against all registered map data. This log records
manual source review separately. A map listed here still needs a ROM playtest.

## Kanto · Silph Co.

Reviewed the map events, their scripts and the post-occupation state set on
arrival in Kanto. The old occupation branches remain in the source, but the
regional initializer hides those trainers and skips the old cutscenes.

| Map directory under `data/maps` | Manual source review | ROM playtest |
| --- | --- | --- |
| `SilphCo_1F_Frlg` | Reception, stairs and elevator access | Pending |
| `SilphCo_2F_Frlg` | Thunder Wave tutor, door and trainer visibility | Pending |
| `SilphCo_3F_Frlg` | Employee, hidden trainer and door state | Pending |
| `SilphCo_4F_Frlg` | Employee, doors and item pickups | Pending |
| `SilphCo_5F_Frlg` | Employee, reports, Card Key and item pickups | Pending |
| `SilphCo_6F_Frlg` | Employees, trainer visibility and door state | Pending |
| `SilphCo_7F_Frlg` | Lapras gift and repeat dialogue, employees and skipped rival scene | Pending |
| `SilphCo_8F_Frlg` | Employee, scientist and door state | Pending |
| `SilphCo_9F_Frlg` | Rest area, historical healing branch and doors | Pending |
| `SilphCo_10F_Frlg` | Employee, trainer visibility and door state | Pending |
| `SilphCo_11F_Frlg` | President and secretary, Master Ball, later Porygon2 gift and skipped occupation finale | Pending |
| `SilphCo_Elevator_Frlg` | Menu, cancellation and return destinations for all 11 floors | Pending |

## All-map source pass

The sweep read 1,578 map files and inventoried 9,216 object events, 4,557
warps, 2,682 background events and 588 coordinate events. It checked that
direct named event scripts exist and searched all per-map scripts for premature
gift completion and inherited dialogue that credits the visitor with old events.
This coverage records source checks, with manual follow-up on the findings.

| Map directory | Finding reviewed | ROM playtest |
| --- | --- | --- |
| `CeladonCity_Condominiums_1F_Frlg` | Tea delivery in the legacy branch | Pending |
| `CeruleanCity_House5_Frlg` | Powder Jar delivery | Pending |
| `VermilionCity_PokemonCenter_1F_Frlg` | VS Seeker delivery | Pending |
| `DarkCave_NorthSide_hns` | BlackGlasses delivery | Pending |
| `FloaromaTown_House1_sinnoh` | Aerial Ace TM delivery | Pending |
| `HearthomeCity_Flat2_F2_sinnoh` | Shell Bell delivery | Pending |
| `HearthomeCity_PoffinHouse_sinnoh` | Pokéblock Case delivery | Pending |
| `PokemonMansion_MaidsRoom_sinnoh` | Soothe Bell delivery | Pending |
| `Route201_sinnoh` | Potion delivery | Pending |
| `MtCoronet_1F_TunnelRoom_sinnoh` | Visible Galactic trainers acknowledge the team's defeat | Pending |

The Route 116 Repeat Ball event was checked and already has a retry path.
Two Island's rescue dialogue belongs to a cutscene skipped by Kanto's
post-story initializer. Individual narrative review and ROM coverage are
still open outside the maps and cases recorded above.

## Dialogue continuity pass

Searched the text in all 1,528 per-map script files for references to the
visitor's identity, family and participation in earlier events. Checked the
state and event bindings of the flagged candidates before altering them.
This is a text sweep with targeted manual review, not individual certification
of every dialogue branch.

- Olivine Gym: Jasmine acknowledges the Johto League victory after her badge
  and gift checks. The Silver Wing can still be claimed if the bag was full.
- Mahogany hideout and the Rocket officer: the next lead is Proton's supplies
  on Five Island, with directions to Bill and the Vermilion ferry.
- Eterna Galactic Building: a grunt mentions the message from their old boss
  before Travis confirms who sent it.
- Mt. Coronet tunnel: the non-battling former grunt now appears as a hiker.
- Celadon condominiums, Three Island tunnel and Sevault Canyon: reachable
  conversations no longer assume earlier meetings, gifts or a Kanto hometown.
- Floaroma Meadow and Two Island: checked the original rescue dialogue against
  the imported storyline's flags. Their original scenes remain skipped.

## Door, movement and exterior lighting pass

- Veilstone Department Store: the exterior warp at (25, 30) uses metatile
  0x25C. Its animation now covers the 16×16 glass tile below the façade.
  The three sliding frames use the same palette as the closed door.
- Canalave arrival: the passenger spawns one tile north of Dawn. Both face
  each other directly before the welcome message.
- The source sweep resolved the labels referenced by 3,172 movement calls.
  This checks references, with manual follow-up on the Canalave arrival.
- Reviewed the palette sources and lighting flags for all 279 map headers
  classified as naturally lit exteriors and counted 40 light sprite events.
  One remaining loose sidecar belongs to the Goldenrod store roof. The roof
  shares the Department Store palettes and does not load that sidecar.
- Rechecked inherited dialogue about Pokétch features, correcting visible
  conversations in Canalave, Jubilife, Solaceon and the Resort Area.
- ROM playtesting remains pending for movement trajectories, door transitions,
  time changes and the appearance of each exterior.

## Transit maps with no local narrative events

Reviewed the listed rooms individually for local dialogue and event bindings. Each has an empty map script, no NPCs, coordinate or background events, and no shared event or script map. Each listed warp leads to a destination warp that points back. This is source coverage only; collision and in-ROM traversal remain untested.

- `BattlePark_Access`
- `DragonsDen_Entrance_hns`
- `EternaCity_GalacticBuilding_B1F_sinnoh`
- `Gate_Route40_hns`
- `IronIsland_1F_sinnoh`
- `JubilifeCity_Flat1_F3_sinnoh`
- `MagmaHideout_2F_3R`
- `MeteorFalls_StevensCave`
- `MtEmber_SummitPath_1F_Frlg`
- `MtEmber_SummitPath_3F_Frlg`
- `NavelRock_1F_Frlg`
- `NavelRock_B1F`
- `NavelRock_B1F_Frlg`
- `NavelRock_BasePath_B10F_Frlg`
- `NavelRock_BasePath_B11F_Frlg`
- `NavelRock_BasePath_B1F_Frlg`
- `NavelRock_BasePath_B2F_Frlg`
- `NavelRock_BasePath_B3F_Frlg`
- `NavelRock_BasePath_B4F_Frlg`
- `NavelRock_BasePath_B5F_Frlg`
- `NavelRock_BasePath_B6F_Frlg`
- `NavelRock_BasePath_B7F_Frlg`
- `NavelRock_BasePath_B8F_Frlg`
- `NavelRock_BasePath_B9F_Frlg`
- `NavelRock_Down01`
- `NavelRock_Down02`
- `NavelRock_Down03`
- `NavelRock_Down04`
- `NavelRock_Down05`
- `NavelRock_Down06`
- `NavelRock_Down07`
- `NavelRock_Down08`
- `NavelRock_Down09`
- `NavelRock_Down10`
- `NavelRock_Down11`
- `NavelRock_Entrance`
- `NavelRock_Fork`
- `NavelRock_Fork_Frlg`
- `NavelRock_SummitPath_2F_Frlg`
- `NavelRock_SummitPath_3F_Frlg`
- `NavelRock_SummitPath_4F_Frlg`
- `NavelRock_SummitPath_5F_Frlg`
- `NavelRock_Up1`
- `NavelRock_Up2`
- `NavelRock_Up3`
- `NavelRock_Up4`
- `Route226_Access_sinnoh`
- `SandgemTown_RivalHouse_F2_sinnoh`
- `SeafloorCavern_Room7`
- `SinnohVictoryRoad_1F_Room1_sinnoh`
- `SinnohVictoryRoad_1F_Room3_sinnoh`
- `SolaceonRuins_Room1_Southeast_sinnoh`
- `SolaceonRuins_Room2_Northeast_sinnoh`
- `SolaceonRuins_Room2_Southeast_sinnoh`
- `SolaceonRuins_Room3_Northwest_sinnoh`
- `SolaceonRuins_Room4_sinnoh`
- `SolaceonRuins_Room4_Southeast_sinnoh`
- `SolaceonRuins_Room5_sinnoh`
- `SolaceonRuins_Room5_Southwest_sinnoh`
- `SolaceonRuins_Room6_Northwest_sinnoh`
- `SolaceonRuins_Room6_sinnoh`
- `SolaceonRuins_Room6_Southeast_sinnoh`
- `VeilstoneCity_DepartmentStore_Roof_sinnoh`
