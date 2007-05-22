#ifndef CRC32_H_
#define CRC32_H_

class CRC32
{
public:
	CRC32();
	void Init(unsigned long pol = 0x00000000);
	unsigned long GetCRC(char *rawData, int len);
	
protected:
	unsigned long Reflect(unsigned long r, char c);
	
private:
	unsigned long crc32Table[256];
};

#endif /*CRC32_H_*/
