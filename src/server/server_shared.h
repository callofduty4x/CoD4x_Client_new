#ifndef SERVER_SERVER_SHARED_H_
#define SERVER_SERVER_SHARED_H_

#include <q_shared.h>

struct gentity_s;

void SV_WaitServer();
void SV_AllowPackets(const bool allow);
void SV_Shutdown(const char *finalmsg);
void SV_GetConfigstring( int index, char *buffer, int bufferSize );
int SV_DObjGetBoneIndex(const gentity_s *ent, unsigned int boneName);
qboolean SV_IsLocalClient(int clientNum);
void SV_GetUserinfo(int index, char *buffer, int bufferSize);
gentity_s *SV_GentityNum( int num );

#endif
