#include "Tlo.h"
Tlo::Tlo()
{
	tekstura.loadFromFile("background.png");
	tlo.setTexture(tekstura);
}
void Tlo::draw(RenderWindow *okienko)
{
	okienko->draw(tlo);
}
