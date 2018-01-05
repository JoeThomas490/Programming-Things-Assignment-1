#ifndef _CORRIDOR_H_
#define _CORRIDOR_H_

class Corridor
{
public:
	Corridor();
	~Corridor();

	unsigned int ID = -1;

	Corridor* m_pFromCorridor = nullptr;

	float m_fTraversalTimeMS = 0;
};

#endif
