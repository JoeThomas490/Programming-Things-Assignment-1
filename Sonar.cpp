#include "Sonar.h"

//Constructor to initialise the NewPing sensor object
SonarClass::SonarClass()
	: m_sonarSensor(SONAR::TRIGGER_PIN, SONAR::ECHO_PIN, SONAR::MAX_DISTANCE_CM)
{
}

//Get a ping from the sonar and return distance
//Returns:
//Distance of ping in CM (0 cm if no hit)
float SonarClass::PingCm()
{
	//Get ping from sonar component
	float ping = m_sonarSensor.ping_cm();
	//Return value from ping
	return ping;
}

SonarClass Sonar;
