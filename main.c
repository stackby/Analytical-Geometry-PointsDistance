#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <math.h>

typedef int point_t;

typedef struct point 
{
	point_t point_x;
	point_t point_y;
	
}point__s;

__attribute__((noinline)) static point__s *point_create (point_t, point_t);
__attribute__((noinline)) static void point_destroy (point__s *);
__attribute__((noinline)) static double point_distance (point__s *, point__s *);
__attribute__((noinline)) static double point_total_sum (int, ...);

int main (int argc, char **argv, char **envp)
{
	point__s *p1 = point_create (0xff, 0xdd);
	point__s *p2 = point_create (0xdb, 0xfe);
	point__s *p3 = point_create (0xcc, 0xbc);
	point__s *p4 = point_create (0xaf, 0xcd);
	
	double first_distance = point_distance (p1, p2);
	double second_distance = point_distance (p3, p4);
	
	double total_distance = point_total_sum (2, first_distance, second_distance);
	printf ("total distance: %.2f", total_distance);
	
	point_destroy (p1);
	point_destroy (p2);
	point_destroy (p3);
	point_destroy (p4);
	
	return 0;
}

point__s *point_create (point_t point_x, point_t point_y)
{
	auto point__s *new_point = (point__s *)malloc(sizeof (point__s));
		if (new_point == NULL) {
			fprintf (stderr, "%s - line %d", "\nMalloc Error\n", __LINE__);
			exit (EXIT_FAILURE);
		}
	new_point->point_x = point_x;
	new_point->point_y = point_y;
	return new_point;	
}

void point_destroy (point__s *point_s)
{
	free (point_s);
}

double point_distance (point__s *first, point__s *second)
{
	auto double points_sum = pow (first->point_x - second->point_x, 2)
					  + pow (first->point_y - second->point_y, 2);
	return sqrt (points_sum);				  
}

double point_total_sum (int args_counter, ...)
{
	__gnuc_va_list sum_list;
	va_start (sum_list, args_counter);
	auto double storing_sum = 0;
	
	for (auto int counter = 0; counter < args_counter; counter++) {
		storing_sum = va_arg (sum_list, double);
	}
	
	va_end (sum_list);
	return storing_sum;
}
