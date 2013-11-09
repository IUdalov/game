#ifndef EXAMPLE_MODEL_H
#define EXAMPLE_MODEL_H

#include "../inits/declarations.h"
#include "../INDIan/core_includes.h"
#include "../physics/physics.h"

using namespace INDIan;

struct ObjChecker{
    double weight;
    DCoord vSpeed;
    CheckersType type;
    int master;
    double angle;
    double angle_speed;
};

class CheckerManager : Model{
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
        _2nd,
        _ai
    };
    enum GamePart{
        Start = 1,
        Disposal,
        Game,
        End
    };
public:
    short CheckEnable;
    vector<Object> arrows;
    IDn CheckChecker;
    int CurNumMoveCh;
    bool ChangeProgressAfterStop;

    //++параметры поля
    Rect FieldRect;
    int FieldMiddle;
    //--

    //++параметры расстановщика
    PosManager selector;
    Coord point_to;
    bool NeedFlyToPos;
    DCoord vMoveAfterHit;
    //--

    //++общие параметры игры
    GameParam game_param;
    int game_part;
    int players_progress;
    int sec_player_control;
    int points_1st;
    int points_2nd;
    int alive_che1_count;
    int alive_che2_count;
    //--

    CheckerManager();
    ~CheckerManager();
    void CreateArrow( Object& arrow, double x_c, double y_c, double x_l, double y_l, double length, int max_num_arrow = 10);
    virtual void EventsHandler(int mess, void *data);

    void LocateSelector(void);
    void PrepareForReturn(int type);
    void ClearSelector(void);

    bool RectInField(Rect r);
    bool RectInRect(Rect r, Rect rf);
    bool RectOutField(Rect r);
    bool RectOutRect(Rect r1, Rect r2);
    bool CheckerOutRect(DCoord crd, double radius, Rect r);
    bool CheckerInPartOfField(Rect rect, short part);

    void Disposal_Timer(void *data);
    void Disposal_MouseDown(IDn,SMouse);
    void Disposal_MouseUp(void);
    void Disposal_MouseMove(void);
    void Disposal_HitChToCh(void* data);

    void Game_Timer(void *data);
    void Game_MouseDown(IDn, SMouse);
    void Game_MouseUp(void);
    void Game_MouseMove(void);
    void Game_HitChToCh(void* data);

    void AIDisposalChecks(void);
    void AIMakeStep(void);

    void RecalcActualAliveCheCount();
};

#endif // EXAMPLE_MODEL_H
