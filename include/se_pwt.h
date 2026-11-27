#ifndef GUARD_SE_PWT_H
#define GUARD_SE_PWT_H

// Super Emerald: Pokemon World Tournament (runs on the Battle Dome engine), see src/se_pwt.c
extern bool8 gSEPwtPartyScaled;

bool32 SE_IsPwt(void);
const struct BattleFrontierTrainer *SE_FrontierTrainerList(void);
const struct TrainerMon *SE_FrontierMonList(void);
bool32 SE_PwtCopyTrainerName(u8 *dst, u16 trainerId);
u16 SE_PwtFacilityClassGfx(u8 facilityClass);
u32 SE_PwtPickTrainers(u16 *ids, u32 count);
u32 SE_PwtEntrantsCount(void);
bool32 SE_PwtRandomBracket(void);
void SE_PwtCupHasEnoughTrainers(void);
void SE_PwtScaleParty(void);
void SE_PwtKeepRealLevel(u32 index, struct Pokemon *mon);
u32 SE_PwtBattlePoints(void);
u32 SE_PwtBuildPartyOrder(void);
void SE_PwtEnterWholeParty(void);
void SE_PwtReduceParty(void);
void SE_PwtRestoreHeldItems(void);
struct FacilityMonGenerator;
bool32 SE_PwtFillOpponentParty(u16 trainerId, struct Pokemon *party, struct FacilityMonGenerator *generator);

#endif // GUARD_SE_PWT_H
