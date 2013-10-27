#include "resources.h"


namespace INDIan{
    namespace Resources{
        vector<Tile*> tileDim;
        bool fail = false;
        int tilesResCount = 0;
        void (*UserTilesLoader)(void) = NULL;

        void EndTileSystem(void){
            for(int i = 0; i < (int)tileDim.size(); i++)
                if(tileDim[i])
                    delete tileDim[i];
            tileDim.clear();
        }
        void AddTile(int idTile, QString fileName, QString maskFileName, int volume, int colums, int lines){
            if(idTile < 1 || idTile >= (int)tilesResCount)
                return;
            Tile* New;
            if(tileDim[idTile]){
                New = tileDim[idTile];
            }
            else{
                tileDim[idTile] = New = new Tile;
            }
            if(!New->Create(fileName, maskFileName,volume,colums,lines)){
                delete New;
                New = NULL;
                fail = true;
                tileDim[idTile] = NULL;
            }
        }
        bool StartTileSystem(void){
            EndTileSystem();
            if(UserTilesLoader)
                UserTilesLoader();
            return !fail;
        }
        bool InitResource(void){
            if(!StartTileSystem())
                return false;
            return true;
        }
        Tile* GetTile( int num){
            if(num < 1 || num >= tilesResCount)
                return NULL;
            return	tileDim[num];
        }
        int GetTileCount(){
            return tileDim.size();
        }
        void DisableResources(){
            EndTileSystem();
        }
        void SetTileCount(int size){
            tilesResCount = size;
            tileDim.resize(tilesResCount, NULL);
        }

        class ResourcesModel : public Model{
        public:
            ResourcesModel() : Model(0, 0){
                Root::AccessModel(this);
            }
            ~ResourcesModel(){
            }
            void EventsHandler(int mess,void* data){
                switch(mess){
                case ME_CREATE:
                    InitResource();
                    break;
                case ME_DESTROY:
                    DisableResources();
                    break;
                default:
                    break;
                }
            }
        }ResModel;
    }
}
