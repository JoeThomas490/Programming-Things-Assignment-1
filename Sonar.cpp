#include "Sonar.h"

SonarClass::SonarClass()
	: m_sonarSensor(SONAR::TRIGGER_PIN, SONAR::ECHO_PIN, SONAR::MAX_DISTANCE_CM)
{
}

float SonarClass::PingCm()
{
	float ping = m_sonarSensor.ping_cm();

	return ping;
}

SonarClass Sonar;
