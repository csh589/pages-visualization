#Mission 1: Identify the pages in the volume data
<br>
##1.1 Way to recognize a single page


In order to identify the number of pages, we assume that there would be an easy way for us to recognize a single page.
At first, we may consider every paper has own the same thickness sothat we can calculate the number of the pages when we have known both the thickness of a page of paper and the thickness of the whole object. 
It is a easy method to evaluate the approximate number of pages, but it can not be a general and precise way due to the pressure of the pages will change the thickness of a single page, and the air gaps between pages also make influence on the whole thickness.
<br><br>
Then we can notice that the air gaps between pages are unavoidable, and the gray level of these gaps are different from the level of the pages. 
So the differences may contribute to recognize pages, if we can detect the boundary of air and paper.
<br><br>

##1.2 Sobel operator


To recognize the edge of the pages, we applied the sobel operator to an image which is a part of the data. 
Sobel operator is a general gradient operator that can calculate the difference of a pixel between others through a 3X3 template. 
In VTK, there is a class named vtkImageSobel2D, which offers encapsulation of the calculation. 
We can use the class in only one direction of the picture, so the calculation can be focused on the difference in Y direction without destroying the horizontal configuration of the pages.


##1.3 Anisotropic Diffusion


After applying sobel operator to the picture, we extract the edges of pages. 
However, most of the edges are discrete and short, which makes it hard to add up. 
Moreover, the operator also extracts a lot of noise points in the picture. The points have high gray level and are possible to disturb the counting of the pages. 
<br><br>
In order to work out the two problems, Anisotropic Diffusion is used here. This diffusion can be used to remove the noise point and make the image smoother. The theory of this function is that the large diffusion occurs only in the place where value of gradient is small, while little diffusion occurs when value of gradient is rather big. This feature help us to remove the noise and be free of destroying edges.


##1.4 Pages counter


After preprocessing, the next step is to find a way to count the edges more precisely. It is easily to understand that the edges can be verified through the transformation of the value of pixel: Once the value enlarged, the counter increase at the same time. But even we preprocess the resulted picture, the edges are still discrete, which means simply count the pages in the Y direction may not work.
<br>
![](https://github.com/csh589/pages-visualization/raw/master/Result-Pictures/Sobel.tif)
<br>
According to statistic, if we do the count in a range, there must be a number which would be close to the true value. And considering the feature of the edges: discrete, when we count the pages in a range, most of the value will be smaller than the true value. So we try to count the pages in the Y direction, then get the largest one as the desired value. 
<br><br>
When we count pages in the field in the Y direction, we get a possible sum pages' number and compared them to another one read in another X coordinate. If we divide the field into parts, i.e. , count a part of pages in the Y direction and finally sum them up, the deviation of the counting will become smaller. Of course if we can divide the field into small enough parts, the result will almost be true value. Considering computing times, the field is divided into 4 parts.


##1.5 Result


According to the counted value in different ranges of X coordinate, we can get the average number of the counted pages: 37 pages. And the evaluation got from thickness of pages is 33 pages, proving that the pages counter works well. If we need to elevate the performance of this counter, we can divide the counting field more finely, and it can be sure that the value will distribute better, following statistic. So we can get a more precise expected value.
