/*
* basic definitions
*/
#define	NUM_BOTPROFILES		64
#define	NUM_BOTCHATSECTIONS		5
#define	MAX_LINES_PER_BOTSECTION		64

char	*botprofiles_text[NUM_BOTPROFILES];
int		botprofiles_count;
int		botprofiles_tick;

int		numbots_spawned;
int		numbots_target;


/*
*  botprofile structure
*/
typedef struct
{
	char	name[16];
	char	skin[MAX_INFO_STRING];
	int		skill;
	int		team;
	char	*chat_text[NUM_BOTCHATSECTIONS][MAX_LINES_PER_BOTSECTION];
	int		chat_linecount[NUM_BOTCHATSECTIONS];
	qboolean		connected;

} botprofile_t ;

botprofile_t	botprofiles[NUM_BOTPROFILES];
