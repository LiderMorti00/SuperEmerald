#include "global.h"
#include "bg.h"
#include "decompress.h"
#include "landmark.h"
#include "event_data.h"
#include "item.h"
#include "constants/items.h"
#include "field_effect.h"
#include "main.h"
#include "menu.h"
#include "overworld.h"
#include "palette.h"
#include "pokenav.h"
#include "region_map.h"
#include "sound.h"
#include "sprite.h"
#include "string_util.h"
#include "task.h"
#include "text_window.h"
#include "util.h"
#include "window.h"
#include "constants/rgb.h"
#include "constants/songs.h"
#include "constants/region_map_sections.h"

#define GFXTAG_CITY_ZOOM 6
#define PALTAG_CITY_ZOOM 11

#define NUM_CITY_MAPS 22

struct Pokenav_RegionMapMenu
{
    u8 worldSel;
    bool8 inRegion;
    u8 unused[10];
    bool32 zoomDisabled;
    u32 (*callback)(struct Pokenav_RegionMapMenu *);
};

struct Pokenav_RegionMapGfx
{
    bool32 (*isTaskActiveCB)(void);
    u32 loopTaskId;
    u16 infoWindowId;
    bool8 regionGfxLoaded;
    struct Sprite *cityZoomTextSprites[3];
    u8 ALIGNED(2) tilemapBuffer[BG_SCREEN_SIZE];
    u8 cityZoomPics[NUM_CITY_MAPS][200];
};

struct CityMapEntry
{
    mapsec_u16_t mapSecId;
    u16 index;
    const u32 *tilemap;
};

static u32 HandleRegionMapInput(struct Pokenav_RegionMapMenu *);
static u32 HandleRegionMapInputZoomDisabled(struct Pokenav_RegionMapMenu *);
static u32 GetExitRegionMapMenuId(struct Pokenav_RegionMapMenu *);
static u32 LoopedTask_DecompressCityMaps(s32);
static bool32 GetCurrentLoopedTaskActive(void);
static void FreeCityZoomViewGfx(void);
static void LoadCityZoomViewGfx(void);
static void DecompressCityMaps(void);
static bool32 IsDecompressCityMapsActive(void);
static void LoadPokenavRegionMapGfx(struct Pokenav_RegionMapGfx *);
static bool32 TryFreeTempTileDataBuffers(void);
static void UpdateMapSecInfoWindow(struct Pokenav_RegionMapGfx *);
static bool32 IsDma3ManagerBusyWithBgCopy_(struct Pokenav_RegionMapGfx *);
static void ChangeBgYForZoom(bool32);
static bool32 IsChangeBgYForZoomActive(void);
static void CreateCityZoomTextSprites(void);
static void DrawCityMap(struct Pokenav_RegionMapGfx *, mapsec_s32_t, int);
static void PrintLandmarkNames(struct Pokenav_RegionMapGfx *, mapsec_s32_t, int);
static void SetCityZoomTextInvisibility(bool32);
static void Task_ChangeBgYForZoom(u8 taskId);
static void UpdateCityZoomTextPosition(void);
static void SpriteCB_CityZoomText(struct Sprite *sprite);
static u32 LoopedTask_UpdateInfoAfterCursorMove(s32);
static u32 LoopedTask_RegionMapZoomOut(s32);
static u32 LoopedTask_RegionMapZoomIn(s32);
static u32 LoopedTask_ExitRegionMap(s32);
static u32 LoopedTask_TreatAsPokeNavFlyMap(s32);
static u32 HandleWorldMapInput(struct Pokenav_RegionMapMenu *);
static u32 OpenRegionMapStep(s32, bool32);
static u32 OpenWorldMapStep(s32, bool32);
static u32 LoopedTask_OpenWorldMap(s32);
static u32 LoopedTask_WorldMapMoved(s32);
static u32 LoopedTask_OpenRegionFromWorld(s32);
static u32 LoopedTask_BackToWorldMap(s32);
static bool32 CanFlyFromPokenavMap(struct RegionMap *regionMap);

extern const u16 gRegionMapCityZoomTiles_Pal[];
extern const u32 gRegionMapCityZoomText_Gfx[];

static const u16 sMapSecInfoWindow_Pal[] = INCGFX_U16("graphics/pokenav/region_map/info_window.pal", ".gbapal");
static const u32 sRegionMapCityZoomTiles_Gfx[] = INCGFX_U32("graphics/pokenav/region_map/zoom_tiles.png", ".4bpp.smol");

#include "regions.h"
#include "data/region_map/city_map_tilemaps.h"

static const struct BgTemplate sRegionMapBgTemplates[3] =
{
    {
        .bg = 1,
        .charBaseIndex = 1,
        .mapBaseIndex = 0x1F,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 1,
        .baseTile = 0
    },
    {
        .bg = 2,
        .charBaseIndex = 2,
        .mapBaseIndex = 0x06,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 2,
        .baseTile = 0
    },
    {
        .bg = 2,
        .charBaseIndex = 0,
        .mapBaseIndex = 0x00,
        .screenSize = 2,
        .paletteMode = 0,
        .priority = 3,
        .baseTile = 0
    },
};

static const LoopedTask sRegionMapLoopTaskFuncs[] =
{
    [POKENAV_MAP_FUNC_NONE]         = NULL,
    [POKENAV_MAP_FUNC_CURSOR_MOVED] = LoopedTask_UpdateInfoAfterCursorMove,
    [POKENAV_MAP_FUNC_ZOOM_OUT]     = LoopedTask_RegionMapZoomOut,
    [POKENAV_MAP_FUNC_ZOOM_IN]      = LoopedTask_RegionMapZoomIn,
    [POKENAV_MAP_FUNC_EXIT]         = LoopedTask_ExitRegionMap,
    [POKENAV_MAP_FUNC_FLY]          = LoopedTask_TreatAsPokeNavFlyMap,
    [POKENAV_MAP_FUNC_WORLD_MOVED]  = LoopedTask_WorldMapMoved,
    [POKENAV_MAP_FUNC_OPEN_REGION]  = LoopedTask_OpenRegionFromWorld,
    [POKENAV_MAP_FUNC_BACK_TO_WORLD] = LoopedTask_BackToWorldMap,
};

