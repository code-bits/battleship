
#include "action.h"
#include "stdafx.h"


namespace Action
{
    void CheckCellOf::Execute(Game * game)
    {
        std::cout << "Execute Check\n";
        target->CheckIfHit(coords, origin, game);
    }


    void ReportMissTo::Execute(Game * game)
    {
        target->OnMiss(coords, origin, game);
        target->Wait();
        origin->Move();
    }


    void ReportHitTo::Execute(Game * game)
    {
        target->OnHit(coords, origin, game);
        target->Move();
        origin->Wait();
    }


    void ReportKillTo::Execute(Game * game)
    {
        target->OnKill(coords, origin, game);
        target->Move();
        origin->Wait();
    }
}
