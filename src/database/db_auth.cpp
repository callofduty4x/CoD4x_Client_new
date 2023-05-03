#include "../zlib/zlib.h"
#include "../q_shared.h"

int DB_AuthLoad_InflateInit(z_stream_s *stream, bool isSecure, const char *__formal)
{
  assert(!isSecure);
  return inflateInit(stream);
}

int DB_AuthLoad_Inflate(struct z_stream_s *stream, int flush)
{
  return inflate(stream, flush);
}

void DB_AuthLoad_InflateEnd(struct z_stream_s *stream)
{
  inflateEnd(stream);
}
