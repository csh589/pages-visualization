#Mission2 Extract the pages where characters exist


##2.1 Background


The overall visualization shows us the words inside the object by adjust the opacity. But the words are overlapped and can not be recognized easily. Additional, the noise is of high gray level, meaning that they obscured the words. There are two ways to extract the words out of the object. The first is Isosurface, and the other is using reslice class.


##2.2 Gaussian smooth filter


Before doing any other procedures, we need to deal with the noise. Noticing that the noise are almost points, they would become smooth when they are averaged by the surrounding points. And when the noise points are averaged, the points forming words need to be maintain their gray level. We can find that Gaussian smooth filter can deal with this problem. For a point in the picture, the filter calculate a weighted mean instead of the original value, which means, close points make more influence on the value. So the points of the characters remain the same, while the noise points are removed.
##2.3 Isosurface


Through Isosurface expression, the elements whose gray level are lower than a certain value would be set at 0 opacity. So the surface and blank pages would be hidden and only the words are visible. Since we use ray casting method to render the object, the isosurface operation can be easily done by setting the mapper with RayCastIsosurface function.

![](https://github.com/csh589/pages-visualization/raw/master/Result-Pictures/Isosurface.png)
<br><br>
##2.4 Slice and Image combine


If we hope to locate where the characters are or more clearly see the layered words, we can slice the object to extract what we want. When the sliced pictures are extracted, we can easily distinguish the ones with characters and the ones being blank. Limited by the compute power of the PC, we can only do the slice for part of the pages. But the slice can be done for several times, then we can use the Append class to combine the slice pictures in Y direction to get a picture of whole scale.
##2.5 Result Images


Even though the reslice class help us to extract most of the pages where characters located in, there are still two problems about the result. Firstly, there are still overlapped characters in some picture, because the reslice class would generate a value for the blank layer with linear interpolation. Furthermore, we have to recognize the pictures by ourselves rather than automatically by computers.


The solution of these two problem can be stated as following advice: 


1. If we slice the pages finely enough, there must be a boundary where the characters are just be in the specific position. But it also refer to a new problem that how to extract the pictures without overlapping characters. 


2. In order to extract the meaningful pictures automatically, we need to check the configuration of the pixels. For example, build a list of possible pixels' configration about the 26 English characters, then when the program is checking the pixels, compared the current configuration to the list. Once if the configuration match one of the options in the list, extract the corresponding pages. This list can be done by Machine Learning.


The result is displayed as following pictures:
![](https://github.com/csh589/pages-visualization/blob/master/Result-Pictures/slice-1.png)
![](https://github.com/csh589/pages-visualization/blob/master/Result-Pictures/slice-2.png)
![](https://github.com/csh589/pages-visualization/blob/master/Result-Pictures/slice-3.png)
![](https://github.com/csh589/pages-visualization/blob/master/Result-Pictures/slice-4.png)
![](https://github.com/csh589/pages-visualization/blob/master/Result-Pictures/slice-5.png)
![](https://github.com/csh589/pages-visualization/blob/master/Result-Pictures/slice-6.png)
![](https://github.com/csh589/pages-visualization/blob/master/Result-Pictures/slice-7.png)
![](https://github.com/csh589/pages-visualization/blob/master/Result-Pictures/slice-8.png)
![](https://github.com/csh589/pages-visualization/blob/master/Result-Pictures/slice-9.png)
![](https://github.com/csh589/pages-visualization/blob/master/Result-Pictures/slice-10.png)
![](https://github.com/csh589/pages-visualization/blob/master/Result-Pictures/slice-11.png)
![](https://github.com/csh589/pages-visualization/blob/master/Result-Pictures/slice-12.png)
![](https://github.com/csh589/pages-visualization/blob/master/Result-Pictures/slice-13.png)
![](https://github.com/csh589/pages-visualization/blob/master/Result-Pictures/slice-14.png)
