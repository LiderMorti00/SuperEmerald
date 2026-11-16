// Super Emerald: the Bug-Catching Contest, ported from Pokemon Heart & Soul
// (https://github.com/PokemonHnS-Development/pokehns-expansion) and adapted.
#include "global.h"
#include "battle.h"
#include "bug_contest.h"
#include "event_data.h"
#include "field_screen_effect.h"
#include "fieldmap.h"
#include "item.h"
#include "load_save.h"
#include "main.h"
#include "overworld.h"
#include "pokemon.h"
#include "pokemon_storage_system.h"
#include "random.h"
#include "script.h"
#include "string_util.h"
#include "constants/battle.h"
#include "constants/items.h"
#include "constants/maps.h"
#include "constants/species.h"

static EWRAM_DATA u32 sBugContestStartTime = 0;
static EWRAM_DATA bool8 sBugContestTimerActive = FALSE;

bool32 GetBugContestFlag(void)
{
    return FlagGet(FLAG_SYS_BUG_CONTEST_MODE);
}

void BugContestRetirePrompt(void)
{
    ScriptContext_SetupScript(BugContest_EventScript_TimesUp);
}

void EnterBugContestMode(void)
{
    FlagSet(FLAG_SYS_BUG_CONTEST_MODE);
    sBugContestStartTime = gMain.vblankCounter1;
    sBugContestTimerActive = TRUE;
}

void ExitBugContestMode(void)
{
    FlagClear(FLAG_SYS_BUG_CONTEST_MODE);
    sBugContestTimerActive = FALSE;
}

bool8 BugContestCheckTimeLimit(void)
{
    u32 elapsed;

    if (!FlagGet(FLAG_SYS_BUG_CONTEST_MODE) || !sBugContestTimerActive)
        return FALSE;

    elapsed = gMain.vblankCounter1 - sBugContestStartTime;
    if (elapsed >= BUG_CONTEST_TIME_LIMIT_FRAMES)
    {
        sBugContestTimerActive = FALSE;
        ScriptContext_SetupScript(BugContest_EventScript_TimesUp);
        return TRUE;
    }
    return FALSE;
}

// Replaces HnS's remove5mons: only the lead Pokemon enters the park (SavePlayerParty has
// already stored the whole party). VAR_RESULT = MON_CANT_GIVE if the lead has fainted.
void SE_BugContestKeepFirstMon(void)
{
    u32 i;

    if (GetMonData(&gParties[B_TRAINER_PLAYER][0], MON_DATA_HP) == 0 || GetMonData(&gParties[B_TRAINER_PLAYER][0], MON_DATA_IS_EGG))
    {
        gSpecialVar_Result = MON_CANT_GIVE;
        return;
    }
    for (i = 1; i < PARTY_SIZE; i++)
        ZeroMonData(&gParties[B_TRAINER_PLAYER][i]);
    CalculatePlayerPartyCount();
    gSpecialVar_Result = MON_GIVEN_TO_PARTY;
}

// Leaving the contest without finishing it (white out, Fly, Escape Rope...): give the
// party back and drop the Sport Balls.
void SE_BugContestCleanupOnLeave(void)
{
    if (!FlagGet(FLAG_SYS_BUG_CONTEST_MODE))
        return;
    if (gSaveBlock1Ptr->location.mapGroup == MAP_GROUP(MAP_NATIONAL_PARK_BUG_CONTEST_HNS)
     && gSaveBlock1Ptr->location.mapNum == MAP_NUM(MAP_NATIONAL_PARK_BUG_CONTEST_HNS))
        return;
    LoadPlayerParty();
    ExitBugContestMode();
    RemoveSportBalls();
    VarSet(VAR_BUG_CONTEST_STATE, 0);
}

bool8 TransferBugContestMon(void)
{
    u8 monIndex = VarGet(VAR_0x8004);
    struct Pokemon *mon = &gParties[B_TRAINER_PLAYER][monIndex];

    if (CopyMonToPC(mon) == MON_GIVEN_TO_PC)
    {
        ZeroMonData(mon);
        CompactPartySlots();
        gSpecialVar_Result = MON_GIVEN_TO_PC;
    }
    else
    {
        gSpecialVar_Result = MON_CANT_GIVE;
    }
    return FALSE;
}

