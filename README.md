# cpp basic signal processing - smarties counter

The present code is the product of a school project suggested by prof. J.-C. Demers from CVM.

The goal was to count the number of smarties of each color present in the image. The code was written with C++ 17 and uses Qt for the interface.

The current master version (pictured) is the most advanced, with adequate lighting equalization, edge and circle detection, but also very redundant code.

The version on dev is a failed attempt at making the code prettier, by using multiple levels of abstraction and inheritance of process strategies. The result is 7-15x slower than the redundant code on master, albeit better looking. 

First photo is after Sobel edge detection, second after approximate circle correlation. Center picture is light map (33 reference images, gaussian + max filter(s)).
![result2](https://i.imgur.com/XFwVQg7.png)
![result](https://i.imgur.com/c4m9kCV.png)

note: J.-C. Demers is the author of the Qt classes and ImgDemo.
