#ifndef COMMANDS_H
#define COMMANDS_H

#define CMD_SET     1
#define CMD_GET     2
#define CMD_MOVE    3

#define AXIS_X      1
#define AXIS_Y      2
#define AXIS_Z      3

struct Command{
    int mType;
    union{

        struct{
            int mParameter;
            int mValue;
        }cmdSet;

        struct{
            int mParameter;
        }cmdGet;

        struct{
            int mAxisId;
            int mDistance;
            int mColor;
        }cmdMove;

    }data;
};


#endif // COMMANDS_H
