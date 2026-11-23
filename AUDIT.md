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

## Sinnoh Ribbon Syndicate

- `ResortArea_RibbonSyndicate_F1_sinnoh`: Read all five NPC scripts and checked the exterior and upstairs warp destinations. Corrected the six-tile offset in both axes for all five NPCs and three warps. Both exit tiles and the stair now coincide with the drawn doorway and stair.
- `ResortArea_RibbonSyndicate_F2_sinnoh`: Read all four NPC scripts, including the spa acceptance, refusal and repeat branches. Checked the return warp to the corrected first-floor stair. Both floors still need a ROM playtest.

## S.S. Aqua

Read the dialogue and event bindings of all eleven Aqua interiors together with the Johto initialization and cruise scripts. ROM traversal and trainer sight lines remain untested.

- `SSAqua_1F_hns`: boarding, crew, exit sailor, cabin destinations and departure announcement. The idle sailor now describes the route without announcing a departure.
- `SSAqua_B1F_hns`: passenger battles, crew and both stairs. The on-duty sailor no longer sends the player looking for a hidden crewmate.
- `SSAqua_CaptainsRoom_hns` and `SSAqua_RoomSSE_hns`: the captain and grandfather now have dialogue consistent with the skipped missing-child event.
- `SSAqua_PlayersRoom_hns`: bed, healing, arrival while sailing and corridor return.
- `SSAqua_RoomNW_hns`: restored Edward and Corey to walkable floor tiles inside the cabin. Checked their battles and the hidden sailor.
- `SSAqua_RoomNE_hns`, `SSAqua_RoomNNE_hns`, `SSAqua_RoomSE_hns`, `SSAqua_RoomSSW_hns` and `SSAqua_RoomSW_hns`: passenger introductions, defeat and post-battle dialogue, the twins' double battle and cabin exits. Sean and Lyle now speak naturally on either leg of the voyage.

## Shared events and Route 34 Day Care

Checked the event bindings and warp destinations of these rooms against the shared attendant, Rock Smash and Strength scripts. The Rusturf story update checks the current map; rocks on distant routes cannot advance that event. Multiplayer sessions and boulder puzzles still require runtime tests.

- `CanalaveCity_PokemonCenter_2F_sinnoh`
- `CelesticTown_PokemonCenter_2F_sinnoh`
- `FightArea_PokemonCenter_2F_sinnoh`
- `FloaromaTwon_PokemonCenter_2F_sinnoh`
- `HearthomeCity_PokemonCenter_2F_sinnoh`
- `JubilifeCity_PokemonCenter_2F_sinnoh`
- `MtEmber_RubyPath_1F_Frlg`
- `MtEmber_RubyPath_B1F_Frlg`
- `MtEmber_RubyPath_B1F_Stairs_Frlg`
- `MtEmber_RubyPath_B2F_Frlg`
- `MtEmber_RubyPath_B2F_Stairs_Frlg`
- `MtEmber_SummitPath_2F_Frlg`
- `OreburghCity_PokemonCenter_2F_sinnoh`
- `PokemonLeague_NorthPokemonCenter_2F_sinnoh`
- `PokemonLeague_SouthPokemonCenter_2F_sinnoh`
- `ResortArea_PokemonCenter_2F_sinnoh`
- `SeafloorCavern_Room2`
- `SeafloorCavern_Room5`
- `SeafloorCavern_Room8`
- `SnowpointCity_PokemonCenter_2F_sinnoh`
- `SnowpointTemple_B2F_sinnoh`
- `SolaceonTown_PokemonCenter_2F_sinnoh`
- `SunyshoreCity_PokemonCenter_2F_sinnoh`
- `SurvivalArea_PokemonCenter_2F_sinnoh`
- `TurnbackCave_Room1_sinnoh`
- `TurnbackCave_Room2_sinnoh`
- `TurnbackCave_Room3_sinnoh`
- `VeilstoneCity_PokemonCenter_2F_sinnoh`

Also read the local conversations and checked the gift attendant in `EternaCity_PokemonCenter_F2_sinnoh` and `SandgemTown_PokemonCenter_2F_sinnoh`. All five Sinnoh gift attendants now use the distribution visibility flag and refresh it on entry. A failed Eon Ticket delivery preserves eligibility.

