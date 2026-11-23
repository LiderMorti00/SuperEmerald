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

## Olivine Lighthouse

- Read the lighthouse trainers' dialogue and checked Huey's rematch, the item bindings, Amphy, the hidden Jasmine scene and the active Iron Crown encounter. The lighthouse staff and visitors now agree that Amphy has recovered before the player arrives in Johto. Jasmine's current gym duties also match the revised dialogue.
- Checked the port's active clerk binding and Jasmine arrival hook. The imported Swagger pickup still has no matching TM. Lighthouse traversal and the arrival scene remain pending in ROM.

## Olivine harbor

- Reviewed both port maps, including their shared doorway, sailor destination menu, hidden Oak and Sabrina scenes, fishing conversations and Jasmine's first-arrival hook. The dock fisherman now gives the Slateport destination before the Johto League and the Vermilion route after the same flag that unlocks the sailing option. Arrival movement and boarding remain pending in ROM.

## Olivine homes and café

- Reviewed the three houses and the café, including both fishing-rod responses, the neighbor's shared dialogue, the siblings, the sailors and the hidden Jasmine scene. Tim no longer uses an unset species buffer, the sailor explains Strength without promising a gift, and the angler checks that the Good Rod was delivered before giving fishing advice.

## Olivine exterior and Pokémon Center

- Reviewed the exterior and Center events, signs, NPCs, building links, healing and respawn. The radio fan recognizes the actual Kanto League flag. Her greeting no longer offers an Aurora Ticket without enabling the ferry; Cozmo handles that ticket and its ferry unlock.
- Replaced the inert Charge Beam pickup with Shock Wave, a supported Electric TM. The Center fisher now describes the café sailor's advice consistently.

## Cianwood exterior, houses and pharmacy

- Reviewed the exterior, three houses and pharmacy. Checked the house returns, signs, smashable rocks, hidden construction NPC and links to the gym, Center and Safari Zone route.
- The pharmacist acknowledges Amphy's recovery, Kirk talks about his Shuckle without offering a loan, and the island advice identifies the badge that gates whirlpool crossings.

## Cianwood to the Safari Zone

- Read and checked the gate, Cliff Edge Cave, Routes 47 and 48, and Embedded Tower. Traced the gate and cave exits, four paired trainers, Route 47 pickups, shared wildlife scripts and the hidden Rayquaza encounter.
- The gate gives the route numbers and explains the Safari Balls. The cave visitor describes the ladders. The tower historian stays available independently of the imported Viridian Gym flag. Runtime traversal remains pending.

## Full narrative pass: Kanto, Sevii Islands, Johto and Sinnoh

Every map directory ending in `_Frlg` (410), `_hns` (242) and `_sinnoh` (401) was dumped with
`/tmp/se/dump.py`, which applies the regional world-state initializers
(`se_postgame.inc`, `se_johto_state.inc`, `se_sinnoh_state.inc`), drops objects whose hide flag
those initializers set, prunes script branches decided by known flags and variables, skips
coordinate events whose trigger variable can no longer match, and prints every text that a
visible NPC, sign or trigger can still show.

Coverage, stated precisely:

- 828 maps produced output (306 Kanto and Sevii, 201 Johto, 321 Sinnoh); 756 of them show at
  least one text (272, 182 and 302). The other directories have no visible event in the
  post-story state. An earlier version of this section said 849; that was an addition error.
- Read in full: NPC, sign, item-ball and trigger text in the post-story state.
- Not read in full: trainer battle text, which was filtered by story keywords; scenes hidden in
  the post-story state (story cutscenes behind flags the initializers set); Hoenn, where only Super
  Emerald additions and text naming another region's places were checked.
- This pass does not replace the per-map tracking table above: maps still marked Pending there
  stay pending for runtime checks (travel, NPC movement, music, lighting).
- Runtime tested in a built ROM: Goldenrod GAME CORNER clerk and the Celestic elder's HM Surf.

Fixed in this pass:

- Kanto: the Viridian GYM, Oak's Sinnoh-starter and Shiny Charm lines now match the HGSS
  league (Lance is CHAMPION, Red waits on Mt. Silver, three regions conquered). Blue no longer
  mentions a Cinnabar meeting that does not happen. Fuchsia's GYM guide, lass and Safari
  warden refer to Janine. Lorelei and Agatha are described as former ELITE FOUR members, Lance
  as CHAMPION. Present-tense Rocket references in Cerulean, Route 4, Lavender, Vermilion,
  Saffron's letter, Pewter, Silph 5F/8F, Mt. Moon and the S.S. Anne now describe the past. The
  Game Corner signs no longer call it the Rocket Game Corner.
- Cerulean robbed house: the hiker now gives TM28 (the grunt who returned it is hidden).
- Two Island: the shop starts with its full stock (`VAR_MAP_SCENE_TWO_ISLAND` = 4), and Lostelle
  no longer greets the visitor as her rescuer. Kanto state version 6.
- Five Island: the meadow boy, fisher and landowner thank the CHAMPION once the warehouse step
  of the Rocket quest is done.
- Vermilion: the S.S. Anne old man and the Snorlax notice match the docked ship and the clear
  road. Saffron NPCs no longer mention a Viridian contest hall, the Power Plant machine part or
  the Copycat house being replaced by the station.
- Johto: Azalea (charcoal kiln, Kurt's granddaughter), Mahogany (Pokémon Center, shop, house,
  gramps), Lake of Rage, Route 43 and the Radio Tower 3F now match the cleared Slowpoke Well,
  Gyarados and Radio Tower events. Rocket lines stay while the matching quest step is active.
  Bill's mother, the Goldenrod beauty, the name rater's TV news, the flower shop, Violet's
  Sudowoodo rumor, Elm's wife, the New Bark neighbor, Blackthorn's cooltrainer and Meara on
  Mt. Silver were rewritten. The Goldenrod coin clerk now says GOLDENROD GAME CORNER instead of
  Mauville.
- Sinnoh: Mt. Coronet and Galactic HQ grunt trainers are hidden after the story
  (`FLAG_SN_HIDE_SP_GRUNT1`); the tunnel room keeps the reformed trainers written in the
  earlier pass. Charon no longer stands in the HQ control room while he hides in the
  warehouse. The Galactic speech hall is hidden and its flags set; `FLAG_SN_GALACTIC_LEFT_LAKE_VALOR`
  is set so HQ staff use their post-story lines. Sinnoh state version 5.
