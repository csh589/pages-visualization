#Overall Visualization


##Pipeline



The visual pipeline of VTK is similar to the pipeline in KVS, including reader,filter,actor,mapper,renderer. The volume data is read by the reader and processed by the filter, then the mapper offers settings for display. At last, the renderer generates the surface of volume data, and creates a window for data to display.

##Volume Property


There are two main functions for displaying, the color map function and the opacity function. In order to properly display the elements of the pictures, these functions need to be set correctly, so the gray levels of them are necessary. It is easy to know that the gray level of the pictures are above 40000, and the functions can be set according to the value.
##Result


Limited by the RAM, this visualization read only a part of the images in raw data (200 images). Further, we can add vtkRendererInteraction class in the program and change the setting of the interact style to achieve a better display.<br><br>
![image](https://github.com/csh589/pages-visualization/raw/master/Result-Pictures/Overall-1.png)
![image](https://github.com/csh589/pages-visualization/raw/master/Result-Pictures/Overall-2.png)
![image](https://github.com/csh589/pages-visualization/raw/master/Result-Pictures/Overall-3.png)
