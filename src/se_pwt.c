// Super Emerald: Pokemon World Tournament (Johto, Route 40).
// It runs on the Battle Dome engine: while the player is in the PWT maps, the Dome uses the PWT roster
// (gym leaders, Elite Four and champions of every region) instead of the Frontier trainers,
// the player's Pokemon are set to level 50 for the battles, there's no Frontier Brain and
// the Battle Points depend on the cup. The PWT keeps its own Dome records (see SE_SwapDomeData).
#include "global.h"
#include "battle_frontier.h"
#include "data.h"
#include "event_data.h"
#include "pokemon.h"
#include "random.h"
#include "string_util.h"
#include "load_save.h"
#include "party_menu.h"
#include "script_pokemon_util.h"
#include "battle_frontier.h"
#include "constants/battle_frontier.h"
#include "constants/event_objects.h"
#include "constants/frontier_util.h"
#include "constants/items.h"
#include "constants/moves.h"
#include "constants/se_pwt.h"
#include "constants/map_groups.h"
#include "constants/species.h"
#include "constants/trainers.h"
#include "constants/easy_chat.h"
#include "constants/pokemon.h"

#include "data/battle_frontier/se_pwt.h"

// The PWT maps have their own scripts (copies of the Dome's); the engine tells it's the PWT by the map
bool32 SE_IsPwt(void)
{
    u16 map = (gSaveBlock1Ptr->location.mapGroup << 8) | gSaveBlock1Ptr->location.mapNum;
    return map == MAP_POKEMON_WORLD_TOURNAMENT_LOBBY
        || map == MAP_POKEMON_WORLD_TOURNAMENT_CORRIDOR
        || map == MAP_POKEMON_WORLD_TOURNAMENT_PRE_BATTLE_ROOM
        || map == MAP_POKEMON_WORLD_TOURNAMENT_ROOM;
}

static u32 GetCup(void)
{
    u32 cup = VarGet(VAR_SE_PWT_CUP);
    return cup < SE_PWT_CUPS_COUNT ? cup : SE_PWT_CUP_WORLD;
}

// The trainers bring the team of the cup: regional team in the LEADERS cups,
// Champions team in the CHAMPIONS CUP, World team in the WORLD CUP (see tools/sfr/se/pwt_variants.py)
const struct BattleFrontierTrainer *SE_FrontierTrainerList(void)
{
    if (!SE_IsPwt())
        return gBattleFrontierTrainers;
    switch (GetCup())
    {
    case SE_PWT_CUP_WORLD:     return gSEPwtTrainersWorld;
    case SE_PWT_CUP_CHAMPIONS: return gSEPwtTrainers;
    default:                   return gSEPwtTrainersRegional;
    }
}

const struct TrainerMon *SE_FrontierMonList(void)
{
    return SE_IsPwt() ? gSEPwtMons : gBattleFrontierMons;
}

// Full name of a PWT trainer (the Frontier trainer struct only fits 7 characters)
bool32 SE_PwtCopyTrainerName(u8 *dst, u16 trainerId)
{
    if (!SE_IsPwt() || trainerId >= SE_PWT_TRAINERS_COUNT)
        return FALSE;
    StringCopy(dst, gSEPwtNames[trainerId]);
    return TRUE;
}

u16 SE_PwtFacilityClassGfx(u8 facilityClass)
{
    if (facilityClass < FACILITY_CLASS_SE_FIRST || facilityClass >= FACILITY_CLASSES_COUNT)
        return OBJ_EVENT_GFX_BOY_1;
    return gSEPwtGfx[facilityClass - FACILITY_CLASS_SE_FIRST];
}

// --- Choosing the opponents of the cup ---------------------------------------------
// LEADERS cups: 7 gym leaders of the region. CHAMPIONS CUP: 7 of its 8 champions.
// WORLD CUP: 15 among every gym leader, Elite Four member and champion (each one once).

