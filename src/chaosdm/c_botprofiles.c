#include "g_local.h"
#include "c_base.h"
#include "c_botai.h"
#include "c_botprofiles.h"
#include "m_player.h"

/*
	
	Settings Available

	bot_minbots
	bot_maxbots
	bot_minskill
	bot_maxskill
	bot_randskill
	bot_ratio
	bot_teamratio
	bot_teamauto
	bot_joindelay

*/

/*
Init the bots
*/
void ManageBotProfiles(void)
{

	/* Dont run during intermission */
	if (level.intermissiontime)
		return;

	/* Only run every x ticks */
	botprofiles_tick++;
	if(botprofiles_tick < 30)
		return;

	/* Reset Ticks */
	botprofiles_tick = 0;

	int numplayers_bot, numplayers_human;
	int p, b, count, skill, team;
	char name[64], model[128];

	numplayers_human = 0;
	numplayers_bot = 0;

	for (p = 0; p < numplayers; p++)
	{
		
		if (!players[p])
			continue;

		if (!players[p]->client)
			continue;
		
		if(Q_stricmp(players[p]->classname,"bot") == 0)
		{
			numplayers_bot++;
		}else if(Q_stricmp(players[p]->classname,"player") == 0){
			numplayers_human++;
		}

	}
	
	numbots_target = round(numplayers_human * (bot_ratio->value / 100));
	if( numbots_target < bot_minbots->value )
		numbots_target = bot_minbots->value;

	if( numbots_target > bot_maxbots->value )
		numbots_target = bot_maxbots->value;

	if( numplayers_human == 0 )
		numbots_target = 0;
	
	/* Still not resetting bots/players on map change */
	printf (" Bot Manager Report on P: %i H: %i - B: %i = T: %i\n", numplayers, numplayers_human, numplayers_bot, numbots_target);

	if( numplayers_bot < numbots_target )
	{
		
		for(p = 0; p<botprofiles_count; p++)
		{

			b = rand()%(botprofiles_count + 1);
			
			if(strlen(botprofiles[b].name) > 0 && !botprofiles[b].connected)
			{
				
				printf (" Bot Manager Adding: %s\n", botprofiles[b].name);

				strcpy (name, botprofiles[b].name);
				strcpy (model, botprofiles[b].skin);
				skill = botprofiles[b].skill;				
				team = botprofiles[b].team;
				if(skill == 0)
					skill = 3;

				Bot_Create(skill, team, name, model); 
			
				botprofiles[b].connected = true;				
				numbots++;
				p = botprofiles_count;

			}

		}

	}
	else if( numplayers_bot > numbots_target )
	{

		count = numplayers_bot - numbots_target;

		printf (" Bot Manager Removing %i Bot(s)\n", count);
		
		for (p = 0; p < numplayers; p++)
		{
		
			if (!players[p])
				continue;

			if (!players[p]->client)
				continue;

			if(Q_stricmp(players[p]->classname,"bot") == 0 && count > 0)
			{

				for(b=0;b<botprofiles_count;b++){
					if( Q_stricmp(players[p]->client->pers.netname, botprofiles[b].name) == 0)
						botprofiles[b].connected = false;
				}

				ClientDisconnect(players[p]);
				count--;
				numbots--;

			}

		}

	}

}

void Load_BotProfiles(void)
{
	FILE	*fp;
	int	line, i, s, params_index;
	char	filename[256], buffer;
	cvar_t	*game_dir;

	game_dir = gi.cvar ("game", "", 0);

#ifdef	_WIN32
	i =  sprintf(filename, ".\\");
	i += sprintf(filename + i, game_dir->string);
	i += sprintf(filename + i, "\\botprofiles.txt");
#else
      strcpy(filename, "./");
      strcat(filename, game_dir->string);
      strcat(filename, "/botprofiles.txt");
#endif

	fp = fopen (filename, "r");
	if (!fp)
	{
		gi.error("Can't open botprofiles.txt!\n");
		return false;
	}

	memset(botprofiles_text, 0, sizeof(botprofiles_text));

	line = -1;

	while (!feof(fp))
	{

		fscanf(fp, "%c", &buffer);

		if (buffer == ';')	//comment, strip the rest of the line
		{
			while (!feof(fp) && (buffer != '\n'))
				fscanf(fp, "%c", &buffer);
		}
		else if (line > NUM_BOTPROFILES -1)
		{
			fclose(fp);
			return true;
		}
		else if (((buffer >= 'a') && (buffer <= 'z')) ||	// a chat line...read it
				 ((buffer >= 'A') && (buffer <= 'Z')) ||
				 (buffer == '%'))
		{
			
			char param_value[MAX_INFO_STRING];
			int params_read, params_index;

			i = 0;
			s = 0;
			line++;
			params_index = 0;
			params_read = 1;

			// allocate memory	
			botprofiles_text[line] = gi.TagMalloc(256, TAG_GAME);
			memset(botprofiles_text[line], 0, 256);


			while (!feof(fp) && params_read == 1)
			{
				
				if( buffer == ' ' || buffer == '\n' ){

					if(params_index == 0){
						strcpy(botprofiles[botprofiles_count].name, param_value);
					}else if(params_index == 1){
						strcpy(botprofiles[botprofiles_count].skin, param_value);
					}else if(params_index == 2){
						botprofiles[botprofiles_count].skill = atoi(param_value);
					}else if(params_index == 3){
						botprofiles[botprofiles_count].team = atoi(param_value);
					}

					memset(param_value, 0, 256);
					params_index++;
					s = 0;

					if(buffer == '\n')
						params_read = 0;

				}else{

					botprofiles_text[line][i++] = buffer;
					param_value[s++] = buffer;

				}

				if(params_read == 1){
					fscanf(fp, "%c", &buffer);
				}

			}

			if (i > 0)
			{
				botprofiles_text[line][i] = '\0';	//append ascii null
			}
			else	//empty line ?
				line--;

			botprofiles_count = line;

		}


	}

	Com_Printf ("\nLoaded Bot Profiles\n");
	
	/* Reset our Vars */
	botprofiles_tick = 0;

	fclose(fp);
	return true;
}

