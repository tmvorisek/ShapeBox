Aj Carvajal
HW4

In Project 2, did you notice how your code to create postscript for Horizontal and Vertical and Layered shapes is all very similar? It has a basic algorithm that is common to all three types, but some of the steps are different for each type. This is a perfect example of where to use the Template design pattern.

Fork a branch of your Project 2 repository so you can work on this assignment individually.

Refactor your code to use the Template design pattern so that there isn't any duplicated code in your create PostScript function. (These three composite shapes will all inherit from a common base class which implements the basic algorithm, which will call functions like moveToFirstPosition()which will be implemented in the derived classes.)

Completely optional, but if you enjoy this exercise, see if you can refactor to eliminate duplicated code in the getHeight() and getWidth() functions in these classes. This isn't as trivial, but I can think of a couple of ways to do it.
