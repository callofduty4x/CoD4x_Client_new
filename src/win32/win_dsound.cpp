#include "../groupvoice/dsound_glob.h"

static dsound_sample_t *s_recordingSamplePtr;
static dsound_sample_t s_recordingSamples[MAX_CLIENTS + 1];
static bool g_recording_initialized;
static LPDIRECTSOUNDCAPTURE g_pDSCaptureInstance;
static int g_sound_recordFrequency = 0x2000;
static int g_sound_recordVolume = 255;
static int g_sound_channels = 1;
static int g_sound_recordBufferSize = 0xC800;
static bool g_currently_recording;
static dsound_sample_t *g_current_sample;
int (*current_audioCallback)(struct audioSample_t *);

/****************************************************************************/
//Sound recording functionality
/****************************************************************************/

bool DSOUNDRecord_Init(bool bCallDsoundInit, const void *handle)
{
  HRESULT hr;

  s_recordingSamplePtr = s_recordingSamples;
  g_recording_initialized = 0;
  if ( bCallDsoundInit && (hr = DirectSoundCaptureCreate(NULL, &g_pDSCaptureInstance, NULL), hr < 0) )
  {
    Com_PrintError(CON_CHANNEL_SOUND, "Error initializing direct sound instance!  %d\n", (int)hr);
    return false;
  }
  g_recording_initialized = 1;
  return true;
}

void DSOUNDRecord_Shutdown()
{
  HRESULT hr;

  hr = 0;
  if ( g_pDSCaptureInstance )
  {
    hr = g_pDSCaptureInstance->Release( );
  }
  g_pDSCaptureInstance = NULL;
  if ( hr < 0 )
  {
    Com_PrintError(CON_CHANNEL_SOUND, "Error releasing direct sound instance!  %d\n", (int)hr);
  }
}

dsound_sample_t * DSOUNDRecord_NewSample()
{
  dsound_sample_t *pRecSample;

  assert(s_recordingSamplePtr - s_recordingSamples <= MAX_CLIENTS + 1);

  pRecSample = s_recordingSamplePtr;
  ++s_recordingSamplePtr;
  memset(pRecSample, 0, sizeof(dsound_sample_t));
  pRecSample->frequency = g_sound_recordFrequency;
  pRecSample->volume = g_sound_recordVolume;
  pRecSample->pan = 128;
  pRecSample->channels = g_sound_channels;
  pRecSample->stopPosition = -1;
  pRecSample->playMode = 2;
  return pRecSample;
}

bool DSOUNDRecord_DestroySample(dsound_sample_t *pRecSample)
{
  if ( !g_recording_initialized )
  {
    return false;
  }
  if ( pRecSample->DSB )
  {
    pRecSample->DSB->Release( );
    pRecSample->DSB = NULL;
  }
  return true;
}


