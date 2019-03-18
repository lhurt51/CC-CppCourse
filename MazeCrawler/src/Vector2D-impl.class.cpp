/*******************************************************************************\
* Programmer Name:																*
* Liam Hurt																		*
*																				*
* Date:																			*
* 3/16/2019																		*
*																				*
* Assignment Requirement:														*
* 7.33 (Maze Traversal) The grid of hashes (#) and dots (.) in Fig. 7.29 is a	*
* two-dimensional builtin array representation of a maze. In the				*
* two-dimensional built-in array, the hashes represent the walls of the maze	*
* and the dots represent squares in the possible paths through the maze. Moves	*
* can be made only to a location in the built-in array that contains a dot.		*
* There is a simple algorithm for walking through a maze that guarantees to		*
* find the exit (assuming that there is an exit). If there is not an exit,		*
* you’ll arrive at the starting location again. Place your right hand on		*
* the wall to your right and begin walking forward. Never remove your hand		*
* from the wall. If the maze turns to the right, you follow the wall to the		*
* right. As long as you do not remove your hand from the wall, eventually		*
* you’ll arrive at the exit of the maze. There may be a shorter path than the	*
* one you’ve taken, but you are guaranteed to get out of the maze if you		*
* follow the algorithm.															*
*																				*
*  # # # # # # # # # # # #														*
*  # . . . # . . . . . . #														*
*  . . # . # . # # # # . #														*
*  # # # . # . . . . # . #														*
*  # . . . . # # # . # . .														*
*  # # # # . # . # . # . #														*
*  # . . # . # . # . # . #														*
*  # # . # . # . # . # . #														*
*  # . . . . . . . . # . #														*
*  # # # # # # . # # # . #														*
*  # . . . . . . # . . . #														*
*  # # # # # # # # # # # #														*
*																				*
* Write recursive function mazeTraverse to walk through the maze. The function	*
* should receive arguments that include a 12-by-12 built-in array of chars		*
* representing the maze and the starting location of the maze. As mazeTraverse	*
* attempts to locate the exit from the maze, it should place the character X	*
* in each square in the path. The function should display the maze after each	*
* move, so the user can watch as the maze is solved.							*
*																				*
\*******************************************************************************/

#include "Vector2D.class.cpp"

