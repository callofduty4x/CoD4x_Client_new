#include "../q_shared.h"

#define DIRECTSOUND_VERSION 0x0800

#include <string.h>
#include <windows.h>
#include <mmreg.h>
#include <mmsystem.h>


#include <dsound.h>

extern char old_rec_source[0x100];

/*
DWORD mixerGetRecordLevel(char* SrcName)
{
  DWORD i;
  DWORD numConnections;
  HMIXEROBJ hmxobj;
  DWORD paDetails;
  struct tagMIXERLINECONTROLSA pmxlc;
  struct tMIXERCONTROLDETAILS pmxcd;
  struct tagMIXERLINEA mixerline;
  MIXERCONTROLA mixerControlObj;

  if ( waveInGetNumDevs() < 1 || mixerGetNumDevs() < 1 || mixerOpen((LPHMIXER)&hmxobj, 0, 0, 0, 0) )
  {
    return -1;
  }
  mixerline.cConnections = 0;
  mixerline.cbStruct = 168;
  mixerline.dwComponentType = 7;

  if(mixerGetLineInfoA(hmxobj, &mixerline, 3u) != MMSYSERR_NOERROR)
  {
    Com_PrintError(CON_CHANNEL_SOUND, "mixerGetRecordSource: Failed to get line info(0)!\n");
    mixerClose((HMIXER)hmxobj);
    return -1;
  }

  numConnections = mixerline.cConnections;

  if(numConnections >= 128)
  {
	Com_PrintError(CON_CHANNEL_SOUND, "mixerGetRecordSource exceeded 128 devices!\n");
	numConnections = 0;
  }

  for( i = 0; i < numConnections; i++ )
  {
    mixerline.dwSource = i;
    if(mixerGetLineInfoA(hmxobj, &mixerline, 1u) != MMSYSERR_NOERROR)
    {
      Com_PrintError(CON_CHANNEL_SOUND, "mixerGetRecordSource: Failed to get line info(1)!\n");
      mixerClose((HMIXER)hmxobj);
      return -1;
    }

    if ( strstr(mixerline.szName, SrcName) )
  	{
  		break;
  	}
  }
  if(i == numConnections)
  {
		Com_PrintWarning(CON_CHANNEL_SOUND, "mixerGetRecordSource: No mic found\n");
  		mixerClose((HMIXER)hmxobj);
		return -1;
  }
  pmxlc.dwLineID = mixerline.dwLineID;
  pmxlc.cbStruct = 24;
  pmxlc.dwControlID = 0x50030001u;
  pmxlc.cControls = 1;
  pmxlc.cbmxctrl = 148;
  pmxlc.pamxctrl = &mixerControlObj;
  if ( mixerGetLineControlsA(hmxobj, &pmxlc, 2u) )
  {
    mixerClose((HMIXER)hmxobj);
    return -1;
  }
  pmxcd.hwndOwner = 0;
  pmxcd.paDetails = &paDetails;
  pmxcd.cbStruct = 24;
  pmxcd.cChannels = 1;
  pmxcd.cbDetails = 4;
  pmxcd.dwControlID = mixerControlObj.dwControlID;
  mixerGetControlDetailsA(hmxobj, &pmxcd, 0);
  mixerClose((HMIXER)hmxobj);
  return paDetails;
}
*/


unsigned int mixerGetRecordLevel(char *SrcName)
{
  tagMIXERCONTROLA mxc;
  unsigned int jj;
  tagMIXERLINECONTROLSA mxlc;
  unsigned int err;
  HMIXER__ *phmx;
  unsigned int ii;
  tagMIXERLINEA mixerline;
  tMIXERCONTROLDETAILS_UNSIGNED newSetting;
  tMIXERCONTROLDETAILS mxcd;

  if ( waveInGetNumDevs() < 1 || mixerGetNumDevs() < 1 || mixerOpen(&phmx, 0, 0, 0, 0) )
  {
    return -1;
  }

  memset(&mixerline, 0, sizeof(mixerline));
  mixerline.cbStruct = sizeof(mixerline);
  mixerline.dwComponentType = 7;
  mixerGetLineInfoA((HMIXEROBJ)phmx, &mixerline, 3u);
  jj = mixerline.cConnections;
  for ( ii = 0; ii < jj; ++ii )
  {
    mixerline.dwSource = ii;
    mixerGetLineInfoA((HMIXEROBJ)phmx, &mixerline, 1u);
    if ( !Q_stricmp(mixerline.szName, SrcName) )
    {
      mxlc.cbStruct = sizeof(mxlc);
      mxlc.dwLineID = mixerline.dwLineID;
      mxlc.dwControlID = 0x50030001;
      mxlc.cControls = 1;
      mxlc.cbmxctrl = sizeof(mxc);
      mxlc.pamxctrl = &mxc;
      err = mixerGetLineControlsA((HMIXEROBJ)phmx, &mxlc, 2u);
      if ( !err )
      {
        mxcd.cbStruct = sizeof(mxcd);
        mxcd.cChannels = 1;
        mxcd.cbDetails = sizeof(newSetting);
        mxcd.paDetails = &newSetting;
        mxcd.cMultipleItems = 0;
        mxcd.dwControlID = mxc.dwControlID;
        mixerGetControlDetailsA((HMIXEROBJ)phmx, &mxcd, 0);
        Com_Printf(CON_CHANNEL_SYSTEM, "Line Control %3d: %22s", (int)mxc.dwControlID, mxlc.pamxctrl->szName);
        Com_Printf(CON_CHANNEL_SYSTEM, "\tcur: %6d\tbounds (%6d-%6d)\n", (int)newSetting.dwValue, (int)mxlc.pamxctrl->Bounds.lMinimum, (int)mxlc.pamxctrl->Bounds.lMaximum);
        mixerClose(phmx);
        return newSetting.dwValue;
      }
      break;
    }
  }
  mixerClose(phmx);
  return -1;
}