void DSOUNDRecord_UpdateSample(dsound_sample_t *pRecSample)
{
    int lLockSize;
    HRESULT hr;
    void *pLock1;
    DWORD dwCapturePos;
    audioSample_t audioSample;
    DWORD dwLockLen2;
    int iChannels;
    void *pLock2;
    DWORD dwReadPos;
    DWORD dwLockLen1;

    if ( !g_recording_initialized )
    {
        return;
    }
    if ( pRecSample->DSCB->GetCurrentPosition(&dwCapturePos, &dwReadPos) < 0 )
    {
        Com_PrintError(CON_CHANNEL_SOUND, "Error: Failed to get cursor positions \n");
    }
    if ( dwReadPos >= pRecSample->dwCaptureOffset )
    {
        lLockSize = dwReadPos - pRecSample->dwCaptureOffset;
    }
    else
    {
        lLockSize = dwReadPos + pRecSample->dwBufferSize - pRecSample->dwCaptureOffset;
    }
    lLockSize -= lLockSize % 4;
    if ( !lLockSize )
    {
        return;
    }
    hr = pRecSample->DSCB->Lock( pRecSample->dwCaptureOffset, lLockSize, &pLock1,
                                    &dwLockLen1, &pLock2, &dwLockLen2, 0);
    if(hr < 0)
    {
        if ( hr == DSERR_INVALIDPARAM )
        {
            Com_Printf(CON_CHANNEL_SOUND, "DSERR_INVALIDPARAM\n");
            Com_Printf(CON_CHANNEL_SOUND, " Offset : %i, length: %i\n", pRecSample->dwCaptureOffset, lLockSize);
        }
        else if ( hr == DSERR_INVALIDCALL )
        {
            Com_Printf(CON_CHANNEL_SOUND, "DSERR_INVALIDCALL\n");
        }
        Com_PrintError(CON_CHANNEL_SOUND, "Error trying to lock sample!\n");
        return;
    }  
    audioSample.stereo = g_sound_channels > 1;
    if ( g_sound_channels <= 1 )
    {
        iChannels = 1;
    }
    else
    {
        iChannels = 2;
    }
    audioSample.bytesPerSample = 2;
    audioSample.frequency = g_sound_recordFrequency;
    audioSample.sampleOffset = 0;
    audioSample.channels = g_sound_channels;
    lLockSize = dwLockLen2 + dwLockLen1;
    if ( pLock1 )
    {
        audioSample.lengthInSamples = dwLockLen1 / (2 * iChannels);
        audioSample.lengthInBytes = dwLockLen1;
        audioSample.buffer = (char *)pLock1;
        current_audioCallback(&audioSample);
    }
    if ( pLock2 )
    {
        audioSample.lengthInSamples = dwLockLen2 / (2 * iChannels);
        audioSample.lengthInBytes = dwLockLen2;
        audioSample.buffer = (char *)pLock2;
        current_audioCallback(&audioSample);
    }
    pRecSample->dwCaptureOffset += lLockSize;
    pRecSample->dwCaptureOffset %= pRecSample->dwBufferSize;

    hr = pRecSample->DSCB->Unlock( pLock1, dwLockLen1, pLock2, dwLockLen2);
    if ( hr < 0 )
    {
        if ( hr == DSERR_INVALIDPARAM )
        {
        Com_Printf(CON_CHANNEL_SOUND, "DSERR_INVALIDPARAM\n");
        Com_Printf(CON_CHANNEL_SOUND, " Offset : %i\n", pRecSample->dwCaptureOffset);
        }
        else if ( hr == DSERR_INVALIDCALL )
        {
        Com_Printf(CON_CHANNEL_SOUND, "DSERR_INVALIDCALL\n");
        }
        Com_PrintError(CON_CHANNEL_SOUND, "Error trying to unlock sample!\n");
    }

}


void DSOUNDRecord_Frame()
{
  if ( g_recording_initialized && g_currently_recording )
  {
    if ( g_current_sample )
    {
      DSOUNDRecord_UpdateSample(g_current_sample);
    }
  }
}

HRESULT DSOUNDRecord_Start(dsound_sample_t *pRecSample)
{
  HRESULT hr;
  DSCBUFFERDESC dscbd;
  tWAVEFORMATEX wfx;

  if ( !g_recording_initialized )
  {
    return -1;
  }
  if ( !pRecSample )
  {
    return -1;
  }
  wfx.wFormatTag = 1;
  wfx.nChannels = g_sound_channels;
  wfx.wBitsPerSample = 16;
  wfx.nSamplesPerSec = g_sound_recordFrequency;
  wfx.nAvgBytesPerSec = 2 * g_sound_channels * g_sound_recordFrequency;
  wfx.nBlockAlign = 2 * g_sound_channels;
  wfx.cbSize = 0;
  dscbd.dwSize = sizeof(dscbd);
  dscbd.dwFlags = 0;
  dscbd.dwBufferBytes = g_sound_recordBufferSize;
  dscbd.dwReserved = 0;
  dscbd.lpwfxFormat = &wfx;
  dscbd.dwFXCount = 0;
  dscbd.lpDSCFXDesc = 0;

  if( pRecSample->DSCB == NULL )
  {
    hr = g_pDSCaptureInstance->CreateCaptureBuffer(&dscbd, &pRecSample->DSCB, NULL);
    if(hr < 0)
    {
      switch ( hr )
      {
        case DSERR_BADFORMAT:
            Com_Printf(CON_CHANNEL_SOUND, "BADFORMAT\n");
            break;
        case DSERR_GENERIC:
            Com_Printf(CON_CHANNEL_SOUND, "GENERIC\n");
            break;
        case DSERR_OUTOFMEMORY:
            Com_Printf(CON_CHANNEL_SOUND, "OUTOFMEMORY \n");
            break;
        case DSERR_INVALIDPARAM:
            Com_Printf(CON_CHANNEL_SOUND, "INVALIDPARAM\n");
            break;
        case DSERR_NODRIVER:
            Com_Printf(CON_CHANNEL_SOUND, "NODRIVER \n");
            break;
        case DSERR_UNINITIALIZED:
            Com_Printf(CON_CHANNEL_SOUND, "UNINITIALIZED \n");
            break;
        default:
            break;
      }
      Com_PrintError(CON_CHANNEL_SOUND, "error: Failed to allocate Capture Buffer \n");
      return -1;
    }
  }
  pRecSample->dwCaptureOffset = 0;
  pRecSample->dwBufferSize = dscbd.dwBufferBytes;
  hr = pRecSample->DSCB->Start( DSCBSTART_LOOPING );
  if ( hr < 0 )
  {
    Com_PrintError(CON_CHANNEL_SOUND, "error: Unable to Read to Buffer\n");
    return -1;
  }
  g_current_sample = pRecSample;
  g_currently_recording = true;
  return hr;
}