In `Route34_DayCare_hns`, reviewed the four NPC bindings and the four encyclopedia signs. Separated the overlapping walking Pokémon and replaced the clerk’s unsupported Odd Egg offer.

## Johto approach to the League

- `Route26_hns` and `Route26North_hns`: checked the trainer bindings, badges and League dialogue, Gaven and Beth's registration and rematches, pickups and exits. Jake and Joyce have playable copies on the northern map. Beth's opponent is no longer named using the Hoenn rival placeholder.
- `Route26_House1_hns` and `Route26_House2_hns`: checked the healing conversation, both book prompts, the seven siblings' map bindings and the two house returns. The letter and four siblings' conversations no longer suggest an unimplemented reward. These four additional outdoor maps received a targeted dialogue check only.
- `Route27_hns` and `Route27_House_hns`: checked the border conversation, trainer and rematch branches, pickups, falls sign and cave and house destinations. The border greeting also fits a return visit. The TM37 explanation now accounts for types immune to sand damage.

## League gate, Route 28 and Tohjo Falls

- `ReceptionGate_hns`: checked the physical badge checkpoint, its forced step back, the three guards and the four destinations. The east guard specifies the Johto League. The officer acknowledges the returning Johto Champion and the open road to Viridian.
- `Route28_hns` and `Route28_House_hns`: checked the signs, wildlife, static encounter, pickup, house and exits. Restored the Flamethrower TM pickup and removed a promise of an unspecified gift from the celebrity's conversation.
- `TohjoFalls_Cavern_hns` and `TohjoFalls_GiovanniRoom_hns`: checked the Heart Scale, entrances, radio, absent Giovanni and seven breakable rocks. Each rock now has its own temporary visibility flag.
- A follow-up search located other item balls wired to empty scripts. Restored pickups with matching existing items on Route 32, at Lake of Rage, Union Cave B1F, Mt. Mortar 1F South, the Goldenrod store basement and underground storage, Ice Path 1F, Rocket Hideout B2F and Burned Tower B1F. These are targeted pickup checks. Imported move names without a corresponding TM in this build still need a design decision.

## Ice Path

- `IcePath_1F_hns`: reviewed the three pickups, two hidden items, alternating wildlife, the skipped Kimono Girl event and both outside exits.
- `IcePath_B1F_hns` and `IcePath_B2F_hns`: checked the puzzle signs, skip destination, pickups, Chien-Pao encounter and four pairs of boulder flags. Fixed Strength recognition for the Johto objects; landed boulders stay in place. The sign explains the holes and the puzzle shortcut waits for its warp.
- `IcePath_B3F_hns` and `IcePath_B4F_hns`: checked the alternating Delibird and Swinub, ten breakable rocks, hidden items, Never-Melt Ice and ladders. The party menu now recognizes the regional breakable rocks. Checked reciprocal destinations for all five floors. Solving the puzzle and interacting with the rocks in a ROM remain untested.

## Johto gym badges and guide dialogue

Cross-checked all eight gym leader map bindings against the eight badge-award scripts, the local guide and statue branches, and the first-battle team data. Imported victory flags were never set by these leaders. The local branches now use the badges already stored in existing saves.

- Violet, Azalea, Goldenrod, Ecruteak, Cianwood, Olivine, Mahogany and Blackthorn: checked guide advice and recognition after victory. Removed the obsolete Blackthorn guide branch sending players to the Dragon's Den to claim a badge already awarded in the gym.
- Cianwood Pokémon Center: checked the nurse, guide, passengers, bookshelf, clock, respawn and return warp. The guide recognizes the Storm Badge and the fisher no longer promises an unavailable Pokémon.

This pass covers badge and dialogue integration; it does not certify every movement in the gym puzzles. Playtesting before and after each victory remains pending.

The Sinnoh comparison covered the two plaque states at all eight gyms. Seven displayed the rival placeholder as a certified challenger regardless of story progress. Plaques now show the gym and leader on arrival, then the player's name after the corresponding Sinnoh badge. Sunyshore's leader and certified trainer list are on separate lines. This is targeted source coverage of the plaques.

