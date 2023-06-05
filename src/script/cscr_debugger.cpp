bool Scr_IgnoreErrors( )
{
  return true;
  //return gScrDebuggerGlob.disableBreakpoints;
}

void Scr_InitDebuggerSystem()
{
    /*
  if ( gScrVarPub[inst].developer )
  {
    if ( gScrDebuggerGlob[inst].debugger_inited_system
      && !Assert_MyHandler("C:\\projects_pc\\cod\\codsrc\\src\\clientscript\\cscr_debugger.cpp", 7828, 0, "%s", "!gScrDebuggerGlob[inst].debugger_inited_system") )
    {
      __debugbreak();
    }
    Scr_InitBreakpoints();
    gScrDebuggerGlob[inst].nextBreakpointCodePos = 0;
    gScrDebuggerGlob[inst].killThreadCodePos = 0;
    gScrDebuggerGlob[inst].breakpointCount = 0;
    if ( gScrVarPub[inst].evaluate && !Assert_MyHandler("C:\\projects_pc\\cod\\codsrc\\src\\clientscript\\cscr_debugger.cpp", 7843, 0, "%s", "!gScrVarPub[inst].evaluate") )
    {
      __debugbreak();
    }
    gScrVarPub[inst].evaluate = 1;
    gScrDebuggerGlob[inst].assignBreakpointSet = 0;
    gScrDebuggerGlob[inst].breakpointPos.bufferIndex = -1;
    gScrDebuggerGlob[inst].atBreakpoint = 0;
    gScrDebuggerGlob[inst].run_debugger = 0;
    Scr_ScriptWatch::Init(&gScrDebuggerGlob[inst].scriptWatch, inst);
    if ( !gScrVarPub[inst].evaluate && !Assert_MyHandler("C:\\projects_pc\\cod\\codsrc\\src\\clientscript\\cscr_debugger.cpp", 7868, 0, "%s", "gScrVarPub[inst].evaluate") )
    {
      __debugbreak();
    }
    gScrVarPub[inst].evaluate = 0;
    gScrDebuggerGlob[inst].debugger_inited_system = 1;
    if ( Sys_IsRemoteDebugServer() && (Scr_SendSource(inst), Sys_IsRemoteDebugServer()) )
    {
      Scr_RunDebugger(inst);
    }
    else
    {
      Scr_ScriptWatch::UpdateBreakpoints(&gScrDebuggerGlob[inst].scriptWatch, inst, 1);
    }
  }*/
}

void Scr_InitDebuggerMain( )
{
    /*
  if ( gScrVarPub[inst].developer )
  {
    if ( *((_BYTE *)&(&gScrDebuggerGlob)[113 * inst] + 424) )
    {
      if ( !Assert_MyHandler("C:\\projects_pc\\cod\\codsrc\\src\\clientscript\\cscr_debugger.cpp", 7679, 0, "%s", "!gScrDebuggerGlob[inst].debugger_inited_main") )
      {
        __debugbreak();
      }
    }
    *(&(&gScrDebuggerGlob)[113 * inst] + 105) = (struct scrDebuggerGlob_t *)Hunk_UserAlloc(g_DebugHunkUser, 1179640, 4, "gScrDebuggerGlob[inst].variableBreakpoints");
    memset((char *)*(&(&gScrDebuggerGlob)[113 * inst] + 105), 0, 0x11FFF8u);
    *(&(&gScrDebuggerGlob)[113 * inst] + 100) = 0;
    *(&(&gScrDebuggerGlob)[113 * inst] + 101) = 0;
    if ( inst )
    {
      *((_BYTE *)&(&gScrDebuggerGlob)[113 * inst] + 440) = 1;
    }
    else
    {
      *((_BYTE *)&gScrDebuggerGlob + 440) = 0;
    }
    *((_BYTE *)&(&gScrDebuggerGlob)[113 * inst] + 424) = 1;
  }*/
}


void Scr_AddAssignmentPos(char *codePos)
{/*
  Scr_OpcodeList_s *opcodeElement;
  
  assert(gScrVarPub.developer);

  if ( gScrCompilePub.developer_statement != 2 && gScrDebuggerGlob.assignHeadCodePos != codePos )
  {
    gScrDebuggerGlob.assignHeadCodePos = codePos;
    opcodeElement = (Scr_OpcodeList_s *)Hunk_UserAlloc(g_DebugHunkUser, sizeof(Scr_OpcodeList_s), 4, "Scr_AddAssignmentPos");
    opcodeElement->codePos = codePos;
    opcodeElement->next = gScrDebuggerGlob.assignHead;
    gScrDebuggerGlob.assignHead = opcodeElement;
  }*/
}

void EmitPreAssignmentPos( )
{/*
  if ( gScrVarPub.developer && gScrCompilePub.developer_statement != 3 )
  {
    Scr_AddAssignmentPos(gScrCompilePub.opcodePos);
  }*/
}

void Scr_ResetAbortDebugger()
{
  //scrDebuggerGlob.abort = 0;
}