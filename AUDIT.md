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