HRESULT DSOUNDRecord_Stop(dsound_sample_t *pRecSample)
{
  HRESULT hr;

  if ( !g_recording_initialized )
  {
    return -1;
  }
  if ( !pRecSample->DSCB )
  {
    return -1;
  }
  if ( pRecSample->DSCB->Stop( ) < 0 )
  {
    Com_PrintError(CON_CHANNEL_SOUND, "Error stopping recording buffer\n");
  }
  else
  {
    g_current_sample = NULL;
    g_currently_recording = false;
  }
  hr = pRecSample->DSCB->Release();
  if ( hr < 0 )
  {
    Com_PrintError(CON_CHANNEL_SOUND, "Error releasing recording buffer\n");
  }
  else
  {
    pRecSample->DSCB = 0;
  }
  return hr;
}

/****************************************************************************/
//Sound playback functionality
/****************************************************************************/
static IDirectSound8 *lpds;
static bool dsoundplay_initialized;
static int g_sound_playBufferSize = 0xC800;

#define MIN_COMFORTABLE_BUFFER_AMOUNT 0x140
#define MAX_COMFORTABLE_BUFFER_AMOUNT 0x2710
#define COMFORTABLE_BUFFER_AMOUNT 0x1770

float maxScalingUpMultiplier = 0.01;
float maxScalingDownMultiplier = 0.01;


bool DSound_Init(bool callDsoundInit, const void *handle)
{
    if ( dsoundplay_initialized )
    {
        return true;
    }
    if ( DirectSoundCreate8(0, &lpds, 0) < 0 )
    {
        Com_Printf(CON_CHANNEL_SOUND, "ERROR: [play] failed to initialize DirectSound\n");
        return false;
    }
    if ( lpds->SetCooperativeLevel((HWND)handle, 2) >= 0 )
    {
      dsoundplay_initialized = true;
      return true;
    }
    Com_Printf(CON_CHANNEL_SOUND, "Error: [play] failure when calling SetCooperativeLevel()\n");
    return false;
}

void DSound_Shutdown()
{
  if ( dsoundplay_initialized )
  {
    lpds->Release( );
    dsoundplay_initialized = false;
  }
}


HRESULT CreateBasicBuffer(IDirectSound8 *lpDirectSound, IDirectSoundBuffer **ppDsb, int sampleRate, int channels, int bufferSize)
{
  HRESULT hr;
  DSBUFFERDESC dsbdesc;
  tWAVEFORMATEX wfx;

  wfx.cbSize = 0;
  wfx.wFormatTag = 1;
  wfx.nChannels = channels;
  wfx.wBitsPerSample = 16;
  wfx.nSamplesPerSec = sampleRate;
  wfx.nBlockAlign = 16 * (uint16_t)channels / 8;
  wfx.nAvgBytesPerSec = sampleRate * wfx.nBlockAlign;
  dsbdesc.dwReserved = 0;
  memset(&dsbdesc.guid3DAlgorithm, 0, sizeof(dsbdesc.guid3DAlgorithm));
  dsbdesc.dwSize = sizeof(dsbdesc);
  dsbdesc.dwFlags = 0x80E8;
  dsbdesc.dwBufferBytes = bufferSize;
  dsbdesc.lpwfxFormat = &wfx;
  hr = lpds->CreateSoundBuffer(&dsbdesc, ppDsb, NULL);
  if ( hr < 0 )
  {
    Com_Printf(CON_CHANNEL_SOUND, "Failed to create sound buffer!\n");
  }
  return hr;
}


dsound_sample_t * DSound_NewSample()
{
  dsound_sample_t *sample;

  if ( !dsoundplay_initialized )
  {
    return NULL;
  }
  sample = DSOUNDRecord_NewSample();
  sample->dwBufferSize = g_sound_playBufferSize;
  if ( CreateBasicBuffer(lpds, &sample->DSB, sample->frequency, sample->channels, g_sound_playBufferSize) >= 0 )
  {
    return sample;
  }
  Com_Printf(CON_CHANNEL_SOUND, "Error: Failed to create DirectSound play buffer\n");
  sample->DSB->Release( );
  sample->DSB = NULL;
  return NULL;
}

