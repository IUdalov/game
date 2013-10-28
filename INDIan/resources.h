#ifndef CRESOURCE_H
#define CRESOURCE_H

//#include "dependences.h"
#include "transport.h"
#include "dependences.h"
#include "formuls.h"

/*#define BEGIN		void
#define INIT_BMP	INDIan::Resources::AddBmpFiles(void){
#define SETCOUNT     SetBmpCount(
#define PLEASE  );
#define END			}*/

namespace INDIan{
    class Tile;

    namespace Resources{
        extern void (*UserTilesLoader)(void);
        void AddTile(int idTile, QString fileName, QString maskFileName, int volume, int colums, int lines);
        Tile* GetTile( int num);
        int GetTileCount();
        void SetTileCount(int size);
    }
}

#endif // CRESOURCE_H