static const struct CompressedSpriteSheet sCityZoomTextSpriteSheet[1] =
{
    {gRegionMapCityZoomText_Gfx, 0x800, GFXTAG_CITY_ZOOM}
};

static const struct SpritePalette sCityZoomTilesSpritePalette[] =
{
    {gRegionMapCityZoomTiles_Pal, PALTAG_CITY_ZOOM},
    {}
};

static const struct WindowTemplate sMapSecInfoWindowTemplate =
{
    .bg = 1,
    .tilemapLeft = 17,
    .tilemapTop = 4,
    .width = 12,
    .height = 13,
    .paletteNum = 1,
    .baseBlock = 0x4C
};

#include "data/region_map/city_map_entries.h"

static const struct OamData sCityZoomTextSprite_OamData =
{
    .y = 0,
    .affineMode = ST_OAM_AFFINE_OFF,
    .objMode = ST_OAM_OBJ_NORMAL,
    .bpp = ST_OAM_4BPP,
    .shape = SPRITE_SHAPE(32x8),
    .x = 0,
    .size = SPRITE_SIZE(32x8),
    .tileNum = 0,
    .priority = 1,
    .paletteNum = 0,
};

static const struct SpriteTemplate sCityZoomTextSpriteTemplate =
{
    .tileTag = GFXTAG_CITY_ZOOM,
    .paletteTag = PALTAG_CITY_ZOOM,
    .oam = &sCityZoomTextSprite_OamData,
    .callback = SpriteCB_CityZoomText,
};

// ---------------------------------------------------------------------------
// Super Emerald: world overview map (Hoenn, Johto, Kanto, Sinnoh, Sevii Islands)
// The picture is a 4bpp text BG. Every BG palette from 5 to 14 holds the same
// colours; a palette belongs to one region (or to the sea) so the selected
// region can be lit and the others dimmed. Colours 13-15 draw the sea lanes,
// and each palette says which lane each of those colours belongs to.
// The land is drawn from the coastlines of the regional maps themselves.
// graphics/pokenav/region_map/world_map.* are made by tools/sfr/world_map_gen.py

enum {
    WORLD_HOENN,
    WORLD_JOHTO,
    WORLD_KANTO,
    WORLD_SINNOH,
    WORLD_SEVII123,
    WORLD_SEVII45,
    WORLD_SEVII67,
    WORLD_COUNT,
    WORLD_SEVII_ALL = WORLD_COUNT,
    WORLD_SEA,
};

enum {
    LANE_NONE,
    LANE_SLATEPORT_OLIVINE,   // S.S. TIDAL, JOHTO TICKET
    LANE_OLIVINE_VERMILION,   // S.S. AQUA, after the JOHTO LEAGUE
    LANE_VERMILION_CANALAVE,  // S.S. AQUA, CANALAVE TICKET
    LANE_VERMILION_SEVII,     // SEAGALLOP, RAINBOW PASS
    LANE_OLIVINE_CHANNEL,     // the stretch both Olivine lanes share
    LANE_COUNT
};

#define WORLD_MAP_FIRST_PAL 5
#define WORLD_MAP_NUM_PALS  10

static const u16 sWorldMap_Pal[] = INCGFX_U16("graphics/pokenav/region_map/world_map.pal", ".gbapal");
static const u32 sWorldMap_Gfx[] = INCGFX_U32("graphics/pokenav/region_map/world_map.png", ".4bpp.smol");
static const u32 sWorldMap_Tilemap[] = INCGFX_U32("graphics/pokenav/region_map/world_map.bin", ".smolTM");

static const struct {
    u8 owner;
    u8 lanes[3];
} sWorldMapPalettes[WORLD_MAP_NUM_PALS] =
{
    {WORLD_HOENN,     {LANE_SLATEPORT_OLIVINE, LANE_OLIVINE_VERMILION, LANE_OLIVINE_CHANNEL}},
    {WORLD_JOHTO,     {LANE_SLATEPORT_OLIVINE, LANE_OLIVINE_VERMILION, LANE_OLIVINE_CHANNEL}},
    {WORLD_KANTO,     {LANE_VERMILION_SEVII,   LANE_OLIVINE_VERMILION, LANE_VERMILION_CANALAVE}},
    {WORLD_SINNOH,    {LANE_SLATEPORT_OLIVINE, LANE_OLIVINE_VERMILION, LANE_VERMILION_CANALAVE}},
    {WORLD_SEVII123,  {LANE_VERMILION_SEVII}},
    {WORLD_SEVII45,   {LANE_VERMILION_SEVII}},
    {WORLD_SEVII67,   {LANE_VERMILION_SEVII}},
    {WORLD_SEVII_ALL, {LANE_VERMILION_SEVII}},
    {WORLD_SEA,       {LANE_SLATEPORT_OLIVINE, LANE_OLIVINE_VERMILION, LANE_OLIVINE_CHANNEL}},
    {WORLD_SEA,       {LANE_VERMILION_SEVII,   LANE_OLIVINE_VERMILION, LANE_VERMILION_CANALAVE}},
};

static const u8 sWorldTargetRegionMap[WORLD_COUNT] =
{
    [WORLD_HOENN]    = REGION_MAP_HOENN,
    [WORLD_JOHTO]    = REGION_MAP_JOHTO,
    [WORLD_KANTO]    = REGION_MAP_KANTO,
    [WORLD_SINNOH]   = REGION_MAP_SINNOH,
    [WORLD_SEVII123] = REGION_MAP_SEVII123,
    [WORLD_SEVII45]  = REGION_MAP_SEVII45,
    [WORLD_SEVII67]  = REGION_MAP_SEVII67,
};

// Up, down, left, right
#define NO_TARGET 0xFF
static const u8 sWorldTargetNeighbors[WORLD_COUNT][4] =
{
    [WORLD_HOENN]    = {WORLD_JOHTO,    NO_TARGET,     NO_TARGET,      WORLD_SEVII123},
    [WORLD_JOHTO]    = {NO_TARGET,      WORLD_HOENN,   NO_TARGET,      WORLD_KANTO},
    [WORLD_KANTO]    = {NO_TARGET,      WORLD_SEVII123, WORLD_JOHTO,   WORLD_SINNOH},
    [WORLD_SINNOH]   = {NO_TARGET,      WORLD_SEVII45, WORLD_KANTO,    NO_TARGET},
    [WORLD_SEVII123] = {WORLD_KANTO,    WORLD_SEVII67, WORLD_HOENN,    WORLD_SEVII45},
    [WORLD_SEVII45]  = {WORLD_SINNOH,   WORLD_SEVII67, WORLD_SEVII123, NO_TARGET},
    [WORLD_SEVII67]  = {WORLD_SEVII45,  NO_TARGET,     WORLD_SEVII123, NO_TARGET},
};

