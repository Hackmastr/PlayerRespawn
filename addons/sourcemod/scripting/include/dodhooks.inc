#if defined _dodhooks_included
#endinput
#endif
#define _dodhooks_included

#define MAX_CONTROL_POINTS 8

enum
{
	Team_Unassigned = 0,
	Team_Spectator,
	Team_Allies,
	Team_Axis
}

enum
{
	PlayerClass_Random = -2,
	PlayerClass_None,
	PlayerClass_Rifleman,
	PlayerClass_Assault,
	PlayerClass_Support,
	PlayerClass_Sniper,
	PlayerClass_Machinegunner,
	PlayerClass_Rocket,
	
	PlayerClass_Size
}

enum
{
	DoDRoundState_RoundInit = 0,
	DoDRoundState_PreGame,
	DoDRoundState_StartGame,
	DoDRoundState_PreRound,
	DoDRoundState_RoundRunning,
	DoDRoundState_AlliesWin,
	DoDRoundState_AxisWin,
	DoDRoundState_Restart,
	DoDRoundState_GameOver,
	
	DoDRoundState_Size
}

enum
{
	PlayerState_Active = 0,
	PlayerState_Welcome = 1,
	PlayerState_PickingTeam = 2,
	PlayerState_PickingClass = 3,
	PlayerState_DeathAnim = 4,
	PlayerState_ObserverMode = 6,
	
	PlayerState_Size
}

enum
{
	BombTargetState_Inactive = 0,
	BombTargetState_Active,
	BombTargetState_Armed,
	
	BombTargetState_Size
}

enum
{
	Voice_Attack = 0,
	Voice_Hold,
	Voice_Left,
	Voice_Right,
	Voice_StickTogether,
	Voice_Cover,
	Voice_UseSmoke,
	Voice_UseGrens,
	Voice_CeaseFire,
	Voice_YesSir,
	Voice_Negative,
	Voice_Backup,
	Voice_FireInHole,
	Voice_Grenade,
	Voice_Sniper,
	Voice_NiceShot,
	Voice_Thanks,
	Voice_AreaClear,
	Voice_DropWeapons,
	Voice_Displace,
	Voice_MgAhead,
	Voice_EnemyBehind,
	Voice_WeGotHim,
	Voice_MoveUpMg,
	Voice_NeedAmmo,
	Voice_UseBazooka,
	Voice_BazookaSpotted,
	Voice_GoGoGo,
	Voice_Medic,
	Voice_CoverFlanks,
	Voice_Tank,
	Voice_TakeAmmo,
	Voice_MoveWithtank,
	Voice_WTF,
	Voice_FireLeft,
	Voice_FireRight,
	Voice_EnemyAhead = 37,
	Voice_FallBack
}

/**
* @brief Checks if a player class is valid
*
* @param playerClass			The player class.
* @return						True if the player class is valid, false otherwise.
*/
stock bool:IsPlayerClassValid(playerClass)
{
	return playerClass != PlayerClass_None;
}

/**
* @brief Sets a players class
*
* @param client					Client index.
* @param playerClass			The player class.
* @noreturn
*/
native SetPlayerClass(client, playerClass);

/**
* @brief Returns a players class
*
* @param client					Client index.
* @return						The players class.
*/
native GetPlayerClass(client);

/**
* @brief Sets a players desired class
*
* @param client					Client index.
* @param desiredPlayerClass		The desired player class.
* @noreturn
*/
native SetDesiredPlayerClass(client, desiredPlayerClass);

/**
* @brief Returns a players desired class
*
* @param client					Client index.
* @return						The desired players class.
*/
native GetDesiredPlayerClass(client);

/**
* @brief Drops the players helmet.
*
* @param client					Client index.
* @param velocity				Velocity of the helmet
* @param origin					Origin of the helmet.
* @noreturn
*/
native PopHelmet(client, const Float:velocity[3], const Float:origin[3]);

/**
* @brief Sets the player state on a specific client.
*
* @param client					Client index.
* @param playerState			Player state.
* @noreturn
*/
native SetPlayerState(client, playerState);

/**
* @brief Precaches a control point icon. Example: sprites/obj_icons/icon_obj_allies.vmt
*
* @param materialName			Name of the material to precache.
* @return						Returns the material index, 0 for error.
*/
native PrecacheCPIcon(const String:materialName[]);

/**
* @brief Sets the different icons on the control point specified.
*
* @param cpIndex				Control point index.
* @param iconAllies				Allies captured/owning icon.
* @param iconAxis				Axis captured/owning icon.
* @param iconNeutral			Neutral icon.
* @param timerCapIcon			Background icon shown while being captured/planted.
* @param bombedIcon				Bombed Icon.
* @noreturn
*/
native SetCPIcons(cpIndex, iconAllies = 0, iconAxis = 0, iconNeutral = 0, timerCapIcon = 0, bombedIcon = 0);

/**
* @brief Sets the amount of control points to show on HUD.
*
* @param amount					Number of control points.
* @noreturn
*/
native SetNumControlPoints(amount);

/**
* @brief Shows or hides a control point on HUD.
*
* @param cpIndex				Control point index.
* @param visible				True to show the control point on HUD, false otherwise.
* @noreturn
*/
native SetCPVisible(cpIndex, bool:visible);

/**
* @brief Pauses the round timer specified.
*
* @param roundTimer				Entity index.
* @noreturn
*/
native PauseTimer(roundTimer);

/**
* @brief Resumes the round timer specified.
*
* @param roundTimer				Entity index.
* @noreturn
*/
native ResumeTimer(roundTimer);

