#include <windows.h>
#include "../groupvoice/dsound_glob.h"
#include "../groupvoice/coder.h"
#include "../q_shared.h"
#include "../common/qcommon.h"
#include "win_dsound.h"
#include "win_shared.h"

dvar_s* winvoice_mic_reclevel;
dvar_s* winvoice_mic_mute;
dvar_s* winvoice_save_voice;
dvar_s* winvoice_mic_scaler;

char old_rec_source[256];
int mic_old_reclevel;

int mic_current_reclevel;
bool g_voice_initialized;
dsound_sample_t* s_clientSamples[MAX_CLIENTS];
int s_clientTalkTime[MAX_CLIENTS];
bool recording;
dsound_sample_t *currentRecordingSample;
float voice_current_voicelevel;
float voice_current_scaler;
struct ClientVoicePacket_t;

void Voice_Playback()
{
    int client;

    if ( !g_voice_initialized )
    {
        return;
    }

    if ( winvoice_mic_reclevel->current.integer != mic_current_reclevel )
    {
        mic_current_reclevel = winvoice_mic_reclevel->current.integer;
        mixerSetRecordLevel("Mic", mic_current_reclevel);
    }
    for ( client = 0; client < MAX_CLIENTS; ++client )
    {
        Sound_SampleFrame(s_clientSamples[client]);
    }
    Sound_Frame();

}

bool Voice_Init()
{
    HWND handle;
    int client;

    Com_Printf(CON_CHANNEL_SYSTEM, "--- Initializing Voice ---\n");

    winvoice_mic_mute = Dvar_RegisterBool("winvoice_mic_mute", 1, 1u, "Mute the microphone");
    winvoice_mic_reclevel = Dvar_RegisterInt("winvoice_mic_reclevel", 65535, 0, 65535, 1u, "Microphone recording level");
    winvoice_save_voice = Dvar_RegisterBool("winvoice_save_voice", 0, 1u, "Write voice data to a file");
    winvoice_mic_scaler = Dvar_RegisterFloat("winvoice_mic_scaler", 1.0, 0.25, 2.0, 1u, "Microphone scaler value");

    g_current_bandwidth_setting = 0;

    if ( !mixerGetRecordSource(old_rec_source) )
    {
        strcpy(old_rec_source, "microphone-not-present");
    }

    mixerSetRecordSource(old_rec_source);
    mic_old_reclevel = mixerGetRecordLevel(old_rec_source);
    mic_current_reclevel = winvoice_mic_reclevel->current.integer;
    mixerSetRecordLevel(old_rec_source, winvoice_mic_reclevel->current.integer);
    mixerSetMicrophoneMute(winvoice_mic_mute->current.enabled);
    g_current_bandwidth_setting = 0;
    handle = GetDesktopWindow();

    Record_Init(0, handle);
    Decode_Init(g_current_bandwidth_setting);
    Encode_Init(g_current_bandwidth_setting);

    if ( Sound_Init(handle) )
    {
        g_voice_initialized = 1;
    }
    memset((char *)s_clientTalkTime, 0, sizeof(s_clientTalkTime));
    for ( client = 0; client < MAX_CLIENTS; ++client )
    {
        s_clientSamples[client] = Sound_NewSample();
        assert(s_clientSamples[client] != NULL);
    }
    return 0;
}


bool Voice_StopRecording()
{
    if ( !recording )
    {
        return false;
    }
    Record_Stop(currentRecordingSample);
    Record_DestroySample(currentRecordingSample);
    recording = false;
    return true;
}

bool Voice_StartRecording()
{
    if ( !recording )
    {
        currentRecordingSample = Record_NewSample();
        Record_Start(currentRecordingSample);
        recording = true;
        //++count_0;
    }
    return true;
}

void Voice_Shutdown()
{
    int client;

    if ( g_voice_initialized )
    {
        return;
    }
    for ( client = 0; client < MAX_CLIENTS; ++client )
    {
        Sound_DestroySample(s_clientSamples[client]);
    }
    Voice_StopRecording();
    Record_Shutdown();
    Encode_Shutdown();
    Decode_Shutdown();
    Sound_Shutdown();
    mixerSetMicrophoneMute(1);
    mixerSetRecordLevel(old_rec_source, mic_old_reclevel);
    mixerSetRecordSource(old_rec_source);
    g_voice_initialized = 0;
}

int sampleCount;
float levelSamples[6];

double Voice_GetVoiceLevel()
{
    unsigned int ii;
    float avgLvl;

    if ( !g_voice_initialized )
    {
        return 0.0;
    }
    levelSamples[sampleCount++ % ARRAY_COUNT(levelSamples)] = (float)(voice_current_voicelevel / 32767.0) / 6.0;
    avgLvl = 0.0;
    for ( ii = 0; ii < ARRAY_COUNT(levelSamples); ++ii )
    {
        avgLvl = avgLvl + levelSamples[ii];
    }
    return avgLvl;
}

bool Voice_IsClientTalking(int clientNum)
{
    assert((unsigned)clientNum < MAX_CLIENTS);

    return (signed int)(Sys_Milliseconds() - s_clientTalkTime[(unsigned)clientNum]) < 300;
}

void Voice_IncomingVoiceData(uint8_t talker, unsigned char *data, int packetDataSize)
{
    int frameSz;
    FILE *stream;
    int i;
    int16_t out[4096];
    unsigned int data_len;

    if ( g_voice_initialized )
    {
/*
        if ( !playing )
        {
            playing = 1;
        }
*/
        data_len = 0;
        
        assert(talker >= 0 && talker < MAX_CLIENTS);

        s_clientTalkTime[talker] = Sys_Milliseconds();

        for (i = 0; i < packetDataSize; i += frameSz)
        {
            if ( packetDataSize - i < g_decode_frame_size )
            {
                frameSz = packetDataSize - i;
            }
            else
            {
                frameSz = g_decode_frame_size;
            }
            data_len = Decode_Sample((char*)data + i, frameSz, out, g_decode_frame_size);
            if ( (signed int)data_len > 0 )
            {
                Sound_UpdateSample(s_clientSamples[talker], (char *)out, data_len);
            }
        }

        if ( winvoice_save_voice->current.enabled )
        {
            stream = fopen("voice.wav", "ab");
            if ( stream )
            {
                fwrite(out, data_len, 1u, stream);
                fclose(stream);
            }
        }
    }
}

int Voice_GetLocalVoiceData(ClientVoicePacket_t *voiceData)
{
    if ( !g_voice_initialized )
    {
        return 0;
    }
    if ( !recording )
    {
        Voice_StartRecording();
    }
    if ( voice_current_scaler != winvoice_mic_scaler->current.value )
    {
        voice_current_scaler = winvoice_mic_scaler->current.value;
        if ( voice_current_scaler >= 0.5 )
        {
            if ( voice_current_scaler > 1.5 )
            {
                voice_current_scaler = 1.5;
            }
        }
        else
        {
            voice_current_scaler = 0.5;
        }
    }
    Record_Frame();
    return 0;
}

void Voice_StopClientSamples()
{
    int client;

    for ( client = 0; client < MAX_CLIENTS; ++client )
    {
        Sound_StopSample(s_clientSamples[client]);
    }
}