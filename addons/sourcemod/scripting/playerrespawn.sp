#pragma semicolon 1

#include <sourcemod>
#include <autoexecconfig>

#undef REQUIRE_PLUGIN
#include <updater>

#undef REQUIRE_EXTENSIONS
#include <cstrike>
#include <tf2>
#include <dodhooks>
#define REQUIRE_EXTENSIONS

#define RESPAWN_VERSION "1.1.3"

#define UPDATE_URL    "https://bara.in/update/playerrespawn.txt"

new Handle:g_hEnablePlugin = INVALID_HANDLE;
new Handle:g_hEnableCount = INVALID_HANDLE;
new Handle:g_hRespawnCount = INVALID_HANDLE;
new Handle:g_hEnableMessage = INVALID_HANDLE;

new g_iRespawnCount[MAXPLAYERS+1] = 0;

public Plugin:myinfo = 
{
	name = "Player Respawn",
	author = "Bara",
	description = "Players are able to respawn themselves",
	version = RESPAWN_VERSION,
	url = "www.bara.in"
}

public OnPluginStart()
{
	if(GetEngineVersion() == Engine_DODS)
	{
		if (GetExtensionFileStatus("dodhooks.ext") != 1)
		{
			SetFailState("Cant found the extensions DODHOOKS!");
		}
	}
	else if(GetEngineVersion() != Engine_CSS && GetEngineVersion() != Engine_CSGO && GetEngineVersion() != Engine_TF2)
	{
		SetFailState("Only CSS, CSGO, TF2 Support and DODS with DODHOOKS");
	}

	LoadTranslations("playerrespawn.phrases");

	CreateConVar("playerrespawn_version", RESPAWN_VERSION, "Player Respawn", FCVAR_NOTIFY|FCVAR_DONTRECORD);

	AutoExecConfig_SetFile("plugin.playerrespawn", "sourcemod");
	AutoExecConfig_SetCreateFile(true);

	g_hEnablePlugin = AutoExecConfig_CreateConVar("respawn_enable", "1", "Enable / Disable this Player Respawn Plugin", _, true, 0.0, true, 1.0);
	g_hEnableMessage = AutoExecConfig_CreateConVar("respawn_message", "1", "Enable / Disable Chat Message when Player use !respawn", _, true, 0.0, true, 1.0);
	g_hEnableCount = AutoExecConfig_CreateConVar("respawn_enable_count", "1", "Enable / Disable certain number of Respawn per Round", _, true, 0.0, true, 1.0);
	g_hRespawnCount = AutoExecConfig_CreateConVar("respawn_count", "2", "How many respawn Count per Round?");

	AutoExecConfig_ExecuteFile();
	AutoExecConfig_CleanFile();

	RegConsoleCmd("sm_respawn", Command_Respawn);

	HookEvent("round_end", Event_RoundEnd);

	if(LibraryExists("updater"))
	{
		Updater_AddPlugin(UPDATE_URL);
	}	
}

public OnLibraryAdded(const String:name[])
{
	if (StrEqual(name, "updater"))
	{
		Updater_AddPlugin(UPDATE_URL);
	}
}

public Event_RoundEnd(Handle:event,const String:name[],bool:dontBroadcast)
{
	if(GetConVarInt(g_hEnablePlugin))
	{
		for(new i = 1; i <= MaxClients; i++)
		{
			if(IsClientValid(i))
			{
				g_iRespawnCount[i] = 0;
			}
		}
	}
}

public Action:Command_Respawn(client, args)
{
	if(GetConVarInt(g_hEnablePlugin))
	{
		if(!IsPlayerAlive(client))
		{
			if(GetConVarInt(g_hEnableCount))
			{
				if(GetConVarInt(g_hRespawnCount) != g_iRespawnCount[client])
				{
					g_iRespawnCount[client]++;
					Respawn_Player(client);
				}
				else
				{
					ReplyToCommand(client, "%T", "RespawnReached", client);
				}
			}
			else
			{
				Respawn_Player(client);
			}
		}
		else
		{
			ReplyToCommand(client, "%T", "PlayerAlive", client);
		}
	}
}

stock Respawn_Player(client)
{
	if(GetEngineVersion() == Engine_CSS || GetEngineVersion() == Engine_CSGO)
	{
		CS_RespawnPlayer(client);

		if(GetConVarInt(g_hEnableMessage))
		{
			PrintToChatAll("%t", "PlayerSpawned", client);
		}
	}
	else if(GetEngineVersion() == Engine_TF2)
	{
		TF2_RespawnPlayer(client);

		if(GetConVarInt(g_hEnableMessage))
		{
			PrintToChatAll("%t", "PlayerSpawned", client);
		}
	}
	else if(GetEngineVersion() == Engine_DODS)
	{
		RespawnPlayer(client, true);

		if(GetConVarInt(g_hEnableMessage))
		{
			PrintToChatAll("%t", "PlayerSpawned", client);
		}
	}
}

public bool:IsClientValid(client)
{
	if(client > 0 && client <= MaxClients && IsClientInGame(client))
	{
		return true;
	}
	return false;
}