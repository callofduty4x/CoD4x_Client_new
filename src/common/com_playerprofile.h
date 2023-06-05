void Com_InitPlayerProfiles(int localclientnum);
bool Com_HasPlayerProfile();
void Com_BuildPlayerProfilePath(char *path, int pathSize, const char* format, ...);
void Com_WriteConfigToFile(int localClientNum, const char *filename);