static bool32 IsInRegionCup(u32 id, u32 cup)
{
    switch (cup)
    {
    case SE_PWT_CUP_KANTO:  return (gSEPwtLeaderRegions[id] & (1 << SE_PWT_KANTO)) != 0;
    case SE_PWT_CUP_JOHTO:  return (gSEPwtLeaderRegions[id] & (1 << SE_PWT_JOHTO)) != 0;
    case SE_PWT_CUP_HOENN:  return (gSEPwtLeaderRegions[id] & (1 << SE_PWT_HOENN)) != 0;
    case SE_PWT_CUP_SINNOH: return (gSEPwtLeaderRegions[id] & (1 << SE_PWT_SINNOH)) != 0;
    case SE_PWT_CUP_KALOS:  return (gSEPwtLeaderRegions[id] & (1 << SE_PWT_KALOS)) != 0;
    default:                return FALSE;
    }
}

static bool32 IsInCup(u32 id, u32 cup)
{
    if (cup == SE_PWT_CUP_CHAMPIONS)
        return gSEPwtInChampionsCup[id];
    if (cup == SE_PWT_CUP_WORLD)
        return gSEPwtLeaderRegions[id] != 0
            || gSEPwtRanks[id] == SE_PWT_RANK_ELITE
            || gSEPwtRanks[id] == SE_PWT_RANK_CHAMPION;
    return IsInRegionCup(id, cup);
}

// Trainers in the bracket: the player and 7 rivals, 15 in the WORLD CUP
u32 SE_PwtEntrantsCount(void)
{
    return GetCup() == SE_PWT_CUP_WORLD ? DOME_TOURNAMENT_TRAINERS_COUNT : DOME_TOURNAMENT_TRAINERS_COUNT / 2;
}

static u32 CountCupTrainers(u32 cup)
{
    u32 i, n = 0;
    for (i = 0; i < SE_PWT_TRAINERS_COUNT; i++)
        n += IsInCup(i, cup);
    return n;
}

// VAR_RESULT = TRUE if the chosen cup has enough different rivals
void SE_PwtCupHasEnoughTrainers(void)
{
    gSpecialVar_Result = CountCupTrainers(GetCup()) >= SE_PwtEntrantsCount() - 1;
}

static void SE_PwtShuffle(u16 *list, u32 count)
{
    u32 i;
    for (i = count; i > 1; i--)
    {
        u32 j = Random() % i;
        u16 tmp = list[i - 1];
        list[i - 1] = list[j];
        list[j] = tmp;
    }
}

// Fills ids[0..count-1] with different PWT trainer ids eligible for the current cup.
// Returns how many it found (less than count only if the cup's list is too short).
u32 SE_PwtPickTrainers(u16 *ids, u32 count)
{
    u16 pool[SE_PWT_TRAINERS_COUNT];
    u32 cup = GetCup();
    u32 n = 0, i;

    for (i = 0; i < SE_PWT_TRAINERS_COUNT; i++)
    {
        if (IsInCup(i, cup))
            pool[n++] = i;
    }
    SE_PwtShuffle(pool, n);
    if (n > count)
        n = count;
    for (i = 0; i < n; i++)
        ids[i] = pool[i];
    return n;
}

// The CHAMPIONS CUP has no seeding: the positions in the bracket are drawn
bool32 SE_PwtRandomBracket(void)
{
    return SE_IsPwt() && GetCup() == SE_PWT_CUP_CHAMPIONS;
}

// --- Level 50 ---------------------------------------------------------------------

EWRAM_DATA bool8 gSEPwtPartyScaled = FALSE;

static void SetMonExpToLevel(struct Pokemon *mon, u32 exp)
{
    u32 hp;
    SetMonData(mon, MON_DATA_EXP, &exp);
    CalculateMonStats(mon);
    hp = GetMonData(mon, MON_DATA_MAX_HP);
    SetMonData(mon, MON_DATA_HP, &hp);
}

// The player's battle party: every Pokemon is set to level 50 like in the PWT of B2W2
void SE_PwtScaleParty(void)
{
    u32 i;

    if (!SE_IsPwt())
        return;
    for (i = 0; i < PARTY_SIZE; i++)
    {
        struct Pokemon *mon = &gParties[B_TRAINER_PLAYER][i];
        u32 species = GetMonData(mon, MON_DATA_SPECIES);
        if (species == SPECIES_NONE || GetMonData(mon, MON_DATA_IS_EGG))
            continue;
        SetMonExpToLevel(mon, gExperienceTables[gSpeciesInfo[species].growthRate][FRONTIER_MAX_LEVEL_50]);
    }
    gSEPwtPartyScaled = TRUE;
}

