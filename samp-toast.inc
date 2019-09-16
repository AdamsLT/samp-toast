/*
 
2d sprites as objects
 
*/
 
#include <YSI\y_hooks>
 
#define SPRITE_HANDICAP "é"
 
#define SPRITE_CREATION_TIME 1
 
new spriteareaid, spriteid, backid, spritetimer, spritesymbol[10];
 
 
forward Create2DObjectSprite(symbol[], Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz);
public Create2DObjectSprite(symbol[], Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz)
{
    spriteareaid = CreateDynamicSphere(x, y, z, 3);
    spriteid = CreateDynamicObject(19475, x, y, z, rx, ry, rz, -1, -1, -1, 10);
    backid = CreateDynamicObject(19475, x, y, z, rx, ry, rz, -1, -1, -1, 10);
 
    memcpy(spritesymbol, symbol, 0, strlen(symbol)*4, sizeof(spritesymbol));
 
    return spriteareaid;
}
 
 
forward UpdateSpriteTimer(updatespriteid, updatebackid);
public UpdateSpriteTimer(updatespriteid, updatebackid)
{
    new Float:x, Float:y, Float:z;
    foreach(new playerid : Player)
    {
        GetPlayerCameraPos(playerid, x, y, z);
        SetObjectFaceCoords3D(updatespriteid, x, y, z, 0.0, -90.0, -90.0);
        SetObjectFaceCoords3D(updatebackid, x, y, z, 0.0, -90.0, -90.0);
    }
}
 
static _Create2DSprite()
{
    SetTimerEx("SpriteDrawer", SPRITE_CREATION_TIME, false, "iiibb", backid, 0, 0xDD545454, true, true);
    SetTimerEx("SpriteDrawer", SPRITE_CREATION_TIME+10, false, "iiibb", spriteid, 0, 0xFFFFFFFF, true, false);
 
    spritetimer = SetTimerEx("UpdateSpriteTimer", 10, true, "ii", spriteid, backid);
}
 
static _Delete2DSprite()
{
    SetTimerEx("SpriteDrawer", SPRITE_CREATION_TIME, false, "iiibb", backid, 160, 0xDD545454, false, true);
    SetTimerEx("SpriteDrawer", SPRITE_CREATION_TIME+10, false, "iiibb", spriteid, 150, 0xFFFFFFFF, false, false);
 
    KillTimer(spritetimer);
}
 
forward SpriteDrawer(passedspriteid, size, colour, bool:creation, bool:isBackground);
public SpriteDrawer(passedspriteid, size, colour, bool:creation, bool:isBackground)
{
    if(isBackground)
        SetDynamicObjectMaterialText(passedspriteid, 0, "n", 100, "Webdings", size, 1, colour, 0, 1);
    else
        SetDynamicObjectMaterialText(passedspriteid, 0, spritesymbol, 100, "Webdings", size, 1, colour, 0, 1);
 
    if(creation && size + 1 != 160)
        SetTimerEx("SpriteDrawer", SPRITE_CREATION_TIME, false, "iiibb", passedspriteid, size+1, colour, creation, isBackground);
    else if(!creation && size - 1 != 0)
        SetTimerEx("SpriteDrawer", SPRITE_CREATION_TIME, false, "iiibb", passedspriteid, size-1, colour, creation, isBackground);
}
 
hook OnPlayerEnterDynamicArea(playerid, STREAMER_TAG_AREA areaid)
{
    if (spriteareaid == areaid)
    {
        _Create2DSprite();
    }
}
 
hook OnPlayerLeaveDynamicArea(playerid, STREAMER_TAG_AREA areaid)
{
    if (spriteareaid)
    {
        _Delete2DSprite();
    }
}
 
 
// HELPERS
 
// https://forum.sa-mp.com/showthread.php?p=1498305&highlight=SetObjectFaceCoords3D#post1498305
// Thank you, RyDeR`
// Thank you, RyDeR`
// Thank you, RyDeR`
// Thank you, RyDeR`
stock SetObjectFaceCoords3D(iObject, Float: fX, Float: fY, Float: fZ, Float: fRollOffset = 0.0, Float: fPitchOffset = 0.0, Float: fYawOffset = 0.0) {
    new
        Float: fOX,
        Float: fOY,
        Float: fOZ,
        Float: fPitch
    ;
    GetDynamicObjectPos(iObject, fOX, fOY, fOZ);
   
    fPitch = floatsqroot(floatpower(fX - fOX, 2.0) + floatpower(fY - fOY, 2.0));
    fPitch = floatabs(atan2(fPitch, fZ - fOZ));
   
    fZ = atan2(fY - fOY, fX - fOX) + 90.0; // Yaw
    SetDynamicObjectRot(iObject, fRollOffset, fPitch + fPitchOffset, fZ + fYawOffset);
}
 
 
// TESTING
 
hook OnGameModeInit()
{
    CreateDynamicObject(1369, 1210.3013, -1297.2666, 12.9643, 0.0000, 0.0000, -23.2800);
    Create2DObjectSprite(SPRITE_HANDICAP,1210.2371, -1297.4523, 13.7008, 0.0, 0.0, 0.0);
}