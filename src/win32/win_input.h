void IN_Shutdown( void );
void IN_Init( void );
void IN_Activate(qboolean active);
void IN_RawMouseInit();
void IN_ActivateMouse( qboolean force );
void IN_RecenterMouse( void );
void IN_MouseEvent( int mstate );
void IN_RawEvent(LPARAM lParam);
void IN_Frame();
