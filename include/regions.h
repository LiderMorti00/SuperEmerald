#ifndef GUARD_REGIONS_H
#define GUARD_REGIONS_H

#include "global.h"
#include "constants/regions.h"

enum KantoSubRegion GetKantoSubregion(u32 mapSecId);

static inline enum Region GetRegionForSectionId(u32 sectionId)
{
    if (sectionId >= KANTO_MAPSEC_START && sectionId < MAPSEC_SPECIAL_AREA)
        return REGION_KANTO;
    if (sectionId >= JOHTO_MAPSEC_START && sectionId <= JOHTO_MAPSEC_END)
        return REGION_JOHTO;
    if (sectionId >= SINNOH_MAPSEC_START && sectionId <= SINNOH_MAPSEC_END)
        return REGION_SINNOH;
    return REGION_HOENN;
}

// TRUE for any section that has an entry in gRegionMapEntries (skips the
// unused gap between the 8-bit sections and the Johto block).
static inline bool32 IsValidMapSec(u32 sectionId)
{
    return sectionId < MAPSEC_NONE
        || (sectionId >= JOHTO_MAPSEC_START && sectionId < MAPSEC_TOTAL_COUNT
            && !(sectionId > JOHTO_MAPSEC_END && sectionId < SINNOH_MAPSEC_START));
}

static inline enum Region GetCurrentRegion(void)
{
    return GetRegionForSectionId(gMapHeader.regionMapSectionId);
}

// Super Fire Red: Kanto and Hoenn share one build, so things that used to depend
// on IS_FRLG now check where the player is (or which tileset style the map uses).
static inline bool32 IsInKanto(void)
{
    return GetCurrentRegion() == REGION_KANTO;
}

static inline bool32 IsInJohto(void)
{
    return GetCurrentRegion() == REGION_JOHTO;
}

static inline bool32 IsInSinnoh(void)
{
    return GetCurrentRegion() == REGION_SINNOH;
}

#define IS_FRLG_MAP_LAYOUT (gMapHeader.mapLayout->isFrlg)

#endif // GUARD_REGIONS_H