static u8 GetWorldTargetForRegionMap(enum RegionMapType type)
{
    u32 i;
    for (i = 0; i < WORLD_COUNT; i++)
    {
        if (sWorldTargetRegionMap[i] == type)
            return i;
    }
    return WORLD_HOENN;
}

static bool32 IsSeaLaneOpen(u32 lane)
{
    bool32 league = FlagGet(FLAG_SE_JOHTO_LEAGUE_CLEARED);
    switch (lane)
    {
    case LANE_SLATEPORT_OLIVINE:
        return CheckBagHasItem(ITEM_JOHTO_TICKET, 1);
    case LANE_OLIVINE_VERMILION:
        return league && CheckBagHasItem(ITEM_JOHTO_TICKET, 1);
    case LANE_VERMILION_CANALAVE:
        return league && CheckBagHasItem(ITEM_CANALAVE_TICKET, 1);
    case LANE_VERMILION_SEVII:
        return league && CheckBagHasItem(ITEM_RAINBOW_PASS, 1);
    case LANE_OLIVINE_CHANNEL:
        return IsSeaLaneOpen(LANE_SLATEPORT_OLIVINE) || IsSeaLaneOpen(LANE_OLIVINE_VERMILION);
    }
    return FALSE;
}

static bool32 IsSeviiWorldOwner(u32 owner)
{
    return owner == WORLD_SEVII123 || owner == WORLD_SEVII45 || owner == WORLD_SEVII67 || owner == WORLD_SEVII_ALL;
}

// The three Sevii groups light up together
static bool32 IsWorldOwnerLit(u32 owner, u32 sel)
{
    if (owner == WORLD_SEA || owner == sel)
        return TRUE;
    return IsSeviiWorldOwner(owner) && IsSeviiWorldOwner(sel);
}

static void LoadWorldMapPalettes(u32 sel)
{
    u16 pal[16];
    u32 i, j;
    bool8 laneOpen[LANE_COUNT];

    for (i = 0; i < LANE_COUNT; i++)
        laneOpen[i] = IsSeaLaneOpen(i);

    for (i = 0; i < WORLD_MAP_NUM_PALS; i++)
    {
        CpuCopy16(sWorldMap_Pal, pal, sizeof(pal));
        for (j = 0; j < 3; j++)
        {
            if (!laneOpen[sWorldMapPalettes[i].lanes[j]])
                pal[13 + j] = pal[1];
        }
        if (!IsWorldOwnerLit(sWorldMapPalettes[i].owner, sel))
        {
            // Dim the land colours of the regions that aren't selected
            for (j = 3; j <= 12; j++)
            {
                u32 r = GET_R(pal[j]), g = GET_G(pal[j]), b = GET_B(pal[j]);
                pal[j] = RGB((r * 7 + 2 * 9) / 16, (g * 7 + 4 * 9) / 16, (b * 7 + 8 * 9) / 16);
            }
        }
        LoadPalette(pal, BG_PLTT_ID(WORLD_MAP_FIRST_PAL + i), PLTT_SIZE_4BPP);
    }
}

// Gently pulse the selected region so it stands out, even the small Sevii groups
static void Task_WorldMapPulse(u8 taskId)
{
    struct Pokenav_RegionMapMenu *menu = GetSubstructPtr(POKENAV_SUBSTRUCT_REGION_MAP_STATE);
    s16 *data = gTasks[taskId].data;
    u32 i, coeff;

    if (gPaletteFade.active)
        return;
    data[0] = (data[0] + 1) & 63;
    coeff = data[0] < 32 ? data[0] / 6 : (63 - data[0]) / 6;
    for (i = 0; i < WORLD_MAP_NUM_PALS; i++)
    {
        // Only the group A opens pulses (and the Sevii name with it)
        u32 owner = sWorldMapPalettes[i].owner;
        if (owner == menu->worldSel || (owner == WORLD_SEVII_ALL && IsSeviiWorldOwner(menu->worldSel)))
            BlendPalette(BG_PLTT_ID(WORLD_MAP_FIRST_PAL + i) + 3, 10, coeff, RGB_WHITE);
    }
}

static void StopWorldMapPulse(void)
{
    u8 taskId = FindTaskIdByFunc(Task_WorldMapPulse);
    if (taskId != TASK_NONE)
        DestroyTask(taskId);
}

static void VBlankCB_WorldMap(void)
{
    TransferPlttBuffer();
    LoadOam();
    ProcessSpriteCopyRequests();
}

u32 PokenavCallback_Init_RegionMap(void)
{
    struct Pokenav_RegionMapMenu *state = AllocSubstruct(POKENAV_SUBSTRUCT_REGION_MAP_STATE, sizeof(struct Pokenav_RegionMapMenu));
    if (!state)
        return FALSE;

    if (!AllocSubstruct(POKENAV_SUBSTRUCT_REGION_MAP, sizeof(struct RegionMap)))
        return FALSE;

    // Super Emerald: the map opens on the world overview, on the player's region
    ClearRegionMapViewType();
    state->worldSel = GetWorldTargetForRegionMap(GetPlayerRegionMapType());
    state->inRegion = FALSE;
    state->zoomDisabled = TRUE;
    state->callback = HandleWorldMapInput;

    return TRUE;
}

void FreeRegionMapSubstruct1(void)
{
    ClearRegionMapViewType();
    FreePokenavSubstruct(POKENAV_SUBSTRUCT_REGION_MAP);
    FreePokenavSubstruct(POKENAV_SUBSTRUCT_REGION_MAP_STATE);
}

u32 GetRegionMapCallback(void)
{
    struct Pokenav_RegionMapMenu *state = GetSubstructPtr(POKENAV_SUBSTRUCT_REGION_MAP_STATE);
    return state->callback(state);
}