// The Dome copies the battle party back to the saved party (moves, held items...).
// Keep the real level and experience of the Pokemon there.
void SE_PwtKeepRealLevel(u32 index, struct Pokemon *mon)
{
    struct Pokemon *saved = &gSaveBlock1Ptr->playerParty[index];

    if (!gSEPwtPartyScaled)
        return;
    if (GetMonData(saved, MON_DATA_PERSONALITY) != GetMonData(mon, MON_DATA_PERSONALITY)
     || GetMonData(saved, MON_DATA_SPECIES) != GetMonData(mon, MON_DATA_SPECIES))
        return;
    SetMonExpToLevel(mon, GetMonData(saved, MON_DATA_EXP));
}

// --- Separate Dome records ----------------------------------------------------------
// The save holds the Dome records of the facility in use (Hoenn's Battle Dome or the PWT);
// the other one's are kept in VAR_SE_DOME_DATA_START..END.

static void SE_SwapDomeData(void)
{
    u32 i, j, n = 0;
    u16 packed = 0, other;
    struct BattleFrontier *f = &gSaveBlock2Ptr->frontier;

    for (i = 0; i < 2; i++)
    {
        for (j = 0; j < 2; j++)
        {
            u16 tmp = f->domeWinStreaks[i][j];
            f->domeWinStreaks[i][j] = VarGet(VAR_SE_DOME_DATA_START + n);
            VarSet(VAR_SE_DOME_DATA_START + n, tmp);
            tmp = f->domeRecordWinStreaks[i][j];
            f->domeRecordWinStreaks[i][j] = VarGet(VAR_SE_DOME_DATA_START + 4 + n);
            VarSet(VAR_SE_DOME_DATA_START + 4 + n, tmp);
            tmp = f->domeTotalChampionships[i][j];
            f->domeTotalChampionships[i][j] = VarGet(VAR_SE_DOME_DATA_START + 8 + n);
            VarSet(VAR_SE_DOME_DATA_START + 8 + n, tmp);
            n++;
        }
    }

    if (f->domeAttemptedSingles50)   packed |= 1 << 0;
    if (f->domeAttemptedSinglesOpen) packed |= 1 << 1;
    if (f->domeHasWonSingles50)      packed |= 1 << 2;
    if (f->domeHasWonSinglesOpen)    packed |= 1 << 3;
    if (f->domeAttemptedDoubles50)   packed |= 1 << 4;
    if (f->domeAttemptedDoublesOpen) packed |= 1 << 5;
    if (f->domeHasWonDoubles50)      packed |= 1 << 6;
    if (f->domeHasWonDoublesOpen)    packed |= 1 << 7;
    if (f->winStreakActiveFlags & STREAK_DOME_SINGLES_50)   packed |= 1 << 8;
    if (f->winStreakActiveFlags & STREAK_DOME_SINGLES_OPEN) packed |= 1 << 9;
    if (f->winStreakActiveFlags & STREAK_DOME_DOUBLES_50)   packed |= 1 << 10;
    if (f->winStreakActiveFlags & STREAK_DOME_DOUBLES_OPEN) packed |= 1 << 11;
    if (FlagGet(FLAG_SYS_DOME_SILVER)) packed |= 1 << 12;
    if (FlagGet(FLAG_SYS_DOME_GOLD))   packed |= 1 << 13;
    if (f->battledBrainFlags & (1 << (FRONTIER_FACILITY_DOME * 2)))     packed |= 1 << 14;
    if (f->battledBrainFlags & (1 << (FRONTIER_FACILITY_DOME * 2 + 1))) packed |= 1 << 15;

    other = VarGet(VAR_SE_DOME_DATA_END);
    VarSet(VAR_SE_DOME_DATA_END, packed);

    f->domeAttemptedSingles50   = (other >> 0) & 1;
    f->domeAttemptedSinglesOpen = (other >> 1) & 1;
    f->domeHasWonSingles50      = (other >> 2) & 1;
    f->domeHasWonSinglesOpen    = (other >> 3) & 1;
    f->domeAttemptedDoubles50   = (other >> 4) & 1;
    f->domeAttemptedDoublesOpen = (other >> 5) & 1;
    f->domeHasWonDoubles50      = (other >> 6) & 1;
    f->domeHasWonDoublesOpen    = (other >> 7) & 1;
    f->winStreakActiveFlags &= ~(STREAK_DOME_SINGLES_50 | STREAK_DOME_SINGLES_OPEN | STREAK_DOME_DOUBLES_50 | STREAK_DOME_DOUBLES_OPEN);
    if (other & (1 << 8))  f->winStreakActiveFlags |= STREAK_DOME_SINGLES_50;
    if (other & (1 << 9))  f->winStreakActiveFlags |= STREAK_DOME_SINGLES_OPEN;
    if (other & (1 << 10)) f->winStreakActiveFlags |= STREAK_DOME_DOUBLES_50;
    if (other & (1 << 11)) f->winStreakActiveFlags |= STREAK_DOME_DOUBLES_OPEN;
    if (other & (1 << 12)) FlagSet(FLAG_SYS_DOME_SILVER); else FlagClear(FLAG_SYS_DOME_SILVER);
    if (other & (1 << 13)) FlagSet(FLAG_SYS_DOME_GOLD);   else FlagClear(FLAG_SYS_DOME_GOLD);
    f->battledBrainFlags &= ~(3 << (FRONTIER_FACILITY_DOME * 2));
    if (other & (1 << 14)) f->battledBrainFlags |= 1 << (FRONTIER_FACILITY_DOME * 2);
    if (other & (1 << 15)) f->battledBrainFlags |= 1 << (FRONTIER_FACILITY_DOME * 2 + 1);
}

