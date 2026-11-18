#ifndef GUARD_CONSTANTS_FLAGS_SE_SINNOH_H
#define GUARD_CONSTANTS_FLAGS_SE_SINNOH_H

// Super Emerald: hand-made Sinnoh flags (0x3200-0x327F, after the imported Sinnoh flags).
// Plain numbers on purpose (scripts pass flags to macros).
#define FLAG_SE_SINNOH_LEAGUE_CLEARED        0x3200
#define FLAG_SE_RECEIVED_SINNOH_STARTER      0x3201
#define FLAG_SE_HIDE_CANALAVE_DAWN           0x3202
#define FLAG_SE_HIDE_LUCAS_SANDGEM           0x3203
#define FLAG_SE_HIDE_LUCAS_HEARTHOME         0x3204
#define FLAG_SE_HIDE_LUCAS_VICTORY_ROAD      0x3205
#define FLAG_SE_RECEIVED_SINNOH_TM1          0x3210
#define FLAG_SE_RECEIVED_SINNOH_TM2          0x3211
#define FLAG_SE_RECEIVED_SINNOH_TM3          0x3212
#define FLAG_SE_RECEIVED_SINNOH_TM4          0x3213
#define FLAG_SE_RECEIVED_SINNOH_TM5          0x3214
#define FLAG_SE_RECEIVED_SINNOH_TM6          0x3215
#define FLAG_SE_RECEIVED_SINNOH_TM7          0x3216
#define FLAG_SE_RECEIVED_SINNOH_TM8          0x3217
#define FLAG_SE_DONE_MESPRIT                 0x3206
#define FLAG_SE_DONE_CRESSELIA               0x3207

// Sinnoh Fly destinations
#define FLAG_SE_VISITED_TWINLEAF_TOWN_SINNOH     0x3220
#define FLAG_SE_VISITED_SANDGEM_TOWN_SINNOH      0x3221
#define FLAG_SE_VISITED_JUBILIFE_CITY_SINNOH     0x3222
#define FLAG_SE_VISITED_OREBURGH_CITY_SINNOH     0x3223
#define FLAG_SE_VISITED_FLOAROMA_TOWN_SINNOH     0x3224
#define FLAG_SE_VISITED_ETERNA_CITY_SINNOH       0x3225
#define FLAG_SE_VISITED_HEARTHOME_CITY_SINNOH    0x3226
#define FLAG_SE_VISITED_SOLACEON_TOWN_SINNOH     0x3227
#define FLAG_SE_VISITED_VEILSTONE_CITY_SINNOH    0x3228
#define FLAG_SE_VISITED_PASTORIA_CITY_SINNOH     0x3229
#define FLAG_SE_VISITED_CELESTIC_TOWN_SINNOH     0x322A
#define FLAG_SE_VISITED_CANALAVE_CITY_SINNOH     0x322B
#define FLAG_SE_VISITED_SNOWPOINT_CITY_SINNOH    0x322C
#define FLAG_SE_VISITED_SUNYSHORE_CITY_SINNOH    0x322D
#define FLAG_SE_VISITED_POKEMON_LEAGUE_SINNOH    0x322E
#define FLAG_SE_VISITED_FIGHT_AREA_SINNOH        0x322F
#define FLAG_SE_VISITED_SURVIVAL_AREA_SINNOH     0x3230
#define FLAG_SE_VISITED_RESORT_AREA_SINNOH       0x3231
#define FLAG_SN_BG_WELCOMED                      0x3232 // the Battleground expert has welcomed the player

