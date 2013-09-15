#ifndef CRESOURCE_H
#define CRESOURCE_H

#include "dependences.h"
#include "graphics.h"
#include "transport.h"

#define BEGIN		void
#define INIT_BMP	cResources::AddBmpFiles(void){
#define END			}

class cResources{
private:
    vector<xBmp*> BmpDim;
    bool fail;
public:
    cResources();
    ~cResources();
    void AddBmpFiles(void);
    void EndBmpSystem(void);
    void Add_BMP(unsigned int ID_BMP, QString file_name, QString mask_filename, unsigned int Volume, unsigned int colums, unsigned int lines);
    bool StartBmpSystem(void);
    bool Init_Resource(void);
    xBmp* Get_BMP(unsigned int num);
    int GetBmpCount();
    void DisResources();
};

#endif // CRESOURCE_H