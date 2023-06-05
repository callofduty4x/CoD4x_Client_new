#include "../q_shared.h"
#include "qcommon.h"

#define CMD_MAX_NESTING 8

struct CmdArgs
{
  int nesting;
  int localClientNum[8];
  int controllerIndex[8];
  int argc[CMD_MAX_NESTING];
  const char **argv[CMD_MAX_NESTING];
};

extern CmdArgs cmd_args;
extern cmd_function_s *cmd_functions;

CmdArgs* Cmd_Args()
{
    return &cmd_args;
}

const char * Cmd_Argv(int argIndex)
{
  CmdArgs *cmd_args;

  cmd_args = Cmd_Args();

  assertx(cmd_args->nesting < CMD_MAX_NESTING, "cmd_args->nesting doesn't index CMD_MAX_NESTING\n\t%i not in [0, %i)", cmd_args->nesting, CMD_MAX_NESTING);
  assertx(argIndex >= 0, "(argIndex) = %i", argIndex);

  if ( argIndex >= cmd_args->argc[cmd_args->nesting] )
  {
    return "";
  }
  return cmd_args->argv[cmd_args->nesting][argIndex];
}

int Cmd_Argc()
{
  CmdArgs *cmd_args;

  cmd_args = Cmd_Args();
  assert(cmd_args->nesting < CMD_MAX_NESTING);
  return cmd_args->argc[cmd_args->nesting];
}

cmd_function_s *Cmd_FindCommand(const char *cmdName)
{
  cmd_function_s *cmd;
  for ( cmd = cmd_functions; cmd; cmd = cmd->next )
  {
    if ( !strcmp(cmdName, cmd->name) )
    {
      return cmd;
    }
  }
  return NULL;
}

void Cmd_AddCommandInternal(const char *cmdName, void (*function)(), cmd_function_s *allocedCmd)
{
  cmd_function_s *cmd;

  assert(cmdName);
  cmd = Cmd_FindCommand(cmdName);
  if ( cmd )
  {
    assert(cmd == allocedCmd);
    if ( function )
    {
      Com_Printf(CON_CHANNEL_SYSTEM, "Cmd_AddCommand: %s already defined\n", cmdName);
    }
  }
  else
  {
    allocedCmd->name = cmdName;
    allocedCmd->function = function;
    allocedCmd->next = cmd_functions;
    //allocedCmd->consoleAccess = 0;
    cmd_functions = allocedCmd;
  }

}


void Cmd_ForEachConsoleAccessName(void (*callback)(const char *))
{
  cmd_function_s *cmd;

  if ( Dvar_GetBool("con_restricted_access") )
  {
    for ( cmd = cmd_functions; cmd; cmd = cmd->next )
    {
      /*
      if ( cmd->consoleAccess )
      {
        callback(cmd->name);
      }*/
    }
  }
  else
  {
    Cmd_ForEach(callback);
  }
}

bool Cmd_AssertNestingIsReset()
{
  return Cmd_Args()->nesting == -1;
}