// Daily rematches: Gym Leaders of Kanto and Johto at the Saffron Dojo, and the two Leagues.
// Cleared every day in DoDailyEvents (src/clock.c).
#define FLAG_DAILY_SE_DOJO_BROCK                 0x3240
#define FLAG_DAILY_SE_DOJO_MISTY                 0x3241
#define FLAG_DAILY_SE_DOJO_LT_SURGE              0x3242
#define FLAG_DAILY_SE_DOJO_ERIKA                 0x3243
#define FLAG_DAILY_SE_DOJO_KOGA                  0x3244
#define FLAG_DAILY_SE_DOJO_SABRINA               0x3245
#define FLAG_DAILY_SE_DOJO_BLAINE                0x3246
#define FLAG_DAILY_SE_DOJO_BLUE                  0x3247
#define FLAG_DAILY_SE_DOJO_FALKNER               0x3248
#define FLAG_DAILY_SE_DOJO_BUGSY                 0x3249
#define FLAG_DAILY_SE_DOJO_WHITNEY               0x324A
#define FLAG_DAILY_SE_DOJO_MORTY                 0x324B
#define FLAG_DAILY_SE_DOJO_CHUCK                 0x324C
#define FLAG_DAILY_SE_DOJO_JASMINE               0x324D
#define FLAG_DAILY_SE_DOJO_PRYCE                 0x324E
#define FLAG_DAILY_SE_DOJO_CLAIR                 0x324F
#define FLAG_DAILY_SE_KANTO_LEAGUE               0x3250
#define FLAG_DAILY_SE_SINNOH_LEAGUE              0x3251
#define FLAG_DAILY_SE_RIVAL_ORO                  0x3252
#define FLAG_DAILY_SE_RIVAL_LUCAS                0x3253

// Celebi event at the Ilex Forest shrine (GS Ball from the Ruins of Alph)
#define FLAG_SE_GS_BALL_PLACED                   0x3260
#define FLAG_SE_DONE_CELEBI                      0x3261

