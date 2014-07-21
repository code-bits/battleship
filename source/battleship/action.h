
#pragma once


namespace Action
{
    class ActionBase
    {
    public:
        ActionBase(Player * target_, Player * origin_, CellCoord cc)
            : target(target_), origin(origin_), coords(cc) { }
        virtual void Execute(Game * game) = 0;

    protected:
        Player * target;
        Player * origin;
        CellCoord coords;
    };


    class CheckCellOf : public ActionBase
    {
    public:
        CheckCellOf(Player * target, Player * origin, CellCoord cc)
            : ActionBase(target, origin, cc) { }
        void Execute(Game * game);
    };


    class ReportMissTo : public ActionBase
    {
    public:
        ReportMissTo(Player * target, Player * origin, CellCoord cc)
            : ActionBase(target, origin, cc) { }
        void Execute(Game * game);
    };

    class ReportHitTo : public ActionBase
    {
    public:
        ReportHitTo(Player * target, Player * origin, CellCoord cc)
            : ActionBase(target, origin, cc) { }
        void Execute(Game * game);
    };

    class ReportKillTo : public ActionBase
    {
    public:
        ReportKillTo(Player * target, Player * origin, CellCoord cc)
            : ActionBase(target, origin, cc) { }
        void Execute(Game * game);
    };
}

