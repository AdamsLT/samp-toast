#if defined _inc_toast
    #undef _inc_toast
#endif

#if defined _toast_included
    #endinput
#endif
#define _toast_included

#if !defined MAX_SPRITES
	#define MAX_SPRITES 100,
#endif


/*

Textured Objects As SpriTes - TOAST
Author: JonasP
Credits: 
	* RyDeR` (https://forum.sa-mp.com/showthread.php?p=1498305&highlight=SetObjectFaceCoords3D#post1498305)

*/

#include <a_samp>
#include <streamer>

#include <YSI\y_hooks>

static const 
	MAX_SPRITES					= 100,
	INVALID_OBJECT_SPRITE_ID 	= -1,
	TRACK_NONE 					= 0,
	TRACK_PLAYER 				= 1,
	SPRITE_ANIM_NONE 			= 0,
	SPRITE_ANIM_POPUP 			= 1;

enum E_SPRITE_DATA
{
	e_Area_ID,
	Float:e_X,
	Float:e_Y,
	Float:e_Z,
	Float:e_RX,
	Float:e_RY,
	Float:e_RZ,
	Float:e_Radius
	e_Tracking_Type,
	e_Animation_Type,
	e_Color,
	e_Symbol[]
}

static
	Iterator:Sprite_Index<MAX_SPRITES>;
	Sprite_Data[MAX_SPRITES][E_SPRITE_DATA];






forward Create2DObjectSprite(const Symbol[], Float:X, Float:Y, Float:Z, Float:RX, Float:RY, Float: RZ, SpriteColor = 0, AnimationType = 1, TrackingType = 1);
forward Delete2DObjectSprite(spriteid);

forward Set2DObjectSpritePos(spriteid, Float:X, Float:Y, Float:Z);
forward Set2DObjectSpriteRot(spriteid, Float:RX, Float:RY, Float: RZ);

forward Set2DOBjectSpriteAnim(spriteid, AnimationType);
forward Set2DObjectSpriteTracking(spriteid, TrackingType);
forward Set2DObjectSpriteColor(spriteid, colour);

forward Rotate2DObjectSprite(spriteid);
forward Animate2DObjectSprite(spriteid);





public Create2DObjectSprite(const Symbol[], Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz, Float:radius, 
	spritecolor = 0, animationtype = 1, trackingtype = 1, worldid = -1, interiorid = -1)
{
	new 
		spriteareaid = INVALID_OBJECT_SPRITE_ID,
		index = Iter_Free(Sprite_Index);


	spriteareaid = CreateDynamicSphere(x, y, z, radius, worldid, interiorid);

	Sprite_Data[index][e_Area_ID] = spriteareaid;
	Sprite_Data[index][e_X] = x;
	Sprite_Data[index][e_Y] = y;
	Sprite_Data[index][e_Z] = z;
	Sprite_Data[index][e_RX] = rz;
	Sprite_Data[index][e_RY] = ry;
	Sprite_Data[index][e_RZ] = rz;
	Sprite_Data[index][e_Radius] = radius;
	Sprite_Data[index][e_Tracking_Type] = trackingtype;
	Sprite_Data[index][e_Animation_Type] = animationtype;
	Sprite_Data[index][e_Colour] = spritecolor;
	Sprite_Data[index][e_Symbol] = Symbol;

	spriteareaid = CreatePlayerObject(playerid, modelid, Float:X, Float:Y, Float:Z, Float:rX, Float:rY, Float:rZ, Float:DrawDistance = 0.0)

	return spriteareaid;
}






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