static u32 HandleRegionMapInput(struct Pokenav_RegionMapMenu *state)
{
    struct RegionMap* regionMap = GetSubstructPtr(POKENAV_SUBSTRUCT_REGION_MAP);

    switch (DoRegionMapInputCallback())
    {
    case MAP_INPUT_MOVE_END:
        return POKENAV_MAP_FUNC_CURSOR_MOVED;
    case MAP_INPUT_A_BUTTON:
        if (!IsRegionMapZoomed())
            return POKENAV_MAP_FUNC_ZOOM_IN;
        return POKENAV_MAP_FUNC_ZOOM_OUT;
    case MAP_INPUT_B_BUTTON:
        state->callback = HandleWorldMapInput;
        return POKENAV_MAP_FUNC_BACK_TO_WORLD;
    case MAP_INPUT_R_BUTTON:
        if (CanFlyFromPokenavMap(regionMap))
            return POKENAV_MAP_FUNC_FLY;
    }

    return POKENAV_MAP_FUNC_NONE;
}

static u32 HandleRegionMapInputZoomDisabled(struct Pokenav_RegionMapMenu *state)
{
    struct RegionMap *regionMap = GetSubstructPtr(POKENAV_SUBSTRUCT_REGION_MAP);

    // Kanto has a full region map but no city zoom artwork. Keep cursor
    // navigation and Poke Rider flight available without enabling zoom.
    if (IsRegionMapShowingKanto())
    {
        switch (DoRegionMapInputCallback())
        {
        case MAP_INPUT_MOVE_END:
            return POKENAV_MAP_FUNC_CURSOR_MOVED;
        case MAP_INPUT_B_BUTTON:
            state->callback = HandleWorldMapInput;
            return POKENAV_MAP_FUNC_BACK_TO_WORLD;
        case MAP_INPUT_R_BUTTON:
            if (CanFlyFromPokenavMap(regionMap))
                return POKENAV_MAP_FUNC_FLY;
            break;
        }
    }
    else if (JOY_NEW(B_BUTTON))
    {
        state->callback = HandleWorldMapInput;
        return POKENAV_MAP_FUNC_BACK_TO_WORLD;
    }

    return POKENAV_MAP_FUNC_NONE;
}

static u32 GetExitRegionMapMenuId(struct Pokenav_RegionMapMenu *state)
{
    return POKENAV_MAIN_MENU_CURSOR_ON_MAP;
}

// Flying from the PokeNav only works on the map of the region the player is in.
// Other regions are reached by ship.
static bool32 CanFlyFromPokenavMap(struct RegionMap *regionMap)
{
    return regionMap->mapSecType == MAPSECTYPE_CITY_CANFLY
        && !IsRegionMapShowingOtherRegion()
        && FlagGet(OW_FLAG_POKE_RIDER)
        && Overworld_MapTypeAllowsTeleportAndFly(gMapHeader.mapType) == TRUE;
}

static u32 HandleWorldMapInput(struct Pokenav_RegionMapMenu *state)
{
    u32 dir, next;

    if (JOY_NEW(A_BUTTON))
    {
        SetRegionMapViewType(sWorldTargetRegionMap[state->worldSel]);
        // Kanto and the Sevii Islands have no city zoom
        state->zoomDisabled = IsRegionMapShowingKanto()
                           || (!IsRegionMapShowingOtherRegion() && IsEventIslandMapSecId(gMapHeader.regionMapSectionId));
        if (!state->zoomDisabled)
            state->callback = HandleRegionMapInput;
        else
            state->callback = HandleRegionMapInputZoomDisabled;
        state->inRegion = TRUE;
        return POKENAV_MAP_FUNC_OPEN_REGION;
    }
    if (JOY_NEW(B_BUTTON))
    {
        state->callback = GetExitRegionMapMenuId;
        return POKENAV_MAP_FUNC_EXIT;
    }

    if (JOY_NEW(DPAD_UP))
        dir = 0;
    else if (JOY_NEW(DPAD_DOWN))
        dir = 1;
    else if (JOY_NEW(DPAD_LEFT))
        dir = 2;
    else if (JOY_NEW(DPAD_RIGHT))
        dir = 3;
    else
        return POKENAV_MAP_FUNC_NONE;

    next = sWorldTargetNeighbors[state->worldSel][dir];
    if (next == NO_TARGET)
        return POKENAV_MAP_FUNC_NONE;
    state->worldSel = next;
    return POKENAV_MAP_FUNC_WORLD_MOVED;
}

bool32 GetZoomDisabled(void)
{
    struct Pokenav_RegionMapMenu *state = GetSubstructPtr(POKENAV_SUBSTRUCT_REGION_MAP_STATE);
    return state->zoomDisabled;
}

bool32 OpenPokenavRegionMap(void)
{
    struct Pokenav_RegionMapGfx *state = AllocSubstruct(POKENAV_SUBSTRUCT_REGION_MAP_ZOOM, sizeof(struct Pokenav_RegionMapGfx));
    if (!state)
        return FALSE;

    state->regionGfxLoaded = FALSE;
    state->loopTaskId = CreateLoopedTask(LoopedTask_OpenWorldMap, 1);
    state->isTaskActiveCB = GetCurrentLoopedTaskActive;
    return TRUE;
}

void CreateRegionMapLoopedTask(s32 index)
{
    struct Pokenav_RegionMapGfx *state = GetSubstructPtr(POKENAV_SUBSTRUCT_REGION_MAP_ZOOM);
    state->loopTaskId = CreateLoopedTask(sRegionMapLoopTaskFuncs[index], 1);
    state->isTaskActiveCB = GetCurrentLoopedTaskActive;
}

bool32 IsRegionMapLoopedTaskActive(void)
{
    struct Pokenav_RegionMapGfx *state = GetSubstructPtr(POKENAV_SUBSTRUCT_REGION_MAP_ZOOM);
    return state->isTaskActiveCB();
}

