bool Encode_Shutdown();
int Encode_GetFrameSize();
int Encode_Sample(int16_t *buffer_in, char *buffer_out, int maxLength);
bool Decode_Init(int bandwidth);
bool Encode_Init(int bandwidth);
void Decode_Shutdown();
int Decode_Sample(char *buffer, int maxLength, int16_t *out, int frame_size);
extern int g_decode_frame_size;
