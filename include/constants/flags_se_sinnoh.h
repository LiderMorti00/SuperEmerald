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

#endif // GUARD_CONSTANTS_FLAGS_SE_SINNOH_H
