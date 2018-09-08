#ifndef COMMANDS_H
#define COMMANDS_H

enum CommandsType{ CMD_SET, CMD_GET, CMD_MOVE, CMD_RESULT};
enum AxisesID{ AXIS_X, AXIS_Y, AXIS_Z, AXIS_COUNT};

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
            int mStepsCount;
            int mDirection;
            int mColorR;
            int mColorG;
            int mColorB;
        }cmdMove;

        struct{
            int mDescription;
        }cmdResult;

    }data;
};


#endif // COMMANDS_H