/**
* @brief Sets time remaining on the round timer specified.
*
* @param roundTimer				Entity index.
* @param time					Time in seconds.
* @noreturn
*/
native SetTimeRemaining(roundTimer, time);

/**
* @brief Returns time remaining on the round timer specified.
*
* @param roundTimer				Entity index.
* @return						Time remaining in seconds.
*/
native Float:GetTimeRemaining(roundTimer);

/**
* @brief Respawns a player.
*
* @param client					Client index.
* @param classCheck				Auto check if the players class is valid. (Prevents server crashes in some cases)
* @noreturn
*/
native RespawnPlayer(client, bool:classCheck = true);

/**
* @brief Makes the specified team to win the round.
*
* @param index					Team index.
* @noreturn
*/
native SetWinningTeam(index);

/**
* @brief Adds wave time to the team specified.
*
* @param index					Team index.
* @param delay					Wave time delay.
* @noreturn
*/
native AddWaveTime(index, Float:delay);

/**
* @brief Sets the current round state.
*
* @param roundState				Round state.
* @noreturn
*/
native SetRoundState(roundState);

/**
* @brief Sets the bomb target state on a bomb target.
*
* @param bombTarget				Entity index.
* @param bombTargetState		Bomb target state.
* @noreturn
*/
native SetBombTargetState(bombtarget, bombTargetState);

/**
* @brief Called when a player has executed a voice command.
*
* @param client					Client index.
* @param voiceCommand			The voice command.
* @return						Plugin_Handled to block, Plugin_Continue otherwise.
*/
forward Action:OnVoiceCommand(client, &voiceCommand);

/**
* @brief Called when a player has executed a join class command.
*
* @param client					Client index.
* @param playerClass			The player class.
* @return						Plugin_Handled to block, Plugin_Continue otherwise.
*/
forward Action:OnJoinClass(client, &playerClass);

/**
* @brief Called when a players helmet is about to drop.
*
* @param client					Client index.
* @param velocity				Velocity of the helmet.
* @param origin					Origin of the helmet
* @return						Plugin_Handled to block, Plugin_Continue otherwise.
*/
forward Action:OnPopHelmet(client, Float:velocity[3], Float:origin[3]);

/**
* @brief Called when a player respawn is being called.
*
* @param client					Client index.
* @return						Plugin_Handled to block, Plugin_Continue otherwise.
*/
forward Action:OnPlayerRespawn(client);

/**
* @brief Called when wave time is being added.
*
* @param index					Team index.
* @param delay					Wave time.
* @return						Plugin_Handled to block, Plugin_Continue otherwise.
*/
forward Action:OnAddWaveTime(index, &Float:delay);

/**
* @brief Called when a team is about to win.
*
* @param index					Team index.
* @return						Plugin_Handled to block, Plugin_Continue otherwise.
*/
forward Action:OnSetWinningTeam(index);

/**
* @brief Called when round state is being entered.
*
* @param roundState				Round state.
* @return						Plugin_Handled to block, Plugin_Continue otherwise.
*/
forward Action:OnEnterRoundState(&roundState);

/**
* @brief Called when a player state is being entered.
*
* @param client					Client index.
* @param playerState			Player state.
* @return						Plugin_Handled to block, Plugin_Continue otherwise.
*/
forward Action:OnEnterPlayerState(client, &playerState);

/**
* @brief Called when a bomb target state is being entered.
*
* @param bombTarget				Entity index.
* @param bombTargetState		Bomb target state.
* @return						Plugin_Handled to block, Plugin_Continue otherwise.
*/
forward Action:OnEnterBombTargetState(bombTarget, &bombTargetState);

public Extension:__ext_dodhooks =
{
	name = "DoD Hooks",
	file = "dodhooks.ext",
	#if defined AUTOLOAD_EXTENSIONS
	autoload = 1,
	#else
	autoload = 0,
	#endif
	#if defined REQUIRE_EXTENSIONS
	required = 1,
	#else
	required = 0,
	#endif
};

#if !defined REQUIRE_EXTENSIONS
public __ext_dodhooks_SetNTVOptional()
{
	MarkNativeAsOptional("SetPlayerClass");
	MarkNativeAsOptional("GetPlayerClass");
	MarkNativeAsOptional("SetDesiredPlayerClass");
	MarkNativeAsOptional("GetDesiredPlayerClass");
	MarkNativeAsOptional("PopHelmet");
	MarkNativeAsOptional("SetPlayerState");
	MarkNativeAsOptional("PrecacheCPIcon");
	MarkNativeAsOptional("SetCPIcons");
	MarkNativeAsOptional("SetCPIconNumPlayers");
	MarkNativeAsOptional("SetCPIconCapInfo");
	MarkNativeAsOptional("SetCPIconBombPlanted");
	MarkNativeAsOptional("SetCPIconBombBeingDefused");
	MarkNativeAsOptional("SetCPIconBombInfo");
	MarkNativeAsOptional("SetCPIconOwner");
	MarkNativeAsOptional("SetNumControlPoints");
	MarkNativeAsOptional("SetCPVisible");
	MarkNativeAsOptional("SetCPPosition");
	MarkNativeAsOptional("StartRoundTimer");
	MarkNativeAsOptional("PauseTimer");
	MarkNativeAsOptional("ResumeTimer");
	MarkNativeAsOptional("SetTimeRemaining");
	MarkNativeAsOptional("GetTimeRemaining");
	MarkNativeAsOptional("RespawnPlayer");
	MarkNativeAsOptional("SetWinningTeam");
	MarkNativeAsOptional("AddWaveTime");
	MarkNativeAsOptional("SetRoundState");
	MarkNativeAsOptional("SetBombTargetState");
}
#endif