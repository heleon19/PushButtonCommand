#include <stdint.h>
#include <Arduino.h>

#include "pushbuttoncommand.h"

#define _STEP_START                         0
#define _STEP_FIRST_RISING_EDGE             1
#define _STEP_WAIT_FOR_LONG_PUSH_END        2
#define _STEP_WAIT_FOR_SECOND_RISING_EDGE   3
#define _STEP_WAIT_FOR_SECOND_FALLING_EDGE  4
#define _STEP_END                           5


PushButtonCommand::PushButtonCommand() 
{
}

void PushButtonCommand::setup(uint8_t length, uint8_t debounce, uint8_t doublclick, uint16_t longpush)
{
    if(_sequences != 0)
    {
        delete [] _sequences;
    }
    _sequences = new uint8_t [length];
    
    if(_counters != 0)
    {
        delete [] _counters;
    }
    _counters = new uint16_t [length];
    
    _debounce = debounce;
    _doublclick = doublclick;
    _longpush = longpush;
}

uint8_t PushButtonCommand::loop(uint8_t index, boolean input)
{
    /* Reset counter if not equal last value */
    if(getLastValue(index) != input)
    {
        setLastValue(index, input);
        _counters[index] = 0;
    }
    
    switch(_sequences[index])
    {
        case _STEP_START:
        {
            if(input && _counters[index]++ == _debounce)
            {
                _sequences[index] = _STEP_FIRST_RISING_EDGE;
            }
            break;
        }
        
        case _STEP_FIRST_RISING_EDGE:
        {
            if(input && _counters[index]++ == _longpush)
            {
                _sequences[index] = _STEP_WAIT_FOR_LONG_PUSH_END;
                return PUSH_CMD_LONGPUSH;
            }
            else if(!input && _counters[index]++ == _debounce)
            {
                _sequences[index] = _STEP_WAIT_FOR_SECOND_RISING_EDGE;
            }
            break;
        }
        
        case _STEP_WAIT_FOR_LONG_PUSH_END:
        {
            if(input)
            {
                return PUSH_CMD_LONGPUSH;
            }
            else if(_counters[index]++ == _debounce)
            {
                _sequences[index] = _STEP_END;
                return PUSH_CMD_NONE;
            }
            break;
        }
        
        case _STEP_WAIT_FOR_SECOND_RISING_EDGE:
        {
            if(input && _counters[index]++ == _debounce)
            {
                _sequences[index] = _STEP_WAIT_FOR_SECOND_FALLING_EDGE;
            }
            else if(!input && _counters[index]++ == _doublclick)
            {
                _sequences[index] = _STEP_END;
                return PUSH_CMD_CLICK;
            }
            break;
        }
        
        case _STEP_WAIT_FOR_SECOND_FALLING_EDGE:
        {
            if(!input && _counters[index]++ == _debounce)
            {
                _sequences[index] = _STEP_END;
                return PUSH_CMD_DOUBLE_CLICK;
            }
            break;
        }
        
        case _STEP_END:
        default:
        {
            _sequences[index] = _STEP_START;
            _counters[index] = 0;
            break;
        }
    }
    
    return PUSH_CMD_NONE;
}

boolean PushButtonCommand::getLastValue(uint8_t index) {
    return (_lastValue & (1 << index));
}

void PushButtonCommand::setLastValue(uint8_t index, boolean value) {
    if(value)
    {
        _lastValue |= (1 << index);
    }
    else
    {
        _lastValue &= ~(1 << index);
    }
}
