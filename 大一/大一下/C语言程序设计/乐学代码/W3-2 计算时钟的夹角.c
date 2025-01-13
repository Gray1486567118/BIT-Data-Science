#include <stdio.h>  
  
int main()  
{  
    int hour, min, hour_storer;  
    double angle_h, angle_m, angle;  
    scanf("%d %d", &hour, &min);  
      
    hour_storer = hour;  
    hour %= 12;  
      
    angle_h = 30 * hour + 0.5 * min;  
    angle_m = 6 * min;  
    angle = angle_h - angle_m;  
      
    angle = (angle > 0) ? angle : -angle;  
    angle = (angle > 180) ? 360 - angle : angle;   
    angle = (angle > 0) ? angle : -angle;  
      
    printf("At %d:%02d the angle is %.1f degrees.\n", hour_storer, min, angle);  
    return 0;  
}