// National Dex completion (tools/sfr/se/dexfill_events.py)
#define FLAG_SE_GIFT_STARTERS_UNOVA      0x3262
#define FLAG_SE_GIFT_STARTERS_KALOS      0x3263
#define FLAG_SE_GIFT_STARTERS_PALDEA     0x3264
#define FLAG_SE_GIFT_STARTERS_GALAR      0x3265
#define FLAG_SE_GIFT_STARTERS_ALOLA      0x3266
// Static legendaries: hidden until the Sinnoh League is cleared (see event_object_movement.c)
#define FLAG_SE_LEGENDS_START                    0x3280
#define FLAG_SE_LEG_VICTINI              0x3280
#define FLAG_SE_LEG_KELDEO               0x3281
#define FLAG_SE_LEG_MELOETTA             0x3282
#define FLAG_SE_LEG_COBALION             0x3283
#define FLAG_SE_LEG_TERRAKION            0x3284
#define FLAG_SE_LEG_VIRIZION             0x3285
#define FLAG_SE_LEG_TORNADUS             0x3286
#define FLAG_SE_LEG_THUNDURUS            0x3287
#define FLAG_SE_LEG_LANDORUS             0x3288
#define FLAG_SE_LEG_RESHIRAM             0x3289
#define FLAG_SE_LEG_ZEKROM               0x328A
#define FLAG_SE_LEG_KYUREM               0x328B
#define FLAG_SE_LEG_JIRACHI              0x328C
#define FLAG_SE_LEG_XERNEAS              0x328D
#define FLAG_SE_LEG_YVELTAL              0x328E
#define FLAG_SE_LEG_ZYGARDE              0x328F
#define FLAG_SE_LEG_DIANCIE              0x3290
#define FLAG_SE_LEG_HOOPA                0x3291
#define FLAG_SE_LEG_VOLCANION            0x3292
#define FLAG_SE_LEG_KORAIDON             0x3293
#define FLAG_SE_LEG_MIRAIDON             0x3294
#define FLAG_SE_LEG_TERAPAGOS            0x3295
#define FLAG_SE_LEG_PECHARUNT            0x3296
#define FLAG_SE_LEG_TING_LU              0x3297
#define FLAG_SE_LEG_CHIEN_PAO            0x3298
#define FLAG_SE_LEG_WO_CHIEN             0x3299
#define FLAG_SE_LEG_CHI_YU               0x329A
#define FLAG_SE_LEG_OKIDOGI              0x329B
#define FLAG_SE_LEG_MUNKIDORI            0x329C
#define FLAG_SE_LEG_FEZANDIPITI          0x329D
#define FLAG_SE_LEG_WALKING_WAKE         0x329E
#define FLAG_SE_LEG_IRON_LEAVES          0x329F
#define FLAG_SE_LEG_IRON_BOULDER         0x32A0
#define FLAG_SE_LEG_IRON_CROWN           0x32A1
#define FLAG_SE_LEG_RAGING_BOLT          0x32A2
#define FLAG_SE_LEG_GOUGING_FIRE         0x32A3
#define FLAG_SE_LEG_ZACIAN               0x32A4
#define FLAG_SE_LEG_ZAMAZENTA            0x32A5
#define FLAG_SE_LEG_ETERNATUS            0x32A6
#define FLAG_SE_LEG_KUBFU                0x32A7
#define FLAG_SE_LEG_ZARUDE               0x32A8
#define FLAG_SE_LEG_GLASTRIER            0x32A9
#define FLAG_SE_LEG_SPECTRIER            0x32AA
#define FLAG_SE_LEG_CALYREX              0x32AB
#define FLAG_SE_LEG_ENAMORUS             0x32AC
#define FLAG_SE_LEG_MANAPHY              0x32AD
#define FLAG_SE_LEG_BLACEPHALON          0x32AE
#define FLAG_SE_LEG_MARSHADOW            0x32AF
#define FLAG_SE_LEG_TAPU_FINI            0x32B0
#define FLAG_SE_LEG_NIHILEGO             0x32B1
#define FLAG_SE_LEG_POIPOLE              0x32B2
#define FLAG_SE_LEG_TAPU_LELE            0x32B3
#define FLAG_SE_LEG_TAPU_KOKO            0x32B4
#define FLAG_SE_LEG_TAPU_BULU            0x32B5
#define FLAG_SE_LEG_KARTANA              0x32B6
#define FLAG_SE_LEG_BUZZWOLE             0x32B7
#define FLAG_SE_LEG_PHEROMOSA            0x32B8
#define FLAG_SE_LEG_ZERAORA              0x32B9
#define FLAG_SE_LEG_MAGEARNA             0x32BA
#define FLAG_SE_LEG_CELESTEELA           0x32BB
#define FLAG_SE_LEG_XURKITREE            0x32BC
#define FLAG_SE_LEG_COSMOG               0x32BD
#define FLAG_SE_LEG_NECROZMA             0x32BE
#define FLAG_SE_LEG_STAKATAKA            0x32BF
#define FLAG_SE_LEG_GUZZLORD             0x32C0
#define FLAG_SE_LEG_MELTAN               0x32C1
#define FLAG_SE_LEG_TYPE_NULL            0x32C2
#define FLAG_SE_LEG_MELMETAL             0x32C3
#define FLAG_SE_LEGENDS_END                      0x32C3

// Super Emerald: side-quest objects. Never set; each one is shown only at its quest stage (see IsObjectTemplateHidden)
#define FLAG_SE_QUEST_OBJ_START          0x32C4
#define FLAG_SE_QUEST_WALLY_JOHTO        0x32C4
#define FLAG_SE_QUEST_WALLY_KANTO        0x32C5
#define FLAG_SE_QUEST_WALLY_SINNOH       0x32C6
#define FLAG_SE_QUEST_STEVEN_JOHTO       0x32C7
#define FLAG_SE_QUEST_STEVEN_KANTO       0x32C8
#define FLAG_SE_QUEST_STEVEN_SINNOH      0x32C9
#define FLAG_SE_QUEST_OBJ_END            0x32C9

#endif // GUARD_CONSTANTS_FLAGS_SE_SINNOH_H