void FreeRegionMapSubstruct2(void)
{
    struct Pokenav_RegionMapGfx *state = GetSubstructPtr(POKENAV_SUBSTRUCT_REGION_MAP_ZOOM);
    StopWorldMapPulse();
    if (state->regionGfxLoaded)
    {
        if (!GetZoomDisabled())
            gSaveBlock2Ptr->regionMapZoom = IsRegionMapZoomed();
        FreeRegionMapIconResources();
        FreeCityZoomViewGfx();
        RemoveWindow(state->infoWindowId);
    }
    FreePokenavSubstruct(POKENAV_SUBSTRUCT_REGION_MAP);
    FreePokenavSubstruct(POKENAV_SUBSTRUCT_REGION_MAP_ZOOM);
    SetPokenavVBlankCallback();
    SetBgMode(0);
}

static void VBlankCB_RegionMap(void)
{
    TransferPlttBuffer();
    LoadOam();
    ProcessSpriteCopyRequests();
    UpdateRegionMapVideoRegs();
}

static bool32 GetCurrentLoopedTaskActive(void)
{
    struct Pokenav_RegionMapGfx *state = GetSubstructPtr(POKENAV_SUBSTRUCT_REGION_MAP_ZOOM);
    return IsLoopedTaskActive(state->loopTaskId);
}

static bool8 ShouldOpenRegionMapZoomed(void)
{
    if (GetZoomDisabled())
        return FALSE;

    return gSaveBlock2Ptr->regionMapZoom == TRUE;
}

static u32 OpenRegionMapStep(s32 taskState, bool32 fromWorld)
{
    int menuGfxId;
    struct RegionMap *regionMap;
    struct Pokenav_RegionMapGfx *state = GetSubstructPtr(POKENAV_SUBSTRUCT_REGION_MAP_ZOOM);
    switch (taskState)
    {
    case 0:
        SetVBlankCallback_(NULL);
        HideBg(1);
        HideBg(2);
        HideBg(3);
        SetBgMode(1);
        InitBgTemplates(sRegionMapBgTemplates, ARRAY_COUNT(sRegionMapBgTemplates) - 1);
        regionMap = GetSubstructPtr(POKENAV_SUBSTRUCT_REGION_MAP);
        InitRegionMapData(regionMap, &sRegionMapBgTemplates[1], ShouldOpenRegionMapZoomed());
        LoadCityZoomViewGfx();
        return LT_INC_AND_PAUSE;
    case 1:
        if (LoadRegionMapGfx())
            return LT_PAUSE;

        if (!GetZoomDisabled() || IsRegionMapShowingKanto())
        {
            CreateRegionMapPlayerIcon(4, 9);
            CreateRegionMapCursor(5, 10);
            TrySetPlayerIconBlink();
        }
        else
        {
            // Dim the region map when zoom is disabled
            // (when the player is off the map)
            BlendRegionMap(RGB_BLACK, 6);
        }
        return LT_INC_AND_PAUSE;
    case 2:
        DecompressCityMaps();
        return LT_INC_AND_CONTINUE;
    case 3:
        if (IsDecompressCityMapsActive())
            return LT_PAUSE;

        LoadPokenavRegionMapGfx(state);
        state->regionGfxLoaded = TRUE;
        return LT_INC_AND_CONTINUE;
    case 4:
        if (TryFreeTempTileDataBuffers())
            return LT_PAUSE;

        UpdateMapSecInfoWindow(state);
        FadeToBlackExceptPrimary();
        return LT_INC_AND_PAUSE;
    case 5:
        if (IsDma3ManagerBusyWithBgCopy_(state))
            return LT_PAUSE;

        ShowBg(1);
        ShowBg(2);
        SetVBlankCallback_(VBlankCB_RegionMap);
        return LT_INC_AND_PAUSE;
    case 6:
        if (!ShouldOpenRegionMapZoomed())
            menuGfxId = POKENAV_GFX_MAP_MENU_ZOOMED_OUT;
        else
            menuGfxId = POKENAV_GFX_MAP_MENU_ZOOMED_IN;

        UpdateRegionMapHelpBarText();
        if (fromWorld)
        {
            UpdateRegionMapRightHeaderTiles(menuGfxId);
        }
        else
        {
            LoadLeftHeaderGfxForIndex(menuGfxId);
            ShowLeftHeaderGfx(menuGfxId, TRUE, TRUE);
        }
        PokenavFadeScreen(POKENAV_FADE_FROM_BLACK);
        return LT_INC_AND_PAUSE;
    case 7:
        if (IsPaletteFadeActive() || AreLeftHeaderSpritesMoving())
            return LT_PAUSE;
        return LT_INC_AND_CONTINUE;
    default:
        return LT_FINISH;
    }
}

static u32 OpenWorldMapStep(s32 taskState, bool32 initial)
{
    struct Pokenav_RegionMapMenu *menu = GetSubstructPtr(POKENAV_SUBSTRUCT_REGION_MAP_STATE);
    switch (taskState)
    {
    case 0:
        SetVBlankCallback_(NULL);
        HideBg(1);
        HideBg(2);
        HideBg(3);
        SetBgMode(0);
        InitBgFromTemplate(&sRegionMapBgTemplates[1]);
        ChangeBgX(2, 0, BG_COORD_SET);
        ChangeBgY(2, 0, BG_COORD_SET);
        DecompressAndCopyTileDataToVram(2, sWorldMap_Gfx, 0, 0, 0);
        return LT_INC_AND_PAUSE;
    case 1:
        if (FreeTempTileDataBuffersIfPossible())
            return LT_PAUSE;
        DecompressAndCopyTileDataToVram(2, sWorldMap_Tilemap, 0, 0, 1);
        return LT_INC_AND_PAUSE;
    case 2:
        if (FreeTempTileDataBuffersIfPossible())
            return LT_PAUSE;
        LoadWorldMapPalettes(menu->worldSel);
        FadeToBlackExceptPrimary();
        return LT_INC_AND_PAUSE;
    case 3:
        if (IsDma3ManagerBusyWithBgCopy())
            return LT_PAUSE;
        ShowBg(2);
        SetVBlankCallback_(VBlankCB_WorldMap);
        PrintHelpBarText(HELPBAR_MAP_WORLD);
        if (initial)
        {
            LoadLeftHeaderGfxForIndex(POKENAV_GFX_MAP_MENU_ZOOMED_OUT);
            ShowLeftHeaderGfx(POKENAV_GFX_MAP_MENU_ZOOMED_OUT, TRUE, TRUE);
        }
        else
        {
            UpdateRegionMapRightHeaderTiles(POKENAV_GFX_MAP_MENU_ZOOMED_OUT);
        }
        PokenavFadeScreen(POKENAV_FADE_FROM_BLACK);
        return LT_INC_AND_PAUSE;
    case 4:
        if (IsPaletteFadeActive() || AreLeftHeaderSpritesMoving())
            return LT_PAUSE;
        if (FindTaskIdByFunc(Task_WorldMapPulse) == TASK_NONE)
            CreateTask(Task_WorldMapPulse, 2);
        return LT_INC_AND_CONTINUE;
    default:
        return LT_FINISH;
    }
}