// PWT lobby (on transition)
void SE_EnterPwt(void)
{
    if (!FlagGet(FLAG_SE_DOME_DATA_PWT))
    {
        SE_SwapDomeData();
        FlagSet(FLAG_SE_DOME_DATA_PWT);
    }
}

// Outside the PWT and in Hoenn's Battle Dome lobby (on transition)
void SE_LeavePwt(void)
{
    if (FlagGet(FLAG_SE_DOME_DATA_PWT))
    {
        SE_SwapDomeData();
        FlagClear(FLAG_SE_DOME_DATA_PWT);
    }
}

// --- Cups ---------------------------------------------------------------------------

static const u8 sCupPoints[SE_PWT_CUPS_COUNT] =
{
    [SE_PWT_CUP_KANTO]     = 6,
    [SE_PWT_CUP_JOHTO]     = 6,
    [SE_PWT_CUP_HOENN]     = 6,
    [SE_PWT_CUP_SINNOH]    = 6,
    [SE_PWT_CUP_KALOS]     = 6,
    [SE_PWT_CUP_CHAMPIONS] = 8,
    [SE_PWT_CUP_WORLD]     = 10,
};

u32 SE_PwtBattlePoints(void)
{
    u32 cup = VarGet(VAR_SE_PWT_CUP);
    if (cup >= SE_PWT_CUPS_COUNT)
        cup = SE_PWT_CUP_WORLD;
    return sCupPoints[cup];
}

static const u8 *const sCupNames[SE_PWT_CUPS_COUNT] =
{
    [SE_PWT_CUP_KANTO]     = COMPOUND_STRING("KANTO LEADERS CUP"),
    [SE_PWT_CUP_JOHTO]     = COMPOUND_STRING("JOHTO LEADERS CUP"),
    [SE_PWT_CUP_HOENN]     = COMPOUND_STRING("HOENN LEADERS CUP"),
    [SE_PWT_CUP_SINNOH]    = COMPOUND_STRING("SINNOH LEADERS CUP"),
    [SE_PWT_CUP_KALOS]     = COMPOUND_STRING("KALOS LEADERS CUP"),
    [SE_PWT_CUP_CHAMPIONS] = COMPOUND_STRING("CHAMPIONS CUP"),
    [SE_PWT_CUP_WORLD]     = COMPOUND_STRING("WORLD CUP"),
};

// STR_VAR_3 = name of the cup in VAR_SE_PWT_CUP
void SE_PwtBufferCupName(void)
{
    u32 cup = VarGet(VAR_SE_PWT_CUP);
    if (cup >= SE_PWT_CUPS_COUNT)
        cup = SE_PWT_CUP_WORLD;
    StringCopy(gStringVar3, sCupNames[cup]);
}

// --- First win of each cup: an item typical of the region ----------------------------

