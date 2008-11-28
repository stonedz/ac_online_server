#include "MapData.h"

MapData::MapData(const Uint16& x, const Uint16& y, std::ifstream* pFin)
	:myX(x),
	myY(y),
	myData(new coord[x*y])
{	
	Uint32 counter = 0;
	Uint32 tot = x*y;

	for(;counter < tot;counter++){
		pFin->read((char *) (&(myData[counter].z)),sizeof(uint8_t));
		pFin->read((char *) (&(myData[counter].t_type)),sizeof(myData[counter].t_type));
		std::cout<< "counter : "<< counter << std::endl;
		std::cout<< "z: " << (int)(myData[counter].z)<< std::endl;
		std::cout<< "type: " << myData[counter].t_type << std::endl;
	}
	
}


MapData::~MapData()
{
	delete[] myData;
}