int mixerSetRecordLevel(const char *SrcName, uint16_t newLevel)
{
  tagMIXERCONTROLA mxc;
  unsigned int jj;
  tagMIXERLINECONTROLSA mxlc;
  unsigned int err;
  HMIXER__ *phmx;
  unsigned int ii;
  tagMIXERLINEA mixerline;
  tMIXERCONTROLDETAILS_UNSIGNED newSetting;
  tMIXERCONTROLDETAILS mxcd;

  if ( waveInGetNumDevs() < 1 || mixerGetNumDevs() < 1 || mixerOpen(&phmx, 0, 0, 0, 0) )
  {
    return 0;
  }

  mixerline.cbStruct = sizeof(mixerline);
  mixerline.dwComponentType = 7;
  if ( mixerGetLineInfoA((HMIXEROBJ)phmx, &mixerline, 3u) )
  {
    return 0;
  }
  jj = mixerline.cConnections;
  for ( ii = 0; ; ++ii )
  {
    if ( ii >= jj )
    {
        mixerClose(phmx);
        return 0;
    }
    mixerline.dwSource = ii;
    if ( !mixerGetLineInfoA((HMIXEROBJ)phmx, &mixerline, 1u) && !Q_stricmp(mixerline.szName, SrcName) )
    {
      break;
    }
  }
  mxlc.cbStruct = sizeof(mxlc);
  mxlc.dwLineID = mixerline.dwLineID;
  mxlc.dwControlID = 0x50030001;
  mxlc.cControls = 1;
  mxlc.cbmxctrl = sizeof(mxc);
  mxlc.pamxctrl = &mxc;
  err = mixerGetLineControlsA((HMIXEROBJ)phmx, &mxlc, 2u);
  if ( err )
  {
    mixerClose(phmx);
    return 0;
  }
  mxcd.cbStruct = sizeof(mxcd);
  mxcd.cChannels = 1;
  mxcd.cbDetails = sizeof(newSetting);
  mxcd.paDetails = &newSetting;
  mxcd.cMultipleItems = 0;
  mxcd.dwControlID = mxc.dwControlID;
  err = mixerGetControlDetailsA((HMIXEROBJ)phmx, &mxcd, 0);
  if ( !err )
  {
    newSetting.dwValue = newLevel;
    mixerSetControlDetails((HMIXEROBJ)phmx, &mxcd, 0);
  }
  mixerClose(phmx);
  return 0;
}

int mixerSetMicrophoneMute(unsigned char bMute)
{
  tagMIXERCONTROLA mxc;
  unsigned int jj;
  tagMIXERLINECONTROLSA mxlc;
  unsigned int err;
  HMIXER__ *phmx;
  unsigned int ii;
  tagMIXERLINEA mixerline;
  tMIXERCONTROLDETAILS_BOOLEAN newSetting;
  tMIXERCONTROLDETAILS mxcd;

  if ( waveInGetNumDevs() < 1 || mixerGetNumDevs() < 1 || mixerOpen(&phmx, 0, 0, 0, 0) )
  {
    return 0;
  }

  mixerline.cbStruct = sizeof(mixerline);
  mixerline.dwComponentType = 4;
  err = mixerGetLineInfoA((HMIXEROBJ)phmx, &mixerline, 3u);
  if ( !err )
  {
    jj = mixerline.cConnections;
    for ( ii = 0; ii < jj; ++ii )
    {
      mixerline.dwSource = ii;
      mixerGetLineInfoA((HMIXEROBJ)phmx, &mixerline, 1u);
      if ( !Q_stricmp(mixerline.szName, old_rec_source) )
      {
        mxlc.cbStruct = sizeof(mxlc);
        mxlc.dwLineID = mixerline.dwLineID;
        mxlc.dwControlID = 0x20010002;
        mxlc.cControls = 1;
        mxlc.cbmxctrl = sizeof(mxc);
        mxlc.pamxctrl = &mxc;
        err = mixerGetLineControlsA((HMIXEROBJ)phmx, &mxlc, 2u);
        if ( !err )
        {
          mxcd.cbStruct = sizeof(mxcd);
          mxcd.cChannels = 1;
          mxcd.cbDetails = sizeof(newSetting);
          mxcd.paDetails = &newSetting;
          mxcd.cMultipleItems = 0;
          mxcd.dwControlID = mxc.dwControlID;
          err = mixerGetControlDetailsA((HMIXEROBJ)phmx, &mxcd, 0);
          if ( !err )
          {
            newSetting.fValue = bMute;
            err = mixerSetControlDetails((HMIXEROBJ)phmx, &mxcd, 0);
          }
        }
        break;
      }
    }
  }
  mixerClose(phmx);
  return 0;
}


