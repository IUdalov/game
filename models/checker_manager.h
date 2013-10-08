#ifndef EXAMPLE_MODEL_H
#define EXAMPLE_MODEL_H

#include "../inits/declarations.h"
#include "../INDIan/core_includes.h"
#include "../physics/physics.h"

extern System_ROOT Root;
extern int ScreenWidth;
extern int ScreenHeight;
extern cResources Resources;
extern Obj_Manager ObjManager;

struct ObjChecker{
    double weight;
    dCoord vSpeed;
    int type;
    int master;
};

struct PosManager{
    Coord       pnt[3];
    IDn     checker[3];
    bool       busy[3];
    vector<IDn> big_chs;
    vector<IDn> middle_chs;
    vector<IDn> small_chs;
};
enum PlayersProgress{
    _1st = 0,
    _2nd
};
enum GamePart{
    Disposal = 1,
    Game
};

class CheckerManager : Model_Objects{
public:
    short CheckEnable;
    vector<CObj> arrows;
    IDn CheckChecker;
    Coord point_to;
    bool NeedFlyToPos;

    //++параметры поля
    Rect FieldRect;
    int FieldMiddle;
    //--

    PosManager selector;

    GameParam game_param;

    int game_part;
    int players_progress;

    CheckerManager();
    ~CheckerManager();
    void CreateArrow( CObj& arrow, double x_c, double y_c, double x_l, double y_l, double length );
    virtual void EventsHandler(unsigned int mess, void *data);

    void LocateSelector(void);
    void PrepareForReturn(int type);
    void ClearSelector(void);

    bool RectInField(Rect r);

    void Disposal_Timer(void *data);
    void Disposal_MouseClick(void);
    void Disposal_MouseMove(void);
    void Disposal_HitChToCh(void* data);

    void Game_Timer(void *data);
    void Game_MouseClick(void);
    void Game_MouseMove(void);
    void Game_HitChToCh(void* data);
};

#endif // EXAMPLE_MODEL_H