int DSound_GetBytesLeft(dsound_sample_t *sample)
{
  return sample->bytesBuffered;
}

unsigned int DSound_UpdateSample(dsound_sample_t *sample, char *data, unsigned int data_len)
{
    signed int bytesToUpload;
    HRESULT hr;
    int dataOffset;
    int bytesLeft;
    void *pLock1;
    DWORD dwLockLen2;
    void *pLock2;
    DWORD dwLockLen1;

    if ( !dsoundplay_initialized )
    {
        return -1;
    }
    if ( !data_len )
    {
        return 0;
    }
    bytesLeft = DSound_GetBytesLeft(sample);

    assert(bytesLeft <= (signed int)sample->currentBufferLength);

    bytesToUpload = (signed int)data_len;

    if ( bytesToUpload > (signed int)(sample->dwBufferSize - bytesLeft) )
    {
        bytesToUpload = sample->dwBufferSize - bytesLeft;
    }
    if ( !bytesToUpload )
    {
        return 0;
    }
    assert(bytesToUpload > 0);
    assert(bytesToUpload < (signed int)sample->dwBufferSize);

    hr = sample->DSB->Lock( sample->currentOffset, bytesToUpload, &pLock1, &dwLockLen1, &pLock2,
                                &dwLockLen2, 0);

    if( hr < 0)
    {
        switch ( hr )
        {
            case DSERR_PRIOLEVELNEEDED:
                Com_Printf(CON_CHANNEL_SOUND, "DSERR_PRIOLEVELNEEDED\n");
                break;
            case DSERR_INVALIDPARAM:
                Com_Printf(CON_CHANNEL_SOUND, "DSERR_INVALIDPARAM\n");
                Com_Printf(CON_CHANNEL_SOUND, " Offset : %i, length: %i\n", sample->currentOffset, bytesToUpload);
                break;
            case DSERR_INVALIDCALL:
                Com_Printf(CON_CHANNEL_SOUND, "DSERR_INVALIDCALL\n");
                break;
            case DSERR_BUFFERLOST:
                Com_Printf(CON_CHANNEL_SOUND, "DSERR_BUFFERLOST\n");
                break;
            default:
                break;
        }
        Com_Printf(CON_CHANNEL_SOUND, "Error trying to lock sample!\n");
        return -1;
    }
    dataOffset = 0;
    if ( pLock1 )
    {
      memcpy((char *)pLock1, data, dwLockLen1);
      dataOffset = dwLockLen1;
    }
    if ( pLock2 )
    {
      memcpy((char *)pLock2, &data[dataOffset], dwLockLen2);
      dataOffset += dwLockLen2;
    }
    hr = sample->DSB->Unlock(pLock1, dwLockLen1, pLock2, dwLockLen2);
    if(hr < 0)
    {
        if ( hr == DSERR_INVALIDPARAM )
        {
            Com_Printf(CON_CHANNEL_SOUND, "DSERR_INVALIDPARAM\n");
        }
        else if ( hr == DSERR_INVALIDCALL )
        {
            Com_Printf(CON_CHANNEL_SOUND, "DSERR_INVALIDCALL\n");
        }
        Com_Printf(CON_CHANNEL_SOUND, "Error trying to unlock sample!\n");
        return -1;
    }
    assert(sample->currentBufferLength <= sample->dwBufferSize);

    if ( sample->currentBufferLength < sample->dwBufferSize )
    {
        sample->currentBufferLength += dataOffset;
        if ( sample->currentBufferLength > sample->dwBufferSize )
        {
            sample->currentBufferLength = sample->dwBufferSize;
        }
    }
    sample->bytesBuffered += dataOffset;

    assert(sample->bytesBuffered <= (signed int)sample->currentBufferLength);

    if ( sample->playing )
    {
        sample->lastOffset = sample->currentOffset;
    }
    sample->currentOffset = (dataOffset + sample->currentOffset) % sample->dwBufferSize;

    assert(bytesLeft + bytesToUpload >= DSound_GetBytesLeft(sample));

    return dwLockLen2 + dwLockLen1;
}

bool DSound_StopSample(dsound_sample_t *sample)
{
  if ( !dsoundplay_initialized )
  {
    return false;
  }
  if ( !sample->playing )
  {
    return false;
  }
  if ( sample->DSB )
  {
    sample->DSB->Stop();
  }
  sample->stopPosition = -1;
  sample->channel = -1;
  sample->playing = 0;
  if ( sample->DSB->SetCurrentPosition( 0 ) < 0 )
  {
    Com_Printf(CON_CHANNEL_SOUND, "Error: Failed to set current position to %i when playing sound buffer!\n", sample->lastOffset);
  }
  return true;
}

