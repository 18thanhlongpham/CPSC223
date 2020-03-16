#include<stdio.h>

typedef struct point point;

struct point{
  double x, y;
};

typedef struct rectangle rectangle;

struct rectangle{
  point ul;
  point br;
};

rectangle* rectangle_init(double ulx, double uly, double brx, double bry){
  ulx=0;
  uly=5;
  brx=5;
  bry=0;
}

void rectangle_move(rectangle* r, double x, double y){
  ulx=ulx+x;
  brx=brx+x;
  uly=uly+y;
  bry=bry+y;
}

void rectangle_expandby(rectangle* r, double expandby){
  x=x+expandby;
  y=y+expandby;
}

double rectangle_area(rectangle* r){
  double area;
  area=x*y;
  return area;
}

double rectangle_perimeter(rectangle* r){
  double perimeter;
  perimeter=(2*x)+(2*y);
  return perimeter;
}
