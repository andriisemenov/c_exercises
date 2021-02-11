/* 
*
* Author: Andrii Semenov
* Used as module. hysteresis.h consists of "extern unsigned int hysteresis(unsigned int input_percent);"
* Using math instead of hard-defined start/stop array of the levels for scalability, different amout of levels and signal resolutions.
* The idea is to calculate the offset to the first critical section and substract this point(10) from the signal.
* Then the base level is calculated. If the signal is higher then the hysteresis + base_level, then level = base_level+1;
* There is comparison made with previous output to stabilize changes in critical (swing areas). 
*
*/

#include "hysteresis.h"
#include <assert.h>

#define HYSTERESIS  5u

#define LEVELS  4u
#define MAX_INPUT 100u
#define SCALE 8u
#define SUB_LEVELS  ( LEVELS * 2u )
#define HYSTERESIS_SCALED (HYSTERESIS<<SCALE)
#define MAX_INPUT_SCALED ( MAX_INPUT << SCALE )
#define INP_PER_LEVEL ( MAX_INPUT_SCALED / LEVELS )
#define HYSTERESIS_SCALED_HALF  ( HYSTERESIS_SCALED/ 2u )

#define OFFSET_SCALED  ( (MAX_INPUT_SCALED / SUB_LEVELS) - HYSTERESIS_SCALED_HALF)

static unsigned int ui_prevInput = 0u;
static unsigned int ui_prevOutput = 0u;

unsigned int hysteresis( unsigned int input_percent )
{
    /*Only numbers from 0 to MAX_INPUT are accepted*/
    assert(input_percent <= MAX_INPUT);

    unsigned int ui_level = 0u;
    unsigned int input_percent_scaled = 0u;
    
    input_percent_scaled = input_percent << SCALE;

    /*Prevent wrapping*/
    if( input_percent_scaled >= OFFSET_SCALED )
    {
        input_percent_scaled = input_percent_scaled - OFFSET_SCALED;
    }
    else
    {
        input_percent_scaled = 0;
    }

    unsigned int ui_baseLevel = (input_percent_scaled / INP_PER_LEVEL);

    if( ui_prevInput < input_percent )
    {
        /*Ascending*/
        if( input_percent_scaled < ( ui_baseLevel * INP_PER_LEVEL + HYSTERESIS_SCALED ) )
        {
            /*Within the boundary, use level*/
            if(ui_prevOutput > ui_baseLevel)
            {
                /*Unless we were already higher then the higher boundary, then output previous level
                *
                * Otherwise:    Input 13 Output 0 
                                Input 15 Output 1 
                                Input 11 Output 1 
                                Input 13 Output 0 
                * 
                */
                ui_level = ui_prevOutput;
            }
            else
            {
                ui_level = ui_baseLevel;
            }
        }
        else
        {
            /*more than hysteresis for this level, level+1*/
            ui_level = ui_baseLevel + 1;
        }
    }
    else if( ui_prevInput > input_percent ){
        /*Descending*/
        if( input_percent_scaled < ( ui_baseLevel * INP_PER_LEVEL + HYSTERESIS_SCALED ) )
        {
            /*Exclude start of critical area on descend*/
            if( input_percent_scaled != ( ui_baseLevel * INP_PER_LEVEL ) && ui_prevOutput != ui_baseLevel )
            {
                ui_level = ui_baseLevel + 1;
            }
            else
            {
                ui_level = ui_baseLevel;
            }
        }
        else
        {
            ui_level = ui_baseLevel + 1;
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