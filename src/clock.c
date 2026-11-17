#include "global.h"
#include "berry.h"
#include "clock.h"
#include "dewford_trend.h"
#include "event_data.h"
#include "field_specials.h"
#include "field_weather.h"
#include "lottery_corner.h"
#include "main.h"
#include "mass_outbreak.h"
#include "overworld.h"
#include "pokerus.h"
#include "random.h"
#include "rtc.h"
#include "time_events.h"
#include "tv.h"
#include "wallclock.h"
#include "constants/form_change_types.h"
#include "apricorn_tree.h"

static void UpdatePerDay(struct Time *localTime);
static void UpdatePerMinute(struct Time *localTime);

void InitTimeBasedEvents(void)
{
    FlagSet(FLAG_SYS_CLOCK_SET);
    RtcCalcLocalTime();
    gSaveBlock2Ptr->lastBerryTreeUpdate = gLocalTime;
    VarSet(VAR_DAYS, gLocalTime.days);
}

void DoTimeBasedEvents(void)
{
    if (FlagGet(FLAG_SYS_CLOCK_SET) && !InPokemonCenter())
    {
        RtcCalcLocalTime();
        UpdatePerDay(&gLocalTime);
        UpdatePerMinute(&gLocalTime);
    }
}

void UpdateDailySeed(void)
{
    gSaveBlock1Ptr->dailySeed = Random32();
}

// Super Emerald: daily flags of Johto, Sinnoh and the rematches live outside the
// vanilla daily block, so they are cleared here one by one.
static const u16 sSEDailyFlags[] =
{
    FLAG_DAILY_FLOWER_SHOP_RECEIVED_BERRY_HNS,
    FLAG_DAILY_BUG_CONTEST_COMPLETED,
    FLAG_DAILY_SN_BARRY, FLAG_DAILY_SN_AMITY, FLAG_DAILY_SN_MAID_DONE, FLAG_DAILY_SN_TROPHY,
    FLAG_DAILY_SN_FOSSIL, FLAG_DAILY_SN_NEWSPRESS, FLAG_DAILY_SN_SPA,
    FLAG_DAILY_SN_BG_ROARK, FLAG_DAILY_SN_BG_GARDENIA, FLAG_DAILY_SN_BG_FANTINA, FLAG_DAILY_SN_BG_MAYLENE,
    FLAG_DAILY_SN_BG_WAKE, FLAG_DAILY_SN_BG_BYRON, FLAG_DAILY_SN_BG_CANDICE, FLAG_DAILY_SN_BG_VOLKNER,
    FLAG_DAILY_SN_BG_BUCK, FLAG_DAILY_SN_BG_CHERYL, FLAG_DAILY_SN_BG_RILEY, FLAG_DAILY_SN_BG_MARLEY,
    FLAG_DAILY_SN_BG_MIRA,
    FLAG_DAILY_SE_KANTO_LEAGUE, FLAG_DAILY_SE_SINNOH_LEAGUE, FLAG_DAILY_SE_RIVAL_ORO, FLAG_DAILY_SE_RIVAL_LUCAS,
};

void DoDailyEvents(u32 daysSince)
{
    u32 i;
    ClearDailyFlags();
    UpdateDailySeed();
    UpdateMassOutbreakDaysLeft(daysSince);
    UpdateDewfordTrendPerDay(daysSince);
    UpdateTVShowsPerDay(daysSince);
    UpdateWeatherPerDay(daysSince);
    UpdatePartyPokerusTime(daysSince);
    UpdateBirchState(daysSince);
    UpdateFrontierManiac(daysSince);
    UpdateFrontierGambler(daysSince);
    SetShoalItemFlag(daysSince);
    if (!OW_USE_DAILY_SEED_FOR_VANILLA_VARIABLES)
    {
        UpdateMirageRnd(daysSince);
        SetRandomLotteryNumber(daysSince);
    }
    UpdateDaysPassedSinceFormChange(daysSince);
    DailyResetApricornTrees();
    for (i = 0; i < ARRAY_COUNT(sSEDailyFlags); i++)
        FlagClear(sSEDailyFlags[i]);
    for (i = FLAG_DAILY_SE_DOJO_BROCK; i <= FLAG_DAILY_SE_DOJO_CLAIR; i++)
        FlagClear(i);
}

static void UpdatePerDay(struct Time *localTime)
{
    u16 *days = GetVarPointer(VAR_DAYS);
    u16 daysSince;

    if (*days != localTime->days && *days <= localTime->days)
    {
        daysSince = localTime->days - *days;
        DoDailyEvents(daysSince);
        *days = localTime->days;
    }
}

static void UpdatePerMinute(struct Time *localTime)
{
    struct Time difference;
    int minutes;

    CalcTimeDifference(&difference, &gSaveBlock2Ptr->lastBerryTreeUpdate, localTime);
    minutes = 24 * 60 * difference.days + 60 * difference.hours + difference.minutes;
    if (minutes != 0)
    {
        if (minutes >= 0)
        {
            BerryTreeTimeUpdate(minutes);
            gSaveBlock2Ptr->lastBerryTreeUpdate = *localTime;
        }
    }
}

void FormChangeTimeUpdate()
{
    s32 i;
    for (i = 0; i < PARTY_SIZE; i++)
    {
        TryFormChange(&gParties[B_TRAINER_PLAYER][i], FORM_CHANGE_TIME_OF_DAY, B_TRAINER_PLAYER);
    }
}

static void ReturnFromStartWallClock(void)
{
    InitTimeBasedEvents();
    SetMainCallback2(CB2_ReturnToFieldContinueScriptPlayMapMusic);
}

void StartWallClock(void)
{
    SetMainCallback2(CB2_StartWallClock);
    gMain.savedCallback = ReturnFromStartWallClock;
}
