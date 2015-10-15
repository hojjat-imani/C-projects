#include <stdio.h>
#include <math.h>
#include <conio.h>
int main(void){
    float diagonal1, diagonal2, area, perimeter,angle, large_angle, small_angle;
    const double PI = 3.141592653589793;

    printf("Enter diagonals:");
    scanf("%f%f", &diagonal1, &diagonal2);
    
    area = diagonal1 * diagonal2 / 2;
    
    perimeter = 2 * sqrt(pow(diagonal1 , 2) + pow(diagonal2 , 2));
    
    angle = 2 * atan(diagonal1 / diagonal2);

    if (angle < (PI / 2)){
              small_angle = angle;
              large_angle = PI - angle;
              }
              else{
                   small_angle = PI - angle;
                   large_angle = angle;
                   }
    
    printf("\nArea: %f", area);
    printf("\nPerimeter: %f", perimeter);
    printf("\nLarge angle: %f", large_angle * 180 / PI);
    printf("\nSmall angle: %f", small_angle * 180 / PI);

    getch();
    return 0;
}
