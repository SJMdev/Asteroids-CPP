/***********************************************************************
 * Header File:
 *    Point : The representation of a position on the screen
 * Author:
 *    Br. Helfrich
 * Summary:
 *    Everything we need to know about a location on the screen, including
 *    the location and the bounds.
 ************************************************************************/

#ifndef POINT_H
#define POINT_H

#include <iostream> // needed for insertion and extraction operator

/*********************************************
 * POINT
 * A single position.  
 *********************************************/
class Point
{
public:
   // constructors
   Point()            : x(0.0), y(0.0),
                        check(false), dead(false), wrap(true)   {}
   Point(bool check)  : x(0.0), y(0.0),
                        check(check), dead(false), wrap(true)   {}
   Point(double x, double y);
   Point(const Point & point) { *this = point; }

   // getters
   double getX()       const { return x;              }
   double getY()       const { return y;              }
   bool  getCheck()   const { return check;          }
   bool  isDead()     const { return dead;           }
   double getXMin()    const { return xMin;           }
   double getXMax()    const { return xMax;           }
   double getYMin()    const { return yMin;           }
   double getYMax()    const { return yMax;           }
   bool  getWrap()    const { return wrap;           }

   // setters
   void setX(double x);
   void setY(double y);
   void addX(double dx)      { setX(getX() + dx);     }
   void addY(double dy)      { setY(getY() + dy);     }
   void setCheck(bool f)    { check = f;             }
   void setWrap(bool f)     { 
//	   std::cout << "Wrap = " << f << std::endl;
	   wrap = f;
   }
   void kill()              { dead = true;           }
   void resurrect()         { dead = false;          }
   const Point & operator = (const Point & rhs);

   static double xMin; // minimum extent of the x position
   static double xMax; // maximum extent of the x position
   static double yMin; // minimum extent of the y position
   static double yMax; // maximum extent of the y position

private:
   double x;           // horizontal position
   double y;           // vertical position
   bool  check;       // do bounds checking
   bool  dead;        // have we exceed our bounds?
   bool  wrap;        // do we wrap around the edge?
};

// stream I/O useful for debugging
std::ostream & operator << (std::ostream & out, const Point & pt);
std::istream & operator >> (std::istream & in,        Point & pt);

#endif // POINT_H
