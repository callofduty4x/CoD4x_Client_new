void IN_Shutdown( void );
void IN_Init( void );
void IN_Activate(qboolean active);
void IN_RawMouseInit();
void IN_ActivateMouse( qboolean force );
void IN_RecenterMouse( void );
void IN_MouseEvent( int mstate );
void IN_Frame();
#ifdef _WINDOWS_H
    void IN_RawEvent(LPARAM lParam);
#endif