static u32 LoopedTask_OpenWorldMap(s32 taskState)
{
    return OpenWorldMapStep(taskState, TRUE);
}

static u32 LoopedTask_WorldMapMoved(s32 taskState)
{
    struct Pokenav_RegionMapMenu *menu = GetSubstructPtr(POKENAV_SUBSTRUCT_REGION_MAP_STATE);
    PlaySE(SE_DEX_SCROLL);
    LoadWorldMapPalettes(menu->worldSel);
    return LT_FINISH;
}

static u32 LoopedTask_OpenRegionFromWorld(s32 taskState)
{
    switch (taskState)
    {
    case 0:
        StopWorldMapPulse();
        PlaySE(SE_SELECT);
        PokenavFadeScreen(POKENAV_FADE_TO_BLACK);
        return LT_INC_AND_PAUSE;
    case 1:
        if (IsPaletteFadeActive())
            return LT_PAUSE;
        return LT_INC_AND_CONTINUE;
    }
    return OpenRegionMapStep(taskState - 2, TRUE);
}

static u32 LoopedTask_BackToWorldMap(s32 taskState)
{
    struct Pokenav_RegionMapGfx *state = GetSubstructPtr(POKENAV_SUBSTRUCT_REGION_MAP_ZOOM);
    struct Pokenav_RegionMapMenu *menu = GetSubstructPtr(POKENAV_SUBSTRUCT_REGION_MAP_STATE);
    switch (taskState)
    {
    case 0:
        PlaySE(SE_SELECT);
        PokenavFadeScreen(POKENAV_FADE_TO_BLACK);
        return LT_INC_AND_PAUSE;
    case 1:
        if (IsPaletteFadeActive())
            return LT_PAUSE;
        if (!menu->zoomDisabled)
            gSaveBlock2Ptr->regionMapZoom = IsRegionMapZoomed();
        SetVBlankCallback_(NULL);
        FreeRegionMapIconResources();
        FreeCityZoomViewGfx();
        RemoveWindow(state->infoWindowId);
        state->regionGfxLoaded = FALSE;
        ClearRegionMapViewType();
        menu->inRegion = FALSE;
        menu->zoomDisabled = TRUE;
        return LT_INC_AND_CONTINUE;
    }
    return OpenWorldMapStep(taskState - 2, FALSE);
}

static u32 LoopedTask_UpdateInfoAfterCursorMove(s32 taskState)
{
    struct Pokenav_RegionMapGfx *state = GetSubstructPtr(POKENAV_SUBSTRUCT_REGION_MAP_ZOOM);
    switch (taskState)
    {
    case 0:
        UpdateMapSecInfoWindow(state);
        UpdateRegionMapHelpBarText();
        return LT_INC_AND_PAUSE;
    case 1:
        if (IsDma3ManagerBusyWithBgCopy_(state))
            return LT_PAUSE;
        break;
    }

    return LT_FINISH;
}

static u32 LoopedTask_RegionMapZoomOut(s32 taskState)
{
    switch (taskState)
    {
    case 0:
        PlaySE(SE_SELECT);
        ChangeBgYForZoom(FALSE);
        SetRegionMapDataForZoom();
        return LT_INC_AND_PAUSE;
    case 1:
        if (UpdateRegionMapZoom() || IsChangeBgYForZoomActive())
            return LT_PAUSE;

        UpdateRegionMapHelpBarText();
        return LT_INC_AND_PAUSE;
    case 2:
        if (WaitForHelpBar())
            return LT_PAUSE;

        UpdateRegionMapRightHeaderTiles(POKENAV_GFX_MAP_MENU_ZOOMED_OUT);
        break;
    }

    return LT_FINISH;
}

static u32 LoopedTask_RegionMapZoomIn(s32 taskState)
{
    struct Pokenav_RegionMapGfx *state = GetSubstructPtr(POKENAV_SUBSTRUCT_REGION_MAP_ZOOM);
    switch (taskState)
    {
    case 0:
        PlaySE(SE_SELECT);
        UpdateMapSecInfoWindow(state);
        return LT_INC_AND_PAUSE;
    case 1:
        if (IsDma3ManagerBusyWithBgCopy_(state))
            return LT_PAUSE;

        ChangeBgYForZoom(TRUE);
        SetRegionMapDataForZoom();
        return LT_INC_AND_PAUSE;
    case 2:
        if (UpdateRegionMapZoom() || IsChangeBgYForZoomActive())
            return LT_PAUSE;

        UpdateRegionMapHelpBarText();
        return LT_INC_AND_PAUSE;
    case 3:
        if (WaitForHelpBar())
            return LT_PAUSE;

        UpdateRegionMapRightHeaderTiles(POKENAV_GFX_MAP_MENU_ZOOMED_IN);
        break;
    }

    return LT_FINISH;
}

static u32 LoopedTask_ExitRegionMap(s32 taskState)
{
    switch (taskState)
    {
    case 0:
        StopWorldMapPulse();
        PlaySE(SE_SELECT);
        PokenavFadeScreen(POKENAV_FADE_TO_BLACK);
        return LT_INC_AND_PAUSE;
    case 1:
        if (IsPaletteFadeActive())
            return LT_PAUSE;

        SetLeftHeaderSpritesInvisibility();
        SlideMenuHeaderDown();
        return LT_INC_AND_PAUSE;
    case 2:
        if (MainMenuLoopedTaskIsBusy())
            return LT_PAUSE;

        HideBg(1);
        HideBg(2);
        HideBg(3);
        return LT_INC_AND_PAUSE;
    }

    return LT_FINISH;
}

