#ifndef STICKMANSTATE
#define STICKMANSTATE

class StickmanState
{
public:
    virtual ~StickmanState();
    virtual void handleStickman(StickmanAdapter *stickman) = 0;
    virtual void update(StickmanAdapter *stickman) = 0;
};

#endif // STICKMANSTATE