static const u16 sCupPrizes[SE_PWT_CUPS_COUNT] =
{
    [SE_PWT_CUP_KANTO]     = ITEM_MASTER_BALL,     // Silph Co.
    [SE_PWT_CUP_JOHTO]     = ITEM_SACRED_ASH,      // Ho-Oh, Bell Tower
    [SE_PWT_CUP_HOENN]     = ITEM_SOUL_DEW,        // Latias and Latios
    [SE_PWT_CUP_SINNOH]    = ITEM_GRISEOUS_ORB,    // Giratina
    [SE_PWT_CUP_KALOS]     = ITEM_LUCARIONITE,     // Mega Evolution, Korrina
    [SE_PWT_CUP_CHAMPIONS] = ITEM_ABILITY_PATCH,
    [SE_PWT_CUP_WORLD]     = ITEM_GOLD_BOTTLE_CAP,
};

// Out: VAR_RESULT = TRUE if this cup's prize hasn't been given yet, VAR_0x8004 = the item
void SE_PwtGetCupPrize(void)
{
    u32 cup = VarGet(VAR_SE_PWT_CUP);
    if (cup >= SE_PWT_CUPS_COUNT)
        cup = SE_PWT_CUP_WORLD;
    gSpecialVar_0x8004 = sCupPrizes[cup];
    gSpecialVar_Result = !FlagGet(FLAG_SE_PWT_PRIZE_KANTO + cup);
}

void SE_PwtSetCupPrizeReceived(void)
{
    u32 cup = VarGet(VAR_SE_PWT_CUP);
    if (cup >= SE_PWT_CUPS_COUNT)
        cup = SE_PWT_CUP_WORLD;
    FlagSet(FLAG_SE_PWT_PRIZE_KANTO + cup);
}

// --- 6 against 6 ------------------------------------------------------------------
// Like in B2W2, the player battles with the whole party (eggs and Frontier-banned Pokemon
// stay out) and the opponents with their 6 Pokemon. The Dome bookkeeping (tourney tree,
// info cards) keeps using the first 3.

// Fills gSelectedOrderFromParty (1-based slots of the saved party) and returns how many
u32 SE_PwtBuildPartyOrder(void)
{
    u32 i, n = 0;

    for (i = 0; i < PARTY_SIZE; i++)
        gSelectedOrderFromParty[i] = 0;
    for (i = 0; i < PARTY_SIZE; i++)
    {
        struct Pokemon *mon = GetSavedPlayerPartyMon(i);
        u32 species = GetMonData(mon, MON_DATA_SPECIES_OR_EGG);
        if (species == SPECIES_NONE || species == SPECIES_EGG)
            continue;
        if (gSpeciesInfo[GetBaseSpecies(species)].isFrontierBanned)
            continue;
        gSelectedOrderFromParty[n++] = i + 1;
    }
    return n;
}

// Lobby: instead of choosing 3 Pokemon, the whole party is entered. The party is saved first
// so the order is built from it. VAR_RESULT: 1 = entered (at least 3 Pokemon), 0 = not enough.
void SE_PwtEnterWholeParty(void)
{
    SavePlayerParty();
    gSpecialVar_Result = SE_PwtBuildPartyOrder() >= FRONTIER_PARTY_SIZE;
}

// The battle party: every entered Pokemon, in party order
void SE_PwtReduceParty(void)
{
    if (SE_PwtBuildPartyOrder() != 0)
        ReducePlayerPartyToSelectedMons();
}

// After a battle: berries and other consumed items come back
void SE_PwtRestoreHeldItems(void)
{
    u32 i, n = SE_PwtBuildPartyOrder();

    for (i = 0; i < n; i++)
    {
        u32 item = GetMonData(GetSavedPlayerPartyMon(gSelectedOrderFromParty[i] - 1), MON_DATA_HELD_ITEM);
        SetMonData(&gParties[B_TRAINER_PLAYER][i], MON_DATA_HELD_ITEM, &item);
    }
}

// The opponent's 6 Pokemon, straight from its PWT team
bool32 SE_PwtFillOpponentParty(u16 trainerId, struct Pokemon *party, struct FacilityMonGenerator *generator)
{
    const u16 *set;
    u32 i;

    if (!SE_IsPwt() || trainerId >= SE_PWT_TRAINERS_COUNT)
        return FALSE;
    set = SE_FrontierTrainerList()[trainerId].monSet;
    for (i = 0; i < PARTY_SIZE && set[i] != 0xFFFF; i++)
        CreateFacilityMon(&party[i], generator, set[i]);
    return TRUE;
}
