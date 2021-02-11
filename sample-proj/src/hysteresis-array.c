/* 
*
* Author: Andrii Semenov
* Used as module. hysteresis.h consists of "extern unsigned int hysteresis(unsigned int input_percent);"
* Basic idea is to loop through an array and check which level the signal corresponds to. 
* 
*
*/

#include "hysteresis.h"
#include <assert.h>
#include <stdio.h>

#define HYSTERESIS  5u
#define MAX_INPUT 100u

#define LEVELS  4u

#define OFFSET_SCALED  ( (MAX_INPUT_SCALED / SUB_LEVELS) - HYSTERESIS_SCALED_HALF)

static unsigned int ui_prevInput = 0u;
static unsigned int ui_prevOutput = 0u;

static unsigned int ui_lowH[LEVELS]={10u, 35u, 60u, 85u};
static unsigned int ui_highH[LEVELS]={15u, 40u, 65u, 90u};

unsigned int hysteresis( unsigned int input_percent )
{
    /*Only numbers from 0 to MAX_INPUT are accepted*/
    assert(input_percent <= MAX_INPUT);

    unsigned int ui_level = 0u;
    char found = 0u;
    int size = sizeof ui_lowH / sizeof ui_lowH[0];


    if( ui_prevInput < input_percent )
    {
        /*Ascending*/
        /*Loop though ui_highH until lower*/
        for(int i=0; (i<size) && !found; i++)
        {
            if(input_percent >= ui_highH[i] | i<ui_prevOutput)
            {
                ui_level++;
            }
            else
            {
                found = 1u;
            }
        }
    }
    else if( ui_prevInput > input_percent )
    {
        /*Descending*/
        /*Loop though ui_lowH and deduce the level*/
        for(int i=0; (i<size) && !found; i++)
        {
            if(input_percent <= ui_lowH[i] )
            {
                found = 1u;
                if(ui_level>ui_prevOutput)
                {
                    ui_level--;
                }
                if(ui_level>ui_prevOutput || ui_level<0 || ui_level>4)
                {
                    printf("Strange %d %d %d %d\n", ui_prevInput, input_percent, ui_prevOutput, ui_level);
                }
            }
            else
            {
                ui_level++;
            }
        }
    }
    else
    {
        /* When prev_input = input we do not know the output at critical regions.
        *  For example, 12 is level 0 on ascending and 1 on descending.
        *  In order to mitigate this, include historic output.
        *  */
        ui_level = ui_prevOutput;
    }


    /* Saving historical data */
    ui_prevInput = input_percent;
    ui_prevOutput = ui_level;

    return ui_level;
}