## Moomoo Farm and multi-item rewards

- `Route39_Barn_hns` and `Route39_FarmHouse_hns`: checked the actual shared scripts bound to the twins, Miltank and both farmers, berry refusal, recovery after seven berries, milk sales, both house exits and repeat dialogue. The farmer's wife now remembers whether Leftovers have already been delivered when six bottles of milk will not fit.
- `Route39_hns`: checked the trainers, grazing Miltank, pickups, signs and the farm entrances. Headbutt advice now refers to eligible trees. The imported Drain Punch pickup still has no matching TM in this build.
- Targeted Kanto follow-up: the Pewter Museum curator and the elder in Lavender's Volunteer Pokémon House now resume their reward bundles at the first undelivered item. Previously completed quest values are unchanged. Script-level retry tests covered every item, repeated failure, successful completion and subsequent interaction; ROM testing remains pending.


## Route 38 and the Ecruteak gate

- `Route38_hns`: checked six trainers, Chad's registration and rematch branch, both twins' shared scripts, berries, visible and hidden items, signposts, connections and the gate warp. Olivia now reports the milk shortage before the seventh berry and the reopened shop afterwards.
- `Gate_EcruteakCity_Route38_hns`: checked the officer and both return warps. The officer recognizes the Hoenn title without assuming the protagonist was born there.

## Ecruteak dialogue and Johto stores

- Reviewed local dialogue and event bindings in Ecruteak's exterior, homes, theater, Pokémon Center, mart and tower offices. Updated the Lake of Rage reports, removed the theater reward rumor, and made the sage acknowledge the Fog Badge. Failed Dowsing Machine and Rainbow Wing deliveries can be retried.
- Restored shopping in six Johto marts whose clerks had a greeting or an empty inventory. The shared stock starts with essentials and expands after earning the Hive and Mineral Badges. This was a targeted clerk check outside Ecruteak.
- ROM verification remains pending for the shop menus and tower checkpoint.

## Burned Tower

- Reviewed both floors, including the hidden original-story NPCs, trainer dialogue, statue scripts, pickups, boulder, Chi-Yu and the stair and hole destinations.
- Followed the basement scene into the Raikou and Entei roamer registration and Suicune's Tin Tower visibility check. The Ecruteak witness now uses the same release flag: the first visit no longer starts with a report of a scene the player has yet to trigger. The scene still runs only once.

## Bellchime Trail and Tin Tower

- Reviewed Bellchime Trail and the ten Tin Tower maps, from the ground floor to the roof, including Morty's hidden scene, the guardians' dialogue, item and statue events, stair and teleport destinations, and the two active legendary encounters.
- Ho-Oh and Suicune now mark the encounter complete after a catch or victory. A loss does not consume either encounter. Visibility on return still follows the Rainbow Wing or Burned Tower requirements.
- Removed a sage's suggestion of an Unown side quest. Kept the tower legend and the clue about Suicune. The old off-map roof warp and hidden original-story actors remain outside the active route. Runtime testing of the climb and battles remains pending.

## Whirl Islands

- Reviewed the seven Whirl Islands maps from the surface entrances to Lugia's chamber, including the pickups and hidden items, Strength boulder, Tentacruel binding, hidden theater actors, and reciprocal warp destinations.
- Lugia still requires the Silver Wing. Defeat by Lugia keeps the encounter available on return, and victory or capture marks it complete. Battle and traversal remain pending in ROM.

## Route 41

- Read the ten swimmers' battle dialogue, checked the four cave entrances and their returns, and followed the paired whirlpool objects into the shared badge check and four movement branches. Confirmed that the Johto initializer hides the optional Tentacruel battles.
- Mathew now gives directions that match the cave entrances and their separate paths. George's challenge no longer suggests a Pokémon loan that his script cannot handle. Whirlpool movement still needs verification in ROM.

## Route 40

- Reviewed the swimmers, shore NPCs, rock and Krabby interactions, and links to Route 41, Olivine and the tournament gate. The youngster now points to the local World Tournament instead of Hoenn's Trainer Hill. Monica's dialogue matches the weekday family letter. The gate was already recorded in the transit-map pass.