void DSound_AdjustSamplePlayback(dsound_sample_t *sample, int bytesLeft)
{
  assert(bytesLeft > 0);

  if ( bytesLeft >= MIN_COMFORTABLE_BUFFER_AMOUNT )
  {
    if ( bytesLeft <= MAX_COMFORTABLE_BUFFER_AMOUNT )
    {
      if ( (!sample->playMode && bytesLeft <= COMFORTABLE_BUFFER_AMOUNT) || (sample->playMode == 1 && bytesLeft >= COMFORTABLE_BUFFER_AMOUNT) )
      {
        sample->playMode = 2;
      }
    }
    else
    {
      sample->playMode = 0;
    }
  }
  else
  {
    sample->playMode = 1;
  }
  switch(sample->playMode)
  {
        case 0:
            sample->DSB->SetFrequency((double)sample->frequency + (double)sample->frequency * maxScalingUpMultiplier);
            break;
        case 1:
            sample->DSB->SetFrequency((double)sample->frequency - (double)sample->frequency * maxScalingDownMultiplier);
            break;
        case 2:
            sample->DSB->SetFrequency(sample->frequency);
            break;
  }
}

bool DSound_BufferUnderrunOccurred(dsound_sample_t *sample)
{
  return sample->bytesBuffered <= 0;
}

void DSound_HandleBufferUnderrun(dsound_sample_t *sample)
{
  sample->DSB->Stop( );
  sample->currentBufferLength = 0;
  sample->currentOffset = 0;
  sample->lastOffset = 0;
  sample->lastPlayPos = 0;
  if ( sample->stopPosition )
  {
    sample->stopPosition -= sample->currentOffset;
  }
  else
  {
    sample->stopPosition = 0;
  }
  sample->DSB->SetCurrentPosition(sample->currentOffset);
  sample->lastOffset = sample->currentOffset;
  sample->playing = 0;
  sample->bytesBuffered = 0;
}

void DSound_SampleFrame(dsound_sample_t *sample)
{
  DWORD dwWritePos;
  HRESULT hr;
  int bytesLeft;
  DWORD dwPlayPos;
  int bytesPlayed;

  bytesLeft = DSound_GetBytesLeft(sample);
  if ( !sample->playing && bytesLeft >= COMFORTABLE_BUFFER_AMOUNT )
  {
    hr = sample->DSB->Play(0, 0, DSBPLAY_LOOPING);
    if ( hr < 0 )
    {
      Com_Printf(CON_CHANNEL_SOUND, "Error: Failed to play DirectSound play buffer (%i)!\n", (int)hr);
      return;
    }
    hr = sample->DSB->SetCurrentPosition(sample->lastPlayPos);
    if ( hr < 0 )
    {
      Com_Printf(CON_CHANNEL_SOUND, "Error: Failed to set current position to %i when playing sound buffer!\n", sample->lastOffset);
    }
    sample->playing = 1;
    sample->playMode = 2;
  }
  if ( sample->playing )
  {
    hr = sample->DSB->GetCurrentPosition(&dwPlayPos, &dwWritePos);
    if ( hr < 0 )
    {
      Com_Printf(CON_CHANNEL_SOUND, "Error: Failed to get cursor positions \n");
    }
    dwWritePos = sample->currentOffset;
    if ( sample->stopPosition < 0 )
    {
      if ( DSound_BufferUnderrunOccurred(sample) )
      {
        DSound_HandleBufferUnderrun(sample);
        return;
      }
    }
    else if ( sample->lastPlayPos > dwPlayPos )
    {
      if ( sample->stopPosition >= (signed int)sample->lastPlayPos || sample->stopPosition <= (signed int)dwPlayPos )
      {
        DSound_StopSample(sample);
        return;
      }
    }
    else if ( (signed int)sample->lastPlayPos < sample->stopPosition && (signed int)dwPlayPos >= sample->stopPosition )
    {
      DSound_StopSample(sample);
      return;
    }
    DSound_AdjustSamplePlayback(sample, bytesLeft);
    bytesPlayed = dwPlayPos - sample->lastPlayPos;
    if ( bytesPlayed < 0 )
    {
      bytesPlayed = dwPlayPos + sample->currentBufferLength - sample->lastPlayPos;
    }
    assert(bytesPlayed >= 0);
    sample->bytesBuffered -= bytesPlayed;
    if ( DSound_BufferUnderrunOccurred(sample) )
    {
      DSound_HandleBufferUnderrun(sample);
    }
    else
    {
      sample->lastPlayPos = dwPlayPos;
    }
  }
}

void DSound_Frame()
{

}