static u32 LoopedTask_TreatAsPokeNavFlyMap(s32 taskState)
{
    switch (taskState)
    {
    case 0:
        PlaySE(SE_SELECT);
        struct RegionMap* regionMap = GetSubstructPtr(POKENAV_SUBSTRUCT_REGION_MAP);
        SetFlyDestination(regionMap);
        gSkipShowMonAnim = TRUE;
        ReturnToFieldFromFlyMapSelect();

        return LT_FINISH;
    }

    return LT_FINISH;
}

static void LoadCityZoomViewGfx(void)
{
    int i;
    for (i = 0; i < ARRAY_COUNT(sCityZoomTextSpriteSheet); i++)
        LoadCompressedSpriteSheet(&sCityZoomTextSpriteSheet[i]);

    Pokenav_AllocAndLoadPalettes(sCityZoomTilesSpritePalette);
    CreateCityZoomTextSprites();
}

static void FreeCityZoomViewGfx(void)
{
    int i;
    struct Pokenav_RegionMapGfx *state = GetSubstructPtr(POKENAV_SUBSTRUCT_REGION_MAP_ZOOM);
    FreeSpriteTilesByTag(GFXTAG_CITY_ZOOM);
    FreeSpritePaletteByTag(PALTAG_CITY_ZOOM);
    for (i = 0; i < (int)ARRAY_COUNT(state->cityZoomTextSprites); i++)
        DestroySprite(state->cityZoomTextSprites[i]);
}

static void LoadPokenavRegionMapGfx(struct Pokenav_RegionMapGfx *state)
{
    BgDmaFill(1, PIXEL_FILL(0), 0x40, 1);
    BgDmaFill(1, PIXEL_FILL(1), 0x41, 1);
    CpuFill16(0x1040, state->tilemapBuffer, 0x800);
    SetBgTilemapBuffer(1, state->tilemapBuffer);
    state->infoWindowId = AddWindow(&sMapSecInfoWindowTemplate);
    LoadUserWindowBorderGfx_(state->infoWindowId, 0x42, BG_PLTT_ID(4));
    DrawTextBorderOuter(state->infoWindowId, 0x42, 4);
    DecompressAndCopyTileDataToVram(1, sRegionMapCityZoomTiles_Gfx, 0, 0, 0);
    FillWindowPixelBuffer(state->infoWindowId, PIXEL_FILL(1));
    PutWindowTilemap(state->infoWindowId);
    CopyWindowToVram(state->infoWindowId, COPYWIN_FULL);
    CopyPaletteIntoBufferUnfaded(sMapSecInfoWindow_Pal, BG_PLTT_ID(1), sizeof(sMapSecInfoWindow_Pal));
    CopyPaletteIntoBufferUnfaded(gRegionMapCityZoomTiles_Pal, BG_PLTT_ID(3), PLTT_SIZE_4BPP);
    if (!IsRegionMapZoomed())
        ChangeBgY(1, -0x6000, BG_COORD_SET);
    else
        ChangeBgY(1, 0, BG_COORD_SET);

    ChangeBgX(1, 0, BG_COORD_SET);
}

static bool32 TryFreeTempTileDataBuffers(void)
{
    return FreeTempTileDataBuffersIfPossible();
}

static void UpdateMapSecInfoWindow(struct Pokenav_RegionMapGfx *state)
{
    struct RegionMap *regionMap = GetSubstructPtr(POKENAV_SUBSTRUCT_REGION_MAP);
    switch (regionMap->mapSecType)
    {
    case MAPSECTYPE_CITY_CANFLY:
        FillWindowPixelBuffer(state->infoWindowId, PIXEL_FILL(1));
        PutWindowRectTilemap(state->infoWindowId, 0, 0, 12, 2);
        AddTextPrinterParameterized(state->infoWindowId, FONT_NARROW, regionMap->mapSecName, 0, 1, TEXT_SKIP_DRAW, NULL);
        DrawCityMap(state, regionMap->mapSecId, regionMap->posWithinMapSec);
        CopyWindowToVram(state->infoWindowId, COPYWIN_FULL);
        SetCityZoomTextInvisibility(FALSE);
        break;
    case MAPSECTYPE_CITY_CANTFLY:
        FillWindowPixelBuffer(state->infoWindowId, PIXEL_FILL(1));
        PutWindowRectTilemap(state->infoWindowId, 0, 0, 12, 2);
        AddTextPrinterParameterized(state->infoWindowId, FONT_NARROW, regionMap->mapSecName, 0, 1, TEXT_SKIP_DRAW, NULL);
        FillBgTilemapBufferRect(1, 0x1041, 17, 6, 12, 11, 17);
        CopyWindowToVram(state->infoWindowId, COPYWIN_FULL);
        SetCityZoomTextInvisibility(TRUE);
        break;
    case MAPSECTYPE_ROUTE:
    case MAPSECTYPE_BATTLE_FRONTIER:
        FillWindowPixelBuffer(state->infoWindowId, PIXEL_FILL(1));
        PutWindowTilemap(state->infoWindowId);
        AddTextPrinterParameterized(state->infoWindowId, FONT_NARROW, regionMap->mapSecName, 0, 1, TEXT_SKIP_DRAW, NULL);
        PrintLandmarkNames(state, regionMap->mapSecId, regionMap->posWithinMapSec);
        CopyWindowToVram(state->infoWindowId, COPYWIN_FULL);
        SetCityZoomTextInvisibility(TRUE);
        break;
    case MAPSECTYPE_NONE:
        FillBgTilemapBufferRect(1, 0x1041, 17, 4, 12, 13, 17);
        CopyBgTilemapBufferToVram(1);
        SetCityZoomTextInvisibility(TRUE);
        break;
    }
}

static bool32 IsDma3ManagerBusyWithBgCopy_(struct Pokenav_RegionMapGfx *state)
{
    return IsDma3ManagerBusyWithBgCopy();
}

#define tZoomIn data[0]

static void ChangeBgYForZoom(bool32 zoomIn)
{
    u8 taskId = CreateTask(Task_ChangeBgYForZoom, 3);
    gTasks[taskId].tZoomIn = zoomIn;
}

static bool32 IsChangeBgYForZoomActive(void)
{
    return FuncIsActiveTask(Task_ChangeBgYForZoom);
}