- Sinnoh: the Celestic elder gives HM SURF without the hidden Cyrus battle. The Mt. Coronet 2F
  Looker double is now a hiker who gives the Black Flute. Eterna, Floaroma, Galactic HQ, Route
  210 café, Route 215 gate, Route 206 (Dawn's father), Oreburgh, Twinleaf, Solaceon Ruins and
  Spring Path NPCs were rewritten for the post-story state. Placeholder words from Platinum
  ("a that") were replaced in Jubilife TV, Veilstone, Solaceon, Route 208 and Turnback Cave.
  The Route 208 Berry Master points to Floaroma instead of Rustboro, and the coin seller shared
  by Celadon and Veilstone no longer names Celadon.

Checked in ROM: Goldenrod coin clerk and Celestic elder gift. `make check-se` reports 0
problems and no changed text exceeds the 216-pixel message box.

### Follow-up review fixes

- HM gifts added by Super Emerald in Sinnoh (Celestic elder's Surf, Jasmine's Waterfall in
  Sunyshore, Riley's Strength on Iron Island) now check `VAR_RESULT` after `giveitem` and only set
  the received flag when the item was actually given; otherwise the bag-full message shows and the
  NPC offers it again.
- Oak's Sinnoh-starter line now names the sixteen BADGES of JOHTO and KANTO separately from the
  journey that started in HOENN.
- Coverage figures above corrected (828 maps with output, not 849) and the limits of the pass
  written out.


## Regression pass after dae2e36217

ROM: built from dae2e36217 plus this commit's changes. Each test starts a new game with
`/tmp/mktest.py`, which places the player on the map and sets the listed flags and variables
in `NewGameInitData`. The regional world state then runs as it does on arrival. No older
save was available, so updating an existing save is untested.

### Accessibility classifications

- Ice Path B4F: the "no warp leads here" note was wrong. The reference search missed the
  warps in B2F and B3F. Fixed in the table and ROM-tested in both directions.
- Mt. Silver Moltres room: the same search error. It is reached from the Waterfall Room by
  SURF and has no visible event. Code only.
- A fresh search of every warp, connection and script reference finds no other map marked
  unreachable that has a way in. Lake Valor (drained) and Lake Verity (low water) are only
  referenced by wild encounter data. TestMap1/2 are not in `map_groups.json`, so they are
  never built.
- Kanto and Sevii: the only maps marked unreachable are the 25 S.S. Anne maps. Each has a
  single row in the review log, written as unreachable, and the log keeps no history, so it
  cannot show which maps were counted as reviewed in the earlier "330 reviewed / 2
  unreachable" report. The 23-map difference matches the S.S. Anne set. The cause is the
  Kanto state (`VAR_MAP_SCENE_VERMILION_CITY` = 3, `FLAG_HIDE_SS_ANNE`) together with the
  pier trigger described in the table. ROM: walking down the pier opens the SEAGALLOP menu.

### Results

| Test | Setup | Steps | Result |
|---|---|---|---|
| Ice Path B2F↔B4F | B2F (15,15) | Right onto the ladder, step off, back on | OK in both directions |
| Ice Path B3F↔B4F | B3F (13,8) | Right onto the ladder, step off, back on | OK in both directions |
| Vermilion pier | (23,31), Kanto state | Down onto the pier | Ticket check, then the SEAGALLOP menu; no S.S. Anne |
| Rocket step 6, full bag | VAR_SE_ROCKET_QUEST 6, Giovanni beaten, POKé BALLS pocket full | Talk twice | "BAG is full" both times, quest stays at 6, Giovanni stays |
| Rocket step 6 | same, bag not full | Talk | MASTER BALL received, farewell, Giovanni leaves |
| Two Island shop | Kanto state, Hoenn CHAMPION | Talk, Buy | "Distant lands" greeting, full stock (ULTRA, REPEAT, TIMER BALL, drinks, LAVA COOKIE) |
| Sinnoh League door | 0 SINNOH badges, before the fix | Walk north | **Bug**: walked straight into AARON's room |
| Sinnoh League door | 7 badges (no ICICLE, BEACON owned), after the fix | Talk to the guards | "You haven't obtained all the BADGES." |
| Sinnoh League door | 8 badges, after the fix | Talk to the guards | Guards step aside, "go forth" |
| WILL, first visit | VAR_MAP_SCENE_POKEMON_LEAGUE 1 | Talk | "Allow me to introduce myself" |
| WILL, rematch | + FLAG_SE_KANTO_COMPLETE | Talk | "So you've returned" |
| AARON, first visit | none | Talk | First-visit greeting |
| AARON, rematch | FLAG_SE_SINNOH_LEAGUE_CLEARED | Talk | "You're back!" |
| Unova starter trio | party full + boxes with 0 / 1 / 2 / 3 free slots | Talk | 0, 1, 2: "need room for three", nothing given. 3: all three given |
| Night, Seven Island | clock 23:00 | Enter and leave the Center, wait 65 s | Night tint outdoors, none indoors; Center windows and door stay lit (pixel count) |
| Night, Veilstone Dept. Store | clock 23:00 | Enter and leave | Glass door stays lit before and after (pixel count) |
| Vermilion → Canalave | JOHTO and CANALAVE tickets, Johto League | Sailor menu → CANALAVE | Boards the S.S. AQUA with the Canalave announcement |
| S.S. AQUA arrival | cruise state 3, destination 4, first Sinnoh arrival | Talk to the door sailor | Disembarks at Canalave, DAWN's welcome scene plays |

### Fixed in this pass

- Sinnoh League: the door guards now stand in front of the door until they let the player
  through, as in Ever Grande. Before, nothing blocked the door.
- Sinnoh gyms can be beaten in any order, so the following now count badges
  (`GetSinnohBadgeCount`) instead of testing one leader's badge:
  - the League guards (all eight)
  - the stock of the generic Sinnoh marts (1, 3 and 5 badges)
  - the Sandgem, Jubilife, Oreburgh and Floaroma marts
  - the Jubilife and Twinleaf NPCs
  - the Sunyshore Center "eight badges" line
- Gym text no longer states Platinum's badge counts, which were wrong both for this badge
  order and for any free order. This covers Gardenia, Maylene, Fantina, Byron, Volkner and
  the Canalave and Sunyshore guides. The texts also no longer promise obedience levels:
  obedience and field moves follow the Hoenn badges.

### Notes and pending

- No map sets `night_music`, so the music is the same by day and night everywhere. This is
  not a regression.
- At night, the windows on the Veilstone Dept. Store's front do not light up; only the glass
  door does (no `.pla` entry for those colors).
- Pending, not run in ROM:
  - loading an older save (none available)
  - Hoenn League first visit and rematch (Emerald scripts, unchanged)
  - walking a full 90-step crossing (the step counter is shared with the S.S. TIDAL code,
    which was read)
  - the Sinnoh mart tiers by badge count (code only)
  - Giovanni's battle itself (the test team lost; the reward was tested with the battle
    flag set)

## Map-by-map branch audit (Johto, Kanto, Sinnoh)

Each map was traced from its objects, signs, trainers and transition/coord events through local and shared scripts. Every branch was checked for its condition, what sets it, and what the speaker knows at that point (first visit, return, rematch, quest in progress, save/load, regional travel order).

Status: **complete** = all reachable branches reviewed; **no events** = no visible event in any state; **unreachable** = no warp reaches it in this game. No map is left partial or pending.

ROM tests run: Goldenrod Dept. Store clerk, Goldenrod Radio Tower lottery, Celestic Town Surf, Rocket Hideout B4F barrier, Route 213 footstep house.

| Region | complete | no events | unreachable |
|---|---|---|---|
| Johto | 205 | 35 | 2 |
| Kanto | 307 | 78 | 25 |
| Sinnoh | 328 | 71 | 2 |

### Johto

| Map | Status | Notes |
|---|---|---|
| AzaleaTown_Gym_hns | complete |  |
| AzaleaTown_House1_hns | complete |  |
| AzaleaTown_KurtsHouse_hns | complete | wall clock sign shares Hoenn clock script (SET_WALL_CLOCK always set): only shows clock |
| AzaleaTown_Mart_hns | complete |  |
| AzaleaTown_PokemonCenter_hns | complete |  |
| AzaleaTown_hns | complete |  |
| BellchimeTrail_hns | complete |  |
| BlackthornCity_Gym_hns | complete |  |
| BlackthornCity_House1_hns | complete |  |
| BlackthornCity_House2_hns | complete |  |
| BlackthornCity_House3_hns | complete | MOVE DELETER and MOVE RELEARNER were text stubs -> wired to real services (HEART SCALE) |
| BlackthornCity_Mart_hns | complete |  |
| BlackthornCity_PokemonCenter_hns | complete |  |
| BlackthornCity_hns | complete | gym boy congratulated you on beating CLAIR before the battle -> badge branch |
| BurnedTower_1F_hns | complete |  |
| BurnedTower_B1F_hns | complete | beasts-release scene on first visit |
| CherrygroveCity_House1_hns | complete |  |
| CherrygroveCity_House2_hns | no events | only object hidden by state flag (guide gent) |
| CherrygroveCity_House3_hns | complete |  |
| CherrygroveCity_Mart_hns | complete |  |
| CherrygroveCity_PokemonCenter_hns | complete |  |
| CherrygroveCity_hns | complete |  |
| CianwoodCity_hns | complete |  |
| CianwoodGym_hns | complete |  |
| CianwoodHouse1_hns | complete |  |
| CianwoodHouse2_hns | complete |  |
| CianwoodHouse3_hns | complete |  |
| CianwoodPokecenter_hns | complete |  |
| CianwoodShop_hns | complete |  |
| CliffEdgeCave_hns | complete |  |
| CliffEdgeGate_hns | complete |  |
| DarkCave_NorthSide_hns | complete |  |
| DarkCave_SouthSide_hns | complete |  |
| DragonsDen_Cavern_hns | complete |  |
| DragonsDen_Entrance_hns | no events |  |
| DragonsDen_Shrine_hns | complete |  |
| EcruteakCity_Gym_hns | complete | Morty Rainbow Wing branch read |
| EcruteakCity_House1_hns | complete |  |
| EcruteakCity_House2_hns | complete |  |
| EcruteakCity_Mart_hns | complete |  |
| EcruteakCity_PokemonCenter_hns | complete | radio-signal line now depends on Rocket quest step 1 |
| EcruteakCity_SageOffice1_hns | complete |  |
| EcruteakCity_SageOffice2_hns | complete |  |
| EcruteakCity_Theater_hns | complete |  |
| EcruteakCity_hns | complete |  |
| EmbeddedTower_hns | no events | RAYQUAZA object hidden (it lives in HOENN) |
| Gate_AzaleaTown_IlexForest_hns | complete |  |
| Gate_EcruteakCity_Route38_hns | complete |  |
| Gate_EcruteakCity_Route42_hns | complete |  |
| Gate_GoldenrodCity_Route35_hns | complete | Randy asked you to deliver a POKéMON (no follow-up in game) -> reworded |
| Gate_IlexForest_Route34_hns | complete |  |
| Gate_MahoganyTown_Route43_hns | complete |  |
| Gate_NationalPark_hns | complete | bug contest flow read |
| Gate_Route29_Route46_hns | complete |  |
| Gate_Route31_VioletCity_hns | complete |  |
| Gate_Route40_hns | no events |  |
| Gate_Route43_hns | no events | Rocket toll gate objects hidden by state flags |
| Gate_RuinsOfAlph_Route32_hns | complete |  |
| Gate_RuinsOfAlph_Route36_hns | complete |  |
| GoldenrodCity_BikeShop_hns | complete |  |
| GoldenrodCity_BillsHouse_hns | complete |  |
| GoldenrodCity_DepartmentStoreBasement_hns | complete |  |
| GoldenrodCity_DepartmentStoreElevator_hns | complete | floor panel sign had no script (showed engine test message) -> panel text |
| GoldenrodCity_DepartmentStore_1F_hns | complete |  |
| GoldenrodCity_DepartmentStore_2F_hns | complete |  |
| GoldenrodCity_DepartmentStore_3F_hns | complete |  |
| GoldenrodCity_DepartmentStore_4F_hns | complete |  |
| GoldenrodCity_DepartmentStore_5F_hns | complete | TM lady only said 'Oh, your POKéMON…' while others say she gives TMs -> gives RETURN/FRUSTRATION by friendship (new flag 0x32F5) |
| GoldenrodCity_DepartmentStore_6F_hns | complete | trade NPC stub showed 'That isn't a [empty]' -> text |
| GoldenrodCity_DepartmentStore_7F_hns | complete |  |
| GoldenrodCity_FlowerShop_hns | complete |  |
| GoldenrodCity_GameCorner_hns | complete | prize/coin checks used the KANTO coin-case flag; all Game Corner checks now accept the COIN CASE item |
| GoldenrodCity_Gym_hns | complete | statue said GOLDENROD TOWN -> CITY |
| GoldenrodCity_House1_hns | complete | NAME RATER was a text stub -> wired to the real name rater script |
| GoldenrodCity_House2_hns | complete | MOVE DELETER asked yes/no with no service -> wired to the real move deleter |
| GoldenrodCity_House3_hns | complete |  |
| GoldenrodCity_PokemonCenter_hns | complete |  |
| GoldenrodCity_RadioTower_1F_hns | complete | LOTTERY clerk was a stub -> real daily lottery (own intro text; clerk object moved to local id 2 so the animation targets him) |
| GoldenrodCity_RadioTower_2F_hns | complete | BUENA asked for a password with no system -> text says the show is on a break |
| GoldenrodCity_RadioTower_3F_hns | complete | 'about 400 kinds' -> over a thousand (matches Route 35 gate) |
| GoldenrodCity_RadioTower_4F_hns | complete |  |
| GoldenrodCity_RadioTower_5F_hns | complete | Archer step 3 battle/reward read |
| GoldenrodCity_TrainStation_hns | complete |  |
| GoldenrodCity_UndergroundEntrance_hns | complete |  |
| GoldenrodCity_UndergroundStorage_hns | complete | Ariana step 2 |
| GoldenrodCity_UndergroundSwitches_hns | complete |  |
| GoldenrodCity_UndergroundTunnel_hns | complete | HAIRCUT BROTHERS offered a paid service with no script -> fully booked text |
| GoldenrodCity_hns | complete | cooltrainer talked about 'that man in black' before any Rocket appeared -> rumor line at quest step 0 |
| IcePath_1F_hns | complete |  |
| IcePath_B1F_hns | complete |  |
| IcePath_B2F_hns | complete |  |
| IcePath_B3F_hns | complete |  |
| IcePath_B4F_hns | complete | Reached from B2F (16,15) and B3F (14,8); both return warps lead back. NEVERMELTICE ball, PROTEIN and CARBOS hidden items, 10 smashable rocks (both warps connect without Rock Smash). ROM-tested: B2F→B4F→B2F and B3F→B4F→B3F. Earlier "unreachable" came from a reference search that missed these warps. |
| IlexForest_hns | complete |  |
| LakeOfRageLowTide_hns | no events |  |
| LakeOfRage_House1_hns | complete | guru promised power but gave nothing -> now gives TM HIDDEN POWER once (flag 0x32F6, bag-full check) |
| LakeOfRage_House2_hns | complete |  |
| LakeOfRage_hns | complete | red GYARADOS object visible while Lois says it is gone -> hidden on transition; Petrel step 1 read |
| MahoganyTown_Gym_hns | complete |  |
| MahoganyTown_House1_hns | complete |  |
| MahoganyTown_PokemonCenter_hns | complete |  |
| MahoganyTown_Shop_hns | complete |  |
| Mahoganytown_hns | complete | RAGECANDYBAR merchant asked 'Want one?' with no sale -> real yes/no purchase (300, money and bag checks) |
| MtMortar_1F_North_hns | complete |  |
| MtMortar_1F_South_hns | no events |  |
| MtMortar_2F_hns | complete |  |
| MtMortar_B1F_hns | complete | Kiyo challenged to a battle that never happens -> text now postpones it |
| MtSilver_1F_ItemRoom_hns | no events |  |
| MtSilver_1F_MoltresRoom_hns | no events | Reached from MtSilver_1F_WaterfallRoom (13,4), across water (needs SURF). MOLTRES is hidden by the Johto state (`FLAG_J_HIDE_MOLTRES`); Kanto keeps its MOLTRES on Mt. Ember. Code only, not ROM-tested. Earlier "unreachable" was the same search error. |
| MtSilver_1F_WaterfallRoom_hns | no events |  |
| MtSilver_2F_hns | no events |  |
| MtSilver_3F_hns | complete |  |
| MtSilver_MountainSide_hns | no events |  |
| MtSilver_Outside_hns | complete |  |
| MtSilver_PokemonCenter_hns | complete |  |
| MtSilver_Snow_hns | no events |  |
| MtSilver_SummitDay_hns | complete |  |
| NationalPark_BugContest_hns | complete | contest flow via data/scripts/bug_contest.inc |
| NationalPark_Normal_hns | complete | Jack '92 kinds of TMs' -> 50 (game has 50) |
| NewBarkTown_House1_hns | complete |  |
| NewBarkTown_House2_hns | complete |  |
| NewBarkTown_Lab_hns | complete |  |
| NewBarkTown_PlayersHouse_1F_hns | complete | ORO's mom said he had left while he waits outside (state 0) -> branch |
| NewBarkTown_PlayersHouse_2F_hns | complete |  |
| NewBarkTown_hns | complete |  |
| OlivineCity_Cafe_hns | complete |  |
| OlivineCity_Gym_hns | complete | Jasmine badge/SILVER WING/after-league read |
| OlivineCity_House1_hns | complete |  |
| OlivineCity_House2_hns | complete |  |
| OlivineCity_House3_hns | complete |  |
| OlivineCity_Lighthouse_hns | complete |  |
| OlivineCity_Mart_hns | complete |  |
| OlivineCity_PokemonCenter_hns | complete |  |
| OlivineCity_PortInside_hns | complete | arrival scene + ship menu |
| OlivineCity_PortOutside_hns | complete |  |
| OlivineCity_hns | complete |  |
| ReceptionGate_hns | complete | edited by the user; read only |
| RocketHideout_B1F_hns | complete |  |
| RocketHideout_B2F_hns | complete |  |
| RocketHideout_B3F_hns | complete | Archer+Ariana step 4 double battle, LARVITAR reward (party/PC full check) |
| Route26North_hns | complete |  |
| Route26_House1_hns | complete |  |
| Route26_House2_hns | complete |  |
| Route26_hns | complete |  |
| Route27_House_hns | complete |  |
| Route27_hns | complete |  |
| Route28_House_hns | complete |  |
| Route28_hns | complete |  |
| Route29_hns | complete |  |
| Route30_House_hns | complete |  |
| Route30_MrPokemonsHouse_hns | complete |  |
| Route30_hns | complete |  |
| Route31_hns | complete |  |
| Route32_PokemonCenter_hns | complete |  |
| Route32_hns | complete | ROAR man said 'NOW TAKE THIS!' and gave nothing -> TM ROAR once (flag 0x32F7); Peter assumed the VIOLET badge -> generic intro |
| Route33_hns | complete |  |
| Route34_DayCare_hns | complete |  |
| Route34_hns | complete | day-care man egg branches read |
| Route35_hns | complete |  |
| Route36_hns | complete |  |
| Route37_hns | complete |  |
| Route38_hns | complete | Olivia branches on MOOMOO quest |
| Route39_Barn_hns | complete | MOOMOO feeding 0..7 |
| Route39_FarmHouse_hns | complete | wife gives LEFTOVERS then MOOMOO MILK x6 (bag-full checks), states 7/9/8 |
| Route39_hns | complete |  |
| Route40_hns | complete |  |
| Route41_hns | complete |  |
| Route42_hns | complete |  |
| Route43_hns | complete |  |
| Route44_hns | complete |  |
| Route45_hns | complete |  |
| Route46_hns | complete |  |
| Route47_hns | complete |  |
| Route48_hns | no events | wild POKEMON objects only |
| RuinsOfAlph_B1F_hns | complete |  |
| RuinsOfAlph_Lab_hns | complete | fossil revival states 0/1/2 read |
| RuinsOfAlph_Outside_hns | complete | STEVEN quest step 0->1 |
| RuinsOfAlph_PuzzleAndRewardChambers_hns | complete |  |
| RuinsOfAlph_WordsRoom1_hns | no events |  |
| RuinsOfAlph_WordsRoom2_hns | no events |  |
| RuinsOfAlph_WordsRoom3_hns | no events |  |
| RuinsOfAlph_WordsRoom4_hns | no events |  |
| SSAqua_1F_hns | complete | cruise states 0..3 and 4 destinations |
| SSAqua_B1F_hns | complete |  |
| SSAqua_CaptainsRoom_hns | complete |  |
| SSAqua_PlayersRoom_hns | complete |  |
| SSAqua_RoomNE_hns | complete |  |
| SSAqua_RoomNNE_hns | complete |  |
| SSAqua_RoomNW_hns | complete |  |
| SSAqua_RoomSE_hns | complete |  |
| SSAqua_RoomSSE_hns | complete |  |
| SSAqua_RoomSSW_hns | complete |  |
| SSAqua_RoomSW_hns | complete |  |
| SafariZoneGate_PokemonCenter_hns | complete | starter-trio gifts could give 1-2 of 3 and later repeat -> room for 3 checked first (new special ScriptHasRoomForThreeMons; also fixes the 4 other trio maps) |
| SafariZoneGate_SafariZoneEntrance_hns | complete | safari fee/ball/box-full and early exit read; blender signs |
| SafariZoneGate_hns | complete | vitamin guru is a real mart |
| SafariZone_Enterance_hns | no events |  |
| SafariZone_Low_Left_hns | no events |  |
| SafariZone_Low_Mid_hns | complete |  |
| SafariZone_Low_Right_hns | no events |  |
| SafariZone_Top_Left_hns | no events |  |
| SafariZone_Top_Mid_hns | no events |  |
| SafariZone_Top_Right_hns | complete |  |
| SlowpokeWell_B1F_hns | complete | Proton step 0 battle/reward |
| SlowpokeWell_B2F_hns | complete |  |
| SproutTower_1F_hns | complete | sage promised an HM at the top -> elder's test |
| SproutTower_2F_hns | complete |  |
| SproutTower_3F_hns | complete | ELDER LI announced a battle that never happens -> he sees the CHAMPION's bond; Neal no longer mentions an HM |
| TestMap1_hns | unreachable | debug map |
| TestMap2_hns | unreachable | debug map |
| TinTower_1F_hns | complete |  |
| TinTower_2F_hns | complete |  |
| TinTower_3F_hns | complete |  |
| TinTower_4F_hns | complete |  |
| TinTower_5F_hns | no events |  |
| TinTower_6F_hns | no events |  |
| TinTower_7F_hns | complete |  |
| TinTower_8F_hns | complete |  |
| TinTower_9F_hns | complete |  |
| TinTower_RoofDay_hns | complete | HO-OH |
| TohjoFalls_Cavern_hns | no events |  |
| TohjoFalls_GiovanniRoom_hns | complete |  |
| UnionCave_1F_hns | complete |  |
| UnionCave_B1F_hns | complete |  |
| UnionCave_B2F_hns | complete |  |
| VictoryRoadKanto_1F_hns | no events |  |
| VictoryRoadKanto_B1F_hns | no events |  |
| VictoryRoadKanto_B2F_hns | no events |  |
| VioletCity_Gym_hns | complete |  |
| VioletCity_House1_hns | complete |  |
| VioletCity_House2_hns | complete |  |
| VioletCity_Mart_hns | complete |  |
| VioletCity_PokemonCenter_hns | complete |  |
| VioletCity_TrainerSchool_hns | complete |  |
| VioletCity_hns | complete |  |
| WhirlIslands_1F_hns | no events |  |
| WhirlIslands_B1F_Inner_hns | no events |  |
| WhirlIslands_B1F_hns | no events |  |
| WhirlIslands_B2F_hns | no events |  |
| WhirlIslands_B3F_hns | no events |  |
| WhirlIslands_Descent_hns | no events |  |
| WhirlIslands_LugiaChamber_hns | complete | LUGIA |

### Kanto

| Map | Status | Notes |
|---|---|---|
| BattleColosseum_2P_Frlg | complete |  |
| BattleColosseum_4P_Frlg | complete |  |
| BirthIsland_Exterior_Frlg | complete |  |
| BirthIsland_Harbor_Frlg | complete |  |
| CeladonCity_Condominiums_1F_Frlg | complete |  |
| CeladonCity_Condominiums_2F_Frlg | complete |  |
| CeladonCity_Condominiums_3F_Frlg | complete |  |
| CeladonCity_Condominiums_RoofRoom_Frlg | complete |  |
| CeladonCity_Condominiums_Roof_Frlg | complete |  |
| CeladonCity_DepartmentStore_1F_Frlg | complete |  |
| CeladonCity_DepartmentStore_2F_Frlg | complete |  |
| CeladonCity_DepartmentStore_3F_Frlg | complete |  |
| CeladonCity_DepartmentStore_4F_Frlg | complete |  |
| CeladonCity_DepartmentStore_5F_Frlg | complete |  |
| CeladonCity_DepartmentStore_Elevator_Frlg | complete |  |
| CeladonCity_DepartmentStore_Roof_Frlg | complete |  |
| CeladonCity_Frlg | complete | Woman: 'new GAME CORNER' -> fixed |
| CeladonCity_GameCorner_Frlg | complete |  |
| CeladonCity_GameCorner_PrizeRoom_Frlg | complete |  |
| CeladonCity_Gym_Frlg | complete |  |
| CeladonCity_Hotel_Frlg | complete |  |
| CeladonCity_House1_Frlg | complete |  |
| CeladonCity_PokemonCenter_1F_Frlg | complete |  |
| CeladonCity_PokemonCenter_2F_Frlg | complete |  |
| CeladonCity_Restaurant_Frlg | complete |  |
| CeruleanCave_1F_Frlg | no events |  |
| CeruleanCave_2F_Frlg | complete |  |
| CeruleanCave_B1F_Frlg | complete |  |
| CeruleanCity_BikeShop_Frlg | complete |  |
| CeruleanCity_Frlg | complete |  |
| CeruleanCity_Gym_Frlg | complete |  |
| CeruleanCity_House1_Frlg | complete |  |
| CeruleanCity_House2_Frlg | complete |  |
| CeruleanCity_House3_Frlg | complete |  |
| CeruleanCity_House4_Frlg | complete |  |
| CeruleanCity_House5_Frlg | complete |  |
| CeruleanCity_Mart_Frlg | complete |  |
| CeruleanCity_PokemonCenter_1F_Frlg | complete |  |
| CeruleanCity_PokemonCenter_2F_Frlg | no events |  |
| CinnabarIsland_Frlg | complete | Bill Sevii scenes unreachable (VAR_MAP_SCENE_CINNABAR_ISLAND=4, setters to 1 none) |
| CinnabarIsland_Gym_Frlg | complete |  |
| CinnabarIsland_Mart_Frlg | complete |  |
| CinnabarIsland_PokemonCenter_1F_Frlg | complete | cooltrainer 'gym locked, key in mansion' contradicted unlocked gym -> fixed; Bill hidden (flag only cleared in unreachable scene) |
| CinnabarIsland_PokemonCenter_2F_Frlg | no events |  |
| CinnabarIsland_PokemonLab_Entrance_Frlg | complete |  |
| CinnabarIsland_PokemonLab_ExperimentRoom_Frlg | complete |  |
| CinnabarIsland_PokemonLab_Lounge_Frlg | complete |  |
| CinnabarIsland_PokemonLab_ResearchRoom_Frlg | complete | 'Eevee three kinds' -> fixed |
| DiglettsCave_B1F_Frlg | complete |  |
| DiglettsCave_NorthEntrance_Frlg | complete |  |
| DiglettsCave_SouthEntrance_Frlg | complete |  |
| FiveIsland_Frlg | complete | quest<5 showed thug texts while warehouse empty -> three-state branches |
| FiveIsland_Harbor_Frlg | complete |  |
| FiveIsland_House1_Frlg | complete |  |
| FiveIsland_House2_Frlg | complete | quest<5 branch added |
| FiveIsland_LostCave_Entrance_Frlg | no events |  |
| FiveIsland_LostCave_Room10_Frlg | complete |  |
| FiveIsland_LostCave_Room11_Frlg | no events |  |
| FiveIsland_LostCave_Room12_Frlg | no events |  |
| FiveIsland_LostCave_Room13_Frlg | no events |  |
| FiveIsland_LostCave_Room14_Frlg | no events |  |
| FiveIsland_LostCave_Room1_Frlg | complete |  |
| FiveIsland_LostCave_Room2_Frlg | no events |  |
| FiveIsland_LostCave_Room3_Frlg | no events |  |
| FiveIsland_LostCave_Room4_Frlg | complete |  |
| FiveIsland_LostCave_Room5_Frlg | no events |  |
| FiveIsland_LostCave_Room6_Frlg | no events |  |
| FiveIsland_LostCave_Room7_Frlg | no events |  |
| FiveIsland_LostCave_Room8_Frlg | no events |  |
| FiveIsland_LostCave_Room9_Frlg | no events |  |
| FiveIsland_Meadow_Frlg | complete |  |
| FiveIsland_MemorialPillar_Frlg | complete |  |
| FiveIsland_PokemonCenter_1F_Frlg | complete |  |
| FiveIsland_PokemonCenter_2F_Frlg | no events |  |
| FiveIsland_ResortGorgeous_Frlg | complete |  |
| FiveIsland_ResortGorgeous_House_Frlg | complete |  |
| FiveIsland_RocketWarehouse_Frlg | complete | quest step 5 battles + reward branch read |
| FiveIsland_WaterLabyrinth_Frlg | complete |  |
| FourIsland_Frlg | complete | old woman 'LORELEI has gone back' (FRLG E4 return) and doll girl -> fixed |
| FourIsland_Harbor_Frlg | complete |  |
| FourIsland_House1_Frlg | complete |  |
| FourIsland_House2_Frlg | complete | typo SITCKERS fixed |
| FourIsland_IcefallCave_1F_Frlg | complete |  |
| FourIsland_IcefallCave_B1F_Frlg | no events |  |
| FourIsland_IcefallCave_Back_Frlg | complete |  |
| FourIsland_IcefallCave_Entrance_Frlg | no events |  |
| FourIsland_LoreleisHouse_Frlg | complete | quest-5 / first / repeat branches |
| FourIsland_Mart_Frlg | complete |  |
| FourIsland_PokemonCenter_1F_Frlg | complete |  |
| FourIsland_PokemonCenter_2F_Frlg | no events |  |
| FourIsland_PokemonDayCare_Frlg | complete |  |
| FuchsiaCity_Frlg | complete |  |
| FuchsiaCity_Gym_Frlg | complete | Janine intro said 'My father, JANINE' -> KOGA |
| FuchsiaCity_House1_Frlg | complete |  |
| FuchsiaCity_House2_Frlg | complete |  |
| FuchsiaCity_House3_Frlg | complete |  |
| FuchsiaCity_Mart_Frlg | complete |  |
| FuchsiaCity_PokemonCenter_1F_Frlg | complete |  |
| FuchsiaCity_PokemonCenter_2F_Frlg | no events |  |
| FuchsiaCity_SafariZone_Entrance_Frlg | complete |  |
| FuchsiaCity_SafariZone_Office_Frlg | complete |  |
| FuchsiaCity_WardensHouse_Frlg | complete |  |
| IndigoPlateau_Exterior_Frlg | complete |  |
| IndigoPlateau_PokemonCenter_1F_Frlg | complete |  |
| IndigoPlateau_PokemonCenter_2F_Frlg | no events |  |
| LavenderTown_Frlg | complete |  |
| LavenderTown_House1_Frlg | complete | 'ghost is gone' contradicted spirit quest -> branch on VAR_SE_SPIRIT_QUEST |
| LavenderTown_House2_Frlg | complete |  |
| LavenderTown_Mart_Frlg | complete |  |
| LavenderTown_PokemonCenter_1F_Frlg | complete |  |
| LavenderTown_PokemonCenter_2F_Frlg | no events |  |
| LavenderTown_VolunteerPokemonHouse_Frlg | complete | spirit quest states 0/1-3/4/5 read |
| MtEmber_Exterior_Frlg | complete | Rocket password scene needs scene var 1, only set inside unreachable Celio scene |
| MtEmber_RubyPath_1F_Frlg | no events |  |
| MtEmber_RubyPath_B1F_Frlg | no events |  |
| MtEmber_RubyPath_B1F_Stairs_Frlg | no events |  |
| MtEmber_RubyPath_B2F_Frlg | no events |  |
| MtEmber_RubyPath_B2F_Stairs_Frlg | no events |  |
| MtEmber_RubyPath_B3F_Frlg | no events |  |
| MtEmber_RubyPath_B4F_Frlg | no events |  |
| MtEmber_RubyPath_B5F_Frlg | complete |  |
| MtEmber_SummitPath_1F_Frlg | no events |  |
| MtEmber_SummitPath_2F_Frlg | no events |  |
| MtEmber_SummitPath_3F_Frlg | no events |  |
| MtEmber_Summit_Frlg | complete |  |
| MtMoon_1F_Frlg | complete | Kent intro 'suspicious men are in the cave' -> fixed |
| MtMoon_B1F_Frlg | no events |  |
| MtMoon_B2F_Frlg | complete |  |
| NavelRock_1F_Frlg | no events |  |
| NavelRock_B1F_Frlg | no events |  |
| NavelRock_BasePath_B10F_Frlg | no events |  |
| NavelRock_BasePath_B11F_Frlg | no events |  |
| NavelRock_BasePath_B1F_Frlg | no events |  |
| NavelRock_BasePath_B2F_Frlg | no events |  |
| NavelRock_BasePath_B3F_Frlg | no events |  |
| NavelRock_BasePath_B4F_Frlg | no events |  |
| NavelRock_BasePath_B5F_Frlg | no events |  |
| NavelRock_BasePath_B6F_Frlg | no events |  |
| NavelRock_BasePath_B7F_Frlg | no events |  |
| NavelRock_BasePath_B8F_Frlg | no events |  |
| NavelRock_BasePath_B9F_Frlg | no events |  |
| NavelRock_Base_Frlg | complete |  |
| NavelRock_Exterior_Frlg | complete |  |
| NavelRock_Fork_Frlg | no events |  |
| NavelRock_Harbor_Frlg | complete |  |
| NavelRock_SummitPath_2F_Frlg | no events |  |
| NavelRock_SummitPath_3F_Frlg | no events |  |
| NavelRock_SummitPath_4F_Frlg | no events |  |
| NavelRock_SummitPath_5F_Frlg | no events |  |
| NavelRock_Summit_Frlg | complete |  |
| OneIsland_Frlg | complete | first-arrival Bill scene unreachable (harbor var only set to 1 in unreachable Cinnabar scene) |
| OneIsland_Harbor_Frlg | complete |  |
| OneIsland_House1_Frlg | complete |  |
| OneIsland_House2_Frlg | complete |  |
| OneIsland_KindleRoad_EmberSpa_Frlg | complete |  |
| OneIsland_KindleRoad_Frlg | complete |  |
| OneIsland_PokemonCenter_1F_Frlg | complete | Celio state 7 branch reachable; Bill/Ruby/Sapphire branches unreachable; crush girl thanked player for Celio's network -> fixed |
| OneIsland_PokemonCenter_2F_Frlg | no events |  |
| OneIsland_TreasureBeach_Frlg | complete |  |
| PalletTown_Frlg | complete | Oak rating scene (OAK var 2) reachable only after Kanto HoF if National Dex never enabled; functional fallback, noted |
| PalletTown_PlayersHouse_1F_Frlg | complete |  |
| PalletTown_PlayersHouse_2F_Frlg | complete | 'PLAYER played with the NES' in Red's room -> fixed |
| PalletTown_ProfessorOaksLab_Frlg | complete | lab var 9 path; scene 7 only via fallback above; scientist 'radio show soon' -> fixed (HGSS era) |
| PalletTown_RivalsHouse_Frlg | complete |  |
| PewterCity_Frlg | complete | Running Shoes aide appeared after beating Brock (Gym cleared the hide flag) -> removed clearflag in gym |
| PewterCity_Gym_Frlg | complete |  |
| PewterCity_House1_Frlg | complete |  |
| PewterCity_House2_Frlg | complete |  |
| PewterCity_Mart_Frlg | complete |  |
| PewterCity_Museum_1F_Frlg | complete | thief quest states 0-5 read |
| PewterCity_Museum_2F_Frlg | complete |  |
| PewterCity_PokemonCenter_1F_Frlg | complete |  |
| PewterCity_PokemonCenter_2F_Frlg | no events |  |
| PokemonLeague_AgathasRoom_Frlg | complete | first/rematch |
| PokemonLeague_BrunosRoom_Frlg | complete | first/rematch (Koga rematch mentions Janine; rematch needs 16 badges) |
| PokemonLeague_ChampionsRoom_Frlg | complete | first/rematch |
| PokemonLeague_HallOfFame_Frlg | complete | Lance welcomed a 'new CHAMPION' on the rematch too -> rematch line added |
| PokemonLeague_LancesRoom_Frlg | complete |  |
| PokemonLeague_LoreleisRoom_Frlg | complete |  |
| PokemonMansion_1F_Frlg | complete |  |
| PokemonMansion_2F_Frlg | complete |  |
| PokemonMansion_3F_Frlg | complete |  |
| PokemonMansion_B1F_Frlg | complete |  |
| PokemonTower_1F_Frlg | complete | channeler branch after spirit quest |
| PokemonTower_2F_Frlg | complete | Silph Scope mechanic: wild GHOST disguise disabled in C (scope unobtainable); channeler text adapted |
| PokemonTower_3F_Frlg | complete |  |
| PokemonTower_4F_Frlg | complete |  |
| PokemonTower_5F_Frlg | complete |  |
| PokemonTower_6F_Frlg | complete |  |
| PokemonTower_7F_Frlg | complete |  |
| PowerPlant_Frlg | complete |  |
| RockTunnel_1F_Frlg | complete | Oliver: Snorlax detour (Snorlax gone) -> fixed |
| RockTunnel_B1F_Frlg | complete |  |
| RocketHideout_B1F_Frlg | complete | BLOCKER: barrier stayed up forever (its grunt is hidden) -> skipped when misc rockets hidden |
| RocketHideout_B2F_Frlg | complete |  |
| RocketHideout_B3F_Frlg | complete |  |
| RocketHideout_B4F_Frlg | complete | BLOCKER: Giovanni door barrier needs two hidden grunts -> skipped when misc rockets hidden; ROM-tested |
| RocketHideout_Elevator_Frlg | complete |  |
| Route10_Frlg | complete |  |
| Route10_PokemonCenter_1F_Frlg | complete |  |
| Route10_PokemonCenter_2F_Frlg | no events |  |
| Route11_EastEntrance_1F_Frlg | complete |  |
| Route11_EastEntrance_2F_Frlg | complete |  |
| Route11_Frlg | complete |  |
| Route12_FishingHouse_Frlg | complete |  |
| Route12_Frlg | complete |  |
| Route12_NorthEntrance_1F_Frlg | complete |  |
| Route12_NorthEntrance_2F_Frlg | complete |  |
| Route13_Frlg | complete |  |
| Route14_Frlg | complete |  |
| Route15_Frlg | complete |  |
| Route15_WestEntrance_1F_Frlg | complete |  |
| Route15_WestEntrance_2F_Frlg | complete |  |
| Route16_Frlg | complete |  |
| Route16_House_Frlg | complete |  |
| Route16_NorthEntrance_1F_Frlg | complete | CYCLING ROAD gate only accepted the FRLG BICYCLE flag -> HOENN Mach/Acro bike also accepted |
| Route16_NorthEntrance_2F_Frlg | complete |  |
| Route17_Frlg | complete |  |
| Route18_EastEntrance_1F_Frlg | complete | same bike gate fix |
| Route18_EastEntrance_2F_Frlg | complete |  |
| Route18_Frlg | complete |  |
| Route19_Frlg | complete |  |
| Route1_Frlg | complete |  |
| Route20_Frlg | complete |  |
| Route21_North_Frlg | complete |  |
| Route21_South_Frlg | complete |  |
| Route22_Frlg | complete |  |
| Route23_Frlg | complete |  |
| Route24_Frlg | complete | Nugget Bridge promised a prize given by the hidden Rocket grunt -> intro reworded |
| Route25_Frlg | complete |  |
| Route25_SeaCottage_Frlg | complete | Clefairy-Bill hidden (HELPED_BILL set by state); human Bill gives RAINBOW PASS |
| Route2_EastBuilding_Frlg | complete |  |
| Route2_Frlg | complete |  |
| Route2_House_Frlg | complete |  |
| Route2_ViridianForest_NorthEntrance_Frlg | complete |  |
| Route2_ViridianForest_SouthEntrance_Frlg | complete |  |
| Route3_Frlg | complete |  |
| Route4_Frlg | complete | boy praised your BOULDERBADGE even without it -> badge branch |
| Route4_PokemonCenter_1F_Frlg | complete |  |
| Route4_PokemonCenter_2F_Frlg | no events |  |
| Route5_Frlg | complete |  |
| Route5_PokemonDayCare_Frlg | complete |  |
| Route5_SouthEntrance_Frlg | complete |  |
| Route6_Frlg | complete |  |
| Route6_NorthEntrance_Frlg | complete |  |
| Route7_EastEntrance_Frlg | complete |  |
| Route7_Frlg | complete |  |
| Route8_Frlg | complete | Megan: 'Saffron gatekeeper won't let us through' (gates open) -> fixed |
| Route8_WestEntrance_Frlg | complete |  |
| Route9_Frlg | complete |  |
| SSAnne_1F_Corridor_Frlg | unreachable | S.S. ANNE has left: VERMILION scene 3 and FLAG_HIDE_SS_ANNE; the pier tiles (22,33)/(23,33) always run the ticket check, which in scene 3 offers the SEAGALLOP or walks the player back up; (24,33) is the sailor; the dock is elevation 3, so it cannot be reached by SURF. ROM: the pier trigger opens the SEAGALLOP ferry. |
| SSAnne_1F_Room1_Frlg | unreachable | S.S. ANNE has left: VERMILION scene 3 and FLAG_HIDE_SS_ANNE; the pier tiles (22,33)/(23,33) always run the ticket check, which in scene 3 offers the SEAGALLOP or walks the player back up; (24,33) is the sailor; the dock is elevation 3, so it cannot be reached by SURF. ROM: the pier trigger opens the SEAGALLOP ferry. |
| SSAnne_1F_Room2_Frlg | unreachable | S.S. ANNE has left: VERMILION scene 3 and FLAG_HIDE_SS_ANNE; the pier tiles (22,33)/(23,33) always run the ticket check, which in scene 3 offers the SEAGALLOP or walks the player back up; (24,33) is the sailor; the dock is elevation 3, so it cannot be reached by SURF. ROM: the pier trigger opens the SEAGALLOP ferry. |
| SSAnne_1F_Room3_Frlg | unreachable | S.S. ANNE has left: VERMILION scene 3 and FLAG_HIDE_SS_ANNE; the pier tiles (22,33)/(23,33) always run the ticket check, which in scene 3 offers the SEAGALLOP or walks the player back up; (24,33) is the sailor; the dock is elevation 3, so it cannot be reached by SURF. ROM: the pier trigger opens the SEAGALLOP ferry. |
| SSAnne_1F_Room4_Frlg | unreachable | S.S. ANNE has left: VERMILION scene 3 and FLAG_HIDE_SS_ANNE; the pier tiles (22,33)/(23,33) always run the ticket check, which in scene 3 offers the SEAGALLOP or walks the player back up; (24,33) is the sailor; the dock is elevation 3, so it cannot be reached by SURF. ROM: the pier trigger opens the SEAGALLOP ferry. |
| SSAnne_1F_Room5_Frlg | unreachable | S.S. ANNE has left: VERMILION scene 3 and FLAG_HIDE_SS_ANNE; the pier tiles (22,33)/(23,33) always run the ticket check, which in scene 3 offers the SEAGALLOP or walks the player back up; (24,33) is the sailor; the dock is elevation 3, so it cannot be reached by SURF. ROM: the pier trigger opens the SEAGALLOP ferry. |
| SSAnne_1F_Room6_Frlg | unreachable | S.S. ANNE has left: VERMILION scene 3 and FLAG_HIDE_SS_ANNE; the pier tiles (22,33)/(23,33) always run the ticket check, which in scene 3 offers the SEAGALLOP or walks the player back up; (24,33) is the sailor; the dock is elevation 3, so it cannot be reached by SURF. ROM: the pier trigger opens the SEAGALLOP ferry. |
| SSAnne_1F_Room7_Frlg | unreachable | S.S. ANNE has left: VERMILION scene 3 and FLAG_HIDE_SS_ANNE; the pier tiles (22,33)/(23,33) always run the ticket check, which in scene 3 offers the SEAGALLOP or walks the player back up; (24,33) is the sailor; the dock is elevation 3, so it cannot be reached by SURF. ROM: the pier trigger opens the SEAGALLOP ferry. |
| SSAnne_2F_Corridor_Frlg | unreachable | S.S. ANNE has left: VERMILION scene 3 and FLAG_HIDE_SS_ANNE; the pier tiles (22,33)/(23,33) always run the ticket check, which in scene 3 offers the SEAGALLOP or walks the player back up; (24,33) is the sailor; the dock is elevation 3, so it cannot be reached by SURF. ROM: the pier trigger opens the SEAGALLOP ferry. |
| SSAnne_2F_Room1_Frlg | unreachable | S.S. ANNE has left: VERMILION scene 3 and FLAG_HIDE_SS_ANNE; the pier tiles (22,33)/(23,33) always run the ticket check, which in scene 3 offers the SEAGALLOP or walks the player back up; (24,33) is the sailor; the dock is elevation 3, so it cannot be reached by SURF. ROM: the pier trigger opens the SEAGALLOP ferry. |
| SSAnne_2F_Room2_Frlg | unreachable | S.S. ANNE has left: VERMILION scene 3 and FLAG_HIDE_SS_ANNE; the pier tiles (22,33)/(23,33) always run the ticket check, which in scene 3 offers the SEAGALLOP or walks the player back up; (24,33) is the sailor; the dock is elevation 3, so it cannot be reached by SURF. ROM: the pier trigger opens the SEAGALLOP ferry. |
| SSAnne_2F_Room3_Frlg | unreachable | S.S. ANNE has left: VERMILION scene 3 and FLAG_HIDE_SS_ANNE; the pier tiles (22,33)/(23,33) always run the ticket check, which in scene 3 offers the SEAGALLOP or walks the player back up; (24,33) is the sailor; the dock is elevation 3, so it cannot be reached by SURF. ROM: the pier trigger opens the SEAGALLOP ferry. |
| SSAnne_2F_Room4_Frlg | unreachable | S.S. ANNE has left: VERMILION scene 3 and FLAG_HIDE_SS_ANNE; the pier tiles (22,33)/(23,33) always run the ticket check, which in scene 3 offers the SEAGALLOP or walks the player back up; (24,33) is the sailor; the dock is elevation 3, so it cannot be reached by SURF. ROM: the pier trigger opens the SEAGALLOP ferry. |
| SSAnne_2F_Room5_Frlg | unreachable | S.S. ANNE has left: VERMILION scene 3 and FLAG_HIDE_SS_ANNE; the pier tiles (22,33)/(23,33) always run the ticket check, which in scene 3 offers the SEAGALLOP or walks the player back up; (24,33) is the sailor; the dock is elevation 3, so it cannot be reached by SURF. ROM: the pier trigger opens the SEAGALLOP ferry. |
| SSAnne_2F_Room6_Frlg | unreachable | S.S. ANNE has left: VERMILION scene 3 and FLAG_HIDE_SS_ANNE; the pier tiles (22,33)/(23,33) always run the ticket check, which in scene 3 offers the SEAGALLOP or walks the player back up; (24,33) is the sailor; the dock is elevation 3, so it cannot be reached by SURF. ROM: the pier trigger opens the SEAGALLOP ferry. |
| SSAnne_3F_Corridor_Frlg | unreachable | S.S. ANNE has left: VERMILION scene 3 and FLAG_HIDE_SS_ANNE; the pier tiles (22,33)/(23,33) always run the ticket check, which in scene 3 offers the SEAGALLOP or walks the player back up; (24,33) is the sailor; the dock is elevation 3, so it cannot be reached by SURF. ROM: the pier trigger opens the SEAGALLOP ferry. |
| SSAnne_B1F_Corridor_Frlg | no events |  |
| SSAnne_B1F_Room1_Frlg | unreachable | S.S. ANNE has left: VERMILION scene 3 and FLAG_HIDE_SS_ANNE; the pier tiles (22,33)/(23,33) always run the ticket check, which in scene 3 offers the SEAGALLOP or walks the player back up; (24,33) is the sailor; the dock is elevation 3, so it cannot be reached by SURF. ROM: the pier trigger opens the SEAGALLOP ferry. |
| SSAnne_B1F_Room2_Frlg | unreachable | S.S. ANNE has left: VERMILION scene 3 and FLAG_HIDE_SS_ANNE; the pier tiles (22,33)/(23,33) always run the ticket check, which in scene 3 offers the SEAGALLOP or walks the player back up; (24,33) is the sailor; the dock is elevation 3, so it cannot be reached by SURF. ROM: the pier trigger opens the SEAGALLOP ferry. |
| SSAnne_B1F_Room3_Frlg | unreachable | S.S. ANNE has left: VERMILION scene 3 and FLAG_HIDE_SS_ANNE; the pier tiles (22,33)/(23,33) always run the ticket check, which in scene 3 offers the SEAGALLOP or walks the player back up; (24,33) is the sailor; the dock is elevation 3, so it cannot be reached by SURF. ROM: the pier trigger opens the SEAGALLOP ferry. |
| SSAnne_B1F_Room4_Frlg | unreachable | S.S. ANNE has left: VERMILION scene 3 and FLAG_HIDE_SS_ANNE; the pier tiles (22,33)/(23,33) always run the ticket check, which in scene 3 offers the SEAGALLOP or walks the player back up; (24,33) is the sailor; the dock is elevation 3, so it cannot be reached by SURF. ROM: the pier trigger opens the SEAGALLOP ferry. |
| SSAnne_B1F_Room5_Frlg | unreachable | S.S. ANNE has left: VERMILION scene 3 and FLAG_HIDE_SS_ANNE; the pier tiles (22,33)/(23,33) always run the ticket check, which in scene 3 offers the SEAGALLOP or walks the player back up; (24,33) is the sailor; the dock is elevation 3, so it cannot be reached by SURF. ROM: the pier trigger opens the SEAGALLOP ferry. |
| SSAnne_CaptainsOffice_Frlg | unreachable | S.S. ANNE has left: VERMILION scene 3 and FLAG_HIDE_SS_ANNE; the pier tiles (22,33)/(23,33) always run the ticket check, which in scene 3 offers the SEAGALLOP or walks the player back up; (24,33) is the sailor; the dock is elevation 3, so it cannot be reached by SURF. ROM: the pier trigger opens the SEAGALLOP ferry. |
| SSAnne_Deck_Frlg | unreachable | S.S. ANNE has left: VERMILION scene 3 and FLAG_HIDE_SS_ANNE; the pier tiles (22,33)/(23,33) always run the ticket check, which in scene 3 offers the SEAGALLOP or walks the player back up; (24,33) is the sailor; the dock is elevation 3, so it cannot be reached by SURF. ROM: the pier trigger opens the SEAGALLOP ferry. |
| SSAnne_Exterior_Frlg | unreachable | S.S. ANNE has left: VERMILION scene 3 and FLAG_HIDE_SS_ANNE; the pier tiles (22,33)/(23,33) always run the ticket check, which in scene 3 offers the SEAGALLOP or walks the player back up; (24,33) is the sailor; the dock is elevation 3, so it cannot be reached by SURF. ROM: the pier trigger opens the SEAGALLOP ferry. |
| SSAnne_Kitchen_Frlg | unreachable | S.S. ANNE has left: VERMILION scene 3 and FLAG_HIDE_SS_ANNE; the pier tiles (22,33)/(23,33) always run the ticket check, which in scene 3 offers the SEAGALLOP or walks the player back up; (24,33) is the sailor; the dock is elevation 3, so it cannot be reached by SURF. ROM: the pier trigger opens the SEAGALLOP ferry. |
| SafariZone_Center_Frlg | complete |  |
| SafariZone_Center_RestHouse_Frlg | complete |  |
| SafariZone_East_Frlg | complete |  |
| SafariZone_East_RestHouse_Frlg | complete |  |
| SafariZone_North_Frlg | complete |  |
| SafariZone_North_RestHouse_Frlg | complete |  |
| SafariZone_SecretHouse_Frlg | complete |  |
| SafariZone_West_Frlg | complete |  |
| SafariZone_West_RestHouse_Frlg | complete |  |
| SaffronCity_CopycatsHouse_1F_Frlg | complete |  |
| SaffronCity_CopycatsHouse_2F_Frlg | complete |  |
| SaffronCity_Dojo_Frlg | complete |  |
| SaffronCity_Frlg | complete | Johto lines: 'zip back home', lost Clefairy doll quest (not in game), 'unused GYM next door' (Dojo active) -> fixed |
| SaffronCity_Gym_Frlg | complete |  |
| SaffronCity_MagnetTrainStation_Frlg | complete |  |
| SaffronCity_Mart_Frlg | complete |  |
| SaffronCity_MrPsychicsHouse_Frlg | complete |  |
| SaffronCity_PokemonCenter_1F_Frlg | complete | 'TEAM ROCKET took off!' -> past tense |
| SaffronCity_PokemonCenter_2F_Frlg | no events |  |
| SeafoamIslands_1F_Frlg | complete |  |
| SeafoamIslands_B1F_Frlg | complete |  |
| SeafoamIslands_B2F_Frlg | complete |  |
| SeafoamIslands_B3F_Frlg | complete |  |
| SeafoamIslands_B4F_Frlg | complete |  |
| SevenIsland_Frlg | complete |  |
| SevenIsland_Harbor_Frlg | complete |  |
| SevenIsland_House_Room1_Frlg | complete |  |
| SevenIsland_House_Room2_Frlg | complete |  |
| SevenIsland_Mart_Frlg | complete |  |
| SevenIsland_PokemonCenter_1F_Frlg | complete |  |
| SevenIsland_PokemonCenter_2F_Frlg | no events |  |
| SevenIsland_SevaultCanyon_Entrance_Frlg | complete |  |
| SevenIsland_SevaultCanyon_Frlg | complete |  |
| SevenIsland_SevaultCanyon_House_Frlg | complete |  |
| SevenIsland_SevaultCanyon_TanobyKey_Frlg | complete |  |
| SevenIsland_TanobyRuins_DilfordChamber_Frlg | no events |  |
| SevenIsland_TanobyRuins_Frlg | complete |  |
| SevenIsland_TanobyRuins_LiptooChamber_Frlg | no events |  |
| SevenIsland_TanobyRuins_MoneanChamber_Frlg | no events |  |
| SevenIsland_TanobyRuins_RixyChamber_Frlg | no events |  |
| SevenIsland_TanobyRuins_ScufibChamber_Frlg | no events |  |
| SevenIsland_TanobyRuins_ViapoisChamber_Frlg | no events |  |
| SevenIsland_TanobyRuins_WeepthChamber_Frlg | no events |  |
| SevenIsland_TrainerTower_Frlg | complete |  |
| SilphCo_10F_Frlg | complete |  |
| SilphCo_11F_Frlg | complete |  |
| SilphCo_1F_Frlg | complete |  |
| SilphCo_2F_Frlg | complete |  |
| SilphCo_3F_Frlg | complete |  |
| SilphCo_4F_Frlg | complete |  |
| SilphCo_5F_Frlg | complete |  |
| SilphCo_6F_Frlg | complete |  |
| SilphCo_7F_Frlg | complete |  |
| SilphCo_8F_Frlg | complete |  |
| SilphCo_9F_Frlg | complete |  |
| SilphCo_Elevator_Frlg | complete |  |
| SixIsland_AlteringCave_Frlg | no events |  |
| SixIsland_DottedHole_1F_Frlg | no events |  |
| SixIsland_DottedHole_B1F_Frlg | no events |  |
| SixIsland_DottedHole_B2F_Frlg | no events |  |
| SixIsland_DottedHole_B3F_Frlg | no events |  |
| SixIsland_DottedHole_B4F_Frlg | no events |  |
| SixIsland_DottedHole_SapphireRoom_Frlg | complete |  |
| SixIsland_Frlg | complete |  |
| SixIsland_GreenPath_Frlg | complete |  |
| SixIsland_Harbor_Frlg | complete |  |
| SixIsland_House_Frlg | complete |  |
| SixIsland_Mart_Frlg | complete |  |
| SixIsland_OutcastIsland_Frlg | complete |  |
| SixIsland_PatternBush_Frlg | complete |  |
| SixIsland_PokemonCenter_1F_Frlg | complete |  |
| SixIsland_PokemonCenter_2F_Frlg | no events |  |
| SixIsland_RuinValley_Frlg | complete |  |
| SixIsland_WaterPath_Frlg | complete |  |
| SixIsland_WaterPath_House1_Frlg | complete |  |
| SixIsland_WaterPath_House2_Frlg | complete |  |
| ThreeIsland_BerryForest_Frlg | complete |  |
| ThreeIsland_BondBridge_Frlg | complete |  |
| ThreeIsland_DunsparceTunnel_Frlg | complete |  |
| ThreeIsland_Frlg | complete | bikers are SE trainers on the island; woman said 'wouldn't want them here again' -> fixed; FRLG gang scene unreachable (scene var 4) |
| ThreeIsland_Harbor_Frlg | complete |  |
| ThreeIsland_House1_Frlg | complete |  |
| ThreeIsland_House2_Frlg | complete |  |
| ThreeIsland_House3_Frlg | complete |  |
| ThreeIsland_House4_Frlg | complete |  |
| ThreeIsland_House5_Frlg | complete |  |
| ThreeIsland_Mart_Frlg | complete | 'glad bikers left' -> calmed down |
| ThreeIsland_PokemonCenter_1F_Frlg | complete |  |
| ThreeIsland_PokemonCenter_2F_Frlg | no events |  |
| ThreeIsland_Port_Frlg | complete | 'BIKERS ran off' -> calmed down |
| TradeCenter_Frlg | complete | engine-driven challenge; texts read |
| TrainerTower_1F_Frlg | complete | engine-driven challenge; texts read |
| TrainerTower_2F_Frlg | complete | engine-driven challenge; texts read |
| TrainerTower_3F_Frlg | complete | engine-driven challenge; texts read |
| TrainerTower_4F_Frlg | complete | engine-driven challenge; texts read |
| TrainerTower_5F_Frlg | complete | engine-driven challenge; texts read |
| TrainerTower_6F_Frlg | complete | engine-driven challenge; texts read |
| TrainerTower_7F_Frlg | complete | engine-driven challenge; texts read |
| TrainerTower_8F_Frlg | complete | engine-driven challenge; texts read |
| TrainerTower_Elevator_Frlg | complete | engine-driven challenge; texts read |
| TrainerTower_Lobby_Frlg | complete | engine-driven challenge; texts read |
| TrainerTower_Roof_Frlg | complete | engine-driven challenge; texts read |
| TwoIsland_CapeBrink_Frlg | complete |  |
| TwoIsland_CapeBrink_House_Frlg | complete |  |
| TwoIsland_Frlg | complete | BUG: shop state recomputed from flags -> opened as 'new' and thanked player for LOSTELLE; state now sets the shop flags (Kanto state v7) |
| TwoIsland_Harbor_Frlg | complete |  |
| TwoIsland_House_Frlg | complete |  |
| TwoIsland_JoyfulGameCorner_Frlg | complete | Lostelle rescue scene unreachable (var 4) |
| TwoIsland_PokemonCenter_1F_Frlg | complete |  |
| TwoIsland_PokemonCenter_2F_Frlg | no events |  |
| UndergroundPath_EastEntrance_Frlg | complete |  |
| UndergroundPath_EastWestTunnel_Frlg | no events |  |
| UndergroundPath_NorthEntrance_Frlg | complete |  |
| UndergroundPath_NorthSouthTunnel_Frlg | no events |  |
| UndergroundPath_SouthEntrance_Frlg | complete |  |
| UndergroundPath_WestEntrance_Frlg | complete |  |
| UnionRoom_Frlg | complete |  |
| VermilionCity_Frlg | complete | old man said S.S. ANNE 'is in port' while ship is gone (my earlier edit was wrong) -> fixed |
| VermilionCity_Gym_Frlg | complete |  |
| VermilionCity_House1_Frlg | complete |  |
| VermilionCity_House2_Frlg | complete |  |
| VermilionCity_House3_Frlg | complete |  |
| VermilionCity_Mart_Frlg | complete |  |
| VermilionCity_PokemonCenter_1F_Frlg | complete |  |
| VermilionCity_PokemonCenter_2F_Frlg | no events |  |
| VermilionCity_PokemonFanClub_Frlg | complete |  |
| ViridianCity_Frlg | complete | coffee man asked about a TEACHY TV the player never got -> asks only if owned |
| ViridianCity_Gym_Frlg | complete |  |
| ViridianCity_House_Frlg | complete |  |
| ViridianCity_Mart_Frlg | complete |  |
| ViridianCity_PokemonCenter_1F_Frlg | complete |  |
| ViridianCity_PokemonCenter_2F_Frlg | no events |  |
| ViridianCity_School_Frlg | complete |  |
| ViridianForest_Frlg | complete |  |

### Sinnoh

| Map | Status | Notes |
|---|---|---|
| AcuityLakefront_sinnoh | complete |  |
| AmitySquare_sinnoh | complete | daily berry gift (bag-full check added earlier) |
| CanalaveCity_Gym_sinnoh | complete |  |
| CanalaveCity_HarborInn_sinnoh | no events | no visible events (objects, if any, hidden by state flags) |
| CanalaveCity_House1_sinnoh | no events | no visible events (objects, if any, hidden by state flags) |
| CanalaveCity_House2_sinnoh | complete | move deleter is real |
| CanalaveCity_House3_sinnoh | complete | LUNAR WING states |
| CanalaveCity_House4_sinnoh | complete |  |
| CanalaveCity_Library_F1_sinnoh | complete |  |
| CanalaveCity_Library_F2_sinnoh | complete |  |
| CanalaveCity_Library_F3_sinnoh | complete | Lake Valor explosion flags never set in SE (only base text reachable) |
| CanalaveCity_Mart_sinnoh | complete |  |
| CanalaveCity_PokemonCenter_1F_sinnoh | complete |  |
| CanalaveCity_PokemonCenter_2F_sinnoh | no events | no visible events (objects, if any, hidden by state flags) |
| CanalaveCity_sinnoh | complete | DAWN arrival scene, ELDRITCH states, ship menu |
| CelesticTown_House1_sinnoh | complete |  |
| CelesticTown_House2_sinnoh | complete |  |
| CelesticTown_House3_sinnoh | complete |  |
| CelesticTown_House4_sinnoh | complete |  |
| CelesticTown_PokemonCenter_1F_sinnoh | complete |  |
| CelesticTown_PokemonCenter_2F_sinnoh | no events | no visible events (objects, if any, hidden by state flags) |
| CelesticTown_Ruins_sinnoh | complete | SURF gift (bag check, ROM-tested earlier); Old CHARM branch |
| CelesticTown_sinnoh | complete |  |
| EternaCity_CycleShop_sinnoh | complete |  |
| EternaCity_Flat1_F1_sinnoh | complete | in-game trade; name rater is real |
| EternaCity_Flat1_F2_sinnoh | complete |  |
| EternaCity_Flat1_F3_sinnoh | complete |  |
| EternaCity_GalacticBuilding_1F_sinnoh | complete |  |
| EternaCity_GalacticBuilding_2F_sinnoh | complete |  |
| EternaCity_GalacticBuilding_3F_sinnoh | no events | no visible events (objects, if any, hidden by state flags) |
| EternaCity_GalacticBuilding_4F_sinnoh | complete | Travis quest step, GIBLE reward |
| EternaCity_GalacticBuilding_B1F_sinnoh | no events | no visible events (objects, if any, hidden by state flags) |
| EternaCity_Gym_sinnoh | complete |  |
| EternaCity_HerbShop_sinnoh | complete |  |
| EternaCity_House1_sinnoh | complete | inscription man asked about a second inscription and never told it -> text closes the thought |
| EternaCity_House2_sinnoh | no events | no visible events (objects, if any, hidden by state flags) |
| EternaCity_Mart_sinnoh | complete |  |
| EternaCity_PokemonCenter_F1_sinnoh | complete |  |
| EternaCity_PokemonCenter_F2_sinnoh | complete |  |
| EternaCity_UndergroundManHouse_sinnoh | complete | daily fossil gift |
| EternaCity_sinnoh | complete | CYRUS/CYNTHIA statue scene hidden (HIDE_ETERNA_STATUE set by state init) |
| EternaForest_sinnoh | complete | honey tree, ZACIAN |
| FightArea_House1_sinnoh | complete |  |
| FightArea_House2_sinnoh | complete | Item Expert asked 'Care to know?' and stopped -> gives his recommendations |
| FightArea_Mart_sinnoh | complete |  |
| FightArea_PokemonCenter_1F_sinnoh | complete |  |
| FightArea_PokemonCenter_2F_sinnoh | no events | no visible events (objects, if any, hidden by state flags) |
| FightArea_sinnoh | complete | BARRY multi/PALMER/BUCK scene hidden by state init; SUPER ROD gift; ferry |
| FloaromaMeadow_House_sinnoh | complete |  |
| FloaromaMeadow_sinnoh | complete |  |
| FloaromaTown_FlowerShop_sinnoh | complete |  |
| FloaromaTown_House1_sinnoh | complete | girl said 'Here's the TM for PLUCK!' and gave nothing (no such TM) -> text fixed |
| FloaromaTown_House2_sinnoh | complete |  |
| FloaromaTown_Mart_sinnoh | complete |  |
| FloaromaTown_PokemonCenter_1F_sinnoh | complete |  |
| FloaromaTown_sinnoh | complete | GRACIDEA needs SHAYMIN |
| FloaromaTwon_PokemonCenter_2F_sinnoh | no events | no visible events (objects, if any, hidden by state flags) |
| FlowerParadise_sinnoh | no events | no visible events (objects, if any, hidden by state flags) |
| FuegoIronworks_Inside_sinnoh | complete | STAR PIECE exchange |
| FuegoIronworks_sinnoh | complete |  |
| FullmoonIsland_Forest_sinnoh | complete |  |
| FullmoonIsland_sinnoh | complete |  |
| GalacticHQ_1F_sinnoh | complete |  |
| GalacticHQ_2F_sinnoh | complete |  |
| GalacticHQ_3F_sinnoh | complete |  |
| GalacticHQ_4F_sinnoh | complete | CYRUS final step |
| GalacticHQ_B1F_sinnoh | complete |  |
| GalacticHQ_B2F_sinnoh | complete |  |
| GalacticHQ_ControlRoom_sinnoh | complete |  |
| GalacticHQ_Hall_sinnoh | no events | no visible events (objects, if any, hidden by state flags) |
| GalacticHQ_Laboratory_sinnoh | complete |  |
| GreatMarsh_sinnoh | complete |  |
| HallOfOrigin_sinnoh | complete | ARCEUS |
| HearthomeCity_EastGate_sinnoh | complete |  |
| HearthomeCity_Flat1_F1_sinnoh | complete |  |
| HearthomeCity_Flat1_F2_sinnoh | complete |  |
| HearthomeCity_Flat2_F1_sinnoh | complete |  |
| HearthomeCity_Flat2_F2_sinnoh | complete |  |
| HearthomeCity_ForeignBuilding_sinnoh | complete |  |
| HearthomeCity_Gym_sinnoh | complete | guide/statue checked BADGE3 (MAYLENE) but FANTINA gives BADGE5 -> fixed; same mix-up fixed in Pastoria (5->4) and Veilstone (4->3) gyms, Mr. Goods (Hearthome) and a Pastoria NPC |
| HearthomeCity_House1_sinnoh | complete | BEBE EEVEE gift |
| HearthomeCity_Mart_sinnoh | complete |  |
| HearthomeCity_PoffinHouse_sinnoh | complete | advice described Poffin cooking -> BERRY BLENDER advice |
| HearthomeCity_PokemonCenter_1F_sinnoh | complete | sent player to the Fan Club for the POKéBLOCK CASE (it is given at the POKéBLOCK HOUSE) -> fixed; KANTO request quest 0..3 |
| HearthomeCity_PokemonCenter_2F_sinnoh | no events | no visible events (objects, if any, hidden by state flags) |
| HearthomeCity_PokemonFanClub_sinnoh | complete |  |
| HearthomeCity_WestGate_sinnoh | complete |  |
| HearthomeCity_sinnoh | complete | LUCAS rival 2 (3 starters), WALLY Sinnoh quest, Mr. Goods (badge fixed), CONTEST guide |
| HotelGrandLake_sinnoh | complete |  |
| IcebergRuins_sinnoh | complete |  |
| IronIsland_1F_sinnoh | no events | no visible events (objects, if any, hidden by state flags) |
| IronIsland_B1F_Left_sinnoh | complete |  |
| IronIsland_B1F_Right_sinnoh | complete |  |
| IronIsland_B2F_Left_sinnoh | complete | Platinum RILEY B2F egg scene hidden; SE RILEY at the entrance |
| IronIsland_B2F_Right_sinnoh | complete |  |
| IronIsland_B3F_sinnoh | no events | no visible events (objects, if any, hidden by state flags) |
| IronIsland_House_sinnoh | complete | BYRON said 'Take this as my apology!' and gave nothing -> METAL COAT once (flag 0x32F8) |
| IronIsland_sinnoh | complete | RILEY egg (party check) |
| IronRuins_sinnoh | complete |  |
| JubilifeCity_Flat1_F1_sinnoh | complete |  |
| JubilifeCity_Flat1_F2_sinnoh | complete |  |
| JubilifeCity_Flat1_F3_sinnoh | no events | no visible events (objects, if any, hidden by state flags) |
| JubilifeCity_Flat2_F1_sinnoh | complete |  |
| JubilifeCity_Flat2_F2_sinnoh | complete |  |
| JubilifeCity_Flat2_F3_sinnoh | complete |  |
| JubilifeCity_Flat3_F1_sinnoh | complete |  |
| JubilifeCity_Flat3_F2_sinnoh | complete |  |
| JubilifeCity_Flat3_F3_sinnoh | complete |  |
| JubilifeCity_JubilifeTV_F1_sinnoh | complete | lottery read; fitting-room invitation -> closed for redecorating |
| JubilifeCity_JubilifeTV_F2_sinnoh | complete | dress-up photo promise -> boudoir being redecorated |
| JubilifeCity_JubilifeTV_F3_sinnoh | complete |  |
| JubilifeCity_JubilifeTV_F4_sinnoh | complete |  |
| JubilifeCity_Mart_sinnoh | complete |  |
| JubilifeCity_PokemonCenter_1F_sinnoh | complete |  |
| JubilifeCity_PokemonCenter_2F_sinnoh | no events | no visible events (objects, if any, hidden by state flags) |
| JubilifeCity_PokemonSchool_sinnoh | complete | two students accepted a battle that never started -> they now defer to the teacher |
| JubilifeCity_PoketchCompany_F1_sinnoh | complete |  |
| JubilifeCity_PoketchCompany_F2_sinnoh | complete |  |
| JubilifeCity_PoketchCompany_F3_sinnoh | complete |  |
| JubilifeCity_sinnoh | complete | clown quiz/CATCHING CHARM; LOOKER greeting assumed a guide friend -> fixed |
| LakeAcuity_Cavern_sinnoh | complete |  |
| LakeAcuity_sinnoh | complete | JUPITER step 2 |
| LakeValor_Cavern_sinnoh | complete |  |
| LakeValor_Drained_sinnoh | unreachable | no warp leads here (Platinum story map) |
| LakeValor_sinnoh | complete | SATURN step 3 |
| LakeVerity_Cavern_sinnoh | complete |  |
| LakeVerity_LowWater_sinnoh | unreachable | no warp leads here (Platinum story map) |
| LakeVerity_sinnoh | complete | MARS step 1 |
| LostTower_1F_sinnoh | complete |  |
| LostTower_2F_sinnoh | complete |  |
| LostTower_3F_sinnoh | complete |  |
| LostTower_4F_sinnoh | complete |  |
| LostTower_5F_sinnoh | complete |  |
| ManiacTunnel_sinnoh | no events | no visible events (objects, if any, hidden by state flags) |
| MtCoronet_1F_North_Room1_sinnoh | no events | no visible events (objects, if any, hidden by state flags) |
| MtCoronet_1F_North_Room2_sinnoh | complete | ICEBERG RUINS entrance after Sinnoh League |
| MtCoronet_1F_South_sinnoh | no events | no visible events (objects, if any, hidden by state flags) |
| MtCoronet_1F_TunnelRoom_sinnoh | complete |  |
| MtCoronet_2F_sinnoh | complete |  |
| MtCoronet_3F_sinnoh | no events | no visible events (objects, if any, hidden by state flags) |
| MtCoronet_4F_Room1_sinnoh | no events | no visible events (objects, if any, hidden by state flags) |
| MtCoronet_4F_Room3_sinnoh | no events | no visible events (objects, if any, hidden by state flags) |
| MtCoronet_5F_sinnoh | no events | no visible events (objects, if any, hidden by state flags) |
| MtCoronet_6F_sinnoh | complete |  |
| MtCoronet_B1F_sinnoh | no events | no visible events (objects, if any, hidden by state flags) |
| MtCoronet_Outside_North_sinnoh | no events | no visible events (objects, if any, hidden by state flags) |
| MtCoronet_Outside_South_sinnoh | no events | no visible events (objects, if any, hidden by state flags) |
| NewmoonIsland_Forest_sinnoh | complete |  |
| NewmoonIsland_sinnoh | complete |  |
| OldChateau_2F_sinnoh | complete | ROTOM |
| OldChateau_DiningRoom_sinnoh | no events | no visible events (objects, if any, hidden by state flags) |
| OldChateau_Entrance_sinnoh | complete | ROTOM CATALOG |
| OldChateau_SideRoom_1_sinnoh | no events | no visible events (objects, if any, hidden by state flags) |
| OldChateau_SideRoom_2_sinnoh | no events | no visible events (objects, if any, hidden by state flags) |
| OreburghCity_Flat1_F1_sinnoh | complete |  |
| OreburghCity_Flat1_F2_sinnoh | complete |  |
| OreburghCity_Flat2_F1_sinnoh | complete | girl accepted a MACHOP-for-ABRA trade that never happened -> she backs out |
| OreburghCity_Flat2_F2_sinnoh | complete |  |
| OreburghCity_Flat3_F1_sinnoh | complete |  |
| OreburghCity_Flat3_F2_sinnoh | complete |  |
| OreburghCity_Gym_sinnoh | complete |  |
| OreburghCity_House1_sinnoh | complete |  |
| OreburghCity_House2_sinnoh | complete |  |
| OreburghCity_House3_sinnoh | complete |  |
| OreburghCity_Mart_sinnoh | complete |  |
| OreburghCity_MiningMuseum_2F_sinnoh | complete |  |
| OreburghCity_MiningMuseum_sinnoh | complete | fossil revival |
| OreburghCity_PokemonCenter_1F_sinnoh | complete | kid assumed the player has a Vs. Recorder -> fixed |
| OreburghCity_PokemonCenter_2F_sinnoh | no events | no visible events (objects, if any, hidden by state flags) |
| OreburghCity_sinnoh | complete | STEVEN Sinnoh quest |
| OreburghGate_1F_sinnoh | complete | hiker praised the COAL BADGE before it was won -> branch on BADGE1 |
| OreburghGate_B1F_sinnoh | complete |  |
| OreburghMine_B1F_sinnoh | complete |  |
| OreburghMine_B2F_sinnoh | complete |  |
| PastoriaCity_GreatMarshGate_sinnoh | complete | Galar trio (room check), safari fee, five-catch prize |
| PastoriaCity_Gym_sinnoh | complete | guide/statue badge fixed (5->4) |
| PastoriaCity_House1_sinnoh | complete |  |
| PastoriaCity_House2_sinnoh | complete | scarf man shares the SLATEPORT fan club logic |
| PastoriaCity_House3_sinnoh | complete |  |
| PastoriaCity_House4_sinnoh | complete | move relearner is real |
| PastoriaCity_House5_sinnoh | complete |  |
| PastoriaCity_Mart_sinnoh | complete |  |
| PastoriaCity_PokemonCenter_1F_sinnoh | complete |  |
| PastoriaCity_PokemonCenter_2F_sinnoh | complete |  |
| PastoriaCity_sinnoh | complete | GALACTIC bomb scene hidden by state init; NPC badge check fixed (5->4) |
| PokemonLeague_AaronRoom_sinnoh | complete | rematch repeated the first-meeting intro -> own rematch greeting |
| PokemonLeague_BerthaRoom_sinnoh | complete | rematch repeated the first-meeting intro -> own rematch greeting |
| PokemonLeague_ChampionRoom_sinnoh | complete | CYNTHIA first/rematch (fixed earlier) |
| PokemonLeague_FlintRoom_sinnoh | complete | intro is only '…', fine for rematch |
| PokemonLeague_HallOfFameRoom_sinnoh | complete |  |
| PokemonLeague_LucianRoom_sinnoh | complete | rematch repeated 'allow me to introduce myself' -> own rematch greeting |
| PokemonLeague_NorthPokemonCenter_1F_sinnoh | complete | daily league lock |
| PokemonLeague_NorthPokemonCenter_2F_sinnoh | no events | no visible events (objects, if any, hidden by state flags) |
| PokemonLeague_SouthPokemonCenter_1F_sinnoh | complete |  |
| PokemonLeague_SouthPokemonCenter_2F_sinnoh | no events | no visible events (objects, if any, hidden by state flags) |
| PokemonMansion_MaidsRoom_sinnoh | complete |  |
| PokemonMansion_Office_sinnoh | complete | Backlot daily trophy garden; 'Would you like to read it?' book had no answer -> text |
| PokemonMansion_sinnoh | complete | maid knockout challenge |
| PokmonLeague_sinnoh | complete |  |
| RavagedPath_sinnoh | no events | no visible events (objects, if any, hidden by state flags) |
| ResortArea_House_sinnoh | complete | boy claimed the player had seen every SINNOH POKéMON unconditionally -> question |
| ResortArea_PokemonCenter_1F_sinnoh | complete |  |
| ResortArea_PokemonCenter_2F_sinnoh | no events | no visible events (objects, if any, hidden by state flags) |
| ResortArea_RibbonSyndicate_F1_sinnoh | complete |  |
| ResortArea_RibbonSyndicate_F2_sinnoh | complete | daily spa |
| ResortArea_Villa_sinnoh | complete |  |
| ResortArea_sinnoh | complete | villa gift |
| RockPeakRuins_sinnoh | complete |  |
| Route201_sinnoh | complete |  |
| Route202_sinnoh | complete |  |
| Route203_sinnoh | complete |  |
| Route204_sinnoh | complete |  |
| Route205_House_sinnoh | complete | 'Rest a while' said the team was refreshed without healing -> real party heal |
| Route205_North_sinnoh | complete |  |
| Route205_South_sinnoh | complete |  |
| Route206_North_sinnoh | complete | EXP. SHARE gift (35 seen) |
| Route206_South_sinnoh | complete |  |
| Route206_sinnoh | complete |  |
| Route207_sinnoh | complete |  |
| Route208_Access_sinnoh | complete |  |
| Route208_House_sinnoh | complete | berry master daily; mulch shop is a real mart |
| Route208_sinnoh | complete | ODD KEYSTONE man told the player to talk to people underground (closed) -> points to the Route 209 pillar where SPIRITOMB is |
| Route209_Access_sinnoh | complete |  |
| Route209_sinnoh | complete | GOOD ROD gift; SPIRITOMB pillar |
| Route210_Cafe_sinnoh | complete | waitress offered MOOMOO MILK with no sale -> real yes/no purchase (500) |
| Route210_House_sinnoh | complete | DRACO METEOR tutor |
| Route210_North_sinnoh | complete |  |
| Route210_South_sinnoh | complete | Platinum CYNTHIA Old CHARM scene hidden by state init |
| Route211_East_sinnoh | complete |  |
| Route211_West_sinnoh | complete |  |
| Route212_Access_sinnoh | complete |  |
| Route212_House_sinnoh | complete | shard tutor (each option checks shards); girl pointed to the closed UNDERGROUND -> text |
| Route212_North_sinnoh | complete |  |
| Route212_South_sinnoh | complete |  |
| Route213_Access_sinnoh | complete |  |
| Route213_FootstepHouse_sinnoh | complete | Dr. Footstep offered a reading and never gave it -> real friendship reading (shared with the Verdanturf rater) |
| Route213_House1_sinnoh | complete |  |
| Route213_House2_sinnoh | complete |  |
| Route213_House3_sinnoh | complete |  |
| Route213_sinnoh | complete |  |
| Route214_Access_sinnoh | complete |  |
| Route214_sinnoh | complete |  |
| Route215_Access_sinnoh | complete |  |
| Route215_sinnoh | complete |  |
| Route216_House_sinnoh | complete | bed heals |
| Route216_sinnoh | complete |  |
| Route217_House1_sinnoh | complete | woman said 'The SPELL TAG… may it serve you well' and gave nothing -> SPELL TAG once (flag 0x32F9) |
| Route217_House2_sinnoh | complete |  |
| Route217_sinnoh | complete |  |
| Route218_East_sinnoh | complete | OLD ROD gift |
| Route218_West_sinnoh | complete |  |
| Route218_sinnoh | complete |  |
| Route219_sinnoh | complete |  |
| Route220_sinnoh | complete |  |
| Route221_House_sinnoh | complete | 'I'll thank you with this item' gave nothing -> EXPERT BELT once (flag 0x32FA) |
| Route221_sinnoh | complete |  |
| Route222_Access_sinnoh | complete |  |
| Route222_House1_sinnoh | complete |  |
| Route222_House2_sinnoh | complete |  |
| Route222_sinnoh | complete |  |
| Route223_sinnoh | complete |  |
| Route224_sinnoh | complete | SHAYMIN, ENAMORUS |
| Route225_Access_sinnoh | complete |  |
| Route225_House_sinnoh | complete |  |
| Route225_sinnoh | complete |  |
| Route226_Access_sinnoh | no events | no visible events (objects, if any, hidden by state flags) |
| Route226_House_sinnoh | complete |  |
| Route226_sinnoh | complete |  |
| Route227_House_sinnoh | complete | 'Rest up here!' with no rest -> real party heal |
| Route227_sinnoh | complete |  |
| Route228_House1_sinnoh | complete | ultimate-move tutor (friendship 6) |
| Route228_House2_sinnoh | complete | old man saw a SUNYSHORE badge the player may not have -> neutral opening |
| Route228_sinnoh | complete | ROCK PEAK RUINS entrance after league |
| Route229_sinnoh | complete |  |
| Route230_sinnoh | complete |  |
| SandgemTown_House1_sinnoh | complete |  |
| SandgemTown_Mart_sinnoh | complete |  |
| SandgemTown_PokemonCenter_1F_sinnoh | complete |  |
| SandgemTown_PokemonCenter_2F_sinnoh | complete |  |
| SandgemTown_RivalHouse_F1_sinnoh | complete |  |
| SandgemTown_RivalHouse_F2_sinnoh | no events | no visible events (objects, if any, hidden by state flags) |
| SandgemTown_RowansLab_sinnoh | complete | starter choice (party/PC check) |
| SandgemTown_sinnoh | complete | LUCAS rival 1; Platinum DAWN/BARRY scene hidden |
| SeabreakPath_North_sinnoh | no events | no visible events (objects, if any, hidden by state flags) |
| SeabreakPath_South_sinnoh | no events | no visible events (objects, if any, hidden by state flags) |
| SendoffSpring_sinnoh | complete |  |
| SinnohVictoryRoad_1F_Room1_sinnoh | no events | no visible events (objects, if any, hidden by state flags) |
| SinnohVictoryRoad_1F_Room2_sinnoh | complete |  |
| SinnohVictoryRoad_1F_Room3_sinnoh | no events | no visible events (objects, if any, hidden by state flags) |
| SinnohVictoryRoad_1F_sinnoh | complete | LUCAS rival 3 |
| SinnohVictoryRoad_2F_sinnoh | complete |  |
| SinnohVictoryRoad_B1F_sinnoh | complete |  |
| SnowpointCity_Gym_1F_sinnoh | complete | ice floor |
| SnowpointCity_Gym_B1F_sinnoh | complete |  |
| SnowpointCity_House1_sinnoh | complete | in-game trade |
| SnowpointCity_House2_sinnoh | complete | shard tutor |
| SnowpointCity_Mart_sinnoh | complete |  |
| SnowpointCity_PokemonCenter_1F_sinnoh | complete | MAYLENE greeted the player by name before ever meeting -> fixed |
| SnowpointCity_PokemonCenter_2F_sinnoh | no events | no visible events (objects, if any, hidden by state flags) |
| SnowpointCity_sinnoh | complete | temple guard told the player to leave while the door is walkable -> lets the CHAMPION pass |
| SnowpointTemple_1F_sinnoh | complete |  |
| SnowpointTemple_B1F_sinnoh | no events | no visible events (objects, if any, hidden by state flags) |
| SnowpointTemple_B2F_sinnoh | no events | no visible events (objects, if any, hidden by state flags) |
| SnowpointTemple_B3F_sinnoh | no events | no visible events (objects, if any, hidden by state flags) |
| SnowpointTemple_B4F_sinnoh | no events | no visible events (objects, if any, hidden by state flags) |
| SnowpointTemple_B5F_sinnoh | complete | REGIGIGAS |
| SolaceonRuins_ManiacTunnelRoom_sinnoh | complete |  |
| SolaceonRuins_Room1_Northwest_sinnoh | no events | no visible events (objects, if any, hidden by state flags) |
| SolaceonRuins_Room1_Southeast_sinnoh | no events | no visible events (objects, if any, hidden by state flags) |
| SolaceonRuins_Room1_sinnoh | complete |  |
| SolaceonRuins_Room2_Northeast_sinnoh | no events | no visible events (objects, if any, hidden by state flags) |
| SolaceonRuins_Room2_Southeast_sinnoh | no events | no visible events (objects, if any, hidden by state flags) |
| SolaceonRuins_Room2_sinnoh | complete |  |
| SolaceonRuins_Room3_Northwest_sinnoh | no events | no visible events (objects, if any, hidden by state flags) |
| SolaceonRuins_Room3_Southwest_sinnoh | no events | no visible events (objects, if any, hidden by state flags) |
| SolaceonRuins_Room3_sinnoh | complete |  |
| SolaceonRuins_Room4_Southeast_sinnoh | no events | no visible events (objects, if any, hidden by state flags) |
| SolaceonRuins_Room4_sinnoh | no events | no visible events (objects, if any, hidden by state flags) |
| SolaceonRuins_Room5_Southeast_sinnoh | no events | no visible events (objects, if any, hidden by state flags) |
| SolaceonRuins_Room5_Southwest_sinnoh | no events | no visible events (objects, if any, hidden by state flags) |
| SolaceonRuins_Room5_sinnoh | no events | no visible events (objects, if any, hidden by state flags) |
| SolaceonRuins_Room6_Northwest_sinnoh | no events | no visible events (objects, if any, hidden by state flags) |
| SolaceonRuins_Room6_Southeast_sinnoh | no events | no visible events (objects, if any, hidden by state flags) |
| SolaceonRuins_Room6_sinnoh | no events | no visible events (objects, if any, hidden by state flags) |
| SolaceonRuins_Room7_sinnoh | complete |  |
| SolaceonTown_DayCare_sinnoh | complete | day-care lady (Hoenn script) |
| SolaceonTown_House1_sinnoh | complete | boy/mom sent the player for a Seal Case and a PC menu that do not exist -> flavor text |
| SolaceonTown_House2_sinnoh | complete |  |
| SolaceonTown_House3_sinnoh | complete |  |
| SolaceonTown_Mart_sinnoh | complete |  |
| SolaceonTown_NewsPress_sinnoh | complete | daily photo request (bag check added earlier) |
| SolaceonTown_PokemonCenter_1F_sinnoh | complete |  |
| SolaceonTown_PokemonCenter_2F_sinnoh | no events | no visible events (objects, if any, hidden by state flags) |
| SolaceonTown_sinnoh | complete | day-care man |
| SpearPillar_sinnoh | complete | DIALGA/PALKIA, altar to HALL OF ORIGIN after league |
| SpringPath_sinnoh | no events | no visible events (objects, if any, hidden by state flags) |
| StarkMountain_Room1_sinnoh | no events | no visible events (objects, if any, hidden by state flags) |
| StarkMountain_Room2_East_sinnoh | complete |  |
| StarkMountain_Room2_West_sinnoh | complete |  |
| StarkMountain_Room3_sinnoh | complete | HEATRAN |
| StarkMountain_sinnoh | complete |  |
| SunyshoreCity_Gym_sinnoh | complete | guide counted 'seven badges' unconditionally -> generic |
| SunyshoreCity_House1_sinnoh | complete |  |
| SunyshoreCity_House2_sinnoh | complete |  |
| SunyshoreCity_House3_sinnoh | complete | UNDERGROUND chatter kept as flavor (UNDERGROUND MAN says it is closed to visitors) |
| SunyshoreCity_House4_sinnoh | complete |  |
| SunyshoreCity_Market_sinnoh | complete | Seal Case errand and 'Effort Ribbon' remark -> fixed |
| SunyshoreCity_Mart_sinnoh | complete |  |
| SunyshoreCity_PokemonCenter_1F_sinnoh | complete | kid assumed seven badges -> generic |
| SunyshoreCity_PokemonCenter_2F_sinnoh | no events | no visible events (objects, if any, hidden by state flags) |
| SunyshoreCity_VistaLighthouse_sinnoh | complete |  |
| SunyshoreCity_sinnoh | complete |  |
| SurvivalArea_Battleground_sinnoh | complete | welcome said the player was BUCK's friend before meeting him -> GYM LEADERS vouch; CHERYL/MIRA first greetings no longer assume they know the player; daily leader rematches read |
| SurvivalArea_House1_sinnoh | complete | shard tutor |
| SurvivalArea_House2_sinnoh | complete |  |
| SurvivalArea_Mart_sinnoh | complete |  |
| SurvivalArea_PokemonCenter_1F_sinnoh | complete |  |
| SurvivalArea_PokemonCenter_2F_sinnoh | no events | no visible events (objects, if any, hidden by state flags) |
| SurvivalArea_sinnoh | complete | BARRY's first battle spoke as an old friend -> introduces himself |
| TrophyGarden_sinnoh | no events | no visible events (objects, if any, hidden by state flags) |
| TurnbackCave_Entrance_sinnoh | complete |  |
| TurnbackCave_GiratinaRoom_sinnoh | complete | portal asked 'leap in?' as a sign with no answer -> portal is closed |
| TurnbackCave_Pillar1_sinnoh | complete |  |
| TurnbackCave_Pillar2_sinnoh | complete |  |
| TurnbackCave_Pillar3_sinnoh | complete |  |
| TurnbackCave_Room1_sinnoh | no events | no visible events (objects, if any, hidden by state flags) |
| TurnbackCave_Room2_sinnoh | no events | no visible events (objects, if any, hidden by state flags) |
| TurnbackCave_Room3_sinnoh | no events | no visible events (objects, if any, hidden by state flags) |
| TwinleafTown_Haouse1_sinnoh | complete |  |
| TwinleafTown_House2_sinnoh | complete |  |
| TwinleafTown_MainHouse_1F_sinnoh | complete |  |
| TwinleafTown_MainHouse_2F_sinnoh | complete | Platinum BARRY scene hidden |
| TwinleafTown_sinnoh | complete |  |
| Twinleaf_Town_RivalsHouse_F1_sinnoh | complete |  |
| Twinleaf_Town_RivalsHouse_F2_sinnoh | no events | no visible events (objects, if any, hidden by state flags) |
| ValleyWindoworks_Indoor_sinnoh | complete |  |
| ValleyWindworks_sinnoh | complete | LOOKER scene hidden; DRIFLOON |
| ValorLakefront_House1_sinnoh | complete |  |
| ValorLakefront_House2_sinnoh | complete |  |
| ValorLakefront_Restaurant_sinnoh | complete | double battles per table |
| ValorLakefront_sinnoh | complete | Platinum CYNTHIA SecretPotion scene hidden; SUITE KEY lady |
| VeilstoneCity_DepartmentStore_1F_sinnoh | complete |  |
| VeilstoneCity_DepartmentStore_2F_sinnoh | complete | receptionist greeted the player by name -> generic |
| VeilstoneCity_DepartmentStore_3F_sinnoh | complete | same |
| VeilstoneCity_DepartmentStore_4F_sinnoh | complete | same |
| VeilstoneCity_DepartmentStore_5F_sinnoh | complete | vending machine asked for a drink and did nothing -> real vending machine |
| VeilstoneCity_DepartmentStore_Roof_sinnoh | no events | no visible events (objects, if any, hidden by state flags) |
| VeilstoneCity_GalacticWarehouse_sinnoh | complete | CHARON step 4 |
| VeilstoneCity_GameCorner_sinnoh | complete | two NPCs sent the player 'next door' for a COIN CASE nobody gives -> fixed |
| VeilstoneCity_Gym_sinnoh | complete | badge check fixed (4->3) |
| VeilstoneCity_House1_sinnoh | complete |  |
| VeilstoneCity_House2_sinnoh | complete | PORYGON gift |
| VeilstoneCity_House3_sinnoh | complete | massage girl promised a lesson 'tomorrow' forever -> no promise |
| VeilstoneCity_House4_sinnoh | complete | clown COIN CASE game |
| VeilstoneCity_PokemonCenter_1F_sinnoh | complete |  |
| VeilstoneCity_PokemonCenter_2F_sinnoh | no events | no visible events (objects, if any, hidden by state flags) |
| VeilstoneCity_PrizeExchange_sinnoh | complete | Hidden Power reader offered a reading he never gives -> text |
| VeilstoneCity_sinnoh | complete | LOOKER quest 0..8 read; LOOKER called the player SINNOH CHAMPION before the league -> HOENN; Platinum warehouse scenes hidden |
| VerityLakefront_sinnoh | complete |  |
| WaywardCave_1F_sinnoh | complete |  |
| WaywardCave_B1F_sinnoh | complete | ETERNATUS |
