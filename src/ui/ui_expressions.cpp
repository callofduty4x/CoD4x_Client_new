#include <ctype.h>
#include "../q_shared.h"
#include "../common/stringed_public.h"

#define NUM_SCREENS 1

union operandInternalDataUnion
{
  int intVal;
  float floatVal;
  const char *string;
};

enum expDataType
{
  VAL_INT = 0x0,
  VAL_FLOAT = 0x1,
  VAL_STRING = 0x2
};


struct Operand
{
  expDataType dataType;
  operandInternalDataUnion internals;
};

struct OperandList
{
  Operand operands[10];
  int operandCount;
};

#define NUM_OPERAND_STRINGS 16

extern char s_tempOperandValueAsString[NUM_OPERAND_STRINGS][256];
extern unsigned int currentTempOperand;

const char* GetSourceString(Operand operand)
{
    char *result;

    if ( operand.dataType == VAL_STRING )
    {
        return operand.internals.string;
    }
    assert(currentTempOperand < NUM_OPERAND_STRINGS);

    result = s_tempOperandValueAsString[currentTempOperand];
    currentTempOperand = (currentTempOperand + 1) % NUM_OPERAND_STRINGS;
    if ( operand.dataType )
    {
        if ( operand.dataType == VAL_FLOAT )
        {
            Com_sprintf(result, sizeof(s_tempOperandValueAsString[0]), "%f", operand.internals.floatVal);
        }
    }
    else
    {
        I_itoa(operand.internals.intVal, result, sizeof(s_tempOperandValueAsString[0]));
    }
    return result;
}

void LocalizationError(const char *errorMessage)
{
    if ( Dvar_GetBool("loc_warnings") )
    {
        assert(errorMessage);

        if ( Dvar_GetBool("loc_warningsAsErrors") )
        {
            Com_Error(ERR_LOCALIZATION, "Error: %s", errorMessage);
        }
        else
        {
            Com_PrintWarning(CON_CHANNEL_UI, "WARNING: %s\n", errorMessage);
        }
    }
}


void ValidateLocalizedStringRef(const char *token, int tokenLen)
{
    signed int charIter;
    char errmsg[1024];

    assert(token);
    assert(tokenLen > 0);

    for ( charIter = 1; charIter < tokenLen; ++charIter )
    {
        if ( !isalnum(token[charIter]) && token[charIter] != '_' )
        {
            Com_sprintf(errmsg, sizeof(errmsg), "Illegal localized string reference: %s must contain only alpha-numeric characters and underscores", token);
            LocalizationError(errmsg);
        }
    }
}


/*
//Not supported due to unavailablity of "s_currentStatement" in CoD4

void Expression_Error(const char *str, ...)
{
    char buf[1024];
    int offset;
    va_list va;

    va_start(va, str);
    if ( !Expression_Throttle() )
    {
        _snprintf(buf, 0x400u, "^1Expression Error (%s:%d): ", s_currentStatement->filename, s_currentStatement->line);
        offset = &buf[strlen(buf) + 1] - &buf[1];
        _vsnprintf(&buf[offset], 0x400u, str, va);
        buf[1023] = 0;
        EmptyStub();
        Com_PrintMessage(CON_CHANNEL_SYSTEM, buf, 3);
    }
}
*/



//REGPARM(3)
//;LocalizeString(OperandList*, Operand*)

void LocalizeString(OperandList* list, Operand *operandResult)
{
    char string[1024];
    //bool useLocalization;
    Operand *operand;
    unsigned int charIndex;
    unsigned int tokenLen;
    //bool enableLocalization;
    expDataType type;
    int parmIndex;
    const char *token;
    unsigned int stringLen;
    char errmsg[1024];

    //useLocalization = 1;
    stringLen = 0;
    for ( parmIndex = 0; parmIndex < list->operandCount; ++parmIndex )
    {
        operand = &list->operands[parmIndex];
        type = list->operands[parmIndex].dataType;
        //enableLocalization = 0;
        if ( type == VAL_STRING )
        {
            token = GetSourceString(*operand);
            tokenLen = strlen(token);
            if ( tokenLen <= 1 )
            {
                continue;
            }
            ValidateLocalizedStringRef(token, tokenLen);
            if ( *token == '@' )
            {
                ++token;
                --tokenLen;
            }
            if ( stringLen + tokenLen + 1 >= sizeof(string) )
            {
                Com_Error(ERR_LOCALIZATION, "Error: %s is too long. Max length is %i\n", token, sizeof(string));
            }
            if ( stringLen )
            {
                string[stringLen++] = 20;
            }
            //useLocalization = true;
        }
        else
        {
            token = GetSourceString(*operand);
            tokenLen = strlen(token);
            for ( charIndex = 0; charIndex < tokenLen; ++charIndex )
            {
                if ( token[charIndex] == 20 || token[charIndex] == 21 || token[charIndex] == 22 )
                {
                    Com_PrintError(CON_CHANNEL_UI, "bad escape character (%i) present in string", token[charIndex]);
                }
                if ( isalpha(token[charIndex]) )
                {
                    Com_sprintf(errmsg, sizeof(errmsg), "Non-localized UI strings are not allowed to have letters in them: \"%s\"", token);
                    LocalizationError(errmsg);
                    break;
                }
            }
            if ( stringLen + tokenLen + 1 >= sizeof(string) )
            {
                Com_Error(ERR_LOCALIZATION, "Error: %s is too long. Max length is %i\n", token, sizeof(string));
            }
            if ( tokenLen )
            {
                string[stringLen++] = 21;
            }
            //useLocalization = false;
        }
        for ( charIndex = 0; charIndex < tokenLen; ++charIndex )
        {
            if ( token[charIndex] != 20 && token[charIndex] != 21 && token[charIndex] != 22 )
            {
                string[stringLen] = token[charIndex];
            }
            else
            {
                string[stringLen] = '.';
            }
            ++stringLen;
        }
    }
    string[stringLen] = 0;
    operandResult->dataType = VAL_STRING;
    operandResult->internals.string = SEH_LocalizeTextMessage(string, "ui string", LOCMSG_NOERR);
    if ( !operandResult->internals.string )
    {
        operandResult->internals.string = "";
    }
}