static void Task_ChangeBgYForZoom(u8 taskId)
{
    if (gTasks[taskId].tZoomIn)
    {
        if (ChangeBgY(1, 0x480, BG_COORD_ADD) >= 0)
        {
            ChangeBgY(1, 0, BG_COORD_SET);
            DestroyTask(taskId);
        }

        UpdateCityZoomTextPosition();
    }
    else
    {
        if (ChangeBgY(1, 0x480, BG_COORD_SUB) <= -0x6000)
        {
            ChangeBgY(1, -0x6000, BG_COORD_SET);
            DestroyTask(taskId);
        }

        UpdateCityZoomTextPosition();
    }
}

#undef tZoomIn

static void DecompressCityMaps(void)
{
    CreateLoopedTask(LoopedTask_DecompressCityMaps, 1);
}

static bool32 IsDecompressCityMapsActive(void)
{
    return FuncIsActiveLoopedTask(LoopedTask_DecompressCityMaps);
}

static u32 LoopedTask_DecompressCityMaps(s32 taskState)
{
    struct Pokenav_RegionMapGfx *state = GetSubstructPtr(POKENAV_SUBSTRUCT_REGION_MAP_ZOOM);
    if (taskState < NUM_CITY_MAPS)
    {
        DecompressDataWithHeaderWram(sPokenavCityMaps[taskState].tilemap, state->cityZoomPics[taskState]);
        return LT_INC_AND_CONTINUE;
    }

    return LT_FINISH;
}

static void DrawCityMap(struct Pokenav_RegionMapGfx *state, mapsec_s32_t mapSecId, int pos)
{
    int i;
    for (i = 0; i < NUM_CITY_MAPS && (sPokenavCityMaps[i].mapSecId != mapSecId || sPokenavCityMaps[i].index != pos); i++)
        ;

    if (i == NUM_CITY_MAPS)
        return;

    FillBgTilemapBufferRect_Palette0(1, 0x1041, 17, 6, 12, 11);
    CopyToBgTilemapBufferRect(1, state->cityZoomPics[i], 18, 6, 10, 10);
}

static void PrintLandmarkNames(struct Pokenav_RegionMapGfx *state, mapsec_s32_t mapSecId, int pos)
{
    int i = 0;
    while (1)
    {
        const u8 *landmarkName = GetLandmarkName(mapSecId, pos, i);
        if (!landmarkName)
            break;

        StringCopyPadded(gStringVar1, landmarkName, CHAR_SPACE, 12);
        AddTextPrinterParameterized(state->infoWindowId, FONT_NARROW, gStringVar1, 0, i * 16 + 17, TEXT_SKIP_DRAW, NULL);
        i++;
    }
}

static void CreateCityZoomTextSprites(void)
{
    int i;
    int y;
    struct Sprite *sprite;
    struct Pokenav_RegionMapGfx *state = GetSubstructPtr(POKENAV_SUBSTRUCT_REGION_MAP_ZOOM);

    // When not zoomed in the text is still created but its pushed off screen
    if (!IsRegionMapZoomed())
        y = 228;
    else
        y = 132;

    for (i = 0; i < (int)ARRAY_COUNT(state->cityZoomTextSprites); i++)
    {
        u8 spriteId = CreateSprite(&sCityZoomTextSpriteTemplate, 152 + i * 32, y, 8);
        sprite = &gSprites[spriteId];
        sprite->data[0] = 0;
        sprite->data[1] = i * 4;
        sprite->data[2] = sprite->oam.tileNum;
        sprite->data[3] = 150;
        sprite->data[4] = i * 4;
        sprite->oam.tileNum += i * 4;
        state->cityZoomTextSprites[i] = sprite;
    }
}

// Slide and cycle through the text key showing what the features on the zoomed city map are
static void SpriteCB_CityZoomText(struct Sprite *sprite)
{
    if (sprite->data[3])
    {
        sprite->data[3]--;
        return;
    }

    if (++sprite->data[0] > 11)
        sprite->data[0] = 0;

    if (++sprite->data[1] > 60)
        sprite->data[1] = 0;

    sprite->oam.tileNum = sprite->data[2] + sprite->data[1];
    if (sprite->data[5] < 4)
    {
        if (sprite->data[0] == 0)
        {
            sprite->data[5]++;
            sprite->data[3] = 120;
        }
    }
    else
    {
        if (sprite->data[1] == sprite->data[4])
        {
            sprite->data[5] = 0;
            sprite->data[0] = 0;
            sprite->data[3] = 120;
        }
    }
}

static void UpdateCityZoomTextPosition(void)
{
    int i;
    struct Pokenav_RegionMapGfx *state = GetSubstructPtr(POKENAV_SUBSTRUCT_REGION_MAP_ZOOM);
    int y = 132 - (GetBgY(1) >> 8);
    for (i = 0; i < (int)ARRAY_COUNT(state->cityZoomTextSprites); i++)
        state->cityZoomTextSprites[i]->y = y;
}

static void SetCityZoomTextInvisibility(bool32 invisible)
{
    int i;
    struct Pokenav_RegionMapGfx *state = GetSubstructPtr(POKENAV_SUBSTRUCT_REGION_MAP_ZOOM);
    for (i = 0; i < (int)ARRAY_COUNT(state->cityZoomTextSprites); i++)
        state->cityZoomTextSprites[i]->invisible = invisible;
}

void UpdateRegionMapHelpBarText(void)
{
    struct RegionMap* regionMap = GetSubstructPtr(POKENAV_SUBSTRUCT_REGION_MAP);

    if (IsRegionMapShowingKanto()) // Super Fire Red: no zoom on the Kanto map
    {
        if (CanFlyFromPokenavMap(regionMap))
            PrintHelpBarText(HELPBAR_MAP_NO_ZOOM_CANFLY);
        else
            PrintHelpBarText(HELPBAR_MAP_NO_ZOOM);
    }
    else if (CanFlyFromPokenavMap(regionMap))
    {
        if (IsRegionMapZoomed())
            PrintHelpBarText(HELPBAR_MAP_ZOOMED_IN_CANFLY);
        else
            PrintHelpBarText(HELPBAR_MAP_ZOOMED_OUT_CANFLY);
    }
    else
    {
        if (IsRegionMapZoomed())
            PrintHelpBarText(HELPBAR_MAP_ZOOMED_IN);
        else
            PrintHelpBarText(HELPBAR_MAP_ZOOMED_OUT);
    }
}