// All the template implementations so I can use all arithmetic data types
template class							Vector2D<int>;
template class							Vector2D<unsigned int>;
template class							Vector2D<short>;
template class							Vector2D<unsigned short>;
template class							Vector2D<long>;
template class							Vector2D<unsigned long>;
template class							Vector2D<long long>;
template class							Vector2D<unsigned long long>;
template class							Vector2D<double>;
template class							Vector2D<float>;
template int							DotProduct(const Vector2D<int>& a, const Vector2D<int>& b);
template unsigned int					DotProduct(const Vector2D<unsigned int>& a, const Vector2D<unsigned int>& b);
template short							DotProduct(const Vector2D<short>& a, const Vector2D<short>& b);
template unsigned short					DotProduct(const Vector2D<unsigned short>& a, const Vector2D<unsigned short>& b);
template long							DotProduct(const Vector2D<long>& a, const Vector2D<long>& b);
template unsigned long					DotProduct(const Vector2D<unsigned long>& a, const Vector2D<unsigned long>& b);
template long long						DotProduct(const Vector2D<long long>& a, const Vector2D<long long>& b);
template unsigned long long				DotProduct(const Vector2D<unsigned long long>& a, const Vector2D<unsigned long long>& b);
template double							DotProduct(const Vector2D<double>& a, const Vector2D<double>& b);
template float							DotProduct(const Vector2D<float>& a, const Vector2D<float>& b);
template int							CrossProduct(const Vector2D<int>& a, const Vector2D<int>& b);
template unsigned int					CrossProduct(const Vector2D<unsigned int>& a, const Vector2D<unsigned int>& b);
template short							CrossProduct(const Vector2D<short>& a, const Vector2D<short>& b);
template unsigned short					CrossProduct(const Vector2D<unsigned short>& a, const Vector2D<unsigned short>& b);
template long							CrossProduct(const Vector2D<long>& a, const Vector2D<long>& b);
template unsigned long					CrossProduct(const Vector2D<unsigned long>& a, const Vector2D<unsigned long>& b);
template long long						CrossProduct(const Vector2D<long long>& a, const Vector2D<long long>& b);
template unsigned long long				CrossProduct(const Vector2D<unsigned long long>& a, const Vector2D<unsigned long long>& b);
template double							CrossProduct(const Vector2D<double>& a, const Vector2D<double>& b);
template float							CrossProduct(const Vector2D<float>& a, const Vector2D<float>& b);
template float							EuclideanNorm(const Vector2D<float>& v);
template Vector2D<float>				Normal(const Vector2D<float>& v);
template Vector2D<int>					Perpendicular(const Vector2D<int>& v);
template Vector2D<unsigned int>			Perpendicular(const Vector2D<unsigned int>& v);
template Vector2D<short>				Perpendicular(const Vector2D<short>& v);
template Vector2D<unsigned short>		Perpendicular(const Vector2D<unsigned short>& v);
template Vector2D<long>					Perpendicular(const Vector2D<long>& v);
template Vector2D<unsigned long>		Perpendicular(const Vector2D<unsigned long>& v);
template Vector2D<long long>			Perpendicular(const Vector2D<long long>& v);
template Vector2D<unsigned long long>	Perpendicular(const Vector2D<unsigned long long>& v);
template Vector2D<double>				Perpendicular(const Vector2D<double>& v);
template Vector2D<float>				Perpendicular(const Vector2D<float>& v);
template bool							Inersect(const Vector2D<int>& line1A, const Vector2D<int>& line1B, const Vector2D<int>& line2A, const Vector2D<int>& line2B);
template bool							Inersect(const Vector2D<unsigned int>& line1A, const Vector2D<unsigned int>& line1B, const Vector2D<unsigned int>& line2A, const Vector2D<unsigned int>& line2B);
template bool							Inersect(const Vector2D<short>& line1A, const Vector2D<short>& line1B, const Vector2D<short>& line2A, const Vector2D<short>& line2B);
template bool							Inersect(const Vector2D<unsigned short>& line1A, const Vector2D<unsigned short>& line1B, const Vector2D<unsigned short>& line2A, const Vector2D<unsigned short>& line2B);
template bool							Inersect(const Vector2D<long>& line1A, const Vector2D<long>& line1B, const Vector2D<long>& line2A, const Vector2D<long>& line2B);
template bool							Inersect(const Vector2D<unsigned long>& line1A, const Vector2D<unsigned long>& line1B, const Vector2D<unsigned long>& line2A, const Vector2D<unsigned long>& line2B);
template bool							Inersect(const Vector2D<long long>& line1A, const Vector2D<long long>& line1B, const Vector2D<long long>& line2A, const Vector2D<long long>& line2B);
template bool							Inersect(const Vector2D<unsigned long long>& line1A, const Vector2D<unsigned long long>& line1B, const Vector2D<unsigned long long>& line2A, const Vector2D<unsigned long long>& line2B);
template bool							Inersect(const Vector2D<double>& line1A, const Vector2D<double>& line1B, const Vector2D<double>& line2A, const Vector2D<double>& line2B);
template bool							Inersect(const Vector2D<float>& line1A, const Vector2D<float>& line1B, const Vector2D<float>& line2A, const Vector2D<float>& line2B);
template Vector2D<int>					GetInersect(const Vector2D<int>& line1A, const Vector2D<int>& line1B, const Vector2D<int>& line2A, const Vector2D<int>& line2B);
template Vector2D<unsigned int>			GetInersect(const Vector2D<unsigned int>& line1A, const Vector2D<unsigned int>& line1B, const Vector2D<unsigned int>& line2A, const Vector2D<unsigned int>& line2B);
template Vector2D<short>				GetInersect(const Vector2D<short>& line1A, const Vector2D<short>& line1B, const Vector2D<short>& line2A, const Vector2D<short>& line2B);
template Vector2D<unsigned short>		GetInersect(const Vector2D<unsigned short>& line1A, const Vector2D<unsigned short>& line1B, const Vector2D<unsigned short>& line2A, const Vector2D<unsigned short>& line2B);
template Vector2D<long>					GetInersect(const Vector2D<long>& line1A, const Vector2D<long>& line1B, const Vector2D<long>& line2A, const Vector2D<long>& line2B);
template Vector2D<unsigned long>		GetInersect(const Vector2D<unsigned long>& line1A, const Vector2D<unsigned long>& line1B, const Vector2D<unsigned long>& line2A, const Vector2D<unsigned long>& line2B);
template Vector2D<long long>			GetInersect(const Vector2D<long long>& line1A, const Vector2D<long long>& line1B, const Vector2D<long long>& line2A, const Vector2D<long long>& line2B);
template Vector2D<unsigned long long>	GetInersect(const Vector2D<unsigned long long>& line1A, const Vector2D<unsigned long long>& line1B, const Vector2D<unsigned long long>& line2A, const Vector2D<unsigned long long>& line2B);
template Vector2D<double>				GetInersect(const Vector2D<double>& line1A, const Vector2D<double>& line1B, const Vector2D<double>& line2A, const Vector2D<double>& line2B);
template Vector2D<float>				GetInersect(const Vector2D<float>& line1A, const Vector2D<float>& line1B, const Vector2D<float>& line2A, const Vector2D<float>& line2B);
