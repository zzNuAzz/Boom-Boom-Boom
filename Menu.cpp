#include "Menu.h"


bool MenuCharator::Point_In_Character(const SDL_Point & mouse, const Charactors & Charactor)
{
	for (int i = 0; i < 5; i++)
		if (SDL_PointInRect(&mouse, &MenuCharator::PickRect[Charactor][i])) return 1;
	return 0;

}

Charactors MenuCharator::getMousePointTo(SDL_Point & mouse)
{
	if (Point_In_Character(mouse, MO_MANG)) return MO_MANG;
	if (Point_In_Character(mouse, BE_BONG)) return BE_BONG;
	if (Point_In_Character(mouse, KHO_KHO)) return KHO_KHO;
	if (Point_In_Character(mouse, NHANH_NHAU)) return NHANH_NHAU;
	if (Point_In_Character(mouse, THIT_MO)) return THIT_MO;
	return NONE;
}