int mixerSetRecordSource(char *SrcName)
{
  int jj;
  tagMIXERLINECONTROLSA mxlc;
  unsigned int err;
  int iNumChannels;
  int iMultipleItems;
  HMIXER__ *phmx;
  tMIXERCONTROLDETAILS_BOOLEAN *lpListBool;
  int ii;
  tagMIXERCONTROLDETAILS_LISTTEXTA *lpListText;
  tagMIXERLINEA mixerline;
  tMIXERCONTROLDETAILS mxcd;
  tagMIXERCONTROLA *lpmxc;

  if ( waveInGetNumDevs() < 1 || mixerGetNumDevs() < 1 || mixerOpen(&phmx, 0, 0, 0, 0) )
  {
    return 0;
  }

  lpmxc = 0;
  lpListText = 0;
  lpListBool = 0;
  mixerline.cbStruct = sizeof(mixerline);
  mixerline.dwComponentType = 7;
  mixerGetLineInfoA((HMIXEROBJ)phmx, &mixerline, 3u);
  lpmxc = (tagMIXERCONTROLA *)calloc(sizeof(tagMIXERCONTROLA) * mixerline.cControls, 1u);
  mxlc.cbStruct = sizeof(mxlc);
  mxlc.dwLineID = mixerline.dwLineID;
  mxlc.dwControlID = 0;
  mxlc.cControls = mixerline.cControls;
  mxlc.cbmxctrl = sizeof(*lpmxc);
  mxlc.pamxctrl = lpmxc;
  err = mixerGetLineControlsA((HMIXEROBJ)phmx, &mxlc, 0);
  if ( !err )
  {
    for ( ii = 0; ii < (signed int)mixerline.cControls; ++ii )
    {
      if ( (lpmxc[ii].dwControlType & 0xF0000000) == 0x70000000 )
      {
        iNumChannels = mixerline.cChannels;
        iMultipleItems = 0;
        if ( lpmxc[ii].fdwControl & 1 )
        {
          iNumChannels = 1;
        }
        if ( lpmxc[ii].fdwControl & 2 )
        {
          iMultipleItems = lpmxc[ii].cMultipleItems;
        }
        lpListText = (tagMIXERCONTROLDETAILS_LISTTEXTA *)calloc(sizeof(tagMIXERCONTROLDETAILS_LISTTEXTA) * iMultipleItems * iNumChannels, 1u);
        mxcd.cbStruct = sizeof(mxcd);
        mxcd.dwControlID = lpmxc[ii].dwControlID;
        mxcd.cChannels = iNumChannels;
        mxcd.cMultipleItems = iMultipleItems;
        mxcd.cbDetails = sizeof(*lpListText);
        mxcd.paDetails = lpListText;
        err = mixerGetControlDetailsA((HMIXEROBJ)phmx, &mxcd, 1u);
        if ( !err )
        {
          lpListBool = (tMIXERCONTROLDETAILS_BOOLEAN *)calloc(sizeof(tMIXERCONTROLDETAILS_BOOLEAN) * iMultipleItems * iNumChannels, 1u);
          mxcd.cbDetails = sizeof(*lpListBool);
          mxcd.paDetails = lpListBool;
          err = mixerGetControlDetailsA((HMIXEROBJ)phmx, &mxcd, 0);
          if ( !err )
          {
            for ( jj = 0; jj < iMultipleItems; ++jj )
            {
              if ( Q_stricmp(lpListText[jj].szName, SrcName) )
              {
                lpListBool[jj].fValue = 0;
              }
              else
              {
                lpListBool[jj].fValue = 1;
              }
            }
            err = mixerSetControlDetails((HMIXEROBJ)phmx, &mxcd, 0);
            if ( lpmxc )
            {
              free(lpmxc);
            }
            lpmxc = 0;
            if ( lpListText )
            {
              free(lpListText);
            }
            lpListText = 0;
            if ( lpListBool )
            {
              free(lpListBool);
            }
            lpListBool = 0;
            if ( !err )
            {
              return 1;
            }
          }
        }
      }
    }
  }
  if ( lpmxc )
  {
    free(lpmxc);
  }
  lpmxc = 0;
  if ( lpListText )
  {
    free(lpListText);
  }
  lpListText = 0;
  if ( lpListBool )
  {
    free(lpListBool);
  }
  return 0;
}



