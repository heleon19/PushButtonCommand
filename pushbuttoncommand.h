/* Push button command lib to debounce buttons and dedect click, double click and long push
 *
 *
 * Written by Reto Jenni 2016
 * 
 */

#ifndef pushbuttoncommand_h
#define pushbuttoncommand_h

#define PUSH_CMD_NONE           0
#define PUSH_CMD_CLICK          1
#define PUSH_CMD_LONG_PUSH      2
#define PUSH_CMD_DOUBLE_CLICK   3
#define PUSH_CMD_LONG_CLICK     4

class PushButtonCommand
{
public:
    PushButtonCommand();
    void setup(uint8_t length, uint8_t debounce, uint8_t doublclick, uint16_t longpush);
    uint8_t loop(uint8_t index, boolean input);
    
private:
    uint8_t* _sequences;
    uint16_t* _counters;
    uint16_t _lastValue;
    
    uint8_t _length;
    uint8_t _debounce;
    uint8_t _doublclick;
    uint16_t _longpush;
    
    boolean getLastValue(uint8_t index);
    void setLastValue(uint8_t index, boolean value);
};




#endif