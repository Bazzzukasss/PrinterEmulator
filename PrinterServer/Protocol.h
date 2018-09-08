#ifndef COMMANDS_H
#define COMMANDS_H

enum CommandsType{ CMD_SET, CMD_GET_SENSORS, CMD_MOVE};
enum AnswersType{ ANS_RESULT, ANS_SENSORS};
enum AxisesID{ AXIS_X, AXIS_Y, AXIS_Z, AXIS_COUNT};
enum ResultsDescriptors{RES_CMD_ACCEPTED,RES_SERVER_BUSY};

struct Command{
    int mType;
    union{

        struct{
            int mAxisId;
            int mValue;
        }cmdSet;

        struct{
            int mSensorId;
        }cmdGetSensors;

        struct{
            int mAxisId;
            int mStepsCount;
            int mDirection;
            int mColorR;
            int mColorG;
            int mColorB;
        }cmdMove;

    }data;
};

struct Answer{
    int mType;
    union{

        struct{
            int mId;
            int mValue;
        }ansSensors;

        struct{
            int mDescription;
        }ansResult;

    }data;
};

#endif // COMMANDS_H