int mixerGetRecordSource(char *srcName)
{
  int jj;
  tagMIXERLINECONTROLSA mxlc;
  unsigned int err;
  int iNumChannels;
  int iMultipleItems;
  HMIXER__ *phmx;
  tMIXERCONTROLDETAILS_BOOLEAN *lpListBool;
  int ii;
  tagMIXERCONTROLDETAILS_LISTTEXTA *lpListText;
  tagMIXERLINEA mixerline;
  tMIXERCONTROLDETAILS mxcd;
  tagMIXERCONTROLA *lpmxc;

  if ( waveInGetNumDevs() < 1 || mixerGetNumDevs() < 1 || mixerOpen(&phmx, 0, 0, 0, 0) )
  {
    return 0;
  }

  lpmxc = 0;
  lpListText = 0;
  lpListBool = 0;
  mixerline.cbStruct = sizeof(mixerline);
  mixerline.dwComponentType = 7;
  mixerGetLineInfoA((HMIXEROBJ)phmx, &mixerline, 3u);
  lpmxc = (tagMIXERCONTROLA *)calloc(sizeof(tagMIXERCONTROLA) * mixerline.cControls, 1u);
  mxlc.cbStruct = sizeof(mxlc);
  mxlc.dwLineID = mixerline.dwLineID;
  mxlc.dwControlID = 0;
  mxlc.cControls = mixerline.cControls;
  mxlc.cbmxctrl = sizeof(*lpmxc);
  mxlc.pamxctrl = lpmxc;
  err = mixerGetLineControlsA((HMIXEROBJ)phmx, &mxlc, 0);
  if ( !err )
  {
    for ( ii = 0; ii < (signed int)mixerline.cControls; ++ii )
    {
      if ( (lpmxc[ii].dwControlType & 0xF0000000) == 0x70000000 )
      {
        iNumChannels = mixerline.cChannels;
        iMultipleItems = 0;
        if ( lpmxc[ii].fdwControl & 1 )
        {
          iNumChannels = 1;
        }
        if ( lpmxc[ii].fdwControl & 2 )
        {
          iMultipleItems = lpmxc[ii].cMultipleItems;
        }
        lpListText = (tagMIXERCONTROLDETAILS_LISTTEXTA *)calloc(sizeof(tagMIXERCONTROLDETAILS_LISTTEXTA) * iMultipleItems * iNumChannels, 1u);
        mxcd.cbStruct = sizeof(mxcd);
        mxcd.dwControlID = lpmxc[ii].dwControlID;
        mxcd.cChannels = iNumChannels;
        mxcd.cMultipleItems = iMultipleItems;
        mxcd.cbDetails = sizeof(*lpListText);
        mxcd.paDetails = lpListText;
        err = mixerGetControlDetailsA((HMIXEROBJ)phmx, &mxcd, 1u);
        if ( !err )
        {
          lpListBool = (tMIXERCONTROLDETAILS_BOOLEAN *)calloc(sizeof(tMIXERCONTROLDETAILS_BOOLEAN) * iMultipleItems * iNumChannels, 1u);
          mxcd.cbDetails = sizeof(*lpListBool);
          mxcd.paDetails = lpListBool;
          err = mixerGetControlDetailsA((HMIXEROBJ)phmx, &mxcd, 0);
          if ( !err )
          {
            for ( jj = 0; jj < iMultipleItems; ++jj )
            {
              if ( lpListBool[jj].fValue == 1 )
              {
                strncpy(srcName, lpListText[jj].szName, 0xFFu);
              }
            }
            if ( lpmxc )
            {
              free(lpmxc);
            }
            lpmxc = 0;
            if ( lpListText )
            {
              free(lpListText);
            }
            lpListText = 0;
            if ( lpListBool )
            {
              free(lpListBool);
            }
            lpListBool = 0;
            if ( !err )
            {
              return 1;
            }
          }
        }
      }
    }
  }
  if ( lpmxc )
  {
    free(lpmxc);
  }
  lpmxc = 0;
  if ( lpListText )
  {
    free(lpListText);
  }
  lpListText = 0;
  if ( lpListBool )
  {
    free(lpListBool);
  }
  return 0;
}