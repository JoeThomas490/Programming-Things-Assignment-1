#ifndef _ROOM_H_
#define _ROOM_H_

class Room
{
public:
	Room();
	~Room();

	unsigned int ID = -1;

	bool m_bHasBeenSearched = false;

	bool m_bObjectDetected = false;
	DIRECTION m_eDirection;
};


#endif

