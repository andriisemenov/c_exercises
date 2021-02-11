/* 
*
* Author: Andrii Semenov
* Used as module. hysteresis.h consists of "extern unsigned int hysteresis(unsigned int input_percent);"
* Using math instead of hard-defined start/stop array of the levels for scalability.
* The idea is to calculate mid points of the critical regions (10-15->12.5, 35-40->37.5, etc.) 
* and use half of hysteresis to offset the sublevel output.
* Sublevels are (2 * levels).
* Then sublevels are converted to levels by dividing by 2.
* Finally, we save historical data: previous input as well as previous output.
* The previous output is needed when prev_input=input in order to calculate the level for critical 
* (swing) areas (10-15, 35-40, etc.)
* 
*/

#include "hysteresis.h"
#include <assert.h>

#define HYSTERESIS  5u

#define LEVELS  4u
#define MAX_INPUT 100u
#define SCALE 8u
#define SUB_LEVELS  ( LEVELS * 2u )
#define MAX_INPUT_SCALED ( MAX_INPUT << SCALE )
#define INP_PER_SUBLEVEL ( MAX_INPUT_SCALED / SUB_LEVELS )
#define HYSTERESIS_SCALED_HALF  (( HYSTERESIS << SCALE ) / 2u )

static unsigned int ui_prevInput = 0u;
static unsigned int ui_prevOutput = 0u;

unsigned int hysteresis( unsigned int input_percent )
{
    /*Only numbers from 0 to MAX_INPUT are accepted*/
    assert(input_percent <= MAX_INPUT);

    unsigned int ui_level = 0u;
    unsigned int input_percent_scaled = 0u;
    
    input_percent_scaled = input_percent << SCALE;

    /*Checking if input is decreasing/increasing, calculating sub-level*/
    if( ui_prevInput < input_percent )
    {
        /* Input is increasing */
        /*Prevent wrapping during calculation*/
        if( input_percent_scaled > HYSTERESIS_SCALED_HALF )
        {
            ui_level = ( input_percent_scaled - HYSTERESIS_SCALED_HALF ) / INP_PER_SUBLEVEL;
            /* Converting sub level to level */
            ui_level = (ui_level + 1u) >> 1u;
            
        }
        else
        {
            ui_level = 0u;
        }
    }
    else if( ui_prevInput > input_percent )
    {
        /* Input is decreasing */
        input_percent_scaled = (input_percent - 1u) << SCALE;
        ui_level = ( input_percent_scaled + HYSTERESIS_SCALED_HALF ) / INP_PER_SUBLEVEL;
        /* Converting sub level to level */
        ui_level = (ui_level + 1u) >> 1u;
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