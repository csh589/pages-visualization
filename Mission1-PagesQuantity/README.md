#Mission 1: Identify the pages in the volume data
<br>
##1.1 Way to recognize a single page


In order to identify the number of pages, we assume that there would be an easy way for us to recognize a single page.
At first, we may consider every paper has own the same thickness sothat we can calculate the number of the pages when we have known both the thickness of a page of paper and the thickness of the whole object. 
It is a easy method to evaluate the apporoximate number of pages, but it can not be a general and precise way due to the pressure of the pages will change the thickness of a single page, and the air gaps between pages also make influence on the whole thickness.
<br><br>
Then we can notice that the air gaps between pages are unavoidble, and the gray level of these gaps are different from the level of the pages. 
So the differences may contribute to the recognization of pages, if we can detect the boundary of air and paper.
<br><br>

##1.2 The sobel operator


To recognize the egde of the pages, we applied the sobel operator to an image which is a part of the data. 
Sobel operator is a general gradient operator that can calculate the difference of a pixel between others through a 3X3 template. 
In VTK, there is a class named vtkImageSobel2D, which offers encapsulation of the calculation. 
We can use the class in only one direction of the picture, so the calculation can be focused on the difference in Y direction without destroying the horizontal configration of the pages.


##1.3 The asdf


After applying sobel operator to the picture, we extract the edges of pages. 
However, most of the edges are discrete and short, which makes it hard to add up. 
Moreover, the operator also extract a lot of noise points. The points have high gray level and are possible to distube the counting of the pages. 
In order to work out the two problems, asdfasdfsadfasdfsadfasdf is used here.


