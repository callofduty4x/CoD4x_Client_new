#include "db_shared.h"

struct z_stream_s;

struct ScriptStringList
{
  int count;
  const char **strings;
};


struct XAssetList
{
  struct ScriptStringList stringList;
  int assetCount;
  struct XAsset *assets;
};

extern struct XAssetList* varXAssetList;
extern ScriptStringList* varScriptStringList;
extern struct XAsset* varXAsset;
extern const char* g_assetNames[];

void DB_PostLoadXZone();
int DB_AuthLoad_InflateInit(z_stream_s *stream, bool isSecure, const char *__formal);
int DB_AuthLoad_Inflate(z_stream_s *stream, int flush);
void DB_AuthLoad_InflateEnd(z_stream_s *stream);

void DB_PushStreamPos(unsigned int index);
void Load_ScriptStringList(bool atStreamStart);
void DB_PopStreamPos();
XAsset *AllocLoad_XAsset();
void Load_Stream(bool atStreamStart, const void *ptr, int size);
void Load_XAsset(bool atStreamStart);
void Load_DelayStream();
void DB_LoadDelayedImages();


struct XAsset
{
  enum XAssetType type;
  union XAssetHeader header;
};