// Score: level, IVs, how much HP is left and how rare the bug is, against the other
// contestants' rolls. VAR_RESULT = place (1-3), VAR_0x8005 = prize.
bool8 JudgeBugContestMon(void)
{
    struct Pokemon *mon = &gParties[B_TRAINER_PLAYER][VarGet(VAR_0x8004)];
    u32 species = GetMonData(mon, MON_DATA_SPECIES);
    u32 score = GetMonData(mon, MON_DATA_LEVEL);
    u32 ivs = GetMonData(mon, MON_DATA_HP_IV) + GetMonData(mon, MON_DATA_ATK_IV) + GetMonData(mon, MON_DATA_DEF_IV)
            + GetMonData(mon, MON_DATA_SPEED_IV) + GetMonData(mon, MON_DATA_SPATK_IV) + GetMonData(mon, MON_DATA_SPDEF_IV);
    u32 maxHP = GetMonData(mon, MON_DATA_MAX_HP);
    u32 placement;

    score += ivs / 4;
    if (maxHP)
        score += (GetMonData(mon, MON_DATA_HP) * 20) / maxHP;
    switch (species)
    {
    case SPECIES_SCYTHER: case SPECIES_PINSIR:      score += 30; break;
    case SPECIES_BUTTERFREE: case SPECIES_BEEDRILL: score += 20; break;
    case SPECIES_VENONAT: case SPECIES_PARAS:       score += 10; break;
    default: break;
    }

    if (score >= 100 + Random() % 15)
        placement = 1;
    else if (score >= 80 + Random() % 15)
        placement = 2;
    else
        placement = 3;
    gSpecialVar_Result = placement;

    {
        static const u16 sFirstPlaceRewards[]  = { ITEM_SUN_STONE, ITEM_MOON_STONE, ITEM_SHINY_STONE };
        static const u16 sSecondPlaceRewards[] = { ITEM_EVERSTONE, ITEM_FIRE_STONE, ITEM_LEAF_STONE };
        static const u16 sThirdPlaceRewards[]  = {
            ITEM_SITRUS_BERRY, ITEM_LUM_BERRY, ITEM_ORAN_BERRY, ITEM_PECHA_BERRY, ITEM_RAWST_BERRY
        };
        switch (placement)
        {
        case 1:  VarSet(VAR_0x8005, sFirstPlaceRewards[Random() % ARRAY_COUNT(sFirstPlaceRewards)]); break;
        case 2:  VarSet(VAR_0x8005, sSecondPlaceRewards[Random() % ARRAY_COUNT(sSecondPlaceRewards)]); break;
        default: VarSet(VAR_0x8005, sThirdPlaceRewards[Random() % ARRAY_COUNT(sThirdPlaceRewards)]); break;
        }
    }
    return FALSE;
}

void CB2_EndBugContestBattle(void)
{
    CpuFill16(0, (void *)(BG_PLTT), BG_PLTT_SIZE);
    ResetOamRange(0, 128);

    if (gBattleOutcome == B_OUTCOME_LOST || gBattleOutcome == B_OUTCOME_DREW)
    {
        SetMainCallback2(CB2_BugContestWhiteOut);
        return;
    }
    if (gBattleOutcome == B_OUTCOME_CAUGHT && CalculatePlayerPartyCount() == PARTY_SIZE)
        ScriptContext_SetupScript(BugContest_EventScript_TimesUp);
    SetMainCallback2(CB2_ReturnToField);
    gFieldCallback = FieldCB_ReturnToFieldNoScriptCheckMusic;
}

bool8 RemoveSportBalls(void)
{
    u16 count = CountTotalItemQuantityInBag(ITEM_SPORT_BALL);
    if (count > 0)
        RemoveBagItem(ITEM_SPORT_BALL, count);
    return FALSE;
}

bool8 ShowBugContestChosenMon(void)
{
    u16 species = GetMonData(&gParties[B_TRAINER_PLAYER][VarGet(VAR_0x8004)], MON_DATA_SPECIES);

    StringCopy(gStringVar1, GetSpeciesName(species));
    switch (species)
    {
    case SPECIES_CATERPIE:   gSpecialVar_Result = 22; break;
    case SPECIES_WEEDLE:     gSpecialVar_Result = 23; break;
    case SPECIES_METAPOD:    gSpecialVar_Result = 24; break;
    case SPECIES_KAKUNA:     gSpecialVar_Result = 25; break;
    case SPECIES_PARAS:      gSpecialVar_Result = 26; break;
    case SPECIES_VENONAT:    gSpecialVar_Result = 27; break;
    case SPECIES_BUTTERFREE: gSpecialVar_Result = 28; break;
    case SPECIES_BEEDRILL:   gSpecialVar_Result = 29; break;
    case SPECIES_SCYTHER:    gSpecialVar_Result = 30; break;
    case SPECIES_PINSIR:     gSpecialVar_Result = 31; break;
    default:                 gSpecialVar_Result = 0;  break;
    }
    return FALSE;
}
