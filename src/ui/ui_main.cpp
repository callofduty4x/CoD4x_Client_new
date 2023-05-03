#include <ctype.h>
#include "../q_shared.h"
#include "../common/stringed_public.h"
#include "../common/sys_shared.h"

struct ConversionArguments
{
  int argCount;
  const char *args[9];
};

void UI_FilterStringForButtonAnimation(char *str, unsigned int strMaxSize)
{
#pragma msg "Maybe empty this? This is empty in CoD4"

    unsigned int idx;

    if ( SEH_GetCurrentLanguage() != 10 && (signed int)Sys_Milliseconds() % 1000 > 800 )
    {
        for ( idx = 0; str[idx] && idx < strMaxSize; ++idx )
        {
            if ( str[idx] == 16 )
            {
                str[idx] = 0xBCu;
            }
            else if ( str[idx] == 17 )
            {
                str[idx] = 0xBDu;
            }
        }
    }
}
void UI_ReplaceConversions(const char *sourceString, ConversionArguments *arguments, char *outputString, int outputStringSize)
{
    signed int len;
    int argIndex;
    int argStringIndex;
    int index;
    int outputStringCounter;
    int sourceStringLength;

    assert(outputString);

    if ( outputString )
    {
        assert(outputStringSize >= 0);
        if ( outputStringSize >= 0 )
        {
            memset(outputString, 0, outputStringSize);
            outputStringCounter = 0;
            assert(sourceString);
            if ( sourceString )
            {
                if ( strstr((char *)sourceString, "&&") )
                {
                    assert(arguments);
                    if ( arguments )
                    {
                        assert(arguments->argCount <= 9);
                        if ( arguments->argCount <= 9 )
                        {
                            sourceStringLength = strlen(sourceString);
                            assert(sourceStringLength > 0);
                            if ( sourceStringLength > 0 )
                            {
                                index = 0;
                                while ( index < sourceStringLength )
                                {
                                    if ( !strncmp(&sourceString[index], "&&", 2u) && isdigit(sourceString[index + 2]) )
                                    {
                                        argIndex = sourceString[index + 2] - '1';
                                        assert(argIndex >= 0 && argIndex < arguments->argCount);
                                        if ( argIndex < 0 )
                                        {
                                            return;
                                        }
                                        if ( argIndex >= arguments->argCount )
                                        {
                                            return;
                                        }
                                        assert(argIndex < 9);
                                        if ( argIndex >= 9 )
                                        {
                                            return;
                                        }
                                        assert(arguments->args[argIndex]);
                                        if ( !arguments->args[argIndex] )
                                        {
                                            return;
                                        }
                                        len = strlen(arguments->args[argIndex]);
                                        for ( argStringIndex = 0; argStringIndex < len; ++argStringIndex )
                                        {
                                            outputString[outputStringCounter++] = arguments->args[argIndex][argStringIndex];
                                        }
                                        index += 3;
                                    }
                                    else
                                    {
                                        outputString[outputStringCounter++] = sourceString[index++];
                                    }
                                }
                                UI_FilterStringForButtonAnimation(outputString, outputStringSize);
                            }
                        }
                    }
                }
                else
                {
                    Q_strncpyz(outputString, sourceString, outputStringSize);
                }
            }
        }
    }
}