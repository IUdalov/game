#include "../physics/physics.h"
#include "../INDIan/core_includes.h"
#include "../inits/declarations.h"

struct AiChecker {
    PhChecker phChecker;
    CheckersType type;
    INDIan::IDn id;
};

inline bool operator==(const AiChecker &a, const AiChecker &b)
{
    return(a.id.id == b.id.id);
}
inline bool operator!=(const AiChecker &a, const AiChecker &b)
{
    return(a.id.id != b.id.id);
}

namespace AI {
    INDIan::IDn MakeStep();
    void Disposal();
    void AddFriend(AiChecker checker);
    void AddEnemy(AiChecker checker);
    void ClearFriends();
    void ClearEnemys();
    void ClearAll();
    void SetFieldRect(INDIan::Rect rect);
    AiChecker* GetFriend(INDIan::IDn id);
    AiChecker* GetEnemy(INDIan::IDn id);
    void SetMaxSpeed(double max);
}


